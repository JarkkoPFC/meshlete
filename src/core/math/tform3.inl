//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// tform3
//============================================================================
template<typename T> const tform3<T> tform3<T>::s_zero(0, 0, 0, 0,
                                                       0, 0, 0, 0,
                                                       0, 0, 0, 0);
template<typename T> const tform3<T> tform3<T>::s_identity(scalar_t(1), 0, 0, 0,
                                                           0, scalar_t(1), 0, 0,
                                                           0, 0, scalar_t(1), 0);
//----------------------------------------------------------------------------

template<typename T>
tform3<T>::tform3()
  :x(scalar_t(1), 0, 0, 0)
  ,y(0, scalar_t(1), 0, 0)
  ,z(0, 0, scalar_t(1), 0)
{
}
//----

template<typename T>
tform3<T>::tform3(scalar_t s_)
  :x(s_, 0, 0, 0)
  ,y(0, s_, 0, 0)
  ,z(0, 0, s_, 0)
{
}
//----

template<typename T>
tform3<T>::tform3(scalar_t sx_, scalar_t sy_, scalar_t sz_)
  :x(sx_, 0, 0, 0)
  ,y(0, sy_, 0, 0)
  ,z(0, 0, sz_, 0)
{
}
//----

template<typename T>
tform3<T>::tform3(const vec3<T> &translation_)
  :x(scalar_t(1), 0, 0, translation_.x)
  ,y(0, scalar_t(1), 0, translation_.y)
  ,z(0, 0, scalar_t(1), translation_.z)
{
}
//----

template<typename T>
tform3<T>::tform3(const vec3<T> &x_, const vec3<T> &y_, const vec3<T> &z_)
  :x(x_, 0)
  ,y(y_, 0)
  ,z(z_, 0)
{
}
//----

template<typename T>
tform3<T>::tform3(const vec3<T> &x_, const vec3<T> &y_, const vec3<T> &z_, const vec3<T> &translation_)
  :x(x_, translation_.x)
  ,y(y_, translation_.y)
  ,z(z_, translation_.z)
{
}
//----

template<typename T>
tform3<T>::tform3(const vec4<T> &x_, const vec4<T> &y_, const vec4<T> &z_)
  :x(x_)
  ,y(y_)
  ,z(z_)
{
}
//----

template<typename T>
tform3<T>::tform3(scalar_t xx_, scalar_t xy_, scalar_t xz_, scalar_t xtrans_,
                  scalar_t yx_, scalar_t yy_, scalar_t yz_, scalar_t ytrans_,
                  scalar_t zx_, scalar_t zy_, scalar_t zz_, scalar_t ztrans_)
  :x(xx_, xy_, xz_, xtrans_)
  ,y(yx_, yy_, yz_, ytrans_)
  ,z(zx_, zy_, zz_, ztrans_)
{
}
//----

template<typename T>
tform3<T>::tform3(const mat33<T> &m_)
  :x(m_.x, 0)
  ,y(m_.y, 0)
  ,z(m_.z, 0)
{
}
//----

template<typename T>
tform3<T>::tform3(const mat33<T> &m_, const vec3<T> &translation_)
  :x(m_.x, translation_.x)
  ,y(m_.y, translation_.y)
  ,z(m_.z, translation_.z)
{
}
//----

template<typename T>
tform3<T>::tform3(const quat<T> &q_)
{
  // convert quaternion to matrix and setup transform
  mat33<T> m;
  convert(m, q_);
  x.set(m.x, 0);
  y.set(m.y, 0);
  z.set(m.z, 0);
}
//----

template<typename T>
tform3<T>::tform3(const quat<T> &q_, const vec3<T> &translation_)
{
  // convert quaternion to matrix and setup transform
  mat33<T> m;
  convert(m, q_);
  x.set(m.x, translation_.x);
  y.set(m.y, translation_.y);
  z.set(m.z, translation_.z);
}
//----

template<typename T>
tform3<T>::tform3(const tform_rt3<T> &t_)
{
  // convert tform_rt3 rotation to matrix and setup transform
  mat33<T> m;
  convert(m, t_.rotation);
  x.set(m.x, t_.translation.x);
  y.set(m.y, t_.translation.y);
  z.set(m.z, t_.translation.z);
}
//----------------------------------------------------------------------------

template<typename T>
const vec4<T> &tform3<T>::operator[](unsigned vidx_) const
{
  // return reference to nth transformation vector (x=0, y=1, z=2)
  PFC_CTF_ASSERT_MSG(sizeof(tform3)==sizeof(vec4<T>)*3, transform3_size_is_incorrect);
  PFC_ASSERT_PEDANTIC(vidx_<3);
  return reinterpret_cast<const vec4<T>*>(this)[vidx_];
}
//----

template<typename T>
vec4<T> &tform3<T>::operator[](unsigned vidx_)
{
  // return reference to nth transformation vector (x=0, y=1, z=2)
  PFC_CTF_ASSERT_MSG(sizeof(tform3)==sizeof(vec4<T>)*3, transform3_size_is_incorrect);
  PFC_ASSERT_PEDANTIC(vidx_<3);
  return reinterpret_cast<vec4<T>*>(this)[vidx_];
}
//----

template<typename T>
mat33<T> tform3<T>::matrix33() const
{
  // return affine matrix of the transform
  return mat33<T>(x.x, x.y, x.z,
                  y.x, y.y, y.z,
                  z.x, z.y, z.z);
}
//----

template<typename T>
mat44<T> tform3<T>::matrix44() const
{
  // return 4x4 matrix of the transform
  return mat44<T>(x.x, x.y, x.z, 0,
                  y.x, y.y, y.z, 0,
                  z.x, z.y, z.z, 0,
                  x.w, y.w, z.w, scalar_t(1));
}
//----

template<typename T>
const vec3<T> &tform3<T>::x_axis() const
{
  // return x-axis vector of the transform
  return reinterpret_cast<const vec3<T>&>(x);
}
//----

template<typename T>
const vec3<T> &tform3<T>::y_axis() const
{
  // return y-axis vector of the transform
  return reinterpret_cast<const vec3<T>&>(y);
}
//----

template<typename T>
const vec3<T> &tform3<T>::z_axis() const
{
  // return z-axis vector of the transform
  return reinterpret_cast<const vec3<T>&>(z);
}
//----

template<typename T>
vec3<T> tform3<T>::translation() const
{
  // return translation vector of the transform
  return vec3<T>(x.w, y.w, z.w);
}
//----------------------------------------------------------------------------

template<typename T>
void tform3<T>::set(scalar_t s_)
{
  // setup uniform scaling transform
  x.set(s_, 0, 0, 0);
  y.set(0, s_, 0, 0);
  z.set(0, 0, s_, 0);
}
//----

template<typename T>
void tform3<T>::set(scalar_t sx_, scalar_t sy_, scalar_t sz_)
{
  // setup non-uniform scaling transform
  x.set(sx_, 0, 0, 0);
  y.set(0, sy_, 0, 0);
  z.set(0, 0, sz_, 0);
}
//----

template<typename T>
void tform3<T>::set(const vec3<T> &translation_)
{
  // setup translation transform
  x.set(scalar_t(1), 0, 0, translation_.x);
  y.set(0, scalar_t(1), 0, translation_.y);
  z.set(0, 0, scalar_t(1), translation_.z);
}
//----

template<typename T>
void tform3<T>::set(const vec3<T> &x_, const vec3<T> &y_, const vec3<T> &z_)
{
  // setup transform from 3 axis and translation
  x.set(x_, 0);
  y.set(y_, 0);
  z.set(z_, 0);
}
//----

template<typename T>
void tform3<T>::set(const vec3<T> &x_, const vec3<T> &y_, const vec3<T> &z_, const vec3<T> &translation_)
{
  // setup transform from 3 axis and translation
  x.set(x_, translation_.x);
  y.set(y_, translation_.y);
  z.set(z_, translation_.z);
}
//----

template<typename T>
void tform3<T>::set(const vec4<T> &x_, const vec4<T> &y_, const vec4<T> &z_)
{
  // setup transform from 3 transform vectors
  x=x_;
  y=y_;
  z=z_;
}
//----

template<typename T>
void tform3<T>::set(scalar_t xx_, scalar_t xy_, scalar_t xz_, scalar_t xtrans_,
                    scalar_t yx_, scalar_t yy_, scalar_t yz_, scalar_t ytrans_,
                    scalar_t zx_, scalar_t zy_, scalar_t zz_, scalar_t ztrans_)
{
  // setup transform from scalars
  x.set(xx_, xy_, xz_, xtrans_);
  y.set(yx_, yy_, yz_, ytrans_);
  z.set(zx_, zy_, zz_, ztrans_);
}
//----

template<typename T>
void tform3<T>::set(const mat33<T> &m_)
{
  // setup transform from affine matrix
  x.set(m_.x, 0);
  y.set(m_.y, 0);
  z.set(m_.z, 0);
}
//----

template<typename T>
void tform3<T>::set(const mat33<T> &m_, const vec3<T> &translation_)
{
  // setup transform from affine matrix and translation
  x.set(m_.x, translation_.x);
  y.set(m_.y, translation_.y);
  z.set(m_.z, translation_.z);
}
//----

template<typename T>
void tform3<T>::set(const quat<T> &q_)
{
  // setup transform from quaternion rotation
  mat33<T> m;
  convert(m, q_);
  x.set(m.x, 0);
  y.set(m.y, 0);
  z.set(m.z, 0);
}
//----

template<typename T>
void tform3<T>::set(const quat<T> &q_, const vec3<T> &translation_)
{
  // setup transform from quaternion rotation and translation
  mat33<T> m;
  convert(m, q_);
  x.set(m.x, translation_.x);
  y.set(m.y, translation_.y);
  z.set(m.z, translation_.z);
}
//----

