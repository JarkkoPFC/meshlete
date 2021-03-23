//============================================================================
// Meshlete Sample Project
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#include "../src/mlet_gen.h"
using namespace pfc;
extern float s_3d_model_pos[];
extern uint32_t s_3d_model_idx[];
usize_t get_num_3d_model_vtx();
usize_t get_num_3d_model_idx();
//----------------------------------------------------------------------------

int main()
{
  // setup geometry
  mesh_geometry geo;
  const usize_t num_vtx=get_num_3d_model_vtx();
  const usize_t num_idx=get_num_3d_model_idx();
  geo.vertices=(const vec3f*)s_3d_model_pos;
  geo.indices=s_3d_model_idx;
  geo.num_vertices=num_vtx;
  geo.num_indices=num_idx;
  seed_oobox3f sbox=seed_oobox3_discrete((const vec3f*)s_3d_model_pos, num_vtx, discrete_axes3_13);
  geo.bvol=bounding_sphere3_exp((const vec3f*)s_3d_model_pos, num_vtx, sbox, true);
  mesh_geometry_segment mseg;
  mseg.start_tri_idx=0;
  mseg.num_tris=uint32_t(num_idx/3);
  mseg.sbox=seed_oobox3_discrete((const vec3f*)s_3d_model_pos, mseg.num_tris*3, discrete_axes3_13, geo.indices+mseg.start_tri_idx);
  mseg.material_id=0;
  geo.segs=&mseg;
  geo.num_segs=1;

  // generate meshlets
  meshlet_gen_cfg cfg;
  cfg.max_mlet_tris=255;
  cfg.max_mlet_vtx=64;
  cfg.mlet_stripify=false;
  p3g_mesh_geometry res;
  generate_meshlets(cfg, geo, res);
  generate_bvols(geo, res);
  generate_vcones(geo, res, 1024, 1024);

  // output stats
  logf("number of meshlets: %i\r\n", res.mlets.size());
  return 0;
}
//----------------------------------------------------------------------------
