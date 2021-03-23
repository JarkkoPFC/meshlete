//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_FAST_MATH_H
#define PFC_CORE_MATH_FAST_MATH_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core/core.h"
namespace pfc
{

// new
PFC_INLINE float32_t fast_rsqrt(float32_t);
PFC_INLINE float64_t fast_rsqrt(float64_t);
PFC_INLINE float32_t fast_sqrt(float32_t);
PFC_INLINE float64_t fast_sqrt(float64_t);
PFC_INLINE float32_t fast_rcp(float32_t);
PFC_INLINE float64_t fast_rcp(float64_t);
//----------------------------------------------------------------------------

//============================================================================
#include "fast_math.inl"
} // namespace pfc
#endif
