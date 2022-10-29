//============================================================================
// Software Rasterizer Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "rasterizer/rasterizer.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_cfg
//============================================================================
rasterizer_cfg::rasterizer_cfg()
{
  dispatches=0;
  max_dispatches=0;
  shader_store=0;
  shader_store_size=0;
  depth.data=0;
  depth.hiz_data=0;
  depth.format=rtzr_depthfmt_none;
  rts=0;
  num_rts=0;
}
//----

void rasterizer_cfg::set_dispatches(rasterizer_dispatch *dispatches_, rasterizer_dispatch_index_t max_dispatches_)
{
  dispatches=dispatches_;
  max_dispatches=max_dispatches_;
}
//----

void rasterizer_cfg::set_shader_store(void *shader_store_, usize_t shader_store_size_)
{
  shader_store=shader_store_;
  shader_store_size=shader_store_size_;
}
//----

void rasterizer_cfg::set_depth(void *depth_buffer_, uint16_t *hiz_buffer_, e_rasterizer_depth_format depth_fmt_)
{
  depth.data=depth_buffer_;
  depth.hiz_data=hiz_buffer_;
  depth.format=depth_fmt_;
}
//----

void rasterizer_cfg::set_rts(rasterizer_render_target *rts_, uint8_t num_rts_)
{
  rts=rts_;
  num_rts=num_rts_;
}
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_stats
//============================================================================
void rasterizer_stats::reset()
{
  // reset stats
  num_dispatches=0;
  shader_store_size=0;
  num_cluster_strips=0;
  tmp_vout_size=0;
  num_clusters=0;
}
//----

void rasterizer_stats::log() const
{
  // print log stats
  PFC_LOGF("> Max dispatches: %zi\r\n", num_dispatches);
  PFC_LOGF("> Max Shader store: %zi\r\n", shader_store_size);
  PFC_LOGF("> Max cluster strips: %zi\r\n", num_cluster_strips);
  PFC_LOGF("> Max vout size: %zi\r\n", tmp_vout_size);
  PFC_LOGF("> Max clusters: %zi\r\n", num_clusters);
}
//----------------------------------------------------------------------------


//============================================================================
// rasterizer
//============================================================================
rasterizer::rasterizer()
{
  m_callback=0;
  mem_zero(&m_cfg, sizeof(m_cfg));
  m_num_dispatches=0;
#if PFC_BUILDOP_RASTERIZER_STATS==1
  m_stats.reset();
#endif
}
//----

void rasterizer::init(const rasterizer_cfg &cfg_, const rasterizer_tiling_cfg &tcfg_, const rasterizer_vertex_cache_cfg &vccfg_)
{
  PFC_ASSERT(m_cfg.depth.format==rtzr_depthfmt_none || m_cfg.depth.data);
  m_tiling.init(tcfg_);
  m_vertex_cache.init(vccfg_);
  m_cfg=cfg_;
  m_num_dispatches=0;
  m_num_clusters=0;
  m_shader_write_pos=0;
  PFC_ASSERT_MSG(((usize_t)cfg_.shader_store&(shader_mem_align-1))==0, ("Shader store not properly aligned\r\n"));

  // clear depth
  switch(cfg_.depth.format)
  {
    // no depth
    case rtzr_depthfmt_none:
    {
      m_cfg.depth.data=0;
      m_cfg.depth.hiz_data=0;
    } break;

    // 8bpp unorm depth buffer
    case rtzr_depthfmt_uint8:
    {
      usize_t depth_tile_size=sizeof(uint8_t)*m_tiling.tile_width()*m_tiling.tile_height();
      mem_set(m_cfg.depth.data, 0xff, depth_tile_size);
    } break;

    // 16bpp unorm depth buffer
    case rtzr_depthfmt_uint16:
    {
      usize_t depth_tile_size=sizeof(uint16_t)*m_tiling.tile_width()*m_tiling.tile_height();
      mem_set(m_cfg.depth.data, 0xff, depth_tile_size);
    } break;

    // float32 depth buffer
    case rtzr_depthfmt_float32:
    {
      float *p=(float*)m_cfg.depth.data, *p_end=p+m_tiling.tile_width()*m_tiling.tile_height();
      do
      {
        *p=1.0f;
      } while(++p<p_end);
    } break;

    // unsupported format
    default: PFC_ERROR(("Unsupported depth format\r\n"));
  }

  // clear hi-z
  if(m_cfg.depth.hiz_data)
    mem_set(m_cfg.depth.hiz_data, 0xff, m_tiling.tile_width()*m_tiling.tile_height()/(rasterizer_hiz_tile_size*rasterizer_hiz_tile_size));

  // clear render targets
  for(uint8_t rt_idx=0; rt_idx<m_cfg.num_rts; ++rt_idx)
  {
    usize_t rt_tile_size=m_cfg.rts[rt_idx].px_size*m_tiling.tile_width()*m_tiling.tile_height();
    mem_zero(m_cfg.rts[rt_idx].data, rt_tile_size);
  }
}
//----------------------------------------------------------------------------

