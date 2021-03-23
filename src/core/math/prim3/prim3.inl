//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================


//============================================================================
// point3
//============================================================================
template<typename T> const point3<T> point3<T>::s_zero(vec3<T>::s_zero);
//----------------------------------------------------------------------------

template<typename T>
point3<T>::point3()
{
}
//----

template<typename T>
point3<T>::point3(const vec3<T> &pos_)
  :pos(pos_)
{
}
//----

template<typename T>
point3<T>::point3(scalar_t x_, scalar_t y_, scalar_t z_)
  :pos(x_, y_, z_)
{
}
//----

template<typename T>
void point3<T>::set(const vec3<T> &pos_)
{
  pos=pos_;
}
//----

template<typename T>
void point3<T>::set(scalar_t x_, scalar_t y_, scalar_t z_)
{
  pos.set(x_, y_, z_);
}
//----------------------------------------------------------------------------


//============================================================================
// line3
//============================================================================
template<typename T> const line3<T> line3<T>::s_zero(vec3<T>::s_zero, vec3<T>::s_zero);
//----------------------------------------------------------------------------

template<typename T>
line3<T>::line3()
{
}
//----

template<typename T>
line3<T>::line3(const vec3<T> &pos_, const vec3<T> &dir_)
  :pos(pos_)
  ,dir(dir_)
{
}
//----

template<typename T>
void line3<T>::set(const vec3<T> &pos_, const vec3<T> &dir_)
{
  pos=pos_;
  dir=dir_;
}
//----------------------------------------------------------------------------


//============================================================================
// ray3
//============================================================================
template<typename T> const ray3<T> ray3<T>::s_zero(vec3<T>::s_zero, vec3<T>::s_zero);
//----------------------------------------------------------------------------

template<typename T>
ray3<T>::ray3()
{
}
//----

template<typename T>
ray3<T>::ray3(const vec3<T> &pos_, const vec3<T> &dir_)
  :pos(pos_)
  ,dir(dir_)
{
}
//----

template<typename T>
void ray3<T>::set(const vec3<T> &pos_, const vec3<T> &dir_)
{
  pos=pos_;
  dir=dir_;
}
//----------------------------------------------------------------------------


//============================================================================
// segment3
//============================================================================
template<typename T> const segment3<T> segment3<T>::s_zero(vec3<T>::s_zero, vec3<T>::s_zero);
//----------------------------------------------------------------------------

template<typename T>
segment3<T>::segment3()
{
}
//----

template<typename T>
segment3<T>::segment3(const vec3<T> &pos_, const vec3<T> &dir_, scalar_t hlen_)
  :pos(pos_)
  ,dir(dir_)
  ,hlen(hlen_)
{
}
//----

template<typename T>
void segment3<T>::set(const vec3<T> &pos_, const vec3<T> &dir_, scalar_t hlen_)
{
  pos=pos_;
  dir=dir_;
  hlen=hlen_;
}
//----------------------------------------------------------------------------


//============================================================================
// tri3
//============================================================================
template<typename T> const tri3<T> tri3<T>::s_zero(vec3<T>::s_zero, vec3<T>::s_zero, vec3<T>::s_zero);
//----------------------------------------------------------------------------

template<typename T>
tri3<T>::tri3()
{
}
//----

template<typename T>
tri3<T>::tri3(const vec3<T> &a_, const vec3<T> &b_, const vec3<T> &c_)
  :a(a_)
  ,b(b_)
  ,c(c_)
{
}
//----

template<typename T>
void tri3<T>::set(const vec3<T> &a_, const vec3<T> &b_, const vec3<T> &c_)
{
  a=a_;
  b=b_;
  c=c_;
}
//----------------------------------------------------------------------------


//============================================================================
// rect3
//============================================================================
template<typename T> const rect3<T> rect3<T>::s_zero(vec3<T>::s_zero, quat<T>::s_zero, vec2<T>::s_zero);
//----------------------------------------------------------------------------

template<typename T>
rect3<T>::rect3()
{
}
//----

template<typename T>
rect3<T>::rect3(const vec3<T> &pos_, const quat<T> &rot_, const vec2<T> &hsize_)
  :pos(pos_)
  ,rot(rot_)
  ,hsize(hsize_)
{
}
//----

template<typename T>
void rect3<T>::set(const vec3<T> &pos_, const quat<T> &rot_, const vec2<T> &hsize_)
{
  pos=pos_;
  rot=rot_;
  hsize=hsize_;
}
//----------------------------------------------------------------------------


//============================================================================
// disc3
//============================================================================
template<typename T> const disc3<T> disc3<T>::s_zero(vec3<T>::s_zero, vec3<T>::s_zero, 0);
//----------------------------------------------------------------------------

template<typename T>
disc3<T>::disc3()
{
}
//----

