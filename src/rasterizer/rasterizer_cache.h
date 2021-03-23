//============================================================================
// Software Rasterizer Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_RASTERIZER_CACHE_H
#define PFC_RASTERIZER_CACHE_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "rasterizer/rasterizer_config.h"
namespace pfc
{

// new
struct rasterizer_vertex_cache_cfg;
class rasterizer_vertex_cache;
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_vertex_cache_cfg
//============================================================================
struct rasterizer_vertex_cache_cfg
{
  // construction and setup
  rasterizer_vertex_cache_cfg();
  void set_cache(void *cache_, usize_t cache_size_);
  void set_cluster_vout(void *vout_, usize_t vout_size_);
  void set_cache_clusters(rasterizer_vertex_cache_offset_t*, usize_t max_clusters_);
  //--------------------------------------------------------------------------

  void *cache;
  void *tmp_cluster_vout;
  rasterizer_vertex_cache_offset_t *cluster_vcache_offs;
  usize_t cache_size;
  usize_t tmp_vout_size;
  usize_t max_clusters;
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_vertex_cache
//============================================================================
class rasterizer_vertex_cache
{
public:
  // construction
  rasterizer_vertex_cache();
  void init(const rasterizer_vertex_cache_cfg&);
  void release();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE usize_t cache_size() const;
  PFC_INLINE void *cluster_cache(rasterizer_global_cluster_index_t cluster_idx_);
  PFC_INLINE usize_t tmp_cluster_vout_size() const;
  PFC_INLINE void *tmp_cluster_vout() const;
  //--------------------------------------------------------------------------

  // allocation
  void *alloc_cluster_cache(rasterizer_global_cluster_index_t, usize_t num_bytes_);
  //--------------------------------------------------------------------------

private:
  rasterizer_vertex_cache(const rasterizer_vertex_cache&); // not implemented
  void operator=(const rasterizer_vertex_cache&); // not implemented
  PFC_CTC_ASSERT_MSG((rasterizer_tform_cache_block_size&(rasterizer_tform_cache_block_size-1))==0, block_size_must_be_power_of_two);
  //--------------------------------------------------------------------------

  //==========================================================================
  // block_header
  //==========================================================================
  struct block_header
  {
    rasterizer_global_cluster_index_t cluster_idx;
    rasterizer_vertex_cache_offset_t num_items;
  };
  PFC_CTC_ASSERT_MSG(sizeof(block_header)<=rasterizer_tform_cache_block_size, block_header_does_not_fit_in_block);
  //--------------------------------------------------------------------------

  rasterizer_vertex_cache_cfg m_cfg;
  usize_t m_cache_alloc_pos;
};
//----------------------------------------------------------------------------




//============================================================================
//============================================================================
// inline & template implementations
//============================================================================
//============================================================================


//============================================================================
// rasterizer_vertex_cache
//============================================================================
usize_t rasterizer_vertex_cache::cache_size() const
{
  return m_cfg.cache_size;
}
//----

void *rasterizer_vertex_cache::cluster_cache(rasterizer_global_cluster_index_t cluster_idx_)
{
  PFC_ASSERT_PEDANTIC(m_cfg.cluster_vcache_offs);
  if(cluster_idx_>=m_cfg.max_clusters)
    return 0;
  rasterizer_vertex_cache_offset_t offs=m_cfg.cluster_vcache_offs[cluster_idx_];
  return offs==rasterizer_vertex_cache_offset_t(-1)?0:(uint8_t*)m_cfg.cache+offs*rasterizer_tform_cache_block_size;
}
//----

usize_t rasterizer_vertex_cache::tmp_cluster_vout_size() const
{
  return m_cfg.tmp_vout_size;
}
//----

void *rasterizer_vertex_cache::tmp_cluster_vout() const
{
  return m_cfg.tmp_cluster_vout;
}
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
