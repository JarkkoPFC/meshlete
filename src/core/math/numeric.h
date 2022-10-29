//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_NUMERIC_H
#define PFC_CORE_MATH_NUMERIC_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core/core.h"
#include <float.h>
#include <limits.h>
namespace pfc
{

// new
template<typename> struct numeric_type;
//----------------------------------------------------------------------------


//============================================================================
// numeric_type
//============================================================================
template<typename T>
struct numeric_type
{
  // type properties
  enum
  {
    is_float  =false,
    is_int    =false,
    is_signed =false
  };
  //--------------------------------------------------------------------------

  static PFC_INLINE T range_min(); // minimum value of the type
  static PFC_INLINE T range_max(); // maximum value of the type
  static PFC_INLINE T zero();      // zero value
  static PFC_INLINE T float_one(); // representation of floating point value 1.0 (range_max for non-float types)
};
//----------------------------------------------------------------------------

//============================================================================
#include "numeric.inl"
} // namespace pfc
#endif
