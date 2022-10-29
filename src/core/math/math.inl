//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// scalar ops
//============================================================================
template<typename T>
PFC_INLINE T mul(T a_, T b_)
{
  // multiply
  return a_*b_;
}
//----

template<typename T>
PFC_INLINE T madd(T a_, T b_, T c_)
{
  // multiply-add
  return a_*b_+c_;
}
//----

template<typename T>
PFC_INLINE T rcp(T v_)
{
  // reciprocal
  PFC_ASSERT_PEDANTIC(v_!=0);
  return T(1)/v_;
}
//----

template<typename T>
PFC_INLINE T rcp_z(T v_)
{
  // reciprocal (return 0 for 0)
  return v_?T(1)/v_:0;
}
//----

template<typename T>
PFC_INLINE T floor(T v_)
{
  // round to floor
  return std::floor(v_);
}
//----

template<typename T>
PFC_INLINE T ceil(T v_)
{
  // round to ceil
  return std::ceil(v_);
}
//----

template<typename T>
PFC_INLINE T trunc(T v_)
{
  // round towards zero
  return T(int(v_));
}
//----

template<typename T>
PFC_INLINE T frc(T v_)
{
  // fractional
  return v_-T(int(v_));
}
//----

template<typename T>
PFC_INLINE T mod(T v_, T div_)
{
  // modulo
  return std::fmod(v_, div_);
}
//----

template<typename T>
PFC_INLINE T cycle(T v_, T cycle_)
{
  // cycle
  T v=T(std::fmod(v_, cycle_));
  return v<0?cycle_+v:v;
}
//----

template<typename T>
PFC_INLINE T cycle1(T v_)
{
  // cycle1
  return v_-T(int(v_))+(v_<0?T(1):0);
}
//----

template<typename T>
PFC_INLINE T sat(T v_)
{
  // saturate to range [0, 1]
  return v_<0?0:v_>T(1)?T(1):v_;
}
//----

template<typename T>
PFC_INLINE T ssat(T v_)
{
  // signed saturate to range [-1, 1]
  return v_<T(-1)?T(-1):v_>T(1)?T(1):v_;
}
//----

template<typename T>
PFC_INLINE T clamp(T v_, T min_, T max_)
{
  // clamp to range [min, max]
  PFC_ASSERT_PEDANTIC(min_<=max_);
  return v_<min_?min_:v_>max_?max_:v_;
}
//----

template<typename T>
PFC_INLINE T abs(T v_)
{
  // absolule
  return T(::abs(v_));
}
template<>
PFC_INLINE int64_t abs<int64_t>(int64_t v_)
{
  // absolule
  return v_<0?-v_:v_;
}
template<>
PFC_INLINE float abs<float>(float v_)
{
  // absolule
  return std::abs(v_);
}
template<>
PFC_INLINE double abs<double>(double v_)
{
  // absolule
  return std::abs(v_);
}
template<>
PFC_INLINE long double abs<long double>(long double v_)
{
  // absolule
  return std::abs(v_);
}
//----

template<typename T>
PFC_INLINE T sgn(T v_)
{
  // signum (v<0 => -1, v>0 => +1, v==0 => 0)
  return v_<0?T(-1):v_>0?T(1):0;
}
//----

template<typename T>
PFC_INLINE T sgn_zp(T v_)
{
  // signum (v<0 => -1, v>=0 => +1)
  return v_<0?T(-1):T(1);
}
//----

template<typename T>
PFC_INLINE T sqr(T v_)
{
  // square
  return v_*v_;
}
//----

template<typename T>
PFC_INLINE T cubic(T v_)
{
  // cubic
  return v_*v_*v_;
}
//----

template<typename T>
PFC_INLINE T sqrt(T v_)
{
  // square root
  PFC_ASSERT_PEDANTIC(v_>=0);
  return T(std::sqrt(v_));
}
//----

template<typename T>
PFC_INLINE T sqrt_z(T v_)
{
  // square root (return 0 for values <0)
  return v_>0?T(std::sqrt(v_)):0;
}
//----

template<typename T>
PFC_INLINE T cbrt(T v_)
{
  // cubic root
  return v_<0?-T(std::pow(-v_, T(1.0/3.0))):T(std::pow(v_, T(1.0/3.0)));
}
//----

template<typename T>
PFC_INLINE T rsqrt(T v_)
{
  // reciprocal square root
  PFC_ASSERT_PEDANTIC(v_>0);
  return T(1)/std::sqrt(v_);
}
//----

template<typename T>
PFC_INLINE T rsqrt_z(T v_)
{
  // reciprocal square root (return 0 for values <=0)
  return v_>0?T(1)/std::sqrt(v_):0;
}
//----

template<typename T>
PFC_INLINE T rcbrt(T v_)
{
  // reciprocal cubic root
  return v_<0?-std::pow(-v_, T(-1.0/3.0)):std::pow(v_, T(-1.0/3.0));
}
//----

template<typename T>
PFC_INLINE T rcbrt_z(T v_)
{
  // reciprocal cubic root (return 0 for 0)
  return v_?v_<0?-std::pow(-v_, T(-1.0/3.0)):std::pow(v_, T(-1.0/3.0)):0;
}
//----

template<typename T>
PFC_INLINE T norm(T v_)
{
  // 1d norm (absolute)
  return std::abs(v_);
}
//----

template<typename T>
PFC_INLINE T rnorm(T v_)
{
  // 1d norm reciprocal
  PFC_ASSERT_PEDANTIC(v_);
  return T(1)/std::abs(v_);
}
//----

template<typename T>
PFC_INLINE T rnorm_z(T v_)
{
  // 1d norm reciprocal (return 0 for 0)
  return v_?T(1)/std::abs(v_):0;
}
//----

template<typename T>
PFC_INLINE T norm2(T v_)
{
  // squared norm (square)
  return v_*v_;
}
//----

template<typename T>
PFC_INLINE T rnorm2(T v_)
{
  // reciprocal squared norm
  PFC_ASSERT_PEDANTIC(v_);
  return T(1)/(v_*v_);
}
//----

template<typename T>
PFC_INLINE T rnorm2_z(T v_)
{
  // reciprocal squared norm (return 0 for 0)
  return v_?T(1)/(v_*v_):0;
}
//----

template<typename T>
PFC_INLINE T norm_l1(T v_)
{
  // 1d L1-norm (absolute)
  return std::abs(v_);
}
//----

template<typename T>
PFC_INLINE T rnorm_l1(T v_)
{
  // 1d L1-norm reciprocal
  return T(1)/std::abs(v_);
}
//----

template<typename T>
PFC_INLINE T rnorm_l1_z(T v_)
{
  // 1d L1-norm reciprocal (return 0 for 0)
  return v_?T(1)/std::abs(v_):0;
}
//----

template<typename T>
PFC_INLINE T exp(T v_)
{
  // natural exponent
  return T(std::exp(v_));
}
//----

template<typename T>
PFC_INLINE T exp2(T v_)
{
  // 2^x
  return T(std::pow(T(2), v_));
}
//----

template<typename T>
PFC_INLINE T ln(T v_)
{
  // nature logarithm
  PFC_ASSERT_PEDANTIC(v_>0);
  return T(std::log(v_));
}
//----

template<typename T>
PFC_INLINE T log2(T v_)
{
  // base-2 logarithm
  PFC_ASSERT_PEDANTIC(v_>0);
  return T(std::log2(v_));
}
//----

template<typename T>
PFC_INLINE T log10(T v_)
{
  // base-10 logarithm
  PFC_ASSERT_PEDANTIC(v_>0);
  return T(std::log10(v_));
}
//----

template<typename T>
PFC_INLINE T pow(T s_, T p_)
{
  // rise value to power
  return T(std::pow(s_, p_));
}
//----

template<typename T>
PFC_INLINE T smoothstep(T t_)
{
  // smoothstep function: 3t^2-2t^3
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(t_>=0 && t_<=scalar_t(1));
  return t_*t_*(scalar_t(3)-scalar_t(2)*t_);
}
//----

template<typename T>
PFC_INLINE T smootherstep(T t_)
{
  // smootherstep function: 6t^5-15t^4+10t^3 (zero 2nd derivative at end points)
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(t_>=0 && t_<=scalar_t(1));
  return t_*t_*t_*(t_*(t_*scalar_t(6)-scalar_t(15))+scalar_t(10));
}
//----

template<typename T>
PFC_INLINE T lerp(T a_, T b_, T t_)
{
  // linear interpolate (f(t=0)=a, f(t=1)=b)
  return a_+(b_-a_)*t_;
}
//----

template<typename T>
PFC_INLINE T dot(T x_, T y_)
{
  // 1d dot product (multiply)
  return x_*y_;
}
//----

PFC_INLINE float32_t u16f_to_fp32(uint16_t u16f_)
{
  // convert unsigned 16-bit float to 32-bit float
  union convert
  {
    uint32_t u32;
    float32_t f32;
  } f2u;
  static const convert s_magic={(127+(127-15))<<23};
  f2u.u32=uint32_t(u16f_)<<13;
  f2u.f32*=s_magic.f32;
  return f2u.f32;
}
//----

PFC_INLINE float32_t s16f_to_fp32(uint16_t s16f_)
{
  // convert signed 16-bit float to 32-bit float
  union convert
  {
    uint32_t u32;
    float32_t f32;
  } f2u;
  static const convert s_magic={(127+(127-15))<<23};
  f2u.u32=uint32_t(s16f_)<<13;
  f2u.f32*=s_magic.f32;
  return f2u.f32;
}
//----

PFC_INLINE uint16_t fp32_to_u16f(float32_t v_)
{
  // convert 32-bit float to unsigned 16-bit float
  uint16_t v=uint16_t(((uint32_t&)v_)>>13);
  return v+(v?0x4000:0);
}
//----

PFC_INLINE uint16_t fp32_to_s16f(float32_t v_)
{
  // convert 32-bit float to signed 16-bit float
  uint16_t v=uint16_t(((uint32_t&)v_)>>13);
  return v+(v?0x4000:0);
}
//----------------------------------------------------------------------------


//============================================================================
// trigonometric scalar ops
//============================================================================
template<typename T>
PFC_INLINE T sin(T v_)
{
  // sine
  return std::sin(v_);
}
//----

template<typename T>
PFC_INLINE T cos(T v_)
{
  // cosine
  return std::cos(v_);
}
//----

template<typename T>
PFC_INLINE void sincos(T &sin_, T &cos_, T v_)
{
  // sine & cosine
  sin_=std::sin(v_);
  cos_=std::cos(v_);
}
//----

template<typename T>
PFC_INLINE T tan(T v_)
{
  // tangent
  return std::tan(v_);
}
//----

template<typename T>
PFC_INLINE T csc(T v_)
{
  // cosecant
  return T(1)/std::sin(v_);
}
//----

template<typename T>
PFC_INLINE T sec(T v_)
{
  // secant
  return T(1)/std::cos(v_);
}
//----

template<typename T>
PFC_INLINE T cot(T v_)
{
  // cotangent
  return T(1)/std::tan(v_);
}
//----

template<typename T>
PFC_INLINE T asin(T v_)
{
  // inverse sine
  PFC_ASSERT_PEDANTIC(v_>=T(-1) && v_<=T(1));
  return std::asin(v_);
}
//----

template<typename T>
PFC_INLINE T acos(T v_)
{
  // inverse cosine
  PFC_ASSERT_PEDANTIC(v_>=T(-1) && v_<=T(1));
  return std::acos(v_);
}
//----

template<typename T>
PFC_INLINE T atan(T v_)
{
  // inverse tangent
  return std::atan(v_);
}
//----

template<typename T>
PFC_INLINE T atan2(T y_, T x_)
{
  // four-quadrant inverse tangent
  return std::atan2(y_, x_);
}
//----

template<typename T>
PFC_INLINE T acsc(T v_)
{
  // inverse cosecant
  return std::asin(T(1)/v_);
}
//----

template<typename T>
PFC_INLINE T asec(T v_)
{
  // inverse secant
  return std::acos(T(1)/v_);
}
//----

template<typename T>
PFC_INLINE T acot(T v_)
{
  // inverse cotangent
  return std::atan(T(1)/v_);
}
//----

template<typename T>
PFC_INLINE T sinh(T v_)
{
  // hyperbolic sine
  return std::sinh(v_);
}
//----

template<typename T>
PFC_INLINE T cosh(T v_)
{
  // hyperbolic cosine
  return std::cosh(v_);
}
//----

template<typename T>
PFC_INLINE T tanh(T v_)
{
  // hyperbolic tangent
  return std::tanh(v_);
}
//----

template<typename T>
PFC_INLINE T csch(T v_)
{
  // hyperbolic cosecant
  return T(1)/std::sinh(v_);
}
//----

template<typename T>
PFC_INLINE T sech(T v_)
{
  // hyperbolic secant
  return T(1)/std::cosh(v_);
}
//----

template<typename T>
PFC_INLINE T coth(T v_)
{
  // hyperbolic cotangent
  return T(1)/std::tanh(v_);
}
//----

template<typename T>
PFC_INLINE T asinh(T v_)
{
  // inverse hyperbolic sine
  return std::log(v_+std::sqrt(v_*v_+T(1)));
}
//----

template<typename T>
PFC_INLINE T acosh(T v_)
{
  // inverse hyperbolic cosine
  PFC_ASSERT_PEDANTIC(v_>=1);
  return std::log(v_+std::sqrt(v_*v_-T(1)));
}
//----

template<typename T>
PFC_INLINE T atanh(T v_)
{
  // inverse hyperbolic tangent
  PFC_ASSERT_PEDANTIC(v_>T(-1) && v_<T(1));
  return T(0.5)*std::log((T(1)+v_)/(T(1)-v_));
}
//----

template<typename T>
PFC_INLINE T acsch(T v_)
{
  // inverse hyperbolic cosecant
  PFC_ASSERT_PEDANTIC(v_);
  T rv=T(1)/v_;
  return std::log(rv+std::sqrt(rv*rv+T(1)));
}
//----

template<typename T>
PFC_INLINE T asech(T v_)
{
  // inverse hyperbolic secant
  PFC_ASSERT_PEDANTIC(v_>0 && v_<=T(1));
  T rv=T(1)/v_;
  return std::log(rv+std::sqrt(rv*rv-T(1)));
}
//----

template<typename T>
PFC_INLINE T acoth(T v_)
{
  // inverse hyperbolic cotangent
  PFC_ASSERT_PEDANTIC(v_<T(-1) || v_>T(1));
  T rv=T(1)/v_;
  return T(0.5)*std::log((T(1)+rv)/(T(1)-rv));
}
//----------------------------------------------------------------------------


//============================================================================
// math constants
//============================================================================
// pi variants
template<typename T> const T math<T>::pi=T(3.14159265358979323846);
template<typename T> const T math<T>::quarter_pi=T(0.25*3.14159265358979323846);
template<typename T> const T math<T>::half_pi=T(0.5*3.14159265358979323846);
template<typename T> const T math<T>::two_pi=T(2.0*3.14159265358979323846);
template<typename T> const T math<T>::four_pi=T(4.0*3.14159265358979323846);
template<typename T> const T math<T>::rpi=T(1.0/3.14159265358979323846);
template<typename T> const T math<T>::quarter_rpi=T(0.25/3.14159265358979323846);
template<typename T> const T math<T>::half_rpi=T(0.5/3.14159265358979323846);
template<typename T> const T math<T>::two_rpi=T(2.0/3.14159265358979323846);
// square root variants
template<typename T> const T math<T>::sqrt2=T(1.4142135623730950488016887242097);
template<typename T> const T math<T>::sqrt3=T(1.7320508075688772935274463415059);
template<typename T> const T math<T>::rsqrt2=T(1.0/1.4142135623730950488016887242097);
template<typename T> const T math<T>::rsqrt3=T(1.0/1.7320508075688772935274463415059);
// angle conversion factors
template<typename T> const T math<T>::deg_to_rad=T(0.01745329251994329577);
template<typename T> const T math<T>::rad_to_deg=T(57.29577951308232087680);
//----------------------------------------------------------------------------


//============================================================================
// vec2
//============================================================================
template<typename T> const vec2<T> vec2<T>::s_zero(T(0));
template<typename T> const vec2<T> vec2<T>::s_one(T(1));
template<typename T> const vec2<T> vec2<T>::s_neg_one(T(-1));
//----------------------------------------------------------------------------

template<typename T>
vec2<T>::vec2()
{
}
//----

template<typename T>
vec2<T>::vec2(T s_)
{
  // init vector with scalar
  x=s_;
  y=s_;
}
//----

template<typename T>
vec2<T>::vec2(T x_, T y_)
{
  // init vector with scalars
  x=x_;
  y=y_;
}
//----

template<typename T>
vec2<T>::vec2(const vec3<T> &v_)
{
  // init vector from 3d vector
  x=v_.x;
  y=v_.y;
}
//----

template<typename T>
vec2<T>::vec2(const T *a_)
{
  // init vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
}
//----------------------------------------------------------------------------

template<typename T>
const T &vec2<T>::operator[](unsigned idx_) const
{
  // return reference to nth component (x=0, y=1)
  PFC_ASSERT_PEDANTIC(idx_<2);
  return reinterpret_cast<const T*>(this)[idx_];
}
//----

template<typename T>
T &vec2<T>::operator[](unsigned idx_)
{
  // return reference to nth component (x=0, y=1)
  PFC_ASSERT_PEDANTIC(idx_<2);
  return reinterpret_cast<T*>(this)[idx_];
}
//----

template<typename T>
void vec2<T>::set(T s_)
{
  // set vector with scalar
  x=s_;
  y=s_;
}
//----

template<typename T>
void vec2<T>::set(T x_, T y_)
{
  // set vector with scalars
  x=x_;
  y=y_;
}
//----

template<typename T>
void vec2<T>::set(const vec2<T> &v_)
{
  // set vector from vector
  x=v_.x;
  y=v_.y;
}
//----

template<typename T>
void vec2<T>::set(const vec3<T> &v_)
{
  // set vector from 3d vector
  x=v_.x;
  y=v_.y;
}
//----

template<typename T>
void vec2<T>::set(const T *a_)
{
  // set vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
}
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE bool is_zero(const vec2<T> &v_)
{
  // test for zero-vector
  return v_.x==0 && v_.y==0;
}
//----

template<typename T>
PFC_INLINE bool is_sat(const vec2<T> &v_)
{
  // test for saturated vector
  typedef typename math<T>::scalar_t scalar_t;
  return    v_.x>=0 && v_.x<=scalar_t(1)
         && v_.y>=0 && v_.y<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const vec2<T> &v_)
{
  // test for signed saturated vector
  typedef typename math<T>::scalar_t scalar_t;
  return    v_.x>=scalar_t(-1) && v_.x<=scalar_t(1)
         && v_.y>=scalar_t(-1) && v_.y<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool operator==(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // test for equality of vectors
  return v0_.x==v1_.x && v0_.y==v1_.y;
}
//----

template<typename T>
PFC_INLINE bool operator==(const vec2<T> &v_, typename math<T>::scalar_t s_)
{
  // test for equality of vector and scalar
  return v_.x==s_ && v_.y==s_;
}
//----

template<typename T>
PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const vec2<T> &v_)
{
  // test for equality of vector and scalar
  return s_==v_.x && s_==v_.y;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // test for inequality of vectors
  return v0_.x!=v1_.x || v0_.y!=v1_.y;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const vec2<T> &v_, typename math<T>::scalar_t s_)
{
  // test for inequality of vector and scalar
  return v_.x!=s_ || v_.y!=s_;
}
//----

template<typename T>
PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const vec2<T> &v_)
{
  // test for inequality of vector and scalar
  return s_!=v_.x || s_!=v_.y;
}
//----

template<typename T>
PFC_INLINE vec2<T> operator<(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v0_.x<v1_.x?scalar_t(1):0, v0_.y<v1_.y?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator<(const vec2<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x<s_?scalar_t(1):0, v_.y<s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator<(typename math<T>::scalar_t s_, const vec2<T> &v_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(s_<v_.x?scalar_t(1):0, s_<v_.y?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator>(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v0_.x>v1_.x?scalar_t(1):0, v0_.y>v1_.y?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator>(const vec2<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x>s_?scalar_t(1):0, v_.y>s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator>(typename math<T>::scalar_t s_, const vec2<T> &v_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(s_>v_.x?scalar_t(1):0, s_>v_.y?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator<=(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v0_.x<=v1_.x?scalar_t(1):0, v0_.y<=v1_.y?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator<=(const vec2<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x<=s_?scalar_t(1):0, v_.y<=s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator<=(typename math<T>::scalar_t s_, const vec2<T> &v_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(s_<=v_.x?scalar_t(1):0, s_<=v_.y?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator>=(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v0_.x>=v1_.x?scalar_t(1):0, v0_.y>=v1_.y?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator>=(const vec2<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x>=s_?scalar_t(1):0, v_.y>=s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator>=(typename math<T>::scalar_t s_, const vec2<T> &v_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(s_>=v_.x?scalar_t(1):0, s_>=v_.y?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> sel_eq(const vec2<T> &t0_, const vec2<T> &t1_, const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise equal vector select (t0_==t1_?v0_:v1_)
  return vec2<T>(t0_.x==t1_.x?v0_.x:v1_.x,
                 t0_.y==t1_.y?v0_.y:v1_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> sel_lt(const vec2<T> &t0_, const vec2<T> &t1_, const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise less-than vector select (t0_<t1_?v0_:v1_)
  return vec2<T>(t0_.x<t1_.x?v0_.x:v1_.x,
                 t0_.y<t1_.y?v0_.y:v1_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> sel_le(const vec2<T> &t0_, const vec2<T> &t1_, const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise less-or-equal vector select (t0_<=t1_?v0_:v1_)
  return vec2<T>(t0_.x<=t1_.x?v0_.x:v1_.x,
                 t0_.y<=t1_.y?v0_.y:v1_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> sel_eqz(const vec2<T> &t_, const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise equal-to-zero vector select (t_==0?v0_:v1_)
  return vec2<T>(t_.x==0?v0_.x:v1_.x,
                 t_.y==0?v0_.y:v1_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> sel_ltz(const vec2<T> &t_, const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise less-than-zero vector select (t_<0?v0_:v1_)
  return vec2<T>(t_.x<0?v0_.x:v1_.x,
                 t_.y<0?v0_.y:v1_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> sel_lez(const vec2<T> &t_, const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise less-or-equal-to-zero vector select (t_<=0?v0_:v1_)
  return vec2<T>(t_.x<=0?v0_.x:v1_.x,
                 t_.y<=0?v0_.y:v1_.y);
}
//----

template<typename T>
PFC_INLINE void operator+=(vec2<T> &vr_, const vec2<T> &v_)
{
  // add vector to vector
  vr_.x+=v_.x;
  vr_.y+=v_.y;
}
//----

template<typename T>
PFC_INLINE void operator+=(vec2<T> &vr_, typename math<T>::scalar_t s_)
{
  // add scalar to each component of the vector
  vr_.x+=s_;
  vr_.y+=s_;
}
//----

template<typename T>
PFC_INLINE void operator-=(vec2<T> &vr_, const vec2<T> &v_)
{
  // subtract vector from vector
  vr_.x-=v_.x;
  vr_.y-=v_.y;
}
//----

template<typename T>
PFC_INLINE void operator-=(vec2<T> &vr_, typename math<T>::scalar_t s_)
{
  // subtract scalar from each component of the vector
  vr_.x-=s_;
  vr_.y-=s_;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec2<T> &vr_, const vec2<T> &v_)
{
  // component-wise vector by vector multiply
  vr_.x*=v_.x;
  vr_.y*=v_.y;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec2<T> &vr_, typename math<T>::scalar_t s_)
{
  // multiply vector by scalar
  vr_.x*=s_;
  vr_.y*=s_;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec2<T> &vr_, const mat22<T> &m_)
{
  // multiply vector by matrix
  vec2<T> v(vr_);
  vr_.x=v.x*m_.x.x+v.y*m_.y.x;
  vr_.y=v.x*m_.x.y+v.y*m_.y.y;
}
//----

template<typename T>
PFC_INLINE void operator/=(vec2<T> &vr_, const vec2<T> &v_)
{
  // component-wise vector by vector division
  PFC_ASSERT_PEDANTIC(v_.x && v_.y);
  vr_.x/=v_.x;
  vr_.y/=v_.y;
}
//----

template<typename T>
PFC_INLINE void operator/=(vec2<T> &vr_, typename math<T>::scalar_t s_)
{
  // divide vector by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  vr_.x*=rs;
  vr_.y*=rs;
}
//----

template<typename T>
PFC_INLINE vec2<T> operator+(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // add vector to vector
  return vec2<T>(v0_.x+v1_.x, v0_.y+v1_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator+(const vec2<T> &v_, typename math<T>::scalar_t s_)
{
  // add scalar to each component of the vector
  return vec2<T>(v_.x+s_, v_.y+s_);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator+(typename math<T>::scalar_t s_, const vec2<T> &v_)
{
  // add each component of the vector to a scalar vector
  return vec2<T>(s_+v_.x, s_+v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator-(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // subtract vector from vector
  return vec2<T>(v0_.x-v1_.x, v0_.y-v1_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator-(const vec2<T> &v_, typename math<T>::scalar_t s_)
{
  // subtract scalar from each component of the vector
  return vec2<T>(v_.x-s_, v_.y-s_);
}
//----

template<typename T> PFC_INLINE vec2<T> operator-(typename math<T>::scalar_t s_, const vec2<T> &v_)
{
  // subtract each component of the vector from a scalar vector
  return vec2<T>(s_-v_.x, s_-v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator-(const vec2<T> &v_)
{
  // negate vector
  return vec2<T>(-v_.x, -v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator*(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise vector by vector multiply
  return vec2<T>(v0_.x*v1_.x, v0_.y*v1_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator*(const vec2<T> &v_, typename math<T>::scalar_t s_)
{
  // multiply vector by scalar
  return vec2<T>(v_.x*s_, v_.y*s_);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator*(typename math<T>::scalar_t s_, const vec2<T> &v_)
{
  // multiply vector by scalar
  return vec2<T>(v_.x*s_, v_.y*s_);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator*(const vec2<T> &v_, const mat22<T> &m_)
{
  // multiply vector my matrix
  return vec2<T>(v_.x*m_.x.x+v_.y*m_.y.x,
                 v_.x*m_.x.y+v_.y*m_.y.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator*(const mat22<T> &m_, const vec2<T> &v_)
{
  // multiply matrix by transposed vector
  return vec2<T>(v_.x*m_.x.x+v_.y*m_.x.y,
                 v_.x*m_.y.x+v_.y*m_.y.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator/(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise vector by vector division
  PFC_ASSERT_PEDANTIC(v1_.x && v1_.y);
  return vec2<T>(v0_.x/v1_.x, v0_.y/v1_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> operator/(const vec2<T> &v_, typename math<T>::scalar_t s_)
{
  // divide vector by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  return vec2<T>(v_.x*rs, v_.y*rs);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t min(const vec2<T> &v_)
{
  // minimum component value
  return min(v_.x, v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> min(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise min vector
  return vec2<T>(v0_.x<v1_.x?v0_.x:v1_.x,
                 v0_.y<v1_.y?v0_.y:v1_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> min(const vec2<T> &v0_, const vec2<T> &v1_, const vec2<T> &v2_)
{
  // component-wise min vector
  return vec2<T>(min(v0_.x, v1_.x, v2_.x),
                 min(v0_.y, v1_.y, v2_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> min(const vec2<T> &v0_, const vec2<T> &v1_, const vec2<T> &v2_, const vec2<T> &v3_)
{
  // component-wise min vector
  return vec2<T>(min(v0_.x, v1_.x, v2_.x, v3_.x),
                 min(v0_.y, v1_.y, v2_.y, v3_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> min(const vec2<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise min vector
  return vec2<T>(v_.x<s_?v_.x:s_,
                 v_.y<s_?v_.y:s_);
}
//----

template<typename T>
PFC_INLINE vec2<T> min(typename math<T>::scalar_t s_, const vec2<T> &v_)
{
  // component-wise min vector
  return vec2<T>(s_<v_.x?s_:v_.x,
                 s_<v_.y?s_:v_.y);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t max(const vec2<T> &v_)
{
  // maximum component value
  return max(v_.x, v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> max(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise max vector
  return vec2<T>(v0_.x>v1_.x?v0_.x:v1_.x,
                 v0_.y>v1_.y?v0_.y:v1_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> max(const vec2<T> &v0_, const vec2<T> &v1_, const vec2<T> &v2_)
{
  // component-wise max vector
  return vec2<T>(max(v0_.x, v1_.x, v2_.x),
                 max(v0_.y, v1_.y, v2_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> max(const vec2<T> &v0_, const vec2<T> &v1_, const vec2<T> &v2_, const vec2<T> &v3_)
{
  // component-wise max vector
  return vec2<T>(max(v0_.x, v1_.x, v2_.x, v3_.x),
                 max(v0_.y, v1_.y, v2_.y, v3_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> max(const vec2<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise max vector
  return vec2<T>(v_.x>s_?v_.x:s_,
                 v_.y>s_?v_.y:s_);
}
//----

template<typename T>
PFC_INLINE vec2<T> max(typename math<T>::scalar_t s_, const vec2<T> &v_)
{
  // component-wise max vector
  return vec2<T>(s_>v_.x?s_:v_.x,
                 s_>v_.y?s_:v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> mul(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // component-wise multiply: v0_*v1
  return vec2<T>(v0_.x*v1_.x, v0_.y*v1_.y);
}

template<typename T>
PFC_INLINE vec2<T> madd(const vec2<T> &vm0_, const vec2<T> &vm1_, const vec2<T> &va_)
{
  // component-wise multiply-add: vm0_*vm1_+va_
  return vec2<T>(vm0_.x*vm1_.x+va_.x, vm0_.y*vm1_.y+va_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> madd(const vec2<T> &vm_, typename math<T>::scalar_t sm_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: vm_*sm_+sa_
  return vec2<T>(vm_.x*sm_+sa_, vm_.y*sm_+sa_);
}
//----

template<typename T>
PFC_INLINE vec2<T> madd(const vec2<T> &vm0_, const vec2<T> &vm1_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: vm0_*vm1_+sa_
  return vec2<T>(vm0_.x*vm1_.x+sa_, vm0_.y*vm1_.y+sa_);
}
//----

template<typename T>
PFC_INLINE vec2<T> madd(const vec2<T> &vm_, typename math<T>::scalar_t sm_, const vec2<T> &va_)
{
  // component-wise multiply-add: vm_*sm_+va_
  return vec2<T>(vm_.x*sm_+va_.x, vm_.y*sm_+va_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> rcp(const vec2<T> &v_)
{
  // component-wise reciprocal
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(v_.x && v_.y);
  return vec2<T>(scalar_t(1)/v_.x, scalar_t(1)/v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> rcp_z(const vec2<T> &v_)
{
  // component-wise reciprocal (set to 0 for 0 components)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x?scalar_t(1)/v_.x:0, v_.y?scalar_t(1)/v_.y:0);
}
//----

template<typename T>
PFC_INLINE vec2<T> floor(const vec2<T> &v_)
{
  // component-wise floor
  return vec2<T>(std::floor(v_.x), std::floor(v_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> ceil(const vec2<T> &v_)
{
  // component-wise ceil
  return vec2<T>(std::ceil(v_.x), std::ceil(v_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> trunc(const vec2<T> &v_)
{
  // component-wise truncate
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(scalar_t(int(v_.x)), scalar_t(int(v_.y)));
}
//----

template<typename T>
PFC_INLINE vec2<T> frc(const vec2<T> &v_)
{
  // component-wise fractional
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x-scalar_t(int(v_.x)), v_.y-scalar_t(int(v_.y)));
}
//----

template<typename T>
PFC_INLINE vec2<T> mod(const vec2<T> &v_, typename math<T>::scalar_t div_)
{
  // component-wise modulo
  return vec2<T>(std::fmod(v_.x, div_), std::fmod(v_.y, div_));
}
//----

template<typename T>
PFC_INLINE vec2<T> cycle(const vec2<T> &v_, typename math<T>::scalar_t cycle_)
{
  // component-wise cycle
  return vec2<T>(std::fmod(v_.x, cycle_)+(v_.x<0?cycle_:0),
                 std::fmod(v_.y, cycle_)+(v_.y<0?cycle_:0));
}
//----

template<typename T>
PFC_INLINE vec2<T> cycle1(const vec2<T> &v_)
{
  // cycle1
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x-scalar_t(int(v_.x))+(v_.x<0?scalar_t(1):0),
                 v_.y-scalar_t(int(v_.y))+(v_.y<0?scalar_t(1):0));
}
//----

template<typename T>
PFC_INLINE vec2<T> sat(const vec2<T> &v_)
{
  // component-wise saturate
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x<0?0:v_.x>scalar_t(1)?scalar_t(1):v_.x,
                 v_.y<0?0:v_.y>scalar_t(1)?scalar_t(1):v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> ssat(const vec2<T> &v_)
{
  // component-wise signed saturate
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x<scalar_t(-1)?scalar_t(-1):v_.x>scalar_t(1)?scalar_t(1):v_.x,
                 v_.y<scalar_t(-1)?scalar_t(-1):v_.y>scalar_t(1)?scalar_t(1):v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> clamp(const vec2<T> &v_, const vec2<T> &min_, const vec2<T> &max_)
{
  // component-wise clamp (to vectors)
  return vec2<T>(v_.x<min_.x?min_.x:v_.x>max_.x?max_.x:v_.x,
                 v_.y<min_.y?min_.y:v_.y>max_.y?max_.y:v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> clamp(const vec2<T> &v_, typename math<T>::scalar_t min_, typename math<T>::scalar_t max_)
{
  // component-wise clamp (to scalars)
  return vec2<T>(v_.x<min_?min_:v_.x>max_?max_:v_.x,
                 v_.y<min_?min_:v_.y>max_?max_:v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> abs(const vec2<T> &v_)
{
  // component-wise absolute
  return vec2<T>(std::abs(v_.x), std::abs(v_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> sgn(const vec2<T> &v_)
{
  // component-wise signum (neg=-1, pos=+1, zero=0)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x<0?scalar_t(-1):v_.x>0?scalar_t(1):0,
                 v_.y<0?scalar_t(-1):v_.y>0?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> sgn_zp(const vec2<T> &v_)
{
  // component-wise signum (neg=-1, pos&zero=+1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x<0?scalar_t(-1):scalar_t(1), v_.y<0?scalar_t(-1):scalar_t(1));
}
//----

template<typename T>
PFC_INLINE vec2<T> sqr(const vec2<T> &v_)
{
  // component-wise square
  return vec2<T>(v_.x*v_.x, v_.y*v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> cubic(const vec2<T> &v_)
{
  // component-wise cubic
  return vec2<T>(v_.x*v_.x*v_.x, v_.y*v_.y*v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> sqrt(const vec2<T> &v_)
{
  // component-wise square root
  PFC_ASSERT_PEDANTIC(v_.x>=0 && v_.y>=0);
  return vec2<T>(std::sqrt(v_.x), std::sqrt(v_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> sqrt_z(const vec2<T> &v_)
{
  // component-wise square root (set to 0 for components less than zero)
  return vec2<T>(v_.x>0?std::sqrt(v_.x):0,
                 v_.y>0?std::sqrt(v_.y):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> cbrt(const vec2<T> &v_)
{
  // component-wise cubic root
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x<0?-std::pow(-v_.x, scalar_t(1.0/3.0)):std::pow(v_.x, scalar_t(1.0/3.0)),
                 v_.y<0?-std::pow(-v_.y, scalar_t(1.0/3.0)):std::pow(v_.y, scalar_t(1.0/3.0)));
}
//----

template<typename T>
PFC_INLINE vec2<T> rsqrt(const vec2<T> &v_)
{
  // component-wise reciprocal square root
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(v_.x>0 && v_.y>0);
  return vec2<T>(scalar_t(1)/std::sqrt(v_.x),
                 scalar_t(1)/std::sqrt(v_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> rsqrt_z(const vec2<T> &v_)
{
  // component-wise reciprocal square root (set to 0 for components less than or equal to zero)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x>0?scalar_t(1)/std::sqrt(v_.x):0,
                 v_.y>0?scalar_t(1)/std::sqrt(v_.y):0);
}
//----

template<typename T>
PFC_INLINE vec2<T> rcbrt(const vec2<T> &v_)
{
  // component-wise reciprocal cubic root
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x<0?-std::pow(-v_.x, scalar_t(-1.0/3.0)):std::pow(v_.x, scalar_t(-1.0/3.0)),
                 v_.y<0?-std::pow(-v_.y, scalar_t(-1.0/3.0)):std::pow(v_.y, scalar_t(-1.0/3.0)));
}
//----

template<typename T>
PFC_INLINE vec2<T> rcbrt_z(const vec2<T> &v_)
{
  // component-wise reciprocal cubic root (set to 0 for 0 components)
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(v_.x?v_.x<0?-std::pow(-v_.x, scalar_t(-1.0/3.0)):std::pow(v_.x, scalar_t(-1.0/3.0)):0,
                 v_.y?v_.y<0?-std::pow(-v_.y, scalar_t(-1.0/3.0)):std::pow(v_.y, scalar_t(-1.0/3.0)):0);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t norm(const vec2<T> &v_)
{
  // norm of the vector (=vector length)
  return std::sqrt(v_.x*v_.x+v_.y*v_.y);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm(const vec2<T> &v_)
{
  // reciprocal norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=v_.x*v_.x+v_.y*v_.y;
  PFC_ASSERT_PEDANTIC(n2);
  return scalar_t(1)/std::sqrt(n2);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm_z(const vec2<T> &v_)
{
  // reciprocal norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=v_.x*v_.x+v_.y*v_.y;
  return n2?scalar_t(1)/std::sqrt(n2):0;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t norm2(const vec2<T> &v_)
{
  // squared norm of the vector
  return v_.x*v_.x+v_.y*v_.y;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm2(const vec2<T> &v_)
{
  // reciprocal squared norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=v_.x*v_.x+v_.y*v_.y;
  PFC_ASSERT_PEDANTIC(n2);
  return scalar_t(1)/n2;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm2_z(const vec2<T> &v_)
{
  // reciprocal squared norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t v=v_.x*v_.x+v_.y*v_.y;
  return v?scalar_t(1)/v:0;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t norm_l1(const vec2<T> &v_)
{
  // L1-norm of the vector (Manhattan norm)
  return abs(v_.x)+abs(v_.y);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm_l1(const vec2<T> &v_)
{
  // reciprocal L1-norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  return scalar_t(1)/(abs(v_.x)+abs(v_.y));
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const vec2<T> &v_)
{
  // reciprocal L1-norm of the vector (return 0 if |v|=0)
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t v=abs(v_.x)+abs(v_.y);
  return v?scalar_t(1)/v:0;
}
//----

template<typename T>
PFC_INLINE vec2<T> exp(const vec2<T> &v_)
{
  // natural exponent
  return vec2<T>(std::exp(v_.x), std::exp(v_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> exp2(const vec2<T> &v_)
{
  // 2^x
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(std::pow(scalar_t(2), v_.x), std::pow(scalar_t(2), v_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> ln(const vec2<T> &v_)
{
  // natural logarithm
  return vec2<T>(std::log(v_.x), std::log(v_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> log2(const vec2<T> &v_)
{
  // base-2 logarithm
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(std::log2(v_.x), std::log2(v_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> log10(const vec2<T> &v_)
{
  // base-10 logarithm
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(std::log10(v_.x), std::log10(v_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> pow(const vec2<T> &v_, typename math<T>::scalar_t power_)
{
  // raises value to the given power
  return vec2<T>(std::pow(v_.x, power_), std::pow(v_.y, power_));
}
//----

template<typename T>
PFC_INLINE vec2<T> unit(const vec2<T> &v_)
{
  // unit vector of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=v_.x*v_.x+v_.y*v_.y;
  PFC_ASSERT_PEDANTIC(n2);
  scalar_t rs=scalar_t(1)/std::sqrt(n2);
  return vec2<T>(v_.x*rs, v_.y*rs);
}
//----

template<typename T>
PFC_INLINE vec2<T> unit_z(const vec2<T> &v_)
{
  // unit vector of the vector. if |v|=0, return v=[0, 0]
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t rs=v_.x*v_.x+v_.y*v_.y;
  if(!rs)
    return vec2<T>(0, 0);
  rs=scalar_t(1)/std::sqrt(rs);
  return vec2<T>(v_.x*rs, v_.y*rs);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t cross(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // cross-product of vectors
  return v0_.x*v1_.y-v0_.y*v1_.x;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t dot(const vec2<T> &v0_, const vec2<T> &v1_)
{
  // dot-product of vectors
  return v0_.x*v1_.x+v0_.y*v1_.y;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t dot1(const vec2<T> &v_)
{
  // dot-product with [1, 1]
  return v_.x+v_.y;
}
//----

template<typename T>
PFC_INLINE void neg(vec2<T> &v_)
{
  // negate the vector
  v_.x=-v_.x;
  v_.y=-v_.y;
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_u(vec2<T> &vr_, Rng &rng_)
{
  // random unit vector (even distribution on unit circle)
  sincos(vr_.x, vr_.y, typename math<T>::scalar_t(rng_.rand_ureal1())*math<T>::two_pi);
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_real1(vec2<T> &vr_, Rng &rng_)
{
  // random vector where each component is in range [-1, 1]
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=scalar_t(rng_.rand_real1());
  vr_.y=scalar_t(rng_.rand_real1());
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_ureal1(vec2<T> &vr_, Rng &rng_)
{
  // random vector where each component is in range [0, 1]
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=scalar_t(rng_.rand_ureal1());
  vr_.y=scalar_t(rng_.rand_ureal1());
}
//----

template<typename T>
PFC_INLINE vec2<T> smoothstep(const vec2<T> &v_)
{
  // component-wise smoothstep function
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(v_.x>=0 && v_.x<=scalar_t(1) && v_.y>=0 && v_.y<=scalar_t(1));
  return vec2<T>(v_.x*v_.x*(scalar_t(3)-scalar_t(2)*v_.x),
                 v_.y*v_.y*(scalar_t(3)-scalar_t(2)*v_.y));
}
//----

template<typename T>
PFC_INLINE vec2<T> smootherstep(const vec2<T> &v_)
{
  // component-wise smootherstep function
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(v_.x>=0 && v_.x<=scalar_t(1) && v_.y>=0 && v_.y<=scalar_t(1));
  return vec2<T>(v_.x*v_.x*v_.x*(v_.x*(v_.x*scalar_t(6)-scalar_t(15))+scalar_t(10)),
                 v_.y*v_.y*v_.y*(v_.y*(v_.y*scalar_t(6)-scalar_t(15))+scalar_t(10)));
}
//----

template<typename T>
PFC_INLINE vec2<T> lerp(const vec2<T> &v0_, const vec2<T> &v1_, typename math<T>::scalar_t t_)
{
  // linear vector interpolation. f(t=0)=v0, f(t=1)=v1
  return vec2<T>(v0_.x+(v1_.x-v0_.x)*t_,
                 v0_.y+(v1_.y-v0_.y)*t_);
}
//----

template<typename T>
PFC_INLINE vec2<T> reflect(const vec2<T> &v_, const vec2<T> &n_)
{
  // reflect vector about normal: v'=2*n*(v.n)/(n.n)-v
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t d=scalar_t(2)*(v_.x*n_.x+v_.y*n_.y)*rcp(n_.x*n_.x+n_.y*n_.y);
  return vec2<T>(d*n_.x-v_.x,
                 d*n_.y-v_.y);
}
//----

template<typename T>
PFC_INLINE vec2<T> reflect_u(const vec2<T> &v_, const vec2<T> &n_)
{
  // reflect vector about unit normal: v'=2*n*(v.n)-v
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t d=scalar_t(2)*(v_.x*n_.x+v_.y*n_.y);
  return vec2<T>(d*n_.x-v_.x,
                 d*n_.y-v_.y);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t perspective_project(const vec2<T> &v_)
{
  // perspective project vector
  return v_.x/v_.y;
}
//----

template<typename T, typename U>
PFC_INLINE vec2<T> to_vec2(const vec2<U> &v_)
{
  // convert between vec2 types
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>(scalar_t(v_.x), scalar_t(v_.y));
}
//----

namespace priv
{
  template<unsigned shuffle_, typename T>
  struct shuffle_vec2_helper
  {
    static vec2<T> shuffle(const vec2<T>&) {PFC_CTF_ERROR(T, invalid_vector_component_shuffle);}
  };
  #define PFC_VECTOR_SHUFFLE(shuffle__, x__, y__)\
  template<typename T> struct shuffle_vec2_helper<shuffle__, T>\
  {\
    static PFC_INLINE vec2<T> shuffle(const vec2<T> &v_) {return vec2<T>(v_.x__, v_.y__);}\
  };
  PFC_VECTOR_SHUFFLE(00, x, x);
  PFC_VECTOR_SHUFFLE(01, x, y);
  PFC_VECTOR_SHUFFLE(10, y, x);
  PFC_VECTOR_SHUFFLE(11, y, y);
  #undef PFC_VECTOR_SHUFFLE
} // namespace priv
//----

template<unsigned shuffle_, typename T>
PFC_INLINE vec2<T> shuffle(const vec2<T> &v_)
{
  return priv::shuffle_vec2_helper<shuffle_, T>::shuffle(v_);
}
//----------------------------------------------------------------------------


//============================================================================
// vec3
//============================================================================
template<typename T> const vec3<T> vec3<T>::s_zero(T(0));
template<typename T> const vec3<T> vec3<T>::s_one(T(1));
template<typename T> const vec3<T> vec3<T>::s_neg_one(T(-1));
//----------------------------------------------------------------------------

template<typename T>
vec3<T>::vec3()
{
}
//----

template<typename T>
vec3<T>::vec3(T s_)
{
  // init vector with scalar
  x=s_;
  y=s_;
  z=s_;
}
//----

template<typename T>
vec3<T>::vec3(T x_, T y_, T z_)
{
  // init vector with scalars
  x=x_;
  y=y_;
  z=z_;
}
//----

template<typename T>
vec3<T>::vec3(const vec2<T> &v_, T z_)
{
  // init vector with 2d vector and z
  x=v_.x;
  y=v_.y;
  z=z_;
}
//----

template<typename T>
vec3<T>::vec3(const vec4<T> &v_)
{
  // init vector with 4d vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
}
//----

template<typename T>
vec3<T>::vec3(const T *a_)
{
  // init vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
  z=a_[2];
}
//----------------------------------------------------------------------------

template<typename T>
const T &vec3<T>::operator[](unsigned idx_) const
{
  // return reference to nth component (x=0, y=1, z=2)
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<const T*>(this)[idx_];
}
//----

template<typename T>
T &vec3<T>::operator[](unsigned idx_)
{
  // return reference to nth component (x=0, y=1, z=2)
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<T*>(this)[idx_];
}
//----

template<typename T>
void vec3<T>::set(T s_)
{
  // set vector with scalar
  x=s_;
  y=s_;
  z=s_;
}
//----

template<typename T>
void vec3<T>::set(T x_, T y_, T z_)
{
  // set vector with scalars
  x=x_;
  y=y_;
  z=z_;
}
//----

template<typename T>
void vec3<T>::set(const vec2<T> &v_, T z_)
{
  // set vector with 2d vector and z
  x=v_.x;
  y=v_.y;
  z=z_;
}
//----

template<typename T>
void vec3<T>::set(const vec3<T> &v_)
{
  // set vector with 3d vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
}
//----

template<typename T>
void vec3<T>::set(const vec4<T> &v_)
{
  // set vector with 4d vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
}
//----

template<typename T>
void vec3<T>::set(const T *a_)
{
  // set vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
  z=a_[2];
}
//----------------------------------------------------------------------------


//============================================================================
// vec3<vec32_t>
//============================================================================
vec3<vec32_t>::vec3()
{
}
//----

vec3<vec32_t>::vec3(uint8_t s_)
{
  // init vector with scalar
  x=s_;
  y=s_;
  z=s_;
}
//----

vec3<vec32_t>::vec3(uint8_t x_, uint8_t y_, uint8_t z_)
{
  // init vector with scalars
  x=x_;
  y=y_;
  z=z_;
}
//----

vec3<vec32_t>::vec3(const vec2<uint8_t> &v_, uint8_t z_)
{
  // init vector with 2d vector and z
  x=v_.x;
  y=v_.y;
  z=z_;
}
//----

vec3<vec32_t>::vec3(const uint8_t *a_)
{
  // init vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
  z=a_[2];
}
//----------------------------------------------------------------------------

const uint8_t &vec3<vec32_t>::operator[](unsigned idx_) const
{
  // return reference to nth component (x=0, y=1, z=2)
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<const uint8_t*>(this)[idx_];
}
//----

uint8_t &vec3<vec32_t>::operator[](unsigned idx_)
{
  // return reference to nth component (x=0, y=1, z=2)
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<uint8_t*>(this)[idx_];
}
//----

void vec3<vec32_t>::set(uint8_t s_)
{
  // set vector with scalar
  x=s_;
  y=s_;
  z=s_;
}
//----

void vec3<vec32_t>::set(uint8_t x_, uint8_t y_, uint8_t z_)
{
  // set vector with scalars
  x=x_;
  y=y_;
  z=z_;
}
//----

void vec3<vec32_t>::set(const vec2<uint8_t> &v_, uint8_t z_)
{
  // set vector with 2d vector and z
  x=v_.x;
  y=v_.y;
  z=z_;
}
//----

void vec3<vec32_t>::set(const vec3<vec32_t> &v_)
{
  // set vector with 2d vector and z
  x=v_.x;
  y=v_.y;
  z=v_.z;
}
//----

void vec3<vec32_t>::set(const uint8_t *a_)
{
  // set vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
  z=a_[2];
}
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE bool is_zero(const vec3<T> &v_)
{
  // test for zero-vector
  return v_.x==0 && v_.y==0 && v_.z==0;
}
//----

template<typename T>
PFC_INLINE bool is_sat(const vec3<T> &v_)
{
  // test for saturated vector
  typedef typename math<T>::scalar_t scalar_t;
  return    v_.x>=0 && v_.x<=scalar_t(1)
         && v_.y>=0 && v_.y<=scalar_t(1)
         && v_.z>=0 && v_.z<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const vec3<T> &v_)
{
  // test for signed saturated vector
  typedef typename math<T>::scalar_t scalar_t;
  return    v_.x>=scalar_t(-1) && v_.x<=scalar_t(1)
         && v_.y>=scalar_t(-1) && v_.y<=scalar_t(1)
         && v_.z>=scalar_t(-1) && v_.z<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool operator==(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // test for equality of vectors
  return v0_.x==v1_.x && v0_.y==v1_.y && v0_.z==v1_.z;
}
//----

template<typename T>
PFC_INLINE bool operator==(const vec3<T> &v_, typename math<T>::scalar_t s_)
{
  // test for equality of vector and scalar
  return v_.x==s_ && v_.y==s_ && v_.z==s_;
}
//----

template<typename T>
PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const vec3<T> &v_)
{
  // test for equality of vector and scalar
  return s_==v_.x && s_==v_.y && s_==v_.z;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // test for inequality of vectors
  return v0_.x!=v1_.x || v0_.y!=v1_.y || v0_.z!=v1_.z;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const vec3<T> &v_, typename math<T>::scalar_t s_)
{
  // test for inequality of vector and scalar
  return v_.x!=s_ || v_.y!=s_ || v_.z!=s_;
}
//----

template<typename T>
PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const vec3<T> &v_)
{
  // test for inequality of vector and scalar
  return s_!=v_.x || s_!=v_.y || s_!=v_.z;
}
//----

template<typename T>
PFC_INLINE vec3<T> operator<(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v0_.x<v1_.x?scalar_t(1):0, v0_.y<v1_.y?scalar_t(1):0, v0_.z<v1_.z?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator<(const vec3<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x<s_?scalar_t(1):0, v_.y<s_?scalar_t(1):0, v_.z<s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator<(typename math<T>::scalar_t s_, const vec3<T> &v_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(s_<v_.x?scalar_t(1):0, s_<v_.y?scalar_t(1):0, s_<v_.z?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator>(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v0_.x>v1_.x?scalar_t(1):0, v0_.y>v1_.y?scalar_t(1):0, v0_.z>v1_.z?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator>(const vec3<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x>s_?scalar_t(1):0, v_.y>s_?scalar_t(1):0, v_.z>s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator>(typename math<T>::scalar_t s_, const vec3<T> &v_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(s_>v_.x?scalar_t(1):0, s_>v_.y?scalar_t(1):0, s_>v_.z?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator<=(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v0_.x<=v1_.x?scalar_t(1):0, v0_.y<=v1_.y?scalar_t(1):0, v0_.z<=v1_.z?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator<=(const vec3<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x<=s_?scalar_t(1):0, v_.y<=s_?scalar_t(1):0, v_.z<=s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator<=(typename math<T>::scalar_t s_, const vec3<T> &v_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(s_<=v_.x?scalar_t(1):0, s_<=v_.y?scalar_t(1):0, s_<=v_.z?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator>=(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v0_.x>=v1_.x?scalar_t(1):0, v0_.y>=v1_.y?scalar_t(1):0, v0_.z>=v1_.z?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator>=(const vec3<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x>=s_?scalar_t(1):0, v_.y>=s_?scalar_t(1):0, v_.z>=s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator>=(typename math<T>::scalar_t s_, const vec3<T> &v_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(s_>=v_.x?scalar_t(1):0, s_>=v_.y?scalar_t(1):0, s_>=v_.z?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> sel_eq(const vec3<T> &t0_, const vec3<T> &t1_, const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise equal vector select (t0_==t1_?v0_:v1_)
  return vec3<T>(t0_.x==t1_.x?v0_.x:v1_.x,
                 t0_.y==t1_.y?v0_.y:v1_.y,
                 t0_.z==t1_.z?v0_.z:v1_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> sel_lt(const vec3<T> &t0_, const vec3<T> &t1_, const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise less-than vector select (t0_<t1_?v0_:v1_)
  return vec3<T>(t0_.x<t1_.x?v0_.x:v1_.x,
                 t0_.y<t1_.y?v0_.y:v1_.y,
                 t0_.z<t1_.z?v0_.z:v1_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> sel_le(const vec3<T> &t0_, const vec3<T> &t1_, const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise less-or-equal vector select (t0_<=t1_?v0_:v1_)
  return vec3<T>(t0_.x<=t1_.x?v0_.x:v1_.x,
                 t0_.y<=t1_.y?v0_.y:v1_.y,
                 t0_.z<=t1_.z?v0_.z:v1_.z);
}
//----

template<typename T> PFC_INLINE vec3<T> sel_eqz(const vec3<T> &t_, const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise equal-to-zero vector select (t_==0?v0_:v1_)
  return vec3<T>(t_.x==0?v0_.x:v1_.x,
                 t_.y==0?v0_.y:v1_.y,
                 t_.z==0?v0_.z:v1_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> sel_ltz(const vec3<T> &t_, const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise less-than-zero vector select (t_<0?v0_:v1_)
  return vec3<T>(t_.x<0?v0_.x:v1_.x,
                 t_.y<0?v0_.y:v1_.y,
                 t_.z<0?v0_.z:v1_.z);
}
//----

template<typename T> PFC_INLINE vec3<T> sel_lez(const vec3<T> &t_, const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise less-or-equal-to-zero vector select (t_<=0?v0_:v1_)
  return vec3<T>(t_.x<=0?v0_.x:v1_.x,
                 t_.y<=0?v0_.y:v1_.y,
                 t_.z<=0?v0_.z:v1_.z);
}
//----

template<typename T>
PFC_INLINE void operator+=(vec3<T> &vr_, const vec3<T> &v_)
{
  // add vector to vector
  vr_.x+=v_.x;
  vr_.y+=v_.y;
  vr_.z+=v_.z;
}
//----

template<typename T>
PFC_INLINE void operator+=(vec3<T> &vr_, typename math<T>::scalar_t s_)
{
  // add scalar to each component of the vector
  vr_.x+=s_;
  vr_.y+=s_;
  vr_.z+=s_;
}
//----

template<typename T>
PFC_INLINE void operator-=(vec3<T> &vr_, const vec3<T> &v_)
{
  // subtract vector from vector
  vr_.x-=v_.x;
  vr_.y-=v_.y;
  vr_.z-=v_.z;
}
//----

template<typename T>
PFC_INLINE void operator-=(vec3<T> &vr_, typename math<T>::scalar_t s_)
{
  // subtract scalar from each component of the vector
  vr_.x-=s_;
  vr_.y-=s_;
  vr_.z-=s_;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec3<T> &vr_, const vec3<T> &v_)
{
  // component-wise vector by vector multiply
  vr_.x*=v_.x;
  vr_.y*=v_.y;
  vr_.z*=v_.z;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec3<T> &vr_, typename math<T>::scalar_t s_)
{
  // multiply vector by scalar
  vr_.x*=s_;
  vr_.y*=s_;
  vr_.z*=s_;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec3<T> &vr_, const mat33<T> &m_)
{
  // multiply vector by matrix
  vec3<T> v(vr_);
  vr_.x=v.x*m_.x.x+v.y*m_.y.x+v.z*m_.z.x;
  vr_.y=v.x*m_.x.y+v.y*m_.y.y+v.z*m_.z.y;
  vr_.z=v.x*m_.x.z+v.y*m_.y.z+v.z*m_.z.z;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec3<T> &vr_, const mat44<T> &m_)
{
  // multiply vector by 4x4 matrix (assume vector w=1)
  vec3<T> v(vr_);
  vr_.x=v.x*m_.x.x+v.y*m_.y.x+v.z*m_.z.x+m_.w.x;
  vr_.y=v.x*m_.x.y+v.y*m_.y.y+v.z*m_.z.y+m_.w.y;
  vr_.z=v.x*m_.x.z+v.y*m_.y.z+v.z*m_.z.z+m_.w.z;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec3<T> &vr_, const quat<T> &q_)
{
  // transform the vector by quaternion: v'=2(qv x (qv x v + wv)) + v
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> s(q_.y*vr_.z-q_.z*vr_.y+q_.w*vr_.x,
            q_.z*vr_.x-q_.x*vr_.z+q_.w*vr_.y,
            q_.x*vr_.y-q_.y*vr_.x+q_.w*vr_.z);
  vr_.x+=scalar_t(2)*(q_.y*s.z-q_.z*s.y);
  vr_.y+=scalar_t(2)*(q_.z*s.x-q_.x*s.z);
  vr_.z+=scalar_t(2)*(q_.x*s.y-q_.y*s.x);
}
//----

template<typename T>
PFC_INLINE void operator/=(vec3<T> &vr_, const vec3<T> &v_)
{
  // component-wise vector by vector division
  PFC_ASSERT_PEDANTIC(v_.x && v_.y && v_.z);
  vr_.x/=v_.x;
  vr_.y/=v_.y;
  vr_.z/=v_.z;
}
//----

template<typename T>
PFC_INLINE void operator/=(vec3<T> &vr_, typename math<T>::scalar_t s_)
{
  // divide vector by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  vr_.x*=rs;
  vr_.y*=rs;
  vr_.z*=rs;
}
//----

template<typename T>
PFC_INLINE vec3<T> operator+(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // add vector to vector
  return vec3<T>(v0_.x+v1_.x, v0_.y+v1_.y, v0_.z+v1_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator+(const vec3<T> &v_, typename math<T>::scalar_t s_)
{
  // add scalar to each component of the vector
  return vec3<T>(v_.x+s_, v_.y+s_, v_.z+s_);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator+(typename math<T>::scalar_t s_, const vec3<T> &v_)
{
  // add each component of the vector to a scalar vector
  return vec3<T>(s_+v_.x, s_+v_.y, s_+v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator-(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // subtract vector from vector
  return vec3<T>(v0_.x-v1_.x, v0_.y-v1_.y, v0_.z-v1_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator-(const vec3<T> &v_, typename math<T>::scalar_t s_)
{
  // subtract scalar from each component of the vector
  return vec3<T>(v_.x-s_, v_.y-s_, v_.z-s_);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator-(typename math<T>::scalar_t s_, const vec3<T> &v_)
{
  // subtract each component of the vector from a scalar vector
  return vec3<T>(s_-v_.x, s_-v_.y, s_-v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator-(const vec3<T> &v_)
{
  // negate vector
  return vec3<T>(-v_.x, -v_.y, -v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator*(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise vector by vector multiply
  return vec3<T>(v0_.x*v1_.x, v0_.y*v1_.y, v0_.z*v1_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator*(const vec3<T> &v_, typename math<T>::scalar_t s_)
{
  // multiply vector by scalar
  return vec3<T>(v_.x*s_, v_.y*s_, v_.z*s_);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator*(typename math<T>::scalar_t s_, const vec3<T> &v_)
{
  // multiply vector by scalar
  return vec3<T>(v_.x*s_, v_.y*s_, v_.z*s_);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator*(const vec3<T> &v_, const mat33<T> &m_)
{
  // multiply vector my matrix
  return vec3<T>(v_.x*m_.x.x+v_.y*m_.y.x+v_.z*m_.z.x,
                 v_.x*m_.x.y+v_.y*m_.y.y+v_.z*m_.z.y,
                 v_.x*m_.x.z+v_.y*m_.y.z+v_.z*m_.z.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator*(const mat33<T> &m_, const vec3<T> &v_)
{
  // multiply matrix by transposed vector
  return vec3<T>(v_.x*m_.x.x+v_.y*m_.x.y+v_.z*m_.x.z,
                 v_.x*m_.y.x+v_.y*m_.y.y+v_.z*m_.y.z,
                 v_.x*m_.z.x+v_.y*m_.z.y+v_.z*m_.z.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator*(const vec3<T> &v_, const mat44<T> &m_)
{
  // multiply vector by 4x4 matrix (assume vector w=1)
  return vec3<T>(v_.x*m_.x.x+v_.y*m_.y.x+v_.z*m_.z.x+m_.w.x,
                 v_.x*m_.x.y+v_.y*m_.y.y+v_.z*m_.z.y+m_.w.y,
                 v_.x*m_.x.z+v_.y*m_.y.z+v_.z*m_.z.z+m_.w.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator*(const mat44<T> &m_, const vec3<T> &v_)
{
  // multiply 4x4 matrix by transposed vector (assume vector w=1)
  return vec3<T>(v_.x*m_.x.x+v_.y*m_.x.y+v_.z*m_.x.z+m_.x.w,
                 v_.x*m_.y.x+v_.y*m_.y.y+v_.z*m_.y.z+m_.y.w,
                 v_.x*m_.z.x+v_.y*m_.z.y+v_.z*m_.z.z+m_.z.w);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator*(const vec3<T> &v_, const quat<T> &q_)
{
  // transform the vector by quaternion: v'=2(qv x (qv x v + wv)) + v
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> s(q_.y*v_.z-q_.z*v_.y+q_.w*v_.x,
            q_.z*v_.x-q_.x*v_.z+q_.w*v_.y,
            q_.x*v_.y-q_.y*v_.x+q_.w*v_.z);
  return vec3<T>(scalar_t(2)*(q_.y*s.z-q_.z*s.y)+v_.x,
                 scalar_t(2)*(q_.z*s.x-q_.x*s.z)+v_.y,
                 scalar_t(2)*(q_.x*s.y-q_.y*s.x)+v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator/(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise vector by vector division
  PFC_ASSERT_PEDANTIC(v1_.x && v1_.y && v1_.z);
  return vec3<T>(v0_.x/v1_.x, v0_.y/v1_.y, v0_.z/v1_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> operator/(const vec3<T> &v_, typename math<T>::scalar_t s_)
{
  // divide vector by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  return vec3<T>(v_.x*rs, v_.y*rs, v_.z*rs);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t min(const vec3<T> &v_)
{
  // minimum component value
  return min(v_.x, v_.y, v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> min(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise min vector
  return vec3<T>(v0_.x<v1_.x?v0_.x:v1_.x,
                 v0_.y<v1_.y?v0_.y:v1_.y,
                 v0_.z<v1_.z?v0_.z:v1_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> min(const vec3<T> &v0_, const vec3<T> &v1_, const vec3<T> &v2_)
{
  // component-wise min vector
  return vec3<T>(min(v0_.x, v1_.x, v2_.x),
                 min(v0_.y, v1_.y, v2_.y),
                 min(v0_.z, v1_.z, v2_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> min(const vec3<T> &v0_, const vec3<T> &v1_, const vec3<T> &v2_, const vec3<T> &v3_)
{
  // component-wise min vector
  return vec3<T>(min(v0_.x, v1_.x, v2_.x, v3_.x),
                 min(v0_.y, v1_.y, v2_.y, v3_.y),
                 min(v0_.z, v1_.z, v2_.z, v3_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> min(const vec3<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise min vector
  return vec3<T>(v_.x<s_?v_.x:s_,
                 v_.y<s_?v_.y:s_,
                 v_.z<s_?v_.z:s_);
}
//----

template<typename T>
PFC_INLINE vec3<T> min(typename math<T>::scalar_t s_, const vec3<T> &v_)
{
  // component-wise min vector
  return vec3<T>(s_<v_.x?s_:v_.x,
                 s_<v_.y?s_:v_.y,
                 s_<v_.z?s_:v_.z);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t max(const vec3<T> &v_)
{
  // maximum component value
  return max(v_.x, v_.y, v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> max(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise max vector
  return vec3<T>(v0_.x>v1_.x?v0_.x:v1_.x,
                 v0_.y>v1_.y?v0_.y:v1_.y,
                 v0_.z>v1_.z?v0_.z:v1_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> max(const vec3<T> &v0_, const vec3<T> &v1_, const vec3<T> &v2_)
{
  // component-wise max vector
  return vec3<T>(max(v0_.x, v1_.x, v2_.x),
                 max(v0_.y, v1_.y, v2_.y),
                 max(v0_.z, v1_.z, v2_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> max(const vec3<T> &v0_, const vec3<T> &v1_, const vec3<T> &v2_, const vec3<T> &v3_)
{
  // component-wise max vector
  return vec3<T>(max(v0_.x, v1_.x, v2_.x, v3_.x),
                 max(v0_.y, v1_.y, v2_.y, v3_.y),
                 max(v0_.z, v1_.z, v2_.z, v3_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> max(const vec3<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise max vector
  return vec3<T>(v_.x>s_?v_.x:s_,
                 v_.y>s_?v_.y:s_,
                 v_.z>s_?v_.z:s_);
}
//----

template<typename T>
PFC_INLINE vec3<T> max(typename math<T>::scalar_t s_, const vec3<T> &v_)
{
  // component-wise max vector
  return vec3<T>(s_>v_.x?s_:v_.x,
                 s_>v_.y?s_:v_.y,
                 s_>v_.z?s_:v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> mul(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // component-wise multiply: v0_*v1_
  return vec3<T>(v0_.x*v1_.x, v0_.y*v1_.y, v0_.z*v1_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> madd(const vec3<T> &vm0_, const vec3<T> &vm1_, const vec3<T> &va_)
{
  // component-wise multiply-add: vm0_*vm1_+va_
  return vec3<T>(vm0_.x*vm1_.x+va_.x, vm0_.y*vm1_.y+va_.y, vm0_.z*vm1_.z+va_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> madd(const vec3<T> &vm_, typename math<T>::scalar_t sm_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: vm_*sm_+sa_
  return vec3<T>(vm_.x*sm_+sa_, vm_.y*sm_+sa_, vm_.z*sm_+sa_);
}
//----

template<typename T>
PFC_INLINE vec3<T> madd(const vec3<T> &vm0_, const vec3<T> &vm1_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: vm_*vm1_+sa_
  return vec3<T>(vm0_.x*vm1_.x+sa_, vm0_.y*vm1_.y+sa_, vm0_.z*vm1_.z+sa_);
}
//----

template<typename T>
PFC_INLINE vec3<T> madd(const vec3<T> &vm_, typename math<T>::scalar_t sm_, const vec3<T> &va_)
{
  // component-wise multiply-add: vm_*sm_+va_
  return vec3<T>(vm_.x*sm_+va_.x, vm_.y*sm_+va_.y, vm_.z*sm_+va_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> rcp(const vec3<T> &v_)
{
  // component-wise reciprocal
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(v_.x && v_.y && v_.z);
  return vec3<T>(scalar_t(1)/v_.x, scalar_t(1)/v_.y, scalar_t(1)/v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> rcp_z(const vec3<T> &v_)
{
  // component-wise reciprocal (set to 0 for 0 components)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x?scalar_t(1)/v_.x:0, v_.y?scalar_t(1)/v_.y:0, v_.z?scalar_t(1)/v_.z:0);
}
//----

template<typename T>
PFC_INLINE vec3<T> floor(const vec3<T> &v_)
{
  // component-wise floor
  return vec3<T>(std::floor(v_.x), std::floor(v_.y), std::floor(v_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> ceil(const vec3<T> &v_)
{
  // component-wise ceil
  return vec3<T>(std::ceil(v_.x), std::ceil(v_.y), std::ceil(v_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> trunc(const vec3<T> &v_)
{
  // component-wise truncate
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(scalar_t(int(v_.x)), scalar_t(int(v_.y)), scalar_t(int(v_.z)));
}
//----

template<typename T>
PFC_INLINE vec3<T> frc(const vec3<T> &v_)
{
  // component-wise fractional
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x-scalar_t(int(v_.x)), v_.y-scalar_t(int(v_.y)), v_.z-scalar_t(int(v_.z)));
}
//----

template<typename T>
PFC_INLINE vec3<T> mod(const vec3<T> &v_, typename math<T>::scalar_t div_)
{
  // component-wise modulo
  return vec3<T>(std::fmod(v_.x, div_), std::fmod(v_.y, div_), std::fmod(v_.z, div_));
}
//----

template<typename T>
PFC_INLINE vec3<T> cycle(const vec3<T> &v_, typename math<T>::scalar_t cycle_)
{
  // component-wise cycle
  return vec3<T>(std::fmod(v_.x, cycle_)+(v_.x<0?cycle_:0),
                 std::fmod(v_.y, cycle_)+(v_.y<0?cycle_:0),
                 std::fmod(v_.z, cycle_)+(v_.z<0?cycle_:0));
}
//----

template<typename T>
PFC_INLINE vec3<T> cycle1(const vec3<T> &v_)
{
  // cycle1
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x-scalar_t(int(v_.x))+(v_.x<0?scalar_t(1):0),
                 v_.y-scalar_t(int(v_.y))+(v_.y<0?scalar_t(1):0),
                 v_.z-scalar_t(int(v_.z))+(v_.z<0?scalar_t(1):0));
}
//----

template<typename T>
PFC_INLINE vec3<T> sat(const vec3<T> &v_)
{
  // component-wise saturate
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x<0?0:v_.x>scalar_t(1)?scalar_t(1):v_.x,
                 v_.y<0?0:v_.y>scalar_t(1)?scalar_t(1):v_.y,
                 v_.z<0?0:v_.z>scalar_t(1)?scalar_t(1):v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> ssat(const vec3<T> &v_)
{
  // component-wise signed saturate
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x<scalar_t(-1)?scalar_t(-1):v_.x>scalar_t(1)?scalar_t(1):v_.x,
                 v_.y<scalar_t(-1)?scalar_t(-1):v_.y>scalar_t(1)?scalar_t(1):v_.y,
                 v_.z<scalar_t(-1)?scalar_t(-1):v_.z>scalar_t(1)?scalar_t(1):v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> clamp(const vec3<T> &v_, const vec3<T> &min_, const vec3<T> &max_)
{
  // component-wise clamp (to vectors)
  return vec3<T>(v_.x<min_.x?min_.x:v_.x>max_.x?max_.x:v_.x,
                 v_.y<min_.y?min_.y:v_.y>max_.y?max_.y:v_.y,
                 v_.z<min_.z?min_.z:v_.z>max_.z?max_.z:v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> clamp(const vec3<T> &v_, typename math<T>::scalar_t min_, typename math<T>::scalar_t max_)
{
  // component-wise clamp (to scalars)
  return vec3<T>(v_.x<min_?min_:v_.x>max_?max_:v_.x,
                 v_.y<min_?min_:v_.y>max_?max_:v_.y,
                 v_.z<min_?min_:v_.z>max_?max_:v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> abs(const vec3<T> &v_)
{
  // component-wise absolute
  return vec3<T>(std::abs(v_.x), std::abs(v_.y), std::abs(v_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> sgn(const vec3<T> &v_)
{
  // component-wise signum (neg=-1, pos=+1, zero=0)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x<0?scalar_t(-1):v_.x>0?scalar_t(1):0, v_.y<0?scalar_t(-1):v_.y>0?scalar_t(1):0, v_.z<0?scalar_t(-1):v_.z>0?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> sgn_zp(const vec3<T> &v_)
{
  // component-wise signum (neg=-1, pos&zero=+1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x<0?scalar_t(-1):scalar_t(1), v_.y<0?scalar_t(-1):scalar_t(1), v_.z<0?scalar_t(-1):scalar_t(1));
}
//----

template<typename T>
PFC_INLINE vec3<T> sqr(const vec3<T> &v_)
{
  // component-wise square
  return vec3<T>(v_.x*v_.x, v_.y*v_.y, v_.z*v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> cubic(const vec3<T> &v_)
{
  // component-wise cubic
  return vec3<T>(v_.x*v_.x*v_.x, v_.y*v_.y*v_.y, v_.z*v_.z*v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> sqrt(const vec3<T> &v_)
{
  // component-wise square root
  PFC_ASSERT_PEDANTIC(v_.x>=0 && v_.y>=0 && v_.z>=0);
  return vec3<T>(std::sqrt(v_.x), std::sqrt(v_.y), std::sqrt(v_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> sqrt_z(const vec3<T> &v_)
{
  // component-wise square root (set to 0 for components less than zero)
  return vec3<T>(sqrt_z(v_.x), sqrt_z(v_.y), sqrt_z(v_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> cbrt(const vec3<T> &v_)
{
  // component-wise cubic root
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x<0?-std::pow(-v_.x, scalar_t(1.0/3.0)):std::pow(v_.x, scalar_t(1.0/3.0)),
                 v_.y<0?-std::pow(-v_.y, scalar_t(1.0/3.0)):std::pow(v_.y, scalar_t(1.0/3.0)),
                 v_.z<0?-std::pow(-v_.z, scalar_t(1.0/3.0)):std::pow(v_.z, scalar_t(1.0/3.0)));
}
//----

template<typename T>
PFC_INLINE vec3<T> rsqrt(const vec3<T> &v_)
{
  // component-wise reciprocal square root
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(v_.x>0 && v_.y>0 && v_.z>0);
  return vec3<T>(scalar_t(1)/std::sqrt(v_.x), scalar_t(1)/std::sqrt(v_.y), scalar_t(1)/std::sqrt(v_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> rsqrt_z(const vec3<T> &v_)
{
  // component-wise reciprocal square root (set to 0 for components less than or equal to zero)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x>0?scalar_t(1)/std::sqrt(v_.x):0,
                 v_.y>0?scalar_t(1)/std::sqrt(v_.y):0,
                 v_.z>0?scalar_t(1)/std::sqrt(v_.z):0);
}
//----

template<typename T>
PFC_INLINE vec3<T> rcbrt(const vec3<T> &v_)
{
  // component-wise reciprocal cubic root
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x<0?-std::pow(-v_.x, scalar_t(-1.0/3.0)):std::pow(v_.x, scalar_t(-1.0/3.0)),
                 v_.y<0?-std::pow(-v_.y, scalar_t(-1.0/3.0)):std::pow(v_.y, scalar_t(-1.0/3.0)),
                 v_.z<0?-std::pow(-v_.z, scalar_t(-1.0/3.0)):std::pow(v_.z, scalar_t(-1.0/3.0)));
}
//----

template<typename T>
PFC_INLINE vec3<T> rcbrt_z(const vec3<T> &v_)
{
  // component-wise reciprocal cubic root (set to 0 for 0 components)
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(v_.x?v_.x<0?-std::pow(-v_.x, scalar_t(-1.0/3.0)):std::pow(v_.x, scalar_t(-1.0/3.0)):0,
                 v_.y?v_.y<0?-std::pow(-v_.y, scalar_t(-1.0/3.0)):std::pow(v_.y, scalar_t(-1.0/3.0)):0,
                 v_.z?v_.z<0?-std::pow(-v_.z, scalar_t(-1.0/3.0)):std::pow(v_.z, scalar_t(-1.0/3.0)):0);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t norm(const vec3<T> &v_)
{
  // norm of the vector (=vector length)
  return std::sqrt(v_.x*v_.x+v_.y*v_.y+v_.z*v_.z);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm(const vec3<T> &v_)
{
  // reciprocal norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=v_.x*v_.x+v_.y*v_.y+v_.z*v_.z;
  PFC_ASSERT_PEDANTIC(n2);
  return scalar_t(1)/std::sqrt(n2);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm_z(const vec3<T> &v_)
{
  // reciprocal norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=v_.x*v_.x+v_.y*v_.y+v_.z*v_.z;
  return n2?scalar_t(1)/std::sqrt(n2):0;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t norm2(const vec3<T> &v_)
{
  // squared norm of the vector
  return v_.x*v_.x+v_.y*v_.y+v_.z*v_.z;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm2(const vec3<T> &v_)
{
  // reciprocal squared norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=v_.x*v_.x+v_.y*v_.y+v_.z*v_.z;
  PFC_ASSERT_PEDANTIC(n2);
  return scalar_t(1)/n2;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm2_z(const vec3<T> &v_)
{
  // reciprocal squared norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t v=v_.x*v_.x+v_.y*v_.y+v_.z*v_.z;
  return v?scalar_t(1)/v:0;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t norm_l1(const vec3<T> &v_)
{
  // L1-norm of the vector (Manhattan norm)
  return abs(v_.x)+abs(v_.y)+abs(v_.z);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm_l1(const vec3<T> &v_)
{
  // reciprocal L1-norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  return scalar_t(1)/(abs(v_.x)+abs(v_.y)+abs(v_.z));
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const vec3<T> &v_)
{
  // reciprocal L1-norm of the vector (return 0 if |v|=0)
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t v=abs(v_.x)+abs(v_.y)+abs(v_.z);
  return v?scalar_t(1)/v:0;
}
//----

template<typename T>
PFC_INLINE vec3<T> exp(const vec3<T> &v_)
{
  // natural exponent
  return vec3<T>(std::exp(v_.x), std::exp(v_.y), std::exp(v_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> exp2(const vec3<T> &v_)
{
  // 2^x
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(std::pow(scalar_t(2), v_.x), std::pow(scalar_t(2), v_.y), std::pow(scalar_t(2), v_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> ln(const vec3<T> &v_)
{
  // natural logarithm
  return vec3<T>(std::log(v_.x), std::log(v_.y), std::log(v_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> log2(const vec3<T> &v_)
{
  // base-2 logarithm
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(std::log2(v_.x), std::log2(v_.y), std::log2(v_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> log10(const vec3<T> &v_)
{
  // base-10 logarithm
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(std::log10(v_.x), std::log10(v_.y), std::log10(v_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> pow(const vec3<T> &v_, typename math<T>::scalar_t power_)
{
  // raises value to the given power
  return vec3<T>(std::pow(v_.x, power_), std::pow(v_.y, power_), std::pow(v_.z, power_));
}
//----

template<typename T>
PFC_INLINE vec3<T> unit(const vec3<T> &v_)
{
  // unit vector of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=v_.x*v_.x+v_.y*v_.y+v_.z*v_.z;
  PFC_ASSERT_PEDANTIC(n2);
  scalar_t rs=scalar_t(1)/std::sqrt(n2);
  return vec3<T>(v_.x*rs, v_.y*rs, v_.z*rs);
}
//----

template<typename T>
PFC_INLINE vec3<T> unit_z(const vec3<T> &v_)
{
  // unit vector of the vector. if |v|=0, return v=[0, 0, 0]
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t rs=v_.x*v_.x+v_.y*v_.y+v_.z*v_.z;
  if(!rs)
    return vec3<T>(0, 0, 0);
  rs=scalar_t(1)/std::sqrt(rs);
  return vec3<T>(v_.x*rs, v_.y*rs, v_.z*rs);
}
//----

template<typename T>
PFC_INLINE vec3<T> cross(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // cross-product of vectors
  return vec3<T>(v0_.y*v1_.z-v0_.z*v1_.y,
                 v0_.z*v1_.x-v0_.x*v1_.z,
                 v0_.x*v1_.y-v0_.y*v1_.x);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t dot(const vec3<T> &v0_, const vec3<T> &v1_)
{
  // dot-product of vectors
  return v0_.x*v1_.x+v0_.y*v1_.y+v0_.z*v1_.z;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t dot1(const vec3<T> &v_)
{
  // dot-product with [1, 1, 1]
  return v_.x+v_.y+v_.z;
}
//----

template<typename T>
PFC_INLINE void neg(vec3<T> &v_)
{
  // negate the vector
  v_.x=-v_.x;
  v_.y=-v_.y;
  v_.z=-v_.z;
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_u(vec3<T> &vr_, Rng &rng_)
{
  // random unit vector (even distribution on unit sphere)
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t s, c;
  sincos(s, c, scalar_t(rng_.rand_ureal1())*math<T>::two_pi);
  scalar_t z=scalar_t(rng_.rand_real1());
  vr_.z=z;
  scalar_t rad=std::sqrt(scalar_t(1)-z*z);
  vr_.x=s*rad;
  vr_.y=c*rad;
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_real1(vec3<T> &vr_, Rng &rng_)
{
  // random vector where each component is in range [-1, 1]
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=scalar_t(rng_.rand_real1());
  vr_.y=scalar_t(rng_.rand_real1());
  vr_.z=scalar_t(rng_.rand_real1());
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_ureal1(vec3<T> &vr_, Rng &rng_)
{
  // random vector where each component is in range [0, 1]
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=scalar_t(rng_.rand_ureal1());
  vr_.y=scalar_t(rng_.rand_ureal1());
  vr_.z=scalar_t(rng_.rand_ureal1());
}
//----

template<typename T>
PFC_INLINE vec3<T> smoothstep(const vec3<T> &v_)
{
  // component-wise smoothstep function
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(v_.x>=0 && v_.x<=scalar_t(1) && v_.y>=0 && v_.y<=scalar_t(1) && v_.z>=0 && v_.z<=scalar_t(1));
  return vec3<T>(v_.x*v_.x*(scalar_t(3)-scalar_t(2)*v_.x),
                 v_.y*v_.y*(scalar_t(3)-scalar_t(2)*v_.y),
                 v_.z*v_.z*(scalar_t(3)-scalar_t(2)*v_.z));
}
//----

template<typename T>
PFC_INLINE vec3<T> smootherstep(const vec3<T> &v_)
{
  // component-wise smootherstep function
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(v_.x>=0 && v_.x<=scalar_t(1) && v_.y>=0 && v_.y<=scalar_t(1) && v_.z>=0 && v_.z<=scalar_t(1));
  return vec3<T>(v_.x*v_.x*v_.x*(v_.x*(v_.x*scalar_t(6)-scalar_t(15))+scalar_t(10)),
                 v_.y*v_.y*v_.y*(v_.y*(v_.y*scalar_t(6)-scalar_t(15))+scalar_t(10)),
                 v_.z*v_.z*v_.z*(v_.z*(v_.z*scalar_t(6)-scalar_t(15))+scalar_t(10)));
}
//----

template<typename T>
PFC_INLINE vec3<T> lerp(const vec3<T> &v0_, const vec3<T> &v1_, typename math<T>::scalar_t t_)
{
  // linear vector interpolation. f(t=0)=v0, f(t=1)=v1
  return vec3<T>(v0_.x+(v1_.x-v0_.x)*t_,
                 v0_.y+(v1_.y-v0_.y)*t_,
                 v0_.z+(v1_.z-v0_.z)*t_);
}
//----

template<typename T> PFC_INLINE vec3<T> reflect(const vec3<T> &v_, const vec3<T> &n_)
{
  // reflect vector about normal: v'=2*n*(v.n)/(n.n)-v
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t d=scalar_t(2)*(v_.x*n_.x+v_.y*n_.y+v_.z*n_.z)*rcp(n_.x*n_.x+n_.y*n_.y+n_.z*n_.z);
  return vec3<T>(d*n_.x-v_.x,
                 d*n_.y-v_.y,
                 d*n_.z-v_.z);
}
//----

template<typename T>
PFC_INLINE vec3<T> reflect_u(const vec3<T> &v_, const vec3<T> &n_)
{
  // reflect vector about unit normal: v'=2*n*(v.n)-v
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t d=scalar_t(2)*(v_.x*n_.x+v_.y*n_.y+v_.z*n_.z);
  return vec3<T>(d*n_.x-v_.x,
                 d*n_.y-v_.y,
                 d*n_.z-v_.z);
}
//----

template<typename T>
PFC_INLINE vec2<T> perspective_project(const vec3<T> &v_)
{
  // perspective project vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t s=scalar_t(1)/v_.z;
  return vec2<T>(v_.x*s, v_.y*s);
}
//----

template<typename T, typename U>
PFC_INLINE vec3<T> to_vec3(const vec3<U> &v_)
{
  // convert between vec3 types
  typedef typename math<T>::scalar_t scalar_t;
  return vec3<T>(scalar_t(v_.x), scalar_t(v_.y), scalar_t(v_.z));
}
//----

namespace priv
{
  template<unsigned shuffle_, typename T>
  struct shuffle_vec3_helper
  {
    static vec3<T> shuffle(const vec3<T>&) {PFC_CTF_ERROR(T, invalid_vector_component_shuffle);}
  };
  #define PFC_VECTOR_SHUFFLE(shuffle__, x__, y__, z__)\
  template<typename T> struct shuffle_vec3_helper<shuffle__, T>\
  {\
    static PFC_INLINE vec3<T> shuffle(const vec3<T> &v_) {return vec3<T>(v_.x__, v_.y__, v_.z__);}\
  };
  PFC_VECTOR_SHUFFLE(000, x, x, x); PFC_VECTOR_SHUFFLE(001, x, x, y); PFC_VECTOR_SHUFFLE(002, x, x, z); PFC_VECTOR_SHUFFLE(010, x, y, x); PFC_VECTOR_SHUFFLE(011, x, y, y); PFC_VECTOR_SHUFFLE(012, x, y, z); PFC_VECTOR_SHUFFLE(020, x, z, x); PFC_VECTOR_SHUFFLE(021, x, z, y); PFC_VECTOR_SHUFFLE(022, x, z, z);
  PFC_VECTOR_SHUFFLE(100, y, x, x); PFC_VECTOR_SHUFFLE(101, y, x, y); PFC_VECTOR_SHUFFLE(102, y, x, z); PFC_VECTOR_SHUFFLE(110, y, y, x); PFC_VECTOR_SHUFFLE(111, y, y, y); PFC_VECTOR_SHUFFLE(112, y, y, z); PFC_VECTOR_SHUFFLE(120, y, z, x); PFC_VECTOR_SHUFFLE(121, y, z, y); PFC_VECTOR_SHUFFLE(122, y, z, z);
  PFC_VECTOR_SHUFFLE(200, z, x, x); PFC_VECTOR_SHUFFLE(201, z, x, y); PFC_VECTOR_SHUFFLE(202, z, x, z); PFC_VECTOR_SHUFFLE(210, z, y, x); PFC_VECTOR_SHUFFLE(211, z, y, y); PFC_VECTOR_SHUFFLE(212, z, y, z); PFC_VECTOR_SHUFFLE(220, z, z, x); PFC_VECTOR_SHUFFLE(221, z, z, y); PFC_VECTOR_SHUFFLE(222, z, z, z);
  #undef PFC_VECTOR_SHUFFLE
} // namespace priv
//----

template<unsigned shuffle_, typename T>
PFC_INLINE vec3<T> shuffle(const vec3<T> &v_)
{
  return priv::shuffle_vec3_helper<shuffle_, T>::shuffle(v_);
}
//----

template<typename T>
PFC_INLINE void pack_u1(vec3_32 &vr_, const vec3<T> &v_)
{
  // pack 3d vector (components in range [0, 1]) to 32-bit 3d vector
  PFC_ASSERT_PEDANTIC_MSG(is_sat(v_), ("All vector components [%f, %f, %f] must be in range [0, 1]\r\n", float(v_.x), float(v_.y), float(v_.z)));
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=uint8_t(v_.x*scalar_t(255.999));
  vr_.y=uint8_t(v_.y*scalar_t(255.999));
  vr_.z=uint8_t(v_.z*scalar_t(255.999));
}
//----

template<typename T>
PFC_INLINE void pack_s1(vec3_32 &vr_, const vec3<T> &v_)
{
  // pack 3d vector (components in range [-1, 1]) to 32-bit 3d vector
  PFC_ASSERT_PEDANTIC_MSG(is_ssat(v_), ("All vector components [%f, %f, %f] must be in range [-1, 1]\r\n", float(v_.x), float(v_.y), float(v_.z)));
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=uint8_t(v_.x*scalar_t(127.999)+scalar_t(128.0));
  vr_.y=uint8_t(v_.y*scalar_t(127.999)+scalar_t(128.0));
  vr_.z=uint8_t(v_.z*scalar_t(127.999)+scalar_t(128.0));
}
//----

template<typename T>
PFC_INLINE void unpack_u1(vec3<T> &vr_, const vec3_32 &v_)
{
  // unpack 3d vector (components in range [0, 1]) from 32-bit 3d vector
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=v_.x*scalar_t(1.0/255.0);
  vr_.y=v_.y*scalar_t(1.0/255.0);
  vr_.z=v_.z*scalar_t(1.0/255.0);
}
//----

template<typename T>
PFC_INLINE void unpack_s1(vec3<T> &vr_, const vec3_32 &v_)
{
  // unpack 3d vector (components in range [-1, 1]) from 32-bit 3d vector
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=v_.x*scalar_t(2.0/255.0)-scalar_t(1);
  vr_.y=v_.y*scalar_t(2.0/255.0)-scalar_t(1);
  vr_.z=v_.z*scalar_t(2.0/255.0)-scalar_t(1);
}
//----------------------------------------------------------------------------


//============================================================================
// vec4
//============================================================================
template<typename T> const vec4<T> vec4<T>::s_zero(T(0));
template<typename T> const vec4<T> vec4<T>::s_one(T(1));
template<typename T> const vec4<T> vec4<T>::s_neg_one(T(-1));
//----------------------------------------------------------------------------

template<typename T>
vec4<T>::vec4()
{
}
//----

template<typename T>
vec4<T>::vec4(T s_)
{
  // init vector with scalar
  x=s_;
  y=s_;
  z=s_;
  w=s_;
}
//----

template<typename T>
vec4<T>::vec4(T x_, T y_, T z_, T w_)
{
  // init vector with scalars
  x=x_;
  y=y_;
  z=z_;
  w=w_;
}
//----

template<typename T>
vec4<T>::vec4(const vec3<T> &v_, T w_)
{
  // init vector with 3d vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

template<typename T>
vec4<T>::vec4(const T *a_)
{
  // init vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
  z=a_[2];
  w=a_[3];
}
//----------------------------------------------------------------------------

template<typename T>
const T &vec4<T>::operator[](unsigned idx_) const
{
  // return reference to nth component (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<const T*>(this)[idx_];
}
//----

template<typename T>
T &vec4<T>::operator[](unsigned idx_)
{
  // return reference to nth component (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<T*>(this)[idx_];
}
//----

template<typename T>
void vec4<T>::set(T s_)
{
  // set vector with scalar
  x=s_;
  y=s_;
  z=s_;
  w=s_;
}
//----

template<typename T>
void vec4<T>::set(T x_, T y_, T z_, T w_)
{
  // set vector with scalars
  x=x_;
  y=y_;
  z=z_;
  w=w_;
}
//----

template<typename T>
void vec4<T>::set(const vec3<T> &v_, T w_)
{
  // set vector with 3d vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

template<typename T>
void vec4<T>::set(const vec4<T> &v_)
{
  // set vector with 3d vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=v_.w;
}
//----

template<typename T>
void vec4<T>::set(const T *a_)
{
  // set vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
  z=a_[2];
  w=a_[3];
}
//----------------------------------------------------------------------------


//============================================================================
// vec4<vec32_t>
//============================================================================
vec4<vec32_t>::vec4()
{
}
//----

vec4<vec32_t>::vec4(uint8_t s_)
{
  // init vector with scalar
  x=s_;
  y=s_;
  z=s_;
  w=s_;
}
//----

vec4<vec32_t>::vec4(uint8_t x_, uint8_t y_, uint8_t z_, uint8_t w_)
{
  // init vector with scalars
  x=x_;
  y=y_;
  z=z_;
  w=w_;
}
//----

vec4<vec32_t>::vec4(const vec3<vec32_t> &v_, uint8_t w_)
{
  // init vector with 3d vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

vec4<vec32_t>::vec4(const uint8_t *a_)
{
  // init vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
  z=a_[2];
  w=a_[3];
}
//----------------------------------------------------------------------------

const uint8_t &vec4<vec32_t>::operator[](unsigned idx_) const
{
  // return reference to nth component (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<const uint8_t*>(this)[idx_];
}
//----

uint8_t &vec4<vec32_t>::operator[](unsigned idx_)
{
  // return reference to nth component (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<uint8_t*>(this)[idx_];
}
//----

void vec4<vec32_t>::set(uint8_t s_)
{
  // set vector with scalar
  x=s_;
  y=s_;
  z=s_;
  w=s_;
}
//----

void vec4<vec32_t>::set(uint8_t x_, uint8_t y_, uint8_t z_, uint8_t w_)
{
  // set vector with scalars
  x=x_;
  y=y_;
  z=z_;
  w=w_;
}
//----

void vec4<vec32_t>::set(const vec3<vec32_t> &v_, uint8_t w_)
{
  // set vector with 3d vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

void vec4<vec32_t>::set(const vec4<vec32_t> &v_)
{
  // set vector with 3d vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=v_.w;
}
//----

void vec4<vec32_t>::set(const uint8_t *a_)
{
  // set vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
  z=a_[2];
  w=a_[3];
}
//---------------------------------------------------------------------------

template<typename T>
PFC_INLINE bool is_zero(const vec4<T> &v_)
{
  // test for zero-vector
  return v_.x==0 && v_.y==0 && v_.z==0 && v_.w==0;
}
//----

template<typename T>
PFC_INLINE bool is_sat(const vec4<T> &v_)
{
  // test for saturated vector
  typedef typename math<T>::scalar_t scalar_t;
  return    v_.x>=0 && v_.x<=scalar_t(1)
         && v_.y>=0 && v_.y<=scalar_t(1)
         && v_.z>=0 && v_.z<=scalar_t(1)
         && v_.w>=0 && v_.w<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const vec4<T> &v_)
{
  // test for signed saturated vector
  typedef typename math<T>::scalar_t scalar_t;
  return    v_.x>=scalar_t(-1) && v_.x<=scalar_t(1)
         && v_.y>=scalar_t(-1) && v_.y<=scalar_t(1)
         && v_.z>=scalar_t(-1) && v_.z<=scalar_t(1)
         && v_.w>=scalar_t(-1) && v_.w<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool operator==(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // test for equality of vectors
  return v0_.x==v1_.x && v0_.y==v1_.y && v0_.z==v1_.z && v0_.w==v1_.w;
}
//----

template<typename T>
PFC_INLINE bool operator==(const vec4<T> &v_, typename math<T>::scalar_t s_)
{
  // test for equality of vector and scalar
  return v_.x==s_ && v_.y==s_ && v_.z==s_ && v_.w==s_;
}
//----

template<typename T>
PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const vec4<T> &v_)
{
  // test for equality of vector and scalar
  return s_==v_.x && s_==v_.y && s_==v_.z && s_==v_.w;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // test for inequality of vectors
  return v0_.x!=v1_.x || v0_.y!=v1_.y || v0_.z!=v1_.z || v0_.w!=v1_.w;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const vec4<T> &v_, typename math<T>::scalar_t s_)
{
  // test for inequality of vector and scalar
  return v_.x!=s_ || v_.y!=s_ || v_.z!=s_ || v_.w!=s_;
}
//----

template<typename T>
PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const vec4<T> &v_)
{
  // test for inequality of vector and scalar
  return s_!=v_.x || s_!=v_.y || s_!=v_.z || s_!=v_.w;
}
//----

template<typename T>
PFC_INLINE vec4<T> operator<(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v0_.x<v1_.x?scalar_t(1):0, v0_.y<v1_.y?scalar_t(1):0, v0_.z<v1_.z?scalar_t(1):0, v0_.w<v1_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator<(const vec4<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x<s_?scalar_t(1):0, v_.y<s_?scalar_t(1):0, v_.z<s_?scalar_t(1):0, v_.w<s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator<(typename math<T>::scalar_t s_, const vec4<T> &v_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(s_<v_.x?scalar_t(1):0, s_<v_.y?scalar_t(1):0, s_<v_.z?scalar_t(1):0, s_<v_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator>(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v0_.x>v1_.x?scalar_t(1):0, v0_.y>v1_.y?scalar_t(1):0, v0_.z>v1_.z?scalar_t(1):0, v0_.w>v1_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator>(const vec4<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x>s_?scalar_t(1):0, v_.y>s_?scalar_t(1):0, v_.z>s_?scalar_t(1):0, v_.w>s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator>(typename math<T>::scalar_t s_, const vec4<T> &v_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(s_>v_.x?scalar_t(1):0, s_>v_.y?scalar_t(1):0, s_>v_.z?scalar_t(1):0, s_>v_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator<=(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v0_.x<=v1_.x?scalar_t(1):0, v0_.y<=v1_.y?scalar_t(1):0, v0_.z<=v1_.z?scalar_t(1):0, v0_.w<=v1_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator<=(const vec4<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x<=s_?scalar_t(1):0, v_.y<=s_?scalar_t(1):0, v_.z<=s_?scalar_t(1):0, v_.w<=s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator<=(typename math<T>::scalar_t s_, const vec4<T> &v_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(s_<=v_.x?scalar_t(1):0, s_<=v_.y?scalar_t(1):0, s_<=v_.z?scalar_t(1):0, s_<=v_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator>=(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v0_.x>=v1_.x?scalar_t(1):0, v0_.y>=v1_.y?scalar_t(1):0, v0_.z>=v1_.z?scalar_t(1):0, v0_.w>=v1_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator>=(const vec4<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x>=s_?scalar_t(1):0, v_.y>=s_?scalar_t(1):0, v_.z>=s_?scalar_t(1):0, v_.w>=s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator>=(typename math<T>::scalar_t s_, const vec4<T> &v_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(s_>=v_.x?scalar_t(1):0, s_>=v_.y?scalar_t(1):0, s_>=v_.z?scalar_t(1):0, s_>=v_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> sel_eq(const vec4<T> &t0_, const vec4<T> &t1_, const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise equal vector select (t0_==t1_?v0_:v1_)
  return vec4<T>(t0_.x==t1_.x?v0_.x:v1_.x,
                 t0_.y==t1_.y?v0_.y:v1_.y,
                 t0_.z==t1_.z?v0_.z:v1_.z,
                 t0_.w==t1_.w?v0_.w:v1_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> sel_lt(const vec4<T> &t0_, const vec4<T> &t1_, const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise less-than vector select (t0_<t1_?v0_:v1_)
  return vec4<T>(t0_.x<t1_.x?v0_.x:v1_.x,
                 t0_.y<t1_.y?v0_.y:v1_.y,
                 t0_.z<t1_.z?v0_.z:v1_.z,
                 t0_.w<t1_.w?v0_.w:v1_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> sel_le(const vec4<T> &t0_, const vec4<T> &t1_, const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise less-or-equal vector select (t0_<=t1_?v0_:v1_)
  return vec4<T>(t0_.x<=t1_.x?v0_.x:v1_.x,
                 t0_.y<=t1_.y?v0_.y:v1_.y,
                 t0_.z<=t1_.z?v0_.z:v1_.z,
                 t0_.w<=t1_.w?v0_.w:v1_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> sel_eqz(const vec4<T> &t_, const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise equal-to-zero vector select (t_==0?v0_:v1_)
  return vec4<T>(t_.x==0?v0_.x:v1_.x,
                 t_.y==0?v0_.y:v1_.y,
                 t_.z==0?v0_.z:v1_.z,
                 t_.w==0?v0_.w:v1_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> sel_ltz(const vec4<T> &t_, const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise less-than-zero vector select (t_<0?v0_:v1_)
  return vec4<T>(t_.x<0?v0_.x:v1_.x,
                 t_.y<0?v0_.y:v1_.y,
                 t_.z<0?v0_.z:v1_.z,
                 t_.w<0?v0_.w:v1_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> sel_lez(const vec4<T> &t_, const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise less-or-equal-to-zero vector select (t_<=0?v0_:v1_)
  return vec4<T>(t_.x<=0?v0_.x:v1_.x,
                 t_.y<=0?v0_.y:v1_.y,
                 t_.z<=0?v0_.z:v1_.z,
                 t_.w<=0?v0_.w:v1_.w);
}
//----

template<typename T>
PFC_INLINE void operator+=(vec4<T> &vr_, const vec4<T> &v_)
{
  // add vector to vector
  vr_.x+=v_.x;
  vr_.y+=v_.y;
  vr_.z+=v_.z;
  vr_.w+=v_.w;
}
//----

template<typename T>
PFC_INLINE void operator+=(vec4<T> &vr_, typename math<T>::scalar_t s_)
{
  // add scalar to each component of the vector
  vr_.x+=s_;
  vr_.y+=s_;
  vr_.z+=s_;
  vr_.w+=s_;
}
//----

template<typename T>
PFC_INLINE void operator-=(vec4<T> &vr_, const vec4<T> &v_)
{
  // subtract vector from vector
  vr_.x-=v_.x;
  vr_.y-=v_.y;
  vr_.z-=v_.z;
  vr_.w-=v_.w;
}
//----

template<typename T>
PFC_INLINE void operator-=(vec4<T> &vr_, typename math<T>::scalar_t s_)
{
  // subtract scalar from each component of the vector
  vr_.x-=s_;
  vr_.y-=s_;
  vr_.z-=s_;
  vr_.w-=s_;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec4<T> &vr_, const vec4<T> &v_)
{
  // component-wise vector by vector multiply
  vr_.x*=v_.x;
  vr_.y*=v_.y;
  vr_.z*=v_.z;
  vr_.w*=v_.w;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec4<T> &vr_, typename math<T>::scalar_t s_)
{
  // multiply vector by scalar
  vr_.x*=s_;
  vr_.y*=s_;
  vr_.z*=s_;
  vr_.w*=s_;
}
//----

template<typename T>
PFC_INLINE void operator*=(vec4<T> &vr_, const mat44<T> &m_)
{
  // multiply vector by matrix
  vec4<T> v(vr_);
  vr_.x=v.x*m_.x.x+v.y*m_.y.x+v.z*m_.z.x+v.w*m_.w.x;
  vr_.y=v.x*m_.x.y+v.y*m_.y.y+v.z*m_.z.y+v.w*m_.w.y;
  vr_.z=v.x*m_.x.z+v.y*m_.y.z+v.z*m_.z.z+v.w*m_.w.z;
  vr_.w=v.x*m_.x.w+v.y*m_.y.w+v.z*m_.z.w+v.w*m_.w.w;
}
//----

template<typename T>
PFC_INLINE void operator/=(vec4<T> &vr_, const vec4<T> &v_)
{
  // component-wise vector by vector division
  PFC_ASSERT_PEDANTIC(v_.x && v_.y && v_.z && v_.w);
  vr_.x/=v_.x;
  vr_.y/=v_.y;
  vr_.z/=v_.z;
  vr_.w/=v_.w;
}
//----

template<typename T>
PFC_INLINE void operator/=(vec4<T> &vr_, typename math<T>::scalar_t s_)
{
  // divide vector by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  vr_.x*=rs;
  vr_.y*=rs;
  vr_.z*=rs;
  vr_.w*=rs;
}
//----

template<typename T>
PFC_INLINE vec4<T> operator+(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // add vector to vector
  return vec4<T>(v0_.x+v1_.x, v0_.y+v1_.y, v0_.z+v1_.z, v0_.w+v1_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator+(const vec4<T> &v_, typename math<T>::scalar_t s_)
{
  // add scalar to each component of the vector
  return vec4<T>(v_.x+s_, v_.y+s_, v_.z+s_, v_.w+s_);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator+(typename math<T>::scalar_t s_, const vec4<T> &v_)
{
  // add each component of the vector to a scalar vector
  return vec4<T>(s_+v_.x, s_+v_.y, s_+v_.z, s_+v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator-(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // subtract vector from vector
  return vec4<T>(v0_.x-v1_.x, v0_.y-v1_.y, v0_.z-v1_.z, v0_.w-v1_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator-(const vec4<T> &v_, typename math<T>::scalar_t s_)
{
  // subtract scalar from each component of the vector
  return vec4<T>(v_.x-s_, v_.y-s_, v_.z-s_, v_.w-s_);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator-(typename math<T>::scalar_t s_, const vec4<T> &v_)
{
  // subtract each component of the vector from a scalar vector
  return vec4<T>(s_-v_.x, s_-v_.y, s_-v_.z, s_-v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator-(const vec4<T> &v_)
{
  // negate vector
  return vec4<T>(-v_.x, -v_.y, -v_.z, -v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator*(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise vector by vector multiply
  return vec4<T>(v0_.x*v1_.x, v0_.y*v1_.y, v0_.z*v1_.z, v0_.w*v1_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator*(const vec4<T> &v_, typename math<T>::scalar_t s_)
{
  // multiply vector by scalar
  return vec4<T>(v_.x*s_, v_.y*s_, v_.z*s_, v_.w*s_);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator*(typename math<T>::scalar_t s_, const vec4<T> &v_)
{
  // multiply vector by scalar
  return vec4<T>(v_.x*s_, v_.y*s_, v_.z*s_, v_.w*s_);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator*(const vec4<T> &v_, const mat44<T> &m_)
{
  // multiply vector by matrix
  return vec4<T>(v_.x*m_.x.x+v_.y*m_.y.x+v_.z*m_.z.x+v_.w*m_.w.x,
                 v_.x*m_.x.y+v_.y*m_.y.y+v_.z*m_.z.y+v_.w*m_.w.y,
                 v_.x*m_.x.z+v_.y*m_.y.z+v_.z*m_.z.z+v_.w*m_.w.z,
                 v_.x*m_.x.w+v_.y*m_.y.w+v_.z*m_.z.w+v_.w*m_.w.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator*(const mat44<T> &m_, const vec4<T> &v_)
{
  // multiply matrix by transposed vector
  return vec4<T>(v_.x*m_.x.x+v_.y*m_.x.y+v_.z*m_.x.z+v_.w*m_.x.w,
                 v_.x*m_.y.x+v_.y*m_.y.y+v_.z*m_.y.z+v_.w*m_.y.w,
                 v_.x*m_.z.x+v_.y*m_.z.y+v_.z*m_.z.z+v_.w*m_.z.w,
                 v_.x*m_.w.x+v_.y*m_.w.y+v_.z*m_.w.z+v_.w*m_.w.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator/(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise vector by vector division
  PFC_ASSERT_PEDANTIC(v1_.x && v1_.y && v1_.z && v1_.w);
  return vec4<T>(v0_.x/v1_.x, v0_.y/v1_.y, v0_.z/v1_.z, v0_.w/v1_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> operator/(const vec4<T> &v_, typename math<T>::scalar_t s_)
{
  // divide vector by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  return vec4<T>(v_.x*rs, v_.y*rs, v_.z*rs, v_.w*rs);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t min(const vec4<T> &v_)
{
  // minimum component value
  return min(v_.x, v_.y, v_.z, v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> min(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise min vector
  return vec4<T>(v0_.x<v1_.x?v0_.x:v1_.x,
                 v0_.y<v1_.y?v0_.y:v1_.y,
                 v0_.z<v1_.z?v0_.z:v1_.z,
                 v0_.w<v1_.w?v0_.w:v1_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> min(const vec4<T> &v0_, const vec4<T> &v1_, const vec4<T> &v2_)
{
  // component-wise min vector
  return vec4<T>(min(v0_.x, v1_.x, v2_.x),
                 min(v0_.y, v1_.y, v2_.y),
                 min(v0_.z, v1_.z, v2_.z),
                 min(v0_.w, v1_.w, v2_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> min(const vec4<T> &v0_, const vec4<T> &v1_, const vec4<T> &v2_, const vec4<T> &v3_)
{
  // component-wise min vector
  return vec4<T>(min(v0_.x, v1_.x, v2_.x, v3_.x),
                 min(v0_.y, v1_.y, v2_.y, v3_.y),
                 min(v0_.z, v1_.z, v2_.z, v3_.z),
                 min(v0_.w, v1_.w, v2_.w, v3_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> min(const vec4<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise min vector
  return vec4<T>(v_.x<s_?v_.x:s_,
                 v_.y<s_?v_.y:s_,
                 v_.z<s_?v_.z:s_,
                 v_.w<s_?v_.w:s_);
}
//----

template<typename T>
PFC_INLINE vec4<T> min(typename math<T>::scalar_t s_, const vec4<T> &v_)
{
  // component-wise min vector
  return vec4<T>(s_<v_.x?s_:v_.x,
                 s_<v_.y?s_:v_.y,
                 s_<v_.z?s_:v_.z,
                 s_<v_.w?s_:v_.w);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t max(const vec4<T> &v_)
{
  // maximum component value
  return max(v_.x, v_.y, v_.z, v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> max(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise max vector
  return vec4<T>(v0_.x>v1_.x?v0_.x:v1_.x,
                 v0_.y>v1_.y?v0_.y:v1_.y,
                 v0_.z>v1_.z?v0_.z:v1_.z,
                 v0_.w>v1_.w?v0_.w:v1_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> max(const vec4<T> &v0_, const vec4<T> &v1_, const vec4<T> &v2_)
{
  // component-wise max vector
  return vec4<T>(max(v0_.x, v1_.x, v2_.x),
                 max(v0_.y, v1_.y, v2_.y),
                 max(v0_.z, v1_.z, v2_.z),
                 max(v0_.w, v1_.w, v2_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> max(const vec4<T> &v0_, const vec4<T> &v1_, const vec4<T> &v2_, const vec4<T> &v3_)
{
  // component-wise max vector
  return vec4<T>(max(v0_.x, v1_.x, v2_.x, v3_.x),
                 max(v0_.y, v1_.y, v2_.y, v3_.y),
                 max(v0_.z, v1_.z, v2_.z, v3_.z),
                 max(v0_.w, v1_.w, v2_.w, v3_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> max(const vec4<T> &v_, typename math<T>::scalar_t s_)
{
  // component-wise max vector
  return vec4<T>(v_.x>s_?v_.x:s_,
                 v_.y>s_?v_.y:s_,
                 v_.z>s_?v_.z:s_,
                 v_.w>s_?v_.w:s_);
}
//----

template<typename T>
PFC_INLINE vec4<T> max(typename math<T>::scalar_t s_, const vec4<T> &v_)
{
  // component-wise max vector
  return vec4<T>(s_>v_.x?s_:v_.x,
                 s_>v_.y?s_:v_.y,
                 s_>v_.z?s_:v_.z,
                 s_>v_.w?s_:v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> mul(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // component-wise multiply: v0_*v1_
  return vec4<T>(v0_.x*v1_.x, v0_.y*v1_.y, v0_.z*v1_.z, v0_.w*v1_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> madd(const vec4<T> &vm0_, const vec4<T> &vm1_, const vec4<T> &va_)
{
  // component-wise multiply-add: vm0_*vm1+va_
  return vec4<T>(vm0_.x*vm1_.x+va_.x, vm0_.y*vm1_.y+va_.y, vm0_.z*vm1_.z+va_.z, vm0_.w*vm1_.w+va_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> madd(const vec4<T> &vm_, typename math<T>::scalar_t sm_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: vm_*sm_+sa_
  return vec4<T>(vm_.x*sm_+sa_, vm_.y*sm_+sa_, vm_.z*sm_+sa_, vm_.w*sm_+sa_);
}
//----

template<typename T>
PFC_INLINE vec4<T> madd(const vec4<T> &vm0_, const vec4<T> &vm1_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: vm0_*vm1_+sa_
  return vec4<T>(vm0_.x*vm1_.x+sa_, vm0_.y*vm1_.y+sa_, vm0_.z*vm1_.z+sa_, vm0_.w*vm1_.w+sa_);
}
//----

template<typename T>
PFC_INLINE vec4<T> madd(const vec4<T> &vm_, typename math<T>::scalar_t sm_, const vec4<T> &va_)
{
  // component-wise multiply-add: vm_*sm_+va_
  return vec4<T>(vm_.x*sm_+va_.x, vm_.y*sm_+va_.y, vm_.z*sm_+va_.z, vm_.w*sm_+va_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> rcp(const vec4<T> &v_)
{
  // component-wise reciprocal
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(v_.x && v_.y && v_.z && v_.w);
  return vec4<T>(scalar_t(1)/v_.x, scalar_t(1)/v_.y, scalar_t(1)/v_.z, scalar_t(1)/v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> rcp_z(const vec4<T> &v_)
{
  // component-wise reciprocal (set to 0 for 0 components)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x?scalar_t(1)/v_.x:0, v_.y?scalar_t(1)/v_.y:0, v_.z?scalar_t(1)/v_.z:0, v_.w?scalar_t(1)/v_.w:0);
}
//----

template<typename T>
PFC_INLINE vec4<T> floor(const vec4<T> &v_)
{
  // component-wise floor
  return vec4<T>(std::floor(v_.x), std::floor(v_.y), std::floor(v_.z), std::floor(v_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> ceil(const vec4<T> &v_)
{
  // component-wise ceil
  return vec4<T>(std::ceil(v_.x), std::ceil(v_.y), std::ceil(v_.z), std::ceil(v_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> trunc(const vec4<T> &v_)
{
  // component-wise truncate
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(scalar_t(int(v_.x)), scalar_t(int(v_.y)), scalar_t(int(v_.z)), scalar_t(int(v_.w)));
}
//----

template<typename T>
PFC_INLINE vec4<T> frc(const vec4<T> &v_)
{
  // component-wise fractional
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x-scalar_t(int(v_.x)), v_.y-scalar_t(int(v_.y)), v_.z-scalar_t(int(v_.z)), v_.w-scalar_t(int(v_.w)));
}
//----

template<typename T>
PFC_INLINE vec4<T> mod(const vec4<T> &v_, typename math<T>::scalar_t div_)
{
  // component-wise modulo
  return vec4<T>(std::fmod(v_.x, div_), std::fmod(v_.y, div_), std::fmod(v_.z, div_), std::fmod(v_.w, div_));
}
//----

template<typename T>
PFC_INLINE vec4<T> cycle(const vec4<T> &v_, typename math<T>::scalar_t cycle_)
{
  // component-wise cycle
  return vec4<T>(std::fmod(v_.x, cycle_)+(v_.x<0?cycle_:0),
                 std::fmod(v_.y, cycle_)+(v_.y<0?cycle_:0),
                 std::fmod(v_.z, cycle_)+(v_.z<0?cycle_:0),
                 std::fmod(v_.w, cycle_)+(v_.w<0?cycle_:0));
}
//----

template<typename T>
PFC_INLINE vec4<T> cycle1(const vec4<T> &v_)
{
  // cycle1
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x-scalar_t(int(v_.x))+(v_.x<0?scalar_t(1):0),
                 v_.y-scalar_t(int(v_.y))+(v_.y<0?scalar_t(1):0),
                 v_.z-scalar_t(int(v_.z))+(v_.z<0?scalar_t(1):0),
                 v_.w-scalar_t(int(v_.w))+(v_.w<0?scalar_t(1):0));
}
//----

template<typename T>
PFC_INLINE vec4<T> sat(const vec4<T> &v_)
{
  // component-wise saturate
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x<0?0:v_.x>scalar_t(1)?scalar_t(1):v_.x,
                 v_.y<0?0:v_.y>scalar_t(1)?scalar_t(1):v_.y,
                 v_.z<0?0:v_.z>scalar_t(1)?scalar_t(1):v_.z,
                 v_.w<0?0:v_.w>scalar_t(1)?scalar_t(1):v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> ssat(const vec4<T> &v_)
{
  // component-wise signed saturate
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x<scalar_t(-1)?scalar_t(-1):v_.x>scalar_t(1)?scalar_t(1):v_.x,
                 v_.y<scalar_t(-1)?scalar_t(-1):v_.y>scalar_t(1)?scalar_t(1):v_.y,
                 v_.z<scalar_t(-1)?scalar_t(-1):v_.z>scalar_t(1)?scalar_t(1):v_.z,
                 v_.w<scalar_t(-1)?scalar_t(-1):v_.w>scalar_t(1)?scalar_t(1):v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> clamp(const vec4<T> &v_, const vec4<T> &min_, const vec4<T> &max_)
{
  // component-wise clamp (to vectors)
  return vec4<T>(v_.x<min_.x?min_.x:v_.x>max_.x?max_.x:v_.x,
                 v_.y<min_.y?min_.y:v_.y>max_.y?max_.y:v_.y,
                 v_.z<min_.z?min_.z:v_.z>max_.z?max_.z:v_.z,
                 v_.w<min_.w?min_.w:v_.w>max_.w?max_.w:v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> clamp(const vec4<T> &v_, typename math<T>::scalar_t min_, typename math<T>::scalar_t max_)
{
  // component-wise clamp (to scalars)
  return vec4<T>(v_.x<min_?min_:v_.x>max_?max_:v_.x,
                 v_.y<min_?min_:v_.y>max_?max_:v_.y,
                 v_.z<min_?min_:v_.z>max_?max_:v_.z,
                 v_.w<min_?min_:v_.w>max_?max_:v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> abs(const vec4<T> &v_)
{
  // component-wise absolute
  return vec4<T>(std::abs(v_.x), std::abs(v_.y), std::abs(v_.z), std::abs(v_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> sgn(const vec4<T> &v_)
{
  // component-wise signum (neg=-1, pos=+1, zero=0)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x<0?scalar_t(-1):v_.x>0?scalar_t(1):0, v_.y<0?scalar_t(-1):v_.y>0?scalar_t(1):0, v_.z<0?scalar_t(-1):v_.z>0?scalar_t(1):0, v_.w<0?scalar_t(-1):v_.w>0?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> sgn_zp(const vec4<T> &v_)
{
  // component-wise signum (neg=-1, pos&zero=+1)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x<0?scalar_t(-1):scalar_t(1), v_.y<0?scalar_t(-1):scalar_t(1), v_.z<0?scalar_t(-1):scalar_t(1), v_.w<0?scalar_t(-1):scalar_t(1));
}
//----

template<typename T>
PFC_INLINE vec4<T> sqr(const vec4<T> &v_)
{
  // component-wise square
  return vec4<T>(v_.x*v_.x, v_.y*v_.y, v_.z*v_.z, v_.w*v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> cubic(const vec4<T> &v_)
{
  // component-wise cubic
  return vec4<T>(v_.x*v_.x*v_.x, v_.y*v_.y*v_.y, v_.z*v_.z*v_.z, v_.w*v_.w*v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> sqrt(const vec4<T> &v_)
{
  // component-wise square root
  PFC_ASSERT_PEDANTIC(v_.x>=0 && v_.y>=0 && v_.z>=0 && v_.w>=0);
  return vec4<T>(std::sqrt(v_.x), std::sqrt(v_.y), std::sqrt(v_.z), std::sqrt(v_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> sqrt_z(const vec4<T> &v_)
{
  // component-wise square root (set to 0 for components less than zero)
  return vec4<T>(sqrt_z(v_.x), sqrt_z(v_.y), sqrt_z(v_.z), sqrt_z(v_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> cbrt(const vec4<T> &v_)
{
  // component-wise cubic root
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x<0?-std::pow(-v_.x, scalar_t(1.0/3.0)):std::pow(v_.x, scalar_t(1.0/3.0)),
                 v_.y<0?-std::pow(-v_.y, scalar_t(1.0/3.0)):std::pow(v_.y, scalar_t(1.0/3.0)),
                 v_.z<0?-std::pow(-v_.z, scalar_t(1.0/3.0)):std::pow(v_.z, scalar_t(1.0/3.0)),
                 v_.w<0?-std::pow(-v_.w, scalar_t(1.0/3.0)):std::pow(v_.w, scalar_t(1.0/3.0)));
}
//----

template<typename T>
PFC_INLINE vec4<T> rsqrt(const vec4<T> &v_)
{
  // component-wise reciprocal square root
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(v_.x>0 && v_.y>0 && v_.z>0 && v_.w>0);
  return vec4<T>(scalar_t(1)/std::sqrt(v_.x), scalar_t(1)/std::sqrt(v_.y), scalar_t(1)/std::sqrt(v_.z), scalar_t(1)/std::sqrt(v_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> rsqrt_z(const vec4<T> &v_)
{
  // component-wise reciprocal square root (set to 0 for components less than or equal to zero)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x>0?scalar_t(1)/std::sqrt(v_.x):0,
                 v_.y>0?scalar_t(1)/std::sqrt(v_.y):0,
                 v_.z>0?scalar_t(1)/std::sqrt(v_.z):0,
                 v_.w>0?scalar_t(1)/std::sqrt(v_.w):0);
}
//----

template<typename T>
PFC_INLINE vec4<T> rcbrt(const vec4<T> &v_)
{
  // component-wise reciprocal cubic root
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x<0?-std::pow(-v_.x, scalar_t(-1.0/3.0)):std::pow(v_.x, scalar_t(-1.0/3.0)),
                 v_.y<0?-std::pow(-v_.y, scalar_t(-1.0/3.0)):std::pow(v_.y, scalar_t(-1.0/3.0)),
                 v_.z<0?-std::pow(-v_.z, scalar_t(-1.0/3.0)):std::pow(v_.z, scalar_t(-1.0/3.0)),
                 v_.w<0?-std::pow(-v_.w, scalar_t(-1.0/3.0)):std::pow(v_.w, scalar_t(-1.0/3.0)));
}
//----

template<typename T>
PFC_INLINE vec4<T> rcbrt_z(const vec4<T> &v_)
{
  // component-wise reciprocal cubic root (set to 0 for 0 components)
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(v_.x?v_.x<0?-std::pow(-v_.x, scalar_t(-1.0/3.0)):std::pow(v_.x, scalar_t(-1.0/3.0)):0,
                 v_.y?v_.y<0?-std::pow(-v_.y, scalar_t(-1.0/3.0)):std::pow(v_.y, scalar_t(-1.0/3.0)):0,
                 v_.z?v_.z<0?-std::pow(-v_.z, scalar_t(-1.0/3.0)):std::pow(v_.z, scalar_t(-1.0/3.0)):0,
                 v_.w?v_.w<0?-std::pow(-v_.w, scalar_t(-1.0/3.0)):std::pow(v_.w, scalar_t(-1.0/3.0)):0);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t norm(const vec4<T> &v_)
{
  // norm of the vector (=vector length)
  return std::sqrt(v_.x*v_.x+v_.y*v_.y+v_.z*v_.z+v_.w*v_.w);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm(const vec4<T> &v_)
{
  // reciprocal norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=v_.x*v_.x+v_.y*v_.y+v_.z*v_.z+v_.w*v_.w;
  PFC_ASSERT_PEDANTIC(n2);
  return scalar_t(1)/std::sqrt(n2);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm_z(const vec4<T> &v_)
{
  // reciprocal norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=v_.x*v_.x+v_.y*v_.y+v_.z*v_.z+v_.w*v_.w;
  return n2?scalar_t(1)/std::sqrt(n2):0;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t norm2(const vec4<T> &v_)
{
  // squared norm of the vector
  return v_.x*v_.x+v_.y*v_.y+v_.z*v_.z+v_.w*v_.w;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm2(const vec4<T> &v_)
{
  // reciprocal squared norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=v_.x*v_.x+v_.y*v_.y+v_.z*v_.z+v_.w*v_.w;
  PFC_ASSERT_PEDANTIC(n2);
  return scalar_t(1)/n2;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm2_z(const vec4<T> &v_)
{
  // reciprocal squared norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t v=v_.x*v_.x+v_.y*v_.y+v_.z*v_.z+v_.w*v_.w;
  return v?scalar_t(1)/v:0;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t norm_l1(const vec4<T> &v_)
{
  // L1-norm of the vector (Manhattan norm)
  return abs(v_.x)+abs(v_.y)+abs(v_.z)+abs(v_.w);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm_l1(const vec4<T> &v_)
{
  // reciprocal L1-norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  return scalar_t(1)/(abs(v_.x)+abs(v_.y)+abs(v_.z)+abs(v_.w));
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const vec4<T> &v_)
{
  // reciprocal L1-norm of the vector (return 0 if |v|=0)
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t v=abs(v_.x)+abs(v_.y)+abs(v_.z)+abs(v_.w);
  return v?scalar_t(1)/v:0;
}
//----

template<typename T>
PFC_INLINE vec4<T> exp(const vec4<T> &v_)
{
  // natural exponent
  return vec4<T>(std::exp(v_.x), std::exp(v_.y), std::exp(v_.z), std::exp(v_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> exp2(const vec4<T> &v_)
{
  // 2^x
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(std::pow(scalar_t(2), v_.x), std::pow(scalar_t(2), v_.y), std::pow(scalar_t(2), v_.z), std::pow(scalar_t(2), v_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> ln(const vec4<T> &v_)
{
  // natural logarithm
  return vec4<T>(std::log(v_.x), std::log(v_.y), std::log(v_.z), std::log(v_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> log2(const vec4<T> &v_)
{
  // base-2 logarithm
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(std::log2(v_.x), std::log2(v_.y), std::log2(v_.z), std::log2(v_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> log10(const vec4<T> &v_)
{
  // base-10 logarithm
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(std::log10(v_.x), std::log10(v_.y), std::log10(v_.z), std::log10(v_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> pow(const vec4<T> &v_, typename math<T>::scalar_t power_)
{
  // raises value to the given power
  return vec4<T>(std::pow(v_.x, power_), std::pow(v_.y, power_), std::pow(v_.z, power_), std::pow(v_.w, power_));
}
//----

template<typename T>
PFC_INLINE vec4<T> unit(const vec4<T> &v_)
{
  // unit vector of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=v_.x*v_.x+v_.y*v_.y+v_.z*v_.z+v_.w*v_.w;
  PFC_ASSERT_PEDANTIC(n2);
  scalar_t rs=scalar_t(1)/std::sqrt(n2);
  return vec4<T>(v_.x*rs, v_.y*rs, v_.z*rs, v_.w*rs);
}
//----

template<typename T>
PFC_INLINE vec4<T> unit_z(const vec4<T> &v_)
{
  // unit vector of the vector. if |v|=0, return v=[0, 0, 0, 0]
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t rs=v_.x*v_.x+v_.y*v_.y+v_.z*v_.z+v_.w*v_.w;
  if(!rs)
    return vec4<T>(0, 0, 0, 0);
  rs=scalar_t(1)/std::sqrt(rs);
  return vec4<T>(v_.x*rs, v_.y*rs, v_.z*rs, v_.w*rs);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t dot(const vec4<T> &v0_, const vec4<T> &v1_)
{
  // dot-product of vectors
  return v0_.x*v1_.x+v0_.y*v1_.y+v0_.z*v1_.z+v0_.w*v1_.w;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t dot1(const vec4<T> &v_)
{
  // dot-product with [1, 1, 1, 1]
  return v_.x+v_.y+v_.z+v_.w;
}
//----

template<typename T>
PFC_INLINE void neg(vec4<T> &v_)
{
  // negate the vector
  v_.x=-v_.x;
  v_.y=-v_.y;
  v_.z=-v_.z;
  v_.w=-v_.w;
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_u(vec4<T> &vr_, Rng &rng_)
{
  // random unit vector (even distribution on unit hypersphere)
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t rs, rc, vs, vc;
  sincos(rs, rc, scalar_t(rng_.rand_ureal1())*math<T>::pi);
  sincos(vs, vc, scalar_t(rng_.rand_ureal1())*math<T>::two_pi);
  scalar_t z=scalar_t(rng_.rand_real1());
  vr_.z=z*rs;
  vr_.w=rc;
  scalar_t rad=std::sqrt(scalar_t(1)-z*z)*rs;
  vr_.x=vs*rad;
  vr_.y=vc*rad;
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_real1(vec4<T> &vr_, Rng &rng_)
{
  // random vector where each component is in range [-1, 1]
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=scalar_t(rng_.rand_real1());
  vr_.y=scalar_t(rng_.rand_real1());
  vr_.z=scalar_t(rng_.rand_real1());
  vr_.w=scalar_t(rng_.rand_real1());
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_ureal1(vec4<T> &vr_, Rng &rng_)
{
  // random vector where each component is in range [0, 1]
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=scalar_t(rng_.rand_ureal1());
  vr_.y=scalar_t(rng_.rand_ureal1());
  vr_.z=scalar_t(rng_.rand_ureal1());
  vr_.w=scalar_t(rng_.rand_ureal1());
}
//----

template<typename T>
PFC_INLINE vec4<T> smoothstep(const vec4<T> &v_)
{
  // component-wise smoothstep function
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(v_.x>=0 && v_.x<=scalar_t(1) && v_.y>=0 && v_.y<=scalar_t(1) && v_.z>=0 && v_.z<=scalar_t(1) && v_.w>=0 && v_.w<=scalar_t(1));
  return vec4<T>(v_.x*v_.x*(scalar_t(3)-scalar_t(2)*v_.x),
                 v_.y*v_.y*(scalar_t(3)-scalar_t(2)*v_.y),
                 v_.z*v_.z*(scalar_t(3)-scalar_t(2)*v_.z),
                 v_.w*v_.w*(scalar_t(3)-scalar_t(2)*v_.w));
}
//----

template<typename T>
PFC_INLINE vec4<T> smootherstep(const vec4<T> &v_)
{
  // component-wise smootherstep function
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(v_.x>=0 && v_.x<=scalar_t(1) && v_.y>=0 && v_.y<=scalar_t(1) && v_.z>=0 && v_.z<=scalar_t(1) && v_.w>=0 && v_.w<=scalar_t(1));
  return vec4<T>(v_.x*v_.x*v_.x*(v_.x*(v_.x*scalar_t(6)-scalar_t(15))+scalar_t(10)),
                 v_.y*v_.y*v_.y*(v_.y*(v_.y*scalar_t(6)-scalar_t(15))+scalar_t(10)),
                 v_.z*v_.z*v_.z*(v_.z*(v_.z*scalar_t(6)-scalar_t(15))+scalar_t(10)),
                 v_.w*v_.w*v_.w*(v_.w*(v_.w*scalar_t(6)-scalar_t(15))+scalar_t(10)));
}
//----

template<typename T>
PFC_INLINE vec4<T> lerp(const vec4<T> &v0_, const vec4<T> &v1_, typename math<T>::scalar_t t_)
{
  // linear vector interpolation. f(t=0)=v0, f(t=1)=v1
  return vec4<T>(v0_.x+(v1_.x-v0_.x)*t_,
                 v0_.y+(v1_.y-v0_.y)*t_,
                 v0_.z+(v1_.z-v0_.z)*t_,
                 v0_.w+(v1_.w-v0_.w)*t_);
}
//----

template<typename T> PFC_INLINE vec4<T> reflect(const vec4<T> &v_, const vec4<T> &n_)
{
  // reflect vector about normal: v'=2*n*(v.n)/(n.n)-v
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t d=scalar_t(2)*(v_.x*n_.x+v_.y*n_.y+v_.z*n_.z+v_.w*n_.w)*rcp(n_.x*n_.x+n_.y*n_.y+n_.z*n_.z+n_.w*n_.w);
  return vec4<T>(d*n_.x-v_.x,
                 d*n_.y-v_.y,
                 d*n_.z-v_.z,
                 d*n_.w-v_.w);
}
//----

template<typename T>
PFC_INLINE vec4<T> reflect_u(const vec4<T> &v_, const vec4<T> &n_)
{
  // reflect vector about unit normal: v'=2*n*(v.n)-v
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t d=scalar_t(2)*(v_.x*n_.x+v_.y*n_.y+v_.z*n_.z+v_.w*n_.w);
  return vec4<T>(d*n_.x-v_.x,
                 d*n_.y-v_.y,
                 d*n_.z-v_.z,
                 d*n_.w-v_.w);
}
//----

template<typename T>
PFC_INLINE vec3<T> perspective_project(const vec4<T> &v_)
{
  // perspective project vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t s=scalar_t(1)/v_.w;
  return vec3<T>(v_.x*s, v_.y*s, v_.z*s);
}
//----

template<typename T, typename U>
PFC_INLINE vec4<T> to_vec4(const vec4<U> &v_)
{
  // convert between vec4 types
  typedef typename math<T>::scalar_t scalar_t;
  return vec4<T>(scalar_t(v_.x), scalar_t(v_.y), scalar_t(v_.z), scalar_t(v_.w));
}
//----

namespace priv
{
  template<unsigned shuffle_, typename T>
  struct shuffle_vec4_helper
  {
    static vec4<T> shuffle(const vec4<T>&) {PFC_CTF_ERROR(T, invalid_vector_component_shuffle);}
  };
  #define PFC_VECTOR_SHUFFLE(shuffle__, x__, y__, z__, w__)\
  template<typename T> struct shuffle_vec4_helper<shuffle__, T>\
  {\
    static PFC_INLINE vec4<T> shuffle(const vec4<T> &v_) {return vec4<T>(v_.x__, v_.y__, v_.z__, v_.w__);}\
  };
  PFC_VECTOR_SHUFFLE(0000, x, x, x, x); PFC_VECTOR_SHUFFLE(0001, x, x, x, y); PFC_VECTOR_SHUFFLE(0002, x, x, x, z); PFC_VECTOR_SHUFFLE(0003, x, x, x, w); PFC_VECTOR_SHUFFLE(0010, x, x, y, x); PFC_VECTOR_SHUFFLE(0011, x, x, y, y); PFC_VECTOR_SHUFFLE(0012, x, x, y, z); PFC_VECTOR_SHUFFLE(0013, x, x, y, w); PFC_VECTOR_SHUFFLE(0020, x, x, z, x); PFC_VECTOR_SHUFFLE(0021, x, x, z, y); PFC_VECTOR_SHUFFLE(0022, x, x, z, z); PFC_VECTOR_SHUFFLE(0023, x, x, z, w); PFC_VECTOR_SHUFFLE(0030, x, x, w, x); PFC_VECTOR_SHUFFLE(0031, x, x, w, y); PFC_VECTOR_SHUFFLE(0032, x, x, w, z); PFC_VECTOR_SHUFFLE(0033, x, x, w, w);
  PFC_VECTOR_SHUFFLE(0100, x, y, x, x); PFC_VECTOR_SHUFFLE(0101, x, y, x, y); PFC_VECTOR_SHUFFLE(0102, x, y, x, z); PFC_VECTOR_SHUFFLE(0103, x, y, x, w); PFC_VECTOR_SHUFFLE(0110, x, y, y, x); PFC_VECTOR_SHUFFLE(0111, x, y, y, y); PFC_VECTOR_SHUFFLE(0112, x, y, y, z); PFC_VECTOR_SHUFFLE(0113, x, y, y, w); PFC_VECTOR_SHUFFLE(0120, x, y, z, x); PFC_VECTOR_SHUFFLE(0121, x, y, z, y); PFC_VECTOR_SHUFFLE(0122, x, y, z, z); PFC_VECTOR_SHUFFLE(0123, x, y, z, w); PFC_VECTOR_SHUFFLE(0130, x, y, w, x); PFC_VECTOR_SHUFFLE(0131, x, y, w, y); PFC_VECTOR_SHUFFLE(0132, x, y, w, z); PFC_VECTOR_SHUFFLE(0133, x, y, w, w);
  PFC_VECTOR_SHUFFLE(0200, x, z, x, x); PFC_VECTOR_SHUFFLE(0201, x, z, x, y); PFC_VECTOR_SHUFFLE(0202, x, z, x, z); PFC_VECTOR_SHUFFLE(0203, x, z, x, w); PFC_VECTOR_SHUFFLE(0210, x, z, y, x); PFC_VECTOR_SHUFFLE(0211, x, z, y, y); PFC_VECTOR_SHUFFLE(0212, x, z, y, z); PFC_VECTOR_SHUFFLE(0213, x, z, y, w); PFC_VECTOR_SHUFFLE(0220, x, z, z, x); PFC_VECTOR_SHUFFLE(0221, x, z, z, y); PFC_VECTOR_SHUFFLE(0222, x, z, z, z); PFC_VECTOR_SHUFFLE(0223, x, z, z, w); PFC_VECTOR_SHUFFLE(0230, x, z, w, x); PFC_VECTOR_SHUFFLE(0231, x, z, w, y); PFC_VECTOR_SHUFFLE(0232, x, z, w, z); PFC_VECTOR_SHUFFLE(0233, x, z, w, w);
  PFC_VECTOR_SHUFFLE(0300, x, w, x, x); PFC_VECTOR_SHUFFLE(0301, x, w, x, y); PFC_VECTOR_SHUFFLE(0302, x, w, x, z); PFC_VECTOR_SHUFFLE(0303, x, w, x, w); PFC_VECTOR_SHUFFLE(0310, x, w, y, x); PFC_VECTOR_SHUFFLE(0311, x, w, y, y); PFC_VECTOR_SHUFFLE(0312, x, w, y, z); PFC_VECTOR_SHUFFLE(0313, x, w, y, w); PFC_VECTOR_SHUFFLE(0320, x, w, z, x); PFC_VECTOR_SHUFFLE(0321, x, w, z, y); PFC_VECTOR_SHUFFLE(0322, x, w, z, z); PFC_VECTOR_SHUFFLE(0323, x, w, z, w); PFC_VECTOR_SHUFFLE(0330, x, w, w, x); PFC_VECTOR_SHUFFLE(0331, x, w, w, y); PFC_VECTOR_SHUFFLE(0332, x, w, w, z); PFC_VECTOR_SHUFFLE(0333, x, w, w, w);
  PFC_VECTOR_SHUFFLE(1000, y, x, x, x); PFC_VECTOR_SHUFFLE(1001, y, x, x, y); PFC_VECTOR_SHUFFLE(1002, y, x, x, z); PFC_VECTOR_SHUFFLE(1003, y, x, x, w); PFC_VECTOR_SHUFFLE(1010, y, x, y, x); PFC_VECTOR_SHUFFLE(1011, y, x, y, y); PFC_VECTOR_SHUFFLE(1012, y, x, y, z); PFC_VECTOR_SHUFFLE(1013, y, x, y, w); PFC_VECTOR_SHUFFLE(1020, y, x, z, x); PFC_VECTOR_SHUFFLE(1021, y, x, z, y); PFC_VECTOR_SHUFFLE(1022, y, x, z, z); PFC_VECTOR_SHUFFLE(1023, y, x, z, w); PFC_VECTOR_SHUFFLE(1030, y, x, w, x); PFC_VECTOR_SHUFFLE(1031, y, x, w, y); PFC_VECTOR_SHUFFLE(1032, y, x, w, z); PFC_VECTOR_SHUFFLE(1033, y, x, w, w);
  PFC_VECTOR_SHUFFLE(1100, y, y, x, x); PFC_VECTOR_SHUFFLE(1101, y, y, x, y); PFC_VECTOR_SHUFFLE(1102, y, y, x, z); PFC_VECTOR_SHUFFLE(1103, y, y, x, w); PFC_VECTOR_SHUFFLE(1110, y, y, y, x); PFC_VECTOR_SHUFFLE(1111, y, y, y, y); PFC_VECTOR_SHUFFLE(1112, y, y, y, z); PFC_VECTOR_SHUFFLE(1113, y, y, y, w); PFC_VECTOR_SHUFFLE(1120, y, y, z, x); PFC_VECTOR_SHUFFLE(1121, y, y, z, y); PFC_VECTOR_SHUFFLE(1122, y, y, z, z); PFC_VECTOR_SHUFFLE(1123, y, y, z, w); PFC_VECTOR_SHUFFLE(1130, y, y, w, x); PFC_VECTOR_SHUFFLE(1131, y, y, w, y); PFC_VECTOR_SHUFFLE(1132, y, y, w, z); PFC_VECTOR_SHUFFLE(1133, y, y, w, w);
  PFC_VECTOR_SHUFFLE(1200, y, z, x, x); PFC_VECTOR_SHUFFLE(1201, y, z, x, y); PFC_VECTOR_SHUFFLE(1202, y, z, x, z); PFC_VECTOR_SHUFFLE(1203, y, z, x, w); PFC_VECTOR_SHUFFLE(1210, y, z, y, x); PFC_VECTOR_SHUFFLE(1211, y, z, y, y); PFC_VECTOR_SHUFFLE(1212, y, z, y, z); PFC_VECTOR_SHUFFLE(1213, y, z, y, w); PFC_VECTOR_SHUFFLE(1220, y, z, z, x); PFC_VECTOR_SHUFFLE(1221, y, z, z, y); PFC_VECTOR_SHUFFLE(1222, y, z, z, z); PFC_VECTOR_SHUFFLE(1223, y, z, z, w); PFC_VECTOR_SHUFFLE(1230, y, z, w, x); PFC_VECTOR_SHUFFLE(1231, y, z, w, y); PFC_VECTOR_SHUFFLE(1232, y, z, w, z); PFC_VECTOR_SHUFFLE(1233, y, z, w, w);
  PFC_VECTOR_SHUFFLE(1300, y, w, x, x); PFC_VECTOR_SHUFFLE(1301, y, w, x, y); PFC_VECTOR_SHUFFLE(1302, y, w, x, z); PFC_VECTOR_SHUFFLE(1303, y, w, x, w); PFC_VECTOR_SHUFFLE(1310, y, w, y, x); PFC_VECTOR_SHUFFLE(1311, y, w, y, y); PFC_VECTOR_SHUFFLE(1312, y, w, y, z); PFC_VECTOR_SHUFFLE(1313, y, w, y, w); PFC_VECTOR_SHUFFLE(1320, y, w, z, x); PFC_VECTOR_SHUFFLE(1321, y, w, z, y); PFC_VECTOR_SHUFFLE(1322, y, w, z, z); PFC_VECTOR_SHUFFLE(1323, y, w, z, w); PFC_VECTOR_SHUFFLE(1330, y, w, w, x); PFC_VECTOR_SHUFFLE(1331, y, w, w, y); PFC_VECTOR_SHUFFLE(1332, y, w, w, z); PFC_VECTOR_SHUFFLE(1333, y, w, w, w);
  PFC_VECTOR_SHUFFLE(2000, z, x, x, x); PFC_VECTOR_SHUFFLE(2001, z, x, x, y); PFC_VECTOR_SHUFFLE(2002, z, x, x, z); PFC_VECTOR_SHUFFLE(2003, z, x, x, w); PFC_VECTOR_SHUFFLE(2010, z, x, y, x); PFC_VECTOR_SHUFFLE(2011, z, x, y, y); PFC_VECTOR_SHUFFLE(2012, z, x, y, z); PFC_VECTOR_SHUFFLE(2013, z, x, y, w); PFC_VECTOR_SHUFFLE(2020, z, x, z, x); PFC_VECTOR_SHUFFLE(2021, z, x, z, y); PFC_VECTOR_SHUFFLE(2022, z, x, z, z); PFC_VECTOR_SHUFFLE(2023, z, x, z, w); PFC_VECTOR_SHUFFLE(2030, z, x, w, x); PFC_VECTOR_SHUFFLE(2031, z, x, w, y); PFC_VECTOR_SHUFFLE(2032, z, x, w, z); PFC_VECTOR_SHUFFLE(2033, z, x, w, w);
  PFC_VECTOR_SHUFFLE(2100, z, y, x, x); PFC_VECTOR_SHUFFLE(2101, z, y, x, y); PFC_VECTOR_SHUFFLE(2102, z, y, x, z); PFC_VECTOR_SHUFFLE(2103, z, y, x, w); PFC_VECTOR_SHUFFLE(2110, z, y, y, x); PFC_VECTOR_SHUFFLE(2111, z, y, y, y); PFC_VECTOR_SHUFFLE(2112, z, y, y, z); PFC_VECTOR_SHUFFLE(2113, z, y, y, w); PFC_VECTOR_SHUFFLE(2120, z, y, z, x); PFC_VECTOR_SHUFFLE(2121, z, y, z, y); PFC_VECTOR_SHUFFLE(2122, z, y, z, z); PFC_VECTOR_SHUFFLE(2123, z, y, z, w); PFC_VECTOR_SHUFFLE(2130, z, y, w, x); PFC_VECTOR_SHUFFLE(2131, z, y, w, y); PFC_VECTOR_SHUFFLE(2132, z, y, w, z); PFC_VECTOR_SHUFFLE(2133, z, y, w, w);
  PFC_VECTOR_SHUFFLE(2200, z, z, x, x); PFC_VECTOR_SHUFFLE(2201, z, z, x, y); PFC_VECTOR_SHUFFLE(2202, z, z, x, z); PFC_VECTOR_SHUFFLE(2203, z, z, x, w); PFC_VECTOR_SHUFFLE(2210, z, z, y, x); PFC_VECTOR_SHUFFLE(2211, z, z, y, y); PFC_VECTOR_SHUFFLE(2212, z, z, y, z); PFC_VECTOR_SHUFFLE(2213, z, z, y, w); PFC_VECTOR_SHUFFLE(2220, z, z, z, x); PFC_VECTOR_SHUFFLE(2221, z, z, z, y); PFC_VECTOR_SHUFFLE(2222, z, z, z, z); PFC_VECTOR_SHUFFLE(2223, z, z, z, w); PFC_VECTOR_SHUFFLE(2230, z, z, w, x); PFC_VECTOR_SHUFFLE(2231, z, z, w, y); PFC_VECTOR_SHUFFLE(2232, z, z, w, z); PFC_VECTOR_SHUFFLE(2233, z, z, w, w);
  PFC_VECTOR_SHUFFLE(2300, z, w, x, x); PFC_VECTOR_SHUFFLE(2301, z, w, x, y); PFC_VECTOR_SHUFFLE(2302, z, w, x, z); PFC_VECTOR_SHUFFLE(2303, z, w, x, w); PFC_VECTOR_SHUFFLE(2310, z, w, y, x); PFC_VECTOR_SHUFFLE(2311, z, w, y, y); PFC_VECTOR_SHUFFLE(2312, z, w, y, z); PFC_VECTOR_SHUFFLE(2313, z, w, y, w); PFC_VECTOR_SHUFFLE(2320, z, w, z, x); PFC_VECTOR_SHUFFLE(2321, z, w, z, y); PFC_VECTOR_SHUFFLE(2322, z, w, z, z); PFC_VECTOR_SHUFFLE(2323, z, w, z, w); PFC_VECTOR_SHUFFLE(2330, z, w, w, x); PFC_VECTOR_SHUFFLE(2331, z, w, w, y); PFC_VECTOR_SHUFFLE(2332, z, w, w, z); PFC_VECTOR_SHUFFLE(2333, z, w, w, w);
  PFC_VECTOR_SHUFFLE(3000, w, x, x, x); PFC_VECTOR_SHUFFLE(3001, w, x, x, y); PFC_VECTOR_SHUFFLE(3002, w, x, x, z); PFC_VECTOR_SHUFFLE(3003, w, x, x, w); PFC_VECTOR_SHUFFLE(3010, w, x, y, x); PFC_VECTOR_SHUFFLE(3011, w, x, y, y); PFC_VECTOR_SHUFFLE(3012, w, x, y, z); PFC_VECTOR_SHUFFLE(3013, w, x, y, w); PFC_VECTOR_SHUFFLE(3020, w, x, z, x); PFC_VECTOR_SHUFFLE(3021, w, x, z, y); PFC_VECTOR_SHUFFLE(3022, w, x, z, z); PFC_VECTOR_SHUFFLE(3023, w, x, z, w); PFC_VECTOR_SHUFFLE(3030, w, x, w, x); PFC_VECTOR_SHUFFLE(3031, w, x, w, y); PFC_VECTOR_SHUFFLE(3032, w, x, w, z); PFC_VECTOR_SHUFFLE(3033, w, x, w, w);
  PFC_VECTOR_SHUFFLE(3100, w, y, x, x); PFC_VECTOR_SHUFFLE(3101, w, y, x, y); PFC_VECTOR_SHUFFLE(3102, w, y, x, z); PFC_VECTOR_SHUFFLE(3103, w, y, x, w); PFC_VECTOR_SHUFFLE(3110, w, y, y, x); PFC_VECTOR_SHUFFLE(3111, w, y, y, y); PFC_VECTOR_SHUFFLE(3112, w, y, y, z); PFC_VECTOR_SHUFFLE(3113, w, y, y, w); PFC_VECTOR_SHUFFLE(3120, w, y, z, x); PFC_VECTOR_SHUFFLE(3121, w, y, z, y); PFC_VECTOR_SHUFFLE(3122, w, y, z, z); PFC_VECTOR_SHUFFLE(3123, w, y, z, w); PFC_VECTOR_SHUFFLE(3130, w, y, w, x); PFC_VECTOR_SHUFFLE(3131, w, y, w, y); PFC_VECTOR_SHUFFLE(3132, w, y, w, z); PFC_VECTOR_SHUFFLE(3133, w, y, w, w);
  PFC_VECTOR_SHUFFLE(3200, w, z, x, x); PFC_VECTOR_SHUFFLE(3201, w, z, x, y); PFC_VECTOR_SHUFFLE(3202, w, z, x, z); PFC_VECTOR_SHUFFLE(3203, w, z, x, w); PFC_VECTOR_SHUFFLE(3210, w, z, y, x); PFC_VECTOR_SHUFFLE(3211, w, z, y, y); PFC_VECTOR_SHUFFLE(3212, w, z, y, z); PFC_VECTOR_SHUFFLE(3213, w, z, y, w); PFC_VECTOR_SHUFFLE(3220, w, z, z, x); PFC_VECTOR_SHUFFLE(3221, w, z, z, y); PFC_VECTOR_SHUFFLE(3222, w, z, z, z); PFC_VECTOR_SHUFFLE(3223, w, z, z, w); PFC_VECTOR_SHUFFLE(3230, w, z, w, x); PFC_VECTOR_SHUFFLE(3231, w, z, w, y); PFC_VECTOR_SHUFFLE(3232, w, z, w, z); PFC_VECTOR_SHUFFLE(3233, w, z, w, w);
  PFC_VECTOR_SHUFFLE(3300, w, w, x, x); PFC_VECTOR_SHUFFLE(3301, w, w, x, y); PFC_VECTOR_SHUFFLE(3302, w, w, x, z); PFC_VECTOR_SHUFFLE(3303, w, w, x, w); PFC_VECTOR_SHUFFLE(3310, w, w, y, x); PFC_VECTOR_SHUFFLE(3311, w, w, y, y); PFC_VECTOR_SHUFFLE(3312, w, w, y, z); PFC_VECTOR_SHUFFLE(3313, w, w, y, w); PFC_VECTOR_SHUFFLE(3320, w, w, z, x); PFC_VECTOR_SHUFFLE(3321, w, w, z, y); PFC_VECTOR_SHUFFLE(3322, w, w, z, z); PFC_VECTOR_SHUFFLE(3323, w, w, z, w); PFC_VECTOR_SHUFFLE(3330, w, w, w, x); PFC_VECTOR_SHUFFLE(3331, w, w, w, y); PFC_VECTOR_SHUFFLE(3332, w, w, w, z); PFC_VECTOR_SHUFFLE(3333, w, w, w, w);
  #undef PFC_VECTOR_SHUFFLE
} // namespace priv
//----

template<unsigned shuffle_, typename T>
PFC_INLINE vec4<T> shuffle(const vec4<T> &v_)
{
  return priv::shuffle_vec4_helper<shuffle_, T>::shuffle(v_);
}
//----

template<typename T>
PFC_INLINE void pack_u1(vec4_32 &vr_, const vec4<T> &v_)
{
  // pack 4d vector (components in range [0, 1]) to 32-bit 4d vector
  PFC_ASSERT_PEDANTIC_MSG(is_sat(v_), ("All vector components [%f, %f, %f, %f] must be in range [0, 1]\r\n", float(v_.x), float(v_.y), float(v_.z), float(v_.w)));
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=uint8_t(v_.x*scalar_t(255.999));
  vr_.y=uint8_t(v_.y*scalar_t(255.999));
  vr_.z=uint8_t(v_.z*scalar_t(255.999));
  vr_.w=uint8_t(v_.w*scalar_t(255.999));
}
//----

template<typename T>
PFC_INLINE void pack_s1(vec4_32 &vr_, const vec4<T> &v_)
{
  // pack 4d vector (components in range [-1, 1]) to 32-bit 4d vector
  PFC_ASSERT_PEDANTIC_MSG(is_ssat(v_), ("All vector components [%f, %f, %f, %f] must be in range [-1, 1]\r\n", float(v_.x), float(v_.y), float(v_.z), float(v_.w)));
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=uint8_t(v_.x*scalar_t(127.999)+scalar_t(128.0));
  vr_.y=uint8_t(v_.y*scalar_t(127.999)+scalar_t(128.0));
  vr_.z=uint8_t(v_.z*scalar_t(127.999)+scalar_t(128.0));
  vr_.w=uint8_t(v_.w*scalar_t(127.999)+scalar_t(128.0));
}
//----

template<typename T>
PFC_INLINE void unpack_u1(vec4<T> &vr_, const vec4_32 &v_)
{
  // unpack 4d vector (components in range [0, 1]) from 32-bit 4d vector
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=v_.x*scalar_t(1.0/255.0);
  vr_.y=v_.y*scalar_t(1.0/255.0);
  vr_.z=v_.z*scalar_t(1.0/255.0);
  vr_.w=v_.w*scalar_t(1.0/255.0);
}
//----

template<typename T>
PFC_INLINE void unpack_s1(vec4<T> &vr_, const vec4_32 &v_)
{
  // unpack 4d vector (components in range [-1, 1]) from 32-bit 4d vector
  typedef typename math<T>::scalar_t scalar_t;
  vr_.x=v_.x*scalar_t(2.0/255.0)-scalar_t(1);
  vr_.y=v_.y*scalar_t(2.0/255.0)-scalar_t(1);
  vr_.z=v_.z*scalar_t(2.0/255.0)-scalar_t(1);
  vr_.w=v_.w*scalar_t(2.0/255.0)-scalar_t(1);
}
//----------------------------------------------------------------------------


//============================================================================
// mat22
//============================================================================
template<typename T> const mat22<T> mat22<T>::s_zero(T(0));
template<typename T> const mat22<T> mat22<T>::s_one(T(1));
template<typename T> const mat22<T> mat22<T>::s_neg_one(T(-1));
template<typename T> const mat22<T> mat22<T>::s_identity(T(1),    0,
                                                            0, T(1));
//----------------------------------------------------------------------------

template<typename T>
mat22<T>::mat22()
{
}
//----

template<typename T>
mat22<T>::mat22(T s_)
{
  // init matrix with scalar
  x.x=s_; x.y=s_;
  y.x=s_; y.y=s_;
}
//----

template<typename T>
mat22<T>::mat22(T d0_, T d1_)
{
  // init matrix with diagonal scalars
  x.x=d0_; x.y=0;
  y.x=0;   y.y=d1_;
}
//----

template<typename T>
mat22<T>::mat22(T m00_, T m01_,
                T m10_, T m11_)
{
  // init matrix with scalars
  x.x=m00_; x.y=m01_;
  y.x=m10_; y.y=m11_;
}
//----

template<typename T>
mat22<T>::mat22(const vec2<T> &diag_)
{
  // init matrix with diagonal vector
  x.x=diag_.x; x.y=0;
  y.x=0;       y.y=diag_.y;
}
//----

template<typename T>
mat22<T>::mat22(const vec2<T> &row0_,
                const vec2<T> &row1_)
{
  // init matrix with row-vectors
  x.x=row0_.x; x.y=row0_.y;
  y.x=row1_.x; y.y=row1_.y;
}
//----

template<typename T>
mat22<T>::mat22(const mat33<T> &m_)
{
  // init matrix with 3d matrix (upper-left matrix)
  x.x=m_.x.x; x.y=m_.x.y;
  y.x=m_.y.x; y.y=m_.y.y;
}
//----

template<typename T>
mat22<T>::mat22(const T *a_)
{
  // init matrix with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x.x=a_[0]; x.y=a_[1];
  y.x=a_[2]; y.y=a_[3];
}
//----------------------------------------------------------------------------

template<typename T>
const vec2<T> &mat22<T>::operator[](unsigned row_) const
{
  // return reference to nth vector (x=0, y=1)
  PFC_ASSERT_PEDANTIC(row_<2);
  return reinterpret_cast<const vec2<T>*>(this)[row_];
}
//----

template<typename T>
vec2<T> &mat22<T>::operator[](unsigned row_)
{
  // return reference to nth vector (x=0, y=1)
  PFC_ASSERT_PEDANTIC(row_<2);
  return reinterpret_cast<vec2<T>*>(this)[row_];
}
//----

template<typename T>
void mat22<T>::set(T s_)
{
  // set matrix with scalar
  x.x=s_; x.y=s_;
  y.x=s_; y.y=s_;
}
//----

template<typename T>
void mat22<T>::set(T d0_, T d1_)
{
  // set matrix with diagonal scalars
  x.x=d0_; x.y=0;
  y.x=0;   y.y=d1_;
}
//----

template<typename T>
void mat22<T>::set(T m00_, T m01_,
                   T m10_, T m11_)
{
  // set matrix with scalars
  x.x=m00_; x.y=m01_;
  y.x=m10_; y.y=m11_;
}
//----

template<typename T>
void mat22<T>::set(const vec2<T> &row0_,
                   const vec2<T> &row1_)
{
  // set matrix with row-vectors
  x.x=row0_.x; x.y=row0_.y;
  y.x=row1_.x; y.y=row1_.y;
}
//----

template<typename T>
void mat22<T>::set(const mat22<T> &m_)
{
  // set matrix with matrix
  x.x=m_.x.x; x.y=m_.x.y;
  y.x=m_.y.x; y.y=m_.y.y;
}
//----

template<typename T>
void mat22<T>::set(const mat33<T> &m_)
{
  // set matrix with 3d matrix (upper-left matrix)
  x.x=m_.x.x; x.y=m_.x.y;
  y.x=m_.y.x; y.y=m_.y.y;
}
//----

template<typename T>
void mat22<T>::set(const T *a_)
{
  // set matrix with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x.x=a_[0]; x.y=a_[1];
  y.x=a_[2]; y.y=a_[3];
}
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE bool is_zero(const mat22<T> &m_)
{
  // test for zero-matrix
  return    m_.x.x==0 && m_.x.y==0
         && m_.y.x==0 && m_.y.y==0;
}
//----

template<typename T>
PFC_INLINE bool is_sat(const mat22<T> &m_)
{
  // test for saturated matrix
  return is_sat(m_.x) && is_sat(m_.y);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const mat22<T> &m_)
{
  // test for signed saturated matrix
  return is_ssat(m_.x) && is_ssat(m_.y);
}
//----

template<typename T>
PFC_INLINE bool operator==(const mat22<T> &m0_, const mat22<T> &m1_)
{
  // test for equality of matrices
  return    m0_.x.x==m1_.x.x && m0_.x.y==m1_.x.y
         && m0_.y.x==m1_.y.x && m0_.y.y==m1_.y.y;
}
//----

template<typename T>
PFC_INLINE bool operator==(const mat22<T> &m_, typename math<T>::scalar_t s_)
{
  // test for equality of matrix and scalar
  return    m_.x.x==s_ && m_.x.y==s_
         && m_.y.x==s_ && m_.y.y==s_;
}
//----

template<typename T>
PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const mat22<T> &m_)
{
  // test for equality of matrix and scalar
  return    s_==m_.x.x && s_==m_.x.y
         && s_==m_.y.x && s_==m_.y.y;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const mat22<T> &m0_, const mat22<T> &m1_)
{
  // test for inequality of matrices
  return    m0_.x.x!=m1_.x.x || m0_.x.y!=m1_.x.y
         || m0_.y.x!=m1_.y.x || m0_.y.y!=m1_.y.y;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const mat22<T> &m_, typename math<T>::scalar_t s_)
{
  // test for inequality of matrix and scalar
  return    m_.x.x!=s_ || m_.x.y!=s_
         || m_.y.x!=s_ || m_.y.y!=s_;
}
//----

template<typename T>
PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const mat22<T> &m_)
{
  // test for inequality of matrix and scalar
  return    s_!=m_.x.x || s_!=m_.x.y
         || s_!=m_.y.x || s_!=m_.y.y;
}
//----

template<typename T>
PFC_INLINE void operator+=(mat22<T> &mr_, const mat22<T> &m_)
{
  // add matrix to matrix
  mr_.x.x+=m_.x.x; mr_.x.y+=m_.x.y;
  mr_.y.x+=m_.y.x; mr_.y.y+=m_.y.y;
}
//----

template<typename T>
PFC_INLINE void operator+=(mat22<T> &mr_, typename math<T>::scalar_t s_)
{
  // add matrix to matrix
  mr_.x.x+=s_; mr_.x.y+=s_;
  mr_.y.x+=s_; mr_.y.y+=s_;
}
//----

template<typename T>
PFC_INLINE void operator-=(mat22<T> &mr_, const mat22<T> &m_)
{
  // subtract matrix from matrix
  mr_.x.x-=m_.x.x; mr_.x.y-=m_.x.y;
  mr_.y.x-=m_.y.x; mr_.y.y-=m_.y.y;
}
//----

template<typename T>
PFC_INLINE void operator-=(mat22<T> &mr_, typename math<T>::scalar_t s_)
{
  // subtract matrix from matrix
  mr_.x.x-=s_; mr_.x.y-=s_;
  mr_.y.x-=s_; mr_.y.y-=s_;
}
//----

template<typename T>
PFC_INLINE void operator*=(mat22<T> &mr_, const mat22<T> &m_)
{
  // multiply matrix by matrix
  vec2<T> v=mr_.x;
  mr_.x.x=v.x*m_.x.x+v.y*m_.y.x; mr_.x.y=v.x*m_.x.y+v.y*m_.y.y;
  v=mr_.y;
  mr_.y.x=v.x*m_.x.x+v.y*m_.y.x; mr_.y.y=v.x*m_.x.y+v.y*m_.y.y;
}
//----

template<typename T>
PFC_INLINE void operator*=(mat22<T> &mr_, typename math<T>::scalar_t s_)
{
  // multiply matrix by scalar
  mr_.x.x*=s_; mr_.x.y*=s_;
  mr_.y.x*=s_; mr_.y.y*=s_;
}
//----

template<typename T>
PFC_INLINE void operator/=(mat22<T> &mr_, typename math<T>::scalar_t s_)
{
  // divide matrix by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  mr_.x.x*=rs; mr_.x.y*=rs;
  mr_.y.x*=rs; mr_.y.y*=rs;
}
//----

template<typename T>
PFC_INLINE mat22<T> operator+(const mat22<T> &m0_, const mat22<T> &m1_)
{
  // add matrix to matrix
  return mat22<T>(m0_.x.x+m1_.x.x, m0_.x.y+m1_.x.y,
                  m0_.y.x+m1_.y.x, m0_.y.y+m1_.y.y);
}
//----

template<typename T>
PFC_INLINE mat22<T> operator+(const mat22<T> &m_, typename math<T>::scalar_t s_)
{
  // add scalar to matrix
  return mat22<T>(m_.x.x+s_, m_.x.y+s_,
                  m_.y.x+s_, m_.y.y+s_);
}
//----

template<typename T>
PFC_INLINE mat22<T> operator+(typename math<T>::scalar_t s_, const mat22<T> &m_)
{
  // add matrix to scalar
  return mat22<T>(s_+m_.x.x, s_+m_.x.y,
                  s_+m_.y.x, s_+m_.y.y);
}
//----

template<typename T>
PFC_INLINE mat22<T> operator-(const mat22<T> &m0_, const mat22<T> &m1_)
{
  // subtract matrix from matrix
  return mat22<T>(m0_.x.x-m1_.x.x, m0_.x.y-m1_.x.y,
                  m0_.y.x-m1_.y.x, m0_.y.y-m1_.y.y);
}
//----

template<typename T>
PFC_INLINE mat22<T> operator-(const mat22<T> &m_, typename math<T>::scalar_t s_)
{
  // subtract matrix from matrix
  return mat22<T>(m_.x.x-s_, m_.x.y-s_,
                  m_.y.x-s_, m_.y.y-s_);
}
//----

template<typename T>
PFC_INLINE mat22<T> operator-(typename math<T>::scalar_t s_, const mat22<T> &m_)
{
  // subtract matrix from matrix
  return mat22<T>(s_-m_.x.x, s_-m_.x.y,
                  s_-m_.y.x, s_-m_.y.y);
}
//----

template<typename T>
PFC_INLINE mat22<T> operator-(const mat22<T> &m_)
{
  // negate matrix
  return mat22<T>(-m_.x.x, -m_.x.y,
                  -m_.y.x, -m_.y.y);
}
//----

template<typename T>
PFC_INLINE mat22<T> operator*(const mat22<T> &m0_, const mat22<T> &m1_)
{
  // multiply matrix by matrix
  return mat22<T>(m0_.x.x*m1_.x.x+m0_.x.y*m1_.y.x, m0_.x.x*m1_.x.y+m0_.x.y*m1_.y.y,
                  m0_.y.x*m1_.x.x+m0_.y.y*m1_.y.x, m0_.y.x*m1_.x.y+m0_.y.y*m1_.y.y);
}
//----

template<typename T>
PFC_INLINE mat22<T> operator*(const mat22<T> &m_, typename math<T>::scalar_t s_)
{
  // multiply matrix by scalar
  return mat22<T>(m_.x.x*s_, m_.x.y*s_,
                  m_.y.x*s_, m_.y.y*s_);
}
//----

template<typename T>
PFC_INLINE mat22<T> operator*(typename math<T>::scalar_t s_, const mat22<T> &m_)
{
  // multiply matrix by scalar
  return mat22<T>(s_*m_.x.x, s_*m_.x.y,
                  s_*m_.y.x, s_*m_.y.y);
}
//----

template<typename T>
PFC_INLINE mat22<T> operator/(const mat22<T> &m_, typename math<T>::scalar_t s_)
{
  // divide matrix by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  return mat22<T>(m_.x.x*rs, m_.x.y*rs,
                  m_.y.x*rs, m_.y.y*rs);
}
//----

template<typename T>
PFC_INLINE mat22<T> mul(const mat22<T> &m0_, const mat22<T> &m1_)
{
  // component-wise matrix multiply: m0_*m1_
  return mat22<T>(m0_.x.x*m1_.x.x, m0_.x.y*m1_.x.y,
                  m0_.y.x*m1_.y.x, m0_.y.y*m1_.y.y);
}
//----

template<typename T>
PFC_INLINE mat22<T> madd(const mat22<T> &mm0_, const mat22<T> &mm1_, const mat22<T> &ma_)
{
  // component-wise multiply-add: mm0_*mm1_+ma_
  return mat22<T>(mm0_.x.x*mm1_.x.x+ma_.x.x, mm0_.x.y*mm1_.x.y+ma_.x.y,
                  mm0_.y.x*mm1_.y.x+ma_.y.x, mm0_.y.y*mm1_.y.y+ma_.y.y);
}
//----

template<typename T>
PFC_INLINE mat22<T> madd(const mat22<T> &mm_, typename math<T>::scalar_t sm_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: mm_*sm_+sa_
  return mat22<T>(mm_.x.x*sm_+sa_, mm_.x.y*sm_+sa_,
                  mm_.y.x*sm_+sa_, mm_.y.y*sm_+sa_);
}
//----

template<typename T>
PFC_INLINE mat22<T> madd(const mat22<T> &mm0_, const mat22<T> &mm1_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: mm0_*mm1_+sa_
  return mat22<T>(mm0_.x.x*mm1_.x.x+sa_, mm0_.x.y*mm1_.x.y+sa_,
                  mm0_.y.x*mm1_.y.x+sa_, mm0_.y.y*mm1_.y.y+sa_);
}
//----

template<typename T>
PFC_INLINE mat22<T> madd(const mat22<T> &mm_, typename math<T>::scalar_t sm_, const mat22<T> &ma_)
{
  // component-wise multiply-add: mm_*sm_+ma_
  return mat22<T>(mm_.x.x*sm_+ma_.x.x, mm_.x.y*sm_+ma_.x.y,
                  mm_.y.x*sm_+ma_.y.x, mm_.y.y*sm_+ma_.y.y);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t det(const mat22<T> &m_)
{
  // determinant of the matrix
  return m_.x.x*m_.y.y-m_.x.y*m_.y.x;
}
//----

template<typename T>
PFC_INLINE mat22<T> inv(const mat22<T> &m_, typename math<T>::scalar_t *det_)
{
  // calculate matrix determinant
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t d=m_.x.x*m_.y.y-m_.x.y*m_.y.x;
  if(*det_)
    *det_=d;
  if(!d)
    return mat22<T>::s_zero;

  // invert the matrix
  scalar_t rd=scalar_t(1)/d;
  return mat22<T>( m_.y.y*rd, -m_.x.y*rd,
                  -m_.y.x*rd,  m_.x.x*rd);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t tr(const mat22<T> &m_)
{
  // trace of the matrix
  return m_.x.x+m_.y.y;
}
//----

template<typename T>
PFC_INLINE void identity(mat22<T> &m_)
{
  // set identity
  typedef typename math<T>::scalar_t scalar_t;
  m_.x.x=scalar_t(1); m_.x.y=0;
  m_.y.x=0;           m_.y.y=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE void transpose(mat22<T> &m_)
{
  // transpose the matrix
  typename math<T>::scalar_t t=m_.y.x;
  m_.y.x=m_.x.y;
  m_.x.y=t;
}
//----

template<typename T>
PFC_INLINE void transpose(mat22<T> &res_, const mat22<T> &m_)
{
  // transpose the matrix
  res_.x.x=m_.x.x; res_.x.y=m_.y.x;
  res_.y.x=m_.x.y; res_.y.y=m_.y.y;
}
//----

template<typename T>
PFC_INLINE void neg(mat22<T> &m_)
{
  // negate the matrix
  m_.x.x=-m_.x.x; m_.x.y=-m_.x.y;
  m_.y.x=-m_.y.x; m_.y.y=-m_.y.y;
}
//----

template<typename T>
PFC_INLINE mat22<T> lerp(const mat22<T> &m0_, const mat22<T> &m1_, typename math<T>::scalar_t t_)
{
  // linear matrix interpolation. f(t=0)=v0, f(t=1)=v1
  return mat22<T>(m0_.x.x+(m1_.x.x-m0_.x.x)*t_, m0_.x.y+(m1_.x.y-m0_.x.y)*t_,
                  m0_.y.x+(m1_.y.x-m0_.y.x)*t_, m0_.y.y+(m1_.y.y-m0_.y.y)*t_);
}
//----

template<typename T>
PFC_INLINE void lerp(mat22<T> &res_, const mat22<T> &m0_, const mat22<T> &m1_, typename math<T>::scalar_t t_)
{
  // linear matrix interpolation. f(t=0)=v0, f(t=1)=v1
  res_.x.x=m0_.x.x+(m1_.x.x-m0_.x.x)*t_; res_.x.y=m0_.x.y+(m1_.x.y-m0_.x.y)*t_;
  res_.y.x=m0_.y.x+(m1_.y.x-m0_.y.x)*t_; res_.y.y=m0_.y.y+(m1_.y.y-m0_.y.y)*t_;
}
//-----

template<typename T, typename U>
PFC_INLINE mat22<T> to_mat22(const mat22<U> &m_)
{
  // convert between mat22 types
  typedef typename math<T>::scalar_t scalar_t;
  return mat22<T>(scalar_t(m_.x.x), scalar_t(m_.x.y),
                  scalar_t(m_.y.x), scalar_t(m_.y.y));
}
//----

template<typename T>
PFC_INLINE void normalize(mat22<T> &m_)
{
  // normalize matrix vectors
  m_.x=unit(m_.x);
  m_.y=unit(m_.y);
}
//----------------------------------------------------------------------------


//============================================================================
// mat33
//============================================================================
template<typename T> const mat33<T> mat33<T>::s_zero(T(0));
template<typename T> const mat33<T> mat33<T>::s_one(T(1));
template<typename T> const mat33<T> mat33<T>::s_neg_one(T(-1));
template<typename T> const mat33<T> mat33<T>::s_identity(T(1),    0,    0,
                                                            0, T(1),    0,
                                                            0,    0, T(1));
//----------------------------------------------------------------------------

template<typename T>
mat33<T>::mat33()
{
}
//----

template<typename T>
mat33<T>::mat33(T s_)
{
  // init matrix with scalar
  x.x=s_; x.y=s_; x.z=s_;
  y.x=s_; y.y=s_; y.z=s_;
  z.x=s_; z.y=s_; z.z=s_;
}
//----

template<typename T>
mat33<T>::mat33(T d0_, T d1_, T d2_)
{
  // init matrix with diagonal scalars
  x.x=d0_; x.y=0;   x.z=0;
  y.x=0;   y.y=d1_; y.z=0;
  z.x=0;   z.y=0;   z.z=d2_;
}
//----

template<typename T>
mat33<T>::mat33(T m00_, T m01_, T m02_,
                T m10_, T m11_, T m12_,
                T m20_, T m21_, T m22_)
{
  // init matrix with scalars
  x.x=m00_; x.y=m01_; x.z=m02_;
  y.x=m10_; y.y=m11_; y.z=m12_;
  z.x=m20_; z.y=m21_; z.z=m22_;
}
//----

template<typename T>
mat33<T>::mat33(const vec3<T> &diag_)
{
  // init matrix with row-vectors
  x.x=diag_.x; x.y=0;       x.z=0;
  y.x=0;       y.y=diag_.y; y.z=0;
  z.x=0;       z.y=0;       z.z=diag_.z;
}
//----

template<typename T>
mat33<T>::mat33(const vec3<T> &row0_,
                const vec3<T> &row1_,
                const vec3<T> &row2_)
{
  // init matrix with row-vectors
  x.x=row0_.x; x.y=row0_.y; x.z=row0_.z;
  y.x=row1_.x; y.y=row1_.y; y.z=row1_.z;
  z.x=row2_.x; z.y=row2_.y; z.z=row2_.z;
}
//----

template<typename T>
mat33<T>::mat33(const mat22<T> &m_)
{
  // init matrix with 2d matrix (upper-left matrix)
  x.x=m_.x.x; x.y=m_.x.y; x.z=0;
  y.x=m_.y.x; y.y=m_.y.y; y.z=0;
  z.x=0;      z.y=0;      z.z=T(1);
}
//----

template<typename T>
mat33<T>::mat33(const mat44<T> &m_)
{
  // init matrix with 4d matrix (upper-left matrix)
  x.x=m_.x.x; x.y=m_.x.y; x.z=m_.x.z;
  y.x=m_.y.x; y.y=m_.y.y; y.z=m_.y.z;
  z.x=m_.z.x; z.y=m_.z.y; z.z=m_.z.z;
}
//----

template<typename T>
mat33<T>::mat33(const T *a_)
{
  // init matrix with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x.x=a_[0]; x.y=a_[1]; x.z=a_[2];
  y.x=a_[3]; y.y=a_[4]; y.z=a_[5];
  z.x=a_[6]; z.y=a_[7]; z.z=a_[8];
}
//----------------------------------------------------------------------------

template<typename T>
const vec3<T> &mat33<T>::operator[](unsigned row_) const
{
  // return reference to nth vector (x=0, y=1, z=2)
  PFC_ASSERT_PEDANTIC(row_<3);
  return reinterpret_cast<const vec3<T>*>(this)[row_];
}
//----

template<typename T>
vec3<T> &mat33<T>::operator[](unsigned row_)
{
  // return reference to nth vector (x=0, y=1, z=2)
  PFC_ASSERT_PEDANTIC(row_<3);
  return reinterpret_cast<vec3<T>*>(this)[row_];
}
//----

template<typename T>
void mat33<T>::set(T s_)
{
  // set matrix with scalar
  x.x=s_; x.y=s_; x.z=s_;
  y.x=s_; y.y=s_; y.z=s_;
  z.x=s_; z.y=s_; z.z=s_;
}
//----

template<typename T>
void mat33<T>::set(T d0_, T d1_, T d2_)
{
  // set matrix with diagonal scalars
  x.x=d0_; x.y=0;   x.z=0;
  y.x=0;   y.y=d1_; y.z=0;
  z.x=0;   z.y=0;   z.z=d2_;
}
//----

template<typename T>
void mat33<T>::set(T m00_, T m01_, T m02_,
                   T m10_, T m11_, T m12_,
                   T m20_, T m21_, T m22_)
{
  // set matrix with scalars
  x.x=m00_; x.y=m01_; x.z=m02_;
  y.x=m10_; y.y=m11_; y.z=m12_;
  z.x=m20_; z.y=m21_; z.z=m22_;
}
//----

template<typename T>
void mat33<T>::set(const vec3<T> &row0_,
                   const vec3<T> &row1_,
                   const vec3<T> &row2_)
{
  // set matrix with row-vectors
  x.x=row0_.x; x.y=row0_.y; x.z=row0_.z;
  y.x=row1_.x; y.y=row1_.y; y.z=row1_.z;
  z.x=row2_.x; z.y=row2_.y; z.z=row2_.z;
}
//----

template<typename T>
void mat33<T>::set(const mat22<T> &m_)
{
  // set matrix with 2d matrix (upper-left matrix)
  x.x=m_.x.x; x.y=m_.x.y; x.z=0;
  y.x=m_.y.x; y.y=m_.y.y; y.z=0;
  z.x=0;      z.y=0;      z.z=T(1);
}
//----

template<typename T>
void mat33<T>::set(const mat33<T> &m_)
{
  // set matrix with matrix
  x.x=m_.x.x; x.y=m_.x.y; x.z=m_.x.z;
  y.x=m_.y.x; y.y=m_.y.y; y.z=m_.y.z;
  z.x=m_.z.x; z.y=m_.z.y; z.z=m_.z.z;
}
//----

template<typename T>
void mat33<T>::set(const mat44<T> &m_)
{
  // set matrix with 4d matrix (upper-left matrix)
  x.x=m_.x.x; x.y=m_.x.y; x.z=m_.x.z;
  y.x=m_.y.x; y.y=m_.y.y; y.z=m_.y.z;
  z.x=m_.z.x; z.y=m_.z.y; z.z=m_.z.z;
}
//----

template<typename T>
void mat33<T>::set(const T *a_)
{
  // set matrix with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x.x=a_[0]; x.y=a_[1]; x.z=a_[2];
  y.x=a_[3]; y.y=a_[4]; y.z=a_[5];
  z.x=a_[6]; z.y=a_[7]; z.z=a_[8];
}
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE bool is_zero(const mat33<T> &m_)
{
  // test for zero-matrix
  return    m_.x.x==0 && m_.x.y==0 && m_.x.z==0
         && m_.y.x==0 && m_.y.y==0 && m_.y.z==0
         && m_.z.x==0 && m_.z.y==0 && m_.z.z==0;
}
//----

template<typename T>
PFC_INLINE bool is_orthogonal(const mat33<T> &m_)
{
  return    dot(m_.x, m_.y)<0.0001f
         && dot(m_.x, m_.z)<0.0001f
         && dot(m_.y, m_.z)<0.0001f;
}
//----

template<typename T>
PFC_INLINE bool is_sat(const mat33<T> &m_)
{
  // test for saturated matrix
  return is_sat(m_.x) && is_sat(m_.y) && is_sat(m_.z);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const mat33<T> &m_)
{
  // test for signed saturated matrix
  return is_ssat(m_.x) && is_ssat(m_.y) && is_ssat(m_.z);
}
//----

template<typename T>
PFC_INLINE bool operator==(const mat33<T> &m0_, const mat33<T> &m1_)
{
  // test for equality of matrices
  return    m0_.x.x==m1_.x.x && m0_.x.y==m1_.x.y && m0_.x.z==m1_.x.z
         && m0_.y.x==m1_.y.x && m0_.y.y==m1_.y.y && m0_.y.z==m1_.y.z
         && m0_.z.x==m1_.z.x && m0_.z.y==m1_.z.y && m0_.z.z==m1_.z.z;
}
//----

template<typename T>
PFC_INLINE bool operator==(const mat33<T> &m_, typename math<T>::scalar_t s_)
{
  // test for equality of matrix and scalar
  return    m_.x.x==s_ && m_.x.y==s_ && m_.x.z==s_
         && m_.y.x==s_ && m_.y.y==s_ && m_.y.z==s_
         && m_.z.x==s_ && m_.z.y==s_ && m_.z.z==s_;
}
//----

template<typename T>
PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const mat33<T> &m_)
{
  // test for equality of matrix and scalar
  return    s_==m_.x.x && s_==m_.x.y && s_==m_.x.z
         && s_==m_.y.x && s_==m_.y.y && s_==m_.y.z
         && s_==m_.z.x && s_==m_.z.y && s_==m_.z.z;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const mat33<T> &m0_, const mat33<T> &m1_)
{
  // test for inequality of matrices
  return    m0_.x.x!=m1_.x.x || m0_.x.y!=m1_.x.y || m0_.x.z!=m1_.x.z
         || m0_.y.x!=m1_.y.x || m0_.y.y!=m1_.y.y || m0_.y.z!=m1_.y.z
         || m0_.z.x!=m1_.z.x || m0_.z.y!=m1_.z.y || m0_.z.z!=m1_.z.z;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const mat33<T> &m_, typename math<T>::scalar_t s_)
{
  // test for inequality of matrix and scalar
  return    m_.x.x!=s_ || m_.x.y!=s_ || m_.x.z!=s_
         || m_.y.x!=s_ || m_.y.y!=s_ || m_.y.z!=s_
         || m_.z.x!=s_ || m_.z.y!=s_ || m_.z.z!=s_;
}
//----

template<typename T>
PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const mat33<T> &m_)
{
  // test for inequality of matrix and scalar
  return    s_!=m_.x.x || s_!=m_.x.y || s_!=m_.x.z
         || s_!=m_.y.x || s_!=m_.y.y || s_!=m_.y.z
         || s_!=m_.z.x || s_!=m_.z.y || s_!=m_.z.z;
}
//----

template<typename T>
PFC_INLINE void operator+=(mat33<T> &mr_, const mat33<T> &m_)
{
  // add matrix to matrix
  mr_.x.x+=m_.x.x; mr_.x.y+=m_.x.y; mr_.x.z+=m_.x.z;
  mr_.y.x+=m_.y.x; mr_.y.y+=m_.y.y; mr_.y.z+=m_.y.z;
  mr_.z.x+=m_.z.x; mr_.z.y+=m_.z.y; mr_.z.z+=m_.z.z;
}
//----

template<typename T>
PFC_INLINE void operator+=(mat33<T> &mr_, typename math<T>::scalar_t s_)
{
  // add matrix to matrix
  mr_.x.x+=s_; mr_.x.y+=s_; mr_.x.z+=s_;
  mr_.y.x+=s_; mr_.y.y+=s_; mr_.y.z+=s_;
  mr_.z.x+=s_; mr_.z.y+=s_; mr_.z.z+=s_;
}
//----

template<typename T>
PFC_INLINE void operator-=(mat33<T> &mr_, const mat33<T> &m_)
{
  // subtract matrix from matrix
  mr_.x.x-=m_.x.x; mr_.x.y-=m_.x.y; mr_.x.z-=m_.x.z;
  mr_.y.x-=m_.y.x; mr_.y.y-=m_.y.y; mr_.y.z-=m_.y.z;
  mr_.z.x-=m_.z.x; mr_.z.y-=m_.z.y; mr_.z.z-=m_.z.z;
}
//----

template<typename T>
PFC_INLINE void operator-=(mat33<T> &mr_, typename math<T>::scalar_t s_)
{
  // subtract matrix from matrix
  mr_.x.x-=s_; mr_.x.y-=s_; mr_.x.z-=s_;
  mr_.y.x-=s_; mr_.y.y-=s_; mr_.y.z-=s_;
  mr_.z.x-=s_; mr_.z.y-=s_; mr_.z.z-=s_;
}
//----

template<typename T>
PFC_INLINE void operator*=(mat33<T> &mr_, const mat33<T> &m_)
{
  // multiply matrix by matrix
  vec3<T> v=mr_.x;
  mr_.x.x=v.x*m_.x.x+v.y*m_.y.x+v.z*m_.z.x; mr_.x.y=v.x*m_.x.y+v.y*m_.y.y+v.z*m_.z.y; mr_.x.z=v.x*m_.x.z+v.y*m_.y.z+v.z*m_.z.z;
  v=mr_.y;
  mr_.y.x=v.x*m_.x.x+v.y*m_.y.x+v.z*m_.z.x; mr_.y.y=v.x*m_.x.y+v.y*m_.y.y+v.z*m_.z.y; mr_.y.z=v.x*m_.x.z+v.y*m_.y.z+v.z*m_.z.z;
  v=mr_.z;
  mr_.z.x=v.x*m_.x.x+v.y*m_.y.x+v.z*m_.z.x; mr_.z.y=v.x*m_.x.y+v.y*m_.y.y+v.z*m_.z.y; mr_.z.z=v.x*m_.x.z+v.y*m_.y.z+v.z*m_.z.z;
}
//----

template<typename T>
PFC_INLINE void operator*=(mat33<T> &mr_, const quat<T> &q_)
{
  // multiply matrix by quaternion
  mr_.x*=q_;
  mr_.y*=q_;
  mr_.z*=q_;
}
//----

template<typename T>
PFC_INLINE void operator*=(mat33<T> &mr_, typename math<T>::scalar_t s_)
{
  // multiply matrix by scalar
  mr_.x.x*=s_; mr_.x.y*=s_; mr_.x.z*=s_;
  mr_.y.x*=s_; mr_.y.y*=s_; mr_.y.z*=s_;
  mr_.z.x*=s_; mr_.z.y*=s_; mr_.z.z*=s_;
}
//----

template<typename T>
PFC_INLINE void operator/=(mat33<T> &mr_, typename math<T>::scalar_t s_)
{
  // divide matrix by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  mr_.x.x*=rs; mr_.x.y*=rs; mr_.x.z*=rs;
  mr_.y.x*=rs; mr_.y.y*=rs; mr_.y.z*=rs;
  mr_.z.x*=rs; mr_.z.y*=rs; mr_.z.z*=rs;
}
//----

template<typename T>
PFC_INLINE mat33<T> operator+(const mat33<T> &m0_, const mat33<T> &m1_)
{
  // add matrix to matrix
  return mat33<T>(m0_.x.x+m1_.x.x, m0_.x.y+m1_.x.y, m0_.x.z+m1_.x.z,
                  m0_.y.x+m1_.y.x, m0_.y.y+m1_.y.y, m0_.y.z+m1_.y.z,
                  m0_.z.x+m1_.z.x, m0_.z.y+m1_.z.y, m0_.z.z+m1_.z.z);
}
//----

template<typename T>
PFC_INLINE mat33<T> operator+(const mat33<T> &m_, typename math<T>::scalar_t s_)
{
  // add matrix to matrix
  return mat33<T>(m_.x.x+s_, m_.x.y+s_, m_.x.z+s_,
                  m_.y.x+s_, m_.y.y+s_, m_.y.z+s_,
                  m_.z.x+s_, m_.z.y+s_, m_.z.z+s_);
}
//----

template<typename T>
PFC_INLINE mat33<T> operator+(typename math<T>::scalar_t s_, const mat33<T> &m_)
{
  // add matrix to matrix
  return mat33<T>(s_+m_.x.x, s_+m_.x.y, s_+m_.x.z,
                  s_+m_.y.x, s_+m_.y.y, s_+m_.y.z,
                  s_+m_.z.x, s_+m_.z.y, s_+m_.z.z);
}
//----

template<typename T>
PFC_INLINE mat33<T> operator-(const mat33<T> &m0_, const mat33<T> &m1_)
{
  // subtract matrix from matrix
  return mat33<T>(m0_.x.x-m1_.x.x, m0_.x.y-m1_.x.y, m0_.x.z-m1_.x.z,
                  m0_.y.x-m1_.y.x, m0_.y.y-m1_.y.y, m0_.y.z-m1_.y.z,
                  m0_.z.x-m1_.z.x, m0_.z.y-m1_.z.y, m0_.z.z-m1_.z.z);
}
//----

template<typename T>
PFC_INLINE mat33<T> operator-(const mat33<T> &m_, typename math<T>::scalar_t s_)
{
  // subtract matrix from matrix
  return mat33<T>(m_.x.x-s_, m_.x.y-s_, m_.x.z-s_,
                  m_.y.x-s_, m_.y.y-s_, m_.y.z-s_,
                  m_.z.x-s_, m_.z.y-s_, m_.z.z-s_);
}
//----

template<typename T>
PFC_INLINE mat33<T> operator-(typename math<T>::scalar_t s_, const mat33<T> &m_)
{
  // subtract matrix from matrix
  return mat33<T>(s_-m_.x.x, s_-m_.x.y, s_-m_.x.z,
                  s_-m_.y.x, s_-m_.y.y, s_-m_.y.z,
                  s_-m_.z.x, s_-m_.z.y, s_-m_.z.z);
}
//----

template<typename T>
PFC_INLINE mat33<T> operator-(const mat33<T> &m_)
{
  // negate matrix
  return mat33<T>(-m_.x.x, -m_.x.y, -m_.x.z,
                  -m_.y.x, -m_.y.y, -m_.y.z,
                  -m_.z.x, -m_.z.y, -m_.z.z);
}
//----

template<typename T>
PFC_INLINE mat33<T> operator*(const mat33<T> &m0_, const mat33<T> &m1_)
{
  // multiply matrix by matrix
  return mat33<T>(m0_.x.x*m1_.x.x+m0_.x.y*m1_.y.x+m0_.x.z*m1_.z.x, m0_.x.x*m1_.x.y+m0_.x.y*m1_.y.y+m0_.x.z*m1_.z.y, m0_.x.x*m1_.x.z+m0_.x.y*m1_.y.z+m0_.x.z*m1_.z.z,
                  m0_.y.x*m1_.x.x+m0_.y.y*m1_.y.x+m0_.y.z*m1_.z.x, m0_.y.x*m1_.x.y+m0_.y.y*m1_.y.y+m0_.y.z*m1_.z.y, m0_.y.x*m1_.x.z+m0_.y.y*m1_.y.z+m0_.y.z*m1_.z.z,
                  m0_.z.x*m1_.x.x+m0_.z.y*m1_.y.x+m0_.z.z*m1_.z.x, m0_.z.x*m1_.x.y+m0_.z.y*m1_.y.y+m0_.z.z*m1_.z.y, m0_.z.x*m1_.x.z+m0_.z.y*m1_.y.z+m0_.z.z*m1_.z.z);
}
//----

template<typename T>
PFC_INLINE mat33<T> operator*(const mat33<T> &m_, const quat<T> &q_)
{
  // multiply matrix by quaternion
  mat33<T> m=m_;
  m.x*=q_;
  m.y*=q_;
  m.z*=q_;
  return m;
}
//----

template<typename T>
PFC_INLINE mat33<T> operator*(const quat<T> &q_, const mat33<T> &m_)
{
  // multiply quaternion by matrix
  mat33<T> m;
  convert(m, q_);
  m*=m_;
  return m;
}
//----

template<typename T>
PFC_INLINE mat33<T> operator*(const mat33<T> &m_, typename math<T>::scalar_t s_)
{
  // multiply matrix by scalar
  return mat33<T>(m_.x.x*s_, m_.x.y*s_, m_.x.z*s_,
                  m_.y.x*s_, m_.y.y*s_, m_.y.z*s_,
                  m_.z.x*s_, m_.z.y*s_, m_.z.z*s_);
}
//----

template<typename T>
PFC_INLINE mat33<T> operator*(typename math<T>::scalar_t s_, const mat33<T> &m_)
{
  // multiply matrix by scalar
  return mat33<T>(s_*m_.x.x, s_*m_.x.y, s_*m_.x.z,
                  s_*m_.y.x, s_*m_.y.y, s_*m_.y.z,
                  s_*m_.z.x, s_*m_.z.y, s_*m_.z.z);
}
//----

template<typename T>
PFC_INLINE mat33<T> operator/(const mat33<T> &m_, typename math<T>::scalar_t s_)
{
  // divide matrix by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  return mat33<T>(m_.x.x*rs, m_.x.y*rs, m_.x.z*rs,
                  m_.y.x*rs, m_.y.y*rs, m_.y.z*rs,
                  m_.z.x*rs, m_.z.y*rs, m_.z.z*rs);
}
//----

template<typename T>
PFC_INLINE mat33<T> mul(const mat33<T> &m0_, const mat33<T> &m1_)
{
  // component-wise multiply: m0_*m1
  return mat33<T>(m0_.x.x*m1_.x.x, m0_.x.y*m1_.x.y, m0_.x.z*m1_.x.z,
                  m0_.y.x*m1_.y.x, m0_.y.y*m1_.y.y, m0_.y.z*m1_.y.z,
                  m0_.z.x*m1_.z.x, m0_.z.y*m1_.z.y, m0_.z.z*m1_.z.z);
}
//----

template<typename T>
PFC_INLINE mat33<T> madd(const mat33<T> &mm0_, const mat33<T> &mm1_, const mat33<T> &ma_)
{
  // component-wise multiply-add: mm0_*mm1_+ma_
  return mat33<T>(mm0_.x.x*mm1_.x.x+ma_.x.x, mm0_.x.y*mm1_.x.y+ma_.x.y, mm0_.x.z*mm1_.x.z+ma_.x.z,
                  mm0_.y.x*mm1_.y.x+ma_.y.x, mm0_.y.y*mm1_.y.y+ma_.y.y, mm0_.y.z*mm1_.y.z+ma_.y.z,
                  mm0_.z.x*mm1_.z.x+ma_.z.x, mm0_.z.y*mm1_.z.y+ma_.z.y, mm0_.z.z*mm1_.z.z+ma_.z.z);
}
//----

template<typename T>
PFC_INLINE mat33<T> madd(const mat33<T> &mm_, typename math<T>::scalar_t sm_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: mm_*sm_+sa_
  return mat33<T>(mm_.x.x*sm_+sa_, mm_.x.y*sm_+sa_, mm_.x.z*sm_+sa_,
                  mm_.y.x*sm_+sa_, mm_.y.y*sm_+sa_, mm_.y.z*sm_+sa_,
                  mm_.z.x*sm_+sa_, mm_.z.y*sm_+sa_, mm_.z.z*sm_+sa_);
}
//----

template<typename T>
PFC_INLINE mat33<T> madd(const mat33<T> &mm0_, const mat33<T> &mm1_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: mm0_*mm1_+sa_
  return mat33<T>(mm0_.x.x*mm1_.x.x+sa_, mm0_.x.y*mm1_.x.y+sa_, mm0_.x.z*mm1_.x.z+sa_,
                  mm0_.y.x*mm1_.y.x+sa_, mm0_.y.y*mm1_.y.y+sa_, mm0_.y.z*mm1_.y.z+sa_,
                  mm0_.z.x*mm1_.z.x+sa_, mm0_.z.y*mm1_.z.y+sa_, mm0_.z.z*mm1_.z.z+sa_);
}
//----

template<typename T>
PFC_INLINE mat33<T> madd(const mat33<T> &mm_, typename math<T>::scalar_t sm_, mat33<T> &ma_)
{
  // component-wise multiply-add: mm_*sm_+ma_
  return mat33<T>(mm_.x.x*sm_+ma_.x.x, mm_.x.y*sm_+ma_.x.y, mm_.x.z*sm_+ma_.x.z,
                  mm_.y.x*sm_+ma_.y.x, mm_.y.y*sm_+ma_.y.y, mm_.y.z*sm_+ma_.y.z,
                  mm_.z.x*sm_+ma_.z.x, mm_.z.y*sm_+ma_.z.y, mm_.z.z*sm_+ma_.z.z);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t det(const mat33<T> &m_)
{
  // determinant of the matrix
  return  m_.x.x*(m_.y.y*m_.z.z-m_.y.z*m_.z.y)
         +m_.y.x*(m_.z.y*m_.x.z-m_.z.z*m_.x.y)
         +m_.z.x*(m_.x.y*m_.y.z-m_.x.z*m_.y.y);
}
//----

template<typename T>
PFC_INLINE mat33<T> inv(const mat33<T> &m_, typename math<T>::scalar_t *det_)
{
  // calculate determinant
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t dx=m_.y.y*m_.z.z-m_.y.z*m_.z.y;
  scalar_t dy=m_.z.y*m_.x.z-m_.z.z*m_.x.y;
  scalar_t dz=m_.x.y*m_.y.z-m_.x.z*m_.y.y;
  scalar_t d=m_.x.x*dx+m_.y.x*dy+m_.z.x*dz;
  if(det_)
    *det_=d;
  if(!d)
    return mat33<T>::s_zero;

  // calculate inverse of the matrix
  scalar_t rd=scalar_t(1)/d;
  return mat33<T>(                           rd*dx,                            rd*dy,                            rd*dz,
                  rd*(m_.y.z*m_.z.x-m_.y.x*m_.z.z), rd*(m_.z.z*m_.x.x-m_.z.x*m_.x.z), rd*(m_.x.z*m_.y.x-m_.x.x*m_.y.z),
                  rd*(m_.y.x*m_.z.y-m_.y.y*m_.z.x), rd*(m_.z.x*m_.x.y-m_.z.y*m_.x.x), rd*(m_.x.x*m_.y.y-m_.x.y*m_.y.x));
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t tr(const mat33<T> &m_)
{
  // trace of the matrix
  return m_.x.x+m_.y.y+m_.z.z;
}
//----

template<typename T>
PFC_INLINE void identity(mat33<T> &m_)
{
  // set identity
  typedef typename math<T>::scalar_t scalar_t;
  m_.x.x=scalar_t(1); m_.x.y=0;           m_.x.z=0;
  m_.y.x=0;           m_.y.y=scalar_t(1); m_.y.z=0;
  m_.z.x=0;           m_.z.y=0;           m_.z.z=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE void transpose(mat33<T> &m_)
{
  // transpose the matrix
  typename math<T>::scalar_t t=m_.x.y;
  m_.x.y=m_.y.x;
  m_.y.x=t;
  t=m_.x.z;
  m_.x.z=m_.z.x;
  m_.z.x=t;
  t=m_.y.z;
  m_.y.z=m_.z.y;
  m_.z.y=t;
}
//----

template<typename T>
PFC_INLINE void transpose(mat33<T> &res_, const mat33<T> &m_)
{
  // transpose the matrix
  res_.x.x=m_.x.x; res_.x.y=m_.y.x; res_.x.z=m_.z.x;
  res_.y.x=m_.x.y; res_.y.y=m_.y.y; res_.y.z=m_.z.y;
  res_.z.x=m_.x.z; res_.z.y=m_.y.z; res_.z.z=m_.z.z;
}
//----

template<typename T>
PFC_INLINE void neg(mat33<T> &m_)
{
  // negate the matrix
  m_.x.x=-m_.x.x; m_.x.y=-m_.x.y; m_.x.z=-m_.x.z;
  m_.y.x=-m_.y.x; m_.y.y=-m_.y.y; m_.y.z=-m_.y.z;
  m_.z.x=-m_.z.x; m_.z.y=-m_.z.y; m_.z.z=-m_.z.z;
}
//----

template<typename T>
PFC_INLINE mat33<T> lerp(const mat33<T> &m0_, const mat33<T> &m1_, typename math<T>::scalar_t t_)
{
  // linear matrix interpolation. f(t=0)=v0, f(t=1)=v1
  return mat33<T>(m0_.x.x+(m1_.x.x-m0_.x.x)*t_, m0_.x.y+(m1_.x.y-m0_.x.y)*t_, m0_.x.z+(m1_.x.z-m0_.x.z)*t_,
                  m0_.y.x+(m1_.y.x-m0_.y.x)*t_, m0_.y.y+(m1_.y.y-m0_.y.y)*t_, m0_.y.z+(m1_.y.z-m0_.y.z)*t_,
                  m0_.z.x+(m1_.z.x-m0_.z.x)*t_, m0_.z.y+(m1_.z.y-m0_.z.y)*t_, m0_.z.z+(m1_.z.z-m0_.z.z)*t_);
}
//----

template<typename T>
PFC_INLINE void lerp(mat33<T> &res_, const mat33<T> &m0_, const mat33<T> &m1_, typename math<T>::scalar_t t_)
{
  // linear matrix interpolation. f(t=0)=v0, f(t=1)=v1
  res_.x.x=m0_.x.x+(m1_.x.x-m0_.x.x)*t_; res_.x.y=m0_.x.y+(m1_.x.y-m0_.x.y)*t_; res_.x.z=m0_.x.z+(m1_.x.z-m0_.x.z)*t_;
  res_.y.x=m0_.y.x+(m1_.y.x-m0_.y.x)*t_; res_.y.y=m0_.y.y+(m1_.y.y-m0_.y.y)*t_; res_.y.z=m0_.y.z+(m1_.y.z-m0_.y.z)*t_;
  res_.z.x=m0_.z.x+(m1_.z.x-m0_.z.x)*t_; res_.z.y=m0_.z.y+(m1_.z.y-m0_.z.y)*t_; res_.z.z=m0_.z.z+(m1_.z.z-m0_.z.z)*t_;
}
//----

template<typename T, typename U>
PFC_INLINE mat33<T> to_mat33(const mat33<U> &m_)
{
  // convert between mat33 types
  typedef typename math<T>::scalar_t scalar_t;
  return mat33<T>(scalar_t(m_.x.x), scalar_t(m_.x.y), scalar_t(m_.x.z),
                  scalar_t(m_.y.x), scalar_t(m_.y.y), scalar_t(m_.y.z),
                  scalar_t(m_.z.x), scalar_t(m_.z.y), scalar_t(m_.z.z));
}
//----

template<typename T>
PFC_INLINE void normalize(mat33<T> &m_)
{
  // normalize matrix vectors
  m_.x=unit(m_.x);
  m_.y=unit(m_.y);
  m_.z=unit(m_.z);
}
//----

template<typename T>
PFC_INLINE void orthonormalize(mat33<T> &res_)
{
  // ortho-normalize the matrix
  res_.x=unit(res_.x);
  res_.y=unit(cross(res_.z, res_.x));
  res_.z=cross(res_.x, res_.y);
}
//----

template<typename T> 
PFC_INLINE void set_rotation_xyz(mat33<T> &res_, typename math<T>::scalar_t x_, typename math<T>::scalar_t y_, typename math<T>::scalar_t z_)
{
  // set rotation matrix with angles in order Rx*Ry*Rz
  typename math<T>::scalar_t sx, cx, sy, cy, sz, cz;
  sincos(sx, cx, x_);
  sincos(sy, cy, y_);
  sincos(sz, cz, z_);
  res_.set(         cy*cz,          cy*sz,   -sy,
           sx*sy*cz-cx*sz, sx*sy*sz+cx*cz, sx*cy,
           cx*sy*cz+sx*sz, cx*sy*sz-sx*cz, cx*cy);
}
//----

template<typename T> 
PFC_INLINE void set_rotation_zyx(mat33<T> &res_, typename math<T>::scalar_t x_, typename math<T>::scalar_t y_, typename math<T>::scalar_t z_)
{
  // set rotation matrix with angles in order Rz*Ry*Rx
  typename math<T>::scalar_t sx, cx, sy, cy, sz, cz;
  sincos(sx, cx, x_);
  sincos(sy, cy, y_);
  sincos(sz, cz, z_);
  res_.set( cz*cy, sz*cx+cz*sy*sx, sz*sx-cz*sy*cx,
           -sz*cy, cz*cx-sz*sy*sx, cz*sx+sz*sy*cx,
               sy,         -cy*sx, cy*cx);
}
//----

template<typename T> 
PFC_INLINE void set_rotation_zxz(mat33<T> &res_, typename math<T>::scalar_t x_, typename math<T>::scalar_t y_, typename math<T>::scalar_t z_)
{
  // set rotation matrix with angles in order Rz*Rx*Rz (Euler)
  typename math<T>::scalar_t sx, cx, sz, cz;
  sincos(sx, cx, x_);
  sincos(sz, cz, z_);
  typename math<T>::scalar_t sz2=sz*sz, cz2=cz*cz, czsz=cz*sz, czszcx=czsz*cx, szsx=sz*sx, sxcz=sx*cz;
  res_.set(   cz2-sz2*cx, czsz+czszcx, szsx,
            -czsz-czszcx, -sz2+cz2*cx, sxcz,
                    szsx,       -sxcz, cx);
}
//----------------------------------------------------------------------------


//============================================================================
// mat44
//============================================================================
template<typename T> const mat44<T> mat44<T>::s_zero(T(0));
template<typename T> const mat44<T> mat44<T>::s_one(T(1));
template<typename T> const mat44<T> mat44<T>::s_neg_one(T(-1));
template<typename T> const mat44<T> mat44<T>::s_identity(T(1),    0,    0,    0,
                                                            0, T(1),    0,    0,
                                                            0,    0, T(1),    0,
                                                            0,    0,    0, T(1));
//----------------------------------------------------------------------------

template<typename T>
mat44<T>::mat44()
{
}
//----

template<typename T>
mat44<T>::mat44(T s_)
{
  // init matrix with scalar
  x.x=s_; x.y=s_; x.z=s_; x.w=s_;
  y.x=s_; y.y=s_; y.z=s_; y.w=s_;
  z.x=s_; z.y=s_; z.z=s_; z.w=s_;
  w.x=s_; w.y=s_; w.z=s_; w.w=s_;
}
//----

template<typename T>
mat44<T>::mat44(T d0_, T d1_, T d2_, T d3_)
{
  // init matrix with diagonal scalars
  x.x=d0_; x.y=0;   x.z=0;   x.w=0;
  y.x=0;   y.y=d1_; y.z=0;   y.w=0;
  z.x=0;   z.y=0;   z.z=d2_; z.w=0;
  w.x=0;   w.y=0;   w.z=0;   w.w=d3_;
}
//----

template<typename T>
mat44<T>::mat44(T m00_, T m01_, T m02_, T m03_,
                T m10_, T m11_, T m12_, T m13_,
                T m20_, T m21_, T m22_, T m23_,
                T m30_, T m31_, T m32_, T m33_)
{
  // init matrix with scalars
  x.x=m00_; x.y=m01_; x.z=m02_; x.w=m03_;
  y.x=m10_; y.y=m11_; y.z=m12_; y.w=m13_;
  z.x=m20_; z.y=m21_; z.z=m22_; z.w=m23_;
  w.x=m30_; w.y=m31_; w.z=m32_; w.w=m33_;
}
//----

template<typename T>
mat44<T>::mat44(const vec4<T> &diag_)
{
  // init matrix with row-vectors
  x.x=diag_.x; x.y=0;       x.z=0;       x.w=0;
  y.x=0;       y.y=diag_.y; y.z=0;       y.w=0;
  z.x=0;       z.y=0;       z.z=diag_.z; z.w=0;
  w.x=0;       w.y=0;       w.z=0;       w.w=diag_.w;
}
//----

template<typename T>
mat44<T>::mat44(const vec4<T> &row0_,
                const vec4<T> &row1_,
                const vec4<T> &row2_,
                const vec4<T> &row3_)
{
  // init matrix with row-vectors
  x.x=row0_.x; x.y=row0_.y; x.z=row0_.z; x.w=row0_.w;
  y.x=row1_.x; y.y=row1_.y; y.z=row1_.z; y.w=row1_.w;
  z.x=row2_.x; z.y=row2_.y; z.z=row2_.z; z.w=row2_.w;
  w.x=row3_.x; w.y=row3_.y; w.z=row3_.z; w.w=row3_.w;
}
//----

template<typename T>
mat44<T>::mat44(const mat33<T> &m_)
{
  // init matrix with 3d matrix (upper-left matrix)
  x.x=m_.x.x; x.y=m_.x.y; x.z=m_.x.z; x.w=0;
  y.x=m_.y.x; y.y=m_.y.y; y.z=m_.y.z; y.w=0;
  z.x=m_.z.x; z.y=m_.z.y; z.z=m_.z.z; z.w=0;
  w.x=0;      w.y=0;      w.z=0;      w.w=T(1);
}
//----

template<typename T>
mat44<T>::mat44(const T *a_)
{
  // init matrix with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x.x=a_[ 0]; x.y=a_[ 1]; x.z=a_[ 2]; x.w=a_[ 3];
  y.x=a_[ 4]; y.y=a_[ 5]; y.z=a_[ 6]; y.w=a_[ 7];
  z.x=a_[ 8]; z.y=a_[ 9]; z.z=a_[10]; z.w=a_[11];
  w.x=a_[12]; w.y=a_[13]; w.z=a_[14]; w.w=a_[15];
}
//----------------------------------------------------------------------------

template<typename T>
const vec4<T> &mat44<T>::operator[](unsigned row_) const
{
  // return reference to nth vector (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(row_<4);
  return reinterpret_cast<const vec4<T>*>(this)[row_];
}
//----

template<typename T>
vec4<T> &mat44<T>::operator[](unsigned row_)
{
  // return reference to nth vector (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(row_<4);
  return reinterpret_cast<vec4<T>*>(this)[row_];
}
//----

template<typename T>
void mat44<T>::set(T s_)
{
  // set matrix with scalar
  x.x=s_; x.y=s_; x.z=s_; x.w=s_;
  y.x=s_; y.y=s_; y.z=s_; y.w=s_;
  z.x=s_; z.y=s_; z.z=s_; z.w=s_;
  w.x=s_; w.y=s_; w.z=s_; w.w=s_;
}
//----

template<typename T>
void mat44<T>::set(T d0_, T d1_, T d2_, T d3_)
{
  // set matrix with diagonal scalars
  x.x=d0_; x.y=0;   x.z=0;   x.w=0;
  y.x=0;   y.y=d1_; y.z=0;   y.w=0;
  z.x=0;   z.y=0;   z.z=d2_; z.w=0;
  w.x=0;   w.y=0;   w.z=0;   w.w=d3_;
}
//----

template<typename T>
void mat44<T>::set(T m00_, T m01_, T m02_, T m03_,
                   T m10_, T m11_, T m12_, T m13_,
                   T m20_, T m21_, T m22_, T m23_,
                   T m30_, T m31_, T m32_, T m33_)
{
  // set matrix with scalars
  x.x=m00_; x.y=m01_; x.z=m02_; x.w=m03_;
  y.x=m10_; y.y=m11_; y.z=m12_; y.w=m13_;
  z.x=m20_; z.y=m21_; z.z=m22_; z.w=m23_;
  w.x=m30_; w.y=m31_; w.z=m32_; w.w=m33_;
}
//----

template<typename T>
void mat44<T>::set(const vec4<T> &row0_,
                   const vec4<T> &row1_,
                   const vec4<T> &row2_,
                   const vec4<T> &row3_)
{
  // set matrix with row-vectors
  x.x=row0_.x; x.y=row0_.y; x.z=row0_.z; x.w=row0_.w;
  y.x=row1_.x; y.y=row1_.y; y.z=row1_.z; y.w=row1_.w;
  z.x=row2_.x; z.y=row2_.y; z.z=row2_.z; z.w=row2_.w;
  w.x=row3_.x; w.y=row3_.y; w.z=row3_.z; w.w=row3_.w;
}
//----

template<typename T>
void mat44<T>::set(const mat33<T> &m_)
{
  // set matrix with one lower dimensional matrix
  x.x=m_.x.x; x.y=m_.x.y; x.z=m_.x.z; x.w=0;
  y.x=m_.y.x; y.y=m_.y.y; y.z=m_.y.z; y.w=0;
  z.x=m_.z.x; z.y=m_.z.y; z.z=m_.z.z; z.w=0;
  w.x=0;      w.y=0;      w.z=0;      w.w=T(1);
}
//----

template<typename T>
void mat44<T>::set(const mat44<T> &m_)
{
  // set matrix with one lower dimensional matrix
  x.x=m_.x.x; x.y=m_.x.y; x.z=m_.x.z; x.w=m_.x.w;
  y.x=m_.y.x; y.y=m_.y.y; y.z=m_.y.z; y.w=m_.y.w;
  z.x=m_.z.x; z.y=m_.z.y; z.z=m_.z.z; z.w=m_.z.w;
  w.x=m_.w.x; w.y=m_.w.y; w.z=m_.w.z; w.w=m_.w.w;
}
//----

template<typename T>
void mat44<T>::set(const T *a_)
{
  // set matrix with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x.x=a_[ 0]; x.y=a_[ 1]; x.z=a_[ 2]; x.w=a_[ 3];
  y.x=a_[ 4]; y.y=a_[ 5]; y.z=a_[ 6]; y.w=a_[ 7];
  z.x=a_[ 8]; z.y=a_[ 9]; z.z=a_[10]; z.w=a_[11];
  w.x=a_[12]; w.y=a_[13]; w.z=a_[14]; w.w=a_[15];
}
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE bool is_zero(const mat44<T> &m_)
{
  // test for zero-matrix
  return    m_.x.x==0 && m_.x.y==0 && m_.x.z==0 && m_.x.w==0
         && m_.y.x==0 && m_.y.y==0 && m_.y.z==0 && m_.y.w==0
         && m_.z.x==0 && m_.z.y==0 && m_.z.z==0 && m_.z.w==0
         && m_.w.x==0 && m_.w.y==0 && m_.w.z==0 && m_.w.w==0;
}
//----

template<typename T>
PFC_INLINE bool is_sat(const mat44<T> &m_)
{
  // test for saturated matrix
  return is_sat(m_.x) && is_sat(m_.y) && is_sat(m_.z) && is_sat(m_.w);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const mat44<T> &m_)
{
  // test for signed saturated matrix
  return is_ssat(m_.x) && is_ssat(m_.y) && is_ssat(m_.z) && is_ssat(m_.w);
}
//----

template<typename T>
PFC_INLINE bool operator==(const mat44<T> &m0_, const mat44<T> &m1_)
{
  // test for equality of matrices
  return    m0_.x.x==m1_.x.x && m0_.x.y==m1_.x.y && m0_.x.z==m1_.x.z && m0_.x.w==m1_.x.w
         && m0_.y.x==m1_.y.x && m0_.y.y==m1_.y.y && m0_.y.z==m1_.y.z && m0_.y.w==m1_.y.w
         && m0_.z.x==m1_.z.x && m0_.z.y==m1_.z.y && m0_.z.z==m1_.z.z && m0_.z.w==m1_.z.w
         && m0_.w.x==m1_.w.x && m0_.w.y==m1_.w.y && m0_.w.z==m1_.w.z && m0_.w.w==m1_.w.w;
}
//----

template<typename T>
PFC_INLINE bool operator==(const mat44<T> &m_, typename math<T>::scalar_t s_)
{
  // test for equality of matrix and scalar
  return    m_.x.x==s_ && m_.x.y==s_ && m_.x.z==s_ && m_.x.w==s_
         && m_.y.x==s_ && m_.y.y==s_ && m_.y.z==s_ && m_.y.w==s_
         && m_.z.x==s_ && m_.z.y==s_ && m_.z.z==s_ && m_.z.w==s_
         && m_.w.x==s_ && m_.w.y==s_ && m_.w.z==s_ && m_.w.w==s_;
}
//----

template<typename T>
PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const mat44<T> &m_)
{
  // test for equality of matrix and scalar
  return    s_==m_.x.x && s_==m_.x.y && s_==m_.x.z && s_==m_.x.w
         && s_==m_.y.x && s_==m_.y.y && s_==m_.y.z && s_==m_.y.w
         && s_==m_.z.x && s_==m_.z.y && s_==m_.z.z && s_==m_.z.w
         && s_==m_.w.x && s_==m_.w.y && s_==m_.w.z && s_==m_.w.w;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const mat44<T> &m0_, const mat44<T> &m1_)
{
  // test for inequality of matrices
  return    m0_.x.x!=m1_.x.x || m0_.x.y!=m1_.x.y || m0_.x.z!=m1_.x.z || m0_.x.w!=m1_.x.w
         || m0_.y.x!=m1_.y.x || m0_.y.y!=m1_.y.y || m0_.y.z!=m1_.y.z || m0_.y.w!=m1_.y.w
         || m0_.z.x!=m1_.z.x || m0_.z.y!=m1_.z.y || m0_.z.z!=m1_.z.z || m0_.z.w!=m1_.z.w
         || m0_.w.x!=m1_.w.x || m0_.w.y!=m1_.w.y || m0_.w.z!=m1_.w.z || m0_.w.w!=m1_.w.w;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const mat44<T> &m_, typename math<T>::scalar_t s_)
{
  // test for inequality of matrix and scalar
  return    m_.x.x!=s_ || m_.x.y!=s_ || m_.x.z!=s_ || m_.x.w!=s_
         || m_.y.x!=s_ || m_.y.y!=s_ || m_.y.z!=s_ || m_.y.w!=s_
         || m_.z.x!=s_ || m_.z.y!=s_ || m_.z.z!=s_ || m_.z.w!=s_
         || m_.w.x!=s_ || m_.w.y!=s_ || m_.w.z!=s_ || m_.w.w!=s_;
}
//----

template<typename T>
PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const mat44<T> &m_)
{
  // test for inequality of matrix and scalar
  return    s_!=m_.x.x || s_!=m_.x.y || s_!=m_.x.z || s_!=m_.x.w
         || s_!=m_.y.x || s_!=m_.y.y || s_!=m_.y.z || s_!=m_.y.w
         || s_!=m_.z.x || s_!=m_.z.y || s_!=m_.z.z || s_!=m_.z.w
         || s_!=m_.w.x || s_!=m_.w.y || s_!=m_.w.z || s_!=m_.w.w;
}
//----

template<typename T>
PFC_INLINE void operator+=(mat44<T> &mr_, const mat44<T> &m_)
{
  // add matrix to matrix
  mr_.x.x+=m_.x.x; mr_.x.y+=m_.x.y; mr_.x.z+=m_.x.z; mr_.x.w+=m_.x.w;
  mr_.y.x+=m_.y.x; mr_.y.y+=m_.y.y; mr_.y.z+=m_.y.z; mr_.y.w+=m_.y.w;
  mr_.z.x+=m_.z.x; mr_.z.y+=m_.z.y; mr_.z.z+=m_.z.z; mr_.z.w+=m_.z.w;
  mr_.w.x+=m_.w.x; mr_.w.y+=m_.w.y; mr_.w.z+=m_.w.z; mr_.w.w+=m_.w.w;
}
//----

template<typename T>
PFC_INLINE void operator+=(mat44<T> &mr_, typename math<T>::scalar_t s_)
{
  // add matrix to matrix
  mr_.x.x+=s_; mr_.x.y+=s_; mr_.x.z+=s_; mr_.x.w+=s_;
  mr_.y.x+=s_; mr_.y.y+=s_; mr_.y.z+=s_; mr_.y.w+=s_;
  mr_.z.x+=s_; mr_.z.y+=s_; mr_.z.z+=s_; mr_.z.w+=s_;
  mr_.w.x+=s_; mr_.w.y+=s_; mr_.w.z+=s_; mr_.w.w+=s_;
}
//----

template<typename T>
PFC_INLINE void operator-=(mat44<T> &mr_, const mat44<T> &m_)
{
  // subtract matrix from matrix
  mr_.x.x-=m_.x.x; mr_.x.y-=m_.x.y; mr_.x.z-=m_.x.z; mr_.x.w-=m_.x.w;
  mr_.y.x-=m_.y.x; mr_.y.y-=m_.y.y; mr_.y.z-=m_.y.z; mr_.y.w-=m_.y.w;
  mr_.z.x-=m_.z.x; mr_.z.y-=m_.z.y; mr_.z.z-=m_.z.z; mr_.z.w-=m_.z.w;
  mr_.w.x-=m_.w.x; mr_.w.y-=m_.w.y; mr_.w.z-=m_.w.z; mr_.w.w-=m_.w.w;
}
//----

template<typename T>
PFC_INLINE void operator-=(mat44<T> &mr_, typename math<T>::scalar_t s_)
{
  // subtract matrix from matrix
  mr_.x.x-=s_; mr_.x.y-=s_; mr_.x.z-=s_; mr_.x.w-=s_;
  mr_.y.x-=s_; mr_.y.y-=s_; mr_.y.z-=s_; mr_.y.w-=s_;
  mr_.z.x-=s_; mr_.z.y-=s_; mr_.z.z-=s_; mr_.z.w-=s_;
  mr_.w.x-=s_; mr_.w.y-=s_; mr_.w.z-=s_; mr_.w.w-=s_;
}
//----

template<typename T>
PFC_INLINE void operator*=(mat44<T> &mr_, const mat44<T> &m_)
{
  // multiply matrix by matrix
  vec4<T> v=mr_.x;
  mr_.x.x=v.x*m_.x.x+v.y*m_.y.x+v.z*m_.z.x+v.w*m_.w.x; mr_.x.y=v.x*m_.x.y+v.y*m_.y.y+v.z*m_.z.y+v.w*m_.w.y; mr_.x.z=v.x*m_.x.z+v.y*m_.y.z+v.z*m_.z.z+v.w*m_.w.z; mr_.x.w=v.x*m_.x.w+v.y*m_.y.w+v.z*m_.z.w+v.w*m_.w.w;
  v=mr_.y;
  mr_.y.x=v.x*m_.x.x+v.y*m_.y.x+v.z*m_.z.x+v.w*m_.w.x; mr_.y.y=v.x*m_.x.y+v.y*m_.y.y+v.z*m_.z.y+v.w*m_.w.y; mr_.y.z=v.x*m_.x.z+v.y*m_.y.z+v.z*m_.z.z+v.w*m_.w.z; mr_.y.w=v.x*m_.x.w+v.y*m_.y.w+v.z*m_.z.w+v.w*m_.w.w;
  v=mr_.z;
  mr_.z.x=v.x*m_.x.x+v.y*m_.y.x+v.z*m_.z.x+v.w*m_.w.x; mr_.z.y=v.x*m_.x.y+v.y*m_.y.y+v.z*m_.z.y+v.w*m_.w.y; mr_.z.z=v.x*m_.x.z+v.y*m_.y.z+v.z*m_.z.z+v.w*m_.w.z; mr_.z.w=v.x*m_.x.w+v.y*m_.y.w+v.z*m_.z.w+v.w*m_.w.w;
  v=mr_.w;
  mr_.w.x=v.x*m_.x.x+v.y*m_.y.x+v.z*m_.z.x+v.w*m_.w.x; mr_.w.y=v.x*m_.x.y+v.y*m_.y.y+v.z*m_.z.y+v.w*m_.w.y; mr_.w.z=v.x*m_.x.z+v.y*m_.y.z+v.z*m_.z.z+v.w*m_.w.z; mr_.w.w=v.x*m_.x.w+v.y*m_.y.w+v.z*m_.z.w+v.w*m_.w.w;
}
//----

template<typename T>
PFC_INLINE void operator*=(mat44<T> &mr_, typename math<T>::scalar_t s_)
{
  // multiply matrix by scalar
  mr_.x.x*=s_; mr_.x.y*=s_; mr_.x.z*=s_; mr_.x.w*=s_;
  mr_.y.x*=s_; mr_.y.y*=s_; mr_.y.z*=s_; mr_.y.w*=s_;
  mr_.z.x*=s_; mr_.z.y*=s_; mr_.z.z*=s_; mr_.z.w*=s_;
  mr_.w.x*=s_; mr_.w.y*=s_; mr_.w.z*=s_; mr_.w.w*=s_;
}
//----

template<typename T>
PFC_INLINE void operator/=(mat44<T> &mr_, typename math<T>::scalar_t s_)
{
  // divide matrix by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  mr_.x.x*=rs; mr_.x.y*=rs; mr_.x.z*=rs; mr_.x.w*=rs;
  mr_.y.x*=rs; mr_.y.y*=rs; mr_.y.z*=rs; mr_.y.w*=rs;
  mr_.z.x*=rs; mr_.z.y*=rs; mr_.z.z*=rs; mr_.z.w*=rs;
  mr_.w.x*=rs; mr_.w.y*=rs; mr_.w.z*=rs; mr_.w.w*=rs;
}
//----

template<typename T>
PFC_INLINE mat44<T> operator+(const mat44<T> &m0_, const mat44<T> &m1_)
{
  // add matrix to matrix
  return mat44<T>(m0_.x.x+m1_.x.x, m0_.x.y+m1_.x.y, m0_.x.z+m1_.x.z, m0_.x.w+m1_.x.w,
                  m0_.y.x+m1_.y.x, m0_.y.y+m1_.y.y, m0_.y.z+m1_.y.z, m0_.y.w+m1_.y.w,
                  m0_.z.x+m1_.z.x, m0_.z.y+m1_.z.y, m0_.z.z+m1_.z.z, m0_.z.w+m1_.z.w,
                  m0_.w.x+m1_.w.x, m0_.w.y+m1_.w.y, m0_.w.z+m1_.w.z, m0_.w.w+m1_.w.w);
}
//----

template<typename T>
PFC_INLINE mat44<T> operator+(const mat44<T> &m_, typename math<T>::scalar_t s_)
{
  // add matrix to matrix
  return mat44<T>(m_.x.x+s_, m_.x.y+s_, m_.x.z+s_, m_.x.w+s_,
                  m_.y.x+s_, m_.y.y+s_, m_.y.z+s_, m_.y.w+s_,
                  m_.z.x+s_, m_.z.y+s_, m_.z.z+s_, m_.z.w+s_,
                  m_.w.x+s_, m_.w.y+s_, m_.w.z+s_, m_.w.w+s_);
}
//----

template<typename T>
PFC_INLINE mat44<T> operator+(typename math<T>::scalar_t s_, const mat44<T> &m_)
{
  // add matrix to matrix
  return mat44<T>(s_+m_.x.x, s_+m_.x.y, s_+m_.x.z, s_+m_.x.w,
                  s_+m_.y.x, s_+m_.y.y, s_+m_.y.z, s_+m_.y.w,
                  s_+m_.z.x, s_+m_.z.y, s_+m_.z.z, s_+m_.z.w,
                  s_+m_.w.x, s_+m_.w.y, s_+m_.w.z, s_+m_.w.w);
}
//----

template<typename T>
PFC_INLINE mat44<T> operator-(const mat44<T> &m0_, const mat44<T> &m1_)
{
  // subtract matrix from matrix
  return mat44<T>(m0_.x.x-m1_.x.x, m0_.x.y-m1_.x.y, m0_.x.z-m1_.x.z, m0_.x.w-m1_.x.w,
                  m0_.y.x-m1_.y.x, m0_.y.y-m1_.y.y, m0_.y.z-m1_.y.z, m0_.y.w-m1_.y.w,
                  m0_.z.x-m1_.z.x, m0_.z.y-m1_.z.y, m0_.z.z-m1_.z.z, m0_.z.w-m1_.z.w,
                  m0_.w.x-m1_.w.x, m0_.w.y-m1_.w.y, m0_.w.z-m1_.w.z, m0_.w.w-m1_.w.w);
}
//----

template<typename T>
PFC_INLINE mat44<T> operator-(const mat44<T> &m_, typename math<T>::scalar_t s_)
{
  // subtract matrix from matrix
  return mat44<T>(m_.x.x-s_, m_.x.y-s_, m_.x.z-s_, m_.x.w-s_,
                  m_.y.x-s_, m_.y.y-s_, m_.y.z-s_, m_.y.w-s_,
                  m_.z.x-s_, m_.z.y-s_, m_.z.z-s_, m_.z.w-s_,
                  m_.w.x-s_, m_.w.y-s_, m_.w.z-s_, m_.w.w-s_);
}
//----

template<typename T>
PFC_INLINE mat44<T> operator-(typename math<T>::scalar_t s_, const mat44<T> &m_)
{
  // subtract matrix from matrix
  return mat44<T>(s_-m_.x.x, s_-m_.x.y, s_-m_.x.z, s_-m_.x.w,
                  s_-m_.y.x, s_-m_.y.y, s_-m_.y.z, s_-m_.y.w,
                  s_-m_.z.x, s_-m_.z.y, s_-m_.z.z, s_-m_.z.w,
                  s_-m_.w.x, s_-m_.w.y, s_-m_.w.z, s_-m_.w.w);
}
//----

template<typename T>
PFC_INLINE mat44<T> operator-(const mat44<T> &m_)
{
  // negate matrix
  return mat44<T>(-m_.x.x, -m_.x.y, -m_.x.z, -m_.x.w,
                  -m_.y.x, -m_.y.y, -m_.y.z, -m_.y.w,
                  -m_.z.x, -m_.z.y, -m_.z.z, -m_.z.w,
                  -m_.w.x, -m_.w.y, -m_.w.z, -m_.w.w);
}
//----

template<typename T>
PFC_INLINE mat44<T> operator*(const mat44<T> &m0_, const mat44<T> &m1_)
{
  // multiply matrix by matrix
  return mat44<T>(m0_.x.x*m1_.x.x+m0_.x.y*m1_.y.x+m0_.x.z*m1_.z.x+m0_.x.w*m1_.w.x, m0_.x.x*m1_.x.y+m0_.x.y*m1_.y.y+m0_.x.z*m1_.z.y+m0_.x.w*m1_.w.y, m0_.x.x*m1_.x.z+m0_.x.y*m1_.y.z+m0_.x.z*m1_.z.z+m0_.x.w*m1_.w.z, m0_.x.x*m1_.x.w+m0_.x.y*m1_.y.w+m0_.x.z*m1_.z.w+m0_.x.w*m1_.w.w,
                  m0_.y.x*m1_.x.x+m0_.y.y*m1_.y.x+m0_.y.z*m1_.z.x+m0_.y.w*m1_.w.x, m0_.y.x*m1_.x.y+m0_.y.y*m1_.y.y+m0_.y.z*m1_.z.y+m0_.y.w*m1_.w.y, m0_.y.x*m1_.x.z+m0_.y.y*m1_.y.z+m0_.y.z*m1_.z.z+m0_.y.w*m1_.w.z, m0_.y.x*m1_.x.w+m0_.y.y*m1_.y.w+m0_.y.z*m1_.z.w+m0_.y.w*m1_.w.w,
                  m0_.z.x*m1_.x.x+m0_.z.y*m1_.y.x+m0_.z.z*m1_.z.x+m0_.z.w*m1_.w.x, m0_.z.x*m1_.x.y+m0_.z.y*m1_.y.y+m0_.z.z*m1_.z.y+m0_.z.w*m1_.w.y, m0_.z.x*m1_.x.z+m0_.z.y*m1_.y.z+m0_.z.z*m1_.z.z+m0_.z.w*m1_.w.z, m0_.z.x*m1_.x.w+m0_.z.y*m1_.y.w+m0_.z.z*m1_.z.w+m0_.z.w*m1_.w.w,
                  m0_.w.x*m1_.x.x+m0_.w.y*m1_.y.x+m0_.w.z*m1_.z.x+m0_.w.w*m1_.w.x, m0_.w.x*m1_.x.y+m0_.w.y*m1_.y.y+m0_.w.z*m1_.z.y+m0_.w.w*m1_.w.y, m0_.w.x*m1_.x.z+m0_.w.y*m1_.y.z+m0_.w.z*m1_.z.z+m0_.w.w*m1_.w.z, m0_.w.x*m1_.x.w+m0_.w.y*m1_.y.w+m0_.w.z*m1_.z.w+m0_.w.w*m1_.w.w);
}
//----

template<typename T>
PFC_INLINE mat44<T> operator*(const mat44<T> &m_, typename math<T>::scalar_t s_)
{
  // multiply matrix by scalar
  return mat44<T>(m_.x.x*s_, m_.x.y*s_, m_.x.z*s_, m_.x.w*s_,
                  m_.y.x*s_, m_.y.y*s_, m_.y.z*s_, m_.y.w*s_,
                  m_.z.x*s_, m_.z.y*s_, m_.z.z*s_, m_.z.w*s_,
                  m_.w.x*s_, m_.w.y*s_, m_.w.z*s_, m_.w.w*s_);
}
//----

template<typename T>
PFC_INLINE mat44<T> operator*(typename math<T>::scalar_t s_, const mat44<T> &m_)
{
  // multiply matrix by scalar
  return mat44<T>(s_*m_.x.x, s_*m_.x.y, s_*m_.x.z, s_*m_.x.w,
                  s_*m_.y.x, s_*m_.y.y, s_*m_.y.z, s_*m_.y.w,
                  s_*m_.z.x, s_*m_.z.y, s_*m_.z.z, s_*m_.z.w,
                  s_*m_.w.x, s_*m_.w.y, s_*m_.w.z, s_*m_.w.w);
}
//----

template<typename T>
PFC_INLINE mat44<T> operator/(const mat44<T> &m_, typename math<T>::scalar_t s_)
{
  // divide matrix by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  return mat44<T>(m_.x.x*rs, m_.x.y*rs, m_.x.z*rs, m_.x.w*rs,
                  m_.y.x*rs, m_.y.y*rs, m_.y.z*rs, m_.y.w*rs,
                  m_.z.x*rs, m_.z.y*rs, m_.z.z*rs, m_.z.w*rs,
                  m_.w.x*rs, m_.w.y*rs, m_.w.z*rs, m_.w.w*rs);
}
//----

template<typename T>
PFC_INLINE mat44<T> mul(const mat44<T> &m0_, const mat44<T> &m1_)
{
  // component-wise multiply: m0_*m1
  return mat44<T>(m0_.x.x*m1_.x.x, m0_.x.y*m1_.x.y, m0_.x.z*m1_.x.z, m0_.x.w*m1_.x.w,
                  m0_.y.x*m1_.y.x, m0_.y.y*m1_.y.y, m0_.y.z*m1_.y.z, m0_.y.w*m1_.y.w,
                  m0_.z.x*m1_.z.x, m0_.z.y*m1_.z.y, m0_.z.z*m1_.z.z, m0_.z.w*m1_.z.w,
                  m0_.w.x*m1_.w.x, m0_.w.y*m1_.w.y, m0_.w.z*m1_.w.z, m0_.w.w*m1_.w.w);
}
//----

template<typename T>
PFC_INLINE mat44<T> madd(const mat44<T> &mm0_, const mat44<T> &mm1_, const mat44<T> &ma_)
{
  // component-wise multiply-add: mm0_*mm1_+ma_
  return mat44<T>(mm0_.x.x*mm1_.x.x+ma_.x.x, mm0_.x.y*mm1_.x.y+ma_.x.y, mm0_.x.z*mm1_.x.z+ma_.x.z, mm0_.x.w*mm1_.x.w+ma_.x.w,
                  mm0_.y.x*mm1_.y.x+ma_.y.x, mm0_.y.y*mm1_.y.y+ma_.y.y, mm0_.y.z*mm1_.y.z+ma_.y.z, mm0_.y.w*mm1_.y.w+ma_.y.w,
                  mm0_.z.x*mm1_.z.x+ma_.z.x, mm0_.z.y*mm1_.z.y+ma_.z.y, mm0_.z.z*mm1_.z.z+ma_.z.z, mm0_.z.w*mm1_.z.w+ma_.z.w,
                  mm0_.w.x*mm1_.w.x+ma_.w.x, mm0_.w.y*mm1_.w.y+ma_.w.y, mm0_.w.z*mm1_.w.z+ma_.w.z, mm0_.w.w*mm1_.w.w+ma_.w.w);
}
//----

template<typename T>
PFC_INLINE mat44<T> madd(const mat44<T> &mm_, typename math<T>::scalar_t sm_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: mm_*sm_+sa_
  return mat44<T>(mm_.x.x*sm_+sa_, mm_.x.y*sm_+sa_, mm_.x.z*sm_+sa_, mm_.x.w*sm_+sa_,
                  mm_.y.x*sm_+sa_, mm_.y.y*sm_+sa_, mm_.y.z*sm_+sa_, mm_.y.w*sm_+sa_,
                  mm_.z.x*sm_+sa_, mm_.z.y*sm_+sa_, mm_.z.z*sm_+sa_, mm_.z.w*sm_+sa_,
                  mm_.w.x*sm_+sa_, mm_.w.y*sm_+sa_, mm_.w.z*sm_+sa_, mm_.w.w*sm_+sa_);
}
//----

template<typename T>
PFC_INLINE mat44<T> madd(const mat44<T> &mm0_, const mat44<T> &mm1_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: mm0_*mm1_+sa_
  return mat44<T>(mm0_.x.x*mm1_.x.x+sa_, mm0_.x.y*mm1_.x.y+sa_, mm0_.x.z*mm1_.x.z+sa_, mm0_.x.w*mm1_.x.w+sa_,
                  mm0_.y.x*mm1_.y.x+sa_, mm0_.y.y*mm1_.y.y+sa_, mm0_.y.z*mm1_.y.z+sa_, mm0_.y.w*mm1_.y.w+sa_,
                  mm0_.z.x*mm1_.z.x+sa_, mm0_.z.y*mm1_.z.y+sa_, mm0_.z.z*mm1_.z.z+sa_, mm0_.z.w*mm1_.z.w+sa_,
                  mm0_.w.x*mm1_.w.x+sa_, mm0_.w.y*mm1_.w.y+sa_, mm0_.w.z*mm1_.w.z+sa_, mm0_.w.w*mm1_.w.w+sa_);
}
//----

template<typename T>
PFC_INLINE mat44<T> madd(const mat44<T> &mm_, typename math<T>::scalar_t sm_, const mat44<T> &ma_)
{
  // component-wise multiply-add: mm_*sm_+ma_
  return mat44<T>(mm_.x.x*sm_+ma_.x.x, mm_.x.y*sm_+ma_.x.y, mm_.x.z*sm_+ma_.x.z, mm_.x.w*sm_+ma_.x.w,
                  mm_.y.x*sm_+ma_.y.x, mm_.y.y*sm_+ma_.y.y, mm_.y.z*sm_+ma_.y.z, mm_.y.w*sm_+ma_.y.w,
                  mm_.z.x*sm_+ma_.z.x, mm_.z.y*sm_+ma_.z.y, mm_.z.z*sm_+ma_.z.z, mm_.z.w*sm_+ma_.z.w,
                  mm_.w.x*sm_+ma_.w.x, mm_.w.y*sm_+ma_.w.y, mm_.w.z*sm_+ma_.w.z, mm_.w.w*sm_+ma_.w.w);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t det(const mat44<T> &m_)
{
  // determinant of the matrix
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t dzw=m_.z.z*m_.w.w-m_.z.w*m_.w.z;
  scalar_t dwx=m_.w.z*m_.x.w-m_.w.w*m_.x.z;
  scalar_t dxy=m_.x.z*m_.y.w-m_.x.w*m_.y.z;
  scalar_t dyz=m_.y.z*m_.z.w-m_.y.w*m_.z.z;
  return  m_.x.x*(m_.y.y*dzw+m_.z.y*(m_.w.z*m_.y.w-m_.w.w*m_.y.z)+m_.w.y*dyz)
         -m_.y.x*(m_.z.y*dwx+m_.w.y*(m_.x.z*m_.z.w-m_.x.w*m_.z.z)+m_.x.y*dzw)
         +m_.z.x*(m_.w.y*dxy+m_.x.y*(m_.y.z*m_.w.w-m_.y.w*m_.w.z)+m_.y.y*dwx)
         -m_.w.x*(m_.x.y*dyz+m_.y.y*(m_.z.z*m_.x.w-m_.z.w*m_.x.z)+m_.z.y*dxy);
}
//----

template<typename T>
PFC_INLINE mat44<T> inv(const mat44<T> &m_, typename math<T>::scalar_t *det_)
{
  // calculate determinant of the matrix
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t dzw=m_.z.z*m_.w.w-m_.z.w*m_.w.z;
  scalar_t dwx=m_.w.z*m_.x.w-m_.w.w*m_.x.z;
  scalar_t dxy=m_.x.z*m_.y.w-m_.x.w*m_.y.z;
  scalar_t dyz=m_.y.z*m_.z.w-m_.y.w*m_.z.z;
  scalar_t dx= m_.y.y*dzw+m_.z.y*(m_.w.z*m_.y.w-m_.w.w*m_.y.z)+m_.w.y*dyz;
  scalar_t dy=-m_.z.y*dwx-m_.w.y*(m_.x.z*m_.z.w-m_.x.w*m_.z.z)-m_.x.y*dzw;
  scalar_t dz= m_.w.y*dxy+m_.x.y*(m_.y.z*m_.w.w-m_.y.w*m_.w.z)+m_.y.y*dwx;
  scalar_t dw=-m_.x.y*dyz-m_.y.y*(m_.z.z*m_.x.w-m_.z.w*m_.x.z)-m_.z.y*dxy;
  scalar_t d=m_.x.x*dx+m_.y.x*dy+m_.z.x*dz+m_.w.x*dw;
  if(det_)
    *det_=d;
  if(!d)
    return mat44<T>::s_zero;

  // calculate inverse of the matrix x-row
  mat44<T> res;
  scalar_t rd=scalar_t(1)/d;
  res.x.x=rd*dx;
  res.x.y=rd*dy;
  res.x.z=rd*dz;
  res.x.w=rd*dw;

  // calculate inverse of the matrix y-row
  dzw=m_.z.w*m_.w.x-m_.z.x*m_.w.w;
  dwx=m_.w.w*m_.x.x-m_.w.x*m_.x.w;
  dxy=m_.x.w*m_.y.x-m_.x.x*m_.y.w;
  dyz=m_.y.w*m_.z.x-m_.y.x*m_.z.w;
  res.y.x=rd*(-m_.y.z*dzw-m_.z.z*(m_.w.w*m_.y.x-m_.w.x*m_.y.w)-m_.w.z*dyz);
  res.y.y=rd*( m_.z.z*dwx+m_.w.z*(m_.x.w*m_.z.x-m_.x.x*m_.z.w)+m_.x.z*dzw);
  res.y.z=rd*(-m_.w.z*dxy-m_.x.z*(m_.y.w*m_.w.x-m_.y.x*m_.w.w)-m_.y.z*dwx);
  res.y.w=rd*( m_.x.z*dyz+m_.y.z*(m_.z.w*m_.x.x-m_.z.x*m_.x.w)+m_.z.z*dxy);

  // calculate inverse of the matrix z-row
  dzw=m_.z.x*m_.w.y-m_.z.y*m_.w.x;
  dwx=m_.w.x*m_.x.y-m_.w.y*m_.x.x;
  dxy=m_.x.x*m_.y.y-m_.x.y*m_.y.x;
  dyz=m_.y.x*m_.z.y-m_.y.y*m_.z.x;
  res.z.x=rd*( m_.y.w*dzw+m_.z.w*(m_.w.x*m_.y.y-m_.w.y*m_.y.x)+m_.w.w*dyz);
  res.z.y=rd*(-m_.z.w*dwx-m_.w.w*(m_.x.x*m_.z.y-m_.x.y*m_.z.x)-m_.x.w*dzw);
  res.z.z=rd*( m_.w.w*dxy+m_.x.w*(m_.y.x*m_.w.y-m_.y.y*m_.w.x)+m_.y.w*dwx);
  res.z.w=rd*(-m_.x.w*dyz-m_.y.w*(m_.z.x*m_.x.y-m_.z.y*m_.x.x)-m_.z.w*dxy);

  // calculate inverse of the matrix w-row
  dzw=m_.z.y*m_.w.z-m_.z.z*m_.w.y;
  dwx=m_.w.y*m_.x.z-m_.w.z*m_.x.y;
  dxy=m_.x.y*m_.y.z-m_.x.z*m_.y.y;
  dyz=m_.y.y*m_.z.z-m_.y.z*m_.z.y;
  res.w.x=rd*(-m_.y.x*dzw-m_.z.x*(m_.w.y*m_.y.z-m_.w.z*m_.y.y)-m_.w.x*dyz);
  res.w.y=rd*( m_.z.x*dwx+m_.w.x*(m_.x.y*m_.z.z-m_.x.z*m_.z.y)+m_.x.x*dzw);
  res.w.z=rd*(-m_.w.x*dxy-m_.x.x*(m_.y.y*m_.w.z-m_.y.z*m_.w.y)-m_.y.x*dwx);
  res.w.w=rd*( m_.x.x*dyz+m_.y.x*(m_.z.y*m_.x.z-m_.z.z*m_.x.y)+m_.z.x*dxy);
  return res;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t tr(const mat44<T> &m_)
{
  // trace of the matrix
  return m_.x.x+m_.y.y+m_.z.z+m_.w.w;
}
//----

template<typename T>
PFC_INLINE void identity(mat44<T> &m_)
{
  // set identity
  typedef typename math<T>::scalar_t scalar_t;
  m_.x.x=scalar_t(1); m_.x.y=0;           m_.x.z=0;           m_.x.w=0;
  m_.y.x=0;           m_.y.y=scalar_t(1); m_.y.z=0;           m_.y.w=0;
  m_.z.x=0;           m_.z.y=0;           m_.z.z=scalar_t(1); m_.z.w=0;
  m_.w.x=0;           m_.w.y=0;           m_.w.z=0;           m_.w.w=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE void transpose(mat44<T> &m_)
{
  // transpose the matrix
  typename math<T>::scalar_t t=m_.x.y;
  m_.x.y=m_.y.x;
  m_.y.x=t;
  t=m_.x.z;
  m_.x.z=m_.z.x;
  m_.z.x=t;
  t=m_.x.w;
  m_.x.w=m_.w.x;
  m_.w.x=t;
  t=m_.y.z;
  m_.y.z=m_.z.y;
  m_.z.y=t;
  t=m_.y.w;
  m_.y.w=m_.w.y;
  m_.w.y=t;
  t=m_.z.w;
  m_.z.w=m_.w.z;
  m_.w.z=t;
}
//----

template<typename T>
PFC_INLINE void transpose(mat44<T> &res_, const mat44<T> &m_)
{
  // transpose the matrix
  res_.x.x=m_.x.x; res_.x.y=m_.y.x; res_.x.z=m_.z.x; res_.x.w=m_.w.x;
  res_.y.x=m_.x.y; res_.y.y=m_.y.y; res_.y.z=m_.z.y; res_.y.w=m_.w.y;
  res_.z.x=m_.x.z; res_.z.y=m_.y.z; res_.z.z=m_.z.z; res_.z.w=m_.w.z;
  res_.w.x=m_.x.w; res_.w.y=m_.y.w; res_.w.z=m_.z.w; res_.w.w=m_.w.w;
}
//----

template<typename T>
PFC_INLINE void neg(mat44<T> &m_)
{
  // negate the matrix
  m_.x.x=-m_.x.x; m_.x.y=-m_.x.y; m_.x.z=-m_.x.z; m_.x.w=-m_.x.w;
  m_.y.x=-m_.y.x; m_.y.y=-m_.y.y; m_.y.z=-m_.y.z; m_.y.w=-m_.y.w;
  m_.z.x=-m_.z.x; m_.z.y=-m_.z.y; m_.z.z=-m_.z.z; m_.z.w=-m_.z.w;
  m_.w.x=-m_.w.x; m_.w.y=-m_.w.y; m_.w.z=-m_.w.z; m_.w.w=-m_.w.w;
}
//----

template<typename T>
PFC_INLINE mat44<T> lerp(const mat44<T> &m0_, const mat44<T> &m1_, typename math<T>::scalar_t t_)
{
  // linear matrix interpolation. f(t=0)=v0, f(t=1)=v1
  return mat44<T>(m0_.x.x+(m1_.x.x-m0_.x.x)*t_, m0_.x.y+(m1_.x.y-m0_.x.y)*t_, m0_.x.z+(m1_.x.z-m0_.x.z)*t_, m0_.x.w+(m1_.x.w-m0_.x.w)*t_,
                  m0_.y.x+(m1_.y.x-m0_.y.x)*t_, m0_.y.y+(m1_.y.y-m0_.y.y)*t_, m0_.y.z+(m1_.y.z-m0_.y.z)*t_, m0_.y.w+(m1_.y.w-m0_.y.w)*t_,
                  m0_.z.x+(m1_.z.x-m0_.z.x)*t_, m0_.z.y+(m1_.z.y-m0_.z.y)*t_, m0_.z.z+(m1_.z.z-m0_.z.z)*t_, m0_.z.w+(m1_.z.w-m0_.z.w)*t_,
                  m0_.w.x+(m1_.w.x-m0_.w.x)*t_, m0_.w.y+(m1_.w.y-m0_.w.y)*t_, m0_.w.z+(m1_.w.z-m0_.w.z)*t_, m0_.w.w+(m1_.w.w-m0_.w.w)*t_);
}
//----

template<typename T>
PFC_INLINE void lerp(mat44<T> &res_, const mat44<T> &m0_, const mat44<T> &m1_, typename math<T>::scalar_t t_)
{
  // linear matrix interpolation. f(t=0)=v0, f(t=1)=v1
  res_.x.x=m0_.x.x+(m1_.x.x-m0_.x.x)*t_; res_.x.y=m0_.x.y+(m1_.x.y-m0_.x.y)*t_; res_.x.z=m0_.x.z+(m1_.x.z-m0_.x.z)*t_; res_.x.w=m0_.x.w+(m1_.x.w-m0_.x.w)*t_;
  res_.y.x=m0_.y.x+(m1_.y.x-m0_.y.x)*t_; res_.y.y=m0_.y.y+(m1_.y.y-m0_.y.y)*t_; res_.y.z=m0_.y.z+(m1_.y.z-m0_.y.z)*t_; res_.y.w=m0_.y.w+(m1_.y.w-m0_.y.w)*t_;
  res_.z.x=m0_.z.x+(m1_.z.x-m0_.z.x)*t_; res_.z.y=m0_.z.y+(m1_.z.y-m0_.z.y)*t_; res_.z.z=m0_.z.z+(m1_.z.z-m0_.z.z)*t_; res_.z.w=m0_.z.w+(m1_.z.w-m0_.z.w)*t_;
  res_.w.x=m0_.w.x+(m1_.w.x-m0_.w.x)*t_; res_.w.y=m0_.w.y+(m1_.w.y-m0_.w.y)*t_; res_.w.z=m0_.w.z+(m1_.w.z-m0_.w.z)*t_; res_.w.w=m0_.w.w+(m1_.w.w-m0_.w.w)*t_;
}
//----

template<typename T, typename U>
PFC_INLINE mat44<T> to_mat44(const mat44<U> &m_)
{
  // convert between mat44 types
  typedef typename math<T>::scalar_t scalar_t;
  return mat44<T>(scalar_t(m_.x.x), scalar_t(m_.x.y), scalar_t(m_.x.z), scalar_t(m_.x.w),
                  scalar_t(m_.y.x), scalar_t(m_.y.y), scalar_t(m_.y.z), scalar_t(m_.y.w),
                  scalar_t(m_.z.x), scalar_t(m_.z.y), scalar_t(m_.z.z), scalar_t(m_.z.w),
                  scalar_t(m_.w.x), scalar_t(m_.w.y), scalar_t(m_.w.z), scalar_t(m_.w.w));
}
//----

template<typename T> PFC_INLINE void normalize(mat44<T> &m_)
{
  // normalize matrix vectors
  m_.x=unit(m_.x);
  m_.y=unit(m_.y);
  m_.z=unit(m_.z);
  m_.w=unit(m_.w);
}
//----------------------------------------------------------------------------


//============================================================================
// quat
//============================================================================
template<typename T> const quat<T> quat<T>::s_zero(T(0));
template<typename T> const quat<T> quat<T>::s_one(T(1));
template<typename T> const quat<T> quat<T>::s_neg_one(T(-1));
template<typename T> const quat<T> quat<T>::s_identity(0, 0, 0, T(1));
//----------------------------------------------------------------------------

template<typename T>
quat<T>::quat()
{
}
//----

template<typename T>
quat<T>::quat(T s_)
{
  // init quat with scalar
  x=s_;
  y=s_;
  z=s_;
  w=s_;
}
//----

template<typename T>
quat<T>::quat(T x_, T y_, T z_, T w_)
{
  // init quat with scalars
  x=x_;
  y=y_;
  z=z_;
  w=w_;
}
//----

template<typename T>
quat<T>::quat(const vec3<T> &v_)
{
  // init quat with 3d vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=0;
}
//----

template<typename T>
quat<T>::quat(const vec3<T> &v_, T w_)
{
  // init quat with 3d vector & w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

template<typename T>
quat<T>::quat(const vec4<T> &v_)
{
  // init quat with 4d vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=v_.w;
}
//----

template<typename T>
quat<T>::quat(const T *a_)
{
  // init quat with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
  z=a_[2];
  w=a_[3];
}
//----------------------------------------------------------------------------

template<typename T>
const T &quat<T>::operator[](unsigned idx_) const
{
  // return reference to nth component (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<const T*>(this)[idx_];
}
//----

template<typename T>
T &quat<T>::operator[](unsigned idx_)
{
  // return reference to nth component (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<T*>(this)[idx_];
}
//----

template<typename T>
void quat<T>::set(T s_)
{
  // set quat with scalar
  x=s_;
  y=s_;
  z=s_;
  w=s_;
}
//----

template<typename T>
void quat<T>::set(T x_, T y_, T z_, T w_)
{
  // set quat with scalars
  x=x_;
  y=y_;
  z=z_;
  w=w_;
}
//----

template<typename T>
void quat<T>::set(const vec3<T> &v_)
{
  // set quat with 3d vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=0;
}
//----

template<typename T>
void quat<T>::set(const vec3<T> &v_, T w_)
{
  // set quat with 3d vector & w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

template<typename T>
void quat<T>::set(const vec4<T> &v_)
{
  // set quat with 4d vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=v_.w;
}
//----

template<typename T>
void quat<T>::set(const quat<T> &q_)
{
  // set quat with quat
  x=q_.x;
  y=q_.y;
  z=q_.z;
  w=q_.w;
}
//----

template<typename T>
void quat<T>::set(const T *a_)
{
  // set quat with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
  z=a_[2];
  w=a_[3];
}
//----------------------------------------------------------------------------


//============================================================================
// quat<vec32_t>
//============================================================================
quat<vec32_t>::quat()
{
}
//----

quat<vec32_t>::quat(uint8_t s_)
{
  // init quat with scalar
  x=s_;
  y=s_;
  z=s_;
  w=s_;
}
//----

quat<vec32_t>::quat(uint8_t x_, uint8_t y_, uint8_t z_, uint8_t w_)
{
  // init quat with scalars
  x=x_;
  y=y_;
  z=z_;
  w=w_;
}
//----

quat<vec32_t>::quat(const vec3<vec32_t> &v_)
{
  // init quat with 3d vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=0;
}
//----

quat<vec32_t>::quat(const vec3<vec32_t> &v_, uint8_t w_)
{
  // init quat with 3d vector & w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

quat<vec32_t>::quat(const vec4<vec32_t> &v_)
{
  // init quat with 4d vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=v_.w;
}
//----

quat<vec32_t>::quat(const uint8_t *a_)
{
  // init quat with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
  z=a_[2];
  w=a_[3];
}
//----------------------------------------------------------------------------

const uint8_t &quat<vec32_t>::operator[](unsigned idx_) const
{
  // return reference to nth component (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<const uint8_t*>(this)[idx_];
}
//----

uint8_t &quat<vec32_t>::operator[](unsigned idx_)
{
  // return reference to nth component (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<uint8_t*>(this)[idx_];
}
//----

void quat<vec32_t>::set(uint8_t s_)
{
  // set quat with scalar
  x=s_;
  y=s_;
  z=s_;
  w=s_;
}
//----

void quat<vec32_t>::set(uint8_t x_, uint8_t y_, uint8_t z_, uint8_t w_)
{
  // set quat with scalars
  x=x_;
  y=y_;
  z=z_;
  w=w_;
}
//----

void quat<vec32_t>::set(const vec3<vec32_t> &v_)
{
  // set quat with 3d vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=0;
}
//----

void quat<vec32_t>::set(const vec3<vec32_t> &v_, uint8_t w_)
{
  // set quat with 3d vector & w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

void quat<vec32_t>::set(const vec4<vec32_t> &v_)
{
  // set quat with 4d vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=v_.w;
}
//----

void quat<vec32_t>::set(const quat<vec32_t> &q_)
{
  // set quat with quat
  x=q_.x;
  y=q_.y;
  z=q_.z;
  w=q_.w;
}
//----

void quat<vec32_t>::set(const uint8_t *a_)
{
  // set quat with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  x=a_[0];
  y=a_[1];
  z=a_[2];
  w=a_[3];
}
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE bool is_zero(const quat<T> &q_)
{
  // test for zero-quaternion
  return q_.x==0 && q_.y==0 && q_.z==0 && q_.w==0;
}
//----

template<typename T>
PFC_INLINE bool is_sat(const quat<T> &q_)
{
  // test for saturated quaternion
  typedef typename math<T>::scalar_t scalar_t;
  return    q_.x>=0 && q_.x<=scalar_t(1)
         && q_.y>=0 && q_.y<=scalar_t(1)
         && q_.z>=0 && q_.z<=scalar_t(1)
         && q_.w>=0 && q_.w<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const quat<T> &q_)
{
  // test for signed saturated quaternion
  typedef typename math<T>::scalar_t scalar_t;
  return    q_.x>=scalar_t(-1) && q_.x<=scalar_t(1)
         && q_.y>=scalar_t(-1) && q_.y<=scalar_t(1)
         && q_.z>=scalar_t(-1) && q_.z<=scalar_t(1)
         && q_.w>=scalar_t(-1) && q_.w<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool operator==(const quat<T> &q0_, const quat<T> &q1_)
{
  // test for equality of quats
  return q0_.x==q1_.x && q0_.y==q1_.y && q0_.z==q1_.z && q0_.w==q1_.w;
}
//----

template<typename T>
PFC_INLINE bool operator==(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // test for equality of quat and scalar
  return q_.x==s_ && q_.y==s_ && q_.z==s_ && q_.w==s_;
}
//----

template<typename T>
PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const quat<T> &q_)
{
  // test for equality of quat and scalar
  return s_==q_.x && s_==q_.y && s_==q_.z && s_==q_.w;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const quat<T> &q0_, const quat<T> &q1_)
{
  // test for inequality of quats
  return q0_.x!=q1_.x || q0_.y!=q1_.y || q0_.z!=q1_.z || q0_.w!=q1_.w;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // test for inequality of quat and scalar
  return q_.x!=s_ || q_.y!=s_ || q_.z!=s_ || q_.w!=s_;
}
//----

template<typename T>
PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const quat<T> &q_)
{
  // test for inequality of quat and scalar
  return s_!=q_.x || s_!=q_.y || s_!=q_.z || s_!=q_.w;
}
//----

template<typename T>
PFC_INLINE quat<T> operator<(const quat<T> &q0_, const quat<T> &q1_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q0_.x<q1_.x?scalar_t(1):0, q0_.y<q1_.y?scalar_t(1):0, q0_.z<q1_.z?scalar_t(1):0, q0_.w<q1_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE quat<T> operator<(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x<s_?scalar_t(1):0, q_.y<s_?scalar_t(1):0, q_.z<s_?scalar_t(1):0, q_.w<s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE quat<T> operator<(typename math<T>::scalar_t s_, const quat<T> &q_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(s_<q_.x?scalar_t(1):0, s_<q_.y?scalar_t(1):0, s_<q_.z?scalar_t(1):0, s_<q_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE quat<T> operator>(const quat<T> &q0_, const quat<T> &q1_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q0_.x>q1_.x?scalar_t(1):0, q0_.y>q1_.y?scalar_t(1):0, q0_.z>q1_.z?scalar_t(1):0, q0_.w>q1_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE quat<T> operator>(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x>s_?scalar_t(1):0, q_.y>s_?scalar_t(1):0, q_.z>s_?scalar_t(1):0, q_.w>s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE quat<T> operator>(typename math<T>::scalar_t s_, const quat<T> &q_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(s_>q_.x?scalar_t(1):0, s_>q_.y?scalar_t(1):0, s_>q_.z?scalar_t(1):0, s_>q_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE quat<T> operator<=(const quat<T> &q0_, const quat<T> &q1_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q0_.x<=q1_.x?scalar_t(1):0, q0_.y<=q1_.y?scalar_t(1):0, q0_.z<=q1_.z?scalar_t(1):0, q0_.w<=q1_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE quat<T> operator<=(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x<=s_?scalar_t(1):0, q_.y<=s_?scalar_t(1):0, q_.z<=s_?scalar_t(1):0, q_.w<=s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE quat<T> operator<=(typename math<T>::scalar_t s_, const quat<T> &q_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(s_<=q_.x?scalar_t(1):0, s_<=q_.y?scalar_t(1):0, s_<=q_.z?scalar_t(1):0, s_<=q_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE quat<T> operator>=(const quat<T> &q0_, const quat<T> &q1_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q0_.x>=q1_.x?scalar_t(1):0, q0_.y>=q1_.y?scalar_t(1):0, q0_.z>=q1_.z?scalar_t(1):0, q0_.w>=q1_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE quat<T> operator>=(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x>=s_?scalar_t(1):0, q_.y>=s_?scalar_t(1):0, q_.z>=s_?scalar_t(1):0, q_.w>=s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE quat<T> operator>=(typename math<T>::scalar_t s_, const quat<T> &q_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(s_>=q_.x?scalar_t(1):0, s_>=q_.y?scalar_t(1):0, s_>=q_.z?scalar_t(1):0, s_>=q_.w?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE quat<T> sel_eq(const quat<T> &t0_, const quat<T> &t1_, const quat<T> &q0_, const quat<T> &q1_)
{
  // component-wise equal quaternion select (t0_==t1_?q0_:q1_)
  return quat<T>(t0_.x==t1_.x?q0_.x:q1_.x,
                 t0_.y==t1_.y?q0_.y:q1_.y,
                 t0_.z==t1_.z?q0_.z:q1_.z,
                 t0_.w==t1_.w?q0_.w:q1_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> sel_lt(const quat<T> &t0_, const quat<T> &t1_, const quat<T> &q0_, const quat<T> &q1_)
{
  // component-wise less-than quaternion select (t0_<t1_?q0_:q1_)
  return quat<T>(t0_.x<t1_.x?q0_.x:q1_.x,
                 t0_.y<t1_.y?q0_.y:q1_.y,
                 t0_.z<t1_.z?q0_.z:q1_.z,
                 t0_.w<t1_.w?q0_.w:q1_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> sel_le(const quat<T> &t0_, const quat<T> &t1_, const quat<T> &q0_, const quat<T> &q1_)
{
  // component-wise less-or-equal quaternion select (t0_<=t1_?q0_:q1_)
  return quat<T>(t0_.x<=t1_.x?q0_.x:q1_.x,
                 t0_.y<=t1_.y?q0_.y:q1_.y,
                 t0_.z<=t1_.z?q0_.z:q1_.z,
                 t0_.w<=t1_.w?q0_.w:q1_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> sel_eqz(const quat<T> &t_, const quat<T> &q0_, const quat<T> &q1_)
{
  // component-wise equal-to-zero quaternion select (t_==0?q0_:q1_)
  return quat<T>(t_.x==0?q0_.x:q1_.x,
                 t_.y==0?q0_.y:q1_.y,
                 t_.z==0?q0_.z:q1_.z,
                 t_.w==0?q0_.w:q1_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> sel_ltz(const quat<T> &t_, const quat<T> &q0_, const quat<T> &q1_)
{
  // component-wise less-than-zero quaternion select (t_<0?q0_:q1_)
  return quat<T>(t_.x<0?q0_.x:q1_.x,
                 t_.y<0?q0_.y:q1_.y,
                 t_.z<0?q0_.z:q1_.z,
                 t_.w<0?q0_.w:q1_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> sel_lez(const quat<T> &t_, const quat<T> &q0_, const quat<T> &q1_)
{
  // component-wise less-or-equal-to-zero quaternion select (t_<=0?q0_:q1_)
  return quat<T>(t_.x<=0?q0_.x:q1_.x,
                 t_.y<=0?q0_.y:q1_.y,
                 t_.z<=0?q0_.z:q1_.z,
                 t_.w<=0?q0_.w:q1_.w);
}
//----

template<typename T>
PFC_INLINE void operator+=(quat<T> &qr_, const quat<T> &q_)
{
  // add quat to quat
  qr_.x+=q_.x;
  qr_.y+=q_.y;
  qr_.z+=q_.z;
  qr_.w+=q_.w;
}
//----

template<typename T>
PFC_INLINE void operator+=(quat<T> &qr_, typename math<T>::scalar_t s_)
{
  // add scalar to each component of the quat
  qr_.x+=s_;
  qr_.y+=s_;
  qr_.z+=s_;
  qr_.w+=s_;
}
//----

template<typename T>
PFC_INLINE void operator-=(quat<T> &qr_, const quat<T> &q_)
{
  // subtract quat from quat
  qr_.x-=q_.x;
  qr_.y-=q_.y;
  qr_.z-=q_.z;
  qr_.w-=q_.w;
}
//----

template<typename T>
PFC_INLINE void operator-=(quat<T> &qr_, typename math<T>::scalar_t s_)
{
  // subtract scalar from each component of the quat
  qr_.x-=s_;
  qr_.y-=s_;
  qr_.z-=s_;
  qr_.w-=s_;
}
//----

template<typename T>
PFC_INLINE void operator*=(quat<T> &qr_, const quat<T> &q_)
{
  // multiply quat by quat
  quat<T> q(qr_);
  qr_.x=q.y*q_.z-q.z*q_.y+q.w*q_.x+q.x*q_.w;
  qr_.y=q.z*q_.x-q.x*q_.z+q.w*q_.y+q.y*q_.w;
  qr_.z=q.x*q_.y-q.y*q_.x+q.w*q_.z+q.z*q_.w;
  qr_.w=q.w*q_.w-q.x*q_.x-q.y*q_.y-q.z*q_.z;
}
//----

template<typename T>
PFC_INLINE void operator*=(quat<T> &qr_, typename math<T>::scalar_t s_)
{
  // multiply quat by scalar
  qr_.x*=s_;
  qr_.y*=s_;
  qr_.z*=s_;
  qr_.w*=s_;
}
//----

template<typename T>
PFC_INLINE void operator/=(quat<T> &qr_, typename math<T>::scalar_t s_)
{
  // divide quat by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  qr_.x*=rs;
  qr_.y*=rs;
  qr_.z*=rs;
  qr_.w*=rs;
}
//----

template<typename T>
PFC_INLINE quat<T> operator+(const quat<T> &q0_, const quat<T> &q1_)
{
  // add quat to quat
  return quat<T>(q0_.x+q1_.x, q0_.y+q1_.y, q0_.z+q1_.z, q0_.w+q1_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> operator+(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // add scalar to each component of the quat
  return quat<T>(q_.x+s_, q_.y+s_, q_.z+s_, q_.w+s_);
}
//----

template<typename T>
PFC_INLINE quat<T> operator+(typename math<T>::scalar_t s_, const quat<T> &q_)
{
  // add each component of the quat to a scalar quat
  return quat<T>(s_+q_.x, s_+q_.y, s_+q_.z, s_+q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> operator-(const quat<T> &q0_, const quat<T> &q1_)
{
  // subtract quat from quat
  return quat<T>(q0_.x-q1_.x, q0_.y-q1_.y, q0_.z-q1_.z, q0_.w-q1_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> operator-(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // subtract scalar from each component of the quat
  return quat<T>(q_.x-s_, q_.y-s_, q_.z-s_, q_.w-s_);
}
//----

template<typename T>
PFC_INLINE quat<T> operator-(typename math<T>::scalar_t s_, const quat<T> &q_)
{
  // subtract each component of the quat from a scalar quat
  return quat<T>(s_-q_.x, s_-q_.y, s_-q_.z, s_-q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> operator-(const quat<T> &q_)
{
  // negate quat
  return quat<T>(-q_.x, -q_.y, -q_.z, -q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> operator*(const quat<T> &q0_, const quat<T> &q1_)
{
  // multiply quat by quat
  return quat<T>(q0_.y*q1_.z-q0_.z*q1_.y+q0_.w*q1_.x+q0_.x*q1_.w,
                 q0_.z*q1_.x-q0_.x*q1_.z+q0_.w*q1_.y+q0_.y*q1_.w,
                 q0_.x*q1_.y-q0_.y*q1_.x+q0_.w*q1_.z+q0_.z*q1_.w,
                 q0_.w*q1_.w-q0_.x*q1_.x-q0_.y*q1_.y-q0_.z*q1_.z);
}
//----

template<typename T>
PFC_INLINE quat<T> operator*(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // multiply quat by scalar
  return quat<T>(q_.x*s_, q_.y*s_, q_.z*s_, q_.w*s_);
}
//----

template<typename T>
PFC_INLINE quat<T> operator*(typename math<T>::scalar_t s_, const quat<T> &q_)
{
  // multiply quat by scalar
  return quat<T>(q_.x*s_, q_.y*s_, q_.z*s_, q_.w*s_);
}
//----

template<typename T>
PFC_INLINE quat<T> operator/(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // divide quat by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  return quat<T>(q_.x*rs, q_.y*rs, q_.z*rs, q_.w*rs);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t min(const quat<T> &q_)
{
  // minimum component value
  return min(q_.x, q_.y, q_.z, q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> min(const quat<T> &q0_, const quat<T> &q1_)
{
  // component-wise min quat
  return quat<T>(q0_.x<q1_.x?q0_.x:q1_.x,
                 q0_.y<q1_.y?q0_.y:q1_.y,
                 q0_.z<q1_.z?q0_.z:q1_.z,
                 q0_.w<q1_.w?q0_.w:q1_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> min(const quat<T> &q0_, const quat<T> &q1_, const quat<T> &q2_)
{
  // component-wise min quat
  return quat<T>(min(q0_.x, q1_.x, q2_.x),
                 min(q0_.y, q1_.y, q2_.y),
                 min(q0_.z, q1_.z, q2_.z),
                 min(q0_.w, q1_.w, q2_.w));
}
//----

template<typename T>
PFC_INLINE quat<T> min(const quat<T> &q0_, const quat<T> &q1_, const quat<T> &q2_, const quat<T> &q3_)
{
  // component-wise min quat
  return quat<T>(min(q0_.x, q1_.x, q2_.x, q3_.x),
                 min(q0_.y, q1_.y, q2_.y, q3_.y),
                 min(q0_.z, q1_.z, q2_.z, q3_.z),
                 min(q0_.w, q1_.w, q2_.w, q3_.w));
}
//----

template<typename T>
PFC_INLINE quat<T> min(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // component-wise min quat
  return quat<T>(q_.x<s_?q_.x:s_,
                 q_.y<s_?q_.y:s_,
                 q_.z<s_?q_.z:s_,
                 q_.w<s_?q_.w:s_);
}
//----

template<typename T>
PFC_INLINE quat<T> min(typename math<T>::scalar_t s_, const quat<T> &q_)
{
  // component-wise min quat
  return quat<T>(s_<q_.x?s_:q_.x,
                 s_<q_.y?s_:q_.y,
                 s_<q_.z?s_:q_.z,
                 s_<q_.w?s_:q_.w);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t max(const quat<T> &q_)
{
  // maximum component value
  return max(q_.x, q_.y, q_.z, q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> max(const quat<T> &q0_, const quat<T> &q1_)
{
  // component-wise max quat
  return quat<T>(q0_.x>q1_.x?q0_.x:q1_.x,
                 q0_.y>q1_.y?q0_.y:q1_.y,
                 q0_.z>q1_.z?q0_.z:q1_.z,
                 q0_.w>q1_.w?q0_.w:q1_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> max(const quat<T> &q0_, const quat<T> &q1_, const quat<T> &q2_)
{
  // component-wise max quat
  return quat<T>(max(q0_.x, q1_.x, q2_.x),
                 max(q0_.y, q1_.y, q2_.y),
                 max(q0_.z, q1_.z, q2_.z),
                 max(q0_.w, q1_.w, q2_.w));
}
//----

template<typename T>
PFC_INLINE quat<T> max(const quat<T> &q0_, const quat<T> &q1_, const quat<T> &q2_, const quat<T> &q3_)
{
  // component-wise max quat
  return quat<T>(max(q0_.x, q1_.x, q2_.x, q3_.x),
                 max(q0_.y, q1_.y, q2_.y, q3_.y),
                 max(q0_.z, q1_.z, q2_.z, q3_.z),
                 max(q0_.w, q1_.w, q2_.w, q3_.w));
}
//----

template<typename T>
PFC_INLINE quat<T> max(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // component-wise max quat
  return quat<T>(q_.x>s_?q_.x:s_,
                 q_.y>s_?q_.y:s_,
                 q_.z>s_?q_.z:s_,
                 q_.w>s_?q_.w:s_);
}
//----

template<typename T>
PFC_INLINE quat<T> max(typename math<T>::scalar_t s_, const quat<T> &q_)
{
  // component-wise max quat
  return quat<T>(s_>q_.x?s_:q_.x,
                 s_>q_.y?s_:q_.y,
                 s_>q_.z?s_:q_.z,
                 s_>q_.w?s_:q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> mul(const quat<T> &q0_, const quat<T> &q1_)
{
  // component-wise multiply: q0_*q1
  return quat<T>(q0_.x*q1_.x, q0_.y*q1_.y, q0_.z*q1_.z, q0_.w*q1_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> madd(const quat<T> &qm0_, const quat<T> &qm1_, const quat<T> &qa_)
{
  // component-wise multiply-add: qm0_*qm1_+qa_
  return quat<T>(qm0_.x*qm1_.x+qa_.x, qm0_.y*qm1_.y+qa_.y, qm0_.z*qm1_.z+qa_.z, qm0_.w*qm1_.w+qa_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> madd(const quat<T> &qm_, typename math<T>::scalar_t sm_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: qm_*sm_+sa_
  return quat<T>(qm_.x*sm_+sa_, qm_.y*sm_+sa_, qm_.z*sm_+sa_, qm_.w*sm_+sa_);
}
//----

template<typename T>
PFC_INLINE quat<T> madd(const quat<T> &qm0_, const quat<T> &qm1_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: qm0_*qm1_+sa_
  return quat<T>(qm0_.x*qm1_.x+sa_, qm0_.y*qm1_.y+sa_, qm0_.z*qm1_.z+sa_, qm0_.w*qm1_.w+sa_);
}
//----

template<typename T>
PFC_INLINE quat<T> madd(const quat<T> &qm_, typename math<T>::scalar_t sm_, const quat<T> &qa_)
{
  // component-wise multiply-add: qm_*sm_+qa_
  return quat<T>(qm_.x*sm_+qa_.x, qm_.y*sm_+qa_.y, qm_.z*sm_+qa_.z, qm_.w*sm_+qa_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> rcp(const quat<T> &q_)
{
  // component-wise reciprocal
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(q_.x && q_.y && q_.z && q_.w);
  return quat<T>(scalar_t(1)/q_.x, scalar_t(1)/q_.y, scalar_t(1)/q_.z, scalar_t(1)/q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> rcp_z(const quat<T> &q_)
{
  // component-wise reciprocal (set to 0 for 0 components)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x?scalar_t(1)/q_.x:0, q_.y?scalar_t(1)/q_.y:0, q_.z?scalar_t(1)/q_.z:0, q_.w?scalar_t(1)/q_.w:0);
}
//----

template<typename T>
PFC_INLINE quat<T> floor(const quat<T> &q_)
{
  // component-wise floor
  return quat<T>(std::floor(q_.x), std::floor(q_.y), std::floor(q_.z), std::floor(q_.w));
}
//----

template<typename T>
PFC_INLINE quat<T> ceil(const quat<T> &q_)
{
  // component-wise ceil
  return quat<T>(std::ceil(q_.x), std::ceil(q_.y), std::ceil(q_.z), std::ceil(q_.w));
}
//----

template<typename T>
PFC_INLINE quat<T> trunc(const quat<T> &q_)
{
  // component-wise truncate
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(scalar_t(int(q_.x)), scalar_t(int(q_.y)), scalar_t(int(q_.z)), scalar_t(int(q_.w)));
}
//----

template<typename T>
PFC_INLINE quat<T> frc(const quat<T> &q_)
{
  // component-wise fractional
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x-scalar_t(int(q_.x)), q_.y-scalar_t(int(q_.y)), q_.z-scalar_t(int(q_.z)), q_.w-scalar_t(int(q_.w)));
}
//----

template<typename T>
PFC_INLINE quat<T> mod(const quat<T> &q_, typename math<T>::scalar_t div_)
{
  // component-wise modulo
  return quat<T>(std::fmod(q_.x, div_), std::fmod(q_.y, div_), std::fmod(q_.z, div_), std::fmod(q_.w, div_));
}
//----

template<typename T>
PFC_INLINE quat<T> cycle(const quat<T> &q_, typename math<T>::scalar_t cycle_)
{
  // component-wise cycle
  return quat<T>(std::fmod(q_.x, cycle_)+(q_.x<0?cycle_:0),
                 std::fmod(q_.y, cycle_)+(q_.y<0?cycle_:0),
                 std::fmod(q_.z, cycle_)+(q_.z<0?cycle_:0),
                 std::fmod(q_.w, cycle_)+(q_.w<0?cycle_:0));
}
//----

template<typename T>
PFC_INLINE quat<T> cycle1(const quat<T> &q_)
{
  // cycle1
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x-scalar_t(int(q_.x))+(q_.x<0?scalar_t(1):0),
                 q_.y-scalar_t(int(q_.y))+(q_.y<0?scalar_t(1):0),
                 q_.z-scalar_t(int(q_.z))+(q_.z<0?scalar_t(1):0),
                 q_.w-scalar_t(int(q_.w))+(q_.w<0?scalar_t(1):0));
}
//----

template<typename T>
PFC_INLINE quat<T> sat(const quat<T> &q_)
{
  // component-wise saturate
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x<0?0:q_.x>scalar_t(1)?scalar_t(1):q_.x,
                 q_.y<0?0:q_.y>scalar_t(1)?scalar_t(1):q_.y,
                 q_.z<0?0:q_.z>scalar_t(1)?scalar_t(1):q_.z,
                 q_.w<0?0:q_.w>scalar_t(1)?scalar_t(1):q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> ssat(const quat<T> &q_)
{
  // component-wise signed saturate
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x<scalar_t(-1)?scalar_t(-1):q_.x>scalar_t(1)?scalar_t(1):q_.x,
                 q_.y<scalar_t(-1)?scalar_t(-1):q_.y>scalar_t(1)?scalar_t(1):q_.y,
                 q_.z<scalar_t(-1)?scalar_t(-1):q_.z>scalar_t(1)?scalar_t(1):q_.z,
                 q_.w<scalar_t(-1)?scalar_t(-1):q_.w>scalar_t(1)?scalar_t(1):q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> clamp(const quat<T> &q_, const quat<T> &min_, const quat<T> &max_)
{
  // component-wise clamp (to quats)
  return quat<T>(q_.x<min_.x?min_.x:q_.x>max_.x?max_.x:q_.x,
                 q_.y<min_.y?min_.y:q_.y>max_.y?max_.y:q_.y,
                 q_.z<min_.z?min_.z:q_.z>max_.z?max_.z:q_.z,
                 q_.w<min_.w?min_.w:q_.w>max_.w?max_.w:q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> clamp(const quat<T> &q_, typename math<T>::scalar_t min_, typename math<T>::scalar_t max_)
{
  // component-wise clamp (to scalars)
  return quat<T>(q_.x<min_?min_:q_.x>max_?max_:q_.x,
                 q_.y<min_?min_:q_.y>max_?max_:q_.y,
                 q_.z<min_?min_:q_.z>max_?max_:q_.z,
                 q_.w<min_?min_:q_.w>max_?max_:q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> abs(const quat<T> &q_)
{
  // component-wise absolute
  return quat<T>(std::abs(q_.x), std::abs(q_.y), std::abs(q_.z), std::abs(q_.w));
}
//----

template<typename T>
PFC_INLINE quat<T> sgn(const quat<T> &q_)
{
  // component-wise signum (neg=-1, pos=+1, zero=0)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x<0?scalar_t(-1):q_.x>0?scalar_t(1):0, q_.y<0?scalar_t(-1):q_.y>0?scalar_t(1):0, q_.z<0?scalar_t(-1):q_.z>0?scalar_t(1):0, q_.w<0?scalar_t(-1):q_.w>0?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE quat<T> sgn_zp(const quat<T> &q_)
{
  // component-wise signum (neg=-1, pos&zero=+1)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x<0?scalar_t(-1):scalar_t(1), q_.y<0?scalar_t(-1):scalar_t(1), q_.z<0?scalar_t(-1):scalar_t(1), q_.w<0?scalar_t(-1):scalar_t(1));
}
//----

template<typename T>
PFC_INLINE quat<T> sqr(const quat<T> &q_)
{
  // component-wise square
  return quat<T>(q_.x*q_.x, q_.y*q_.y, q_.z*q_.z, q_.w*q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> cubic(const quat<T> &q_)
{
  // component-wise cubic
  return quat<T>(q_.x*q_.x*q_.x, q_.y*q_.y*q_.y, q_.z*q_.z*q_.z, q_.w*q_.w*q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> sqrt(const quat<T> &q_)
{
  // component-wise square root
  PFC_ASSERT_PEDANTIC(q_.x>=0 && q_.y>=0 && q_.z>=0 && q_.w>=0);
  return quat<T>(std::sqrt(q_.x), std::sqrt(q_.y), std::sqrt(q_.z), std::sqrt(q_.w));
}
//----

template<typename T>
PFC_INLINE quat<T> sqrt_z(const quat<T> &q_)
{
  // component-wise square root (set to 0 for components less than zero)
  return quat<T>(sqrt_z(q_.x), sqrt_z(q_.y), sqrt_z(q_.z), sqrt_z(q_.w));
}
//----

template<typename T>
PFC_INLINE quat<T> cbrt(const quat<T> &q_)
{
  // component-wise cubic root
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x<0?-std::pow(-q_.x, scalar_t(1.0/3.0)):std::pow(q_.x, scalar_t(1.0/3.0)),
                 q_.y<0?-std::pow(-q_.y, scalar_t(1.0/3.0)):std::pow(q_.y, scalar_t(1.0/3.0)),
                 q_.z<0?-std::pow(-q_.z, scalar_t(1.0/3.0)):std::pow(q_.z, scalar_t(1.0/3.0)),
                 q_.w<0?-std::pow(-q_.w, scalar_t(1.0/3.0)):std::pow(q_.w, scalar_t(1.0/3.0)));
}
//----

template<typename T>
PFC_INLINE quat<T> rsqrt(const quat<T> &q_)
{
  // component-wise reciprocal square root
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(q_.x>0 && q_.y>0 && q_.z>0 && q_.w>0);
  return quat<T>(scalar_t(1)/std::sqrt(q_.x), scalar_t(1)/std::sqrt(q_.y), scalar_t(1)/std::sqrt(q_.z), scalar_t(1)/std::sqrt(q_.w));
}
//----

template<typename T>
PFC_INLINE quat<T> rsqrt_z(const quat<T> &q_)
{
  // component-wise reciprocal square root (set to 0 for components less than or equal to zero)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x>0?scalar_t(1)/std::sqrt(q_.x):0,
                 q_.y>0?scalar_t(1)/std::sqrt(q_.y):0,
                 q_.z>0?scalar_t(1)/std::sqrt(q_.z):0,
                 q_.w>0?scalar_t(1)/std::sqrt(q_.w):0);
}
//----

template<typename T>
PFC_INLINE quat<T> rcbrt(const quat<T> &q_)
{
  // component-wise reciprocal cubic root
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x<0?-std::pow(-q_.x, scalar_t(-1.0/3.0)):std::pow(q_.x, scalar_t(-1.0/3.0)),
                 q_.y<0?-std::pow(-q_.y, scalar_t(-1.0/3.0)):std::pow(q_.y, scalar_t(-1.0/3.0)),
                 q_.z<0?-std::pow(-q_.z, scalar_t(-1.0/3.0)):std::pow(q_.z, scalar_t(-1.0/3.0)),
                 q_.w<0?-std::pow(-q_.w, scalar_t(-1.0/3.0)):std::pow(q_.w, scalar_t(-1.0/3.0)));
}
//----

template<typename T>
PFC_INLINE quat<T> rcbrt_z(const quat<T> &q_)
{
  // component-wise reciprocal cubic root (set to 0 for 0 component)
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(q_.x?q_.x<0?-std::pow(-q_.x, scalar_t(-1.0/3.0)):std::pow(q_.x, scalar_t(-1.0/3.0)):0,
                 q_.y?q_.y<0?-std::pow(-q_.y, scalar_t(-1.0/3.0)):std::pow(q_.y, scalar_t(-1.0/3.0)):0,
                 q_.z?q_.z<0?-std::pow(-q_.z, scalar_t(-1.0/3.0)):std::pow(q_.z, scalar_t(-1.0/3.0)):0,
                 q_.w?q_.w<0?-std::pow(-q_.w, scalar_t(-1.0/3.0)):std::pow(q_.w, scalar_t(-1.0/3.0)):0);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t norm(const quat<T> &q_)
{
  // norm of the quat (=quat length)
  return std::sqrt(q_.x*q_.x+q_.y*q_.y+q_.z*q_.z+q_.w*q_.w);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm(const quat<T> &q_)
{
  // reciprocal norm of the quat
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=q_.x*q_.x+q_.y*q_.y+q_.z*q_.z+q_.w*q_.w;
  PFC_ASSERT_PEDANTIC(n2);
  return scalar_t(1)/std::sqrt(n2);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm_z(const quat<T> &q_)
{
  // reciprocal norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=q_.x*q_.x+q_.y*q_.y+q_.z*q_.z+q_.w*q_.w;
  return n2>0?scalar_t(1)/std::sqrt(n2):0;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t norm2(const quat<T> &q_)
{
  // squared norm of the quat
  return q_.x*q_.x+q_.y*q_.y+q_.z*q_.z+q_.w*q_.w;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm2(const quat<T> &q_)
{
  // reciprocal squared norm of the quat
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=q_.x*q_.x+q_.y*q_.y+q_.z*q_.z+q_.w*q_.w;
  PFC_ASSERT_PEDANTIC(n2);
  return scalar_t(1)/n2;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm2_z(const quat<T> &q_)
{
  // reciprocal squared norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t v=q_.x*q_.x+q_.y*q_.y+q_.z*q_.z+q_.w*q_.w;
  return v>0?scalar_t(1)/v:0;
}
//----

template<typename T>
PFC_INLINE quat<T> unit(const quat<T> &q_)
{
  // unit quat of the quat
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=q_.x*q_.x+q_.y*q_.y+q_.z*q_.z+q_.w*q_.w;
  PFC_ASSERT_PEDANTIC(n2);
  scalar_t rs=scalar_t(1)/std::sqrt(n2);
  return quat<T>(q_.x*rs, q_.y*rs, q_.z*rs, q_.w*rs);
}
//----

template<typename T>
PFC_INLINE quat<T> unit_z(const quat<T> &q_)
{
  // unit quat of the quat. if |q|=0, return q=[v=0, w=1]
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t rs=q_.x*q_.x+q_.y*q_.y+q_.z*q_.z+q_.w*q_.w;
  if(!rs)
    return quat<T>(0, 0, 0, scalar_t(1));
  rs=scalar_t(1)/std::sqrt(rs);
  return quat<T>(q_.x*rs, q_.y*rs, q_.z*rs, q_.w*rs);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t dot(const quat<T> &q0_, const quat<T> &q1_)
{
  // dot-product of quats
  return q0_.x*q1_.x+q0_.y*q1_.y+q0_.z*q1_.z+q0_.w*q1_.w;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t dot1(const quat<T> &q_)
{
  // dot-product with [1, 1, 1, 1]
  return q_.x+q_.y+q_.z+q_.w;
}
//----

template<typename T>
PFC_INLINE quat<T> cross(const quat<T> &q0_, const quat<T> &q1_)
{
  // cross-product of quats: cross(q0, q1)=[v0 x v1, 0]
  return quat<T>(q0_.y*q1_.z-q0_.z*q1_.y,
                 q0_.z*q1_.x-q0_.x*q1_.z,
                 q0_.x*q1_.y-q0_.y*q1_.x,
                 0);
}
//----

template<typename T>
PFC_INLINE quat<T> outer(const quat<T> &q0_, const quat<T> &q1_)
{
  // Euclidean outer-product of quats: outer(q0, q1)=[w0*v1-w1*v0-(v0 x v1), 0]
  return quat<T>(q0_.w*q1_.x-q1_.w*q0_.x-q0_.y*q1_.z+q0_.z*q1_.y,
                 q0_.w*q1_.y-q1_.w*q0_.y-q0_.z*q1_.x+q0_.x*q1_.z,
                 q0_.w*q1_.z-q1_.w*q0_.z-q0_.x*q1_.y+q0_.y*q1_.x,
                 0);
}
//----

template<typename T>
PFC_INLINE quat<T> even(const quat<T> &q0_, const quat<T> &q1_)
{
  // even-product of quats: even(q0, q1)=[w0*v1+w1*v0, w0*w1-dot(v0, v1)]
  return quat<T>(q0_.w*q1_.x+q1_.w*q0_.x,
                 q0_.w*q1_.y+q1_.w*q0_.y,
                 q0_.w*q1_.z+q1_.w*q0_.z,
                 q0_.w*q1_.w-q0_.x*q1_.x-q0_.y*q1_.y-q0_.z*q1_.z);
}
//----

template<typename T>
PFC_INLINE quat<T> conj(const quat<T> &q_)
{
  // conjugate of the quat
  return quat<T>(-q_.x, -q_.y, -q_.z, q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> inv(const quat<T> &q_)
{
  // inverse of the quat
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=q_.x*q_.x+q_.y*q_.y+q_.z*q_.z+q_.w*q_.w;
  PFC_ASSERT_PEDANTIC(n2);
  scalar_t rn2=scalar_t(1)/n2;
  return quat<T>(-q_.x*rn2, -q_.y*rn2, -q_.z*rn2, q_.w*rn2);
}
//----

template<typename T>
PFC_INLINE quat<T> inv_u(const quat<T> &q_)
{
  // inverse of the unit-quat
  return quat<T>(-q_.x, -q_.y, -q_.z, q_.w);
}
//----

template<typename T>
PFC_INLINE quat<T> exp(const quat<T> &q_)
{
  // quat natural exponent: exp(w)*[sin(|v|)*v/|v|, cos(|v|)]
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t vn=std::sqrt(q_.x*q_.x+q_.y*q_.y+q_.z*q_.z);
  PFC_ASSERT_PEDANTIC(vn);
  scalar_t s, c;
  sincos(s, c, vn);
  scalar_t ew=exp(q_.w);
  scalar_t vf=ew*s/vn;
  return quat<T>(q_.x*vf, q_.y*vf, q_.z*vf, ew*c);
}
//----

template<typename T>
PFC_INLINE quat<T> exp_u(const quat<T> &q_)
{
  // unit quat natural exponent: exp(w)*[sin(|v|)*v/|v|, cos(|v|)]
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(q_.w<=scalar_t(1));
  scalar_t vn=std::sqrt(scalar_t(1)-q_.w*q_.w);
  PFC_ASSERT_PEDANTIC(vn);
  scalar_t s, c;
  sincos(s, c, vn);
  scalar_t ew=exp(q_.w);
  scalar_t vf=ew*s/vn;
  return quat<T>(q_.x*vf, q_.y*vf, q_.z*vf, ew*c);
}
//----

template<typename T>
PFC_INLINE quat<T> ln(const quat<T> &q_)
{
  // quat natural logarithm: [acos(w/|q|)*v/|v|, ln(|q|)]
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t vn2=q_.x*q_.x+q_.y*q_.y+q_.z*q_.z;
  scalar_t n2=vn2+q_.w*q_.w;
  PFC_ASSERT_PEDANTIC(vn2 && n2);
  scalar_t rqn=scalar_t(1)/std::sqrt(n2);
  scalar_t vf=scalar_t(1)/std::sqrt(vn2)*acos(q_.w*rqn);
  return quat<T>(q_.x*vf, q_.y*vf, q_.z*vf, -ln(rqn));
}
//----

template<typename T>
PFC_INLINE quat<T> ln_u(const quat<T> &q_)
{
  // unit quat natural logarithm: [acos(w)*v/|v|, 0]
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t vn2=q_.x*q_.x+q_.y*q_.y+q_.z*q_.z;
  PFC_ASSERT_PEDANTIC(vn2);
  scalar_t vf=scalar_t(1)/std::sqrt(vn2)*acos(q_.w);
  return quat<T>(q_.x*vf, q_.y*vf, q_.z*vf, 0);
}
//----

template<typename T>
PFC_INLINE quat<T> pow(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // quat power: exp(ln(q)*s_)
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t s, c;
  scalar_t vn2=q_.x*q_.x+q_.y*q_.y+q_.z*q_.z;
  scalar_t qn=std::sqrt(vn2+q_.w*q_.w);
  PFC_ASSERT_PEDANTIC(vn2 && qn);
  sincos(s, c, acos(q_.w/qn)*s_);
  scalar_t ew=pow(qn, s_);
  scalar_t vf=ew*s/std::sqrt(vn2);
  return quat<T>(q_.x*vf, q_.y*vf, q_.z*vf, ew*c);
}
//----

template<typename T>
PFC_INLINE quat<T> pow_u(const quat<T> &q_, typename math<T>::scalar_t s_)
{
  // unit quat power: exp(ln_u(q)*s_)
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t vn=s_*acos(q_.w);
  PFC_ASSERT_PEDANTIC(vn);
  scalar_t s, c;
  sincos(s, c, vn);
  scalar_t vf=s/vn;
  return quat<T>(q_.x*vf, q_.y*vf, q_.z*vf, c);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t arg(const quat<T> &q_)
{
  // argument of the quat
  typename math<T>::scalar_t n2=q_.x*q_.x+q_.y*q_.y+q_.z*q_.z+q_.w*q_.w;
  PFC_ASSERT_PEDANTIC(n2);
  return acos(q_.w/std::sqrt(n2));
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t arg_u(const quat<T> &q_)
{
  // argument of the unit quat
  return acos(q_.w);
}
//----

template<typename T>
PFC_INLINE void neg(quat<T> &q_)
{
  // negate the quat
  q_.x=-q_.x;
  q_.y=-q_.y;
  q_.z=-q_.z;
  q_.w=-q_.w;
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_u(quat<T> &qr_, Rng &rng_)
{
  // random unit quaternion (even distribution on unit hypersphere)
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t rs, rc, vs, vc;
  sincos(rs, rc, scalar_t(rng_.rand_ureal1())*math<T>::pi);
  sincos(vs, vc, scalar_t(rng_.rand_ureal1())*math<T>::two_pi);
  scalar_t z=scalar_t(rng_.rand_real1());
  qr_.z=z*rs;
  qr_.w=rc;
  scalar_t rad=std::sqrt(scalar_t(1)-z*z)*rs;
  qr_.x=vs*rad;
  qr_.y=vc*rad;
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_real1(quat<T> &qr_, Rng &rng_)
{
  // random quaternion where each component is in range [-1, 1]
  typedef typename math<T>::scalar_t scalar_t;
  qr_.x=scalar_t(rng_.rand_real1());
  qr_.y=scalar_t(rng_.rand_real1());
  qr_.z=scalar_t(rng_.rand_real1());
  qr_.w=scalar_t(rng_.rand_real1());
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_ureal1(quat<T> &qr_, Rng &rng_)
{
  // random quaternion where each component is in range [0, 1]
  typedef typename math<T>::scalar_t scalar_t;
  qr_.x=scalar_t(rng_.rand_ureal1());
  qr_.y=scalar_t(rng_.rand_ureal1());
  qr_.z=scalar_t(rng_.rand_ureal1());
  qr_.w=scalar_t(rng_.rand_ureal1());
}
//----

template<typename T>
PFC_INLINE quat<T> smoothstep(const quat<T> &q_)
{
  // component-wise smoothstep function
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(q_.x>=0 && q_.x<=scalar_t(1) && q_.y>=0 && q_.y<=scalar_t(1) && q_.z>=0 && q_.z<=scalar_t(1) && q_.w>=0 && q_.w<=scalar_t(1));
  return quat<T>(q_.x*q_.x*(scalar_t(3)-scalar_t(2)*q_.x),
                 q_.y*q_.y*(scalar_t(3)-scalar_t(2)*q_.y),
                 q_.z*q_.z*(scalar_t(3)-scalar_t(2)*q_.z),
                 q_.w*q_.w*(scalar_t(3)-scalar_t(2)*q_.w));
}
//----

template<typename T>
PFC_INLINE quat<T> smootherstep(const quat<T> &q_)
{
  // component-wise smootherstep function
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(q_.x>=0 && q_.x<=scalar_t(1) && q_.y>=0 && q_.y<=scalar_t(1) && q_.z>=0 && q_.z<=scalar_t(1) && q_.w>=0 && q_.w<=scalar_t(1));
  return quat<T>(q_.x*q_.x*q_.x*(q_.x*(q_.x*scalar_t(6)-scalar_t(15))+scalar_t(10)),
                 q_.y*q_.y*q_.y*(q_.y*(q_.y*scalar_t(6)-scalar_t(15))+scalar_t(10)),
                 q_.z*q_.z*q_.z*(q_.z*(q_.z*scalar_t(6)-scalar_t(15))+scalar_t(10)),
                 q_.w*q_.w*q_.w*(q_.w*(q_.w*scalar_t(6)-scalar_t(15))+scalar_t(10)));
}
//----

template<typename T>
PFC_INLINE quat<T> lerp(const quat<T> &q0_, const quat<T> &q1_, typename math<T>::scalar_t t_)
{
  // linear quat interpolation. f(t=0)=q0, f(t=1)=q1
  return quat<T>(q0_.x+(q1_.x-q0_.x)*t_, q0_.y+(q1_.y-q0_.y)*t_, q0_.z+(q1_.z-q0_.z)*t_, q0_.w+(q1_.w-q0_.w)*t_);
}
//----

template<typename T>
PFC_INLINE quat<T> nlerp(const quat<T> &q0_, const quat<T> &q1_, typename math<T>::scalar_t t_)
{
  // normalized linear quat interpolation. f(t=0)=q0/|q0|, f(t=1)=q1/|q1|
  typedef typename math<T>::scalar_t scalar_t;
  quat<T> q(q0_.x+(q1_.x-q0_.x)*t_, q0_.y+(q1_.y-q0_.y)*t_, q0_.z+(q1_.z-q0_.z)*t_, q0_.w+(q1_.w-q0_.w)*t_);
  scalar_t n2=q.x*q.x+q.y*q.y+q.z*q.z+q.w*q.w;
  PFC_ASSERT_PEDANTIC(n2);
  scalar_t rs=scalar_t(1)/std::sqrt(n2);
  return quat<T>(q.x*rs, q.y*rs, q.z*rs, q.w*rs);
}
//----

template<typename T>
PFC_INLINE quat<T> nlerp_z(const quat<T> &q0_, const quat<T> &q1_, typename math<T>::scalar_t t_)
{
  // normalized linear quat interpolation. f(t=0)=q0/|q0|, f(t=1)=q1/|q1|. if interpolated |q|=0, return [0, 0, 0, 1]
  typedef typename math<T>::scalar_t scalar_t;
  quat<T> q(q0_.x+(q1_.x-q0_.x)*t_, q0_.y+(q1_.y-q0_.y)*t_, q0_.z+(q1_.z-q0_.z)*t_, q0_.w+(q1_.w-q0_.w)*t_);
  scalar_t rs=q.x*q.x+q.y*q.y+q.z*q.z+q.w*q.w;
  if(!rs)
    return quat<T>(0, 0, 0, scalar_t(1));
  rs=scalar_t(1)/std::sqrt(rs);
  return quat<T>(q.x*rs, q.y*rs, q.z*rs, q.w*rs);
}
//----

template<typename T>
PFC_INLINE quat<T> slerp(const quat<T> &q0_, const quat<T> &q1_, typename math<T>::scalar_t t_)
{
  // spherical linear quat interpolation. f(t=0)=q0, f(t=1)=q1
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t a=acos(q0_.x*q1_.x+q0_.y*q1_.y+q0_.z*q1_.z+q0_.w*q1_.w);
  scalar_t rs=csc(a);
  return q0_*(sin((scalar_t(1)-t_)*a)*rs)+q1_*(sin(t_*a)*rs);
}
//----

template<typename T>
PFC_INLINE quat<T> rot_u(const vec3<T> &src_, const vec3<T> &dst_)
{
  // generate rotation from source to destination direction
  vec3<T> v=unit_z(src_+dst_);
  return quat<T>(cross(v, dst_), dot(v, dst_));
}
//----

template<typename T>
PFC_INLINE quat<T> zrot_u(const vec3<T> &dst_)
{
  // generate rotation from z-axis to destination direction
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> v=unit_z(dst_+vec3<T>(0, 0, scalar_t(1)));
  if(is_zero(v))
    v.set(scalar_t(1), 0, 0);
  return quat<T>(cross(vec3<T>(0, 0, scalar_t(1)), v), v.z);
}
//----

template<typename T>
PFC_INLINE quat<T> axis_rot(const vec3<T> &axis_, typename math<T>::scalar_t angle_)
{
  // generate rotation from axis and angle (radians)
  typedef typename math<T>::scalar_t scalar_t;
  if(!norm2(axis_))
    return quat<T>(0, 0, 0, scalar_t(1));
  scalar_t s, c;
  sincos(s, c, angle_*scalar_t(0.5));
  return quat<T>(unit(axis_)*s, c);
}
//----

template<typename T>
PFC_INLINE quat<T> axis_rot_u(const vec3<T> &axis_, typename math<T>::scalar_t angle_)
{
  // generate rotation from unit axis and angle (radians)
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC_MSG(abs(norm2(axis_)-scalar_t(1))<scalar_t(0.0005), ("Axis vector length must be 1.0 (%f)\r\n", norm(axis_)));
  scalar_t s, c;
  sincos(s, c, angle_*scalar_t(0.5));
  return quat<T>(axis_*s, c);
}
//----

template<typename T>
void convert_u(mat33<T> &m_, const quat<T> &q_)
{
  // convert the unit quat to 3x3 row major rotation matrix
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t xs=q_.x+q_.x;
  scalar_t ys=q_.y+q_.y;
  scalar_t zs=q_.z+q_.z;
  scalar_t xx=q_.x*xs;
  scalar_t yy=q_.y*ys;
  scalar_t zz=q_.z*zs;
  m_.x.x=scalar_t(1)-yy-zz;
  m_.y.y=scalar_t(1)-xx-zz;
  m_.z.z=scalar_t(1)-xx-yy;
  scalar_t xy=q_.x*ys;
  scalar_t wz=q_.w*zs;
  m_.x.y=xy+wz;
  m_.y.x=xy-wz;
  scalar_t xz=q_.x*zs;
  scalar_t wy=q_.w*ys;
  m_.x.z=xz-wy;
  m_.z.x=xz+wy;
  scalar_t yz=q_.y*zs;
  scalar_t wx=q_.w*xs;
  m_.y.z=yz+wx;
  m_.z.y=yz-wx;
}
//----

template<typename T>
void convert(mat33<T> &m_, const quat<T> &q_)
{
  // convert the quat to 3x3 row major rotation matrix
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t s=rnorm2(q_);
  s+=s;
  scalar_t xs=q_.x*s;
  scalar_t ys=q_.y*s;
  scalar_t zs=q_.z*s;
  scalar_t xx=q_.x*xs;
  scalar_t yy=q_.y*ys;
  scalar_t zz=q_.z*zs;
  m_.x.x=scalar_t(1)-yy-zz;
  m_.y.y=scalar_t(1)-xx-zz;
  m_.z.z=scalar_t(1)-xx-yy;
  scalar_t xy=q_.x*ys;
  scalar_t wz=q_.w*zs;
  m_.x.y=xy+wz;
  m_.y.x=xy-wz;
  scalar_t xz=q_.x*zs;
  scalar_t wy=q_.w*ys;
  m_.x.z=xz-wy;
  m_.z.x=xz+wy;
  scalar_t yz=q_.y*zs;
  scalar_t wx=q_.w*xs;
  m_.y.z=yz+wx;
  m_.z.y=yz-wx;
}
//----

template<typename T>
void convert(quat<T> &q_, const mat33<T> &m_)
{
  // check for positive matrix trace
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC_MSG(abs(det(m_)-scalar_t(1))<scalar_t(0.01), ("Matrix determinant must be 1 for quaternion conversion (det = %f)\r\n", float(det(m_))));
  scalar_t tr=m_.x.x+m_.y.y+m_.z.z;
  if(tr>0)
  {
    scalar_t s=std::sqrt(tr+scalar_t(1));
    q_.w=s*scalar_t(0.5);
    s=scalar_t(0.5)/s;
    q_.x=(m_.y.z-m_.z.y)*s;
    q_.y=(m_.z.x-m_.x.z)*s;
    q_.z=(m_.x.y-m_.y.x)*s;
  }
  else
  {
    // find largest diagonal value and setup element indices
    unsigned i=m_.y.y>m_.x.x?1:0;
    if(m_.z.z>m_[i][i])
      i=2;
    const unsigned next[3]={1, 2, 0};
    unsigned j=next[i], k=next[j];

    // convert the matrix
    scalar_t s=std::sqrt(m_[i][i]-m_[j][j]-m_[k][k]+scalar_t(1));
    q_[i]=s*scalar_t(0.5);
    s=scalar_t(0.5)/s;
    q_.w=(m_[j][k]-m_[k][j])*s;
    q_[j]=(m_[i][j]+m_[j][i])*s;
    q_[k]=(m_[i][k]+m_[k][i])*s;
  }
}
//----

template<typename T, typename U>
PFC_INLINE quat<T> to_quat(const quat<U> &q_)
{
  // convert between quat types
  typedef typename math<T>::scalar_t scalar_t;
  return quat<T>(scalar_t(q_.x), scalar_t(q_.y), scalar_t(q_.z), scalar_t(q_.w));
}
//----

namespace priv
{
  template<unsigned shuffle_, typename T>
  struct shuffle_quat_helper
  {
    static quat<T> shuffle(const quat<T>&) {PFC_CTF_ERROR(T, invalid_quaternion_component_shuffle);}
  };
  #define PFC_QUAT_SHUFFLE(shuffle__, x__, y__, z__, w__)\
  template<typename T> struct shuffle_quat_helper<shuffle__, T>\
  {\
    static PFC_INLINE quat<T> shuffle(const quat<T> &q_) {return quat<T>(q_.x__, q_.y__, q_.z__, q_.w__);}\
  };
  PFC_QUAT_SHUFFLE(0000, x, x, x, x); PFC_QUAT_SHUFFLE(0001, x, x, x, y); PFC_QUAT_SHUFFLE(0002, x, x, x, z); PFC_QUAT_SHUFFLE(0003, x, x, x, w); PFC_QUAT_SHUFFLE(0010, x, x, y, x); PFC_QUAT_SHUFFLE(0011, x, x, y, y); PFC_QUAT_SHUFFLE(0012, x, x, y, z); PFC_QUAT_SHUFFLE(0013, x, x, y, w); PFC_QUAT_SHUFFLE(0020, x, x, z, x); PFC_QUAT_SHUFFLE(0021, x, x, z, y); PFC_QUAT_SHUFFLE(0022, x, x, z, z); PFC_QUAT_SHUFFLE(0023, x, x, z, w); PFC_QUAT_SHUFFLE(0030, x, x, w, x); PFC_QUAT_SHUFFLE(0031, x, x, w, y); PFC_QUAT_SHUFFLE(0032, x, x, w, z); PFC_QUAT_SHUFFLE(0033, x, x, w, w);
  PFC_QUAT_SHUFFLE(0100, x, y, x, x); PFC_QUAT_SHUFFLE(0101, x, y, x, y); PFC_QUAT_SHUFFLE(0102, x, y, x, z); PFC_QUAT_SHUFFLE(0103, x, y, x, w); PFC_QUAT_SHUFFLE(0110, x, y, y, x); PFC_QUAT_SHUFFLE(0111, x, y, y, y); PFC_QUAT_SHUFFLE(0112, x, y, y, z); PFC_QUAT_SHUFFLE(0113, x, y, y, w); PFC_QUAT_SHUFFLE(0120, x, y, z, x); PFC_QUAT_SHUFFLE(0121, x, y, z, y); PFC_QUAT_SHUFFLE(0122, x, y, z, z); PFC_QUAT_SHUFFLE(0123, x, y, z, w); PFC_QUAT_SHUFFLE(0130, x, y, w, x); PFC_QUAT_SHUFFLE(0131, x, y, w, y); PFC_QUAT_SHUFFLE(0132, x, y, w, z); PFC_QUAT_SHUFFLE(0133, x, y, w, w);
  PFC_QUAT_SHUFFLE(0200, x, z, x, x); PFC_QUAT_SHUFFLE(0201, x, z, x, y); PFC_QUAT_SHUFFLE(0202, x, z, x, z); PFC_QUAT_SHUFFLE(0203, x, z, x, w); PFC_QUAT_SHUFFLE(0210, x, z, y, x); PFC_QUAT_SHUFFLE(0211, x, z, y, y); PFC_QUAT_SHUFFLE(0212, x, z, y, z); PFC_QUAT_SHUFFLE(0213, x, z, y, w); PFC_QUAT_SHUFFLE(0220, x, z, z, x); PFC_QUAT_SHUFFLE(0221, x, z, z, y); PFC_QUAT_SHUFFLE(0222, x, z, z, z); PFC_QUAT_SHUFFLE(0223, x, z, z, w); PFC_QUAT_SHUFFLE(0230, x, z, w, x); PFC_QUAT_SHUFFLE(0231, x, z, w, y); PFC_QUAT_SHUFFLE(0232, x, z, w, z); PFC_QUAT_SHUFFLE(0233, x, z, w, w);
  PFC_QUAT_SHUFFLE(0300, x, w, x, x); PFC_QUAT_SHUFFLE(0301, x, w, x, y); PFC_QUAT_SHUFFLE(0302, x, w, x, z); PFC_QUAT_SHUFFLE(0303, x, w, x, w); PFC_QUAT_SHUFFLE(0310, x, w, y, x); PFC_QUAT_SHUFFLE(0311, x, w, y, y); PFC_QUAT_SHUFFLE(0312, x, w, y, z); PFC_QUAT_SHUFFLE(0313, x, w, y, w); PFC_QUAT_SHUFFLE(0320, x, w, z, x); PFC_QUAT_SHUFFLE(0321, x, w, z, y); PFC_QUAT_SHUFFLE(0322, x, w, z, z); PFC_QUAT_SHUFFLE(0323, x, w, z, w); PFC_QUAT_SHUFFLE(0330, x, w, w, x); PFC_QUAT_SHUFFLE(0331, x, w, w, y); PFC_QUAT_SHUFFLE(0332, x, w, w, z); PFC_QUAT_SHUFFLE(0333, x, w, w, w);
  PFC_QUAT_SHUFFLE(1000, y, x, x, x); PFC_QUAT_SHUFFLE(1001, y, x, x, y); PFC_QUAT_SHUFFLE(1002, y, x, x, z); PFC_QUAT_SHUFFLE(1003, y, x, x, w); PFC_QUAT_SHUFFLE(1010, y, x, y, x); PFC_QUAT_SHUFFLE(1011, y, x, y, y); PFC_QUAT_SHUFFLE(1012, y, x, y, z); PFC_QUAT_SHUFFLE(1013, y, x, y, w); PFC_QUAT_SHUFFLE(1020, y, x, z, x); PFC_QUAT_SHUFFLE(1021, y, x, z, y); PFC_QUAT_SHUFFLE(1022, y, x, z, z); PFC_QUAT_SHUFFLE(1023, y, x, z, w); PFC_QUAT_SHUFFLE(1030, y, x, w, x); PFC_QUAT_SHUFFLE(1031, y, x, w, y); PFC_QUAT_SHUFFLE(1032, y, x, w, z); PFC_QUAT_SHUFFLE(1033, y, x, w, w);
  PFC_QUAT_SHUFFLE(1100, y, y, x, x); PFC_QUAT_SHUFFLE(1101, y, y, x, y); PFC_QUAT_SHUFFLE(1102, y, y, x, z); PFC_QUAT_SHUFFLE(1103, y, y, x, w); PFC_QUAT_SHUFFLE(1110, y, y, y, x); PFC_QUAT_SHUFFLE(1111, y, y, y, y); PFC_QUAT_SHUFFLE(1112, y, y, y, z); PFC_QUAT_SHUFFLE(1113, y, y, y, w); PFC_QUAT_SHUFFLE(1120, y, y, z, x); PFC_QUAT_SHUFFLE(1121, y, y, z, y); PFC_QUAT_SHUFFLE(1122, y, y, z, z); PFC_QUAT_SHUFFLE(1123, y, y, z, w); PFC_QUAT_SHUFFLE(1130, y, y, w, x); PFC_QUAT_SHUFFLE(1131, y, y, w, y); PFC_QUAT_SHUFFLE(1132, y, y, w, z); PFC_QUAT_SHUFFLE(1133, y, y, w, w);
  PFC_QUAT_SHUFFLE(1200, y, z, x, x); PFC_QUAT_SHUFFLE(1201, y, z, x, y); PFC_QUAT_SHUFFLE(1202, y, z, x, z); PFC_QUAT_SHUFFLE(1203, y, z, x, w); PFC_QUAT_SHUFFLE(1210, y, z, y, x); PFC_QUAT_SHUFFLE(1211, y, z, y, y); PFC_QUAT_SHUFFLE(1212, y, z, y, z); PFC_QUAT_SHUFFLE(1213, y, z, y, w); PFC_QUAT_SHUFFLE(1220, y, z, z, x); PFC_QUAT_SHUFFLE(1221, y, z, z, y); PFC_QUAT_SHUFFLE(1222, y, z, z, z); PFC_QUAT_SHUFFLE(1223, y, z, z, w); PFC_QUAT_SHUFFLE(1230, y, z, w, x); PFC_QUAT_SHUFFLE(1231, y, z, w, y); PFC_QUAT_SHUFFLE(1232, y, z, w, z); PFC_QUAT_SHUFFLE(1233, y, z, w, w);
  PFC_QUAT_SHUFFLE(1300, y, w, x, x); PFC_QUAT_SHUFFLE(1301, y, w, x, y); PFC_QUAT_SHUFFLE(1302, y, w, x, z); PFC_QUAT_SHUFFLE(1303, y, w, x, w); PFC_QUAT_SHUFFLE(1310, y, w, y, x); PFC_QUAT_SHUFFLE(1311, y, w, y, y); PFC_QUAT_SHUFFLE(1312, y, w, y, z); PFC_QUAT_SHUFFLE(1313, y, w, y, w); PFC_QUAT_SHUFFLE(1320, y, w, z, x); PFC_QUAT_SHUFFLE(1321, y, w, z, y); PFC_QUAT_SHUFFLE(1322, y, w, z, z); PFC_QUAT_SHUFFLE(1323, y, w, z, w); PFC_QUAT_SHUFFLE(1330, y, w, w, x); PFC_QUAT_SHUFFLE(1331, y, w, w, y); PFC_QUAT_SHUFFLE(1332, y, w, w, z); PFC_QUAT_SHUFFLE(1333, y, w, w, w);
  PFC_QUAT_SHUFFLE(2000, z, x, x, x); PFC_QUAT_SHUFFLE(2001, z, x, x, y); PFC_QUAT_SHUFFLE(2002, z, x, x, z); PFC_QUAT_SHUFFLE(2003, z, x, x, w); PFC_QUAT_SHUFFLE(2010, z, x, y, x); PFC_QUAT_SHUFFLE(2011, z, x, y, y); PFC_QUAT_SHUFFLE(2012, z, x, y, z); PFC_QUAT_SHUFFLE(2013, z, x, y, w); PFC_QUAT_SHUFFLE(2020, z, x, z, x); PFC_QUAT_SHUFFLE(2021, z, x, z, y); PFC_QUAT_SHUFFLE(2022, z, x, z, z); PFC_QUAT_SHUFFLE(2023, z, x, z, w); PFC_QUAT_SHUFFLE(2030, z, x, w, x); PFC_QUAT_SHUFFLE(2031, z, x, w, y); PFC_QUAT_SHUFFLE(2032, z, x, w, z); PFC_QUAT_SHUFFLE(2033, z, x, w, w);
  PFC_QUAT_SHUFFLE(2100, z, y, x, x); PFC_QUAT_SHUFFLE(2101, z, y, x, y); PFC_QUAT_SHUFFLE(2102, z, y, x, z); PFC_QUAT_SHUFFLE(2103, z, y, x, w); PFC_QUAT_SHUFFLE(2110, z, y, y, x); PFC_QUAT_SHUFFLE(2111, z, y, y, y); PFC_QUAT_SHUFFLE(2112, z, y, y, z); PFC_QUAT_SHUFFLE(2113, z, y, y, w); PFC_QUAT_SHUFFLE(2120, z, y, z, x); PFC_QUAT_SHUFFLE(2121, z, y, z, y); PFC_QUAT_SHUFFLE(2122, z, y, z, z); PFC_QUAT_SHUFFLE(2123, z, y, z, w); PFC_QUAT_SHUFFLE(2130, z, y, w, x); PFC_QUAT_SHUFFLE(2131, z, y, w, y); PFC_QUAT_SHUFFLE(2132, z, y, w, z); PFC_QUAT_SHUFFLE(2133, z, y, w, w);
  PFC_QUAT_SHUFFLE(2200, z, z, x, x); PFC_QUAT_SHUFFLE(2201, z, z, x, y); PFC_QUAT_SHUFFLE(2202, z, z, x, z); PFC_QUAT_SHUFFLE(2203, z, z, x, w); PFC_QUAT_SHUFFLE(2210, z, z, y, x); PFC_QUAT_SHUFFLE(2211, z, z, y, y); PFC_QUAT_SHUFFLE(2212, z, z, y, z); PFC_QUAT_SHUFFLE(2213, z, z, y, w); PFC_QUAT_SHUFFLE(2220, z, z, z, x); PFC_QUAT_SHUFFLE(2221, z, z, z, y); PFC_QUAT_SHUFFLE(2222, z, z, z, z); PFC_QUAT_SHUFFLE(2223, z, z, z, w); PFC_QUAT_SHUFFLE(2230, z, z, w, x); PFC_QUAT_SHUFFLE(2231, z, z, w, y); PFC_QUAT_SHUFFLE(2232, z, z, w, z); PFC_QUAT_SHUFFLE(2233, z, z, w, w);
  PFC_QUAT_SHUFFLE(2300, z, w, x, x); PFC_QUAT_SHUFFLE(2301, z, w, x, y); PFC_QUAT_SHUFFLE(2302, z, w, x, z); PFC_QUAT_SHUFFLE(2303, z, w, x, w); PFC_QUAT_SHUFFLE(2310, z, w, y, x); PFC_QUAT_SHUFFLE(2311, z, w, y, y); PFC_QUAT_SHUFFLE(2312, z, w, y, z); PFC_QUAT_SHUFFLE(2313, z, w, y, w); PFC_QUAT_SHUFFLE(2320, z, w, z, x); PFC_QUAT_SHUFFLE(2321, z, w, z, y); PFC_QUAT_SHUFFLE(2322, z, w, z, z); PFC_QUAT_SHUFFLE(2323, z, w, z, w); PFC_QUAT_SHUFFLE(2330, z, w, w, x); PFC_QUAT_SHUFFLE(2331, z, w, w, y); PFC_QUAT_SHUFFLE(2332, z, w, w, z); PFC_QUAT_SHUFFLE(2333, z, w, w, w);
  PFC_QUAT_SHUFFLE(3000, w, x, x, x); PFC_QUAT_SHUFFLE(3001, w, x, x, y); PFC_QUAT_SHUFFLE(3002, w, x, x, z); PFC_QUAT_SHUFFLE(3003, w, x, x, w); PFC_QUAT_SHUFFLE(3010, w, x, y, x); PFC_QUAT_SHUFFLE(3011, w, x, y, y); PFC_QUAT_SHUFFLE(3012, w, x, y, z); PFC_QUAT_SHUFFLE(3013, w, x, y, w); PFC_QUAT_SHUFFLE(3020, w, x, z, x); PFC_QUAT_SHUFFLE(3021, w, x, z, y); PFC_QUAT_SHUFFLE(3022, w, x, z, z); PFC_QUAT_SHUFFLE(3023, w, x, z, w); PFC_QUAT_SHUFFLE(3030, w, x, w, x); PFC_QUAT_SHUFFLE(3031, w, x, w, y); PFC_QUAT_SHUFFLE(3032, w, x, w, z); PFC_QUAT_SHUFFLE(3033, w, x, w, w);
  PFC_QUAT_SHUFFLE(3100, w, y, x, x); PFC_QUAT_SHUFFLE(3101, w, y, x, y); PFC_QUAT_SHUFFLE(3102, w, y, x, z); PFC_QUAT_SHUFFLE(3103, w, y, x, w); PFC_QUAT_SHUFFLE(3110, w, y, y, x); PFC_QUAT_SHUFFLE(3111, w, y, y, y); PFC_QUAT_SHUFFLE(3112, w, y, y, z); PFC_QUAT_SHUFFLE(3113, w, y, y, w); PFC_QUAT_SHUFFLE(3120, w, y, z, x); PFC_QUAT_SHUFFLE(3121, w, y, z, y); PFC_QUAT_SHUFFLE(3122, w, y, z, z); PFC_QUAT_SHUFFLE(3123, w, y, z, w); PFC_QUAT_SHUFFLE(3130, w, y, w, x); PFC_QUAT_SHUFFLE(3131, w, y, w, y); PFC_QUAT_SHUFFLE(3132, w, y, w, z); PFC_QUAT_SHUFFLE(3133, w, y, w, w);
  PFC_QUAT_SHUFFLE(3200, w, z, x, x); PFC_QUAT_SHUFFLE(3201, w, z, x, y); PFC_QUAT_SHUFFLE(3202, w, z, x, z); PFC_QUAT_SHUFFLE(3203, w, z, x, w); PFC_QUAT_SHUFFLE(3210, w, z, y, x); PFC_QUAT_SHUFFLE(3211, w, z, y, y); PFC_QUAT_SHUFFLE(3212, w, z, y, z); PFC_QUAT_SHUFFLE(3213, w, z, y, w); PFC_QUAT_SHUFFLE(3220, w, z, z, x); PFC_QUAT_SHUFFLE(3221, w, z, z, y); PFC_QUAT_SHUFFLE(3222, w, z, z, z); PFC_QUAT_SHUFFLE(3223, w, z, z, w); PFC_QUAT_SHUFFLE(3230, w, z, w, x); PFC_QUAT_SHUFFLE(3231, w, z, w, y); PFC_QUAT_SHUFFLE(3232, w, z, w, z); PFC_QUAT_SHUFFLE(3233, w, z, w, w);
  PFC_QUAT_SHUFFLE(3300, w, w, x, x); PFC_QUAT_SHUFFLE(3301, w, w, x, y); PFC_QUAT_SHUFFLE(3302, w, w, x, z); PFC_QUAT_SHUFFLE(3303, w, w, x, w); PFC_QUAT_SHUFFLE(3310, w, w, y, x); PFC_QUAT_SHUFFLE(3311, w, w, y, y); PFC_QUAT_SHUFFLE(3312, w, w, y, z); PFC_QUAT_SHUFFLE(3313, w, w, y, w); PFC_QUAT_SHUFFLE(3320, w, w, z, x); PFC_QUAT_SHUFFLE(3321, w, w, z, y); PFC_QUAT_SHUFFLE(3322, w, w, z, z); PFC_QUAT_SHUFFLE(3323, w, w, z, w); PFC_QUAT_SHUFFLE(3330, w, w, w, x); PFC_QUAT_SHUFFLE(3331, w, w, w, y); PFC_QUAT_SHUFFLE(3332, w, w, w, z); PFC_QUAT_SHUFFLE(3333, w, w, w, w);
  #undef PFC_QUAT_SHUFFLE
} // namespace priv
//----

template<unsigned shuffle_, typename T>
PFC_INLINE quat<T> shuffle(const quat<T> &q_)
{
  return priv::shuffle_quat_helper<shuffle_, T>::shuffle(q_);
}
//----

template<typename T>
PFC_INLINE void pack_u1(quat_32 &qr_, const quat<T> &q_)
{
  // pack quat (components in range [0, 1]) to 32-bit quat
  PFC_ASSERT_PEDANTIC_MSG(is_sat(q_), ("All quaternion components [%f, %f, %f, %f] must be in range [0, 1]\r\n", float(q_.x), float(q_.y), float(q_.z), float(q_.w)));
  typedef typename math<T>::scalar_t scalar_t;
  qr_.x=uint8_t(q_.x*scalar_t(255.999));
  qr_.y=uint8_t(q_.y*scalar_t(255.999));
  qr_.z=uint8_t(q_.z*scalar_t(255.999));
  qr_.w=uint8_t(q_.w*scalar_t(255.999));
}
//----

template<typename T>
PFC_INLINE void pack_s1(quat_32 &qr_, const quat<T> &q_)
{
  // pack quat (components in range [-1, 1]) to 32-bit quat
  PFC_ASSERT_PEDANTIC_MSG(is_ssat(q_), ("All quaternion components [%f, %f, %f, %f] must be in range [-1, 1]\r\n", float(q_.x), float(q_.y), float(q_.z), float(q_.w)));
  typedef typename math<T>::scalar_t scalar_t;
  qr_.x=uint8_t(q_.x*scalar_t(127.999)+scalar_t(128.0));
  qr_.y=uint8_t(q_.y*scalar_t(127.999)+scalar_t(128.0));
  qr_.z=uint8_t(q_.z*scalar_t(127.999)+scalar_t(128.0));
  qr_.w=uint8_t(q_.w*scalar_t(127.999)+scalar_t(128.0));
}
//----

template<typename T>
PFC_INLINE void unpack_u1(quat<T> &qr_, const quat_32 &q_)
{
  // unpack quat (components in range [0, 1]) from 32-bit quat
  typedef typename math<T>::scalar_t scalar_t;
  qr_.x=q_.x*scalar_t(1.0/255.0);
  qr_.y=q_.y*scalar_t(1.0/255.0);
  qr_.z=q_.z*scalar_t(1.0/255.0);
  qr_.w=q_.w*scalar_t(1.0/255.0);
}
//----

template<typename T>
PFC_INLINE void unpack_s1(quat<T> &qr_, const quat_32 &q_)
{
  // unpack quat (components in range [-1, 1]) from 32-bit quat
  typedef typename math<T>::scalar_t scalar_t;
  qr_.x=q_.x*scalar_t(2.0/255.0)-scalar_t(1);
  qr_.y=q_.y*scalar_t(2.0/255.0)-scalar_t(1);
  qr_.z=q_.z*scalar_t(2.0/255.0)-scalar_t(1);
  qr_.w=q_.w*scalar_t(2.0/255.0)-scalar_t(1);
}
//----

template<typename T>
PFC_INLINE const vec3<T> &vec(const quat<T> &q_)
{
  // return vector of quat
  return reinterpret_cast<const vec3<T>&>(q_);
}
//----

template<typename T>
PFC_INLINE vec3<T> &vec(quat<T> &q_)
{
  // return vector of quat
  return reinterpret_cast<vec3<T>&>(q_);
}
//----------------------------------------------------------------------------


//============================================================================
// complex
//============================================================================
template<typename T> const complex<T> complex<T>::s_zero(T(0));
template<typename T> const complex<T> complex<T>::s_one(T(1));
template<typename T> const complex<T> complex<T>::s_neg_one(T(-1));
//----------------------------------------------------------------------------

template<typename T>
complex<T>::complex()
{
}
//----

template<typename T>
complex<T>::complex(T s_)
  :real(s_)
  ,imag(s_)
{
  // init complex with real scalar
}
//----

template<typename T>
complex<T>::complex(T real_, T imag_)
  :real(real_)
  ,imag(imag_)
{
  // init complex with real and imaginary scalars
}
//----

template<typename T>
complex<T>::complex(const T *a_)
{
  // init complex with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  real=a_[0];
  imag=a_[1];
}
//----------------------------------------------------------------------------

template<typename T>
const T &complex<T>::operator[](unsigned idx_) const
{
  // return reference to nth component (real=0, imag=1)
  PFC_ASSERT_PEDANTIC(idx_<2);
  return reinterpret_cast<const T*>(this)[idx_];
}
//----

template<typename T>
T &complex<T>::operator[](unsigned idx_)
{
  // return reference to nth component (real=0, imag=1)
  PFC_ASSERT_PEDANTIC(idx_<2);
  return reinterpret_cast<T*>(this)[idx_];
}
//----

template<typename T>
void complex<T>::set(T s_)
{
  // set complex with scalar
  real=s_;
  imag=s_;
}
//----

template<typename T>
void complex<T>::set(T real_, T imag_)
{
  // set complex with real and imaginary scalars
  real=real_;
  imag=imag_;
}
//----

template<typename T>
void complex<T>::set(const complex<T> &c_)
{
  // set complex with complex
  real=c_.real;
  imag=c_.imag;
}
//----

template<typename T>
void complex<T>::set(const T *a_)
{
  // init complex with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  real=a_[0];
  imag=a_[1];
}
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE bool is_zero(const complex<T> &c_)
{
  // test for zero-complex number
  return c_.real==0 && c_.imag==0;
}
//----

template<typename T>
PFC_INLINE bool is_sat(const complex<T> &c_)
{
  // test for saturated complex number
  typedef typename math<T>::scalar_t scalar_t;
  return    c_.real>=0 && c_.real<=scalar_t(1)
         && c_.imag>=0 && c_.imag<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const complex<T> &c_)
{
  // test for signed saturated complex number
  typedef typename math<T>::scalar_t scalar_t;
  return    c_.real>=scalar_t(-1) && c_.real<=scalar_t(1)
         && c_.imag>=scalar_t(-1) && c_.imag<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool operator==(const complex<T> &c0_, const complex<T> &c1_)
{
  // test for equality of complex numbers
  return c0_.real==c1_.real && c0_.imag==c1_.imag;
}
//----

template<typename T>
PFC_INLINE bool operator==(const complex<T> &c_, typename math<T>::scalar_t s_)
{
  // test for equality of complex numbers and scalar
  return c_.real==s_ && c_.imag==s_;
}
//----

template<typename T>
PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const complex<T> &c_)
{
  // test for equality of complex numbers and scalar
  return s_==c_.real && s_==c_.imag;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const complex<T> &c0_, const complex<T> &c1_)
{
  // test for inequality of complex numbers
  return c0_.real!=c1_.real || c0_.imag!=c1_.imag;
}
//----

template<typename T>
PFC_INLINE bool operator!=(const complex<T> &c_, typename math<T>::scalar_t s_)
{
  // test for inequality of complex number and scalar
  return c_.real!=s_ || c_.imag!=s_;
}
//----

template<typename T>
PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const complex<T> &c_)
{
  // test for inequality of complex number and scalar
  return s_!=c_.real || s_!=c_.imag;
}
//----

template<typename T>
PFC_INLINE complex<T> operator<(const complex<T> &c0_, const complex<T> &c1_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c0_.real<c1_.real?scalar_t(1):0, c0_.imag<c1_.imag?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE complex<T> operator<(const complex<T> &c_, typename math<T>::scalar_t s_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real<s_?scalar_t(1):0, c_.imag<s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE complex<T> operator<(typename math<T>::scalar_t s_, const complex<T> &c_)
{
  // component-wise less-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(s_<c_.real?scalar_t(1):0, s_<c_.imag?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE complex<T> operator>(const complex<T> &c0_, const complex<T> &c1_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c0_.real>c1_.real?scalar_t(1):0, c0_.imag>c1_.imag?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE complex<T> operator>(const complex<T> &c_, typename math<T>::scalar_t s_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real>s_?scalar_t(1):0, c_.imag>s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE complex<T> operator>(typename math<T>::scalar_t s_, const complex<T> &c_)
{
  // component-wise greater-than (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(s_>c_.real?scalar_t(1):0, s_>c_.imag?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE complex<T> operator<=(const complex<T> &c0_, const complex<T> &c1_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c0_.real<=c1_.real?scalar_t(1):0, c0_.imag<=c1_.imag?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE complex<T> operator<=(const complex<T> &c_, typename math<T>::scalar_t s_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real<=s_?scalar_t(1):0, c_.imag<=s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE complex<T> operator<=(typename math<T>::scalar_t s_, const complex<T> &c_)
{
  // component-wise less-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(s_<=c_.real?scalar_t(1):0, s_<=c_.imag?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE complex<T> operator>=(const complex<T> &c0_, const complex<T> &c1_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c0_.real>=c1_.real?scalar_t(1):0, c0_.imag>=c1_.imag?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE complex<T> operator>=(const complex<T> &c_, typename math<T>::scalar_t s_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real>=s_?scalar_t(1):0, c_.imag>=s_?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE complex<T> operator>=(typename math<T>::scalar_t s_, const complex<T> &c_)
{
  // component-wise greater-or-equal (false=0, true=1)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(s_>=c_.real?scalar_t(1):0, s_>=c_.imag?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE complex<T> sel_eq(const complex<T> &t0_, const complex<T> &t1_, const complex<T> &c0_, const complex<T> &c1_)
{
  // component-wise equal complex number select (t0_==t1_?c0_:c1_)
  return complex<T>(t0_.real==t1_.real?c0_.real:c1_.real,
                    t0_.imag==t1_.imag?c0_.imag:c1_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> sel_lt(const complex<T> &t0_, const complex<T> &t1_, const complex<T> &c0_, const complex<T> &c1_)
{
  // component-wise less-than complex number select (t0_<t1_?c0_:c1_)
  return complex<T>(t0_.real<t1_.real?c0_.real:c1_.real,
                    t0_.imag<t1_.imag?c0_.imag:c1_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> sel_le(const complex<T> &t0_, const complex<T> &t1_, const complex<T> &c0_, const complex<T> &c1_)
{
  // component-wise less-or-equal complex number select (t0_<=t1_?c0_:c1_)
  return complex<T>(t0_.real<=t1_.real?c0_.real:c1_.real,
                    t0_.imag<=t1_.imag?c0_.imag:c1_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> sel_eqz(const complex<T> &t_, const complex<T> &c0_, const complex<T> &c1_)
{
  // component-wise equal-to-zero complex number select (t_==0?c0_:c1_)
  return complex<T>(t_.real==0?c0_.real:c1_.real,
                    t_.imag==0?c0_.imag:c1_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> sel_ltz(const complex<T> &t_, const complex<T> &c0_, const complex<T> &c1_)
{
  // component-wise less-than-zero complex number select (t_<0?c0_:c1_)
  return complex<T>(t_.real<0?c0_.real:c1_.real,
                    t_.imag<0?c0_.imag:c1_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> sel_lez(const complex<T> &t_, const complex<T> &c0_, const complex<T> &c1_)
{
  // component-wise less-or-equal-to-zero complex number select (t_<=0?c0_:c1_)
  return complex<T>(t_.real<=0?c0_.real:c1_.real,
                    t_.imag<=0?c0_.imag:c1_.imag);
}
//----

template<typename T>
PFC_INLINE void operator+=(complex<T> &cr_, const complex<T> &c_)
{
  // add complex to complex
  cr_.real+=c_.real;
  cr_.imag+=c_.imag;
}
//----

template<typename T>
PFC_INLINE void operator+=(complex<T> &cr_, typename math<T>::scalar_t s_)
{
  // add scalar to each component of the complex
  cr_.real+=s_;
  cr_.imag+=s_;
}
//----

template<typename T>
PFC_INLINE void operator-=(complex<T> &cr_, const complex<T> &c_)
{
  // subtract complex from complex
  cr_.real-=c_.real;
  cr_.imag-=c_.imag;
}
//----

template<typename T>
PFC_INLINE void operator-=(complex<T> &cr_, typename math<T>::scalar_t s_)
{
  // subtract scalar from each component of the complex
  cr_.real-=s_;
  cr_.imag-=s_;
}
//----

template<typename T>
PFC_INLINE void operator*=(complex<T> &cr_, const complex<T> &c_)
{
  // multiply complex by complex
  typename math<T>::scalar_t i=cr_.real*c_.imag+cr_.imag*c_.real;
  cr_.real=cr_.real*c_.real-cr_.imag*c_.imag;
  cr_.imag=i;
}
//----

template<typename T>
PFC_INLINE void operator*=(complex<T> &cr_, typename math<T>::scalar_t s_)
{
  // multiply complex by scalar
  cr_.real*=s_;
  cr_.imag*=s_;
}
//----

template<typename T>
PFC_INLINE void operator/=(complex<T> &cr_, typename math<T>::scalar_t s_)
{
  // divide complex by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  cr_.real*=rs;
  cr_.imag*=rs;
}
//----

template<typename T>
PFC_INLINE complex<T> operator+(const complex<T> &c0_, const complex<T> &c1_)
{
  // add complex to complex
  return complex<T>(c0_.real+c1_.real, c0_.imag+c1_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> operator+(const complex<T> &c_, typename math<T>::scalar_t s_)
{
  // add scalar to each component of the complex
  return complex<T>(c_.real+s_, c_.imag+s_);
}
//----

template<typename T>
PFC_INLINE complex<T> operator+(typename math<T>::scalar_t s_, const complex<T> &c_)
{
  // add each component of the complex to a scalar complex
  return complex<T>(s_+c_.real, s_+c_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> operator-(const complex<T> &c0_, const complex<T> &c1_)
{
  // subtract complex from complex
  return complex<T>(c0_.real-c1_.real, c0_.imag-c1_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> operator-(const complex<T> &c_, typename math<T>::scalar_t s_)
{
  // subtract scalar from each component of the complex
  return complex<T>(c_.real-s_, c_.imag-s_);
}
//----

template<typename T>
PFC_INLINE complex<T> operator-(typename math<T>::scalar_t s_, const complex<T> &c_)
{
  // subtract each component of the complex from a scalar complex
  return complex<T>(s_-c_.real, s_-c_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> operator-(const complex<T> &c_)
{
  // negate complex
  return complex<T>(-c_.real, -c_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> operator*(const complex<T> &c0_, const complex<T> &c1_)
{
  // multiply complex by complex
  return complex<T>(c0_.real*c1_.real-c0_.imag*c1_.imag,
                    c0_.real*c1_.imag+c0_.imag*c1_.real);
}
//----

template<typename T>
PFC_INLINE complex<T> operator*(const complex<T> &c_, typename math<T>::scalar_t s_)
{
  // multiply complex by scalar
  return complex<T>(c_.real*s_, c_.imag*s_);
}
//----

template<typename T>
PFC_INLINE complex<T> operator*(typename math<T>::scalar_t s_, const complex<T> &c_)
{
  // multiply complex by scalar
  return complex<T>(c_.real*s_, c_.imag*s_);
}
//----

template<typename T>
PFC_INLINE complex<T> operator/(const complex<T> &c_, typename math<T>::scalar_t s_)
{
  // divide complex by scalar
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(s_);
  scalar_t rs=scalar_t(1)/s_;
  return complex<T>(c_.real*rs, c_.imag*rs);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t min(const complex<T> &c_)
{
  // minimum component value
  return min(c_.real, c_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> min(const complex<T> &c0_, const complex<T> &c1_)
{
  // component-wise min complex
  return complex<T>(c0_.real<c1_.real?c0_.real:c1_.real,
                    c0_.imag<c1_.imag?c0_.imag:c1_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> min(const complex<T> &c0_, const complex<T> &c1_, const complex<T> &c2_)
{
  // component-wise min complex
  return complex<T>(min(c0_.real, c1_.real, c2_.real),
                    min(c0_.imag, c1_.imag, c2_.imag));
}
//----

template<typename T>
PFC_INLINE complex<T> min(const complex<T> &c0_, const complex<T> &c1_, const complex<T> &c2_, const complex<T> &c3_)
{
  // component-wise min complex
  return complex<T>(min(c0_.real, c1_.real, c2_.real, c3_.real),
                    min(c0_.imag, c1_.imag, c2_.imag, c3_.imag));
}
//----

template<typename T>
PFC_INLINE complex<T> min(const complex<T> &c_, typename math<T>::scalar_t s_)
{
  // component-wise min complex
  return complex<T>(c_.real<s_?c_.real:s_,
                    c_.imag<s_?c_.imag:s_);
}
//----

template<typename T>
PFC_INLINE complex<T> min(typename math<T>::scalar_t s_, const complex<T> &c_)
{
  // component-wise min complex
  return complex<T>(c_.real<s_?c_.real:s_,
                    c_.imag<s_?c_.imag:s_);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t max(const complex<T> &c_)
{
  // maximum component value
  return max(v_.real, c_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> max(const complex<T> &c0_, const complex<T> &c1_)
{
  // component-wise max complex
  return complex<T>(c0_.real>c1_.real?c0_.real:c1_.real,
                    c0_.imag>c1_.imag?c0_.imag:c1_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> max(const complex<T> &c0_, const complex<T> &c1_, const complex<T> &c2_)
{
  // component-wise max complex
  return complex<T>(max(c0_.real, c1_.real, c2_.real),
                    max(c0_.imag, c1_.imag, c2_.imag));
}
//----

template<typename T>
PFC_INLINE complex<T> max(const complex<T> &c0_, const complex<T> &c1_, const complex<T> &c2_, const complex<T> &c3_)
{
  // component-wise max complex
  return complex<T>(max(c0_.real, c1_.real, c2_.real, c3_.real),
                    max(c0_.imag, c1_.imag, c2_.imag, c3_.imag));
}
//----

template<typename T>
PFC_INLINE complex<T> max(const complex<T> &c_, typename math<T>::scalar_t s_)
{
  // component-wise max complex
  return complex<T>(c_.real>s_?c_.real:s_,
                    c_.imag>s_?c_.imag:s_);
}
//----

template<typename T>
PFC_INLINE complex<T> max(typename math<T>::scalar_t s_, const complex<T> &c_)
{
  // component-wise max complex
  return complex<T>(c_.real>s_?c_.real:s_,
                    c_.imag>s_?c_.imag:s_);
}
//----

template<typename T>
PFC_INLINE complex<T> mul(const complex<T> &c0_, const complex<T> &c1_)
{
  // component-wise multiply: c0_*c1
  return complex<T>(c0_.real*c1_.real, c0_.imag*c1_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> madd(const complex<T> &cm0_, const complex<T> &cm1_, const complex<T> &ca_)
{
  // component-wise multiply-add: cm0_*cm1_+ca_
  return complex<T>(cm0_.real*cm1_.real+ca_.real, cm0_.imag*cm1_.imag+ca_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> madd(const complex<T> &cm_, typename math<T>::scalar_t sm_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: cm_*sm_+sa_
  return complex<T>(cm_.real*sm_+sa_, cm_.imag*sm_+sa_);
}
//----

template<typename T>
PFC_INLINE complex<T> madd(const complex<T> &cm0_, const complex<T> &cm1_, typename math<T>::scalar_t sa_)
{
  // component-wise multiply-add: cm0_*cm1_+sa_
  return complex<T>(cm0_.real*cm1_.real+sa_, cm0_.imag*cm1_.imag+sa_);
}
//----

template<typename T>
PFC_INLINE complex<T> madd(const complex<T> &cm_, typename math<T>::scalar_t sm_, const complex<T> &ca_)
{
  // component-wise multiply-add: cm_*sm_+ca_
  return complex<T>(cm_.real*sm_+ca_.real, cm_.imag*sm_+ca_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> rcp(const complex<T> &c_)
{
  // component-wise reciprocal
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(c_.real && c_.imag);
  return complex<T>(scalar_t(1)/c_.real, scalar_t(1)/c_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> rcp_z(const complex<T> &c_)
{
  // component-wise reciprocal (set to 0 for 0 components)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real?scalar_t(1)/c_.real:0, c_.imag?scalar_t(1)/c_.imag:0);
}
//----

template<typename T>
PFC_INLINE complex<T> floor(const complex<T> &c_)
{
  // component-wise floor
  return complex<T>(std::floor(c_.real), std::floor(c_.imag));
}
//----

template<typename T>
PFC_INLINE complex<T> ceil(const complex<T> &c_)
{
  // component-wise ceil
  return complex<T>(std::ceil(c_.real), std::ceil(c_.imag));
}
//----

template<typename T>
PFC_INLINE complex<T> trunc(const complex<T> &c_)
{
  // component-wise truncate
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(scalar_t(int(c_.real)), scalar_t(int(c_.imag)));
}
//----

template<typename T>
PFC_INLINE complex<T> frc(const complex<T> &c_)
{
  // component-wise fractional
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real-scalar_t(int(c_.real)), c_.imag-scalar_t(int(c_.imag)));
}
//----

template<typename T>
PFC_INLINE complex<T> mod(const complex<T> &c_, typename math<T>::scalar_t div_)
{
  // component-wise modulo
  return complex<T>(std::fmod(c_.real, div_), std::fmod(c_.imag, div_));
}
//----

template<typename T>
PFC_INLINE complex<T> cycle(const complex<T> &c_, typename math<T>::scalar_t cycle_)
{
  // component-wise cycle
  return complex<T>(std::fmod(c_.real, cycle_)+(c_.real<0?cycle_:0),
                    std::fmod(c_.imag, cycle_)+(c_.imag<0?cycle_:0));
}
//----

template<typename T>
PFC_INLINE complex<T> cycle1(const complex<T> &c_)
{
  // cycle1
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real-scalar_t(int(c_.real))+(c_.real<0?scalar_t(1):0),
                    c_.imag-scalar_t(int(c_.imag))+(c_.imag<0?scalar_t(1):0));
}
//----

template<typename T>
PFC_INLINE complex<T> sat(const complex<T> &c_)
{
  // component-wise saturate
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real<0?0:c_.real>scalar_t(1)?scalar_t(1):c_.real,
                    c_.imag<0?0:c_.imag>scalar_t(1)?scalar_t(1):c_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> ssat(const complex<T> &c_)
{
  // component-wise signed saturate
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real<scalar_t(-1)?scalar_t(-1):c_.real>scalar_t(1)?scalar_t(1):c_.real,
                    c_.imag<scalar_t(-1)?scalar_t(-1):c_.imag>scalar_t(1)?scalar_t(1):c_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> clamp(const complex<T> &c_, const complex<T> &min_, const complex<T> &max_)
{
  // component-wise clamp (to complex)
  return complex<T>(c_.real<min_.real?min_.real:c_.real>max_.real?max_.real:c_.real,
                    c_.imag<min_.imag?min_.imag:c_.imag>max_.imag?max_.imag:c_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> clamp(const complex<T> &c_, typename math<T>::scalar_t min_, typename math<T>::scalar_t max_)
{
  // component-wise clamp (to scalar)
  return complex<T>(c_.real<min_?min_:c_.real>max_?max_:c_.real,
                    c_.imag<min_?min_:c_.imag>max_?max_:c_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> abs(const complex<T> &c_)
{
  // component-wise absolute
  return complex<T>(std::abs(c_.real), std::abs(c_.imag));
}
//----

template<typename T>
PFC_INLINE complex<T> sgn(const complex<T> &c_)
{
  // component-wise signum (neg=-1, pos=+1, zero=0)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real<0?scalar_t(-1):c_.real>0?scalar_t(1):0, c_.imag<0?scalar_t(-1):c_.imag>0?scalar_t(1):0);
}
//----

template<typename T>
PFC_INLINE complex<T> sgn_zp(const complex<T> &c_)
{
  // component-wise signum (neg=-1, pos&zero=+1)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real<0?scalar_t(-1):scalar_t(1), c_.imag<0?scalar_t(-1):scalar_t(1));
}
//----

template<typename T>
PFC_INLINE complex<T> sqr(const complex<T> &c_)
{
  // component-wise square
  return complex<T>(c_.real*c_.real, c_.imag*c_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> cubic(const complex<T> &c_)
{
  // component-wise cubic
  return complex<T>(c_.real*c_.real*c_.real, c_.imag*c_.imag*c_.imag);
}
//----

template<typename T>
PFC_INLINE complex<T> sqrt(const complex<T> &c_)
{
  // component-wise square root
  PFC_ASSERT_PEDANTIC(c_.real>=0 && c_.imag>=0);
  return complex<T>(std::sqrt(c_.real), std::sqrt(c_.imag));
}
//----

template<typename T>
PFC_INLINE complex<T> sqrt_z(const complex<T> &c_)
{
  // component-wise square root (set to 0 for components less than zero)
  return complex<T>(sqrt_z(c_.real), sqrt_z(c_.imag));
}
//----

template<typename T>
PFC_INLINE complex<T> cbrt(const complex<T> &c_)
{
  // component-wise cubic root
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real<0?-std::pow(-c_.real, scalar_t(1.0/3.0)):std::pow(c_.real, scalar_t(1.0/3.0)),
                    c_.imag<0?-std::pow(-c_.imag, scalar_t(1.0/3.0)):std::pow(c_.imag, scalar_t(1.0/3.0)));
}
//----

template<typename T>
PFC_INLINE complex<T> rsqrt(const complex<T> &c_)
{
  // component-wise reciprocal square root
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(c_.real>0 && c_.imag>0);
  return complex<T>(scalar_t(1)/std::sqrt(c_.real), scalar_t(1)/std::sqrt(c_.imag));
}
//----

template<typename T>
PFC_INLINE complex<T> rsqrt_z(const complex<T> &c_)
{
  // component-wise reciprocal square root (set to 0 for components less than or equal to zero)
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real>0?scalar_t(1)/std::sqrt(c_.real):0,
                    c_.imag>0?scalar_t(1)/std::sqrt(c_.imag):0);
}
//----

template<typename T>
PFC_INLINE complex<T> rcbrt(const complex<T> &c_)
{
  // component-wise cubic root
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real<0?-std::pow(-c_.real, scalar_t(-1.0/3.0)):std::pow(c_.real, scalar_t(-1.0/3.0)),
                    c_.imag<0?-std::pow(-c_.imag, scalar_t(-1.0/3.0)):std::pow(c_.imag, scalar_t(-1.0/3.0)));
}
//----

template<typename T>
PFC_INLINE complex<T> rcbrt_z(const complex<T> &c_)
{
  // component-wise cubic root
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(c_.real?c_.real<0?-std::pow(-c_.real, scalar_t(-1.0/3.0)):std::pow(c_.real, scalar_t(-1.0/3.0)):0,
                    c_.imag?c_.imag<0?-std::pow(-c_.imag, scalar_t(-1.0/3.0)):std::pow(c_.imag, scalar_t(-1.0/3.0)):0);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t norm(const complex<T> &c_)
{
  // norm of the complex (=complex length)
  return std::sqrt(c_.real*c_.real+c_.imag*c_.imag);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm(const complex<T> &c_)
{
  // reciprocal norm of the complex
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=c_.real*c_.real+c_.imag*c_.imag;
  PFC_ASSERT_PEDANTIC(n2);
  return scalar_t(1)/std::sqrt(n2);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm_z(const complex<T> &c_)
{
  // reciprocal norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=c_.real*c_.real+c_.imag*c_.imag;
  return n2>0?scalar_t(1)/std::sqrt(n2):0;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t norm2(const complex<T> &c_)
{
  // squared norm of the complex
  return c_.real*c_.real+c_.imag*c_.imag;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm2(const complex<T> &c_)
{
  // reciprocal squared norm of the complex
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=c_.real*c_.real+c_.imag*c_.imag;
  PFC_ASSERT_PEDANTIC(n2);
  return scalar_t(1)/n2;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t rnorm2_z(const complex<T> &c_)
{
  // reciprocal squared norm of the vector
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t v=c_.real*c_.real+c_.imag*c_.imag;
  return v>0?scalar_t(1)/v:0;
}
//----

template<typename T>
PFC_INLINE complex<T> unit(const complex<T> &c_)
{
  // unit complex of the complex
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n2=c_.real*c_.real+c_.imag*c_.imag;
  PFC_ASSERT_PEDANTIC(n2);
  scalar_t rs=scalar_t(1)/std::sqrt(n2);
  return complex<T>(c_.real*rs, c_.imag*rs);
}
//----

template<typename T>
PFC_INLINE complex<T> unit_z(const complex<T> &c_)
{
  // unit complex of the complex. if |c|=0, return c=[0, 0]
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t rs=c_.real*c_.real+c_.imag*c_.imag;
  if(!rs)
    return complex<T>(0, 0);
  rs=scalar_t(1)/std::sqrt(rs);
  return complex<T>(c_.real*rs, c_.imag*rs);
}
//----

template<typename T>
PFC_INLINE complex<T> conj(const complex<T> &c_)
{
  // conjugate of the complex
  return complex<T>(c_.real, -c_.imag);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t dot(const complex<T> &c0_, const complex<T> &c1_)
{
  // dot-product of complex numbers
  return c0_.real*c1_.real+c0_.imag*c1_.imag;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t dot1(const complex<T> &c_)
{
  // dot-product with [1, 1]
  return c_.real+c_.imag;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t arg(const complex<T> &c_)
{
  // argument of the complex
  return atan2(c_.imag, c_.real);
}
//----

template<typename T>
PFC_INLINE void neg(complex<T> &c_)
{
  // negate the complex
  c_.real=-c_.real;
  c_.imag=-c_.imag;
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_u(complex<T> &cr_, Rng &rng_)
{
  // random unit complex number (even distribution on unit circle)
  sincos(cr_.real, cr_.imag, typename math<T>::scalar_t(rng_.rand_ureal1())*math<T>::two_pi);
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_real1(complex<T> &cr_, Rng &rng_)
{
  // random complex number where each component is in range [-1, 1]
  typedef typename math<T>::scalar_t scalar_t;
  cr_.real=scalar_t(rng_.rand_real1());
  cr_.imag=scalar_t(rng_.rand_real1());
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_ureal1(complex<T> &cr_, Rng &rng_)
{
  // random complex number where each component is in range [0, 1]
  typedef typename math<T>::scalar_t scalar_t;
  cr_.real=scalar_t(rng_.rand_ureal1());
  cr_.imag=scalar_t(rng_.rand_ureal1());
}
//----

template<typename T>
PFC_INLINE complex<T> smoothstep(const complex<T> &c_)
{
  // component-wise smoothstep function
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(c_.real>=0 && c_.real<=scalar_t(1) && c_.imag>=0 && c_.imag<=scalar_t(1));
  return complex<T>(c_.real*c_.real*(scalar_t(3)-scalar_t(2)*c_.real),
                    c_.imag*c_.imag*(scalar_t(3)-scalar_t(2)*c_.imag));
}
//----

template<typename T>
PFC_INLINE complex<T> smootherstep(const complex<T> &c_)
{
  // component-wise smootherstep function
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC(c_.real>=0 && c_.real<=scalar_t(1) && c_.imag>=0 && c_.imag<=scalar_t(1));
  return complex<T>(c_.real*c_.real*c_.real*(c_.real*(c_.real*scalar_t(6)-scalar_t(15))+scalar_t(10)),
                    c_.imag*c_.imag*c_.imag*(c_.imag*(c_.imag*scalar_t(6)-scalar_t(15))+scalar_t(10)));
}
//----

template<typename T>
PFC_INLINE complex<T> lerp(const complex<T> &c0_, const complex<T> &c1_, typename math<T>::scalar_t t_)
{
  // linear complex interpolation. f(t=0)=c0, f(t=1)=c1
  return complex<T>(c0_.real+(c1_.real-c0_.real)*t_, c0_.imag+(c1_.imag-c0_.imag)*t_);
}
//----

template<typename T>
PFC_INLINE complex<T> nlerp(const complex<T> &c0_, const complex<T> &c1_, typename math<T>::scalar_t t_)
{
  // normalized linear complex interpolation. f(t=0)=c0/|c0|, f(t=1)=c1/|c1|
  typedef typename math<T>::scalar_t scalar_t;
  complex<T> c(c0_.real+(c1_.real-c0_.real)*t_, c0_.imag+(c1_.imag-c0_.imag)*t_);
  scalar_t n2=c.real*c.real+c.imag*c.imag;
  PFC_ASSERT_PEDANTIC(n2);
  scalar_t rs=scalar_t(1)/std::sqrt(n2);
  return complex<T>(c.real*rs, c.imag*rs);
}
//----

template<typename T>
PFC_INLINE complex<T> nlerp_z(const complex<T> &c0_, const complex<T> &c1_, typename math<T>::scalar_t t_)
{
  // normalized linear complex interpolation. f(t=0)=c0/|c0|, f(t=1)=c1/|c1|. if interpolated |c|=0, return [0, 0]
  typedef typename math<T>::scalar_t scalar_t;
  complex<T> c(c0_.real+(c1_.real-c0_.real)*t_, c0_.imag+(c1_.imag-c0_.imag)*t_);
  scalar_t rs=c.real*c.real+c.imag*c.imag;
  if(!rs)
    return complex<T>(0, 0);
  rs=scalar_t(1)/std::sqrt(rs);
  return complex<T>(c.real*rs, c.imag*rs);
}
//----

template<typename T, typename U>
PFC_INLINE complex<T> to_complex(const complex<U> &c_)
{
  // convert between complex types
  typedef typename math<T>::scalar_t scalar_t;
  return complex<T>(scalar_t(c_.real), scalar_t(c_.imag));
}
//----

namespace priv
{
  template<unsigned shuffle_, typename T>
  struct shuffle_complex_helper
  {
    static complex<T> shuffle(const complex<T>&) {PFC_CTF_ERROR(T, invalid_complex_component_shuffle);}
  };
  #define PFC_COMPLEX_SHUFFLE(shuffle__, real__, imag__)\
  template<typename T> struct shuffle_complex_helper<shuffle__, T>\
  {\
    static PFC_INLINE complex<T> shuffle(const complex<T> &c_) {return complex<T>(c_.real__, c_.imag__);}\
  };
  PFC_COMPLEX_SHUFFLE(00, real, real);
  PFC_COMPLEX_SHUFFLE(01, real, imag);
  PFC_COMPLEX_SHUFFLE(10, imag, real);
  PFC_COMPLEX_SHUFFLE(11, imag, imag);
  #undef PFC_COMPLEX_SHUFFLE
} // namespace priv
//----

template<unsigned shuffle_, typename T>
PFC_INLINE complex<T> shuffle(const complex<T> &c_)
{
  return priv::shuffle_complex_helper<shuffle_, T>::shuffle(c_);
}
//----------------------------------------------------------------------------
