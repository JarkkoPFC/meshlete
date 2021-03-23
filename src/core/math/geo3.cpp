//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#include "core/math/geo3.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// triangle_mesh_topology
//============================================================================
triangle_mesh_topology::triangle_mesh_topology()
{
  m_pass_id=0xffffffff;
}
//----

triangle_mesh_topology::triangle_mesh_topology(const uint32_t *indices_, usize_t num_verts_, usize_t num_tris_, bool is_tri_strip_)
{
  init(indices_, num_verts_, num_tris_, is_tri_strip_);
}
//----

void triangle_mesh_topology::init(const uint32_t *indices_, usize_t num_verts_, usize_t num_tris_, bool is_tri_strip_)
{
  // allocate topology structures
  m_vertices.resize(num_verts_);
  m_edges.resize(num_tris_*3);
  m_triangles.resize(num_tris_);
  m_clusters.clear();

  // setup topology structures
  vertex *vertices_data=m_vertices.data();
  mem_set(vertices_data, 0xff, sizeof(*vertices_data)*num_verts_);
  edge *edges_data=m_edges.data();
  uint32_t num_edges=0;
  triangle *tri=m_triangles.data(), *tri_end=tri+num_tris_;
  uint32_t tidx=0;
  const unsigned idx_step=is_tri_strip_?1:3;
  while(tri<tri_end)
  {
    // setup triangle vertices and edges
    tri->pass_id=0xffffffff;
    tri->cidx=0xffffffff;
    for(unsigned vi=0; vi<3; ++vi)
    {
      // prepare new edge
      edge &ne=edges_data[num_edges];
      uint32_t idx0=indices_[(vi+1)%3], idx1=indices_[(vi+2)%3];
      ne.vidx_min=min(idx0, idx1);
      ne.vidx_max=idx0+idx1-ne.vidx_min;

      // check if the edge exists
      vertex &vtx_min=vertices_data[ne.vidx_min];
      uint32_t elst_min=vtx_min.edge_list, eidx=elst_min;
      while(eidx!=0xffffffff)
      {
        edge &e=edges_data[eidx>>1];
        if(e.vidx_min==ne.vidx_min && e.vidx_max==ne.vidx_max)
          goto edge_found;
        eidx=e.next_vtx_edge[eidx&1];
      }

      // link the new edge to the two vertices
      ne.pass_id=0xffffffff;
      ne.tri_list=0xffffffff;
      ne.next_vtx_edge[0]=elst_min;
      vertex &vtx_max=vertices_data[ne.vidx_max];
      ne.next_vtx_edge[1]=vtx_max.edge_list;
      eidx=(num_edges++)*2;
      vtx_min.edge_list=eidx|0;
      vtx_max.edge_list=eidx|1;

      // link edge to the triangle and setup edge and vertex indices
      edge_found:
      eidx>>=1;
      edge &e=edges_data[eidx];
      tri->next_edge_tri[vi]=e.tri_list;
      e.tri_list=tidx|vi;
      tri->eidx[vi]=eidx;
      tri->vidx[vi]=indices_[vi];
    }

    // next triangle
    indices_+=idx_step;
    ++tri;
    tidx+=4;
  }
  m_edges.resize(num_edges);
}
//----

triangle_mesh_topology::~triangle_mesh_topology()
{
}
//----------------------------------------------------------------------------

// Updates triangle list for a cluster. This should be called after cluster
// for triangles in the cluster have been changed with set_tri_cluster()
void triangle_mesh_topology::update_cluster_tri_list(uint32_t cluster_idx_)
{
  // split cluster triangle list to proper clusters
  cluster *clusters_data=m_clusters.data();
  triangle *triangles_data=m_triangles.data();
  cluster &c=clusters_data[cluster_idx_];
  uint32_t tlst=c.tri_list;
  c.tri_list=0xffffffff;
  c.num_tris=0;
  while(tlst!=0xffffffff)
  {
    triangle &tri=triangles_data[tlst];
    uint32_t next_tri=tri.next_cluster_tri;
    cluster &c=clusters_data[tri.cidx];
    tri.next_cluster_tri=c.tri_list;
    c.tri_list=tlst;
    ++c.num_tris;
    tlst=next_tri;
  }
}
//----------------------------------------------------------------------------
