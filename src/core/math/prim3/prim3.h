//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_PRIM3_H
#define PFC_CORE_MATH_PRIM3_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core/math/math.h"
#include "core/math/numeric.h"
namespace pfc
{

// new
template<typename> struct point3;
template<typename> struct line3;
template<typename> struct ray3;
template<typename> struct segment3;
template<typename> struct tri3;
template<typename> struct rect3;
template<typename> struct disc3;
template<typename> struct plane3;
template<typename> struct sphere3;
template<typename> struct cylinder3;
template<typename> struct capsule3;
template<typename> struct cone3;
template<typename> struct aabox3;
template<typename> struct oobox3;
template<typename> struct frustum3;
typedef point3<float> point3f;
typedef point3<double> point3d;
typedef line3<float> line3f;
typedef line3<double> line3d;
typedef ray3<float> ray3f;
typedef ray3<double> ray3d;
typedef segment3<float> segment3f;
typedef segment3<double> segment3d;
typedef tri3<float> tri3f;
typedef tri3<double> tri3d;
typedef rect3<float> rect3f;
typedef rect3<double> rect3d;
typedef disc3<float> disc3f;
typedef disc3<double> disc3d;
typedef plane3<float> plane3f;
typedef plane3<double> plane3d;
typedef sphere3<float> sphere3f;
typedef sphere3<double> sphere3d;
typedef cylinder3<float> cylinder3f;
typedef cylinder3<double> cylinder3d;
typedef capsule3<float> capsule3f;
typedef capsule3<double> capsule3d;
typedef cone3<float> cone3f;
typedef cone3<double> cone3d;
typedef aabox3<float> aabox3f;
typedef aabox3<double> aabox3d;
typedef oobox3<float> oobox3f;
typedef oobox3<double> oobox3d;
typedef frustum3<float> frustum3f;
typedef frustum3<double> frustum3d;
// area functions
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const tri3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const rect3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const disc3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const sphere3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const cylinder3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const capsule3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const cone3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const aabox3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const oobox3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const frustum3<T>&);
// volume functions
template<typename T> PFC_INLINE typename math<T>::scalar_t volume(const sphere3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t volume(const cylinder3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t volume(const capsule3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t volume(const cone3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t volume(const aabox3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t volume(const oobox3<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t volume(const frustum3<T>&);
//----------------------------------------------------------------------------


//============================================================================
// point3
//============================================================================
template<typename T>
struct point3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE point3();
  PFC_INLINE point3(const vec3<T> &pos_);
  PFC_INLINE point3(scalar_t x_, scalar_t y_, scalar_t z_);
  PFC_INLINE void set(const vec3<T> &pos_);
  PFC_INLINE void set(scalar_t x_, scalar_t y_, scalar_t z_);
  //--------------------------------------------------------------------------

  static const point3<T> s_zero;
  vec3<T> pos;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, point3<T>, is_type_pod, is_type_pod<vec3<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, point3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// line3
//============================================================================
template<typename T>
struct line3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE line3();
  PFC_INLINE line3(const vec3<T> &pos_, const vec3<T> &dir_);
  PFC_INLINE void set(const vec3<T> &pos_, const vec3<T> &dir_);
  //--------------------------------------------------------------------------

  static const line3<T> s_zero;
  vec3<T> pos;  // point on the line
  vec3<T> dir;  // unit direction of the line
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, line3<T>, is_type_pod, is_type_pod<vec3<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, line3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// ray3
//============================================================================
template<typename T>
struct ray3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE ray3();
  PFC_INLINE ray3(const vec3<T> &pos_, const vec3<T> &dir_);
  PFC_INLINE void set(const vec3<T> &pos_, const vec3<T> &dir_);
  //--------------------------------------------------------------------------

  static const ray3<T> s_zero;
  vec3<T> pos;  // starting point of the ray
  vec3<T> dir;  // unit direction of the ray
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, ray3<T>, is_type_pod, is_type_pod<vec3<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, ray3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// segment3
//============================================================================
template<typename T>
struct segment3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE segment3();
  PFC_INLINE segment3(const vec3<T> &pos_, const vec3<T> &dir_, scalar_t hlen_);
  PFC_INLINE void set(const vec3<T> &pos_, const vec3<T> &dir_, scalar_t hlen_);
  //--------------------------------------------------------------------------

  static const segment3<T> s_zero;
  vec3<T> pos;   // center position of the segment
  vec3<T> dir;   // unit direction of the segment
  scalar_t hlen; // half-length of the segment
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, segment3<T>, is_type_pod, is_type_pod<vec3<T> >::res && is_type_pod<math<T>::scalar_t>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, segment3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res && is_type_pod_stream<math<T>::scalar_t>::res);
//----------------------------------------------------------------------------


//============================================================================
// tri3
//============================================================================
template<typename T>
struct tri3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE tri3();
  PFC_INLINE tri3(const vec3<T>&, const vec3<T>&, const vec3<T>&);
  PFC_INLINE void set(const vec3<T>&, const vec3<T>&, const vec3<T>&);
  //--------------------------------------------------------------------------

  static const tri3<T> s_zero;
  vec3<T> a, b, c;  // 3 points of the triangle. normal = (b-a) x (c-a) = clock-wise
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, tri3<T>, is_type_pod, is_type_pod<vec3<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, tri3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// rect3
//============================================================================
template<typename T>
struct rect3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE rect3();
  PFC_INLINE rect3(const vec3<T> &pos_, const quat<T> &rot_, const vec2<T> &hsize_);
  PFC_INLINE void set(const vec3<T> &pos_, const quat<T> &rot_, const vec2<T> &hsize_);
  //--------------------------------------------------------------------------

  static const rect3<T> s_zero;
  vec3<T> pos;    // center position of the rect
  quat<T> rot;    // rect orientation
  vec2<T> hsize;  // half of the length of the rect along each axis
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, rect3<T>, is_type_pod, is_type_pod<vec3<T> >::res && is_type_pod<quat<T> >::res && is_type_pod<vec2<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, rect3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res && is_type_pod_stream<quat<T> >::res && is_type_pod_stream<vec2<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// disc3
//============================================================================
template<typename T>
struct disc3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE disc3();
  PFC_INLINE disc3(const vec3<T> &pos_, const vec3<T> &normal_, scalar_t rad_);
  PFC_INLINE void set(const vec3<T> &pos_, const vec3<T> &normal_, scalar_t rad_);
  //--------------------------------------------------------------------------

  static const disc3<T> s_zero;
  vec3<T> pos;
  vec3<T> normal;
  scalar_t rad;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, disc3<T>, is_type_pod, is_type_pod<vec3<T> >::res && is_type_pod<math<T>::scalar_t>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, disc3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res && is_type_pod_stream<math<T>::scalar_t>::res);
//----------------------------------------------------------------------------


//============================================================================
// plane3
//============================================================================
template<typename T>
struct plane3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE plane3();
  PFC_INLINE plane3(const vec3<T> &normal_, scalar_t d_);
  PFC_INLINE void set(const vec3<T> &normal_, scalar_t d_);
  //--------------------------------------------------------------------------

  static const plane3<T> s_zero;
  vec3<T> normal;  // unit normal of the plane
  scalar_t d;      // plane distance from origo [0, 0, 0]
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, plane3<T>, is_type_pod, is_type_pod<vec3<T> >::res && is_type_pod<math<T>::scalar_t>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, plane3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res && is_type_pod_stream<math<T>::scalar_t>::res);
//----------------------------------------------------------------------------


//============================================================================
// sphere3
//============================================================================
template<typename T>
struct sphere3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE sphere3();
  PFC_INLINE sphere3(const vec3<T> &pos_, scalar_t rad_);
  PFC_INLINE void set(const vec3<T> &pos_, scalar_t rad_);
  //--------------------------------------------------------------------------

  static const sphere3<T> s_zero;
  vec3<T> pos;   // center position of the sphere
  scalar_t rad;  // sphere radius
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, sphere3<T>, is_type_pod, is_type_pod<vec3<T> >::res && is_type_pod<math<T>::scalar_t>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, sphere3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res && is_type_pod_stream<math<T>::scalar_t>::res);
//----------------------------------------------------------------------------


//============================================================================
// cylinder3
//============================================================================
template<typename T>
struct cylinder3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE cylinder3();
  PFC_INLINE cylinder3(const vec3<T> &pos_, const vec3<T> &dir_, scalar_t hlen_, scalar_t rad_);
  PFC_INLINE void set(const vec3<T> &pos_, const vec3<T> &dir_, scalar_t hlen_, scalar_t rad_);
  //--------------------------------------------------------------------------

  static const cylinder3<T> s_zero;
  vec3<T> pos;    // center position of the cylinder
  vec3<T> dir;    // cylinder unit direction
  scalar_t hlen;  // half of the length of the cylinder
  scalar_t rad;   // cylinder radius
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, cylinder3<T>, is_type_pod, is_type_pod<vec3<T> >::res && is_type_pod<math<T>::scalar_t>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, cylinder3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res && is_type_pod_stream<math<T>::scalar_t>::res);
//----------------------------------------------------------------------------


//============================================================================
// capsule3
//============================================================================
template<typename T>
struct capsule3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE capsule3();
  PFC_INLINE capsule3(const vec3<T> &pos_, const vec3<T> &dir_, scalar_t hlen_, scalar_t rad_);
  PFC_INLINE void set(const vec3<T> &pos_, const vec3<T> &dir_, scalar_t hlen_, scalar_t rad_);
  //--------------------------------------------------------------------------

  static const capsule3<T> s_zero;
  vec3<T> pos;    // center position of the capsule
  vec3<T> dir;    // capsule unit direction
  scalar_t hlen;  // half of the length of the capsule
  scalar_t rad;   // capsule radius
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, capsule3<T>, is_type_pod, is_type_pod<vec3<T> >::res && is_type_pod<math<T>::scalar_t>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, capsule3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res && is_type_pod_stream<math<T>::scalar_t>::res);
//----------------------------------------------------------------------------


