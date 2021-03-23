//============================================================================
// Software Rasterizer Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_RASTERIZER_H
#define PFC_RASTERIZER_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "rasterizer/rasterizer_tiling.h"
#include "rasterizer/rasterizer_cache.h"
#include "rasterizer/rasterizer_shader.h"
#include "core/math/fast_math.h"
namespace pfc
{

// new
typedef vec2<uint16_t> vec2u16;
typedef vec2<int32_t> vec2i32;
typedef vec3<int32_t> vec3i32;
struct rasterizer_depth_target;
struct rasterizer_render_target;
struct rasterizer_dispatch;
struct rasterizer_stats;
struct rasterizer_cfg;
class rasterizer_callback_base;
class rasterizer;
// build config
#if defined(PFC_DEBUG) || defined(PFC_RELEASE)
#define PFC_BUILDOP_RASTERIZER_STATS 1
#else
#define PFC_BUILDOP_RASTERIZER_STATS 0
#endif
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_depth_target
//============================================================================
struct rasterizer_depth_target
{
  void *data;
  uint16_t *hiz_data;
  e_rasterizer_depth_format format;
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_render_target
//============================================================================
struct rasterizer_render_target
{
  void *data;
  uint8_t px_size;
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_dispatch
//============================================================================
struct rasterizer_dispatch
{
  usize_t shader_wrapper[2];
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_data_transfer
//============================================================================
struct rasterizer_data_transfer
{
  usize_t data_offset;
  uint16_t x, y;
  uint16_t width, height;
};
//---------------------------------------------------------------------------


//============================================================================
// rasterizer_memory_cfg_base
//============================================================================
// rasterizer memory config struct from this struct which also specifies:
//   enum {fbuf_width=...};
//   enum {fbuf_height=...};
// you can also override config values for the new config, e.g.
// struct my_rasterizer_mem_cfg: rasterizer_memory_cfg_base
// {
//   enum {fbuf_width=320};     // frame buffer resolution
//   enum {fbuf_height=240};
//   enum {depth_format=rtzr_depthfmt_float32};
// };
struct rasterizer_memory_cfg_base
{
  // depth
  enum {depth_format=rtzr_depthfmt_uint16};
  enum {depth_hiz=true};
  // render target & frame buffer
  typedef uint16_t fbuf_fmt_t;           // native frame buffer format
  typedef fbuf_fmt_t rt_fmt_t;           // render target format
  // config
  enum {max_dispatches=64};              // max shader dispatches per commit
  enum {shader_store_size=16384};        // total shader store per commit
  enum {tile_width=64, tile_height=64};  // tile size in pixels
  enum {tile_order=tileorder_morton};    // tile render order
  enum {max_clusters=256};               // maximum total rendered clusters per commit
  enum {max_cluster_strips=256};         // max total cluster strips (for cluster tile binning)
  enum {max_vout_size=64*32};            // max cluster vertex output size in bytes
  enum {vcache_size=32768};              // vertex cache size in bytes
  enum {max_dma_transfers=8};            // maximum queued DMA transfers
  enum {dma_buffer_px=tile_width*        // number of pixel allocated for DMA transfer buffer
                      tile_height};
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_memory
//============================================================================
// container for rasterizer memory defined by the config
template<class Cfg>
struct rasterizer_memory
{
  enum {tiled_rt_width=(Cfg::fbuf_width+Cfg::tile_width-1)/Cfg::tile_width};
  enum {tiled_rt_height=(Cfg::fbuf_height+Cfg::tile_height-1)/Cfg::tile_height};
  enum {num_rt_tiles=tiled_rt_width*tiled_rt_height};
  //--------------------------------------------------------------------------

  // initialization
  rasterizer_memory();
  template<class HWDevice> rasterizer_memory(HWDevice&);
  template<class HWDevice> void init(HWDevice&);
  //--------------------------------------------------------------------------