template<typename T>
disc3<T>::disc3(const vec3<T> &pos_, const vec3<T> &normal_, scalar_t rad_)
  :pos(pos_)
  ,normal(normal_)
  ,rad(rad_)
{
}
//----

template<typename T>
void disc3<T>::set(const vec3<T> &pos_, const vec3<T> &normal_, scalar_t rad_)
{
  pos=pos_;
  normal=normal_;
  rad=rad_;
}
//----------------------------------------------------------------------------


//============================================================================
// plane3
//============================================================================
template<typename T> const plane3<T> plane3<T>::s_zero(vec3<T>::s_zero, 0);
//----------------------------------------------------------------------------

template<typename T>
plane3<T>::plane3()
{
}
//----

template<typename T>
plane3<T>::plane3(const vec3<T> &normal_, scalar_t d_)
  :normal(normal_)
  ,d(d_)
{
}
//----

template<typename T>
void plane3<T>::set(const vec3<T> &normal_, scalar_t d_)
{
  normal=normal_;
  d=d_;
}
//----------------------------------------------------------------------------


//============================================================================
// sphere3
//============================================================================
template<typename T> const sphere3<T> sphere3<T>::s_zero(vec3<T>::s_zero, 0);
//----------------------------------------------------------------------------

template<typename T>
sphere3<T>::sphere3()
{
}
//----

template<typename T>
sphere3<T>::sphere3(const vec3<T> &pos_, scalar_t rad_)
  :pos(pos_)
  ,rad(rad_)
{
}
//----

template<typename T>
void sphere3<T>::set(const vec3<T> &pos_, scalar_t rad_)
{
  pos=pos_;
  rad=rad_;
}
//----------------------------------------------------------------------------


//============================================================================
// cylinder3
//============================================================================
template<typename T> const cylinder3<T> cylinder3<T>::s_zero(vec3<T>::s_zero, vec3<T>(0, 0, 1), 0, 0);
//----------------------------------------------------------------------------

template<typename T>
cylinder3<T>::cylinder3()
{
}
//----

template<typename T>
cylinder3<T>::cylinder3(const vec3<T> &pos_, const vec3<T> &dir_, scalar_t hlen_, scalar_t rad_)
  :pos(pos_)
  ,dir(dir_)
  ,hlen(hlen_)
  ,rad(rad_)
{
}
//----

template<typename T>
void cylinder3<T>::set(const vec3<T> &pos_, const vec3<T> &dir_, scalar_t hlen_, scalar_t rad_)
{
  pos=pos_;
  dir=dir_;
  hlen=hlen_;
  rad=rad_;
}
//----------------------------------------------------------------------------


//============================================================================
// capsule3
//============================================================================
template<typename T> const capsule3<T> capsule3<T>::s_zero(vec3<T>::s_zero, vec3<T>(0, 0, 1), 0, 0);
//----------------------------------------------------------------------------

template<typename T>
capsule3<T>::capsule3()
{
}
//----

template<typename T>
capsule3<T>::capsule3(const vec3<T> &pos_, const vec3<T> &dir_, scalar_t hlen_, scalar_t rad_)
  :pos(pos_)
  ,dir(dir_)
  ,hlen(hlen_)
  ,rad(rad_)
{
}
//----

template<typename T>
void capsule3<T>::set(const vec3<T> &pos_, const vec3<T> &dir_, scalar_t hlen_, scalar_t rad_)
{
  pos=pos_;
  dir=dir_;
  hlen=hlen_;
  rad=rad_;
}
//----------------------------------------------------------------------------


//============================================================================
// cone3
//============================================================================
template<typename T> const cone3<T> cone3<T>::s_zero(vec3<T>::s_zero, vec3<T>(0, 0, 1), 0, 1);
//----------------------------------------------------------------------------

template<typename T>
cone3<T>::cone3()
{
}
//----

template<typename T>
cone3<T>::cone3(const vec3<T> &apex_pos_, const vec3<T> &dir_, scalar_t height_, scalar_t cos_apex_hangle_)
  :apex_pos(apex_pos_)
  ,dir(dir_)
  ,height(height_)
  ,cos_apex_hangle(cos_apex_hangle_)
{
}
//----

template<typename T>
void cone3<T>::set(const vec3<T> &apex_pos_, const vec3<T> &dir_, scalar_t height_, scalar_t cos_apex_hangle_)
{
  apex_pos=apex_pos_;
  dir=dir_;
  height=height_;
  cos_apex_hangle=cos_apex_hangle_;
}
//----------------------------------------------------------------------------


//============================================================================
// aabox3
//============================================================================
template<typename T> const aabox3<T> aabox3<T>::s_zero(vec3<T>::s_zero, vec3<T>::s_zero);
//----------------------------------------------------------------------------

template<typename T>
aabox3<T>::aabox3()
{
}
//----

