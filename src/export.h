//============================================================================
// Meshlete - Meshlet-based 3D object converter
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_MESHLETE_EXPORT_H
#define PFC_MESHLETE_EXPORT_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/core.h"
namespace pfc
{
struct mesh_geometry;
struct p3g_mesh_geometry;
struct p3g_meshlet;
class bin_output_stream_base;

// new
enum {p3g_file_version=0x1000};  // v1.0
struct export_cfg_p3g;
struct export_cfg_dae;
bool export_p3g(bin_output_stream_base&, const export_cfg_p3g&, const mesh_geometry&, const p3g_mesh_geometry&);
bool export_dae(bin_output_stream_base&, const export_cfg_dae&, const mesh_geometry&, const p3g_mesh_geometry&);
//----------------------------------------------------------------------------


//============================================================================
// e_p3g_flags
//============================================================================
enum e_p3g_flags
{
  p3gflag_32bit_index = 0x0001,  // 32-bit vertex indices (instead of 16-bit)
  p3gflag_tristrips   = 0x0002,  // tri-strips meshlets (instead of tri-lists)
  p3gflag_bvols       = 0x0004,  // store meshlet bounding volumes
  p3gflag_vcones      = 0x0008,  // store meshlet visibility cones
};
//----------------------------------------------------------------------------


//============================================================================
// export_cfg_dae
//============================================================================
struct export_cfg_dae
{
  bool export_meshlet_bvols;
  bool export_meshlet_vcones;
};
//----------------------------------------------------------------------------


//============================================================================
// export_cfg_p3g
//============================================================================
struct export_cfg_p3g
{
  bool export_meshlet_bvols;
  bool export_meshlet_vcones;
  uint32_t vbuf_align;
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