  // tile pixel storage
  typename depth_format_traits<(e_rasterizer_depth_format)Cfg::depth_format>::depth_format_t depth_tile[Cfg::depth_format!=int(rtzr_depthfmt_none)?Cfg::tile_width*Cfg::tile_height:0];
  uint16_t depth_hiz_tile[Cfg::depth_format!=int(rtzr_depthfmt_none) && Cfg::depth_hiz?Cfg::tile_width*Cfg::tile_height/(rasterizer_hiz_tile_size*rasterizer_hiz_tile_size):0];
  typename Cfg::rt_fmt_t rt_tile[Cfg::tile_width*Cfg::tile_height];
  // shader dispatching
  rasterizer_dispatch dispatches[Cfg::max_dispatches];
  usize_t shader_store[Cfg::shader_store_size/sizeof(usize_t)];
  // frame buffer tiling
  uint16_t tile_map[Cfg::tile_order==int(tileorder_linear)?0:num_rt_tiles];
  rasterizer_tile tiles[num_rt_tiles];
  rasterizer_cluster clusters[Cfg::max_clusters];
  rasterizer_tile_cluster_strip cluster_strips[Cfg::max_cluster_strips];
  rasterizer_render_target rts[1];
  // vertex cache
  usize_t vcache_buf[Cfg::vcache_size/sizeof(usize_t)];
  usize_t cluster_vout_buf[Cfg::max_vout_size/sizeof(usize_t)];
  rasterizer_vertex_cache_offset_t vcache_offs[Cfg::vcache_size?Cfg::max_clusters:0];
  // DMA
  typename Cfg::fbuf_fmt_t dma_buf[Cfg::max_dma_transfers?Cfg::dma_buffer_px:0];
  rasterizer_data_transfer dma_transfers[Cfg::max_dma_transfers];
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_stats
//============================================================================
struct rasterizer_stats
{
  void reset();
  void log() const;
  //--------------------------------------------------------------------------

  usize_t num_dispatches;
  usize_t shader_store_size;
  usize_t num_cluster_strips;
  usize_t tmp_vout_size;
  usize_t num_clusters;
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_cfg
//============================================================================
struct rasterizer_cfg
{
  // construction & setup
  rasterizer_cfg();
  void set_dispatches(rasterizer_dispatch*, rasterizer_dispatch_index_t max_dispatches_);
  void set_shader_store(void *shader_store_, usize_t shader_store_size_);
  void set_depth(void *depth_buffer_, uint16_t *hiz_buffer_, e_rasterizer_depth_format);
  void set_rts(rasterizer_render_target *rts_, uint8_t num_rts_);
  //--------------------------------------------------------------------------

  rasterizer_dispatch *dispatches;
  rasterizer_dispatch_index_t max_dispatches;
  void *shader_store;
  usize_t shader_store_size;
  rasterizer_depth_target depth;
  rasterizer_render_target *rts;
  uint8_t num_rts;
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_callback_base
//============================================================================
class rasterizer_callback_base
{
public:
  // callback interface
  virtual void submit_tile(uint8_t tx_, uint8_t ty_, uint16_t tile_width_, uint16_t tile_height_, const vec2u16 &reg_min_, const vec2u16 &reg_end_)=0;
  //--------------------------------------------------------------------------

protected:
  // construction
  rasterizer_callback_base() {}
  //--------------------------------------------------------------------------

  //==========================================================================
  // tile_pshader
  //==========================================================================
  template<class TShader>
  struct tile_pshader
  {
    PFC_INLINE uint16_t exec(uint16_t x_, uint16_t y_) const
    {
      return shader->shade_pixel(rts, *dt, px_offs+x_+y_*pitch, x_, y_);
    }
    //------------------------------------------------------------------------

