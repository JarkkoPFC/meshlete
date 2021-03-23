//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_GEO3_H
#define PFC_CORE_MATH_GEO3_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core/math/prim3/prim3.h"
#include "core/math/numeric.h"
#include "core/containers.h"
namespace pfc
{

// new
// extended primitives
template<typename T> struct seed_oobox3;
typedef seed_oobox3<float> seed_oobox3f;
typedef seed_oobox3<double> seed_oobox3d;
// bounding volume calculations
enum e_discrete_axes3 {discrete_axes3_3, discrete_axes3_7, discrete_axes3_13, discrete_axes3_49};
template<typename T> seed_oobox3<T> seed_oobox3_discrete(const vec3<T> *points_, usize_t num_points_, e_discrete_axes3=discrete_axes3_49, const uint32_t *point_indices_=0);
template<typename T> sphere3<T> bounding_sphere3_exp(const vec3<T> *points_, usize_t num_points_, const seed_oobox3<T>&, bool use_oobox_=false, const uint32_t *point_indices_=0);
// topology
class triangle_mesh_topology;
//----------------------------------------------------------------------------


//============================================================================
// seed_oobox3
//============================================================================
template<typename T>
struct seed_oobox3
{
  oobox3<T> oobox;
  vec3<T> max_ext[2]; // extremal points for maximum axis
};
//----------------------------------------------------------------------------


//============================================================================
// triangle_mesh_topology
//============================================================================
class triangle_mesh_topology
{
public:
  // construction
  triangle_mesh_topology();
  triangle_mesh_topology(const uint32_t *indices_, usize_t num_verts_, usize_t num_tris_, bool is_tri_strip_=false);
  void init(const uint32_t *indices_, usize_t num_verts_, usize_t num_tris_, bool is_tri_strip_=false);
  ~triangle_mesh_topology();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE usize_t num_vertices() const;
  PFC_INLINE usize_t num_edges() const;
  PFC_INLINE usize_t num_triangles() const;
  PFC_INLINE usize_t num_clusters() const;
  PFC_INLINE usize_t num_cluster_tris(uint32_t cluster_idx_) const;
  //--------------------------------------------------------------------------

  // cluster construction
  PFC_INLINE uint32_t add_cluster();
  PFC_INLINE void add_cluster_tri(uint32_t tri_idx_, uint32_t cluster_idx_);
  //--------------------------------------------------------------------------

  // triangle operators
  PFC_INLINE const uint32_t *tri_vidx(uint32_t tri_idx_) const;
  PFC_INLINE const uint32_t *tri_eidx(uint32_t tri_idx_) const;
  PFC_INLINE uint32_t tri_cluster(uint32_t tri_idx_) const;
  PFC_INLINE void set_tri_cluster(uint32_t tri_idx_, uint32_t cluster_idx_);
  void update_cluster_tri_list(uint32_t cluster_idx_);
  //--------------------------------------------------------------------------

  // mesh traversal
  template<class Pred> void for_each_vtx_tri(uint32_t vtx_idx_, Pred&) const;
  template<class Pred> void for_each_edge_tri(uint32_t edge_idx_, Pred&) const;
  template<class Pred> void for_each_tri_vtx_tri(uint32_t tri_idx_, Pred&) const;
  template<class Pred> void for_each_tri_edge_tri(uint32_t tri_idx_, Pred&) const;
  template<class Pred> void for_each_cluster_vtx(uint32_t cluster_idx_, Pred&) const;
  template<class Pred> void for_each_cluster_tri(uint32_t cluster_idx_, Pred&) const;
  template<class Pred> void for_each_edge_connected_cluster_tri(uint32_t start_tri_idx_, Pred&) const;
  //--------------------------------------------------------------------------

private:
  //==========================================================================
  // vertex
  //==========================================================================
  struct vertex
  {
    mutable uint32_t pass_id;
    uint32_t edge_list;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // edge
  //==========================================================================
  struct edge
  {
    mutable uint32_t pass_id;
    uint32_t vidx_min, vidx_max;
    uint32_t tri_list;
    uint32_t next_vtx_edge[2];
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // triangle
  //==========================================================================
  struct triangle
  {
    mutable uint32_t pass_id;
    uint32_t cidx;
    uint32_t vidx[3];
    uint32_t eidx[3];
    uint32_t next_edge_tri[3];
    uint32_t next_cluster_tri;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // cluster
  //==========================================================================
  struct cluster
  {
    uint32_t tri_list;
    uint32_t num_tris;
  };
  //--------------------------------------------------------------------------

  mutable uint32_t m_pass_id;
  pfc::array<vertex> m_vertices;
  pfc::array<edge> m_edges;
  pfc::array<triangle> m_triangles;
  pfc::array<cluster> m_clusters;
};
//----------------------------------------------------------------------------

//============================================================================
#include "geo3.inl"
} // namespace pfc
#endif
