//============================================================================
// Meshlete - Meshlet-based 3D object converter
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "geo_setup.h"
#include "src/export.h"
#include "src/mlet_gen.h"
#include "sxp_src/core_engine/mesh.h"
#include "sxp_src/core/fsys/fsys.h"
#include "sxp_src/core/math/bit_math.h"
#include "sxp_src/core/sort.h"
#include "sxp_src/core/main.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// config
//============================================================================
static const char *s_tool_name="Meshlete v0.1.5";
static const char *s_tool_desc="Meshlet-based 3D object converter";
static const char *s_copyright_message="Copyright (c) 2022, Jarkko Lempiainen. All rights reserved.";
static const char *s_usage_message="Usage: meshlete [options] -i <input.obj> -o <output.p3g>   (-h for help)";
static const char *s_conversion_fail_msg="Conversion failed!\r\n";
static const char *s_conversion_success_msg="Done!\r\n";
static const char *s_default_vcfg_filename="vfmt.xml";
//----------------------------------------------------------------------------


//============================================================================
// bcd16_version_str
//============================================================================
stack_str8 bcd16_version_str(uint16_t version_)
{
  stack_str8 s;
  s.format("%i.", version_>>12);
  version_<<=4;
  do
  {
    s.push_back_format("%x", (version_>>12));
    version_<<=4;
  } while(version_);
  return s;
}
//----------------------------------------------------------------------------


//============================================================================
// str_strip_quotes
//============================================================================
void str_strip_quotes(heap_str &s_)
{
  s_.resize(str_strip_outer_chars(s_.c_str(), '\"'));
}
//----------------------------------------------------------------------------


//============================================================================
// e_p3g_output_type
//============================================================================
enum e_p3g_output_type
{
  p3gouttype_bin,
  p3gouttype_hex,
  p3gouttype_hexd,
};
//----------------------------------------------------------------------------


//============================================================================
// command_arguments
//============================================================================
struct command_arguments
{
  command_arguments()
  {
    vfmt_name="pnu";
    vbuf_align=4;
    mlet_max_vtx=64;
    mlet_max_tris=128;
    p3g_output_type=p3gouttype_bin;
    num_vcone_views=1024;
    vcone_render_res=1024;
    mlet_bvols=false;
    mlet_vcones=false;
    mlet_stripify=false;
    debug_bvols=false;
    debug_vcones=false;
    suppress_copyright=false;
  }
  //----

  heap_str input_file;
  heap_str friendly_input_file;
  heap_str output_file;
  heap_str friendly_output_file;
  heap_str debug_output_file;
  heap_str friendly_debug_output_file;
  heap_str vcfg_filename;
  heap_str vfmt_name;
  uint32_t vbuf_align;
  uint8_t mlet_max_vtx;
  uint8_t mlet_max_tris;
  e_p3g_output_type p3g_output_type;
  uint32_t num_vcone_views;
  uint32_t vcone_render_res;
  bool mlet_bvols;
  bool mlet_vcones;
  bool mlet_stripify;
  bool debug_bvols;
  bool debug_vcones;
  bool suppress_copyright;
};
//----