    const TShader *shader;
    const rasterizer_render_target *rts;
    const rasterizer_depth_target *dt;
    usize_t px_offs;
    uint16_t pitch;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // tile_shader_wrapper_base
  //==========================================================================
  struct tile_shader_wrapper_base
  {
    virtual void copy_region(void *dst_, const rasterizer_render_target *rts_, const rasterizer_depth_target&, usize_t src_px_offs_, uint16_t x_, uint16_t y_, uint16_t width_, uint16_t height_, uint16_t pitch_)=0;
    virtual void transfer_region(const rasterizer_render_target *rts_, const rasterizer_depth_target &dt_, usize_t src_px_offs_, uint16_t x_, uint16_t y_, uint16_t width_, uint16_t height_, uint16_t pitch_)=0;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // tile_shader_wrapper
  //==========================================================================
  template<class HWDevice, class TShader>
  struct tile_shader_wrapper: tile_shader_wrapper_base
  {
    virtual void copy_region(void *dst_, const rasterizer_render_target *rts_, const rasterizer_depth_target&, usize_t src_px_offs_, uint16_t x_, uint16_t y_, uint16_t width_, uint16_t height_, uint16_t pitch_);
    virtual void transfer_region(const rasterizer_render_target *rts_, const rasterizer_depth_target &dt_, usize_t src_px_offs_, uint16_t x_, uint16_t y_, uint16_t width_, uint16_t height_, uint16_t pitch_);
    HWDevice *m_dev;
    const TShader *m_shader;
  };
  //--------------------------------------------------------------------------

private:
  rasterizer_callback_base(const rasterizer_callback_base&); // not implemented
  void operator=(const rasterizer_callback_base&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer
//============================================================================
class rasterizer
{
public:
  // construction
  rasterizer();
  void init(const rasterizer_cfg&, const rasterizer_tiling_cfg&, const rasterizer_vertex_cache_cfg&);
  PFC_INLINE void set_callback(rasterizer_callback_base*);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE uint8_t num_render_targets() const;
  PFC_INLINE const rasterizer_render_target *render_targets() const;
  PFC_INLINE const rasterizer_depth_target &depth_target() const;
  //--------------------------------------------------------------------------

  // rasterization
  template<class Shader> void dispatch_shader(const Shader&);
  void commit();
  //--------------------------------------------------------------------------

  // stats (query after commit)
  PFC_INLINE void reset_stats();
  PFC_INLINE void log_stats() const;
  PFC_INLINE rasterizer_stats stats() const;
  //--------------------------------------------------------------------------
  
private:
  struct result;
  rasterizer(const rasterizer&); // not implemented
  void operator=(const rasterizer&); // not implemented
  template<typename> void update_hiz(const result&);
  static PFC_INLINE int32_t cross2d(const vec2i32& a_, const vec2i32& b_, const vec2i32& c_)  {return (b_.x-a_.x)*(c_.y-a_.y)-(b_.y-a_.y)*(c_.x-a_.x);}
  template<int> static PFC_INLINE float read_depth(const void *dbuf_, uint32_t offs_);
  template<int> static PFC_INLINE void write_depth(const void *dbuf_, uint32_t offs_, float z_);
  template<int> static PFC_INLINE bool test_depth(float z_, float zbuf_);
  template<typename T> static PFC_INLINE uint16_t hiz_value(T);
  //--------------------------------------------------------------------------

  //==========================================================================
  // result
  //==========================================================================
  struct result
  {
    vec2u16 tile_min, tile_end;
    e_rasterizer_depth_format hiz_depth_format;
    usize_t max_vout;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // render_target_cfg
  //==========================================================================
  struct render_target_cfg
  {
    uint16_t rt_width, rt_height;
    vec2f rt_coord_scale;
    uint16_t tile_width, tile_height;
    uint16_t tile_pitch;
    rasterizer_depth_target depth;
    rasterizer_render_target *rts;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // shader_wrapper_base
  //==========================================================================
  struct shader_wrapper_base
  {
    virtual void rasterize_cluster(result&, const render_target_cfg&, uint16_t tile_x_, uint16_t tile_y_, rasterizer_vertex_cache&, rasterizer_local_cluster_index_t, rasterizer_global_cluster_index_t) const=0;
    const void *m_shader;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // shader_wrapper
  //==========================================================================
  template<class Shader>
  struct shader_wrapper: shader_wrapper_base
  {
    shader_wrapper(const Shader&);
    virtual void rasterize_cluster(result&, const render_target_cfg&, uint16_t tile_x_, uint16_t tile_y_, rasterizer_vertex_cache&, rasterizer_local_cluster_index_t, rasterizer_global_cluster_index_t) const;
  };
  //--------------------------------------------------------------------------

  enum {shader_mem_align=sizeof(usize_t)};
  rasterizer_callback_base *m_callback;
  rasterizer_cfg m_cfg;
  rasterizer_tiling m_tiling;
  rasterizer_vertex_cache m_vertex_cache;
  rasterizer_dispatch_index_t m_num_dispatches;
  rasterizer_global_cluster_index_t m_num_clusters;
  usize_t m_shader_write_pos;
  // stats
#if PFC_BUILDOP_RASTERIZER_STATS==1
  rasterizer_stats m_stats;
#endif
};
//----------------------------------------------------------------------------




//============================================================================
//============================================================================
// inline & template implementations
//============================================================================
//============================================================================


//============================================================================
// rasterizer_memory
//============================================================================
template<class Cfg>
rasterizer_memory<Cfg>::rasterizer_memory()
{
}
//----

template<class Cfg>
template<class HWDevice>
rasterizer_memory<Cfg>::rasterizer_memory(HWDevice &dev_)
{
  init(dev_);
}
//----

template<class Cfg>
template<class HWDevice>
void rasterizer_memory<Cfg>::init(HWDevice &dev_)
{
  // setup rasterizer config
  rasterizer_cfg rcfg;
  rcfg.set_dispatches(dispatches, Cfg::max_dispatches);
  rcfg.set_shader_store(shader_store, sizeof(shader_store));
  rcfg.set_depth(depth_tile, Cfg::depth_hiz?depth_hiz_tile:0, (e_rasterizer_depth_format)Cfg::depth_format);
  rts[0].data=rt_tile;
  rts[0].px_size=sizeof(typename Cfg::rt_fmt_t);
  rcfg.set_rts(rts, sizeof(rts)/sizeof(*rts));

  // setup tiling config
  rasterizer_tiling_cfg tcfg;
  tcfg.set_render_target_size(Cfg::fbuf_width, Cfg::fbuf_height);
  tcfg.set_tiles(tiles, Cfg::tile_order==int(tileorder_linear)?0:tile_map, Cfg::tile_width, Cfg::tile_height);
  tcfg.set_tile_order((e_tile_order)Cfg::tile_order);
  tcfg.set_clusters(clusters, Cfg::max_clusters);
  tcfg.set_cluster_strips(cluster_strips, Cfg::max_cluster_strips);

  // setup vertex cache config
  rasterizer_vertex_cache_cfg vccfg;
  vccfg.set_cache(vcache_buf, sizeof(vcache_buf));
  vccfg.set_cluster_vout(cluster_vout_buf, sizeof(cluster_vout_buf));
  vccfg.set_cache_clusters(Cfg::vcache_size?vcache_offs:0, Cfg::vcache_size?Cfg::max_clusters:0);

  // initialize rasterizer
  dev_.init_rasterizer(rcfg, tcfg, vccfg);
  if(Cfg::max_dma_transfers)
    dev_.init_dma(dma_transfers, Cfg::max_dma_transfers, dma_buf, sizeof(dma_buf));
}
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_callback_base::tile_shader_wrapper
//============================================================================
template<class HWDevice, class TShader>
void rasterizer_callback_base::tile_shader_wrapper<HWDevice, TShader>::copy_region(void *dst_, const rasterizer_render_target *rts_, const rasterizer_depth_target &dt_, usize_t src_px_offs_, uint16_t x_, uint16_t y_, uint16_t width_, uint16_t height_, uint16_t pitch_)
{
  // apply tile shader to the given region of pixels
  typedef typename TShader::dst_fmt_t dst_fmt_t;
  dst_fmt_t *dst=(dst_fmt_t*)dst_, *dst_end=dst+width_*height_;
  const TShader *sh=m_shader;
  uint16_t row_pitch=pitch_-width_;
  do
  {
    // process scanline
    const dst_fmt_t *dst_scan_end=dst+width_;
    uint16_t x=x_;
    do
    {
      *dst++=sh->shade_pixel(rts_, dt_, src_px_offs_++, x++, y_);
    } while(dst<dst_scan_end);

    // proceed to the scanline
    src_px_offs_+=row_pitch;
    ++y_;
  } while(dst<dst_end);
}
//----

template<class HWDevice, class TShader>
void rasterizer_callback_base::tile_shader_wrapper<HWDevice, TShader>::transfer_region(const rasterizer_render_target *rts_, const rasterizer_depth_target &dt_, usize_t src_px_offs_, uint16_t x_, uint16_t y_, uint16_t width_, uint16_t height_, uint16_t pitch_)
{
  // transform tile region to the display
  tile_pshader<TShader> ps={m_shader, rts_, &dt_, src_px_offs_-x_-y_*pitch_, pitch_};
  m_dev->fast_draw_rect(x_, y_, width_, height_, ps);
}
//----------------------------------------------------------------------------


//============================================================================
// rasterizer::shader_wrapper
//============================================================================
template<class Shader>
rasterizer::shader_wrapper<Shader>::shader_wrapper(const Shader &sh_)
{
  m_shader=&sh_;
}
//----------------------------------------------------------------------------

template<class Shader>
void rasterizer::shader_wrapper<Shader>::rasterize_cluster(result &res_, const render_target_cfg &rt_cfg_, uint16_t tile_x_, uint16_t tile_y_, rasterizer_vertex_cache &vcache_, rasterizer_local_cluster_index_t cluster_idx_, rasterizer_global_cluster_index_t global_cluster_idx_) const
{
  // get cluster and transformed cluster vertices
  enum {cullmode=Shader::cullmode};
  typedef typename Shader::vout vout_t;
  PFC_ASSERT(Shader::depth_format==int(rtzr_depthfmt_none) || int(Shader::depth_format)==int(rt_cfg_.depth.format));
  res_.hiz_depth_format=Shader::depth_write && Shader::hiz_write?e_rasterizer_depth_format(Shader::depth_format):rtzr_depthfmt_none;
  const Shader &sh=*(const Shader*)m_shader;
  const void *cluster;
  vout_t *vout;
  if(!Shader::vertex_cache || cluster_idx_&rasterizer_max_local_clusters || !vcache_.cache_size())
  {
    // use temporal store for vout (single tile cluster lifetime or no caching)
    cluster_idx_&=~rasterizer_max_local_clusters;
    cluster=sh.cluster(cluster_idx_);
    usize_t vout_size=sh.num_cluster_vertices(cluster)*sizeof(vout_t);
    PFC_ASSERT_MSG(vout_size<=vcache_.tmp_cluster_vout_size(), ("Temporal vertex output buffer is too small (%zi bytes) for the cluster vertex output (%zi bytes)\r\n", vcache_.tmp_cluster_vout_size(), vout_size));
    res_.max_vout=max(res_.max_vout, vout_size);
    vout=(vout_t*)vcache_.tmp_cluster_vout();
  }
  else
  {
    // allocate vout from cache if the result is not in the cache yet
    cluster=sh.cluster(cluster_idx_);
    vout=(vout_t*)vcache_.cluster_cache(global_cluster_idx_);
    if(vout)
      goto vout_found_in_cache;
    usize_t vout_size=sh.num_cluster_vertices(cluster)*sizeof(vout_t);
    res_.max_vout=max(res_.max_vout, vout_size);
    vout=(vout_t*)vcache_.alloc_cluster_cache(global_cluster_idx_, vout_size);
  }
  sh.tform_cluster(vout, cluster);
  vout_found_in_cache:;

  // rasterize the cluster
  uint16_t tile_xe=tile_x_+rt_cfg_.tile_width, tile_ye=tile_y_+rt_cfg_.tile_height;
  uint8_t num_prims=sh.num_cluster_triangles(cluster);
  for(uint8_t prim_idx=0; prim_idx<num_prims; ++prim_idx)
  {
    // setup triangle
    uint8_t vidx[3];
    vec4f vpos[3];
    sh.setup_primitive(vout, cluster, prim_idx, vidx, vpos);
    vec2i32 v0={int32_t((1.0f+vpos[0].x)*rt_cfg_.rt_coord_scale.x), int32_t((1.0f-vpos[0].y)*rt_cfg_.rt_coord_scale.y)};
    vec2i32 v1={int32_t((1.0f+vpos[1].x)*rt_cfg_.rt_coord_scale.x), int32_t((1.0f-vpos[1].y)*rt_cfg_.rt_coord_scale.y)};
    vec2i32 v2={int32_t((1.0f+vpos[2].x)*rt_cfg_.rt_coord_scale.x), int32_t((1.0f-vpos[2].y)*rt_cfg_.rt_coord_scale.y)};

    // check backface culling
    int32_t signed_area=cross2d(v0, v1, v2);
    if(int(cullmode)!=rtzr_cullmode_none)
    {
      if(int(cullmode)==rtzr_cullmode_cw)
        signed_area=-signed_area;
      if(signed_area<=0)
        continue;
    }
    const bool is_front_facing=cullmode==int(rtzr_cullmode_ccw) || (cullmode==int(rtzr_cullmode_none) && signed_area>0);

    // calculate triangle bounding rectangle (clamp to tile boundaries)
    minmax_res<int32_t> brect_minmax_x=minmax(v0.x, v1.x, v2.x);
    minmax_res<int32_t> brect_minmax_y=minmax(v0.y, v1.y, v2.y);
    vec2u16 brect_min={(uint16_t)max<int16_t>(tile_x_, int16_t(brect_minmax_x.min+rasterizer_subpixel_bitmask)>>rasterizer_subpixel_bits),
                       (uint16_t)max<int16_t>(tile_y_, int16_t(brect_minmax_y.min+rasterizer_subpixel_bitmask)>>rasterizer_subpixel_bits)};
    vec2u16 brect_end={(uint16_t)min<int16_t>(tile_xe, int16_t(brect_minmax_x.max>>rasterizer_subpixel_bits)+1),
                       (uint16_t)min<int16_t>(tile_ye, int16_t(brect_minmax_y.max>>rasterizer_subpixel_bits)+1)};
    uint16_t brect_width=brect_end.x-brect_min.x;
    uint16_t brect_height=brect_end.y-brect_min.y;
    if(int16_t(brect_width)<=0 || int16_t(brect_height)<=0)
      continue;

    // setup triangle edge functions
    vec2i32 p={brect_min.x<<rasterizer_subpixel_bits, brect_min.y<<rasterizer_subpixel_bits};
    vec3i32 w_row={cross2d(v1, v2, p), cross2d(v2, v0, p), cross2d(v0, v1, p)};
    vec3i32 dwdx={v1.y-v2.y, v2.y-v0.y, v0.y-v1.y};
    vec3i32 dwdy={v2.x-v1.x, v0.x-v2.x, v1.x-v0.x};
    if(!is_front_facing)
    {
      w_row.x=-w_row.x; w_row.y=-w_row.y; w_row.z=-w_row.z;
      dwdx.x=-dwdx.x; dwdx.y=-dwdx.y; dwdx.z=-dwdx.z;
      dwdy.x=-dwdy.x; dwdy.y=-dwdy.y; dwdy.z=-dwdy.z;
    }
    if(dwdx.x<0 || (!dwdx.x && dwdy.x>0))
      --w_row.x;
    if(dwdx.y<0 || (!dwdx.y && dwdy.y>0))
      --w_row.y;
    if(dwdx.z<0 || (!dwdx.z && dwdy.z>0))
      --w_row.z;
    w_row.x>>=rasterizer_subpixel_bits;
    w_row.y>>=rasterizer_subpixel_bits;
    w_row.z>>=rasterizer_subpixel_bits;

    // setup triangle bounds
    brect_min.x-=tile_x_;
    brect_min.y-=tile_y_;
    brect_end.x-=tile_x_;
    brect_end.y-=tile_y_;
    res_.tile_min=min(res_.tile_min, brect_min);
    res_.tile_end=max(res_.tile_end, brect_end);

    // rasterize the triangle
    float bc_scale=1.0f/(w_row.x+w_row.y+w_row.z);
    vpos[0].z*=bc_scale;
    vpos[1].z*=bc_scale;
    vpos[2].z*=bc_scale;
    uint32_t px_offs_row=brect_min.x+brect_min.y*rt_cfg_.tile_pitch;
    do
    {
      // skip pixels until hit the triangle /*todo: can we efficiently skip to the triangle edge without iteration?*/
      vec3i32 w=w_row;
      uint32_t px_offs=uint32_t(-brect_width);
      while(int32_t((w.x|w.y|w.z)&px_offs)<=0)
      {
        w.x+=dwdx.x;
        w.y+=dwdx.y;
        w.z+=dwdx.z;
        ++px_offs;
      }

      // rasterize triangle scanline span
      uint32_t px_offs_end=px_offs_row+brect_width;
      px_offs+=px_offs_end;
      while((w.x|w.y|w.z)>0 && px_offs<px_offs_end)
      {
        vec3f bc={float(w.x), float(w.y), float(w.z)};
        float z=(bc.x*vpos[0].z+bc.y*vpos[1].z+bc.z*vpos[2].z);
        if(test_depth<Shader::depth_format!=int(rtzr_depthfmt_none)?Shader::depth_func:int(rtzr_depthfunc_always)>(z, read_depth<Shader::depth_format>(rt_cfg_.depth.data, px_offs)))
        {
          write_depth<Shader::depth_write?int(Shader::depth_format):int(rtzr_depthfmt_none)>(rt_cfg_.depth.data, px_offs, z);
          if(Shader::interp==int(rtzr_interp_perspective) || Shader::interp==int(rtzr_interp_perspective_fast))
          {
            bc.x*=vpos[0].w;
            bc.y*=vpos[1].w;
            bc.z*=vpos[2].w;
            float bc_sum=bc.x+bc.y+bc.z;
            float oobc=Shader::interp==int(rtzr_interp_perspective)?1.0f/bc_sum:fast_rcp(bc_sum);
            bc.x*=oobc;
            bc.y*=oobc;
            bc.z*=oobc;
          }
          else
          {
            bc.x*=bc_scale;
            bc.y*=bc_scale;
            bc.z*=bc_scale;
          }
          sh.shade_pixel(rt_cfg_.rts, vout, px_offs, vidx, bc, prim_idx, tile_x_, tile_y_);
        }
        w.x+=dwdx.x;
        w.y+=dwdx.y;
        w.z+=dwdx.z;
        ++px_offs;
      }

      // proceed to the next scanline
      w_row.x+=dwdy.x;
      w_row.y+=dwdy.y;
      w_row.z+=dwdy.z;
      px_offs_row+=rt_cfg_.tile_pitch;
    } while(--brect_height);
  }
}
//----------------------------------------------------------------------------


//============================================================================
// rasterizer
//============================================================================
template<> PFC_INLINE float rasterizer::read_depth<rtzr_depthfmt_none>(const void*, uint32_t)                {return 1.0f;}
template<> PFC_INLINE float rasterizer::read_depth<rtzr_depthfmt_uint8>(const void *dbuf_, uint32_t offs_)   {return ((const uint8_t*)dbuf_)[offs_]/255.0f;}
template<> PFC_INLINE float rasterizer::read_depth<rtzr_depthfmt_uint16>(const void *dbuf_, uint32_t offs_)  {return ((const uint16_t*)dbuf_)[offs_]/65535.0f;}
template<> PFC_INLINE float rasterizer::read_depth<rtzr_depthfmt_float32>(const void *dbuf_, uint32_t offs_) {return ((const float*)dbuf_)[offs_];}
//----

template<> PFC_INLINE void rasterizer::write_depth<rtzr_depthfmt_none>(const void*, uint32_t, float)                   {}
template<> PFC_INLINE void rasterizer::write_depth<rtzr_depthfmt_uint8>(const void *dbuf_, uint32_t offs_, float z_)   {((uint8_t*)dbuf_)[offs_]=uint8_t(z_*255.0f);}
template<> PFC_INLINE void rasterizer::write_depth<rtzr_depthfmt_uint16>(const void *dbuf_, uint32_t offs_, float z_)  {((uint16_t*)dbuf_)[offs_]=uint16_t(z_*65535.0f);}
template<> PFC_INLINE void rasterizer::write_depth<rtzr_depthfmt_float32>(const void *dbuf_, uint32_t offs_, float z_) {((float*)dbuf_)[offs_]=z_;}
//----

template<> PFC_INLINE bool rasterizer::test_depth<rtzr_depthfunc_always>(float, float)                 {return true;}
template<> PFC_INLINE bool rasterizer::test_depth<rtzr_depthfunc_never>(float, float)                  {return false;}
template<> PFC_INLINE bool rasterizer::test_depth<rtzr_depthfunc_equal>(float z_, float zbuf_)         {return z_==zbuf_;}
template<> PFC_INLINE bool rasterizer::test_depth<rtzr_depthfunc_not_equal>(float z_, float zbuf_)     {return z_!=zbuf_;}
template<> PFC_INLINE bool rasterizer::test_depth<rtzr_depthfunc_less>(float z_, float zbuf_)          {return z_<zbuf_;}
template<> PFC_INLINE bool rasterizer::test_depth<rtzr_depthfunc_less_equal>(float z_, float zbuf_)    {return z_<=zbuf_;}
template<> PFC_INLINE bool rasterizer::test_depth<rtzr_depthfunc_greater>(float z_, float zbuf_)       {return z_>zbuf_;}
template<> PFC_INLINE bool rasterizer::test_depth<rtzr_depthfunc_greater_equal>(float z_, float zbuf_) {return z_>=zbuf_;}
//----

template<> PFC_INLINE uint16_t rasterizer::hiz_value<uint8_t>(uint8_t z_)     {return uint16_t(z_)<<8;}
template<> PFC_INLINE uint16_t rasterizer::hiz_value<uint16_t>(uint16_t z_)   {return z_;}
template<> PFC_INLINE uint16_t rasterizer::hiz_value<float32_t>(float32_t z_) {return uint16_t(z_*65535.0f);}
//----------------------------------------------------------------------------

void rasterizer::set_callback(rasterizer_callback_base *cb_)
{
  m_callback=cb_;
}
//----------------------------------------------------------------------------

uint8_t rasterizer::num_render_targets() const
{
  return m_cfg.num_rts;
}
//----

const rasterizer_render_target *rasterizer::render_targets() const
{
  return m_cfg.rts;
}
//----

const rasterizer_depth_target &rasterizer::depth_target() const
{
  return m_cfg.depth;
}
//----------------------------------------------------------------------------

void rasterizer::reset_stats()
{
#if PFC_BUILDOP_RASTERIZER_STATS==1
  m_stats.reset();
#endif
}
//----

void rasterizer::log_stats() const
{
#if PFC_BUILDOP_RASTERIZER_STATS==1
  m_stats.log();
#endif
}
//----

rasterizer_stats rasterizer::stats() const
{
#if PFC_BUILDOP_RASTERIZER_STATS==1
  return m_stats;
#else
  rasterizer_stats s;
  s.reset();
  return s;
#endif
}
//----------------------------------------------------------------------------

template<class Shader>
void rasterizer::dispatch_shader(const Shader &sh_)
{
  // prepare dispatch
  PFC_ASSERT(m_cfg.dispatches);
  PFC_ASSERT_MSG(m_num_dispatches<m_cfg.max_dispatches, ("Exceeding max shader dispatch count (%i)\r\n", m_cfg.max_dispatches));
  PFC_ASSERT_MSG(m_shader_write_pos+sizeof(Shader)<=m_cfg.shader_store_size, ("Out of shader store memory (%zi bytes)\r\n", m_cfg.shader_store_size));
  rasterizer_dispatch &dispatch=m_cfg.dispatches[m_num_dispatches];
  PFC_CTF_ASSERT(sizeof(shader_wrapper<Shader>)<=sizeof(dispatch.shader_wrapper));

  // setup shader
  Shader *sh=(Shader*)((uint8_t*)m_cfg.shader_store+m_shader_write_pos);
  mem_copy(sh, &sh_, sizeof(sh_));
  PFC_PNEW(dispatch.shader_wrapper)shader_wrapper<Shader>(*sh);
  m_shader_write_pos+=(sizeof(sh_)+sizeof(usize_t)-1)&-shader_mem_align;

  // setup clusters
  rasterizer_local_cluster_index_t num_clusters=sh->init_shader();
  for(rasterizer_local_cluster_index_t cidx=0; cidx<num_clusters; ++cidx)
    sh->setup_cluster(m_tiling, m_num_dispatches, cidx);
  m_num_clusters+=num_clusters;
  ++m_num_dispatches;
}
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