void rasterizer::commit()
{
  // setup render target config
  PFC_ASSERT(m_callback);
  render_target_cfg rt_cfg;
  rt_cfg.rt_width=m_tiling.rt_width();
  rt_cfg.rt_height=m_tiling.rt_height();
  rt_cfg.rt_coord_scale.set(float((m_tiling.rt_width()/2)<<rasterizer_subpixel_bits), float((m_tiling.rt_height()/2)<<rasterizer_subpixel_bits));
  rt_cfg.depth=m_cfg.depth;
  rt_cfg.rts=m_cfg.rts;
  rt_cfg.tile_pitch=m_tiling.tile_width();

#if PFC_BUILDOP_RASTERIZER_STATS==1
  // update
  m_stats.num_dispatches=max<usize_t>(m_num_dispatches, m_stats.num_dispatches);
  m_stats.shader_store_size=max(m_shader_write_pos, m_stats.shader_store_size);
  m_stats.num_cluster_strips=max<usize_t>(m_tiling.num_cluster_strips(), m_stats.num_cluster_strips);
  m_stats.num_clusters=max<usize_t>(m_num_clusters, m_stats.num_clusters);
#endif

  // rasterize cluster triangles in all tiles
  rasterizer_tile *tile=m_tiling.tiles(), *tile_end=tile+m_tiling.num_tiles();
  do
  {
    // setup tile coords and size
    uint8_t tx=tile->x, ty=tile->y;
    uint16_t tile_x=tx<<m_tiling.tile_width_shift();
    uint16_t tile_y=ty<<m_tiling.tile_height_shift();
    uint16_t tile_hiz_x=tile_x/rasterizer_hiz_tile_size;
    uint16_t tile_hiz_y=tile_y/rasterizer_hiz_tile_size;
    rt_cfg.tile_width=min<uint16_t>(m_tiling.rt_width()-tile_x, m_tiling.tile_width());
    rt_cfg.tile_height=min<uint16_t>(m_tiling.rt_height()-tile_y, m_tiling.tile_height());

    // rasterize tile clusters
    rasterizer_global_cluster_index_t num_tile_clusters=tile->num_clusters;
    rasterizer_cluster_strip_index_t cstrip_idx=tile->cluster_strip_first;
    rasterizer_dispatch_index_t cur_dispatch_idx=rasterizer_dispatch_index_t(-1);
    result res={{rt_cfg.tile_width, rt_cfg.tile_height}, {0, 0}, rtzr_depthfmt_none, 0};
    vec2u16 tile_bounds_min={rt_cfg.tile_width, rt_cfg.tile_height};
    vec2u16 tile_bounds_end={0, 0};
    bool hiz_test=false;
    while(num_tile_clusters)
    {
      // rasterize cluster strip
      const rasterizer_tile_cluster_strip &cstrip=m_tiling.cluster_strip(cstrip_idx);
      uint8_t num_strip_clusters=(uint8_t)min<rasterizer_global_cluster_index_t>(num_tile_clusters, rasterizer_max_strip_clusters);
      num_tile_clusters-=num_strip_clusters;
      const rasterizer_global_cluster_index_t *global_cluster_idx=cstrip.global_cluster_idx, *global_cluster_idx_end=global_cluster_idx+num_strip_clusters;
      do
      {
        // check dispatch change
        rasterizer_cluster &cluster=m_tiling.cluster(*global_cluster_idx);
        if(cur_dispatch_idx!=cluster.dispatch_idx)
        {
          // update dispatch state
          hiz_test=cur_dispatch_idx!=rasterizer_dispatch_index_t(-1);
          cur_dispatch_idx=cluster.dispatch_idx;

#if PFC_BUILDOP_RASTERIZER_HIZ==1
          // check for hi-z update
          if(m_cfg.depth.hiz_data && res.hiz_depth_format!=rtzr_depthfmt_none && res.tile_end.x && res.tile_end.y)
          {
            // update hi-z for the changed tile region
            switch(res.hiz_depth_format)
            {
              // 8bpp unorm depth buffer
              case rtzr_depthfmt_uint8: update_hiz<uint8_t>(res); break;
              // 16bpp unorm depth buffer
              case rtzr_depthfmt_uint16: update_hiz<uint16_t>(res); break;
              // float32 depth buffer
              case rtzr_depthfmt_float32: update_hiz<float32_t>(res); break;
              // unsupported format
              default: PFC_ERROR(("Unsupported depth format\r\n"));
            }
          }
          tile_bounds_min=min(tile_bounds_min, res.tile_min);
          tile_bounds_end=max(tile_bounds_end, res.tile_end);
          res.tile_min.set(rt_cfg.tile_width, rt_cfg.tile_height);
          res.tile_end.set(0, 0);
#endif
        }

#if PFC_BUILDOP_RASTERIZER_HIZ==1
        // check cluster occlusion against hi-z
        const uint16_t *hiz_data=m_cfg.depth.hiz_data;
        if(hiz_test && hiz_data)
        {
          // get max hi-z value within cluster bounds of the tile
          const uint16_t hiz_test_x=(uint16_t)max<int16_t>(0, cluster.hiz_x-tile_hiz_x);
          const uint16_t hiz_test_y=(uint16_t)max<int16_t>(0, cluster.hiz_y-tile_hiz_y);
          const uint16_t hiz_test_width=min<int16_t>(m_tiling.tile_width()/rasterizer_hiz_tile_size-hiz_test_x, cluster.hiz_x+cluster.hiz_width-tile_hiz_x-hiz_test_x);
          const uint16_t hiz_test_height=min<int16_t>(m_tiling.tile_height()/rasterizer_hiz_tile_size-hiz_test_y, cluster.hiz_y+cluster.hiz_height-tile_hiz_y-hiz_test_y);
          const uint16_t hiz_pitch=m_tiling.tile_width()/rasterizer_hiz_tile_size;
          const uint16_t hiz_scan_pitch=hiz_pitch-hiz_test_width;
          const uint16_t *hiz_buf=hiz_data+hiz_test_x+hiz_test_y*hiz_pitch;
          const uint16_t *hiz_buf_end=hiz_buf+hiz_test_height*hiz_pitch;
          if(!hiz_test_width || !hiz_test_height)
            continue;
          uint16_t max_hiz=0;
          do
          {
            const uint16_t *hiz_scan_end=hiz_buf+hiz_test_width;
            do
            {
              max_hiz=max(max_hiz, *hiz_buf);
            } while(++hiz_buf<hiz_scan_end);
            hiz_buf+=hiz_scan_pitch;
          } while(hiz_buf<hiz_buf_end);

          // skip cluster if max hi-z value is less than cluster min-z
          if(max_hiz<cluster.min_z)
            continue;
        }
#endif

        // rasterize the cluster for the tile
        const void *wrapper=m_cfg.dispatches[cur_dispatch_idx].shader_wrapper;
        ((const shader_wrapper_base*)wrapper)->rasterize_cluster(res, rt_cfg, tile_x, tile_y, m_vertex_cache, cluster.local_cluster_idx, *global_cluster_idx);
      } while(++global_cluster_idx<global_cluster_idx_end);
      cstrip_idx=cstrip.next;
    }
    res.tile_min=min(res.tile_min, tile_bounds_min);
    res.tile_end=max(res.tile_end, tile_bounds_end);
#if PFC_BUILDOP_RASTERIZER_STATS==1
    m_stats.tmp_vout_size=max(res.max_vout, m_stats.tmp_vout_size);
#endif

    // calculate tile update region and submit tile
    vec2u16 update_region_min=min(res.tile_min, vec2u16(tile->tile_min.x, tile->tile_min.y));
    vec2u16 update_region_end=max(res.tile_end, vec2u16(tile->tile_end.x, tile->tile_end.y));
    tile->tile_min.x=rasterizer_tile_size_t(res.tile_min.x);
    tile->tile_min.y=rasterizer_tile_size_t(res.tile_min.y);
    tile->tile_end.x=rasterizer_tile_size_t(res.tile_end.x);
    tile->tile_end.y=rasterizer_tile_size_t(res.tile_end.y);
    if(update_region_end.x && update_region_end.y)
    {
      // submit tile
      m_callback->submit_tile(tx, ty, rt_cfg.tile_width, rt_cfg.tile_height, update_region_min, update_region_end);
      bool clear_subtile=   res.tile_min.x || res.tile_end.x<m_tiling.tile_width()
                         || res.tile_min.y || res.tile_end.y<m_tiling.tile_height();
      if(!res.tile_end.x || !res.tile_end.y)
        continue;

      // clear depth
      switch(m_cfg.depth.format)
      {
        // no depth
        case rtzr_depthfmt_none: break;

        // 8bpp unorm depth buffer
        case rtzr_depthfmt_uint8:
        {
          if(clear_subtile)
          {
            usize_t depth_subtile_sline_size=sizeof(uint8_t)*(res.tile_end.x-res.tile_min.x);
            usize_t depth_tile_width=m_tiling.tile_width();
            uint8_t *p=(uint8_t*)m_cfg.depth.data+res.tile_min.x+res.tile_min.y*m_tiling.tile_width();
            uint8_t *p_end=p+depth_tile_width*(res.tile_end.y-res.tile_min.y);
            do
            {
              mem_set(p, 0xff, depth_subtile_sline_size);
              p+=depth_tile_width;
            } while(p<p_end);
          }
          else
          {
            usize_t depth_tile_size=sizeof(uint8_t)*m_tiling.tile_width()*m_tiling.tile_height();
            mem_set(m_cfg.depth.data, 0xff, depth_tile_size);
          }
        } break;

        // 16bpp unorm depth buffer
        case rtzr_depthfmt_uint16:
        {
          if(clear_subtile)
          {
            usize_t depth_subtile_sline_size=sizeof(uint16_t)*(res.tile_end.x-res.tile_min.x);
            usize_t depth_tile_width=m_tiling.tile_width();
            uint16_t *p=(uint16_t*)m_cfg.depth.data+res.tile_min.x+res.tile_min.y*m_tiling.tile_width();
            uint16_t *p_end=p+depth_tile_width*(res.tile_end.y-res.tile_min.y);
            do
            {
              mem_set(p, 0xff, depth_subtile_sline_size);
              p+=depth_tile_width;
            } while(p<p_end);
          }
          else
          {
            usize_t depth_tile_size=sizeof(uint16_t)*m_tiling.tile_width()*m_tiling.tile_height();
            mem_set(m_cfg.depth.data, 0xff, depth_tile_size);
          }
        } break;

        // 32bpp float depth buffer
        case rtzr_depthfmt_float32:
        {
          if(clear_subtile)
          {
            usize_t subtile_width=res.tile_end.x-res.tile_min.x;
            usize_t depth_tile_pitch_delta=m_tiling.tile_width()-subtile_width;
            float32_t *p=(float32_t*)m_cfg.depth.data+res.tile_min.x+res.tile_min.y*m_tiling.tile_width();
            float32_t *p_tile_end=p+m_tiling.tile_width()*(res.tile_end.y-res.tile_min.y);
            do
            {
              float32_t *scan_p_end=p+subtile_width;
              do
              {
                *p=1.0f;
              } while(++p<scan_p_end);
              p+=depth_tile_pitch_delta;
            } while(p<p_tile_end);
          }
          else
          {
            float32_t *p=(float32_t*)m_cfg.depth.data, *p_end=p+m_tiling.tile_width()*m_tiling.tile_height();
            do
            {
              *p=1.0f;
            } while(++p<p_end);
          }
        } break;

        // unsupported format
        default: PFC_ERROR(("Unsupported depth format\r\n"));
      }

      // clear hi-z
      if(m_cfg.depth.hiz_data)
        mem_set(m_cfg.depth.hiz_data, 0xff, sizeof(uint16_t)*m_tiling.tile_width()*m_tiling.tile_height()/(rasterizer_hiz_tile_size*rasterizer_hiz_tile_size));

      // clear render targets
      for(uint8_t rt_idx=0; rt_idx<m_cfg.num_rts; ++rt_idx)
      {
        uint16_t px_size=m_cfg.rts[rt_idx].px_size;
        usize_t rt_tile_pitch=px_size*m_tiling.tile_width();
        if(clear_subtile)
        {
          usize_t rt_subtile_sline_size=px_size*(res.tile_end.x-res.tile_min.x);
          uint8_t *p=(uint8_t*)m_cfg.rts[rt_idx].data+px_size*(res.tile_min.x+res.tile_min.y*m_tiling.tile_width());
          uint8_t *p_end=p+rt_tile_pitch*(res.tile_end.y-res.tile_min.y);
          do
          {
            mem_zero(p, rt_subtile_sline_size);
            p+=rt_tile_pitch;
          } while(p<p_end);
        }
        else
        {
          usize_t rt_tile_size=rt_tile_pitch*m_tiling.tile_height();
          mem_zero(m_cfg.rts[rt_idx].data, rt_tile_size);
        }
      }
    }
  } while(++tile<tile_end);

  // clear rasterizer state
  m_tiling.clear();
  m_vertex_cache.release();
  m_num_dispatches=0;
  m_num_clusters=0;
  m_shader_write_pos=0;
}
//----------------------------------------------------------------------------