bool parse_command_arguments(command_arguments &ca_, const char **args_, unsigned num_args_)
{
  // parse arguments
  heap_str error_msg;
  for(unsigned arg_idx=0; arg_idx<num_args_; ++arg_idx)
  {
    // check compiler for option
    if(args_[arg_idx][0]=='-')
    {
      // switch to proper argument handling
      const char *carg=args_[arg_idx];
      usize_t arg_size=str_size(carg);
      switch(to_lower(carg[1]))
      {
        // help
        case 'h':
        {
          if(arg_size==2)
          {
            // output help
            logf("%s - %s (P3G v%s)\r\n" // tool name, desc & version
                 "%s\r\n"     // copyright
                 "\r\n"
                 "%s\r\n"     // usage
                 "\r\n"
                 "Options:\r\n"
                 "  -i <file>    Input file (supported formats: obj/dae/fbx/3ds/lwo)\r\n"
                 "  -o <file>    Output file (p3g format)\r\n"
                 "  -hex         Output data as comma separated byte ASCII hex codes\r\n"
                 "  -hexd        Output data as comma separated dword ASCII hex codes\r\n"
                 "\r\n"
                 "  -vf <vfmt>   Output vertex format (default: \"pnu\")\r\n"
                 "  -vc <file>   Vertex format config file (default: \"%s\")\r\n"
                 "  -va <align>  Vertex data file alignment (default: 4)\r\n"
                 "\r\n"
                 "  -mv <num>    Max meshlet vertices (8-255, default: 64)\r\n"
                 "  -mt <num>    Max meshlet triangles (8-255, default: 128)\r\n"
                 "  -mb          Export meshlet bounding spheres\r\n"
                 "  -mc          Export meshlet visibility cones (forces -mb)\r\n"
                 "  -mcv <num>   Number of visibility cone views (default: 1024)\r\n"
                 "  -mcr <res>   Visibility cone render resolution (default: 1024)\r\n"
//                 "  -ms          Stripify meshlets\r\n"
                 "\r\n"
                 "  -do <file>   Debug output file (Collada .dae format)\r\n"
                 "  -db          Debug bounding spheres\r\n"
                 "  -dc          Debug visibility cones\r\n"
                 "\r\n"
                 "  -h           Print this screen\n"
                 "  -c           Suppress copyright message\r\n", 
                 s_tool_name, s_tool_desc, bcd16_version_str(p3g_file_version).c_str(),
                 s_copyright_message,
                 s_usage_message,
                 s_default_vcfg_filename);
            return false;
          }
          else if(str_eq(carg, "-hex"))
            ca_.p3g_output_type=p3gouttype_hex;
          else if(str_eq(carg, "-hexd"))
            ca_.p3g_output_type=p3gouttype_hexd;
        }

        case 'i':
        {
          if(arg_size==2 && arg_idx<num_args_-1)
          {
            ca_.input_file=args_[++arg_idx];
            str_strip_quotes(ca_.input_file);
            ca_.friendly_input_file=get_filename(ca_.input_file.c_str());
            str_lower(ca_.friendly_input_file.c_str());
          }
        } break;

        // output file
        case 'o':
        {
          if(arg_size==2 && arg_idx<num_args_-1)
          {
            ca_.output_file=args_[++arg_idx];
            str_strip_quotes(ca_.output_file);
            ca_.friendly_output_file=get_filename(ca_.output_file.c_str());
            str_lower(ca_.friendly_output_file.c_str());
          }
        } break;

        // vertex data generation
        case 'v':
        {
          if(str_eq(carg, "-vf") && arg_idx<num_args_-1)
          {
            ca_.vfmt_name=args_[++arg_idx];
            str_strip_quotes(ca_.vfmt_name);
          }
          else if(str_eq(carg, "-vc") && arg_idx<num_args_-1)
          {
            ca_.vcfg_filename=args_[++arg_idx];
            str_strip_quotes(ca_.vcfg_filename);
          }
          else if(str_eq(carg, "-va") && arg_idx<num_args_-1)
          {
            // get vertex alignment param
            int valign=0;
            if(!str_to_int(valign, args_[++arg_idx]))
            {
              error_msg+="> Error: Invalid vertex alignment parameter";
              break;
            }
            if(!is_pow2(uint32_t(valign)) || valign>1024)
            {
              error_msg.push_back_format("> Error: Vertex alignment (-va %i) must be power-of-2 and <=1024\r\n", valign);
              break;
            }
            ca_.vbuf_align=valign;
          }
        } break;

        // meshlet data generation
        case 'm':
        {
          if(str_eq(carg, "-mv") && arg_idx<num_args_-1)
          {
            // get max meshlet vertex count param
            int mlet_max_vtx=0;
            if(!str_to_int(mlet_max_vtx, args_[++arg_idx]))
            {
              error_msg+=("> Error: Invalid meshnet vertex count parameter\r\n");
              break;
            }
            if(mlet_max_vtx<8 || mlet_max_vtx>255)
            {
              error_msg.push_back_format("> Error: Max meshlet vertex count (-mv %i) must be 8-255\r\n", mlet_max_vtx);
              break;
            }
            ca_.mlet_max_vtx=(uint8_t)mlet_max_vtx;
          }
          else if(str_eq(carg, "-mt") && arg_idx<num_args_-1)
          {
            // get max meshlet triangle count param
            int mlet_max_tris=0;
            if(!str_to_int(mlet_max_tris, args_[++arg_idx]))
            {
              error_msg+="> Error: Invalid meshlet triangle count parameter\r\n";
              break;
            }
            if(mlet_max_tris<8 || mlet_max_tris>255)
            {
              error_msg.push_back_format("> Error: Max meshlet triangle count (-mt %i) must be 8-255\r\n", mlet_max_tris);
              break;
            }
            ca_.mlet_max_tris=(uint8_t)mlet_max_tris;
          }
          else if(str_eq(carg, "-mb"))
            ca_.mlet_bvols=true;
          else if(str_eq(carg, "-mc"))
          {
            ca_.mlet_vcones=true;
            ca_.mlet_bvols=true;
          }
          else if(str_eq(carg, "-mcv") && arg_idx<num_args_-1)
          {
            // get visibility cone view count param
            int num_vcone_views=0;
            if(!str_to_int(num_vcone_views, args_[++arg_idx]))
            {
              error_msg+="> Error: Invalid visibility cone count parameter\r\n";
              break;
            }
            if(num_vcone_views<8 || num_vcone_views>65536)
            {
              error_msg.push_back_format("> Error: Number of visibility cone views (-mcv %i) must be 8-65536\r\n", num_vcone_views);
              break;
            }
            ca_.num_vcone_views=num_vcone_views;
          }
          else if(str_eq(carg, "-mcr") && arg_idx<num_args_-1)
          {
            // get visibility cone render resolution
            int vcone_render_res=0;
            if(!str_to_int(vcone_render_res, args_[++arg_idx]))
            {
              error_msg+="> Error: Invalid visibility cone render resolution parameter\r\n";
              break;
            }
            if(vcone_render_res<128 || vcone_render_res>16384 || !is_pow2(uint16_t(vcone_render_res)))
            {
              error_msg.push_back_format("> Error: Visibility cone render resolution (-mcr %i) must be 128-16384 and power-of-2\r\n", vcone_render_res);
              break;
            }
            ca_.vcone_render_res=vcone_render_res;
          }
          else if(str_eq(carg, "-ms"))
            ca_.mlet_stripify=true;
        } break;

        // debug
        case 'd':
        {
          if(str_eq(carg, "-do") && arg_idx<num_args_-1)
          {
            ca_.debug_output_file=args_[++arg_idx];
            str_strip_quotes(ca_.debug_output_file);
            ca_.friendly_debug_output_file=get_filename(ca_.debug_output_file.c_str());
            str_lower(ca_.friendly_debug_output_file.c_str());
          }
          if(str_eq(carg, "-db"))
            ca_.debug_bvols=true;
          if(str_eq(carg, "-dc"))
            ca_.debug_vcones=true;
        } break;

        // suppress copyright text
        case 'c':
        {
          if(arg_size==2)
            ca_.suppress_copyright=true;
        } break;
      }
    }
  }

  // check for help string and copyright message output
  if(!ca_.suppress_copyright)
  {
    logf("%s - %s (P3G v%s)\r\n", s_tool_name, s_tool_desc, bcd16_version_str(p3g_file_version).c_str());
    log("");
    logf("%s\r\n\r\n", s_copyright_message);
  }
  if(!ca_.input_file.size() || (!ca_.output_file.size() && !ca_.debug_output_file.size()))
  {
    log(s_usage_message);
    log("\r\n");
    return false;
  }
  if(error_msg.size())
  {
    error(error_msg.c_str());
    return false;
  }

  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// log_meshlet_stats
//============================================================================
void log_meshlet_stats(const sphere3f &mesh_bvol_, const p3g_mesh_geometry &p3g_geo_)
{
  // collect meshlet stats
  uint32_t num_mlets=(uint32_t)p3g_geo_.mlets.size();
  uint32_t total_mlet_vtx=0, total_mlet_tris=0;
  array<float> mlet_bvol_rads(num_mlets);
  uint32_t mlet_idx=0;
  for(const p3g_mesh_segment &seg:p3g_geo_.segs)
  {
    sphere3f seg_bvol=dequantize_segment_bvol(seg.qbvol_pos, seg.qbvol_rad, mesh_bvol_);
    for(uint32_t midx=0; midx<seg.num_mlets; ++midx)
    {
      const p3g_meshlet &mlet=p3g_geo_.mlets[seg.start_mlet+midx];
      float rad=dequantize_meshlet_bvol(mlet.qbvol_pos, mlet.qbvol_rad, seg_bvol).rad;
      total_mlet_vtx+=mlet.num_vtx;
      total_mlet_tris+=mlet.num_tris;
      mlet_bvol_rads[mlet_idx++]=rad;
    }
  }
  quick_sort(mlet_bvol_rads.data(), mlet_bvol_rads.size());
  float med_bvol_rad=mlet_bvol_rads[mlet_idx/2];

  // setup average bounding volume unit
  stack_str8 bvol_unit="m";
  if(med_bvol_rad<1.0f)
  {
    bvol_unit="cm";
    med_bvol_rad*=100.0f;
    if(med_bvol_rad<1.0f)
    {
      bvol_unit="mm";
      med_bvol_rad*=10.0f;
    }
  }
  else if(med_bvol_rad>=1000.0f)
  {
    bvol_unit="km";
    med_bvol_rad/=1000.0f;
  }

  // log stats
  float avg_mlet_vtx=float(total_mlet_vtx)/num_mlets;
  float avg_mlet_tris=float(total_mlet_tris)/num_mlets;
  logf(">   %i meshlets (avg. %.1f vtx, %.1f tris)\r\n", num_mlets, avg_mlet_vtx, avg_mlet_tris);
  logf(">   Median meshlet bvol rad: %.1f%s\r\n", med_bvol_rad, bvol_unit.c_str());
}
//----------------------------------------------------------------------------


//============================================================================
// main
//============================================================================
PFC_MAIN(const char *args_[], unsigned num_args_)
{
  // parse command line arguments
  command_arguments ca;
  if(!parse_command_arguments(ca, args_, num_args_))
    return -1;
  owner_ref<file_system_base> fsys=create_default_file_system(true);

  // try open the mesh input file
  owner_ptr<bin_input_stream_base> fin=fsys->open_read(ca.input_file.c_str(), 0, fopencheck_none);
  if(!fin.data)
  {
    errorf("> Error: Unable to read file \"%s\"\r\n", ca.input_file.c_str());
    errorf(s_conversion_fail_msg);
    return -1;
  }

  // load mesh and access mesh data
  logf("> Loading 3D mesh \"%s\"...\r\n", ca.friendly_input_file.c_str());
  mesh msh(*fin);
  {
    unsigned num_mesh_vertices=(unsigned)msh.vertex_buffer(0).num_vertices();
    usize_t num_mesh_segs=msh.num_segments();
    uint32_t num_mesh_triangles=0;
    for(unsigned i=0; i<num_mesh_segs; ++i)
      num_mesh_triangles+=msh.segment(i).num_primitives;
    logf(">   %i %s, %i %s, %i %s\r\n", num_mesh_segs, num_mesh_segs==1?"segment":"segments", num_mesh_vertices, num_mesh_vertices==1?"vertex":"vertices", num_mesh_triangles, num_mesh_triangles==1?"triangle":"triangles");
  }

  // setup mesh geometry
  mesh_geometry_setup_cfg setup_cfg;
  heap_str vcfg_filename;
  if(ca.vcfg_filename.size())
    vcfg_filename=ca.vcfg_filename;
  else
  {
    vcfg_filename=executable_dir();
    vcfg_filename+="/";
    vcfg_filename+=s_default_vcfg_filename;
  }
  setup_cfg.vcfg_file=vcfg_filename.c_str();
  setup_cfg.vfmt_name=ca.vfmt_name.c_str();
  mesh_geometry mgeo;
  mesh_geometry_container mgeo_container;
  setup_mesh_geometry(msh, setup_cfg, mgeo, mgeo_container);

  // generate meshlets for the mesh
  logf("> Generating meshlets (max %i verts, %i tris)...\r\n", ca.mlet_max_vtx, ca.mlet_max_tris);
  p3g_mesh_geometry p3g_geo;
  meshlet_gen_cfg mgen_cfg;
  mgen_cfg.max_mlet_vtx=ca.mlet_max_vtx;
  mgen_cfg.max_mlet_tris=ca.mlet_max_tris;
  mgen_cfg.mlet_stripify=ca.mlet_stripify;
  generate_meshlets(mgen_cfg, mgeo, p3g_geo);

  // generate bounding volumes and visibility cones
  logf("> Generating meshlet bounding volumes...\r\n");
  generate_bvols(mgeo, p3g_geo);
  log_meshlet_stats(mgeo.bvol, p3g_geo);
  if(ca.mlet_vcones || ca.debug_vcones)
    generate_vcones(mgeo, p3g_geo, ca.num_vcone_views, uint16_t(ca.vcone_render_res));

  if(ca.debug_output_file.size())
  {
    // export debug Collada mesh
    owner_ptr<bin_output_stream_base> fout=fsys->open_write(ca.debug_output_file.c_str());
    if(!fout.data)
    {
      errorf("> Error: Unable to write debug file \"%s\"\r\n", ca.debug_output_file.c_str());
      errorf(s_conversion_fail_msg);
      return -1;
    }
    else
    {
      logf("> Exporting Collada file \"%s\"...\r\n", ca.friendly_debug_output_file.c_str());
      export_cfg_dae cfg;
      cfg.export_meshlet_bvols=ca.debug_bvols;
      cfg.export_meshlet_vcones=ca.debug_vcones;
      if(!export_dae(*fout.data, cfg, mgeo, p3g_geo))
      {
        errorf(s_conversion_fail_msg);
        return -1;
      }
    }
  }

  if(ca.output_file.size())
  {
    // export p3g file
    owner_ptr<bin_output_stream_base> fout=fsys->open_write(ca.output_file.c_str());
    if(!fout.data)
    {
      errorf("> Error: Unable to write p3g file \"%s\"\r\n", ca.output_file.c_str());
      errorf(s_conversion_fail_msg);
      return -1;
    }
    logf("> Exporting P3G file \"%s\"...\r\n", ca.friendly_output_file.c_str());
    export_cfg_p3g cfg;
    cfg.export_meshlet_bvols=ca.mlet_bvols;
    cfg.export_meshlet_vcones=ca.mlet_vcones;
    cfg.vbuf_align=ca.vbuf_align;
    switch(ca.p3g_output_type)
    {
      // export binary file
      case p3gouttype_bin:
      {
        if(!export_p3g(*fout, cfg, mgeo, p3g_geo))
        {
          errorf(s_conversion_fail_msg);
          return -1;
        }
      } break;

      // export hex ASCII file
      case p3gouttype_hex:
      case p3gouttype_hexd:
      {
        // export data to container
        array<uint8_t> p3g_data;
        {
          container_output_stream<array<uint8_t> > cout(p3g_data);
          if(!export_p3g(cout, cfg, mgeo, p3g_geo))
          {
            errorf(s_conversion_fail_msg);
            return -1;
          }
        }

        // output stats
        uint32_t total_mlet_vtx=0, total_mlet_tris=0;
        for(const p3g_mesh_segment &seg:p3g_geo.segs)
          for(uint32_t midx=0; midx<seg.num_mlets; ++midx)
          {
            const p3g_meshlet &mlet=p3g_geo.mlets[seg.start_mlet+midx];
            total_mlet_vtx+=mlet.num_vtx;
            total_mlet_tris+=mlet.num_tris;
          }
        stack_str32 avg_vtx_str, avg_tris_str;
        uint32_t num_mlets=(uint32_t)p3g_geo.mlets.size();
        float avg_mlet_vtx=float(total_mlet_vtx)/num_mlets;
        float avg_mlet_tris=float(total_mlet_tris)/num_mlets;
        avg_vtx_str.format("%.1f", avg_mlet_vtx);
        avg_tris_str.format("%.1f", avg_mlet_tris);
        text_output_stream(*fout)<<"//  Mesh file: "<<ca.friendly_input_file.c_str()<<"\r\n"
                                 <<"//   Segments: "<<mgeo.num_segs<<"\r\n"
                                 <<"//   Meshlets: "<<p3g_geo.mlets.size()<<" (avg. "<<avg_vtx_str.c_str()<<" vtx, "<<avg_tris_str.c_str()<<" tris)\r\n"
                                 <<"//  Triangles: "<<mgeo.num_indices/3<<"\r\n"
                                 <<"//   Vertices: "<<mgeo.num_vertices<<"\r\n"
                                 <<"// Vertex fmt: "<<ca.vfmt_name.c_str()<<" (id="<<mgeo.vfmt_id<<", size="<<mgeo.vbuf_size/mgeo.num_vertices<<")\r\n"
                                 <<"//    Options: BVols: "<<(ca.mlet_bvols?"yes":"no")<<", VCones: "<<(ca.mlet_vcones?"yes":"no")<<"\r\n"
                                 <<"//       Size: "<<p3g_data.size()<<" bytes\r\n"
                                 <<"//   Exporter: "<<s_tool_name<<" (P3G v"<<bcd16_version_str(p3g_file_version).c_str()<<")\r\n";

        // export the ASCII file
        if(ca.p3g_output_type==p3gouttype_hexd)
        {
          // write data as dword hex codes
          stack_str32 strbuf;
          p3g_data.insert_back((0-p3g_data.size())&3, uint8_t(0));
          usize_t dwords_left=p3g_data.size()/4;
          const uint32_t *dwords=(const uint32_t*)p3g_data.data();
          while(dwords_left)
          {
            usize_t num_dwords=min<usize_t>(dwords_left, 128);
            for(unsigned i=0; i<num_dwords; ++i)
            {
              strbuf.format("0x%08x, ", dwords[i]);
              *fout.data<<strbuf.c_str();
            }
            *fout.data<<"\r\n";
            dwords+=num_dwords;
            dwords_left-=num_dwords;
          }
        }
        else
        {
          // write data as byte hex codes
          stack_str32 strbuf;
          usize_t data_left=p3g_data.size();
          const uint8_t *bytes=p3g_data.data();
          while(data_left)
          {
            usize_t num_bytes=min<usize_t>(data_left, 256);
            for(unsigned i=0; i<num_bytes; ++i)
            {
              strbuf.format("0x%02x, ", bytes[i]);
              *fout.data<<strbuf.c_str();
            }
            *fout.data<<"\r\n";
            bytes+=num_bytes;
            data_left-=num_bytes;
          }
        }
      } break;
    }
  }
  log(s_conversion_success_msg);
  return 0;
}
//----------------------------------------------------------------------------
