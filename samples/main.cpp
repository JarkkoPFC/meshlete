//============================================================================
// Meshlete Sample Project
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "src/mlet_gen.h"
#include "src/export.h"
#include "sxp_src/core/streams.h"
using namespace pfc;
extern float s_3d_model_pos[];
extern uint32_t s_3d_model_idx[];
usize_t get_num_3d_model_vtx();
usize_t get_num_3d_model_idx();
//----------------------------------------------------------------------------

int main()
{
  // setup the geometry for meshlet generation. the data should be parsed from
  // some 3D object format e.g. obj/dae/fbx/etc. but here we just use pre-parsed
  // vertex and triangle data for simplicity.
  mesh_geometry geo;
  const usize_t num_vtx=get_num_3d_model_vtx();
  const usize_t num_idx=get_num_3d_model_idx();
  geo.vertices=(const vec3f*)s_3d_model_pos;
  geo.indices=s_3d_model_idx;
  geo.num_vertices=num_vtx;
  geo.num_indices=num_idx;
  seed_oobox3f sbox=seed_oobox3_discrete((const vec3f*)s_3d_model_pos, num_vtx, discrete_axes3_49);
  geo.bvol=bounding_sphere3_exp((const vec3f*)s_3d_model_pos, num_vtx, sbox, true);
  mesh_geometry_segment mseg;
  mseg.start_tri_idx=0;
  mseg.num_tris=uint32_t(num_idx/3);
  mseg.sbox=seed_oobox3_discrete((const vec3f*)s_3d_model_pos, mseg.num_tris*3, discrete_axes3_49, geo.indices+mseg.start_tri_idx);
  mseg.material_id=0;
  geo.segs=&mseg;
  geo.num_segs=1;

  // generate meshlets, bounding volumes and visibility cones with some parameters
  meshlet_gen_cfg mlet_gen_cfg;
  mlet_gen_cfg.max_mlet_tris=255;   // max number of triangles in a meshlet
  mlet_gen_cfg.max_mlet_vtx=64;     // max number of vertices in a meshlet
  mlet_gen_cfg.mlet_stripify=false; // use triangle list or strip. strips are not current supported
  p3g_mesh_geometry geo_result;
  generate_meshlets(mlet_gen_cfg, geo, geo_result);
  generate_bvols(geo, geo_result); // generate bounding sphere for each meshlet
  generate_vcones(geo, geo_result, 1024, 1024); // generate visibility cones using 1024 views rendered to 1024x1024 map

  // output stats
  logf("number of meshlets: %i\r\n", geo_result.mlets.size());

  // provide the vertex buffer, the buffer size and vertex format ID here.
  // vertex buffer contains vertices with the required vertex attributes (e.g. position, uvs, etc.)
  // in an interleaved format specified by the vfmt_id.
  geo.vbuf=0;
  geo.vbuf_size=0;
  geo.vfmt_id=0;

  // export the p3g file to an array. the array can be saved as a binary
  // file, or converted to hex strings that can be #included in c++ projects.
  array<uint8_t> p3g_data;
  container_output_stream<array<uint8_t> > s(p3g_data);
  export_cfg_p3g p3g_cfg;
  p3g_cfg.export_meshlet_bvols=true;  // export bounding volumes
  p3g_cfg.export_meshlet_vcones=true; // export visibility cones
  p3g_cfg.vbuf_align=4; // align vertex buffer data to 4-byte boundary
  export_p3g(s, p3g_cfg, geo, geo_result);

  return 0;
}
//----------------------------------------------------------------------------
