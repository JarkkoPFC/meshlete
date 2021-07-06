//============================================================================
// Meshlete - Meshlet-based 3D object converter
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#include "mlet_gen.h"
#include "rasterizer/rasterizer.h"
#include "core/math/geo3.h"
#include "core/math/monte_carlo.h"
#include "core/math/tform3.h"
#include "core/sort.h"
#include <algorithm>
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// locals
//============================================================================
namespace
{
  //==========================================================================
  // bounding volume quantization
  //==========================================================================
  void quantize_segment_bvol(int16_t *out_qbvol_pos_, uint16_t &out_qbvol_rad_, const sphere3f &seg_bvol_, const sphere3f &mesh_bvol_)
  {
    float rrad=rcp_z(mesh_bvol_.rad);
    vec3f seg_bvol_pos=(seg_bvol_.pos-mesh_bvol_.pos)*(32767.0f*rrad);
    out_qbvol_pos_[0]=int16_t(clamp(round(seg_bvol_pos.x), -32767.5f, 32767.5f));
    out_qbvol_pos_[1]=int16_t(clamp(round(seg_bvol_pos.y), -32767.5f, 32767.5f));
    out_qbvol_pos_[2]=int16_t(clamp(round(seg_bvol_pos.z), -32767.5f, 32767.5f));
    out_qbvol_rad_=uint16_t(min<int>(65535, int(ceil(seg_bvol_.rad*65535.0f*rrad))));
  }
  //----