template<typename T>
void tform3<T>::set(const tform_rt3<T> &t_)
{
  // setup transform from tform_rt3
  mat33<T> m;
  convert(m, t_.rotation);
  x.set(m.x, t_.translation.x);
  y.set(m.y, t_.translation.y);
  z.set(m.z, t_.translation.z);
}
//----

template<typename T>
void tform3<T>::set_rotation(const mat33<T> &r_)
{
  // set rotation part of the transform
  x.x=r_.x.x; x.y=r_.x.y; x.z=r_.x.z;
  y.x=r_.y.x; y.y=r_.y.y; y.z=r_.y.z;
  z.x=r_.z.x; z.y=r_.z.y; z.z=r_.z.z;
}
//----

template<typename T>
void tform3<T>::set_translation(const vec3<T> &t_)
{
  // set translation part of the transform
  x.w=t_.x;
  y.w=t_.y;
  z.w=t_.z;
}
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE bool is_zero(const tform3<T> &t_)
{
  // test for zero-transform
  return is_zero(t_.x) && is_zero(t_.y) && is_zero(t_.z);
}
//----

template<typename T>
PFC_INLINE bool is_orthogonal(const tform3<T> &t_)
{
  // test for orthogonal transform
  return    t_.x.x*t_.y.x+t_.x.y*t_.y.y+t_.x.z*t_.y.z<0.0001f
         && t_.x.x*t_.z.x+t_.x.y*t_.z.y+t_.x.z*t_.z.z<0.0001f
         && t_.y.x*t_.z.x+t_.y.y*t_.z.y+t_.y.z*t_.z.z<0.0001f;
}
//----

template<typename T>
PFC_INLINE bool is_sat(const tform3<T> &t_)
{
  // test for saturated transform
  return is_sat(t_.x) && is_sat(t_.y) && is_sat(t_.z);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const tform3<T> &t_)
{
  // test for signed saturated transform
  return is_ssat(t_.x) && is_ssat(t_.y) && is_ssat(t_.z);
}
//----

template<typename T>
PFC_INLINE bool operator==(const tform3<T> &t0_, const tform3<T> &t1_)
{
  // test for equality of transforms
  return    t0_.x==t1_.x
         && t0_.y==t1_.y
         && t0_.z==t1_.z;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const tform3<T> &t0_, const tform3<T> &t1_)
{
  // test for inequality of transforms
  return    t0_.x!=t1_.x
         || t0_.y!=t1_.y
         || t0_.z!=t1_.z;
}
//----

template<typename T>
PFC_INLINE void operator+=(tform3<T> &tr_, const tform3<T> &t_)
{
  // add transform to transform
  tr_.x+=t_.x;
  tr_.y+=t_.y;
  tr_.z+=t_.z;
}
//----

template<typename T>
PFC_INLINE void operator-=(tform3<T> &tr_, const tform3<T> &t_)
{
  // subtract transform from transform
  tr_.x-=t_.x;
  tr_.y-=t_.y;
  tr_.z-=t_.z;
}
//----

template<typename T>
PFC_INLINE void operator*=(tform3<T> &tr_, const tform3<T> &t_)
{
  // multiply transform by transform
  const vec3<T> p(tr_.x.w, tr_.y.w, tr_.z.w);
  vec4<T> v=tr_.x;
  tr_.x.x=v.x*t_.x.x+v.y*t_.y.x+v.z*t_.z.x; tr_.x.y=v.x*t_.x.y+v.y*t_.y.y+v.z*t_.z.y; tr_.x.z=v.x*t_.x.z+v.y*t_.y.z+v.z*t_.z.z; tr_.x.w=p.x*t_.x.x+p.y*t_.y.x+p.z*t_.z.x+t_.x.w;
  v=tr_.y;
  tr_.y.x=v.x*t_.x.x+v.y*t_.y.x+v.z*t_.z.x; tr_.y.y=v.x*t_.x.y+v.y*t_.y.y+v.z*t_.z.y; tr_.y.z=v.x*t_.x.z+v.y*t_.y.z+v.z*t_.z.z; tr_.y.w=p.x*t_.x.y+p.y*t_.y.y+p.z*t_.z.y+t_.y.w;
  v=tr_.z;
  tr_.z.x=v.x*t_.x.x+v.y*t_.y.x+v.z*t_.z.x; tr_.z.y=v.x*t_.x.y+v.y*t_.y.y+v.z*t_.z.y; tr_.z.z=v.x*t_.x.z+v.y*t_.y.z+v.z*t_.z.z; tr_.z.w=p.x*t_.x.z+p.y*t_.y.z+p.z*t_.z.z+t_.z.w;
}
//----

template<typename T>
PFC_INLINE void operator*=(tform3<T> &tr_, const quat<T> &q_)
{
  // multiply transform by quaternion
  vec3<T> p(tr_.x.w, tr_.y.w, tr_.z.w);
  p*=q_;
  reinterpret_cast<vec3<T>&>(tr_.x)*=q_; tr_.x.w=p.x;
  reinterpret_cast<vec3<T>&>(tr_.y)*=q_; tr_.y.w=p.y;
  reinterpret_cast<vec3<T>&>(tr_.z)*=q_; tr_.z.w=p.z;
}
//----

template<typename T>
PFC_INLINE void operator*=(tform3<T> &tr_, const mat33<T> &m_)
{
  // multiply transform by matrix
  vec3<T> p(tr_.x.w, tr_.y.w, tr_.z.w);
  p*=m_;
  reinterpret_cast<vec3<T>&>(tr_.x)*=m_; tr_.x.w=p.x;
  reinterpret_cast<vec3<T>&>(tr_.y)*=m_; tr_.y.w=p.y;
  reinterpret_cast<vec3<T>&>(tr_.z)*=m_; tr_.z.w=p.z;
}
//----

template<typename T>
PFC_INLINE void operator*=(tform3<T> &tr_, typename math<T>::scalar_t s_)
{
  // multiply transform by scalar
  tr_.x*=s_;
  tr_.y*=s_;
  tr_.z*=s_;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec3<T> &vr_, const tform3<T> &t_)
{
  // multiply vector by transform (assume w=1)
  vec3<T> v(vr_);
  vr_.x=v.x*t_.x.x+v.y*t_.y.x+v.z*t_.z.x+t_.x.w;
  vr_.y=v.x*t_.x.y+v.y*t_.y.y+v.z*t_.z.y+t_.y.w;
  vr_.z=v.x*t_.x.z+v.y*t_.y.z+v.z*t_.z.z+t_.z.w;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec4<T> &vr_, const tform3<T> &t_)
{
  // multiply vector by transform
  vec4<T> v(vr_);
  vr_.x=v.x*t_.x.x+v.y*t_.y.x+v.z*t_.z.x+v.w*t_.x.w;
  vr_.y=v.x*t_.x.y+v.y*t_.y.y+v.z*t_.z.y+v.w*t_.y.w;
  vr_.z=v.x*t_.x.z+v.y*t_.y.z+v.z*t_.z.z+v.w*t_.z.w;
}
//----

template<typename T>
PFC_INLINE void operator*=(mat44<T> &mr_, const tform3<T> &t_)
{
  // multiply 4x4 matrix by transform
  vec4<T> v=mr_.x;
  mr_.x.x=v.x*t_.x.x+v.y*t_.y.x+v.z*t_.z.x+v.w*t_.x.w; mr_.x.y=v.x*t_.x.y+v.y*t_.y.y+v.z*t_.z.y+v.w*t_.y.w; mr_.x.z=v.x*t_.x.z+v.y*t_.y.z+v.z*t_.z.z+v.w*t_.z.w; mr_.x.w=v.w;
  v=mr_.y;
  mr_.y.x=v.x*t_.x.x+v.y*t_.y.x+v.z*t_.z.x+v.w*t_.x.w; mr_.y.y=v.x*t_.x.y+v.y*t_.y.y+v.z*t_.z.y+v.w*t_.y.w; mr_.y.z=v.x*t_.x.z+v.y*t_.y.z+v.z*t_.z.z+v.w*t_.z.w; mr_.y.w=v.w;
  v=mr_.z;
  mr_.z.x=v.x*t_.x.x+v.y*t_.y.x+v.z*t_.z.x+v.w*t_.x.w; mr_.z.y=v.x*t_.x.y+v.y*t_.y.y+v.z*t_.z.y+v.w*t_.y.w; mr_.z.z=v.x*t_.x.z+v.y*t_.y.z+v.z*t_.z.z+v.w*t_.z.w; mr_.z.w=v.w;
  v=mr_.w;
  mr_.w.x=v.x*t_.x.x+v.y*t_.y.x+v.z*t_.z.x+v.w*t_.x.w; mr_.w.y=v.x*t_.x.y+v.y*t_.y.y+v.z*t_.z.y+v.w*t_.y.w; mr_.w.z=v.x*t_.x.z+v.y*t_.y.z+v.z*t_.z.z+v.w*t_.z.w; mr_.w.w=v.w;
}
//----

template<typename T>
PFC_INLINE void operator/=(tform3<T> &tr_, typename math<T>::scalar_t s_)
{
  // divide transform by scalar
  typename math<T>::scalar_t rs=rcp(s_);
  tr_.x*=rs;
  tr_.y*=rs;
  tr_.z*=rs;
}
//----

template<typename T>
PFC_INLINE tform3<T> operator+(const tform3<T> &t0_, const tform3<T> &t1_)
{
  // add transform to transform
  return tform3<T>(t0_.x+t1_.x,
                   t0_.y+t1_.y,
                   t0_.z+t1_.z);
}
//----

