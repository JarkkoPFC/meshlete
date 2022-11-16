//============================================================================
// Meshlete - Meshlet-based 3D object converter
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "geo_setup.h"
#include "vbuf_expr.h"
#include "sxp_src/core/math/geo3.h"
#include "sxp_src/core/fsys/fsys.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// locals
//============================================================================
namespace
{
  //==========================================================================
  // init_vbuf_expression_parser
  //==========================================================================
  void init_vbuf_expression_parser(vbuf_expression_parser_t &parser_, const sphere3f &mesh_bvol_, const mesh_vertex_buffer &vbuf_)
  {
    // setup functions and globals
    typedef vbuf_expression_parser_t::var_t var_t;
    init_vbuf_expression_parser_funcs(parser_);
    parser_.set_var("mesh_bvol_pos", var_t(&mesh_bvol_.pos, 1));
    parser_.set_var("mesh_bvol_rad", var_t(&mesh_bvol_.rad, 1));

    // access vertex data streams
    uint32_t num_vtx=(uint32_t)vbuf_.num_vertices();
    const vec3f *pos_data=(const vec3f*)vbuf_.vertex_channel(vtxchannel_position);
    const vec3f *normal_data=(const vec3f*)vbuf_.vertex_channel(vtxchannel_normal);
    const vec3f *binormal_data=(const vec3f*)vbuf_.vertex_channel(vtxchannel_binormal);
    const vec3f *tangent_data=(const vec3f*)vbuf_.vertex_channel(vtxchannel_tangent);
    const vec2f *uv_data[4];
    for(unsigned uvi=0; uvi<4; ++uvi)
      uv_data[uvi]=(const vec2f*)vbuf_.vertex_channel(vtxchannel_uv, uvi);
    const vec4f *color_data[4];
    for(unsigned ci=0; ci<4; ++ci)
      color_data[ci]=(const vec4f*)vbuf_.vertex_channel(vtxchannel_color, ci);

    // setup vertex data variables
    parser_.set_var("pos", pos_data?var_t(pos_data, num_vtx):var_t(&vec3f::s_zero, 1));
    parser_.set_var("normal", normal_data?var_t(normal_data, num_vtx):var_t(&vec3f::s_zero, 1));
    parser_.set_var("binormal", binormal_data?var_t(binormal_data, num_vtx):var_t(&vec3f::s_zero, 1));
    parser_.set_var("tangent", tangent_data?var_t(tangent_data, num_vtx):var_t(&vec3f::s_zero, 1));
    parser_.set_var("uv", uv_data[0]?var_t(uv_data[0], num_vtx):var_t(&vec2f::s_zero, 1));
    parser_.set_var("uv0", uv_data[0]?var_t(uv_data[0], num_vtx):var_t(&vec2f::s_zero, 1));
    parser_.set_var("uv1", uv_data[1]?var_t(uv_data[1], num_vtx):var_t(&vec2f::s_zero, 1));
    parser_.set_var("uv2", uv_data[2]?var_t(uv_data[2], num_vtx):var_t(&vec2f::s_zero, 1));
    parser_.set_var("uv3", uv_data[3]?var_t(uv_data[3], num_vtx):var_t(&vec2f::s_zero, 1));
    parser_.set_var("color", color_data[0]?var_t(color_data[0], num_vtx):var_t(&vec4f::s_zero, 1));
    parser_.set_var("color0", color_data[0]?var_t(color_data[0], num_vtx):var_t(&vec4f::s_zero, 1));
    parser_.set_var("color1", color_data[1]?var_t(color_data[1], num_vtx):var_t(&vec4f::s_zero, 1));
    parser_.set_var("color2", color_data[2]?var_t(color_data[2], num_vtx):var_t(&vec4f::s_zero, 1));
    parser_.set_var("color3", color_data[3]?var_t(color_data[3], num_vtx):var_t(&vec4f::s_zero, 1));

    if(normal_data && binormal_data && tangent_data)
    {
      // generate quaternion and 32bit quantized rotations from the tangent frame
      vec4f *qframe_data=(vec4f*)PFC_MEM_ALLOC(num_vtx*sizeof(vec4f));
      int32_t *tbn32_data=(int32_t*)PFC_MEM_ALLOC(num_vtx*sizeof(uint32_t));
      for(uint32_t i=0; i<num_vtx; ++i)
      {
        vec3f n=normal_data[i];
        vec3f b=unit_z(cross(n, tangent_data[i]));
        if(norm2(b)>0.0f)
        {
          // setup quaternion rotation
          vec3f t=cross(b, n);
          bool is_right_handed=dot(b, binormal_data[i])<0.0f;
          quatf q;
          convert(q, mat33f(t, b, n));
          qframe_data[i].set(q.x, q.y, q.z, is_right_handed?1.0f:0.0f);

          // setup 32bit quantized rotation
          uint32_t tbn32=quantize_mat33_32(mat33f(t, is_right_handed?-b:b, n));
          tbn32_data[i]=tbn32;
        }
        else
        {
          qframe_data[i].set(0.0f, 0.0f, 0.0f, 1.0f);
          vec2f oct=vec3_to_oct2x1(n);
          uint32_t qx=uint32_t((oct.x+2.0f)*(0.25f*2047.0f)+0.5f); // 11 bits
          uint32_t qy=uint32_t((oct.y+1.0f)*(0.5f*1023.0f)+0.5f);  // 10 bits
          tbn32_data[i]=(qy<<11)|qx;
        }
      }

      // setup expression variables
      parser_.set_var("qframe", var_t(qframe_data, num_vtx));
      ((var_t*)parser_.var("qframe"))->pinned_owner=true;
      parser_.set_var("tbn32", var_t(tbn32_data, num_vtx));
      ((var_t*)parser_.var("tbn32"))->pinned_owner=true;
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // e_vtx_element_type
  //==========================================================================
  enum e_vtx_element_type
  {
    vtxelemtype_none,
    // integer formats
    vtxelemtype_int8,
    vtxelemtype_uint8,
    vtxelemtype_int16,
    vtxelemtype_uint16,
    vtxelemtype_int32,
    vtxelemtype_uint32,
    // float formats
    vtxelemtype_float16,
    vtxelemtype_float32,
  };
  PFC_ENUM(e_vtx_element_type);
  //----

  #define PFC_ENUM_TYPE e_vtx_element_type
  #define PFC_ENUM_PREFIX vtxelemtype_
  #define PFC_ENUM_VALS PFC_ENUM_VAL(int8)\
                        PFC_ENUM_VAL(uint8)\
                        PFC_ENUM_VAL(int16)\
                        PFC_ENUM_VAL(uint16)\
                        PFC_ENUM_VAL(int32)\
                        PFC_ENUM_VAL(uint32)\
                        PFC_ENUM_VAL(float16)\
                        PFC_ENUM_VAL(float32)
  #include "sxp_src/core/enum.inc"
  //----

  unsigned vtx_element_type_size(e_vtx_element_type type_)
  {
    switch(type_)
    {
      case vtxelemtype_int8:     return 1;
      case vtxelemtype_uint8:    return 1;
      case vtxelemtype_int16:    return 2;
      case vtxelemtype_uint16:   return 2;
      case vtxelemtype_int32:    return 4;
      case vtxelemtype_uint32:   return 4;
      case vtxelemtype_float16:  return 2;
      case vtxelemtype_float32:  return 4;
      default: PFC_ERROR(("Unsupported vertex element type \"%s\"\r\n", enum_string(type_)));
    }
    return 0;
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // vtx_element
  //==========================================================================
  struct vtx_element
  { PFC_MONO(vtx_element) {PFC_VAR2(type, expr);}
    e_vtx_element_type type;
    heap_str expr;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // vtx_format
  //==========================================================================
  struct vtx_format
  { PFC_MONO(vtx_format) {PFC_VAR2(id, name);}
    PFC_INLINE bool operator==(const char *name_) const  {return name==name_;}
    //------------------------------------------------------------------------

    uint8_t id;
    heap_str name;
    array<vtx_element> elements;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // vtx_float16
  //==========================================================================
  struct vtx_float16
  {
    PFC_INLINE vtx_float16(float32_t v_)  {data=fp32_to_s16f(clamp(v_, -65504.0f, 65504.0f));}
    PFC_INLINE vtx_float16(int32_t v_)    {data=fp32_to_s16f(float32_t(clamp(v_, -65504, 65504)));}
    uint16_t data;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // vtx_id
  //==========================================================================
  struct vtx_id
  {
    PFC_INLINE bool operator<(const vtx_id &vid_) const  {return crc32<vid_.crc32;}
    uint32_t crc32;
    uint32_t orig_vidx;
  };
} // namespace <anonymous>
//----------------------------------------------------------------------------


//============================================================================
// setup_geometry
//============================================================================
bool pfc::setup_mesh_geometry(const mesh &mesh_, const mesh_geometry_setup_cfg &cfg_, mesh_geometry &mgeo_, mesh_geometry_container &mgeo_container_)
{
  // parse vertex config
  logf("> Setting up geometry...\r\n");
  array<vtx_format> vtx_formats;
  {
    owner_ptr<bin_input_stream_base> xmlf=afs_open_read(cfg_.vcfg_file);
    if(!xmlf.data)
    {
      errorf(">   Error: Unable to read vertex config file \"%s\"\r\n", cfg_.vcfg_file);
      return false;
    }
    xml_stream_parser xml_parser;
    xml_parser.begin_element("vertex_formats")
                .begin_element("format", vtx_formats, true)
                  .begin_element("element", &vtx_format::elements, true).end_element()
                .end_element()
              .end_element();
    xml_input_stream xmls(*xmlf);
    xml_parser.process_stream(xmls);
  }

  // calculate vertex size
  const vtx_format *vfmt=linear_search(vtx_formats.data(), vtx_formats.size(), cfg_.vfmt_name);
  if(!vfmt)
  {
    errorf(">   Error: No definition for vertex format \"%s\" (-vf)\r\n", cfg_.vfmt_name);
    return false;
  }
  unsigned vtx_size=0;
  for(const vtx_element &elem_: vfmt->elements)
    vtx_size+=vtx_element_type_size(elem_.type);
  logf(">   Vertex format: \"%s\" (%i bytes)\r\n", cfg_.vfmt_name, vtx_size);

  // calculate mesh bounding volume
  const mesh_vertex_buffer &mesh_vbuf=mesh_.vertex_buffer(0);
  const vec3f *mesh_pos_data=(const vec3f*)mesh_vbuf.vertex_channel(vtxchannel_position);
  uint32_t num_mesh_vtx=(uint32_t)mesh_vbuf.num_vertices();
  seed_oobox3f mesh_sbox=seed_oobox3_discrete(mesh_pos_data, num_mesh_vtx, discrete_axes3_49);
  sphere3f mesh_bvol=bounding_sphere3_exp(mesh_pos_data, num_mesh_vtx, mesh_sbox, true);

  // generate temporary vertex buffer
  uint32_t tmp_vbuf_size=(uint32_t)num_mesh_vtx*vtx_size;
  owner_data tmp_vbuf=PFC_MEM_ALLOC(tmp_vbuf_size);
  {
    uint8_t *tmp_vbuf_data=(uint8_t*)tmp_vbuf.data;
    mem_zero(tmp_vbuf_data, tmp_vbuf_size);
    vbuf_expression_parser_t expr_parser;
    init_vbuf_expression_parser(expr_parser, mesh_bvol, mesh_vbuf);
    unsigned velem_idx=0;
    for(const vtx_element &elem_: vfmt->elements)
    {
      const char *expr=elem_.expr.c_str();
      vbuf_expression_value v=expr_parser.evaluate(expr);
      if(!v.num_data_elems)
      {
        errorf(">   Error: Failed to evaluate vertex format \"%s\" expression for element #%i: \"%s\"\r\n", cfg_.vfmt_name, velem_idx+1, expr);
        return false;
      }
      switch(elem_.type)
      {
        case vtxelemtype_int8:    v.get((int8_t*)tmp_vbuf_data, num_mesh_vtx, vtx_size); break;
        case vtxelemtype_uint8:   v.get((uint8_t*)tmp_vbuf_data, num_mesh_vtx, vtx_size); break;
        case vtxelemtype_int16:   v.get((int16_t*)tmp_vbuf_data, num_mesh_vtx, vtx_size); break;
        case vtxelemtype_uint16:  v.get((uint16_t*)tmp_vbuf_data, num_mesh_vtx, vtx_size); break;
        case vtxelemtype_int32:   v.get((int32_t*)tmp_vbuf_data, num_mesh_vtx, vtx_size); break;
        case vtxelemtype_uint32:  v.get((uint32_t*)tmp_vbuf_data, num_mesh_vtx, vtx_size); break;
        case vtxelemtype_float16: v.get((vtx_float16*)tmp_vbuf_data, num_mesh_vtx, vtx_size); break;
        case vtxelemtype_float32: v.get((float32_t*)tmp_vbuf_data, num_mesh_vtx, vtx_size); break;
      }
      tmp_vbuf_data+=vtx_element_type_size(elem_.type);
      ++velem_idx;
    }
  }

  // remove vertex duplicates for the target vertex format
  mgeo_container_.vbuf=PFC_MEM_ALLOC(tmp_vbuf_size);
  array<uint32_t> reindices(num_mesh_vtx, 0xffffffff);
  uint32_t *reindices_data=reindices.data();
  uint32_t num_vtx=0;
  {
    // create crc32 (of data) sorted list of vertices
    array<vtx_id> vtx_ids(num_mesh_vtx);
    vtx_id *vtx_ids_data=vtx_ids.data();
    const uint8_t *tmp_vbuf_data=(uint8_t*)tmp_vbuf.data;
    for(uint32_t vidx=0; vidx<num_mesh_vtx; ++vidx)
    {
      vtx_id &vid=vtx_ids_data[vidx];
      vid.crc32=crc32(tmp_vbuf_data+vidx*vtx_size, vtx_size);
      vid.orig_vidx=vidx;
    }
    quick_sort(vtx_ids_data, num_mesh_vtx);

    // reindex vertices and build new vertex buffer
    uint8_t *vbuf_data=(uint8_t*)mgeo_container_.vbuf.data;
    for(uint32_t vidx=0; vidx<num_mesh_vtx; ++vidx)
    {
      // check for already reindexed vertex
      const vtx_id &vid=vtx_ids_data[vidx];
      if(reindices_data[vid.orig_vidx]!=0xffffffff)
        continue;

      // reindex the vertex and add new vertex buffer data
      reindices_data[vid.orig_vidx]=num_vtx;
      const void *ref_vdata=tmp_vbuf_data+vid.orig_vidx*vtx_size;
      mem_copy(vbuf_data+num_vtx*vtx_size, ref_vdata, vtx_size);
      mgeo_container_.vertices.push_back(mesh_pos_data[vid.orig_vidx]);

      // search for duplicates
      uint32_t ref_crc32=vid.crc32;
      for(uint32_t tvidx=vidx+1; tvidx<num_mesh_vtx; ++tvidx)
      {
        const vtx_id &tvid=vtx_ids_data[tvidx];
        if(ref_crc32!=tvid.crc32)
          break;
        if(mem_eq(ref_vdata, tmp_vbuf_data+tvid.orig_vidx*vtx_size, vtx_size))
          reindices_data[tvid.orig_vidx]=num_vtx;
      }
      ++num_vtx;
    }
  }

  // setup geometry segments
  usize_t num_mesh_segs=mesh_.num_segments();
  const uint32_t *mesh_indices=mesh_.indices();
  mgeo_container_.indices.reserve(mesh_.num_indices());
  for(unsigned msi=0; msi<num_mesh_segs; ++msi)
  {
    // validate primitive type
    const mesh_segment &mseg=mesh_.segment(msi);
    if(mseg.primitive_type!=meshprim_trilist && mseg.primitive_type!=meshprim_tristrip)
      continue;

    // add new segment
    mesh_geometry_segment &mgseg=mgeo_container_.segs.push_back();
    mgseg.material_id=crc32(mseg.material_name.c_str());
    mgseg.start_tri_idx=(uint32_t)mgeo_container_.indices.size();
    const unsigned prim_step=mseg.primitive_type==meshprim_trilist?3:1;
    const uint32_t *seg_indices=mesh_indices+mseg.prim_start_index;
    mgseg.num_tris=0;
    for(uint32_t ti=0; ti<mseg.num_primitives; ++ti)
    {
      // check for degenerate triangle
      uint32_t tidx[3]={reindices_data[seg_indices[0]],
                        reindices_data[seg_indices[1]],
                        reindices_data[seg_indices[2]]};
      seg_indices+=prim_step;
      if(tidx[0]==tidx[1] || tidx[0]==tidx[2] || tidx[1]==tidx[2])
        continue;
      mgeo_container_.indices.insert_back(3, tidx);
      ++mgseg.num_tris;
    }
    mgseg.sbox=seed_oobox3_discrete(mgeo_container_.vertices.data(), mgseg.num_tris*3, discrete_axes3_49, mgeo_container_.indices.data()+mgseg.start_tri_idx);
  }

  // setup mesh geometry
  mgeo_.bvol=mesh_bvol;
  mgeo_.segs=mgeo_container_.segs.data();
  mgeo_.vertices=mgeo_container_.vertices.data();
  mgeo_.indices=mgeo_container_.indices.data();
  mgeo_.vbuf=mgeo_container_.vbuf.data;
  mgeo_.vbuf_size=num_vtx*vtx_size;
  mgeo_.vfmt_id=vfmt->id;
  mgeo_.num_segs=mgeo_container_.segs.size();
  mgeo_.num_vertices=num_vtx;
  mgeo_.num_indices=uint32_t(mgeo_container_.indices.size());
  usize_t num_segs=mgeo_container_.segs.size();
  unsigned num_tris=unsigned(mgeo_.num_indices/3);
  logf(">   %i %s, %i %s, %i %s\r\n", num_segs, num_segs>1?"segments":"segment", num_vtx, num_vtx>1?"vertices":"vertex", num_tris, num_tris>1?"triangles":"triangle");
  return true;
}
//----------------------------------------------------------------------------
