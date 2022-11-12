//============================================================================
// Meshlete - Meshlet-based 3D object converter
//
// Copyright (c) 2020, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_MESHLETE_VBUF_EXPR_H
#define PFC_MESHLETE_VBUF_EXPR_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/expression.h"
#include "sxp_src/core/math/math.h"

// new
struct vbuf_expression_value;
typedef pfc::expression_parser<pfc::expression_parser_config<vbuf_expression_value> > vbuf_expression_parser_t;
void init_vbuf_expression_parser_funcs(vbuf_expression_parser_t&);
//----------------------------------------------------------------------------


//============================================================================
// vbuf_expression_value
//============================================================================
struct vbuf_expression_value
{
  // construction
  vbuf_expression_value();
  vbuf_expression_value(const vbuf_expression_value&);
  vbuf_expression_value(pfc::float64_t);
  vbuf_expression_value(int64_t);
  vbuf_expression_value(const char *str_, pfc::usize_t str_len_);
  vbuf_expression_value(const pfc::float32_t*, uint32_t num_vals_);
  vbuf_expression_value(const pfc::vec2f*, uint32_t num_vals_);
  vbuf_expression_value(const pfc::vec3f*, uint32_t num_vals_);
  vbuf_expression_value(const pfc::vec4f*, uint32_t num_vals_);
  vbuf_expression_value(const int32_t*, uint32_t num_vals_);
  vbuf_expression_value(const pfc::vec2i*, uint32_t num_vals_);
  vbuf_expression_value(const pfc::vec3i*, uint32_t num_vals_);
  vbuf_expression_value(const pfc::vec4i*, uint32_t num_vals_);
  ~vbuf_expression_value();
  template<typename T> void init(T*, uint8_t num_elems_, uint32_t num_vals_);
  void init(uint8_t num_elems_, uint32_t num_vals_);
  //--------------------------------------------------------------------------

  // data gathering
  template<typename T> bool get(T*, uint32_t num_vals_, unsigned stride_=0) const;
  //--------------------------------------------------------------------------

  typedef pfc::pod_variant<pfc::float32_t*, int32_t*, const char*> value_t;
  value_t value;
  pfc::owner_data data;
  uint32_t num_vals;
  uint8_t pinned_owner;
  uint8_t num_data_elems;
  uint8_t data_stride;
  uint8_t data_offset;
};
//----------------------------------------------------------------------------

//============================================================================
#include "vbuf_expr.inl"
#endif
