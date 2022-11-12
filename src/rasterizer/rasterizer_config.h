//============================================================================
// Software Rasterizer Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_RASTERIZER_CONFIG_H
#define PFC_RASTERIZER_CONFIG_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/core.h"
namespace pfc
{

// new
#define PFC_BUILDOP_RASTERIZER_HIZ 1
typedef uint16_t rasterizer_vertex_cache_offset_t;
typedef uint16_t rasterizer_local_cluster_index_t;   // clusters for single shader dispatch
typedef uint16_t rasterizer_global_cluster_index_t;  // clusters for all shader dispatches in a frame
typedef uint16_t rasterizer_cluster_strip_index_t;   // cluster strips in a frame
typedef uint16_t rasterizer_dispatch_index_t;        // dispatch calls in a frame
typedef uint16_t rasterizer_tile_size_t;             // tile size
enum {rasterizer_subpixel_bits=4};                   // rasterization sub-pixel precision
enum {rasterizer_hiz_tile_size=16};                  // hi-z tile size
enum {rasterizer_max_strip_clusters=32};             // number of clusters per cluster strip
enum {rasterizer_tform_cache_block_size=16};         // transform cache block size in bytes (allocation granularity)
//----
enum {rasterizer_max_local_clusters=(rasterizer_local_cluster_index_t(-1)>>1)+1};
enum {rasterizer_subpixel_bitmask=rasterizer_subpixel_bits?(1<<rasterizer_subpixel_bits)-1:0};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