  void quantize_meshlet_bvol(int8_t *out_qbvol_pos_, uint8_t &out_qbvol_rad_, const sphere3f &mlet_bvol_, const sphere3f &seg_bvol_)
  {
    float rrad=rcp_z(seg_bvol_.rad);
    vec3f mlet_bvol_pos=(mlet_bvol_.pos-seg_bvol_.pos)*(127.0f*rrad);
    out_qbvol_pos_[0]=int8_t(clamp(round(mlet_bvol_pos.x), -127.5f, 127.5f));
    out_qbvol_pos_[1]=int8_t(clamp(round(mlet_bvol_pos.y), -127.5f, 127.5f));
    out_qbvol_pos_[2]=int8_t(clamp(round(mlet_bvol_pos.z), -127.5f, 127.5f));
    out_qbvol_rad_=uint8_t(min<int>(255, int(ceil(mlet_bvol_.rad*255.0f*rrad))));
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // visibility cone quantization
  //==========================================================================
  void quantize_meshlet_vcone(int8_t *out_qvcone_dir_, int8_t &out_qvcone_dot_, const vec3f &cone_dir_, float cone_dot_)
  {
    out_qvcone_dir_[0]=int8_t(127.5f*cone_dir_.x);
    out_qvcone_dir_[1]=int8_t(127.5f*cone_dir_.y);
    out_qvcone_dir_[2]=int8_t(127.5f*cone_dir_.z);
    out_qvcone_dot_=max<int8_t>(-127, int8_t(floor(127.5f*cone_dot_)));
  }
  //--------------------------------------------------------------------------


  //==========================================================================
  // stripify_meshlet
  //==========================================================================
  usize_t stripify_meshlet(uint8_t *res_, const uint8_t *indices_, uint32_t num_idx_, uint32_t num_vtx_)
  {
    /*todo*/
    PFC_ERROR_NOT_IMPL();
    return 0;
/*    uint32_t *res_idx=(uint32_t*)PFC_STACK_MALLOC(num_idx_*(p3g_meshlet_tristrip_restart?4:5)*sizeof(uint32_t));
    uint32_t *indices=(uint32_t*)PFC_STACK_MALLOC(num_idx_*sizeof(uint32_t));
    for(uint32_t i=0; i<num_idx_; ++i)
      indices[i]=indices_[i];
    usize_t num_idx=meshopt_stripify(res_idx, indices, num_idx_, num_vtx_, p3g_meshlet_tristrip_restart);
    for(usize_t i=0; i<num_idx; ++i)
      res_[i]=(uint8_t)res_idx[i];
    return num_idx;*/
  }
} // namespace <anonymous>
//----------------------------------------------------------------------------


//============================================================================
// bounding volume dequantization
//============================================================================
sphere3f pfc::dequantize_segment_bvol(const int16_t *qbvol_pos_, uint16_t qbvol_rad_, const sphere3f &mesh_bvol_)
{
  return sphere3f(vec3f(qbvol_pos_[0], qbvol_pos_[1], qbvol_pos_[2])*(mesh_bvol_.rad/32767.0f)+mesh_bvol_.pos,
                  qbvol_rad_*(mesh_bvol_.rad/65535.0f));
}
//----

sphere3f pfc::dequantize_meshlet_bvol(const int8_t *qbvol_pos_, uint8_t qbvol_rad_, const sphere3f &seg_bvol_)
{
  return sphere3f(vec3f(qbvol_pos_[0], qbvol_pos_[1], qbvol_pos_[2])*(seg_bvol_.rad/127.0f)+seg_bvol_.pos,
                  qbvol_rad_*(seg_bvol_.rad/255.0f));
}
//----------------------------------------------------------------------------


//============================================================================
// visibility cone dequantization
//============================================================================
void pfc::dequantize_meshlet_vcone(vec3f &out_dir_, float &out_dot_, const int8_t *qvcone_dir_, int8_t qvcone_dot_)
{
  out_dir_.x=qvcone_dir_[0]/127.0f;
  out_dir_.y=qvcone_dir_[1]/127.0f;
  out_dir_.z=qvcone_dir_[2]/127.0f;
  out_dot_=(qvcone_dot_-0.5f)/127.5f;
}
//----------------------------------------------------------------------------


//============================================================================
// generate_meshlets
//============================================================================
void pfc::generate_meshlets(const meshlet_gen_cfg &cfg_, const mesh_geometry &mgeo_, p3g_mesh_geometry &p3g_geo_)
{
  usize_t num_segs=mgeo_.num_segs;
  p3g_geo_.segs.resize(num_segs);
  p3g_geo_.num_tris=0;
  p3g_geo_.is_stripified=cfg_.mlet_stripify;
  for(usize_t seg_idx=0; seg_idx<num_segs; ++seg_idx)
  {
    // access segment data
    const mesh_geometry_segment &mgseg=mgeo_.segs[seg_idx];
    p3g_mesh_segment &p3g_seg=p3g_geo_.segs[seg_idx];
    p3g_seg.num_tris=mgseg.num_tris;
    p3g_geo_.num_tris+=mgseg.num_tris;
    const uint32_t *seg_indices=mgeo_.indices+mgseg.start_tri_idx;

    // setup segment
    p3g_seg.material_id=mgseg.material_id;
    p3g_seg.start_vidx=(uint32_t)p3g_geo_.mlet_vidx.size();
    p3g_seg.start_tidx=(uint32_t)p3g_geo_.mlet_tidx.size();
    p3g_seg.start_mlet=(uint32_t)p3g_geo_.mlets.size();

    // setup segment topology and find mesh major axis
    triangle_mesh_topology topology(seg_indices, mgeo_.num_vertices, mgseg.num_tris);
    vec3f majpr_axis=vec3f(1.0f, 0.0f, 0.0f)*mgseg.sbox.oobox.rot;
    if(majpr_axis.z>0.0f)
      majpr_axis=-majpr_axis;

    // sort triangles along the major axis & remove degenerate tris
    typedef pair<float, uint32_t> tri_ordinal_t;
    array<tri_ordinal_t> tri_order(mgseg.num_tris);
    tri_ordinal_t *tri_order_data=tri_order.data();
    const vec3f *pos_data=mgeo_.vertices;
    for(uint32_t tidx=0; tidx<mgseg.num_tris; ++tidx)
    {
      // check degenerate triangle
      const uint32_t *tvidx=topology.tri_vidx(tidx);
      if(tvidx[0]==tvidx[1] || tvidx[0]==tvidx[2] || tvidx[1]==tvidx[2])
        topology.set_tri_cluster(tidx, 0xfffffffe);

      // calculate triangle minimum vector on the major axis
      tri_ordinal_t &to=tri_order_data[tidx];
      float vp0=dot(majpr_axis, pos_data[tvidx[0]]);
      float vp1=dot(majpr_axis, pos_data[tvidx[1]]);
      float vp2=dot(majpr_axis, pos_data[tvidx[2]]);
      to.first=min(vp0, vp1, vp2);
      to.second=tidx;
    }
    quick_sort(tri_order_data, mgseg.num_tris);

    // assign all triangle to meshlets
    uint32_t num_mlets=0;
    uint32_t *mlet_tris=(uint32_t*)PFC_STACK_MALLOC(cfg_.max_mlet_tris*sizeof(uint32_t));
    uint32_t *mlet_border_edges=(uint32_t*)PFC_STACK_MALLOC(cfg_.max_mlet_tris*3*sizeof(uint32_t));
    uint32_t *mlet_vidx=(uint32_t*)PFC_STACK_MALLOC(cfg_.max_mlet_vtx*sizeof(uint32_t));
    uint8_t *mlet_tidx=(uint8_t*)PFC_STACK_MALLOC(cfg_.max_mlet_tris*3);
    uint8_t *mlet_strip_tidx=(uint8_t*)PFC_STACK_MALLOC(cfg_.max_mlet_tris*sizeof(uint8_t)*(p3g_meshlet_tristrip_restart?4:5));
    for(uint32_t toi=0; toi<mgseg.num_tris; ++toi)
    {
      uint32_t tidx=tri_order_data[toi].second;
      if(topology.tri_cluster(tidx)==0xffffffff)
      {
        // add the first triangle for the meshlet
        mlet_tris[0]=tidx;
        topology.set_tri_cluster(tidx, num_mlets);
        mem_copy(mlet_border_edges, topology.tri_eidx(tidx), sizeof(uint32_t)*3);
        unsigned num_mlet_tris=1;
        unsigned num_border_edges=3;
        unsigned num_mlet_vtx=3;

        // setup initial meshlet test point
        const uint32_t *stri_vidx=topology.tri_vidx(tidx);
        vec3f mlet_test_pos=(pos_data[stri_vidx[0]]+pos_data[stri_vidx[1]]+pos_data[stri_vidx[2]])/3.0f;

        // add triangles to the meshlet until reaching max meshlet triangle/vertex count
        while(num_mlet_tris<cfg_.max_mlet_tris && num_mlet_vtx<cfg_.max_mlet_vtx)
        {
          // try to find the best triangle attached to the meshlet border
          uint32_t best_tidx=0xffffffff;
          unsigned best_num_shared_vtx=0;
          float best_dist2=FLT_MAX;
          for(unsigned bei=0; bei<num_border_edges; ++bei)
          {
            unsigned num_valid_border_edge_tris=0;
            auto pred=[&](uint32_t tidx_, unsigned teidx_)
            {
              // check if the triangle is already assigned to a meshlet
              if(topology.tri_cluster(tidx_)!=0xffffffff)
                return;

              // count the number of shared vertices between the triangle and the meshlet
              unsigned num_shared_vtx=2;
              auto pred=[&](uint32_t tidx_)
              {
                if(topology.tri_cluster(tidx_)==num_mlets)
                  num_shared_vtx=3;
              };
              topology.for_each_vtx_tri(topology.tri_vidx(tidx_)[teidx_], pred);

              // check for the best triangle
              if(num_shared_vtx>=best_num_shared_vtx)
              {
                const uint32_t *tri_vidx=topology.tri_vidx(tidx_);
                float dist2=min(norm2(pos_data[tri_vidx[0]]-mlet_test_pos),
                                norm2(pos_data[tri_vidx[1]]-mlet_test_pos),
                                norm2(pos_data[tri_vidx[2]]-mlet_test_pos));
                if(num_shared_vtx>best_num_shared_vtx || dist2<best_dist2)
                {
                  best_tidx=tidx_;
                  best_num_shared_vtx=num_shared_vtx;
                  best_dist2=dist2;
                }
              }
              ++num_valid_border_edge_tris;
            };
            topology.for_each_edge_tri(mlet_border_edges[bei], pred);

            // remove orphaned border edge
            if(!num_valid_border_edge_tris)
              mlet_border_edges[bei--]=mlet_border_edges[--num_border_edges];
          }

          // check if found an edge-connected triangle
          unsigned num_new_vtx=3-best_num_shared_vtx;
          if(!best_num_shared_vtx)
          {
            // find spatially closest unassigned triangle /*todo: optimize spatial search*/
            for(uint32_t tidx=0; tidx<mgseg.num_tris; ++tidx)
              if(topology.tri_cluster(tidx)==0xffffffff)
              {
                const uint32_t *tri_vidx=topology.tri_vidx(tidx);
                float dist2=min(norm2(pos_data[tri_vidx[0]]-mlet_test_pos),
                                norm2(pos_data[tri_vidx[1]]-mlet_test_pos),
                                norm2(pos_data[tri_vidx[2]]-mlet_test_pos));
                if(dist2<best_dist2)
                {
                  best_tidx=tidx;
                  best_dist2=dist2;
                }
              }

            if(best_tidx!=0xffffffff)
            {
              // update new vertex count
              num_new_vtx=3;
              bool is_vtx_shared[3]={false};
              auto pred=[&](uint32_t tidx_, unsigned tvidx_, unsigned btvidx_)
              {
                if(!is_vtx_shared[btvidx_] && topology.tri_cluster(tidx_)==num_mlets)
                {
                  is_vtx_shared[btvidx_]=true;
                  --num_new_vtx;
                }
              };
              topology.for_each_tri_vtx_tri(best_tidx, pred);
            }
          }

          // check for premature meshlet termination
          if(best_tidx==0xffffffff || num_mlet_vtx+num_new_vtx>cfg_.max_mlet_vtx)
            break;

          // update meshlet testing position
          const uint32_t *btri_vidx=topology.tri_vidx(best_tidx);
          vec3f tcpos=(pos_data[btri_vidx[0]]+pos_data[btri_vidx[1]]+pos_data[btri_vidx[2]])/3.0f;
          mlet_test_pos=lerp(tcpos, mlet_test_pos, 0.5f+0.5f*float(num_mlet_tris)/(num_mlet_tris+1));

          // add the best matching triangle to the meshlet
          mlet_tris[num_mlet_tris++]=best_tidx;
          topology.set_tri_cluster(best_tidx, num_mlets);
          mem_copy(mlet_border_edges+num_border_edges, topology.tri_eidx(best_tidx), sizeof(uint32_t)*3);
          num_border_edges+=3;
          num_mlet_vtx+=num_new_vtx;
        }

        // add unassigned triangles to the meshlet whose vertices already exist in the meshlet
        {
          for(unsigned cti=0; cti<num_mlet_tris && num_mlet_tris<cfg_.max_mlet_tris; ++cti)
          {
            auto pred=[&](uint32_t tidx_, unsigned teidx_)
            {
              if(topology.tri_cluster(tidx_)!=0xffffffff || num_mlet_tris==cfg_.max_mlet_tris)
                return;
              unsigned num_shared_vtx=2;
              auto pred=[&](uint32_t tidx_)
              {
                if(topology.tri_cluster(tidx_)==num_mlets)
                  num_shared_vtx=3;
              };
              topology.for_each_vtx_tri(topology.tri_vidx(tidx_)[teidx_],  pred);
              if(num_shared_vtx==3)
              {
                mlet_tris[num_mlet_tris++]=tidx_;
                topology.set_tri_cluster(tidx_, num_mlets);
              }
            };
            topology.for_each_tri_edge_tri(mlet_tris[cti], pred);
          }
        }

        {
          // generate meshlet vertex and triangle index buffers
          unsigned num_vtx=0;
          unsigned num_idx=0;
          for(unsigned tidx=0; tidx<num_mlet_tris; ++tidx)
          {
            const uint32_t *tri_vidx=topology.tri_vidx(mlet_tris[tidx]);
            for(unsigned vi=0; vi<3; ++vi)
            {
              uint32_t *v=linear_search(mlet_vidx, num_vtx, tri_vidx[vi]);
              if(!v)
              {
                // add new vertex
                v=mlet_vidx+num_vtx;
                mlet_vidx[num_vtx++]=tri_vidx[vi];
              }
              mlet_tidx[num_idx++]=uint8_t(v-mlet_vidx);
            }
          }
          PFC_ASSERT(num_vtx==num_mlet_vtx);

          // add meshlet
          p3g_meshlet &mlet=p3g_geo_.mlets.push_back();
          mem_zero(&mlet, sizeof(mlet));
          mlet.num_vtx=num_mlet_vtx;
          mlet.num_idx=num_mlet_tris*3;
          mlet.num_tris=num_mlet_tris;
          mlet.start_vidx=(uint32_t)p3g_geo_.mlet_vidx.size();
          mlet.start_tidx=(uint32_t)p3g_geo_.mlet_tidx.size();
          if(cfg_.mlet_stripify)
          {
            mlet.num_idx=(uint32_t)stripify_meshlet(mlet_strip_tidx, mlet_tidx, mlet.num_idx, mlet.num_vtx);
            p3g_geo_.mlet_tidx.insert_back(mlet.num_idx, mlet_strip_tidx);
          }
          else
            p3g_geo_.mlet_tidx.insert_back(mlet.num_idx, mlet_tidx);
          p3g_geo_.mlet_vidx.insert_back(mlet.num_vtx, mlet_vidx);
        }
        ++num_mlets;
      }
    }

    // setup segment
    p3g_seg.num_vidx=(uint32_t)p3g_geo_.mlet_vidx.size()-p3g_seg.start_vidx;
    p3g_seg.num_tidx=(uint32_t)p3g_geo_.mlet_tidx.size()-p3g_seg.start_tidx;
    p3g_seg.num_mlets=num_mlets;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// generate_bvols
//============================================================================
void pfc::generate_bvols(const mesh_geometry &mgeo_, p3g_mesh_geometry &p3g_geo_)
{
  for(usize_t seg_idx=0; seg_idx<mgeo_.num_segs; ++seg_idx)
  {
    // calculate segment bounding volume
    const mesh_geometry_segment &mgseg=mgeo_.segs[seg_idx];
    p3g_mesh_segment &p3g_seg=p3g_geo_.segs[seg_idx];
    const vec3f *mesh_pos_data=mgeo_.vertices;
    sphere3f seg_bvol=bounding_sphere3_exp(mesh_pos_data, p3g_seg.num_vidx, mgseg.sbox, true, p3g_geo_.mlet_vidx.data()+p3g_seg.start_vidx);
    if(seg_bvol.rad-1.0f/65535.0f>mgeo_.bvol.rad)
      warnf("Warning: Segment %i bounding volume (%f) is larger than mesh bounding volume (%f)\r\n", seg_idx, seg_bvol.rad, mgeo_.bvol.rad);
    quantize_segment_bvol(p3g_seg.qbvol_pos, p3g_seg.qbvol_rad, seg_bvol, mgeo_.bvol);
    seg_bvol=dequantize_segment_bvol(p3g_seg.qbvol_pos, p3g_seg.qbvol_rad, mgeo_.bvol);

    // calculate meshlet bounding volumes
    const uint32_t *vtx_idx=p3g_geo_.mlet_vidx.data()+p3g_seg.start_vidx;
    for(uint32_t midx=0; midx<p3g_seg.num_mlets; ++midx)
    {
      // setup meshlet bounding volume
      p3g_meshlet &mlet=p3g_geo_.mlets[p3g_seg.start_mlet+midx];
      seed_oobox3f mlet_sbox=seed_oobox3_discrete(mesh_pos_data, mlet.num_vtx, discrete_axes3_49, vtx_idx);
      sphere3f mlet_bvol=bounding_sphere3_exp(mesh_pos_data, mlet.num_vtx, mlet_sbox, true, vtx_idx);
      if(mlet_bvol.rad-1.0f/255.0f>seg_bvol.rad)
        warnf("Warning: Meshlet %i bounding volume (%f) is larger than segment %i bounding volume (%f)\r\n", midx, mlet_bvol.rad, seg_idx, seg_bvol.rad);
      quantize_meshlet_bvol(mlet.qbvol_pos, mlet.qbvol_rad, mlet_bvol, seg_bvol);
      vtx_idx+=mlet.num_vtx;
    }
  }
}
//----------------------------------------------------------------------------


//============================================================================
// meshlet_visibility_shader
//============================================================================
struct meshlet_visibility_shader: rasterizer_shader_base
{
  struct vout
  {
    vec4f pos;
  };
  //----

  // config
  enum {depth_format=rtzr_depthfmt_float32};
  enum {perspective_bc=false};
  //--------------------------------------------------------------------------

  PFC_INLINE rasterizer_local_cluster_index_t init_shader() const
  {
    return (rasterizer_local_cluster_index_t)p3g_seg->num_mlets;
  }
  //----

  void setup_cluster(rasterizer_tiling &tiling_, rasterizer_dispatch_index_t dispatch_idx_, rasterizer_local_cluster_index_t cluster_idx_) const 
  {
    tiling_.add_cluster(dispatch_idx_, cluster_idx_);
  }
  //----

  PFC_INLINE const void *cluster(rasterizer_local_cluster_index_t cluster_idx_) const
  {
    mlet_idx=cluster_idx_;
    return &p3g_geo->mlets[p3g_seg->start_mlet+cluster_idx_];
  }
  //----

  PFC_INLINE uint8_t num_cluster_vertices(const void *cluster_) const
  {
    const p3g_meshlet *mlet=(const p3g_meshlet*)cluster_;
    return (uint8_t)mlet->num_vtx;
  }
  //----

  PFC_INLINE uint8_t num_cluster_triangles(const void *cluster_) const
  {
    const p3g_meshlet *mlet=(const p3g_meshlet*)cluster_;
    return (uint8_t)mlet->num_tris;
  }
  //----

  void tform_cluster(vout *tform_cache_, const void *cluster_) const /*todo: can we make the design more parallelizable?*/
  {
    // transform meshlet vertices
    const p3g_meshlet *mlet=(const p3g_meshlet*)cluster_;
    uint8_t num_cluster_vtx=(uint8_t)mlet->num_vtx;
    const uint32_t *vibuf=p3g_geo->mlet_vidx.data()+mlet->start_vidx;
    for(unsigned i=0; i<num_cluster_vtx; ++i)
    {
      const vec3f &vi=pos[vibuf[i]];
      vout &vo=*tform_cache_++;
      vec4f p={vi.x, vi.y, vi.z, 1.0f};
      p*=m_o2p;
      float oow=1.0f/p.w;
      vo.pos.x=p.x*oow;
      vo.pos.y=p.y*oow;
      vo.pos.z=p.z*oow;
      vo.pos.w=oow;
    }
  }
  //----

  void setup_primitive(const vout *vtx_, const void *cluster_, uint8_t prim_idx_, uint8_t vidx_[3], vec4f vpos_[3]) const
  {
    const p3g_meshlet *mlet=(const p3g_meshlet*)cluster_;
    const uint8_t *tibuf=p3g_geo->mlet_tidx.data()+mlet->start_tidx;
    const uint8_t *pidx=tibuf+prim_idx_*3;
    vidx_[0]=pidx[0];
    vidx_[1]=pidx[1];
    vidx_[2]=pidx[2];
    vpos_[0]=vtx_[vidx_[0]].pos;
    vpos_[1]=vtx_[vidx_[1]].pos;
    vpos_[2]=vtx_[vidx_[2]].pos;
  }
  //----

  PFC_INLINE void shade_pixel(const rasterizer_render_target *rts_, const vout *vtx_, uint32_t offset_, uint8_t vidx_[3], const vec3f &bc_, uint16_t, uint16_t, uint16_t) const
  {
    uint32_t *rt0=(uint32_t*)(rts_[0].data);
    rt0[offset_]=mlet_start_idx+mlet_idx;
  }
  //--------------------------------------------------------------------------

  // data
  p3g_mesh_geometry *p3g_geo;
  p3g_mesh_segment *p3g_seg;
  const vec3f *pos;
  mat44f m_o2p;
  uint32_t mlet_start_idx;
  mutable uint16_t mlet_idx;
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_tile_callback
//============================================================================
class rasterizer_tile_callback: public rasterizer_callback_base
{
public:
  // construction
  rasterizer_tile_callback(uint32_t *img_, uint32_t *tile_) {m_image=img_; m_tile=tile_;}
  //--------------------------------------------------------------------------

private:
  virtual void submit_tile(uint8_t tx_, uint8_t ty_, uint16_t tile_width_, uint16_t tile_height_, const vec2u16 &reg_min_, const vec2u16 &reg_end_)
  {
    mem_copy(m_image, m_tile, usize_t(tile_width_)*usize_t(tile_height_)*sizeof(uint32_t));
  }
  //--------------------------------------------------------------------------

  uint32_t *m_tile;
  uint32_t *m_image;
};
//----------------------------------------------------------------------------


//============================================================================
// generate_vcones
//============================================================================
void pfc::generate_vcones(const mesh_geometry &mgeo_, p3g_mesh_geometry &p3g_geo_, unsigned num_views_, uint16_t view_res_)
{
  // rasterizer config
  uint16_t view_width=view_res_, view_height=view_res_;
  enum {max_dispatches=256};
  enum {tmp_vout_size=256*16};
  enum {max_cluters=65535};
  enum {max_cluster_strips=512};
  enum {shader_store_size=max_dispatches*128};
  enum {num_tiles=1};
  logf("> Generating meshlet visibility cones (%i views, %ix%i)...\r\n", num_views_, view_width, view_height);

  // alloc rasterizer resources
  uint16_t tile_width=view_width, tile_height=view_height;
  owner_data depth=PFC_MEM_ALLOC(tile_width*tile_height*sizeof(float32_t));
  owner_data tile_rt0=PFC_MEM_ALLOC(tile_width*tile_height*sizeof(uint32_t));
  owner_data rt0=PFC_MEM_ALLOC(tile_width*tile_height*sizeof(uint32_t));
  rasterizer_dispatch dispatches[max_dispatches];
  usize_t shader_store[shader_store_size/sizeof(usize_t)];
  rasterizer_render_target rts[]={{tile_rt0.data, sizeof(uint32_t)}};
  rasterizer_tile tiles[num_tiles];
  rasterizer_cluster clusters[max_cluters];
  rasterizer_tile_cluster_strip cstrips[max_cluster_strips];
  usize_t tmp_cluster_vout[tmp_vout_size/sizeof(usize_t)];
  rasterizer_tile_callback rtzr_cb((uint32_t*)rt0.data, (uint32_t*)tile_rt0.data);

  // setup rasterizer config
  rasterizer_cfg rst_cfg;
  rst_cfg.dispatches=dispatches;
  rst_cfg.max_dispatches=max_dispatches;
  rst_cfg.shader_store=shader_store;
  rst_cfg.shader_store_size=sizeof(shader_store);
  rst_cfg.depth.data=depth.data;
  rst_cfg.depth.format=rtzr_depthfmt_float32;
  rst_cfg.depth.hiz_data=0;
  rst_cfg.rts=rts;
  rst_cfg.num_rts=1;

  // setup tiling config (single tile)
  rasterizer_tiling_cfg tiling_cfg;
  tiling_cfg.tile_order=tileorder_linear;
  tiling_cfg.tiles=tiles;
  tiling_cfg.clusters=clusters;
  tiling_cfg.max_clusters=max_cluters;
  tiling_cfg.cluster_strips=cstrips;
  tiling_cfg.max_cluster_strips=max_cluster_strips;
  tiling_cfg.rt_width=view_width;
  tiling_cfg.rt_height=view_height;
  tiling_cfg.tile_width=tile_width;
  tiling_cfg.tile_height=tile_height;

  // setup vertex cache config (no cache)
  rasterizer_vertex_cache_cfg vcache_cfg;
  vcache_cfg.cache=0;
  vcache_cfg.tmp_cluster_vout=tmp_cluster_vout;
  vcache_cfg.cluster_vcache_offs=0;
  vcache_cfg.cache_size=0;
  vcache_cfg.tmp_vout_size=sizeof(tmp_cluster_vout);
  vcache_cfg.max_clusters=0;

  // setup rasterizer
  rasterizer rtzr;
  rtzr.init(rst_cfg, tiling_cfg, vcache_cfg);
  rtzr.set_callback(&rtzr_cb);

  // create meshlet visibilities for given number of views
  usize_t num_mlets=p3g_geo_.mlets.size();
  usize_t view_visibility_size=(num_mlets+7)/8;
  owner_data meshlet_visibility=PFC_MEM_ALLOC(num_views_*view_visibility_size);
  uint8_t *meshlet_visibility_data=(uint8_t*)meshlet_visibility.data;
  mem_zero(meshlet_visibility_data, num_views_*view_visibility_size);
  array<vec3f> view_dirs(num_views_);
  logf("> --------------------------------------------------\r\n> ");
  unsigned old_pos=0;
  for(unsigned view_idx=0; view_idx<num_views_; ++view_idx)
  {
    // setup camera for the view
    vec3f view_dir=cone_strata_vector<float>(view_idx, num_views_, -1.0f);
    view_dirs[view_idx]=-view_dir;
    tform3f v2w;
    zrot_u(v2w, mgeo_.bvol.pos-view_dir*(mgeo_.bvol.rad+0.1f), view_dir);
    mat44f v2p=orthogonal_matrix<float>(mgeo_.bvol.rad*2.0f, 1.0f, 0.1f, 0.1f+mgeo_.bvol.rad*2.0f);
    mat44f w2p=inv(v2w)*v2p;

    // render mesh segments
    usize_t num_segs=p3g_geo_.segs.size();
    uint32_t mlet_start_idx=1;
    for(usize_t seg_idx=0; seg_idx<num_segs; ++seg_idx)
    {
      // setup shader and rasterize the segment
      p3g_mesh_segment &p3g_seg=p3g_geo_.segs[seg_idx];
      meshlet_visibility_shader sh;
      sh.p3g_geo=&p3g_geo_;
      sh.p3g_seg=&p3g_seg;
      sh.pos=mgeo_.vertices;
      sh.m_o2p=w2p;
      sh.mlet_start_idx=mlet_start_idx;
      rtzr.dispatch_shader(sh);
      mlet_start_idx+=p3g_seg.num_mlets;
    }
    rtzr.commit();

    // gather cluster visibility for the view
    uint32_t *midx_data=(uint32_t*)rt0.data, *midx_data_end=midx_data+tile_width*tile_height;
    do
    {
      uint32_t mlet_idx=*midx_data;
      if(mlet_idx--)
        meshlet_visibility_data[mlet_idx/8]|=1<<(mlet_idx&7);
    } while(++midx_data<midx_data_end);
    meshlet_visibility_data+=view_visibility_size;
    unsigned new_pos=unsigned(50.0f*float(view_idx+1)/num_views_+0.5f);
    while(old_pos<new_pos)
    {
      logf("#");
      ++old_pos;
    }
  }
  logf("\r\n");

  // build visibility cones for meshlets
  owner_data visibility_points=PFC_MEM_ALLOC(num_views_*sizeof(vec3f));
  vec3f *visibility_points_data=(vec3f*)visibility_points.data;
  for(usize_t mlet_idx=0; mlet_idx<num_mlets; ++mlet_idx)
  {
    // build list of visibility points
    uint32_t num_visible_views=0;
    uint8_t *vis_data=(uint8_t*)meshlet_visibility.data+mlet_idx/8;
    uint8_t vis_bitmask=1<<(mlet_idx&7);
    for(unsigned view_idx=0; view_idx<num_views_; ++view_idx)
    {
      if(*vis_data&vis_bitmask)
        visibility_points_data[num_visible_views++]=view_dirs[view_idx];
      vis_data+=view_visibility_size;
    }

    // find cone containing all the view vectors
    p3g_meshlet &mlet=p3g_geo_.mlets[mlet_idx];
    if(num_visible_views)
    {
      // calculate average cone direction as the initial cone direction
      vec3f cone_dir=0.0f;
      for(unsigned i=0; i<num_visible_views; ++i)
        cone_dir+=visibility_points_data[i];
      if(is_zero(cone_dir))
        cone_dir=visibility_points_data[0];
      else
        cone_dir=unit(cone_dir);

      // calculate angle of the closest view direction from the initial dir as the initial cone opening angle
      float cos_cone_angle=-2.0f;
      for(unsigned i=0; i<num_visible_views; ++i)
        cos_cone_angle=max(cos_cone_angle, ssat(dot(cone_dir, visibility_points_data[i])));

      // expand the cone with view dirs outside the current cone
      while(true)
      {
        // find view closest from the cone dir (end search if inside the cone)
        float max_d=-2.0f;
        unsigned max_i=unsigned(-1);
        for(unsigned i=0; i<num_visible_views; ++i)
        {
          float d=dot(cone_dir, visibility_points_data[i]);
          if(d+0.001f<cos_cone_angle && d>max_d)
          {
            max_d=d;
            max_i=i;
          }
        }
        if(max_i==unsigned(-1))
          break;

        // expand and rotate the cone to contain the old cone and the new angle dir
        float cone_angle=acos(cos_cone_angle);
        vec3f rot_axis=unit_z(cross(cone_dir, visibility_points_data[max_i]));
        float rot_angle=(acos(max_d)-cone_angle)/2.0f;
        cone_dir*=axis_rot_u(rot_axis, rot_angle);
        cos_cone_angle=cos(min(mathf::pi, cone_angle+rot_angle));
      }
      cos_cone_angle=cos(min(mathf::pi, acos(cos_cone_angle)+cone_strata_half_angle(num_views_, -1.0f)));

      // quantize the meshlet visibility cone
      quantize_meshlet_vcone(mlet.qvcone_dir, mlet.qvcone_dot, unit_z(cone_dir), cos_cone_angle);
    }
    else
    {
      // meshlet not visible from any view direction => delete
      mlet.qvcone_dir[0]=0;
      mlet.qvcone_dir[1]=0;
      mlet.qvcone_dir[2]=0;
      mlet.qvcone_dot=0;
    }
  }
}
//----------------------------------------------------------------------------