template<typename T>
PFC_INLINE tform3<T> operator-(const tform3<T> &t0_, const tform3<T> &t1_)
{
  // subtract transform from transform
  return tform3<T>(t0_.x-t1_.x,
                   t0_.y-t1_.y,
                   t0_.z-t1_.z);
}
//----

template<typename T>
PFC_INLINE tform3<T> operator-(const tform3<T> &t_)
{
  // negate transform
  return tform3<T>(-t_.x, -t_.y, -t_.z);
}
//----

template<typename T>
PFC_INLINE tform3<T> operator*(const tform3<T> &t0_, const tform3<T> &t1_)
{
  // multiply transform by transform
  return tform3<T>(t0_.x.x*t1_.x.x+t0_.x.y*t1_.y.x+t0_.x.z*t1_.z.x, t0_.x.x*t1_.x.y+t0_.x.y*t1_.y.y+t0_.x.z*t1_.z.y, t0_.x.x*t1_.x.z+t0_.x.y*t1_.y.z+t0_.x.z*t1_.z.z, t0_.x.w*t1_.x.x+t0_.y.w*t1_.y.x+t0_.z.w*t1_.z.x+t1_.x.w,
                   t0_.y.x*t1_.x.x+t0_.y.y*t1_.y.x+t0_.y.z*t1_.z.x, t0_.y.x*t1_.x.y+t0_.y.y*t1_.y.y+t0_.y.z*t1_.z.y, t0_.y.x*t1_.x.z+t0_.y.y*t1_.y.z+t0_.y.z*t1_.z.z, t0_.x.w*t1_.x.y+t0_.y.w*t1_.y.y+t0_.z.w*t1_.z.y+t1_.y.w,
                   t0_.z.x*t1_.x.x+t0_.z.y*t1_.y.x+t0_.z.z*t1_.z.x, t0_.z.x*t1_.x.y+t0_.z.y*t1_.y.y+t0_.z.z*t1_.z.y, t0_.z.x*t1_.x.z+t0_.z.y*t1_.y.z+t0_.z.z*t1_.z.z, t0_.x.w*t1_.x.z+t0_.y.w*t1_.y.z+t0_.z.w*t1_.z.z+t1_.z.w);
}
//----

template<typename T>
PFC_INLINE tform3<T> operator*(const tform3<T> &t_, const quat<T> &q_)
{
  // multiply transform by quaternion
  return tform3<T>(reinterpret_cast<const vec3<T>&>(t_.x)*q_,
                   reinterpret_cast<const vec3<T>&>(t_.y)*q_,
                   reinterpret_cast<const vec3<T>&>(t_.z)*q_,
                   vec3<T>(t_.x.w, t_.y.w, t_.z.w)*q_);
}
//----

template<typename T>
PFC_INLINE tform3<T> operator*(const tform3<T> &t_, const mat33<T> &m_)
{
  // multiply transform by matrix
  return tform3<T>(reinterpret_cast<const vec3<T>&>(t_.x)*m_,
                   reinterpret_cast<const vec3<T>&>(t_.y)*m_,
                   reinterpret_cast<const vec3<T>&>(t_.z)*m_,
                   vec3<T>(t_.x.w, t_.y.w, t_.z.w)*m_);
}
//----

template<typename T>
PFC_INLINE tform3<T> operator*(const tform3<T> &t_, typename math<T>::scalar_t s_)
{
  // multiply transform by scalar
  return tform3<T>(t_.x*s_, t_.y*s_, t_.z*s_);
}
//----

