//============================================================================
// Meshlete - Meshlet-based 3D object converter
//
// Copyright (c) 2020, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_MESHLETE_GEO_SETUP_H
#define PFC_MESHLETE_GEO_SETUP_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core_engine/mesh.h"
#include "src/mlet_gen.h"
namespace pfc
{

// new
struct mesh_geometry_setup_cfg;
struct mesh_geometry_container;
bool setup_mesh_geometry(const mesh&, const mesh_geometry_setup_cfg&, mesh_geometry&, mesh_geometry_container&);
//----------------------------------------------------------------------------


//============================================================================
// mesh_geometry_setup_cfg
//============================================================================
struct mesh_geometry_setup_cfg
{
  const char *vcfg_file;
  const char *vfmt_name;
};
//----------------------------------------------------------------------------


//============================================================================
// mesh_geometry_container
//============================================================================
struct mesh_geometry_container
{
  array<mesh_geometry_segment> segs;
  array<vec3f> vertices;
  array<uint32_t> indices;
  owner_data vbuf;
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