template<typename T>
void rasterizer::update_hiz(const rasterizer::result &res_)
{
  // prepare hi-z update
  vec2i32 hiz_tile_min={res_.tile_min.x/rasterizer_hiz_tile_size, res_.tile_min.y/rasterizer_hiz_tile_size};
  vec2i32 hiz_tile_end={(res_.tile_end.x+rasterizer_hiz_tile_size-1)/rasterizer_hiz_tile_size, (res_.tile_end.y+rasterizer_hiz_tile_size-1)/rasterizer_hiz_tile_size};
  uint16_t hiz_update_width=uint16_t(hiz_tile_end.x-hiz_tile_min.x);
  uint16_t hiz_update_height=uint16_t(hiz_tile_end.y-hiz_tile_min.y);
  uint16_t hiz_tile_pitch=m_tiling.tile_width()/rasterizer_hiz_tile_size;
  uint16_t zbuf_tile_scan_pitch=m_tiling.tile_width()-hiz_update_width*rasterizer_hiz_tile_size;

  // iterate over all hi-z tiles
  uint16_t *hiz_buf=m_cfg.depth.hiz_data+hiz_tile_min.x+hiz_tile_min.y*hiz_tile_pitch;
  uint16_t *hiz_buf_end=hiz_buf+hiz_update_height*hiz_tile_pitch;
  uint16_t hiz_y=uint16_t(hiz_tile_min.y*rasterizer_hiz_tile_size);
  do
  {
    uint16_t *hiz_buf_scan_end=hiz_buf+hiz_update_width;
    uint16_t hiz_x=uint16_t(hiz_tile_min.x*rasterizer_hiz_tile_size);
    do
    {
      // update hi-z tile
      const T *zbuf=(T*)m_cfg.depth.data+hiz_x+hiz_y*m_tiling.tile_width();
      const T *zbuf_end=zbuf+m_tiling.tile_width()*rasterizer_hiz_tile_size;
      T tile_maxz=0;
      do
      {
        // update hi-z tile scanline
        PFC_CTF_ASSERT(rasterizer_hiz_tile_size==16);
        T maxz[4];
        maxz[0]=max(zbuf[ 0], zbuf[ 1], zbuf[ 2], zbuf[ 3]);
        maxz[1]=max(zbuf[ 4], zbuf[ 5], zbuf[ 6], zbuf[ 7]);
        maxz[2]=max(zbuf[ 8], zbuf[ 9], zbuf[10], zbuf[11]);
        maxz[3]=max(zbuf[12], zbuf[13], zbuf[14], zbuf[15]);
        tile_maxz=max(tile_maxz, max(maxz[0], maxz[1], maxz[2], maxz[3]));
        zbuf+=m_tiling.tile_width();
      } while(zbuf<zbuf_end);
      *hiz_buf=hiz_value(tile_maxz);
      hiz_x+=rasterizer_hiz_tile_size;
    } while(++hiz_buf<hiz_buf_scan_end);

    // proceed to the next row of hi-z tiles
    hiz_y+=rasterizer_hiz_tile_size;
    hiz_buf+=zbuf_tile_scan_pitch/rasterizer_hiz_tile_size;
  } while(hiz_buf<hiz_buf_end);
}
//----------------------------------------------------------------------------