template<typename T>
PFC_INLINE tform3<T> operator*(typename math<T>::scalar_t s_, const tform3<T> &t_)
{
  // multiply transform by scalar
  return tform3<T>(t_.x*s_, t_.y*s_, t_.z*s_);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator*(const vec3<T> &v_, const tform3<T> &t_)
{
  // multiply 3d vector by transform (assume vector w=1)
  return vec3<T>(v_.x*t_.x.x+v_.y*t_.y.x+v_.z*t_.z.x+t_.x.w,
                 v_.x*t_.x.y+v_.y*t_.y.y+v_.z*t_.z.y+t_.y.w,
                 v_.x*t_.x.z+v_.y*t_.y.z+v_.z*t_.z.z+t_.z.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator*(const vec4<T> &v_, const tform3<T> &t_)
{
  // multiply 4d vector by transform
  return vec4<T>(v_.x*t_.x.x+v_.y*t_.y.x+v_.z*t_.z.x+v_.w*t_.x.w,
                 v_.x*t_.x.y+v_.y*t_.y.y+v_.z*t_.z.y+v_.w*t_.y.w,
                 v_.x*t_.x.z+v_.y*t_.y.z+v_.z*t_.z.z+v_.w*t_.z.w,
                 v_.w);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator*(const tform3<T> &t_, const vec3<T> &v_)
{
  // multiply transform by transposed 3d vector
  return vec3<T>(v_.x*t_.x.x+v_.y*t_.x.y+v_.z*t_.x.z,
                 v_.x*t_.y.x+v_.y*t_.y.y+v_.z*t_.y.z,
                 v_.x*t_.z.x+v_.y*t_.z.y+v_.z*t_.z.z);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator*(const tform3<T> &t_, const vec4<T> &v_)
{
  // multiply transform by transposed 4d vector
  return vec4<T>(v_.x*t_.x.x+v_.y*t_.x.y+v_.z*t_.x.z,
                 v_.x*t_.y.x+v_.y*t_.y.y+v_.z*t_.y.z,
                 v_.x*t_.z.x+v_.y*t_.z.y+v_.z*t_.z.z,
                 v_.x*t_.x.w+v_.y*t_.y.w+v_.z*t_.z.w+v_.w);
}
//----

template<typename T>
PFC_INLINE mat44<T> operator*(const mat44<T> &m_, const tform3<T> &t_)
{
  // multiply 4x4 matrix by transform
  return mat44<T>(m_.x.x*t_.x.x+m_.x.y*t_.y.x+m_.x.z*t_.z.x+m_.x.w*t_.x.w, m_.x.x*t_.x.y+m_.x.y*t_.y.y+m_.x.z*t_.z.y+m_.x.w*t_.y.w, m_.x.x*t_.x.z+m_.x.y*t_.y.z+m_.x.z*t_.z.z+m_.x.w*t_.z.w, m_.x.w,
                  m_.y.x*t_.x.x+m_.y.y*t_.y.x+m_.y.z*t_.z.x+m_.y.w*t_.x.w, m_.y.x*t_.x.y+m_.y.y*t_.y.y+m_.y.z*t_.z.y+m_.y.w*t_.y.w, m_.y.x*t_.x.z+m_.y.y*t_.y.z+m_.y.z*t_.z.z+m_.y.w*t_.z.w, m_.y.w,
                  m_.z.x*t_.x.x+m_.z.y*t_.y.x+m_.z.z*t_.z.x+m_.z.w*t_.x.w, m_.z.x*t_.x.y+m_.z.y*t_.y.y+m_.z.z*t_.z.y+m_.z.w*t_.y.w, m_.z.x*t_.x.z+m_.z.y*t_.y.z+m_.z.z*t_.z.z+m_.z.w*t_.z.w, m_.z.w,
                  m_.w.x*t_.x.x+m_.w.y*t_.y.x+m_.w.z*t_.z.x+m_.w.w*t_.x.w, m_.w.x*t_.x.y+m_.w.y*t_.y.y+m_.w.z*t_.z.y+m_.w.w*t_.y.w, m_.w.x*t_.x.z+m_.w.y*t_.y.z+m_.w.z*t_.z.z+m_.w.w*t_.z.w, m_.w.w);
}
//----

template<typename T>
PFC_INLINE mat44<T> operator*(const tform3<T> &t_, const mat44<T> &m_)
{
  // multiply transform by 4x4 matrix
  return mat44<T>(t_.x.x*m_.x.x+t_.x.y*m_.y.x+t_.x.z*m_.z.x,        t_.x.x*m_.x.y+t_.x.y*m_.y.y+t_.x.z*m_.z.y,        t_.x.x*m_.x.z+t_.x.y*m_.y.z+t_.x.z*m_.z.z,        t_.x.x*m_.x.w+t_.x.y*m_.y.w+t_.x.z*m_.z.w,
                  t_.y.x*m_.x.x+t_.y.y*m_.y.x+t_.y.z*m_.z.x,        t_.y.x*m_.x.y+t_.y.y*m_.y.y+t_.y.z*m_.z.y,        t_.y.x*m_.x.z+t_.y.y*m_.y.z+t_.y.z*m_.z.z,        t_.y.x*m_.x.w+t_.y.y*m_.y.w+t_.y.z*m_.z.w,
                  t_.z.x*m_.x.x+t_.z.y*m_.y.x+t_.z.z*m_.z.x,        t_.z.x*m_.x.y+t_.z.y*m_.y.y+t_.z.z*m_.z.y,        t_.z.x*m_.x.z+t_.z.y*m_.y.z+t_.z.z*m_.z.z,        t_.z.x*m_.x.w+t_.z.y*m_.y.w+t_.z.z*m_.z.w,
                  t_.x.w*m_.x.x+t_.y.w*m_.y.x+t_.z.w*m_.z.x+m_.w.x, t_.x.w*m_.x.y+t_.y.w*m_.y.y+t_.z.w*m_.z.y+m_.w.y, t_.x.w*m_.x.z+t_.y.w*m_.y.z+t_.z.w*m_.z.z+m_.w.z, t_.x.w*m_.x.w+t_.y.w*m_.y.w+t_.z.w*m_.z.w+m_.w.w);
}
//----

template<typename T>
PFC_INLINE tform3<T> operator/(const tform3<T> &t_, typename math<T>::scalar_t s_)
{
  // divide transform by scalar
  typename math<T>::scalar_t rs=rcp(s_);
  return tform3<T>(t_.x*rs, t_.y*rs, t_.z*rs);
}
//----

template<typename T>
PFC_INLINE tform3<T> madd(const tform3<T> &t0_, const tform3<T> &t1_, const tform3<T> &t2_)
{
  // component-wise multiply-add: t0_*t1+t2_
  return tform3<T>(madd(t0_.x, t1_.x, t2_.x), madd(t0_.y, t1_.y, t2_.z), madd(t0_.z, t1_.z, t2_.z));
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t det(const tform3<T> &t_)
{
  // calculate determinant
  return  t_.x.x*(t_.y.y*t_.z.z-t_.y.z*t_.z.y)
         +t_.y.x*(t_.z.y*t_.x.z-t_.z.z*t_.x.y)
         +t_.z.x*(t_.x.y*t_.y.z-t_.x.z*t_.y.y);
}
//----

template<typename T>
PFC_INLINE tform3<T> inv(const tform3<T> &t_, typename math<T>::scalar_t *det_)
{
  // calculate determinant
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t d= t_.x.x*(t_.y.y*t_.z.z-t_.y.z*t_.z.y)
             +t_.y.x*(t_.z.y*t_.x.z-t_.z.z*t_.x.y)
             +t_.z.x*(t_.x.y*t_.y.z-t_.x.z*t_.y.y);
  if(det_)
    *det_=d;
  if(!d)
    return tform3<T>::s_zero;

  // calculate inverse of the transform
  mat33<T> m((t_.y.y*t_.z.z-t_.y.z*t_.z.y), (t_.x.z*t_.z.y-t_.x.y*t_.z.z), (t_.x.y*t_.y.z-t_.x.z*t_.y.y),
             (t_.y.z*t_.z.x-t_.y.x*t_.z.z), (t_.x.x*t_.z.z-t_.x.z*t_.z.x), (t_.x.z*t_.y.x-t_.x.x*t_.y.z),
             (t_.y.x*t_.z.y-t_.y.y*t_.z.x), (t_.x.y*t_.z.x-t_.x.x*t_.z.y), (t_.x.x*t_.y.y-t_.x.y*t_.y.x));
  m/=d;
  return tform3<T>(m, -t_.translation()*m);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t tr(const tform3<T> &t_)
{
  // calculate trace of the transform
  return t_.x.x+t_.y.y+t_.z.z;
}
//----

template<typename T>
PFC_INLINE void identity(tform3<T> &tr_)
{
  // set identity transform
  typedef typename math<T>::scalar_t scalar_t;
  tr_.x.set(scalar_t(1), 0, 0, 0);
  tr_.y.set(0, scalar_t(1), 0, 0);
  tr_.z.set(0, 0, scalar_t(1), 0);
}
//----

template<typename T>
PFC_INLINE void transpose_matrix33(tform3<T> &tr_)
{
  // transpose the 3x3 upper-left matrix of the transform
  typename math<T>::scalar_t t;
  t=tr_.x.y;
  tr_.x.y=tr_.y.x;
  tr_.y.x=t;
  t=tr_.x.z;
  tr_.x.z=tr_.z.x;
  tr_.z.x=t;
  t=tr_.y.z;
  tr_.y.z=tr_.z.y;
  tr_.z.y=t;
}
//----

template<typename T>
PFC_INLINE void transpose_matrix33(tform3<T> &tr_, const tform3<T> &t_)
{
  // transpose the 3x3 upper-left matrix of the transform
  tr_.x.x=t_.x.x; tr_.x.y=t_.y.x; tr_.x.z=t_.z.x; tr_.x.w=t_.x.w;
  tr_.y.x=t_.x.y; tr_.y.y=t_.y.y; tr_.y.z=t_.z.y; tr_.y.w=t_.y.w;
  tr_.z.x=t_.x.z; tr_.z.y=t_.y.z; tr_.z.z=t_.z.z; tr_.z.w=t_.z.w;
}
//----

template<typename T>
PFC_INLINE void neg(tform3<T> &tr_)
{
  // negate transform
  neg(tr_.x);
  neg(tr_.y);
  neg(tr_.z);
}
//----

template<typename T>
PFC_INLINE tform3<T> lerp(const tform3<T> &t0_, const tform3<T> &t1_, typename math<T>::scalar_t t_)
{
  // linear transform interpolation. f(t=0)=t0, f(t=1)=t1
  return tform3<T>(lerp(t0_.x, t1_.x, t_),
                   lerp(t0_.y, t1_.y, t_),
                   lerp(t0_.z, t1_.z, t_));
}
//----

template<typename T>
PFC_INLINE void lerp(tform3<T> &tr_, const tform3<T> &t0_, const tform3<T> &t1_, typename math<T>::scalar_t t_)
{
  // linear transform interpolation. f(t=0)=t0, f(t=1)=t1
  tr_.x=lerp(t0_.x, t1_.x, t_);
  tr_.y=lerp(t0_.y, t1_.y, t_);
  tr_.z=lerp(t0_.z, t1_.z, t_);
}
//----

template<typename T>
PFC_INLINE void zrot_u(tform3<T> &tr_, const vec3<T> &pos_, const vec3<T> &zdir_)
{
  // set z-axis to point to given direction by using quaternion rotation
  mat33<T> m;
  convert_u(m, zrot_u(zdir_));
  tr_.set(m, pos_);
}
//----

template<typename T>
PFC_INLINE void zrot_u(tform3<T> &tr_, const vec3<T> &pos_, const vec3<T> &zdir_, const vec3<T> &up_)
{
  // set z-axis to point to given direction by using up-vector
  mat33<T> m;
  vec3<T> x=cross(up_, zdir_);
  if(is_zero(x))
    x.set(typename math<T>::scalar_t(1), 0, 0);
  m.x=unit(x);
  m.y=cross(zdir_, m.x);
  m.z=zdir_;
  tr_.set(m, pos_);
}
//----

template<typename T>
PFC_INLINE void axis_rot(tform3<T> &tr_, const vec3<T> &pos_, const vec3<T> &axis_, typename math<T>::scalar_t angle_)
{
  // generate rotation from axis and angle (radians)
  mat33<T> m;
  convert(m, axis_rot(axis_, angle_));
  tr_.x.x=m.x.x; tr_.x.y=m.x.y; tr_.x.z=m.x.z; tr_.x.w=pos_.x;
  tr_.y.x=m.y.x; tr_.y.y=m.y.y; tr_.y.z=m.y.z; tr_.y.w=pos_.y;
  tr_.z.x=m.z.x; tr_.z.y=m.z.y; tr_.z.z=m.z.z; tr_.z.w=pos_.z;
}
//----

template<typename T>
PFC_INLINE void axis_rot_u(tform3<T> &tr_, const vec3<T> &pos_, const vec3<T> &axis_, typename math<T>::scalar_t angle_)
{
  // generate rotation from unit axis and angle (radians)
  mat33<T> m;
  convert(m, axis_rot_u(axis_, angle_));
  tr_.x.x=m.x.x; tr_.x.y=m.x.y; tr_.x.z=m.x.z; tr_.x.w=pos_.x;
  tr_.y.x=m.y.x; tr_.y.y=m.y.y; tr_.y.z=m.y.z; tr_.y.w=pos_.y;
  tr_.z.x=m.z.x; tr_.z.y=m.z.y; tr_.z.z=m.z.z; tr_.z.w=pos_.z;
}
//----

template<typename T, typename U>
PFC_INLINE tform3<T> to_tform3(const tform3<U> &t_)
{
  // convert between tform3 types
  typedef typename math<T>::scalar_t scalar_t;
  tform3<T> t(scalar_t(t_.x.x), scalar_t(t_.x.y), scalar_t(t_.x.z), scalar_t(t_.x.w),
              scalar_t(t_.y.x), scalar_t(t_.y.y), scalar_t(t_.y.z), scalar_t(t_.y.w),
              scalar_t(t_.z.x), scalar_t(t_.z.y), scalar_t(t_.z.z), scalar_t(t_.z.w));
  return t;
}
//----

template<typename T>
PFC_INLINE void orthonormalize(tform3<T> &tr_)
{
  // ortho-normalize the transform
  tr_.x.set(unit((vec3<T>&)tr_.x), tr_.x.w);
  tr_.y.set(unit(cross((vec3<T>&)tr_.z, (vec3<T>&)tr_.x)), tr_.y.w);
  tr_.z.set(cross((vec3<T>&)tr_.x, (vec3<T>&)tr_.y), tr_.z.w);
}
//----------------------------------------------------------------------------


//============================================================================
// tform_rt3
//============================================================================
template<typename T> const tform_rt3<T> tform_rt3<T>::s_zero(quat<T>(0, 0, 0, 0), vec3<T>(0, 0, 0));
template<typename T> const tform_rt3<T> tform_rt3<T>::s_identity(quat<T>(0, 0, 0, scalar_t(1)), vec3<T>(0, 0, 0));
//----------------------------------------------------------------------------

template<typename T>
tform_rt3<T>::tform_rt3()
  :rotation(0, 0, 0, scalar_t(1))
  ,translation(0, 0, 0)
{
}
//----

template<typename T>
tform_rt3<T>::tform_rt3(const quat<T> &rotation_)
  :rotation(rotation_)
  ,translation(0, 0, 0)
{
}
//----

template<typename T>
tform_rt3<T>::tform_rt3(const vec3<T> &translation_)
  :rotation(0, 0, 0, scalar_t(1))
  ,translation(translation_)
{
}
//----

template<typename T>
tform_rt3<T>::tform_rt3(const quat<T> &rotation_, const vec3<T> &translation_)
  :rotation(rotation_)
  ,translation(translation_)
{
}
//----

template<typename T>
tform_rt3<T>::tform_rt3(const tform3<T> &tform_)
{
  // convert tform3 to tform_rt3
  mat33<T> rot=tform_.matrix33();
  orthonormalize(rot);
  convert(rotation, rot);
  translation=tform_.translation();
}
//----------------------------------------------------------------------------

template<typename T>
mat33<T> tform_rt3<T>::matrix33() const
{
  // return 3x3 rotation matrix
  mat33<T> mr;
  convert(mr, rotation);
  return mr;
}
//----

template<typename T>
mat44<T> tform_rt3<T>::matrix44() const
{
  // return 4x4 matrix
  mat33<T> mr;
  convert(mr, rotation);
  mat44<T> m(mr);
  m.w.set(translation, scalar_t(1));
  return m;
}
//----------------------------------------------------------------------------

template<typename T>
void tform_rt3<T>::set(const quat<T> &rotation_)
{
  rotation=rotation_;
  translation.set(scalar_t(0));
}
//----

template<typename T>
void tform_rt3<T>::set(const vec3<T> &translation_)
{
  rotation=quat<T>::s_identity;
  translation=translation_;
}
//---

template<typename T>
void tform_rt3<T>::set(const quat<T> &rotation_, const vec3<T> &translation_)
{
  rotation=rotation_;
  translation=translation_;
}
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE bool is_zero(const tform_rt3<T> &t_)
{
  // test for zero-transform
  return is_zero(t_.rotation) && is_zero(t_.translation);
}
//----

template<typename T>
PFC_INLINE bool is_sat(const tform_rt3<T> &t_)
{
  // test for saturated transform
  return is_sat(t_.rotation) && is_sat(t_.translation);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const tform_rt3<T> &t_)
{
  // test for signed saturated transform
  return is_ssat(t_.rotation) && is_ssat(t_.translation);
}
//----

template<typename T>
PFC_INLINE bool operator==(const tform_rt3<T> &t0_, const tform_rt3<T> &t1_)
{
  // test for equality of transforms
  return    t0_.rotation==t1_.rotation
         && t0_.translation==t1_.translation;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const tform_rt3<T> &t0_, const tform_rt3<T> &t1_)
{
  // test for inequality of transforms
  return    t0_.rotation!=t1_.rotation
         || t0_.translation!=t1_.translation;
}
//----

template<typename T>
PFC_INLINE void operator+=(tform_rt3<T> &tr_, const tform_rt3<T> &t_)
{
  // add transform to transform
  tr_.rotation+=t_.rotation;
  tr_.translation+=t_.translation;
}
//----

template<typename T>
PFC_INLINE void operator-=(tform_rt3<T> &tr_, const tform_rt3<T> &t_)
{
  // subtract transform from transform
  tr_.rotation-=t_.rotation;
  tr_.translation-=t_.translation;
}
//----

template<typename T>
PFC_INLINE void operator*=(tform_rt3<T> &tr_, const tform_rt3<T> &t_)
{
  // multiply transform by transform
  tr_.rotation=t_.rotation*tr_.rotation;
  tr_.translation*=t_.rotation;
  tr_.translation+=t_.translation;
}
//----

template<typename T>
PFC_INLINE void operator*=(tform_rt3<T> &tr_, const quat<T> &q_)
{
  // multiply transform by quaternion
  tr_.rotation=q_*tr_.rotation;
  tr_.translation*=q_;
}
//----

template<typename T>
PFC_INLINE void operator*=(tform_rt3<T> &tr_, typename math<T>::scalar_t s_)
{
  // multiply transform by scalar
  tr_.rotation*=s_;
  tr_.translation*=s_;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec3<T> &vr_, const tform_rt3<T> &t_)
{
  // multiply 3d vector by transform (assume w=1)
  vr_*=t_.rotation;
  vr_+=t_.translation;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec4<T> &vr_, const tform_rt3<T> &t_)
{
  // multiply 4d vector by transform
  vr_.set(vec3<T>(vr_.x, vr_.y, vr_.z)*t_.rotation+vr_.w*t_.translation, vr_.w);
}
//----

template<typename T>
PFC_INLINE void operator*=(mat44<T> &mr_, const tform_rt3<T> &t_)
{
  mr_*=t_.matrix();
}
//----

template<typename T>
PFC_INLINE void operator/=(tform_rt3<T> &tr_, typename math<T>::scalar_t s_)
{
  // divide transform by scalar
  typename math<T>::scalar_t rs=rcp(s_);
  tr_.rotation*=rs;
  tr_.translation*=rs;
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> operator+(const tform_rt3<T> &t0_, const tform_rt3<T> &t1_)
{
  // add transform to transform
  return tform_rt3<T>(t0_.rotation+t1_.rotation, t0_.translation+t1_.translation);
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> operator-(const tform_rt3<T> &t0_, const tform_rt3<T> &t1_)
{
  // subtract transform from transform
  return tform_rt3<T>(t0_.rotation-t1_.rotation, t0_.translation-t1_.translation);
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> operator-(const tform_rt3<T> &t_)
{
  // negate transform
  return tform_rt3<T>(-t_.rotation, -t_.translation);
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> operator*(const tform_rt3<T> &t0_, const tform_rt3<T> &t1_)
{
  // multiply transform by transform
  return tform_rt3<T>(t1_.rotation*t0_.rotation, t0_.translation*t1_.rotation+t1_.translation);
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> operator*(const tform_rt3<T> &t_, const quat<T> &q_)
{
  // multiply transform by quaternion
  return tform_rt3<T>(q_*t_.rotation, t_.translation*q_);
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> operator*(const tform_rt3<T> &t_, typename math<T>::scalar_t s_)
{
  // multiply transform by scalar
  return tform_rt3<T>(t_.rotation*s_, t_.translation*s_);
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> operator*(typename math<T>::scalar_t s_, const tform_rt3<T> &t_)
{
  // multiply transform by scalar
  return tform_rt3<T>(t_.rotation*s_, t_.translation*s_);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator*(const vec3<T> &v_, const tform_rt3<T> &t_)
{
  // multiply 3d vector by transform (assume w=1)
  return v_*t_.rotation+t_.translation;
}
//----

template<typename T>
PFC_INLINE vec4<T> operator*(const vec4<T> &v_, const tform_rt3<T> &t_)
{
  // multiply 4d vector by transform
  return vec4<T>(vec3<T>(v_.x, v_.y, v_.z)*t_.rotation+v_.w*t_.translation, v_.w);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator*(const tform_rt3<T> &t_, const vec3<T> &v_)
{
  // multiply transform by transposed 3d vector
  return v_*inv_u(t_.rotation);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator*(const tform_rt3<T> &t_, const vec4<T> &v_)
{
  // multiply transform by transposed 4d vector
  return vec4<T>(((const vec3<T>&)v_)*inv_u(t_.rotation), dot(v_, vec4<T>(t_.translation, typename math<T>::scalar_t(1))));
}
//----

template<typename T>
PFC_INLINE mat44<T> operator*(const mat44<T> &m_, const tform_rt3<T> &t_)
{
  return m_*t_.matrix();
}
//----

template<typename T>
PFC_INLINE mat44<T> operator*(const tform_rt3<T> &t_, const mat44<T> &m_)
{
  return t_.matrix()*m_;
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> operator/(const tform_rt3<T> &t_, typename math<T>::scalar_t s_)
{
  // divide transform by scalar
  typename math<T>::scalar_t rs=rcp(s_);
  return tform_rt3<T>(t_.rotation*rs, t_.translation*rs);
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> madd(const tform_rt3<T> &t0_, const tform_rt3<T> &t1_, const tform_rt3<T> &t2_)
{
  // component-wise multiply-add: t0_*t1+t2_
  return tform_rt3<T>(madd(t0_.rotation, t1_.rotation, t2_.rotation), madd(t0_.translation, t1_.translation, t2_.translation));
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> inv(const tform_rt3<T> &t_)
{
  // inverse of the transform
  quat<T> ir=inv_u(t_.rotation);
  return tform_rt3<T>(ir, -t_.translation*ir);
}
//----

template<typename T>
PFC_INLINE void identity(tform_rt3<T> &tr_)
{
  // set transform to identity
  tr_.rotation=quat<T>::s_identity;
  tr_.translation.set(math<T>::scalar_t(0));
}
//----

template<typename T>
PFC_INLINE void neg(tform_rt3<T> &tr_)
{
  // negate the transform
  neg(tr_.rotation);
  neg(tr_.translation);
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> lerp(const tform_rt3<T> &t0_, const tform_rt3<T> &t1_, typename math<T>::scalar_t t_)
{
  // linear interpolation of transforms: f(t=0)=t0, f(t=1)=t1
  return t0_*(typename math<T>::scalar_t(1)-t_)+t1_*t_;
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> nlerp(const tform_rt3<T> &t0_, const tform_rt3<T> &t1_, typename math<T>::scalar_t t_)
{
  // linear interpolation of transforms with normalized rotation
  tform_rt3<T> t=t0_*(typename math<T>::scalar_t(1)-t_)+t1_*t_;
  t.rotation=unit(t.rotation);
  return t;
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> nlerp_z(const tform_rt3<T> &t0_, const tform_rt3<T> &t1_, typename math<T>::scalar_t t_)
{
  // linear interpolation of transforms with normalized rotation, if |rotation|=0, rotation=[0, 0, 0, 1]
  tform_rt3<T> t=t0_*(typename math<T>::scalar_t(1)-t_)+t1_*t_;
  t.rotation=unit_z(t.rotation);
  return t;
}
//----

template<typename T>
PFC_INLINE tform_rt3<T> slerp(const tform_rt3<T> &t0_, const tform_rt3<T> &t1_, typename math<T>::scalar_t t_)
{
  // linear interpolation of translation with spherical rotation interpolation
  return tform_rt3<T>(slerp(t0_.rotation, t1_.rotation, t_), lerp(t0_.translation, t1_.translation, t_));
}
//----

template<typename T>
PFC_INLINE void zrot_u(tform_rt3<T> &tr_, const vec3<T> &pos_, const vec3<T> &zdir_)
{
  // set z-axis to point to given direction by using quaternion rotation
  tr_.rotation=zrot_u(zdir_);
  tr_.translation=pos_;
}
//----

template<typename T>
PFC_INLINE void axis_rot(tform_rt3<T> &tr_, const vec3<T> &pos_, const vec3<T> &axis_, typename math<T>::scalar_t angle_)
{
  // setup transform from position and rotation about given axis
  tr_.rotation=axis_rot(axis_, angle_);
  tr_.translation=pos_;
}
//----

template<typename T>
PFC_INLINE void axis_rot_u(tform_rt3<T> &tr_, const vec3<T> &pos_, const vec3<T> &axis_, typename math<T>::scalar_t angle_)
{
  // setup transform from position and rotation about unit given axis
  tr_.rotation=axis_rot_u(axis_, angle_);
  tr_.translation=pos_;
}
//----

template<typename T, typename U>
PFC_INLINE tform_rt3<T> to_tform_rt3(const tform_rt3<U> &t_)
{
  // convert between tform_rt3 types
  tform_rt3<T> t(to_quat<T>(t_.rotation), to_vec3<T>(t_.translation));
  return t;
}
//----------------------------------------------------------------------------


//============================================================================
// camera
//============================================================================
template<typename T>
camera<T>::camera()
  :m_view_to_proj(scalar_t(1), scalar_t(0), scalar_t(0), scalar_t(0),
                  scalar_t(0), scalar_t(1), scalar_t(0), scalar_t(0),
                  scalar_t(0), scalar_t(0), scalar_t(1), scalar_t(0),
                  scalar_t(0), scalar_t(0), scalar_t(0), scalar_t(1))
  ,m_view_to_world(scalar_t(1), scalar_t(0), scalar_t(0), scalar_t(0),
                   scalar_t(0), scalar_t(1), scalar_t(0), scalar_t(0),
                   scalar_t(0), scalar_t(0), scalar_t(1), scalar_t(0))
  ,m_near(scalar_t(0))
  ,m_far(scalar_t(1))
{
  update_transforms();
}
//----

template<typename T>
camera<T>::camera(const mat44<T> &view_to_proj_, scalar_t near_, scalar_t far_)
  :m_view_to_proj(view_to_proj_)
  ,m_view_to_world(scalar_t(1), scalar_t(0), scalar_t(0), scalar_t(0),
                   scalar_t(0), scalar_t(1), scalar_t(0), scalar_t(0),
                   scalar_t(0), scalar_t(0), scalar_t(1), scalar_t(0))
  ,m_near(near_)
  ,m_far(far_)
{
  update_transforms();
}
//----

template<typename T>
camera<T>::camera(const tform3<T> &view_to_world_, const mat44<T> &view_to_proj_, scalar_t near_, scalar_t far_)
  :m_view_to_proj(view_to_proj_)
  ,m_view_to_world(view_to_world_)
  ,m_near(near_)
  ,m_far(far_)
{
  update_transforms();
}
//----------------------------------------------------------------------------

template<typename T>
const mat44<T> &camera<T>::view_to_proj() const
{
  return m_view_to_proj;
}
//----

template<typename T>
const mat44<T> &camera<T>::proj_to_view() const
{
  return m_proj_to_view;
}
//----

template<typename T>
const tform3<T> &camera<T>::world_to_view() const
{
  return m_world_to_view;
}
//----

template<typename T>
const tform3<T> &camera<T>::view_to_world() const
{
  return m_view_to_world;
}
//----

template<typename T>
const mat44<T> &camera<T>::world_to_proj() const
{
  return m_world_to_proj;
}
//----

template<typename T>
const mat44<T> &camera<T>::proj_to_world() const
{
  return m_proj_to_world;
}
//----

template<typename T>
typename math<T>::scalar_t camera<T>::near_plane() const
{
  return m_near;
}
//----

template<typename T>
typename math<T>::scalar_t camera<T>::far_plane() const
{
  return m_far;
}
//----

template<typename T>
vec3<T> camera<T>::world_x() const
{
  return vec3<T>(m_view_to_world.x.x, m_view_to_world.x.y, m_view_to_world.x.z);
}
//----

template<typename T>
vec3<T> camera<T>::world_y() const
{
  return vec3<T>(m_view_to_world.y.x, m_view_to_world.y.y, m_view_to_world.y.z);
}
//----

template<typename T>
vec3<T> camera<T>::world_z() const
{
  return vec3<T>(m_view_to_world.z.x, m_view_to_world.z.y, m_view_to_world.z.z);
}
//----

template<typename T>
vec3<T> camera<T>::world_pos() const
{
  return vec3<T>(m_view_to_world.x.w, m_view_to_world.y.w, m_view_to_world.z.w);
}
//----------------------------------------------------------------------------

template<typename T>
void camera<T>::set_transform(const mat44<T> &view_to_proj_,
                              const tform3<T> &view_to_world_,
                              scalar_t near_,
                              scalar_t far_)
{
  m_view_to_proj=view_to_proj_;
  m_view_to_world=view_to_world_;
  m_near=near_;
  m_far=far_;
  update_transforms();
}
//----

template<typename T>
void camera<T>::set_view_to_proj(const mat44<T> &m_, scalar_t near_, scalar_t far_)
{
  m_view_to_proj=m_;
  m_near=near_;
  m_far=far_;
  update_transforms();
}
//----

template<typename T>
void camera<T>::set_view_to_world(const tform3<T> &t_)
{
  m_view_to_world=t_;
  update_transforms();
}
//----------------------------------------------------------------------------

template<typename T>
void camera<T>::update_transforms()
{
  // update transformation matrices
  m_proj_to_view=inv(m_view_to_proj);
  m_world_to_view=inv(m_view_to_world);
  m_world_to_proj=m_world_to_view*m_view_to_proj;
  m_proj_to_world=m_proj_to_view*m_view_to_world;
}
//----------------------------------------------------------------------------

template<typename T, typename U>
PFC_INLINE camera<T> to_camera(const camera<U> &c_)
{
  // convert between camera types
  typedef typename math<T>::scalar_t scalar_t;
  camera<T> c(to_tform3<T>(c_.view_to_world()),
              to_mat44<T>(c_.view_to_proj()),
              scalar_t(c_.near_plane()),
              scalar_t(c_.far_plane()));
  return c;
}
//----------------------------------------------------------------------------


//============================================================================
// projection matrix setup
//============================================================================
template<typename T>
mat44<T> perspective_matrix(typename math<T>::scalar_t fov_width_, typename math<T>::scalar_t aspect_ratio_, typename math<T>::scalar_t near_, typename math<T>::scalar_t far_, bool reversed_)
{
  // setup perspective matrix with FOV angles (radians) and near/far planes
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT(near_>=0);
  PFC_ASSERT(far_>near_);
  PFC_ASSERT(fov_width_<math<T>::pi);
  scalar_t q=far_*rcp(far_-near_);
  scalar_t b=scalar_t(0);
  if(reversed_)
  {
    q=-q;
    b=scalar_t(1);
  }
  scalar_t w=cot(fov_width_*scalar_t(0.5));
  scalar_t h=w*aspect_ratio_;
  return mat44f(          w, scalar_t(0), scalar_t(0), scalar_t(0),
                scalar_t(0),           h, scalar_t(0), scalar_t(0),
                scalar_t(0), scalar_t(0),         b+q, scalar_t(1),
                scalar_t(0), scalar_t(0),    -q*near_, scalar_t(0));
}
//----

template<typename T>
mat44<T> orthogonal_matrix(typename math<T>::scalar_t width_, typename math<T>::scalar_t aspect_ratio_, typename math<T>::scalar_t near_, typename math<T>::scalar_t far_, bool reversed_)
{
  // setup orthogonal projection matrix
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT(width_>0);
  PFC_ASSERT(far_>near_);
  scalar_t q=rcp(far_-near_);
  scalar_t b=scalar_t(0);
  if(reversed_)
  {
    q=-q;
    b=scalar_t(1);
  }
  scalar_t w=scalar_t(2)*rcp(width_);
  scalar_t h=w*aspect_ratio_;
  return mat44<T>(          w, scalar_t(0), scalar_t(0), scalar_t(0),
                  scalar_t(0),           h, scalar_t(0), scalar_t(0),
                  scalar_t(0), scalar_t(0),           q, scalar_t(0),
                  scalar_t(0), scalar_t(0),   b-q*near_, scalar_t(1));
}
//----------------------------------------------------------------------------


//============================================================================
// fov_width/height
//============================================================================
template<typename T>
PFC_INLINE typename math<T>::scalar_t fov_width(const mat44<T> &v2p_)
{
  return 2*atan(1/v2p_.x.x);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t fov_height(const mat44<T> &v2p_)
{
  return 2*atan(1/v2p_.y.y);
}
//----------------------------------------------------------------------------


//============================================================================
// calculate_world_ray
//============================================================================
template<typename T>
ray3<T> calculate_world_ray(const camera<T> &cam_, typename math<T>::scalar_t screen_x_, typename math<T>::scalar_t screen_y_)
{
  // calculate ray origin
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t nw=cam_.view_to_proj().z.w*cam_.near_plane()+cam_.view_to_proj().w.w;
  vec3<T> rpos=vec4<T>(screen_x_*nw, screen_y_*nw, scalar_t(0), nw)*cam_.proj_to_world();

  // calculate ray direction
  vec3<T> rdir;
  if(cam_.view_to_proj().z.w)
    rdir=unit(rpos-cam_.world_pos());
  else
    rdir=cam_.view_to_world().z_axis();

  // construct ray from origin & direction
  return ray3<T>(rpos, rdir);
}
//----------------------------------------------------------------------------


//============================================================================
// calculate_world_pos
//============================================================================
template<typename T>
vec3<T> calculate_world_pos(const camera<T> &cam_, typename math<T>::scalar_t screen_x_, typename math<T>::scalar_t screen_y_, typename math<T>::scalar_t proj_z_)
{
  // calculate projection space vector and transform it to world space
  typedef typename math<T>::scalar_t scalar_t;
  const mat44<T> &v2p=cam_.view_to_proj();
  scalar_t w=v2p.z.w*(proj_z_-v2p.w.z)*rcp(v2p.z.z)+v2p.w.w;
  vec4<T> posw=vec4<T>(screen_x_*w, screen_y_*w, proj_z_, w)*cam_.proj_to_world();
  return vec3<T>(posw.x, posw.y, posw.z);
}
//----------------------------------------------------------------------------


//============================================================================
// calculate_fov_planes
//============================================================================
template<typename T>
void calculate_fov_planes(plane3<T> planes_[6], const mat44<T> &p2w_)
{
  // calculate the 8 corned points for the FOV
  PFC_ASSERT(planes_);
  typedef typename math<T>::scalar_t scalar_t;
  const vec3<T> fov_points[]=
  {
    perspective_project(vec4f(scalar_t(-1), scalar_t(-1), scalar_t(0), scalar_t(1))*p2w_),
    perspective_project(vec4f(scalar_t(+1), scalar_t(-1), scalar_t(0), scalar_t(1))*p2w_),
    perspective_project(vec4f(scalar_t(-1), scalar_t(+1), scalar_t(0), scalar_t(1))*p2w_),
    perspective_project(vec4f(scalar_t(+1), scalar_t(+1), scalar_t(0), scalar_t(1))*p2w_),
    perspective_project(vec4f(scalar_t(-1), scalar_t(-1), scalar_t(1), scalar_t(1))*p2w_),
    perspective_project(vec4f(scalar_t(+1), scalar_t(-1), scalar_t(1), scalar_t(1))*p2w_),
    perspective_project(vec4f(scalar_t(-1), scalar_t(+1), scalar_t(1), scalar_t(1))*p2w_),
    perspective_project(vec4f(scalar_t(+1), scalar_t(+1), scalar_t(1), scalar_t(1))*p2w_),
  };

  // calculate plane normals (left, right, bottom, top, near, far)
  const vec3<T> lbf=fov_points[4]-fov_points[0];
  const vec3<T> rtf=fov_points[7]-fov_points[3];
  const vec3<T> r=fov_points[7]-fov_points[6];
  const vec3<T> u=fov_points[6]-fov_points[4];
  planes_[0].normal=unit(cross(lbf, u));
  planes_[1].normal=unit(cross(u, rtf));
  planes_[2].normal=unit(cross(r, lbf));
  planes_[3].normal=unit(cross(rtf, r));
  planes_[4].normal=unit(cross(u, r));
  planes_[5].normal=-planes_[4].normal;

  // calculate plane distances from origo
  planes_[0].d=dot(planes_[0].normal, fov_points[0]);
  planes_[1].d=dot(planes_[1].normal, fov_points[1]);
  planes_[2].d=dot(planes_[2].normal, fov_points[0]);
  planes_[3].d=dot(planes_[3].normal, fov_points[3]);
  planes_[4].d=dot(planes_[4].normal, fov_points[0]);
  planes_[5].d=dot(planes_[5].normal, fov_points[4]);
}
//----------------------------------------------------------------------------


//============================================================================
// calculate_screen_to_world_matrix
//============================================================================
// calculates matrix from screen space to world space. the generated matrix M
// can be used so that v'=v*M where v=[x, y, 1, w] and x=[0, vp_width_],
// y=[0, vp_height_], and w=depth from the camera origin (not near plane).
// it's assumed that the last column of the projection matrix is [0, 0, 1, 0]
template<typename T>
mat44<T> calculate_screen_to_world_matrix(const camera<T> &cam_, typename math<T>::scalar_t vp_width_, typename math<T>::scalar_t vp_height_)
{
  typedef typename math<T>::scalar_t scalar_t;
  mat44<T> s2w=mat44<T>(scalar_t( 2), scalar_t( 0), scalar_t(0), scalar_t(0),
                        scalar_t( 0), scalar_t(-2), scalar_t(0), scalar_t(0),
                        scalar_t( 0), scalar_t( 0), scalar_t(1), scalar_t(0),
                        scalar_t(-1), scalar_t( 1), scalar_t(0), scalar_t(1))*cam_.proj_to_world();
  s2w.x/=vp_width_;
  s2w.y/=vp_height_;
  s2w.w+=s2w.z*cam_.view_to_proj().z.z;
  s2w.z*=cam_.view_to_proj().w.z;
  transpose(s2w);
  return s2w;
}
//----------------------------------------------------------------------------


//============================================================================
// sphere_screen_extents
//============================================================================
// Calculates the exact screen extents xyzw=[left, bottom, right, top] in
// normalized screen coordinates [-1, 1] for a sphere in view space. For
// performance, the projection matrix (v2p) is assumed to be setup so that
// z.w=1 and w.w=0. The sphere is also assumed to be completely in front
// of the camera.
// This is an optimized implementation of paper "2D Polyhedral Bounds of a
// Clipped Perspective-Projected 3D Sphere": http://jcgt.org/published/0002/02/05/paper.pdf
template<typename T>
vec4<T> sphere_screen_extents(const vec3<T> &pos_, typename math<T>::scalar_t rad_, const mat44<T> &v2p_)
{
  // calculate horizontal extents
  PFC_ASSERT_PEDANTIC(v2p_.z.w==1 && v2p_.w.w==0);
  typedef typename math<T>::scalar_t scalar_t;
  vec4<T> res;
  scalar_t rad2=rad_*rad_, d=pos_.z*rad_;
  scalar_t hv=sqrt(pos_.x*pos_.x+pos_.z*pos_.z-rad2);
  scalar_t ha=pos_.x*hv, hb=pos_.x*rad_, hc=pos_.z*hv;
  res.x=(ha-d)*v2p_.x.x/(hc+hb); // left
  res.z=(ha+d)*v2p_.x.x/(hc-hb); // right

  // calculate vertical extents
  scalar_t vv=sqrt(pos_.y*pos_.y+pos_.z*pos_.z-rad2);
  scalar_t va=pos_.y*vv, vb=pos_.y*rad_, vc=pos_.z*vv;
  res.y=(va-d)*v2p_.y.y/(vc+vb); // bottom
  res.w=(va+d)*v2p_.y.y/(vc-vb); // top
  return res;
}
//----------------------------------------------------------------------------


//============================================================================
// compressed_rotation_spi
//============================================================================
template<class Storage>
compressed_rotation_spi<Storage>::compressed_rotation_spi()
{
  m_data.clear();
}
//----

template<class Storage>
compressed_rotation_spi<Storage>::compressed_rotation_spi(const quatf &q_)
{
  init_precise(q_);
}
//----

template<class Storage>
compressed_rotation_spi<Storage>::compressed_rotation_spi(const vec3f &axis_, float angle_)
{
  init_precise(axis_, angle_);
}
//----

template<class Storage>
bool compressed_rotation_spi<Storage>::init_precise(const quatf &q_)
{
  // get rotation axis from the quaternion
  PFC_ASSERT_MSG(abs(norm2(q_)-1.0f)<0.00001f, ("Rotation quaternion must be unit quaternion\r\n"));
  bool negated_z=q_.z<0.0f;
  quatf rot=negated_z?-q_:q_;
  vec3f axis=vec(rot);
  if(is_zero(axis))
  {
    m_data.clear();
    return false;
  }

  // initialize rotation with axis/angle pair
  init_precise(unit(axis), acos(rot.w)*2.0f);
  return negated_z;
}
//----

template<class Storage>
void compressed_rotation_spi<Storage>::init_precise(const vec3f &axis_, float angle_)
{
  // validate inputs
  enum {num_spiral_revolutions=Storage::num_spiral_revolutions};
  enum {max_spiral_angle_quantized=(1<<Storage::num_rotation_axis_bits)-1};
  static const float s_phi_to_spiral=float(4.0*num_spiral_revolutions);
  static const float s_spiral_to_phi=float(1.0/(4.0*num_spiral_revolutions));
  static const float s_max_spiral_angle=float(math<double>::two_pi*num_spiral_revolutions);
  static const float s_quantize_factor=float(double(max_spiral_angle_quantized)/sqr(math<double>::two_pi*num_spiral_revolutions));
  static const float s_dequantize_factor=float(sqr(math<double>::two_pi*num_spiral_revolutions)/double(max_spiral_angle_quantized));
  PFC_ASSERT_MSG(abs(norm2(axis_)-1.0f)<0.00001f, ("Rotation axis must be a unit vector\r\n"));
  PFC_ASSERT_MSG(angle_>=0.0f && angle_<=mathf::two_pi, ("Rotation angle (%f) must be in range [0, 2pi]\r\n", angle_));

  // calculate two spiral angles 2pi apart which are closest to the axis
  float z_spiral_angle=acos(axis_.z)*s_phi_to_spiral;
  float delta=cycle(atan2(axis_.y, axis_.x)-z_spiral_angle, mathf::two_pi);
  float spiral_angle_lo=max(z_spiral_angle+delta-mathf::two_pi, 0.0f);
  float spiral_angle_hi=min(z_spiral_angle+delta, s_max_spiral_angle);

  // test which one of the 4 potential quantized spiral angles is closest to the axis
  unsigned quant_spiral_angle_lo=unsigned(spiral_angle_lo*spiral_angle_lo*s_quantize_factor);
  unsigned quant_spiral_angle_hi=unsigned(spiral_angle_hi*spiral_angle_hi*s_quantize_factor);
  unsigned quant_spiral_angles[4]={quant_spiral_angle_lo,
                                   quant_spiral_angle_lo+1, 
                                   quant_spiral_angle_hi,
                                   min(quant_spiral_angle_hi+1, unsigned(max_spiral_angle_quantized))};
  float closest_dot=-2.0f;
  unsigned closest_guant_spiral_angle=0;
  for(unsigned i=0; i<4; ++i)
  {
    // extract vector from the quantized spiral angle
    float spiral_angle=sqrt(quant_spiral_angles[i]*s_dequantize_factor);
    float r, z, s, c;
    sincos(r, z, spiral_angle*s_spiral_to_phi);
    sincos(s, c, spiral_angle);

    // test if the vector has smallest deviation from the rotation axis
    float d=dot(vec3f(r*c, r*s, z), axis_);
    if(d>closest_dot)
    {
      closest_dot=d;
      closest_guant_spiral_angle=quant_spiral_angles[i];
    }
  }

  // pack quantized spiral angle & axis angle to the rotation data
  unsigned quant_axis_angle=unsigned(angle_*float(1<<Storage::num_rotation_angle_bits)/mathf::two_pi+0.5f)&((1<<Storage::num_rotation_angle_bits)-1);
  m_data.set_quant_spiral_angle(closest_guant_spiral_angle, quant_axis_angle);
}
//----------------------------------------------------------------------------

template<class Storage>
vec3f compressed_rotation_spi<Storage>::axis() const PFC_NOTHROW
{
  // extract rotation axis from spiral angle
  enum {num_spiral_revolutions=Storage::num_spiral_revolutions};
  enum {max_spiral_angle_quantized=(1<<Storage::num_rotation_axis_bits)-1};
  static const float s_spiral_to_phi=float(1.0/(4.0*num_spiral_revolutions));
  static const float s_dequantize_factor=float(sqr(math<double>::two_pi*num_spiral_revolutions)/max_spiral_angle_quantized);
  float spiral_angle=sqrt(m_data.quant_spiral_angle()*s_dequantize_factor);
  float r, z, s, c;
  sincos(r, z, spiral_angle*s_spiral_to_phi);
  sincos(s, c, spiral_angle);
  return vec3f(r*c, r*s, z);
}
//----

template<class Storage>
float compressed_rotation_spi<Storage>::angle() const
{
  static const float s_dequantize_factor=float(math<double>::two_pi/double(1<<Storage::num_rotation_angle_bits));
  return m_data.quant_rotation_angle()*s_dequantize_factor;
}
//----

template<class Storage>
quatf compressed_rotation_spi<Storage>::quat() const
{
  return axis_rot_u(axis(), angle());
}
//----------------------------------------------------------------------------


//============================================================================
// compressed_rotation_oct
//============================================================================
template<class Storage>
compressed_rotation_oct<Storage>::compressed_rotation_oct()
{
  m_data.clear();
}
//----

template<class Storage>
compressed_rotation_oct<Storage>::compressed_rotation_oct(const quatf &q_)
{
  init_fast(q_);
}
//----

template<class Storage>
compressed_rotation_oct<Storage>::compressed_rotation_oct(const vec3f &axis_, float angle_)
{
  init_fast(axis_, angle_);
}
//----

template<class Storage>
bool compressed_rotation_oct<Storage>::init_fast(const quatf &q_)
{
  // get rotation axis from the quaternion
  PFC_ASSERT_MSG(abs(norm2(q_)-1.0f)<0.00001f, ("Rotation quaternion must be unit quaternion\r\n"));
  bool negated_z=q_.z<0.0f;
  quatf rot=negated_z?-q_:q_;
  vec3f axis=vec(rot);
  if(is_zero(axis))
  {
    m_data.clear();
    return false;
  }

  // initialize the rotation using axis/angle
  init_fast(unit(axis), acos(rot.w)*2.0f);
  return negated_z;
}
//----

template<class Storage>
void compressed_rotation_oct<Storage>::init_fast(const vec3f &axis_, float angle_)
{
  // project axis to octahedron and quantize the projection & rotation angle
  PFC_ASSERT_PEDANTIC_MSG(abs(norm2(axis_)-1.0f)<0.00001f, ("Rotation axis must be a unit vector\r\n"));
  PFC_ASSERT_PEDANTIC_MSG(angle_>=0.0f && angle_<=mathf::two_pi, ("Rotation angle (%f) must be in range [0, 2pi]\r\n", angle_));
  vec2f p=vec2f(axis_)*rnorm_l1(axis_);
  unsigned quant_axis_angle=unsigned(angle_*float(1<<Storage::num_rotation_angle_bits)/mathf::two_pi+0.5f)&((1<<Storage::num_rotation_angle_bits)-1);;
  m_data.set_quant_oct_projection(unsigned((p.x+p.y)*((1<<(Storage::num_oct_projection_x_bits-1))-0.5f)+(1<<(Storage::num_oct_projection_x_bits-1))),
                                  unsigned((p.x-p.y)*((1<<(Storage::num_oct_projection_y_bits-1))-0.5f)+(1<<(Storage::num_oct_projection_y_bits-1))),
                                  quant_axis_angle);
}
//----------------------------------------------------------------------------

template<class Storage>
vec3f compressed_rotation_oct<Storage>::axis() const PFC_NOTHROW
{
  vec2i evq=m_data.quant_oct_projection();
  vec2f ev=madd(vec2f(float(evq.x), float(evq.y)), vec2f(2.0f/float((1<<Storage::num_oct_projection_x_bits)-1), 2.0f/float((1<<Storage::num_oct_projection_y_bits)-1)), -1.0f);
  ev=vec2f(ev.x+ev.y, ev.x-ev.y)*0.5f;
  return unit(vec3f(ev, 1.0f-norm_l1(ev)));
}
//----

template<class Storage>
float compressed_rotation_oct<Storage>::angle() const
{
  static const float s_dequantize_factor=float(math<double>::two_pi/double(1<<Storage::num_rotation_angle_bits));
  return m_data.quant_rotation_angle()*s_dequantize_factor;
}
//----

template<class Storage>
quatf compressed_rotation_oct<Storage>::quat() const
{
  return axis_rot_u(axis(), angle());
}
//----------------------------------------------------------------------------


//============================================================================
// compressed_rotation_storage_24
//============================================================================
unsigned compressed_rotation_storage_24::quant_rotation_angle() const
{
  return m_data[2];
}
//----

unsigned compressed_rotation_storage_24::quant_spiral_angle() const
{
  return m_data[0]+(m_data[1]<<8);
}
//----

vec2i compressed_rotation_storage_24::quant_oct_projection() const
{
  return vec2i(m_data[0], m_data[1]);
}
//----

void compressed_rotation_storage_24::clear()
{
  mem_zero(m_data, 3);
}
//----

void compressed_rotation_storage_24::set_quant_spiral_angle(unsigned quant_spiral_angle_, unsigned quant_rot_angle_)
{
  m_data[0]=uint8_t(quant_spiral_angle_);
  m_data[1]=uint8_t(quant_spiral_angle_>>8);
  m_data[2]=uint8_t(quant_rot_angle_);
}
//----

void compressed_rotation_storage_24::set_quant_oct_projection(unsigned quant_proj_x_, unsigned quant_proj_y_, unsigned quant_rot_angle_)
{
  m_data[0]=uint8_t(quant_proj_x_);
  m_data[1]=uint8_t(quant_proj_y_);
  m_data[2]=uint8_t(quant_rot_angle_);
}
//----------------------------------------------------------------------------


//============================================================================
// compressed_rotation_storage_32
//============================================================================
unsigned compressed_rotation_storage_32::quant_rotation_angle() const
{
//  return m_data>>num_spiral_angle_bits;
  return m_data>>num_rotation_axis_bits;
}
//----

unsigned compressed_rotation_storage_32::quant_spiral_angle() const
{
  return m_data&((1<<num_rotation_axis_bits)-1);
}
//----

vec2i compressed_rotation_storage_32::quant_oct_projection() const
{
  return vec2i(m_data&((1<<num_oct_projection_x_bits)-1), (m_data>>num_oct_projection_x_bits)&((1<<num_oct_projection_y_bits)-1));
}
//----

void compressed_rotation_storage_32::clear()
{
  m_data=0;
}
//----

void compressed_rotation_storage_32::set_quant_spiral_angle(unsigned quant_spiral_angle_, unsigned quant_rot_angle_)
{
  m_data=quant_spiral_angle_|(quant_rot_angle_<<num_rotation_axis_bits);
}
//----

void compressed_rotation_storage_32::set_quant_oct_projection(unsigned quant_proj_x_, unsigned quant_proj_y_, unsigned quant_rot_angle_)
{
  m_data=quant_proj_x_|(quant_proj_y_<<num_oct_projection_x_bits)|(quant_rot_angle_<<num_rotation_axis_bits);
}
//----------------------------------------------------------------------------