template<typename T>
aabox3<T>::aabox3(const vec3<T> &pos_, const vec3<T> &hsize_)
  :pos(pos_)
  ,hsize(hsize_)
{
}
//----

template<typename T>
void aabox3<T>::set(const vec3<T> &pos_, const vec3<T> &hsize_)
{
  pos=pos_;
  hsize=hsize_;
}
//----------------------------------------------------------------------------


//============================================================================
// oobox3
//============================================================================
template<typename T> const oobox3<T> oobox3<T>::s_zero(vec3<T>::s_zero, vec3<T>::s_zero, quat<T>::s_identity);
//----------------------------------------------------------------------------

template<typename T>
oobox3<T>::oobox3()
{
}
//----

template<typename T>
oobox3<T>::oobox3(const vec3<T> &pos_, const vec3<T> &hsize_, const quat<T> &rot_)
  :pos(pos_)
  ,hsize(hsize_)
  ,rot(rot_)
{
}
//----

template<typename T>
void oobox3<T>::set(const vec3<T> &pos_, const vec3<T> &hsize_, const quat<T> &rot_)
{
  pos=pos_;
  hsize=hsize_;
  rot=rot_;
}
//----------------------------------------------------------------------------


//============================================================================
// frustum3
//============================================================================
template<typename T>
frustum3<T>::frustum3()
{
}
//----

template<typename T>
frustum3<T>::frustum3(const mat44<T> &p2l_)
{
  proj_to_local=p2l_;
}
//----

template<typename T>
void frustum3<T>::set(const mat44<T> &p2l_)
{
  proj_to_local=p2l_;
}
//----------------------------------------------------------------------------


//============================================================================
// area functions
//============================================================================
template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const tri3<T> &t_)
{
  return norm(cross(t_.b-t_.a, t_.c-t_.a))*typename math<T>::scalar_t(0.5);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const rect3<T> &r_)
{
  return r_.hsize.x*r_.hsize.y*typename math<T>::scalar_t(4.0);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const disc3<T> &d_)
{
  return typename math<T>::pi*d_.rad*d_.rad;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const sphere3<T> &s_)
{
  return math<T>::four_pi*s_.rad*s_.rad;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const cylinder3<T> &cyl_)
{
  return math<T>::two_pi*cyl_.rad*(typename math<T>::scalar_t(2)*cyl_.hlen+cyl_.rad);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const capsule3<T> &cap_)
{
  return math<T>::four_pi*cap_.rad*(cap_.hlen+cap_.rad);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const cone3<T> &cone_)
{
  float cos2_apex_hangle=cone_.cos_apex_hangle*cone_.cos_apex_hangle;
  float base_rad2=cone_.height*cone_.height*(1.0f-cos2_apex_hangle)/cos2_apex_hangle;
  return math<T>::pi*(base_rad2*sqrt(base_rad2*(base_rad2+cone_.height*cone_.height)));
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const aabox3<T> &ab_)
{
  return (ab_.hsize.x*(ab_.hsize.y+ab_.hsize.z)+ab_.hsize.y*ab_.hsize.z)*typename math<T>::scalar_t(8.0);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const oobox3<T> &ob_)
{
  return (ob_.hsize.x*(ob_.hsize.y+ob_.hsize.z)+ob_.hsize.y*ob_.hsize.z)*typename math<T>::scalar_t(8.0);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const frustum3<T> &f_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----------------------------------------------------------------------------


//============================================================================
// volume functions
//============================================================================
template<typename T>
PFC_INLINE typename math<T>::scalar_t volume(const sphere3<T> &s_)
{
  return typename math<T>::scalar_t(1.0/3.0)*math<T>::four_pi*s_.rad*s_.rad*s_.rad;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t volume(const cylinder3<T> &cyl_)
{
  return math<T>::two_pi*cyl_.rad*cyl_.rad*cyl_.hlen;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t volume(const capsule3<T> &cap_)
{
  return math<T>::two_pi*cap_.rad*cap_.rad*(cap_.hlen+typename math<T>::scalar_t(2.0/3.0)*cap_.rad);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t volume(const cone3<T> &cone_)
{
  float cos2_apex_hangle=cone_.cos_apex_hangle*cone_.cos_apex_hangle;
  float base_rad2=cone_.height*cone_.height*(1.0f-cos2_apex_hangle)/cos2_apex_hangle;
  return typename math<T>::scalar_t(1.0/3.0)*math<T>::pi*base_rad2*cone_.height;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t volume(const aabox3<T> &ab_)
{
  return ab_.hsize.x*ab_.hsize.y*ab_.hsize.z*typename math<T>::scalar_t(8.0);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t volume(const oobox3<T> &ob_)
{
  return ob_.hsize.x*ob_.hsize.y*ob_.hsize.z*typename math<T>::scalar_t(8.0);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t volume(const frustum3<T> &f_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----------------------------------------------------------------------------
