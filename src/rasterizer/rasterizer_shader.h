//============================================================================
// Software Rasterizer Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_RASTERIZER_SHADER_H
#define PFC_RASTERIZER_SHADER_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "rasterizer/rasterizer_config.h"
#include "core/math/math.h"
namespace pfc
{

// new
struct rasterizer_shader_base;
//----------------------------------------------------------------------------


//============================================================================
// e_depth_format
//============================================================================
enum e_rasterizer_depth_format
{
  rtzr_depthfmt_none,    // no depth (test always passes, writes do nothing)
  rtzr_depthfmt_uint8,   // 8-bit depth in range [0, 255]
  rtzr_depthfmt_uint16,  // 16-bit depth in range [0, 65535]
  rtzr_depthfmt_float32  // float32 depth in range [0, 1]
};
//----

template<e_rasterizer_depth_format> struct depth_format_traits;
template<> struct depth_format_traits<rtzr_depthfmt_none>    {typedef uint8_t depth_format_t;};
template<> struct depth_format_traits<rtzr_depthfmt_uint8>   {typedef uint8_t depth_format_t;};
template<> struct depth_format_traits<rtzr_depthfmt_uint16>  {typedef uint16_t depth_format_t;};
template<> struct depth_format_traits<rtzr_depthfmt_float32> {typedef float32_t depth_format_t;};
//----------------------------------------------------------------------------


//============================================================================
// e_rasterizer_cullmode
//============================================================================
enum e_rasterizer_cullmode
{
  rtzr_cullmode_none,  // no culling
  rtzr_cullmode_cw,    // cull clockwise triangles
  rtzr_cullmode_ccw,   // cull counter-clockwise triangles
};
//----------------------------------------------------------------------------


//============================================================================
// e_rasterizer_depth_func
//============================================================================
enum e_rasterizer_depth_func
{
  rtzr_depthfunc_always,
  rtzr_depthfunc_never,
  rtzr_depthfunc_equal,
  rtzr_depthfunc_not_equal,
  rtzr_depthfunc_less,
  rtzr_depthfunc_less_equal,
  rtzr_depthfunc_greater,
  rtzr_depthfunc_greater_equal,
};
//----------------------------------------------------------------------------


//============================================================================
// e_rasterizer_interp_type
//============================================================================
enum e_rasterizer_interp_type
{
  rtzr_interp_noperspective,     // no perspective-correct interpolation (fastest)
  rtzr_interp_perspective,       // perspective correct interpolation
  rtzr_interp_perspective_fast,  // approximate fast perspective correct interpolation
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_shader_base
//============================================================================
struct rasterizer_shader_base
{
  // default config
  enum {depth_format=rtzr_depthfmt_none};
  enum {depth_func=rtzr_depthfunc_less};
  enum {depth_write=true};
  enum {hiz_write=true};
  enum {cullmode=rtzr_cullmode_ccw};
  enum {interp=rtzr_interp_perspective};
  enum {vertex_cache=true};
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
