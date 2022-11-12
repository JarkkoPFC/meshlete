//============================================================================
// Software Rasterizer Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "rasterizer_cache.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_vertex_cache_cfg
//============================================================================
rasterizer_vertex_cache_cfg::rasterizer_vertex_cache_cfg()
{
  cache=0;
  tmp_cluster_vout=0;
  cluster_vcache_offs=0;
  cache_size=0;
  tmp_vout_size=0;
  max_clusters=0;
}
//----

void rasterizer_vertex_cache_cfg::set_cache(void *cache_, usize_t cache_size_)
{
  cache=cache_;
  cache_size=cache_size_;
}
//----

void rasterizer_vertex_cache_cfg::set_cluster_vout(void *vout_, usize_t vout_size_)
{
  tmp_cluster_vout=vout_;
  tmp_vout_size=vout_size_;
}
//----

void rasterizer_vertex_cache_cfg::set_cache_clusters(rasterizer_vertex_cache_offset_t *vcache_offs_, usize_t max_clusters_)
{
  cluster_vcache_offs=vcache_offs_;
  max_clusters=max_clusters_;
}
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_vertex_cache
//============================================================================
rasterizer_vertex_cache::rasterizer_vertex_cache()
{
  mem_zero(&m_cfg, sizeof(m_cfg));
  m_cache_alloc_pos=0;
}
//----

void rasterizer_vertex_cache::init(const rasterizer_vertex_cache_cfg &cfg_)
{
  PFC_ASSERT(!cfg_.cache_size || cfg_.cache);
  PFC_ASSERT_MSG((usize_t(cfg_.cache)&0x3)==0, ("Vertex cache data not properly aligned\r\n"));
  PFC_ASSERT_MSG(cfg_.cache_size<rasterizer_tform_cache_block_size*(rasterizer_vertex_cache_offset_t(-1)), ("Unable to completely address vertex cache size of %zi bytes\r\n", cfg_.cache_size));
  m_cfg=cfg_;
  release();
}
//----

void rasterizer_vertex_cache::release()
{
  if(!m_cfg.cache)
    return;
  m_cache_alloc_pos=0;
  block_header *bh=(block_header*)(m_cfg.cache);
  bh->cluster_idx=rasterizer_global_cluster_index_t(-1);
  bh->num_items=rasterizer_vertex_cache_offset_t(m_cfg.cache_size/rasterizer_tform_cache_block_size);
  mem_set(m_cfg.cluster_vcache_offs, 0xff, m_cfg.max_clusters*sizeof(rasterizer_vertex_cache_offset_t));
}
//----------------------------------------------------------------------------

void *rasterizer_vertex_cache::alloc_cluster_cache(rasterizer_global_cluster_index_t cluster_idx_, usize_t num_bytes_)
{
  // get number of items to allocate and allocation location
  PFC_ASSERT_MSG(m_cfg.cache, ("Vertex cache not initialized\r\n"));
  if(cluster_idx_>=m_cfg.max_clusters)
    return m_cfg.tmp_cluster_vout;
  rasterizer_vertex_cache_offset_t num_items=rasterizer_vertex_cache_offset_t(1+(num_bytes_+rasterizer_tform_cache_block_size-1)/rasterizer_tform_cache_block_size);
  if((m_cache_alloc_pos+num_items)*rasterizer_tform_cache_block_size>m_cfg.cache_size)
  {
    m_cache_alloc_pos=0;
    PFC_ASSERT_MSG((m_cache_alloc_pos+num_items)*rasterizer_tform_cache_block_size<=m_cfg.cache_size, ("Unable to allocate %zi bytes from vertex cache (%zi bytes)\r\n", num_bytes_, m_cfg.cache_size));
  }
  block_header *alloc_bh=(block_header*)((uint8_t*)m_cfg.cache+m_cache_alloc_pos*rasterizer_tform_cache_block_size);

  // free enough items for the new allocation
  block_header *free_bh=alloc_bh;
  rasterizer_vertex_cache_offset_t num_freed_items=0;
  while(num_freed_items<num_items)
  {
    rasterizer_vertex_cache_offset_t num_block_items=free_bh->num_items;
    num_freed_items+=num_block_items;
    rasterizer_global_cluster_index_t cidx=free_bh->cluster_idx;
    if(cidx!=rasterizer_global_cluster_index_t(-1))
      m_cfg.cluster_vcache_offs[cidx]=rasterizer_vertex_cache_offset_t(-1);
    (uint8_t*&)free_bh+=num_block_items*rasterizer_tform_cache_block_size;
  }

  // allocate items
  alloc_bh->cluster_idx=cluster_idx_;
  alloc_bh->num_items=num_items;
  m_cfg.cluster_vcache_offs[cluster_idx_]=rasterizer_vertex_cache_offset_t(m_cache_alloc_pos+1);
  m_cache_alloc_pos+=num_items;
  if(num_freed_items>num_items)
  {
    // add block header for the remaining items
    block_header *extra_bh=(block_header*)((uint8_t*)alloc_bh+num_items*rasterizer_tform_cache_block_size);
    extra_bh->cluster_idx=rasterizer_global_cluster_index_t(-1);
    extra_bh->num_items=num_freed_items-num_items;
  }
  return (uint8_t*)alloc_bh+rasterizer_tform_cache_block_size;
}
//----------------------------------------------------------------------------
