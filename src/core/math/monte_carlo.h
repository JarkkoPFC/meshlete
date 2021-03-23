//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_MONTE_CARLO_H
#define PFC_CORE_MATH_MONTE_CARLO_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
//#include "core/math/prim3/prim3_isect.h"
#include "core/math/bit_math.h"
#include "core/math/math.h"
namespace pfc
{

// new
// quasirandom sequences
template<typename T> PFC_INLINE vec2<T> hammersley(unsigned idx_, unsigned num_samples_);
// cone sampling
template<typename T> PFC_INLINE T cone_solid_angle(T cos_half_apex_angle_);
template<typename T> PFC_INLINE vec3<T> cone_uniform_vector(const vec2<T> &xi_, typename math<T>::scalar_t cos_half_apex_angle_);
template<typename T> PFC_INLINE vec3<T> cone_strata_vector(unsigned sample_idx_, unsigned num_samples_, typename math<T>::scalar_t cos_half_apex_angle_);
PFC_INLINE ufloat_t cone_strata_half_angle(unsigned num_samples_, ufloat_t cos_half_apex_angle_);
template<class PrimitiveType> typename PrimitiveType::scalar_t mc_solid_angle_stratified(const PrimitiveType&, const vec3<typename PrimitiveType::type_t> &pos_, const vec3<typename PrimitiveType::type_t> &dir_, typename PrimitiveType::scalar_t cos_half_apex_angle_, unsigned num_samples_);
//----------------------------------------------------------------------------

//============================================================================
#include "monte_carlo.inl"
} // namespace pfc
#endif
