//============================================================================
// Meshlete - Meshlet-based 3D object converter
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_MESHLETE_MLET_GEN_H
#define PFC_MESHLETE_MLET_GEN_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/math/geo3.h"
namespace pfc
{

// new
enum {p3g_meshlet_tristrip_restart=0xff}; // set to 0 to use degenerate triangles instead of restart index
struct mesh_geometry_segment;
struct mesh_geometry;
struct meshlet_gen_cfg;
struct p3g_meshlet;
struct p3g_mesh_segment;
struct p3g_mesh_geometry;
sphere3f dequantize_segment_bvol(const int16_t *qbvol_pos_, uint16_t qbvol_rad_, const sphere3f &mesh_bvol_);
sphere3f dequantize_meshlet_bvol(const int8_t *qbvol_pos_, uint8_t qbvol_rad_, const sphere3f &seg_bvol_);
void dequantize_meshlet_vcone(vec3f &out_dir_, float &out_dot_, const int8_t *qvcone_dir_, int8_t qvcone_dot_);
void generate_meshlets(const meshlet_gen_cfg&, const mesh_geometry&, p3g_mesh_geometry&);
void generate_bvols(const mesh_geometry&, p3g_mesh_geometry&);
void generate_vcones(const mesh_geometry&, p3g_mesh_geometry&, unsigned num_views_, uint16_t view_res_);
//----------------------------------------------------------------------------


//============================================================================
// mesh_geometry_segment
//============================================================================
struct mesh_geometry_segment
{
  seed_oobox3f sbox;
  uint32_t material_id;
  uint32_t start_tri_idx;
  uint32_t num_tris;
};
//----------------------------------------------------------------------------


//============================================================================
// mesh_geometry
//============================================================================
struct mesh_geometry
{
  sphere3f bvol;
  const mesh_geometry_segment *segs;
  const vec3f *vertices;
  const uint32_t *indices;
  const void *vbuf;
  usize_t vbuf_size;
  uint8_t vfmt_id;
  usize_t num_segs;
  usize_t num_vertices;
  usize_t num_indices;
};
//----------------------------------------------------------------------------


//============================================================================
// meshlet_gen_config
//============================================================================
struct meshlet_gen_cfg
{
  uint8_t max_mlet_vtx;
  uint8_t max_mlet_tris;
  bool mlet_stripify;
};
//----------------------------------------------------------------------------


//============================================================================
// p3g_meshlet
//============================================================================
struct p3g_meshlet
{
  uint32_t num_vtx;
  uint32_t num_idx;
  uint32_t num_tris;
  uint32_t start_vidx;
  uint32_t start_tidx;
  int8_t qbvol_pos[3];
  uint8_t qbvol_rad;
  int8_t qvcone_dir[3];
  int8_t qvcone_dot;
};
//----------------------------------------------------------------------------


//============================================================================
// p3g_mesh_segment
//============================================================================
struct p3g_mesh_segment
{
  uint32_t material_id;
  uint32_t start_vidx;
  uint32_t start_tidx;
  uint32_t start_mlet;
  uint32_t num_vidx;
  uint32_t num_tidx;
  uint32_t num_tris;
  uint32_t num_mlets;
  int16_t qbvol_pos[3];
  uint16_t qbvol_rad;
};
//----------------------------------------------------------------------------


//============================================================================
// p3g_mesh_geometry
//============================================================================
struct p3g_mesh_geometry
{
  uint32_t num_tris;
  bool is_stripified;
  array<p3g_mesh_segment> segs;
  array<p3g_meshlet> mlets;
  array<uint32_t> mlet_vidx;
  array<uint8_t> mlet_tidx;
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
