//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_PRIM3_ISECT_H
#define PFC_CORE_MATH_PRIM3_ISECT_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core/math/prim3/prim3.h"
namespace pfc
{

// new
template<typename T> bool isect(const point3<T>&, const plane3<T>&);
template<typename T> bool isect(const point3<T>&, const sphere3<T>&);
template<typename T> bool isect(const point3<T>&, const cylinder3<T>&);
template<typename T> bool isect(const point3<T>&, const capsule3<T>&);
template<typename T> bool isect(const point3<T>&, const cone3<T>&);
template<typename T> bool isect(const point3<T>&, const aabox3<T>&);
template<typename T> bool isect(const point3<T>&, const oobox3<T>&);
template<typename T> bool isect(const point3<T>&, const frustum3<T>&);
template<typename T> bool isect(const line3<T>&, const tri3<T>&);
template<typename T> bool isect(const line3<T>&, const tri3<T>&, typename math<T>::scalar_t&);
template<typename T> bool isect(const line3<T>&, const rect3<T>&);
template<typename T> bool isect(const line3<T>&, const rect3<T>&, typename math<T>::scalar_t&);
template<typename T> bool isect(const line3<T>&, const rect3<T>&, typename math<T>::scalar_t &t_, typename math<T>::scalar_t &u_, typename math<T>::scalar_t &v_);
template<typename T> bool isect(const line3<T>&, const disc3<T>&);
template<typename T> bool isect(const line3<T>&, const disc3<T>&, typename math<T>::scalar_t&);
template<typename T> bool isect(const line3<T>&, const plane3<T>&, typename math<T>::scalar_t&);
template<typename T> bool isect(const line3<T>&, const sphere3<T>&);
template<typename T> bool isect(const line3<T>&, const sphere3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const line3<T>&, const cylinder3<T>&);
template<typename T> bool isect(const line3<T>&, const cylinder3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const line3<T>&, const capsule3<T>&);
template<typename T> bool isect(const line3<T>&, const capsule3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const line3<T>&, const cone3<T>&);
template<typename T> bool isect(const line3<T>&, const cone3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const line3<T>&, const aabox3<T>&);
template<typename T> bool isect(const line3<T>&, const aabox3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const line3<T>&, const oobox3<T>&);
template<typename T> bool isect(const line3<T>&, const oobox3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const line3<T>&, const frustum3<T>&);
template<typename T> bool isect(const line3<T>&, const frustum3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const ray3<T>&, const tri3<T>&);
template<typename T> bool isect(const ray3<T>&, const tri3<T>&, typename math<T>::scalar_t&);
template<typename T> bool isect(const ray3<T>&, const rect3<T>&);
template<typename T> bool isect(const ray3<T>&, const rect3<T>&, typename math<T>::scalar_t&);
template<typename T> bool isect(const ray3<T>&, const rect3<T>&, typename math<T>::scalar_t &t_, typename math<T>::scalar_t &u_, typename math<T>::scalar_t &v_);
template<typename T> bool isect(const ray3<T>&, const disc3<T>&);
template<typename T> bool isect(const ray3<T>&, const disc3<T>&, typename math<T>::scalar_t&);
template<typename T> bool isect(const ray3<T>&, const plane3<T>&);
template<typename T> bool isect(const ray3<T>&, const plane3<T>&, typename math<T>::scalar_t&);
template<typename T> bool isect(const ray3<T>&, const sphere3<T>&);
template<typename T> bool isect(const ray3<T>&, const sphere3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const ray3<T>&, const cylinder3<T>&);
template<typename T> bool isect(const ray3<T>&, const cylinder3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const ray3<T>&, const capsule3<T>&);
template<typename T> bool isect(const ray3<T>&, const capsule3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const ray3<T>&, const cone3<T>&);
template<typename T> bool isect(const ray3<T>&, const cone3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const ray3<T>&, const aabox3<T>&);
template<typename T> bool isect(const ray3<T>&, const aabox3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const ray3<T>&, const oobox3<T>&);
template<typename T> bool isect(const ray3<T>&, const oobox3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const ray3<T>&, const frustum3<T>&);
template<typename T> bool isect(const ray3<T>&, const frustum3<T>&, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_);
template<typename T> bool isect(const segment3<T>&, const tri3<T>&);
template<typename T> bool isect(const segment3<T>&, const rect3<T>&);
template<typename T> bool isect(const segment3<T>&, const disc3<T>&);
template<typename T> bool isect(const segment3<T>&, const plane3<T>&);
template<typename T> bool isect(const segment3<T>&, const sphere3<T>&);
template<typename T> bool isect(const segment3<T>&, const cylinder3<T>&);
template<typename T> bool isect(const segment3<T>&, const capsule3<T>&);
template<typename T> bool isect(const segment3<T>&, const cone3<T>&);
template<typename T> bool isect(const segment3<T>&, const aabox3<T>&);
template<typename T> bool isect(const segment3<T>&, const oobox3<T>&);
template<typename T> bool isect(const segment3<T>&, const frustum3<T>&);
template<typename T> bool isect(const tri3<T>&, const tri3<T>&);
template<typename T> bool isect(const tri3<T>&, const rect3<T>&);
template<typename T> bool isect(const tri3<T>&, const disc3<T>&);
template<typename T> bool isect(const tri3<T>&, const plane3<T>&);
template<typename T> bool isect(const tri3<T>&, const sphere3<T>&);
template<typename T> bool isect(const tri3<T>&, const cylinder3<T>&);
template<typename T> bool isect(const tri3<T>&, const capsule3<T>&);
template<typename T> bool isect(const tri3<T>&, const cone3<T>&);
template<typename T> bool isect(const tri3<T>&, const aabox3<T>&);
template<typename T> bool isect(const tri3<T>&, const oobox3<T>&);
template<typename T> bool isect(const tri3<T>&, const frustum3<T>&);
template<typename T> bool isect(const rect3<T>&, const rect3<T>&);
template<typename T> bool isect(const rect3<T>&, const disc3<T>&);
template<typename T> bool isect(const rect3<T>&, const plane3<T>&);
template<typename T> bool isect(const rect3<T>&, const sphere3<T>&);
template<typename T> bool isect(const rect3<T>&, const cylinder3<T>&);
template<typename T> bool isect(const rect3<T>&, const capsule3<T>&);
template<typename T> bool isect(const rect3<T>&, const cone3<T>&);
template<typename T> bool isect(const rect3<T>&, const aabox3<T>&);
template<typename T> bool isect(const rect3<T>&, const oobox3<T>&);
template<typename T> bool isect(const rect3<T>&, const frustum3<T>&);
template<typename T> bool isect(const disc3<T>&, const disc3<T>&);
template<typename T> bool isect(const disc3<T>&, const plane3<T>&);
template<typename T> bool isect(const disc3<T>&, const sphere3<T>&);
template<typename T> bool isect(const disc3<T>&, const cylinder3<T>&);
template<typename T> bool isect(const disc3<T>&, const capsule3<T>&);
template<typename T> bool isect(const disc3<T>&, const cone3<T>&);
template<typename T> bool isect(const disc3<T>&, const aabox3<T>&);
template<typename T> bool isect(const disc3<T>&, const oobox3<T>&);
template<typename T> bool isect(const disc3<T>&, const frustum3<T>&);
template<typename T> bool isect(const plane3<T>&, const sphere3<T>&);
template<typename T> bool isect(const plane3<T>&, const cylinder3<T>&);
template<typename T> bool isect(const plane3<T>&, const capsule3<T>&);
template<typename T> bool isect(const plane3<T>&, const cone3<T>&);
template<typename T> bool isect(const plane3<T>&, const aabox3<T>&);
template<typename T> bool isect(const plane3<T>&, const oobox3<T>&);
template<typename T> bool isect(const plane3<T>&, const frustum3<T>&);
template<typename T> bool isect(const sphere3<T>&, const sphere3<T>&);
template<typename T> bool isect(const sphere3<T>&, const cylinder3<T>&);
template<typename T> bool isect(const sphere3<T>&, const capsule3<T>&);
template<typename T> bool isect(const sphere3<T>&, const cone3<T>&);
template<typename T> bool isect(const sphere3<T>&, const aabox3<T>&);
template<typename T> bool isect(const sphere3<T>&, const oobox3<T>&);
template<typename T> bool isect(const sphere3<T>&, const frustum3<T>&);
template<typename T> bool isect(const cylinder3<T>&, const cylinder3<T>&);
template<typename T> bool isect(const cylinder3<T>&, const capsule3<T>&);
template<typename T> bool isect(const cylinder3<T>&, const cone3<T>&);
template<typename T> bool isect(const cylinder3<T>&, const aabox3<T>&);
template<typename T> bool isect(const cylinder3<T>&, const oobox3<T>&);
template<typename T> bool isect(const cylinder3<T>&, const frustum3<T>&);
template<typename T> bool isect(const capsule3<T>&, const capsule3<T>&);
template<typename T> bool isect(const capsule3<T>&, const cone3<T>&);
template<typename T> bool isect(const capsule3<T>&, const aabox3<T>&);
template<typename T> bool isect(const capsule3<T>&, const oobox3<T>&);
template<typename T> bool isect(const capsule3<T>&, const frustum3<T>&);
template<typename T> bool isect(const cone3<T>&, const cone3<T>&);
template<typename T> bool isect(const cone3<T>&, const aabox3<T>&);
template<typename T> bool isect(const cone3<T>&, const oobox3<T>&);
template<typename T> bool isect(const cone3<T>&, const frustum3<T>&);
template<typename T> bool isect(const aabox3<T>&, const aabox3<T>&);
template<typename T> bool isect(const aabox3<T>&, const oobox3<T>&);
template<typename T> bool isect(const aabox3<T>&, const frustum3<T>&);
template<typename T> bool isect(const oobox3<T>&, const oobox3<T>&);
template<typename T> bool isect(const oobox3<T>&, const frustum3<T>&);
template<typename T> bool isect(const frustum3<T>&, const frustum3<T>&);
// intersection type routines: isect_type(a, b) = how primitive a relates to b
enum e_isect_type
{
  isect_type_none =0x00,
  isect_type_in   =0x01,
  isect_type_out  =0x02,
  isect_type_both =0x03
};
template<typename T> e_isect_type isect_type(const tri3<T>&, const plane3<T>&);
template<typename T> e_isect_type isect_type(const tri3<T>&, const sphere3<T>&);
template<typename T> e_isect_type isect_type(const tri3<T>&, const cylinder3<T>&);
template<typename T> e_isect_type isect_type(const tri3<T>&, const capsule3<T>&);
template<typename T> e_isect_type isect_type(const tri3<T>&, const cone3<T>&);
template<typename T> e_isect_type isect_type(const tri3<T>&, const aabox3<T>&);
template<typename T> e_isect_type isect_type(const tri3<T>&, const oobox3<T>&);
template<typename T> e_isect_type isect_type(const tri3<T>&, const frustum3<T>&);
template<typename T> e_isect_type isect_type(const rect3<T>&, const plane3<T>&);
template<typename T> e_isect_type isect_type(const rect3<T>&, const sphere3<T>&);
template<typename T> e_isect_type isect_type(const rect3<T>&, const cylinder3<T>&);
template<typename T> e_isect_type isect_type(const rect3<T>&, const capsule3<T>&);
template<typename T> e_isect_type isect_type(const rect3<T>&, const cone3<T>&);
template<typename T> e_isect_type isect_type(const rect3<T>&, const aabox3<T>&);
template<typename T> e_isect_type isect_type(const rect3<T>&, const oobox3<T>&);
template<typename T> e_isect_type isect_type(const rect3<T>&, const frustum3<T>&);
template<typename T> e_isect_type isect_type(const disc3<T>&, const plane3<T>&);
template<typename T> e_isect_type isect_type(const disc3<T>&, const sphere3<T>&);
template<typename T> e_isect_type isect_type(const disc3<T>&, const cylinder3<T>&);
template<typename T> e_isect_type isect_type(const disc3<T>&, const capsule3<T>&);
template<typename T> e_isect_type isect_type(const disc3<T>&, const cone3<T>&);
template<typename T> e_isect_type isect_type(const disc3<T>&, const aabox3<T>&);
template<typename T> e_isect_type isect_type(const disc3<T>&, const oobox3<T>&);
template<typename T> e_isect_type isect_type(const disc3<T>&, const frustum3<T>&);
template<typename T> e_isect_type isect_type(const sphere3<T>&, const plane3<T>&);
template<typename T> e_isect_type isect_type(const sphere3<T>&, const sphere3<T>&);
template<typename T> e_isect_type isect_type(const sphere3<T>&, const cylinder3<T>&);
template<typename T> e_isect_type isect_type(const sphere3<T>&, const capsule3<T>&);
template<typename T> e_isect_type isect_type(const sphere3<T>&, const cone3<T>&);
template<typename T> e_isect_type isect_type(const sphere3<T>&, const aabox3<T>&);
template<typename T> e_isect_type isect_type(const sphere3<T>&, const oobox3<T>&);
template<typename T> e_isect_type isect_type(const sphere3<T>&, const frustum3<T>&);
template<typename T> e_isect_type isect_type(const cylinder3<T>&, const plane3<T>&);
template<typename T> e_isect_type isect_type(const cylinder3<T>&, const sphere3<T>&);
template<typename T> e_isect_type isect_type(const cylinder3<T>&, const cylinder3<T>&);
template<typename T> e_isect_type isect_type(const cylinder3<T>&, const capsule3<T>&);
template<typename T> e_isect_type isect_type(const cylinder3<T>&, const cone3<T>&);
template<typename T> e_isect_type isect_type(const cylinder3<T>&, const aabox3<T>&);
template<typename T> e_isect_type isect_type(const cylinder3<T>&, const oobox3<T>&);
template<typename T> e_isect_type isect_type(const cylinder3<T>&, const frustum3<T>&);
template<typename T> e_isect_type isect_type(const capsule3<T>&, const plane3<T>&);
template<typename T> e_isect_type isect_type(const capsule3<T>&, const sphere3<T>&);
template<typename T> e_isect_type isect_type(const capsule3<T>&, const cylinder3<T>&);
template<typename T> e_isect_type isect_type(const capsule3<T>&, const capsule3<T>&);
template<typename T> e_isect_type isect_type(const capsule3<T>&, const cone3<T>&);
template<typename T> e_isect_type isect_type(const capsule3<T>&, const aabox3<T>&);
template<typename T> e_isect_type isect_type(const capsule3<T>&, const oobox3<T>&);
template<typename T> e_isect_type isect_type(const capsule3<T>&, const frustum3<T>&);
template<typename T> e_isect_type isect_type(const cone3<T>&, const plane3<T>&);
template<typename T> e_isect_type isect_type(const cone3<T>&, const sphere3<T>&);
template<typename T> e_isect_type isect_type(const cone3<T>&, const cylinder3<T>&);
template<typename T> e_isect_type isect_type(const cone3<T>&, const capsule3<T>&);
template<typename T> e_isect_type isect_type(const cone3<T>&, const cone3<T>&);
template<typename T> e_isect_type isect_type(const cone3<T>&, const aabox3<T>&);
template<typename T> e_isect_type isect_type(const cone3<T>&, const oobox3<T>&);
template<typename T> e_isect_type isect_type(const cone3<T>&, const frustum3<T>&);
template<typename T> e_isect_type isect_type(const aabox3<T>&, const plane3<T>&);
template<typename T> e_isect_type isect_type(const aabox3<T>&, const sphere3<T>&);
template<typename T> e_isect_type isect_type(const aabox3<T>&, const cylinder3<T>&);
template<typename T> e_isect_type isect_type(const aabox3<T>&, const capsule3<T>&);
template<typename T> e_isect_type isect_type(const aabox3<T>&, const cone3<T>&);
template<typename T> e_isect_type isect_type(const aabox3<T>&, const aabox3<T>&);
template<typename T> e_isect_type isect_type(const aabox3<T>&, const oobox3<T>&);
template<typename T> e_isect_type isect_type(const aabox3<T>&, const frustum3<T>&);
template<typename T> e_isect_type isect_type(const oobox3<T>&, const plane3<T>&);
template<typename T> e_isect_type isect_type(const oobox3<T>&, const sphere3<T>&);
template<typename T> e_isect_type isect_type(const oobox3<T>&, const cylinder3<T>&);
template<typename T> e_isect_type isect_type(const oobox3<T>&, const capsule3<T>&);
template<typename T> e_isect_type isect_type(const oobox3<T>&, const cone3<T>&);
template<typename T> e_isect_type isect_type(const oobox3<T>&, const aabox3<T>&);
template<typename T> e_isect_type isect_type(const oobox3<T>&, const oobox3<T>&);
template<typename T> e_isect_type isect_type(const oobox3<T>&, const frustum3<T>&);
template<typename T> e_isect_type isect_type(const frustum3<T>&, const plane3<T>&);
template<typename T> e_isect_type isect_type(const frustum3<T>&, const sphere3<T>&);
template<typename T> e_isect_type isect_type(const frustum3<T>&, const cylinder3<T>&);
template<typename T> e_isect_type isect_type(const frustum3<T>&, const capsule3<T>&);
template<typename T> e_isect_type isect_type(const frustum3<T>&, const cone3<T>&);
template<typename T> e_isect_type isect_type(const frustum3<T>&, const aabox3<T>&);
template<typename T> e_isect_type isect_type(const frustum3<T>&, const oobox3<T>&);
template<typename T> e_isect_type isect_type(const frustum3<T>&, const frustum3<T>&);
//----------------------------------------------------------------------------

//============================================================================
#include "prim3_isect.inl"
} // namespace pfc
#endif