//============================================================================
// cone3
//============================================================================
template<typename T>
struct cone3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE cone3();
  PFC_INLINE cone3(const vec3<T> &apex_pos_, const vec3<T> &dir_, scalar_t height_, scalar_t cos_apex_hangle_);
  PFC_INLINE void set(const vec3<T> &apex_pos_, const vec3<T> &dir_, scalar_t height_, scalar_t cos_apex_hangle_);
  //--------------------------------------------------------------------------

  static const cone3<T> s_zero;
  vec3<T> apex_pos;         // apex position
  vec3<T> dir;              // cone unit direction
  scalar_t height;          // cone height
  scalar_t cos_apex_hangle; // cosine of half-angle of the apex
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, cone3<T>, is_type_pod, is_type_pod<vec3<T> >::res && is_type_pod<math<T>::scalar_t>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, cone3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res && is_type_pod_stream<math<T>::scalar_t>::res);
//----------------------------------------------------------------------------


//============================================================================
// aabox3
//============================================================================
template<typename T>
struct aabox3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE aabox3();
  PFC_INLINE aabox3(const vec3<T> &pos_, const vec3<T> &hsize_);
  PFC_INLINE void set(const vec3<T> &pos_, const vec3<T> &hsize_);
  //--------------------------------------------------------------------------

  static const aabox3<T> s_zero;
  vec3<T> pos;    // center position of the box
  vec3<T> hsize;  // half of the length of the box along each axis
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, aabox3<T>, is_type_pod, is_type_pod<vec3<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, aabox3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// oobox3
//============================================================================
template<typename T>
struct oobox3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE oobox3();
  PFC_INLINE oobox3(const vec3<T> &pos_, const vec3<T> &hsize_, const quat<T> &rot_);
  PFC_INLINE void set(const vec3<T> &pos_, const vec3<T> &hsize_, const quat<T> &rot_);
  //--------------------------------------------------------------------------

  static const oobox3<T> s_zero;
  vec3<T> pos;    // center position of the box
  vec3<T> hsize;  // half of the length of the box along each axis
  quat<T> rot;    // box orientation
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, oobox3<T>, is_type_pod, is_type_pod<vec3<T> >::res && is_type_pod<quat<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, oobox3<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res && is_type_pod_stream<quat<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// frustum3
//============================================================================
template<typename T>
struct frustum3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE frustum3();
  PFC_INLINE frustum3(const mat44<T> &p2l_);
  PFC_INLINE void set(const mat44<T> &p2l_);
  //--------------------------------------------------------------------------

  mat44<T> proj_to_local;  // projection -> local space transformation
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, frustum3<T>, is_type_pod, is_type_pod<mat44<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, frustum3<T>, is_type_pod_stream, is_type_pod_stream<mat44<T> >::res);
//----------------------------------------------------------------------------

//============================================================================
#include "prim3.inl"
} // namespace pfc
#endif
