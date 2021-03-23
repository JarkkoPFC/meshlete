//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_H
#define PFC_CORE_MATH_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core/meta.h"
#include <cmath>
namespace pfc
{

// new
template<typename> struct math;     // math constants
template<typename> struct vec2;     // 2d vector
template<typename> struct vec3;     // 3d vector
template<typename> struct vec4;     // 4d vector
template<typename> struct mat22;    // 2x2 matrix
template<typename> struct mat33;    // 3x3 matrix
template<typename> struct mat44;    // 4x4 matrix
template<typename> struct quat;     // quaternion
template<typename> struct complex;  // complex number
struct vec32_t;
typedef math<float> mathf;
typedef math<double> mathd;
typedef vec2<float> vec2f;
typedef vec2<double> vec2d;
typedef vec2<int> vec2i;
typedef vec2<unsigned> vec2u;
typedef vec2<short> vec2s;
typedef vec3<float> vec3f;
typedef vec3<double> vec3d;
typedef vec3<int> vec3i;
typedef vec3<unsigned> vec3u;
typedef vec3<short> vec3s;
typedef vec3<vec32_t> vec3_32;
typedef vec4<float> vec4f;
typedef vec4<double> vec4d;
typedef vec4<int> vec4i;
typedef vec4<unsigned> vec4u;
typedef vec4<short> vec4s;
typedef vec4<vec32_t> vec4_32;
typedef mat22<float> mat22f;
typedef mat22<double> mat22d;
typedef mat22<int> mat22i;
typedef mat22<unsigned> mat22u;
typedef mat22<short> mat22s;
typedef mat33<float> mat33f;
typedef mat33<double> mat33d;
typedef mat33<int> mat33i;
typedef mat33<unsigned> mat33u;
typedef mat33<short> mat33s;
typedef mat44<float> mat44f;
typedef mat44<double> mat44d;
typedef mat44<int> mat44i;
typedef mat44<unsigned> mat44u;
typedef mat44<short> mat44s;
typedef quat<float> quatf;
typedef quat<double> quatd;
typedef quat<int> quati;
typedef quat<unsigned> quatu;
typedef quat<short> quats;
typedef quat<vec32_t> quat_32;
typedef complex<float> complexf;
typedef complex<double> complexd;
typedef complex<int> complexi;
typedef complex<unsigned> complexu;
typedef complex<short> complexs;
// traits
template<typename> struct is_type_vec {enum {res=false};};
template<typename> struct is_type_mat {enum {res=false};};
template<typename> struct is_type_quat {enum {res=false};};
template<typename> struct is_type_complex {enum {res=false};};
// macro to prefer pfc free math functions in function scope, i.e. use pfc::acos() instead of ::acos() when writing: float a=acos(b);
#define PFC_FUNC_PREFER_MATH_LIB\
  using namespace pfc;\
  using pfc::mul; using pfc::madd; using pfc::rcp; using pfc::rcp_z; using pfc::floor; using pfc::ceil; using pfc::trunc; using pfc::frc; using pfc::mod;\
  using pfc::cycle; using pfc::cycle1; using pfc::sat; using pfc::ssat; using pfc::clamp; using pfc::abs; using pfc::sgn; using pfc::sgn_zp; using pfc::sqr; using pfc::cubic;\
  using pfc::sqrt; using pfc::sqrt_z; using pfc::cbrt; using pfc::rsqrt; using pfc::rsqrt_z; using pfc::rcbrt; using pfc::rcbrt_z; using pfc::norm;\
  using pfc::rnorm; using pfc::rnorm_z; using pfc::rnorm_z; using pfc::norm2; using pfc::rnorm2; using pfc::rnorm2_z; using pfc::norm_l1; using pfc::rnorm_l1;\
  using pfc::rnorm_l1_z; using pfc::exp; using pfc::exp2; using pfc::ln; using pfc::log2; using pfc::log10; using pfc::pow; using pfc::smoothstep; using pfc::smootherstep; using pfc::lerp; using pfc::dot;\
  using pfc::sin; using pfc::cos; using pfc::sincos; using pfc::tan; using pfc::csc; using pfc::sec; using pfc::cot; using pfc::asin; using pfc::acos;\
  using pfc::atan; using pfc::atan2; using pfc::acsc; using pfc::asec; using pfc::acot; using pfc::sinh; using pfc::cosh; using pfc::tanh; using pfc::csch;\
  using pfc::sech; using pfc::coth; using pfc::asinh; using pfc::acosh; using pfc::atanh; using pfc::acsch; using pfc::asech; using pfc::acoth;
// scalar functions
template<typename T> PFC_INLINE T mul(T a_, T b_);             // a_*b_
template<typename T> PFC_INLINE T madd(T a_, T b_, T c_);      // a_*b_+c_
template<typename T> PFC_INLINE T rcp(T);                      // reciprocal: 1/x
template<typename T> PFC_INLINE T rcp_z(T);                    // reciprocal: 1/x, if x=0 returns 0
template<typename T> PFC_INLINE T floor(T v_);                 // greatest integer less than or equal to the value
template<typename T> PFC_INLINE T ceil(T v_);                  // smallest integer greater than or equal to the value
template<typename T> PFC_INLINE T trunc(T v_);                 // truncate decimal part from the value
template<typename T> PFC_INLINE T frc(T v_);                   // fractional part (for negative values returns 1-fractional part)
template<typename T> PFC_INLINE T mod(T v_, T div_);           // remainder of v_/div_
template<typename T> PFC_INLINE T cycle(T v_, T cycle_);       // same as mod() except for negative result returns: cycle_+mod(v_, cycle_)
template<typename T> PFC_INLINE T cycle1(T v_);                // same as frc() but for negative results returns: 1+frc(v_)
template<typename T> PFC_INLINE T sat(T);                      // saturate scalar to range [0, 1]
template<typename T> PFC_INLINE T ssat(T);                     // saturate scalar to range [-1, 1]
template<typename T> PFC_INLINE T clamp(T v_, T min_, T max_); // clamp scalar to range [min, max]
template<typename T> PFC_INLINE T abs(T);                      // absolute: |x|
template<typename T> PFC_INLINE T sgn(T);                      // signum (neg=-1, pos=+1, zero=0)
template<typename T> PFC_INLINE T sgn_zp(T);                   // signum (neg=-1, pos&zero=+1)
template<typename T> PFC_INLINE T sqr(T);                      // square: x*x
template<typename T> PFC_INLINE T cubic(T);                    // cubic: x*x*x
template<typename T> PFC_INLINE T sqrt(T);                     // square root
template<typename T> PFC_INLINE T sqrt_z(T);                   // square root (set to 0 if the value is less than zero)
template<typename T> PFC_INLINE T cbrt(T);                     // cubic root
template<typename T> PFC_INLINE T rsqrt(T);                    // reciprocal square root: 1/sqrt(x)
template<typename T> PFC_INLINE T rsqrt_z(T);                  // reciprocal square root: 1/sqrt(x). set to 0 if the value is less than or equal to zero
template<typename T> PFC_INLINE T rcbrt(T);                    // reciprocal cubic root: 1/cbrt(x)
template<typename T> PFC_INLINE T rcbrt_z(T);                  // reciprocal cubic root: 1/cbrt(x). set to 0 if the value is zero
template<typename T> PFC_INLINE T norm(T);                     // absolute: |x|
template<typename T> PFC_INLINE T rnorm(T);                    // absolute reciprocal: 1/|x|
template<typename T> PFC_INLINE T rnorm_z(T);                  // absolute reciprocal: 1/|x| (if x=0, returns 0)
template<typename T> PFC_INLINE T norm2(T);                    // square: x*x
template<typename T> PFC_INLINE T rnorm2(T);                   // square reciprocal: 1/(x*x)
template<typename T> PFC_INLINE T rnorm2_z(T);                 // square reciprocal: 1/(x*x) (if x=0, returns 0)
template<typename T> PFC_INLINE T norm_l1(T);                  // absolute: |x|
template<typename T> PFC_INLINE T rnorm_l1(T);                 // absolute reciprocal: 1/|x|
template<typename T> PFC_INLINE T rnorm_l1_z(T);               // absolute reciprocal: 1/|x| (if x=0, returns 0)
template<typename T> PFC_INLINE T exp(T);                      // natural exponent: e^x
template<typename T> PFC_INLINE T exp2(T);                     // 2^x
template<typename T> PFC_INLINE T ln(T);                       // natural logarithm
template<typename T> PFC_INLINE T log2(T);                     // base-2 logarithm
template<typename T> PFC_INLINE T log10(T);                    // base-10 logarithm
template<typename T> PFC_INLINE T pow(T, T);                   // power
template<typename T> PFC_INLINE T smoothstep(T t_);            // smoothstep function: t=[0, 1]
template<typename T> PFC_INLINE T smootherstep(T t_);          // smootherstep function: t=[0, 1]
template<typename T> PFC_INLINE T lerp(T a_, T b_, T t_);      // linear interpolation of scalars: f(t=0)=a_, f(t=1)=b_
template<typename T> PFC_INLINE T dot(T x_, T y_);             // x_*y_
PFC_INLINE float32_t u16f_to_fp32(uint16_t u16f_);             // convert unsigned 16-bit float to 32-bit float
PFC_INLINE float32_t s16f_to_fp32(uint16_t s16f_);             // convert signed 16-bit float to 32-bit float
PFC_INLINE uint16_t fp32_to_u16f(float32_t v_);                // convert 32-bit float to unsigned 16-bit float
PFC_INLINE uint16_t fp32_to_s16f(float32_t v_);                // convert 32-bit float to signed 16-bit float
// trigonometric scalar functions
template<typename T> PFC_INLINE T sin(T);                         // sine
template<typename T> PFC_INLINE T cos(T);                         // cosine
template<typename T> PFC_INLINE void sincos(T &sin_, T &cos_, T); // sine & cosine
template<typename T> PFC_INLINE T tan(T);                         // tangent
template<typename T> PFC_INLINE T csc(T);                         // cosecant: 1/sin(x)
template<typename T> PFC_INLINE T sec(T);                         // secant: 1/cos(x)
template<typename T> PFC_INLINE T cot(T);                         // cotangent: 1/tan(x)
template<typename T> PFC_INLINE T asin(T);                        // arcus sine
template<typename T> PFC_INLINE T acos(T);                        // arcus cosine
template<typename T> PFC_INLINE T atan(T);                        // arcus tangent
template<typename T> PFC_INLINE T atan2(T y_, T x_);              // arcus tangent
template<typename T> PFC_INLINE T acsc(T);                        // arcus cosecant
template<typename T> PFC_INLINE T asec(T);                        // arcus secant
template<typename T> PFC_INLINE T acot(T);                        // arcus cotangent
template<typename T> PFC_INLINE T sinh(T);                        // hyperbolic sine
template<typename T> PFC_INLINE T cosh(T);                        // hyperbolic cosine
template<typename T> PFC_INLINE T tanh(T);                        // hyperbolic tangent
template<typename T> PFC_INLINE T csch(T);                        // hyperbolic cosecant
template<typename T> PFC_INLINE T sech(T);                        // hyperbolic secant
template<typename T> PFC_INLINE T coth(T);                        // hyperbolic cotangent
template<typename T> PFC_INLINE T asinh(T);                       // arcus hyperbolic sine
template<typename T> PFC_INLINE T acosh(T);                       // arcus hyperbolic cosine
template<typename T> PFC_INLINE T atanh(T);                       // arcus hyperbolic tangent
template<typename T> PFC_INLINE T acsch(T);                       // arcus hyperbolic cosecant
template<typename T> PFC_INLINE T asech(T);                       // arcus hyperbolic secant
template<typename T> PFC_INLINE T acoth(T);                       // arcus hyperbolic cotangent
// 2d vector ops
template<typename T> PFC_INLINE bool is_zero(const vec2<T>&);                                     // test for zero-vector, i.e. all components equal zero (exact)
template<typename T> PFC_INLINE bool is_sat(const vec2<T>&);                                      // test for saturated vector, i.e. all components are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const vec2<T>&);                                     // test for signed saturated vector, i.e. all components are in range [-1, 1]
template<typename T> PFC_INLINE bool operator==(const vec2<T>&, const vec2<T>&);                  // test for equality of vectors, i.e. all components of the vectors are equal (exact)
template<typename T> PFC_INLINE bool operator==(const vec2<T>&, typename math<T>::scalar_t);      // test for equality of vector and scalar, i.e. all components of the vector equals the scalar (exact)
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t, const vec2<T>&);      // test for equality of vector and scalar, i.e. all components of the vector equals the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(const vec2<T>&, const vec2<T>&);                  // test for inequality of vectors, i.e. any of the components of the vectors are unequal (exact)
template<typename T> PFC_INLINE bool operator!=(const vec2<T>&, typename math<T>::scalar_t);      // test for inequality of vector and scalar, i.e. any of the components of the vector is unequal to the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t, const vec2<T>&);      // test for inequality of vector and scalar, i.e. any of the components of the vector is unequal to the scalar (exact)
template<typename T> PFC_INLINE vec2<T> operator<(const vec2<T>&, const vec2<T>&);                // component-wise vector less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec2<T> operator<(const vec2<T>&, typename math<T>::scalar_t);    // component-wise vector less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec2<T> operator<(typename math<T>::scalar_t, const vec2<T>&);    // component-wise vector less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec2<T> operator>(const vec2<T>&, const vec2<T>&);                // component-wise vector greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec2<T> operator>(const vec2<T>&, typename math<T>::scalar_t);    // component-wise vector greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec2<T> operator>(typename math<T>::scalar_t, const vec2<T>&);    // component-wise vector greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec2<T> operator<=(const vec2<T>&, const vec2<T>&);               // component-wise vector less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec2<T> operator<=(const vec2<T>&, typename math<T>::scalar_t);   // component-wise vector less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec2<T> operator<=(typename math<T>::scalar_t, const vec2<T>&);   // component-wise vector less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec2<T> operator>=(const vec2<T>&, const vec2<T>&);               // component-wise vector greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec2<T> operator>=(const vec2<T>&, typename math<T>::scalar_t);   // component-wise vector greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec2<T> operator>=(typename math<T>::scalar_t, const vec2<T>&);   // component-wise vector greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec2<T> sel_eq(const vec2<T> &t0_, const vec2<T> &t1_,            // component-wise equal vector select (t0_==t1_?v0_:v1_)
                                               const vec2<T> &v0_, const vec2<T> &v1_);
template<typename T> PFC_INLINE vec2<T> sel_lt(const vec2<T> &t0_, const vec2<T> &t1_,            // component-wise less-than vector select (t0_<t1_?v0_:v1_)
                                               const vec2<T> &v0_, const vec2<T> &v1_);
template<typename T> PFC_INLINE vec2<T> sel_le(const vec2<T> &t0_, const vec2<T> &t1_,            // component-wise less-or-equal vector select (t0_<=t1_?v0_:v1_)
                                               const vec2<T> &v0_, const vec2<T> &v1_);
template<typename T> PFC_INLINE vec2<T> sel_eqz(const vec2<T> &t_,                                // component-wise equal-to-zero vector select (t_==0?v0_:v1_)
                                                const vec2<T> &v0_, const vec2<T> &v1_);
template<typename T> PFC_INLINE vec2<T> sel_ltz(const vec2<T> &t_,                                // component-wise less-than-zero vector select (t_<0?v0_:v1_)
                                                const vec2<T> &v0_, const vec2<T> &v1_);
template<typename T> PFC_INLINE vec2<T> sel_lez(const vec2<T> &t_,                                // component-wise less-or-equal-to-zero vector select (t_<=0?v0_:v1_)
                                                const vec2<T> &v0_, const vec2<T> &v1_);
template<typename T> PFC_INLINE void operator+=(vec2<T>&, const vec2<T>&);                        // add vector to vector
template<typename T> PFC_INLINE void operator+=(vec2<T>&, typename math<T>::scalar_t);            // add scalar to each component of the vector
template<typename T> PFC_INLINE void operator-=(vec2<T>&, const vec2<T>&);                        // subtract vector from vector
template<typename T> PFC_INLINE void operator-=(vec2<T>&, typename math<T>::scalar_t);            // subtract scalar from each component of the vector
template<typename T> PFC_INLINE void operator*=(vec2<T>&, const vec2<T>&);                        // component-wise vector by vector multiplication
template<typename T> PFC_INLINE void operator*=(vec2<T>&, typename math<T>::scalar_t);            // vector by scalar multiplication
template<typename T> PFC_INLINE void operator*=(vec2<T>&, const mat22<T>&);                       // vector by matrix multiplication
template<typename T> PFC_INLINE void operator/=(vec2<T>&, const vec2<T>&);                        // component-wise vector by vector division
template<typename T> PFC_INLINE void operator/=(vec2<T>&, typename math<T>::scalar_t);            // vector by scalar division
template<typename T> PFC_INLINE vec2<T> operator+(const vec2<T>&, const vec2<T>&);                // add vector to vector
template<typename T> PFC_INLINE vec2<T> operator+(const vec2<T>&, typename math<T>::scalar_t);    // add scalar to each component of the vector
template<typename T> PFC_INLINE vec2<T> operator+(typename math<T>::scalar_t, const vec2<T>&);    // add each component of the vector to a scalar vector
template<typename T> PFC_INLINE vec2<T> operator-(const vec2<T>&, const vec2<T>&);                // subtract vector from vector
template<typename T> PFC_INLINE vec2<T> operator-(const vec2<T>&, typename math<T>::scalar_t);    // subtract scalar from each component of the vector
template<typename T> PFC_INLINE vec2<T> operator-(typename math<T>::scalar_t, const vec2<T>&);    // subtract each component of the vector from a scalar vector
template<typename T> PFC_INLINE vec2<T> operator-(const vec2<T>&);                                // negate the vector
template<typename T> PFC_INLINE vec2<T> operator*(const vec2<T>&, const vec2<T>&);                // component-wise vector by vector multiplication
template<typename T> PFC_INLINE vec2<T> operator*(const vec2<T>&, typename math<T>::scalar_t);    // vector by scalar multiplication
template<typename T> PFC_INLINE vec2<T> operator*(typename math<T>::scalar_t, const vec2<T>&);    // vector by scalar multiplication
template<typename T> PFC_INLINE vec2<T> operator*(const vec2<T>&, const mat22<T>&);               // vector by matrix multiplication
template<typename T> PFC_INLINE vec2<T> operator*(const mat22<T>&, const vec2<T>&);               // matrix by transposed vector multiplication
template<typename T> PFC_INLINE vec2<T> operator/(const vec2<T>&, const vec2<T>&);                // component-wise vector by vector division
template<typename T> PFC_INLINE vec2<T> operator/(const vec2<T>&, typename math<T>::scalar_t);    // vector by scalar division
template<typename T> PFC_INLINE typename math<T>::scalar_t min(const vec2<T>&);                   // minimum component value
template<typename T> PFC_INLINE vec2<T> min(const vec2<T>&, const vec2<T>&);                      // component-wise minimum of the vectors
template<typename T> PFC_INLINE vec2<T> min(const vec2<T>&, const vec2<T>&, const vec2<T>&);
template<typename T> PFC_INLINE vec2<T> min(const vec2<T>&, const vec2<T>&, const vec2<T>&, const vec2<T>&);
template<typename T> PFC_INLINE vec2<T> min(const vec2<T>&, typename math<T>::scalar_t);          // component-wise minimum of the vector and scalar
template<typename T> PFC_INLINE vec2<T> min(typename math<T>::scalar_t, const vec2<T>&);          // component-wise minimum of the vector and scalar
template<typename T> PFC_INLINE typename math<T>::scalar_t max(const vec2<T>&);                   // maximum component value
template<typename T> PFC_INLINE vec2<T> max(const vec2<T>&, const vec2<T>&);                      // component-wise maximum of the vectors
template<typename T> PFC_INLINE vec2<T> max(const vec2<T>&, const vec2<T>&, const vec2<T>&);
template<typename T> PFC_INLINE vec2<T> max(const vec2<T>&, const vec2<T>&, const vec2<T>&, const vec2<T>&);
template<typename T> PFC_INLINE vec2<T> max(const vec2<T>&, typename math<T>::scalar_t);          // component-wise maximum of the vector and scalar
template<typename T> PFC_INLINE vec2<T> max(typename math<T>::scalar_t, const vec2<T>&);          // component-wise maximum of the vector and scalar
template<typename T> PFC_INLINE vec2<T> mul(const vec2<T> &v0_, const vec2<T> &v1_);              // component-wise multiply: v0_*v1_
template<typename T> PFC_INLINE vec2<T> madd(const vec2<T> &v0_,                                  // component-wise multiply-add: v0_*v1+v2_
                                             const vec2<T> &v1_,
                                             const vec2<T> &v2_);
template<typename T> PFC_INLINE vec2<T> madd(const vec2<T> &v_,                                   // vector-scalar-scalar multiply-add: v_*mul_+add_
                                             typename math<T>::scalar_t mul_,
                                             typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE vec2<T> madd(const vec2<T> &v_,                                   // vector-vector-scalar multiply-add: v_*mul_+add_
                                             const vec2<T> &mul_,
                                             typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE vec2<T> madd(const vec2<T> &v_,                                   // vector-scalar-vector multiply-add: v_*mul_+add_
                                             typename math<T>::scalar_t mul_,
                                             const vec2<T> &add_);
template<typename T> PFC_INLINE vec2<T> rcp(const vec2<T>&);                                      // component-wise vector reciprocal
template<typename T> PFC_INLINE vec2<T> rcp_z(const vec2<T>&);                                    // component-wise vector reciprocal (set 0 for 0 components)
template<typename T> PFC_INLINE vec2<T> floor(const vec2<T>&);                                    // component-wise greatest integer less than or equal to the value
template<typename T> PFC_INLINE vec2<T> ceil(const vec2<T>&);                                     // component-wise smallest integer greater than or equal to the value
template<typename T> PFC_INLINE vec2<T> trunc(const vec2<T>&);                                    // component-wise truncate decimal part from the value
template<typename T> PFC_INLINE vec2<T> frc(const vec2<T>&);                                      // component-wise fractional part (for negative values returns 1-fractional part)
template<typename T> PFC_INLINE vec2<T> mod(const vec2<T>&, typename math<T>::scalar_t div_);     // component-wise modulo
template<typename T> PFC_INLINE vec2<T> cycle(const vec2<T>&, typename math<T>::scalar_t cycle_); // component-wise cycle
template<typename T> PFC_INLINE vec2<T> cycle1(const vec2<T>&);                                   // component-wise cycle1
template<typename T> PFC_INLINE vec2<T> sat(const vec2<T>&);                                      // component-wise vector saturate
template<typename T> PFC_INLINE vec2<T> ssat(const vec2<T>&);                                     // component-wise vector signed saturate
template<typename T> PFC_INLINE vec2<T> clamp(const vec2<T>&,                                     // component-wise clamp of the vector
                                              const vec2<T> &min_,
                                              const vec2<T> &max_);
template<typename T> PFC_INLINE vec2<T> clamp(const vec2<T>&,                                     // component-wise clamp of the vector with scalars
                                              typename math<T>::scalar_t min_,
                                              typename math<T>::scalar_t max_);
template<typename T> PFC_INLINE vec2<T> abs(const vec2<T>&);                                      // component-wise vector absolute
template<typename T> PFC_INLINE vec2<T> sgn(const vec2<T>&);                                      // component-wise signum (neg=-1, pos=+1, zero=0)
template<typename T> PFC_INLINE vec2<T> sgn_zp(const vec2<T>&);                                   // component-wise signum (neg=-1, pos&zero=+1)
template<typename T> PFC_INLINE vec2<T> sqr(const vec2<T>&);                                      // component-wise square: x*x
template<typename T> PFC_INLINE vec2<T> cubic(const vec2<T>&);                                    // component-wise cubic: x*x*x
template<typename T> PFC_INLINE vec2<T> sqrt(const vec2<T>&);                                     // component-wise square root
template<typename T> PFC_INLINE vec2<T> sqrt_z(const vec2<T>&);                                   // component-wise square root (set 0 for components less than zero)
template<typename T> PFC_INLINE vec2<T> cbrt(const vec2<T>&);                                     // component-wise cubic root
template<typename T> PFC_INLINE vec2<T> rsqrt(const vec2<T>&);                                    // component-wise vector reciprocal square root
template<typename T> PFC_INLINE vec2<T> rsqrt_z(const vec2<T>&);                                  // component-wise vector reciprocal square root (set 0 for components less than or equal to zero)
template<typename T> PFC_INLINE vec2<T> rcbrt(const vec2<T>&);                                    // component-wise reciprocal cubic root
template<typename T> PFC_INLINE vec2<T> rcbrt_z(const vec2<T>&);                                  // component-wise reciprocal cubic root (set 0 for components that are 0)
template<typename T> PFC_INLINE typename math<T>::scalar_t norm(const vec2<T>&);                  // vector norm (length): |v|
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm(const vec2<T>&);                 // reciprocal of the vector norm: 1/|v|
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_z(const vec2<T>&);               // reciprocal of the vector norm: 1/|v| (if |v|=0, return 0)
template<typename T> PFC_INLINE typename math<T>::scalar_t norm2(const vec2<T>&);                 // squared vector norm: |v|^2
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2(const vec2<T>&);                // reciprocal of the squared vector norm: 1/|v|^2
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2_z(const vec2<T>&);              // reciprocal of the squared vector norm: 1/|v|^2 (if |v|=0, return 0)
template<typename T> PFC_INLINE typename math<T>::scalar_t norm_l1(const vec2<T>&);               // vector L1-norm (Manhattan norm)
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1(const vec2<T>&);              // reciprocal of the vector L1-norm
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const vec2<T>&);            // reciprocal of the vector L1-norm (if |v|=0, return 0)
template<typename T> PFC_INLINE vec2<T> exp(const vec2<T>&);                                      // component-wise natural exponent: e^x
template<typename T> PFC_INLINE vec2<T> exp2(const vec2<T>&);                                     // component-wise 2^x
template<typename T> PFC_INLINE vec2<T> ln(const vec2<T>&);                                       // component-wise natural logarithm
template<typename T> PFC_INLINE vec2<T> log2(const vec2<T>&);                                     // component-wise base-2 logarithm
template<typename T> PFC_INLINE vec2<T> log10(const vec2<T>&);                                    // component-wise base-10 logarithm
template<typename T> PFC_INLINE vec2<T> pow(const vec2<T>&, typename math<T>::scalar_t);          // component-wise power
template<typename T> PFC_INLINE vec2<T> unit(const vec2<T>&);                                     // unit vector of the vector: v/|v|
template<typename T> PFC_INLINE vec2<T> unit_z(const vec2<T>&);                                   // unit vector of the vector (if |v|=0, return v=[0, 0])
template<typename T> PFC_INLINE typename math<T>::scalar_t cross(const vec2<T>&, const vec2<T>&); // 2d vector cross-product
template<typename T> PFC_INLINE typename math<T>::scalar_t dot(const vec2<T>&, const vec2<T>&);   // vector dot-product
template<typename T> PFC_INLINE typename math<T>::scalar_t dot1(const vec2<T>&);                  // vector dot-product with vector [1, 1] (component sum)
template<typename T> PFC_INLINE void neg(vec2<T>&);                                               // negate the vector
template<typename T, class Rng> PFC_INLINE void rand_u(vec2<T>&, Rng&);                           // random unit vector
template<typename T, class Rng> PFC_INLINE void rand_real1(vec2<T>&, Rng&);                       // random vector where each component is in range [-1, 1]
template<typename T, class Rng> PFC_INLINE void rand_ureal1(vec2<T>&, Rng&);                      // random vector where each component is in range [0, 1]
template<typename T> PFC_INLINE vec2<T> smoothstep(const vec2<T>&);                               // component-wise smoothstep function
template<typename T> PFC_INLINE vec2<T> smootherstep(const vec2<T>&);                             // component-wise smootherstep function
template<typename T> PFC_INLINE vec2<T> lerp(const vec2<T> &v0_,                                  // linear interpolation of vectors: f(t=0)=v0, f(t=1)=v1
                                             const vec2<T> &v1_,
                                             typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE vec2<T> reflect(const vec2<T> &v_, const vec2<T> &n_);            // reflect vector about normal
template<typename T> PFC_INLINE vec2<T> reflect_u(const vec2<T> &v_, const vec2<T> &n_);          // reflect vector about unit normal
template<typename T> PFC_INLINE typename math<T>::scalar_t perspective_project(const vec2<T>&);   // perspective project vector (divide by last component)
template<typename T, typename U> PFC_INLINE vec2<T> to_vec2(const vec2<U>&);                      // convert between vec2 types
template<unsigned shuffle_, typename T> PFC_INLINE vec2<T> shuffle(const vec2<T>&);               // shuffle vector components (e.g. shuffle<11>(v_) == vec2f(v_.y, v_.y))
// 3d vector ops
template<typename T> PFC_INLINE bool is_zero(const vec3<T>&);                                     // test for zero-vector, i.e. all components equal zero (exact)
template<typename T> PFC_INLINE bool is_sat(const vec3<T>&);                                      // test for saturated vector, i.e. all components are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const vec3<T>&);                                     // test for signed saturated vector, i.e. all components are in range [-1, 1]
template<typename T> PFC_INLINE bool operator==(const vec3<T>&, const vec3<T>&);                  // test for equality of vectors, i.e. all components of the vectors are equal (exact)
template<typename T> PFC_INLINE bool operator==(const vec3<T>&, typename math<T>::scalar_t);      // test for equality of vector and scalar, i.e. all components of the vector equals the scalar (exact)
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t, const vec3<T>&);      // test for equality of vector and scalar, i.e. all components of the vector equals the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(const vec3<T>&, const vec3<T>&);                  // test for inequality of vectors, i.e. any of the components of the vectors are unequal (exact)
template<typename T> PFC_INLINE bool operator!=(const vec3<T>&, typename math<T>::scalar_t);      // test for inequality of vector and scalar, i.e. any of the components of the vector is unequal to the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t, const vec3<T>&);      // test for inequality of vector and scalar, i.e. any of the components of the vector is unequal to the scalar (exact)
template<typename T> PFC_INLINE vec3<T> operator<(const vec3<T>&, const vec3<T>&);                // component-wise vector less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec3<T> operator<(const vec3<T>&, typename math<T>::scalar_t);    // component-wise vector less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec3<T> operator<(typename math<T>::scalar_t, const vec3<T>&);    // component-wise vector less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec3<T> operator>(const vec3<T>&, const vec3<T>&);                // component-wise vector greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec3<T> operator>(const vec3<T>&, typename math<T>::scalar_t);    // component-wise vector greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec3<T> operator>(typename math<T>::scalar_t, const vec3<T>&);    // component-wise vector greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec3<T> operator<=(const vec3<T>&, const vec3<T>&);               // component-wise vector less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec3<T> operator<=(const vec3<T>&, typename math<T>::scalar_t);   // component-wise vector less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec3<T> operator<=(typename math<T>::scalar_t, const vec3<T>&);   // component-wise vector less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec3<T> operator>=(const vec3<T>&, const vec3<T>&);               // component-wise vector greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec3<T> operator>=(const vec3<T>&, typename math<T>::scalar_t);   // component-wise vector greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec3<T> operator>=(typename math<T>::scalar_t, const vec3<T>&);   // component-wise vector greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec3<T> sel_eq(const vec3<T> &t0_, const vec3<T> &t1_,            // component-wise equal vector select (t0_==t1_?v0_:v1_)
                                               const vec3<T> &v0_, const vec3<T> &v1_);
template<typename T> PFC_INLINE vec3<T> sel_lt(const vec3<T> &t0_, const vec3<T> &t1_,            // component-wise less-than vector select (t0_<t1_?v0_:v1_)
                                               const vec3<T> &v0_, const vec3<T> &v1_);
template<typename T> PFC_INLINE vec3<T> sel_le(const vec3<T> &t0_, const vec3<T> &t1_,            // component-wise less-or-equal vector select (t0_<=t1_?v0_:v1_)
                                               const vec3<T> &v0_, const vec3<T> &v1_);
template<typename T> PFC_INLINE vec3<T> sel_eqz(const vec3<T> &t_,                                // component-wise equal-to-zero vector select (t_==0?v0_:v1_)
                                                const vec3<T> &v0_, const vec3<T> &v1_);
template<typename T> PFC_INLINE vec3<T> sel_ltz(const vec3<T> &t_,                                // component-wise less-than-zero vector select (t_<0?v0_:v1_)
                                                const vec3<T> &v0_, const vec3<T> &v1_);
template<typename T> PFC_INLINE vec3<T> sel_lez(const vec3<T> &t_,                                // component-wise less-or-equal-to-zero vector select (t_<=0?v0_:v1_)
                                                const vec3<T> &v0_, const vec3<T> &v1_);
template<typename T> PFC_INLINE void operator+=(vec3<T>&, const vec3<T>&);                        // add vector to vector
template<typename T> PFC_INLINE void operator+=(vec3<T>&, typename math<T>::scalar_t);            // add scalar to each component of the vector
template<typename T> PFC_INLINE void operator-=(vec3<T>&, const vec3<T>&);                        // subtract vector from vector
template<typename T> PFC_INLINE void operator-=(vec3<T>&, typename math<T>::scalar_t);            // subtract scalar from each component of the vector
template<typename T> PFC_INLINE void operator*=(vec3<T>&, const vec3<T>&);                        // component-wise vector by vector multiplication
template<typename T> PFC_INLINE void operator*=(vec3<T>&, typename math<T>::scalar_t);            // vector by scalar multiplication
template<typename T> PFC_INLINE void operator*=(vec3<T>&, const mat33<T>&);                       // vector by matrix multiplication
template<typename T> PFC_INLINE void operator*=(vec3<T>&, const mat44<T>&);                       // vector by matrix multiplication (assume vector w=1)
template<typename T> PFC_INLINE void operator*=(vec3<T>&, const quat<T>&);                        // vector by quaternion multiplication
template<typename T> PFC_INLINE void operator/=(vec3<T>&, const vec3<T>&);                        // component-wise vector by vector division
template<typename T> PFC_INLINE void operator/=(vec3<T>&, typename math<T>::scalar_t);            // vector by scalar division
template<typename T> PFC_INLINE vec3<T> operator+(const vec3<T>&, const vec3<T>&);                // add vector to vector
template<typename T> PFC_INLINE vec3<T> operator+(const vec3<T>&, typename math<T>::scalar_t);    // add scalar to each component of the vector
template<typename T> PFC_INLINE vec3<T> operator+(typename math<T>::scalar_t, const vec3<T>&);    // add each component of the vector to a scalar vector
template<typename T> PFC_INLINE vec3<T> operator-(const vec3<T>&, const vec3<T>&);                // subtract vector from vector
template<typename T> PFC_INLINE vec3<T> operator-(const vec3<T>&, typename math<T>::scalar_t);    // subtract scalar from each component of the vector
template<typename T> PFC_INLINE vec3<T> operator-(typename math<T>::scalar_t, const vec3<T>&);    // subtract each component of the vector from a scalar vector
template<typename T> PFC_INLINE vec3<T> operator-(const vec3<T>&);                                // negate the vector
template<typename T> PFC_INLINE vec3<T> operator*(const vec3<T>&, const vec3<T>&);                // component-wise vector by vector multiplication
template<typename T> PFC_INLINE vec3<T> operator*(const vec3<T>&, typename math<T>::scalar_t);    // vector by scalar multiplication
template<typename T> PFC_INLINE vec3<T> operator*(typename math<T>::scalar_t, const vec3<T>&);    // vector by scalar multiplication
template<typename T> PFC_INLINE vec3<T> operator*(const vec3<T>&, const mat33<T>&);               // vector by matrix multiplication
template<typename T> PFC_INLINE vec3<T> operator*(const mat33<T>&, const vec3<T>&);               // matrix by transposed vector multiplication
template<typename T> PFC_INLINE vec3<T> operator*(const vec3<T>&, const mat44<T>&);               // vector by matrix multiplication (assume vector w=1)
template<typename T> PFC_INLINE vec3<T> operator*(const mat44<T>&, const vec3<T>&);               // matrix by transposed vector multiplication (assume vector w=1)
template<typename T> PFC_INLINE vec3<T> operator*(const vec3<T>&, const quat<T>&);                // vector by quaternion multiplication
template<typename T> PFC_INLINE vec3<T> operator/(const vec3<T>&, const vec3<T>&);                // component-wise vector by vector division
template<typename T> PFC_INLINE vec3<T> operator/(const vec3<T>&, typename math<T>::scalar_t);    // vector by scalar division
template<typename T> PFC_INLINE typename math<T>::scalar_t min(const vec3<T>&);                   // minimum component value
template<typename T> PFC_INLINE vec3<T> min(const vec3<T>&, const vec3<T>&);                      // component-wise minimum of the vectors
template<typename T> PFC_INLINE vec3<T> min(const vec3<T>&, const vec3<T>&, const vec3<T>&);
template<typename T> PFC_INLINE vec3<T> min(const vec3<T>&, const vec3<T>&, const vec3<T>&, const vec3<T>&);
template<typename T> PFC_INLINE vec3<T> min(const vec3<T>&, typename math<T>::scalar_t);          // component-wise minimum of the vector and scalar
template<typename T> PFC_INLINE vec3<T> min(typename math<T>::scalar_t, const vec3<T>&);          // component-wise minimum of the vector and scalar
template<typename T> PFC_INLINE typename math<T>::scalar_t max(const vec3<T>&);                   // maximum component value
template<typename T> PFC_INLINE vec3<T> max(const vec3<T>&, const vec3<T>&);                      // component-wise maximum of the vectors
template<typename T> PFC_INLINE vec3<T> max(const vec3<T>&, const vec3<T>&, const vec3<T>&);
template<typename T> PFC_INLINE vec3<T> max(const vec3<T>&, const vec3<T>&, const vec3<T>&, const vec3<T>&);
template<typename T> PFC_INLINE vec3<T> max(const vec3<T>&, typename math<T>::scalar_t);          // component-wise maximum of the vector and scalar
template<typename T> PFC_INLINE vec3<T> max(typename math<T>::scalar_t, const vec3<T>&);          // component-wise maximum of the vector and scalar
template<typename T> PFC_INLINE vec3<T> mul(const vec3<T> &v0_, const vec3<T> &v1_);              // component-wise vector multiply: v0_*v1_
template<typename T> PFC_INLINE vec3<T> madd(const vec3<T> &v0_,                                  // component-wise multiply-add: v0_*v1+v2_
                                             const vec3<T> &v1_,
                                             const vec3<T> &v2_);
template<typename T> PFC_INLINE vec3<T> madd(const vec3<T> &v_,                                   // vector-scalar-scalar multiply-add: v_*mul_+add_
                                             typename math<T>::scalar_t mul_,
                                             typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE vec3<T> madd(const vec3<T> &v_,                                   // vector-vector-scalar multiply-add: v_*mul_+add_
                                             const vec3<T> &mul_,
                                             typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE vec3<T> madd(const vec3<T> &v_,                                   // vector-scalar-vector multiply-add: v_*mul_+add_
                                             typename math<T>::scalar_t mul_,
                                             const vec3<T> &add_);
template<typename T> PFC_INLINE vec3<T> rcp(const vec3<T>&);                                      // component-wise vector reciprocal
template<typename T> PFC_INLINE vec3<T> rcp_z(const vec3<T>&);                                    // component-wise vector reciprocal (set 0 for 0 components)
template<typename T> PFC_INLINE vec3<T> floor(const vec3<T>&);                                    // component-wise greatest integer less than or equal to the value
template<typename T> PFC_INLINE vec3<T> ceil(const vec3<T>&);                                     // component-wise smallest integer greater than or equal to the value
template<typename T> PFC_INLINE vec3<T> trunc(const vec3<T>&);                                    // component-wise truncate decimal part from the value
template<typename T> PFC_INLINE vec3<T> frc(const vec3<T>&);                                      // component-wise fractional part (for negative values returns 1-fractional part)
template<typename T> PFC_INLINE vec3<T> mod(const vec3<T>&, typename math<T>::scalar_t div_);     // component-wise modulo
template<typename T> PFC_INLINE vec3<T> cycle(const vec3<T>&, typename math<T>::scalar_t cycle_); // component-wise cycle
template<typename T> PFC_INLINE vec3<T> cycle1(const vec3<T>&);                                   // component-wise cycle1
template<typename T> PFC_INLINE vec3<T> sat(const vec3<T>&);                                      // component-wise vector saturate
template<typename T> PFC_INLINE vec3<T> ssat(const vec3<T>&);                                     // component-wise vector signed saturate
template<typename T> PFC_INLINE vec3<T> clamp(const vec3<T>&,                                     // component-wise clamp of the vector
                                              const vec3<T> &min_,
                                              const vec3<T> &max_);
template<typename T> PFC_INLINE vec3<T> clamp(const vec3<T>&,                                     // component-wise clamp of the vector with scalars
                                              typename math<T>::scalar_t min_,
                                              typename math<T>::scalar_t max_);
template<typename T> PFC_INLINE vec3<T> abs(const vec3<T>&);                                      // component-wise vector absolute
template<typename T> PFC_INLINE vec3<T> sgn(const vec3<T>&);                                      // component-wise signum (neg=-1, pos=+1, zero=0)
template<typename T> PFC_INLINE vec3<T> sgn_zp(const vec3<T>&);                                   // component-wise signum (neg=-1, pos&zero=+1)
template<typename T> PFC_INLINE vec3<T> sqr(const vec3<T>&);                                      // component-wise square: x*x
template<typename T> PFC_INLINE vec3<T> cubic(const vec3<T>&);                                    // component-wise cubic: x*x*x
template<typename T> PFC_INLINE vec3<T> sqrt(const vec3<T>&);                                     // component-wise vector square root
template<typename T> PFC_INLINE vec3<T> sqrt_z(const vec3<T>&);                                   // component-wise vector square root (set 0 for components less than zero)
template<typename T> PFC_INLINE vec2<T> cbrt(const vec2<T>&);                                     // component-wise cubic root
template<typename T> PFC_INLINE vec3<T> rsqrt(const vec3<T>&);                                    // component-wise vector reciprocal square root
template<typename T> PFC_INLINE vec3<T> rsqrt_z(const vec3<T>&);                                  // component-wise vector reciprocal square root (set 0 for components less than or equal to zero)
template<typename T> PFC_INLINE vec3<T> rcbrt(const vec3<T>&);                                    // component-wise reciprocal cubic root
template<typename T> PFC_INLINE vec3<T> rcbrt_z(const vec3<T>&);                                  // component-wise reciprocal cubic root (set 0 for components that are 0)
template<typename T> PFC_INLINE typename math<T>::scalar_t norm(const vec3<T>&);                  // vector norm (length): |v|
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm(const vec3<T>&);                 // reciprocal of the vector norm: 1/|v|
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_z(const vec3<T>&);               // reciprocal of the vector norm: 1/|v| (return 0, if |v|=0)
template<typename T> PFC_INLINE typename math<T>::scalar_t norm2(const vec3<T>&);                 // squared vector norm: |v|^2
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2(const vec3<T>&);                // reciprocal of the squared vector norm: 1/|v|^2
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2_z(const vec3<T>&);              // reciprocal of the squared vector norm: 1/|v|^2 (return 0, if |v|=0)
template<typename T> PFC_INLINE typename math<T>::scalar_t norm_l1(const vec3<T>&);               // vector L1-norm (Manhattan norm)
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1(const vec3<T>&);              // reciprocal of the vector L1-norm
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const vec3<T>&);            // reciprocal of the vector L1-norm (if |v|=0, return 0)
template<typename T> PFC_INLINE vec3<T> exp(const vec3<T>&);                                      // component-wise natural exponent
template<typename T> PFC_INLINE vec3<T> exp2(const vec3<T>&);                                     // component-wise 2^x
template<typename T> PFC_INLINE vec3<T> ln(const vec3<T>&);                                       // component-wise natural logarithm
template<typename T> PFC_INLINE vec3<T> log2(const vec3<T>&);                                     // component-wise base-2 logarithm
template<typename T> PFC_INLINE vec3<T> log10(const vec3<T>&);                                    // component-wise base-10 logarithm
template<typename T> PFC_INLINE vec3<T> pow(const vec3<T>&, typename math<T>::scalar_t);          // component-wise power
template<typename T> PFC_INLINE vec3<T> unit(const vec3<T>&);                                     // unit vector of the vector: v/|v|
template<typename T> PFC_INLINE vec3<T> unit_z(const vec3<T>&);                                   // unit vector of the vector (if |v|=0, return v=[0, 0, 0])
template<typename T> PFC_INLINE vec3<T> cross(const vec3<T>&, const vec3<T>&);                    // vector cross-product
template<typename T> PFC_INLINE typename math<T>::scalar_t dot(const vec3<T>&, const vec3<T>&);   // vector dot-product
template<typename T> PFC_INLINE typename math<T>::scalar_t dot1(const vec3<T>&);                  // vector dot-product with vector [1, 1, 1] (component sum)
template<typename T> PFC_INLINE void neg(vec3<T>&);                                               // negate the vector
template<typename T, class Rng> PFC_INLINE void rand_u(vec3<T>&, Rng&);                           // random unit vector
template<typename T, class Rng> PFC_INLINE void rand_real1(vec3<T>&, Rng&);                       // random vector where each component is in range [-1, 1]
template<typename T, class Rng> PFC_INLINE void rand_ureal1(vec3<T>&, Rng&);                      // random vector where each component is in range [0, 1]
template<typename T> PFC_INLINE vec3<T> smoothstep(const vec3<T>&);                               // component-wise smoothstep function
template<typename T> PFC_INLINE vec3<T> smootherstep(const vec3<T>&);                             // component-wise smootherstep function
template<typename T> PFC_INLINE vec3<T> lerp(const vec3<T> &v0_,                                  // linear interpolation of vectors: f(t=0)=v0, f(t=1)=v1
                                             const vec3<T> &v1_,
                                             typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE vec3<T> reflect(const vec3<T> &v_, const vec3<T> &n_);            // reflect vector about normal
template<typename T> PFC_INLINE vec3<T> reflect_u(const vec3<T> &v_, const vec3<T> &n_);          // reflect vector about unit normal
template<typename T> PFC_INLINE vec2<T> perspective_project(const vec3<T>&);                      // perspective project vector (divide by last component)
template<typename T, typename U> PFC_INLINE vec3<T> to_vec3(const vec3<U>&);                      // convert between vec3 types
template<unsigned shuffle_, typename T> PFC_INLINE vec3<T> shuffle(const vec3<T>&);               // shuffle vector components (e.g. shuffle<211>(v_) == vec3f(v_.z, v_.y, v_.y))
template<typename T> PFC_INLINE void pack_u1(vec3_32&, const vec3<T>&);                           // pack 3d vector (components in range [0, 1]) to 32-bit 3d vector
template<typename T> PFC_INLINE void pack_s1(vec3_32&, const vec3<T>&);                           // pack 3d vector (components in range [-1, 1]) to 32-bit 3d vector
template<typename T> PFC_INLINE void unpack_u1(vec3<T>&, const vec3_32&);                         // unpack 32-bit 3d vector to 3d vector (components in range [0, 1])
template<typename T> PFC_INLINE void unpack_s1(vec3<T>&, const vec3_32&);                         // unpack 32-bit 3d vector to 3d vector (components in range [-1, 1])
// 4d vector ops
template<typename T> PFC_INLINE bool is_zero(const vec4<T>&);                                     // test for zero-vector, i.e. all components equal zero (exact)
template<typename T> PFC_INLINE bool is_sat(const vec4<T>&);                                      // test for saturated vector, i.e. all components are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const vec4<T>&);                                     // test for signed saturated vector, i.e. all components are in range [-1, 1]
template<typename T> PFC_INLINE bool operator==(const vec4<T>&, const vec4<T>&);                  // test for equality of vectors, i.e. all components of the vectors are equal (exact)
template<typename T> PFC_INLINE bool operator==(const vec4<T>&, typename math<T>::scalar_t);      // test for equality of vector and scalar, i.e. all components of the vector equals the scalar (exact)
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t, const vec4<T>&);      // test for equality of vector and scalar, i.e. all components of the vector equals the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(const vec4<T>&, const vec4<T>&);                  // test for inequality of vectors, i.e. any of the components of the vectors are unequal (exact)
template<typename T> PFC_INLINE bool operator!=(const vec4<T>&, typename math<T>::scalar_t);      // test for inequality of vector and scalar, i.e. any of the components of the vector is unequal to the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t, const vec4<T>&);      // test for inequality of vector and scalar, i.e. any of the components of the vector is unequal to the scalar (exact)
template<typename T> PFC_INLINE vec4<T> operator<(const vec4<T>&, const vec4<T>&);                // component-wise vector less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec4<T> operator<(const vec4<T>&, typename math<T>::scalar_t);    // component-wise vector less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec4<T> operator<(typename math<T>::scalar_t, const vec4<T>&);    // component-wise vector less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec4<T> operator>(const vec4<T>&, const vec4<T>&);                // component-wise vector greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec4<T> operator>(const vec4<T>&, typename math<T>::scalar_t);    // component-wise vector greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec4<T> operator>(typename math<T>::scalar_t, const vec4<T>&);    // component-wise vector greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE vec4<T> operator<=(const vec4<T>&, const vec4<T>&);               // component-wise vector less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec4<T> operator<=(const vec4<T>&, typename math<T>::scalar_t);   // component-wise vector less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec4<T> operator<=(typename math<T>::scalar_t, const vec4<T>&);   // component-wise vector less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec4<T> operator>=(const vec4<T>&, const vec4<T>&);               // component-wise vector greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec4<T> operator>=(const vec4<T>&, typename math<T>::scalar_t);   // component-wise vector greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec4<T> operator>=(typename math<T>::scalar_t, const vec4<T>&);   // component-wise vector greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE vec4<T> sel_eq(const vec4<T> &t0_, const vec4<T> &t1_,            // component-wise equal vector select (t0_==t1_?v0_:v1_)
                                               const vec4<T> &v0_, const vec4<T> &v1_);
template<typename T> PFC_INLINE vec4<T> sel_lt(const vec4<T> &t0_, const vec4<T> &t1_,            // component-wise less-than vector select (t0_<t1_?v0_:v1_)
                                               const vec4<T> &v0_, const vec4<T> &v1_);
template<typename T> PFC_INLINE vec4<T> sel_le(const vec4<T> &t0_, const vec4<T> &t1_,            // component-wise less-or-equal vector select (t0_<=t1_?v0_:v1_)
                                               const vec4<T> &v0_, const vec4<T> &v1_);
template<typename T> PFC_INLINE vec4<T> sel_eqz(const vec4<T> &t_,                                // component-wise equal-to-zero vector select (t_==0?v0_:v1_)
                                                const vec4<T> &v0_, const vec4<T> &v1_);
template<typename T> PFC_INLINE vec4<T> sel_ltz(const vec4<T> &t_,                                // component-wise less-than-zero vector select (t_<0?v0_:v1_)
                                                const vec4<T> &v0_, const vec4<T> &v1_);
template<typename T> PFC_INLINE vec4<T> sel_lez(const vec4<T> &t_,                                // component-wise less-or-equal-to-zero vector select (t_<=0?v0_:v1_)
                                                const vec4<T> &v0_, const vec4<T> &v1_);
template<typename T> PFC_INLINE void operator+=(vec4<T>&, const vec4<T>&);                        // add vector to vector
template<typename T> PFC_INLINE void operator+=(vec4<T>&, typename math<T>::scalar_t);            // add scalar to each component of the vector
template<typename T> PFC_INLINE void operator-=(vec4<T>&, const vec4<T>&);                        // subtract vector from vector
template<typename T> PFC_INLINE void operator-=(vec4<T>&, typename math<T>::scalar_t);            // subtract scalar from each component of the vector
template<typename T> PFC_INLINE void operator*=(vec4<T>&, const vec4<T>&);                        // component-wise vector by vector multiplication
template<typename T> PFC_INLINE void operator*=(vec4<T>&, typename math<T>::scalar_t);            // vector by scalar multiplication
template<typename T> PFC_INLINE void operator*=(vec4<T>&, const mat44<T>&);                       // vector by matrix multiplication
template<typename T> PFC_INLINE void operator/=(vec4<T>&, const vec4<T>&);                        // component-wise vector by vector division
template<typename T> PFC_INLINE void operator/=(vec4<T>&, typename math<T>::scalar_t);            // vector by scalar division
template<typename T> PFC_INLINE vec4<T> operator+(const vec4<T>&, const vec4<T>&);                // add vector to vector
template<typename T> PFC_INLINE vec4<T> operator+(const vec4<T>&, typename math<T>::scalar_t);    // add scalar to each component of the vector
template<typename T> PFC_INLINE vec4<T> operator+(typename math<T>::scalar_t, const vec4<T>&);    // add each component of the vector to a scalar vector
template<typename T> PFC_INLINE vec4<T> operator-(const vec4<T>&, const vec4<T>&);                // subtract vector from vector
template<typename T> PFC_INLINE vec4<T> operator-(const vec4<T>&, typename math<T>::scalar_t);    // subtract scalar from each component of the vector
template<typename T> PFC_INLINE vec4<T> operator-(typename math<T>::scalar_t, const vec4<T>&);    // subtract each component of the vector from a scalar vector
template<typename T> PFC_INLINE vec4<T> operator-(const vec4<T>&);                                // negate the vector
template<typename T> PFC_INLINE vec4<T> operator*(const vec4<T>&, const vec4<T>&);                // component-wise vector by vector multiplication
template<typename T> PFC_INLINE vec4<T> operator*(const vec4<T>&, typename math<T>::scalar_t);    // vector by scalar multiplication
template<typename T> PFC_INLINE vec4<T> operator*(typename math<T>::scalar_t, const vec4<T>&);    // vector by scalar multiplication
template<typename T> PFC_INLINE vec4<T> operator*(const vec4<T>&, const mat44<T>&);               // vector by matrix multiplication
template<typename T> PFC_INLINE vec4<T> operator*(const mat44<T>&, const vec4<T>&);               // matrix by transposed vector multiplication
template<typename T> PFC_INLINE vec4<T> operator/(const vec4<T>&, const vec4<T>&);                // component-wise vector by vector division
template<typename T> PFC_INLINE vec4<T> operator/(const vec4<T>&, typename math<T>::scalar_t);    // vector by scalar division
template<typename T> PFC_INLINE typename math<T>::scalar_t min(const vec4<T>&);                   // minimum component value
template<typename T> PFC_INLINE vec4<T> min(const vec4<T>&, const vec4<T>&);                      // component-wise minimum of the vectors
template<typename T> PFC_INLINE vec4<T> min(const vec4<T>&, const vec4<T>&, const vec4<T>&);
template<typename T> PFC_INLINE vec4<T> min(const vec4<T>&, const vec4<T>&, const vec4<T>&, const vec4<T>&);
template<typename T> PFC_INLINE vec4<T> min(const vec4<T>&, typename math<T>::scalar_t);          // component-wise minimum of the vector and scalar
template<typename T> PFC_INLINE vec4<T> min(typename math<T>::scalar_t, const vec4<T>&);          // component-wise minimum of the vector and scalar
template<typename T> PFC_INLINE typename math<T>::scalar_t max(const vec4<T>&);                   // maximum component value
template<typename T> PFC_INLINE vec4<T> max(const vec4<T>&, const vec4<T>&);                      // component-wise maximum of the vectors
template<typename T> PFC_INLINE vec4<T> max(const vec4<T>&, const vec4<T>&, const vec4<T>&);
template<typename T> PFC_INLINE vec4<T> max(const vec4<T>&, const vec4<T>&, const vec4<T>&, const vec4<T>&);
template<typename T> PFC_INLINE vec4<T> max(const vec4<T>&, typename math<T>::scalar_t);          // component-wise maximum of the vector and scalar
template<typename T> PFC_INLINE vec4<T> max(typename math<T>::scalar_t, const vec4<T>&);          // component-wise maximum of the vector and scalar
template<typename T> PFC_INLINE vec4<T> mul(const vec4<T> &v0_, const vec4<T> &v1_);              // component-wise multiply: v0_*v1_
template<typename T> PFC_INLINE vec4<T> madd(const vec4<T> &v0_,                                  // component-wise multiply-add: v0_*v1+v2_
                                             const vec4<T> &v1_,
                                             const vec4<T> &v2_);
template<typename T> PFC_INLINE vec4<T> madd(const vec4<T> &v_,                                   // vector-scalar-scalar multiply-add: v_*mul_+add_
                                             typename math<T>::scalar_t mul_,
                                             typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE vec4<T> madd(const vec4<T> &v_,                                   // vector-vector-scalar multiply-add: v_*mul_+add_
                                             const vec4<T> &mul_,
                                             typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE vec4<T> madd(const vec4<T> &v_,                                   // vector-scalar-vector multiply-add: v_*mul_+add_
                                             typename math<T>::scalar_t mul_,
                                             const vec4<T> &add_);
template<typename T> PFC_INLINE vec4<T> rcp(const vec4<T>&);                                      // component-wise vector reciprocal
template<typename T> PFC_INLINE vec4<T> rcp_z(const vec4<T>&);                                    // component-wise vector reciprocal (set 0 for 0 components)
template<typename T> PFC_INLINE vec4<T> floor(const vec4<T>&);                                    // component-wise greatest integer less than or equal to the value
template<typename T> PFC_INLINE vec4<T> ceil(const vec4<T>&);                                     // component-wise smallest integer greater than or equal to the value
template<typename T> PFC_INLINE vec4<T> trunc(const vec4<T>&);                                    // component-wise truncate decimal part from the value
template<typename T> PFC_INLINE vec4<T> frc(const vec4<T>&);                                      // component-wise fractional part (for negative values returns 1-fractional part)
template<typename T> PFC_INLINE vec4<T> mod(const vec4<T>&, typename math<T>::scalar_t div_);     // component-wise modulo
template<typename T> PFC_INLINE vec4<T> cycle(const vec4<T>&, typename math<T>::scalar_t cycle_); // component-wise cycle
template<typename T> PFC_INLINE vec4<T> cycle1(const vec4<T>&);                                   // component-wise cycle1
template<typename T> PFC_INLINE vec4<T> sat(const vec4<T>&);                                      // component-wise vector saturate
template<typename T> PFC_INLINE vec4<T> ssat(const vec4<T>&);                                     // component-wise vector signed saturate
template<typename T> PFC_INLINE vec4<T> clamp(const vec4<T>&,                                     // component-wise clamp of the vector
                                              const vec4<T> &min_,
                                              const vec4<T> &max_);
template<typename T> PFC_INLINE vec4<T> clamp(const vec4<T>&,                                     // component-wise clamp of the vector with scalars
                                              typename math<T>::scalar_t min_,
                                              typename math<T>::scalar_t max_);
template<typename T> PFC_INLINE vec4<T> abs(const vec4<T>&);                                      // component-wise vector absolute
template<typename T> PFC_INLINE vec4<T> sgn(const vec4<T>&);                                      // component-wise signum (neg=-1, pos=+1, zero=0)
template<typename T> PFC_INLINE vec4<T> sgn_zp(const vec4<T>&);                                   // component-wise signum (neg=-1, pos&zero=+1)
template<typename T> PFC_INLINE vec4<T> sqr(const vec4<T>&);                                      // component-wise square: x*x
template<typename T> PFC_INLINE vec4<T> cubic(const vec4<T>&);                                    // component-wise cubic: x*x*x
template<typename T> PFC_INLINE vec4<T> sqrt(const vec4<T>&);                                     // component-wise vector square root
template<typename T> PFC_INLINE vec4<T> sqrt_z(const vec4<T>&);                                   // component-wise vector square root (set 0 for components less than zero)
template<typename T> PFC_INLINE vec4<T> cbrt(const vec4<T>&);                                     // component-wise cubic root
template<typename T> PFC_INLINE vec4<T> rsqrt(const vec4<T>&);                                    // component-wise vector reciprocal square root
template<typename T> PFC_INLINE vec4<T> rsqrt_z(const vec4<T>&);                                  // component-wise vector reciprocal square root (set 0 for components less than or equal to zero)
template<typename T> PFC_INLINE vec4<T> rcbrt(const vec4<T>&);                                    // component-wise reciprocal cubic root
template<typename T> PFC_INLINE vec4<T> rcbrt_z(const vec4<T>&);                                  // component-wise reciprocal cubic root (set 0 for components that are 0)
template<typename T> PFC_INLINE typename math<T>::scalar_t norm(const vec4<T>&);                  // vector norm (length): |v|
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm(const vec4<T>&);                 // reciprocal of the vector norm: 1/|v|
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_z(const vec4<T>&);               // reciprocal of the vector norm: 1/|v| (return 0, if |v|=0)
template<typename T> PFC_INLINE typename math<T>::scalar_t norm2(const vec4<T>&);                 // squared vector norm: |v|^2
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2(const vec4<T>&);                // reciprocal of the squared vector norm: 1/|v|^2
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2_z(const vec4<T>&);              // reciprocal of the squared vector norm: 1/|v|^2 (return 0, if |v|=0)
template<typename T> PFC_INLINE typename math<T>::scalar_t norm_l1(const vec4<T>&);               // vector L1-norm (Manhattan norm)
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1(const vec4<T>&);              // reciprocal of the vector L1-norm
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const vec4<T>&);            // reciprocal of the vector L1-norm (if |v|=0, return 0)
template<typename T> PFC_INLINE vec4<T> exp(const vec4<T>&);                                      // component-wise natural exponent
template<typename T> PFC_INLINE vec4<T> exp2(const vec4<T>&);                                     // component-wise 2^x
template<typename T> PFC_INLINE vec4<T> ln(const vec4<T>&);                                       // component-wise natural logarithm
template<typename T> PFC_INLINE vec4<T> log2(const vec4<T>&);                                     // component-wise base-2 logarithm
template<typename T> PFC_INLINE vec4<T> log10(const vec4<T>&);                                    // component-wise base-10 logarithm
template<typename T> PFC_INLINE vec4<T> pow(const vec4<T>&, typename math<T>::scalar_t);          // component-wise power
template<typename T> PFC_INLINE vec4<T> unit(const vec4<T>&);                                     // unit vector of the vector: v/|v|
template<typename T> PFC_INLINE vec4<T> unit_z(const vec4<T>&);                                   // unit vector of the vector (if |v|=0, return v=[0, 0, 0, 0])
template<typename T> PFC_INLINE typename math<T>::scalar_t dot(const vec4<T>&, const vec4<T>&);   // vector dot-product
template<typename T> PFC_INLINE typename math<T>::scalar_t dot1(const vec4<T>&);                  // vector dot-product with vector [1, 1, 1, 1] (component sum)
template<typename T> PFC_INLINE void neg(vec4<T>&);                                               // negate the vector
template<typename T, class Rng> PFC_INLINE void rand_u(vec4<T>&, Rng&);                           // random unit vector
template<typename T, class Rng> PFC_INLINE void rand_real1(vec4<T>&, Rng&);                       // random vector where each component is in range [-1, 1]
template<typename T, class Rng> PFC_INLINE void rand_ureal1(vec4<T>&, Rng&);                      // random vector where each component is in range [0, 1]
template<typename T> PFC_INLINE vec4<T> smoothstep(const vec4<T>&);                               // component-wise smoothstep function
template<typename T> PFC_INLINE vec4<T> smootherstep(const vec4<T>&);                             // component-wise smootherstep function
template<typename T> PFC_INLINE vec4<T> lerp(const vec4<T> &v0_,                                  // linear interpolation of vectors: f(t=0)=v0, f(t=1)=v1
                                             const vec4<T> &v1_,
                                             typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE vec4<T> reflect(const vec4<T> &v_, const vec4<T> &n_);            // reflect vector about normal
template<typename T> PFC_INLINE vec4<T> reflect_u(const vec4<T> &v_, const vec4<T> &n_);          // reflect vector about unit normal
template<typename T> PFC_INLINE vec3<T> perspective_project(const vec4<T>&);                      // perspective project vector (divide by last component)
template<typename T, typename U> PFC_INLINE vec4<T> to_vec4(const vec4<U>&);                      // convert between vec4 types
template<unsigned shuffle_, typename T> PFC_INLINE vec4<T> shuffle(const vec4<T>&);               // shuffle vector components (e.g. shuffle<2311>(v_) == vec4f(v_.z, v_.w, v_.y, v_.y))
template<typename T> PFC_INLINE void pack_u1(vec4_32&, const vec4<T>&);                           // pack 4d vector (components in range [0, 1]) to 32-bit 4d vector
template<typename T> PFC_INLINE void pack_s1(vec4_32&, const vec4<T>&);                           // pack 4d vector (components in range [-1, 1]) to 32-bit 4d vector
template<typename T> PFC_INLINE void unpack_u1(vec4<T>&, const vec4_32&);                         // unpack 32-bit 4d vector to 4d vector (components in range [0, 1])
template<typename T> PFC_INLINE void unpack_s1(vec4<T>&, const vec4_32&);                         // unpack 32-bit 4d vector to 4d vector (components in range [-1, 1])
// 2x2 matrix ops
template<typename T> PFC_INLINE bool is_zero(const mat22<T>&);                                    // test for zero-matrix, i.e. all components equal zero (exact)
template<typename T> PFC_INLINE bool is_sat(const mat22<T>&);                                     // test for saturated matrix, i.e. all components are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const mat22<T>&);                                    // test for signed saturated matrix, i.e. all components are in range [-1, 1]
template<typename T> PFC_INLINE bool operator==(const mat22<T>&, const mat22<T>&);                // test for equality of matrices, i.e. all components of the matrices are equal (exact)
template<typename T> PFC_INLINE bool operator==(const mat22<T>&, typename math<T>::scalar_t);     // test for equality of matrix and scalar, i.e. all components of the matrix equals the scalar (exact)
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t, const mat22<T>&);     // test for equality of matrix and scalar, i.e. all components of the matrix equals the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(const mat22<T>&, const mat22<T>&);                // test for inequality of matrices, i.e. any of the components of the vectors are unequal (exact)
template<typename T> PFC_INLINE bool operator!=(const mat22<T>&, typename math<T>::scalar_t);     // test for inequality of matrix and scalar, i.e. any of the components of the matrix is unequal to the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t, const mat22<T>&);     // test for inequality of matrix and scalar, i.e. any of the components of the matrix is unequal to the scalar (exact)
template<typename T> PFC_INLINE void operator+=(mat22<T>&, const mat22<T>&);                      // add matrix to matrix
template<typename T> PFC_INLINE void operator+=(mat22<T>&, typename math<T>::scalar_t);           // add scalar to matrix
template<typename T> PFC_INLINE void operator-=(mat22<T>&, const mat22<T>&);                      // subtract matrix from matrix
template<typename T> PFC_INLINE void operator-=(mat22<T>&, typename math<T>::scalar_t);           // subtract scalar from matrix
template<typename T> PFC_INLINE void operator*=(mat22<T>&, const mat22<T>&);                      // multiply matrix by matrix
template<typename T> PFC_INLINE void operator*=(mat22<T>&, typename math<T>::scalar_t);           // multiply matrix by scalar
template<typename T> PFC_INLINE void operator/=(mat22<T>&, typename math<T>::scalar_t);           // divide matrix by scalar
template<typename T> PFC_INLINE mat22<T> operator+(const mat22<T>&, const mat22<T>&);             // add matrix to matrix
template<typename T> PFC_INLINE mat22<T> operator+(const mat22<T>&, typename math<T>::scalar_t);  // add scalar to matrix
template<typename T> PFC_INLINE mat22<T> operator+(typename math<T>::scalar_t, const mat22<T>&);  // add matrix to scalar
template<typename T> PFC_INLINE mat22<T> operator-(const mat22<T>&, const mat22<T>&);             // subtract matrix from matrix
template<typename T> PFC_INLINE mat22<T> operator-(const mat22<T>&, typename math<T>::scalar_t);  // subtract scalar from matrix
template<typename T> PFC_INLINE mat22<T> operator-(typename math<T>::scalar_t, const mat22<T>&);  // subtract matrix from scalar
template<typename T> PFC_INLINE mat22<T> operator-(const mat22<T>&);                              // negate the matrix
template<typename T> PFC_INLINE mat22<T> operator*(const mat22<T>&, const mat22<T>&);             // multiply matrix by matrix
template<typename T> PFC_INLINE mat22<T> operator*(const mat22<T>&, typename math<T>::scalar_t);  // multiply matrix by scalar
template<typename T> PFC_INLINE mat22<T> operator*(typename math<T>::scalar_t, const mat22<T>&);  // multiply matrix by scalar
template<typename T> PFC_INLINE mat22<T> operator/(const mat22<T>&, typename math<T>::scalar_t);  // divide matrix by scalar
template<typename T> PFC_INLINE mat22<T> mul(const mat22<T> &m0_, const mat22<T> &m1_);           // component-wise multiply: m0_*m1_
template<typename T> PFC_INLINE mat22<T> madd(const mat22<T> &m0_,                                // component-wise multiply-add: m0_*m1+m2_
                                              const mat22<T> &m1_,
                                              const mat22<T> &m2_);
template<typename T> PFC_INLINE mat22<T> madd(const mat22<T> &m_,                                 // matrix-scalar-scalar multiply-add: m_*mul_+add_
                                              typename math<T>::scalar_t mul_,
                                              typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE mat22<T> madd(const mat22<T> &m_,                                 // matrix-matrix-scalar multiply-add: m_*mul_+add_
                                              const mat22<T> &mul_,
                                              typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE mat22<T> madd(const mat22<T> &m_,                                 // matrix-scalar-matrix multiply-add: m_*mul_+add_
                                              typename math<T>::scalar_t mul_,
                                              const mat22<T> &add_);
template<typename T> PFC_INLINE typename math<T>::scalar_t det(const mat22<T>&);                  // determinant of the matrix
template<typename T> PFC_INLINE mat22<T> inv(const mat22<T>&, typename math<T>::scalar_t *det_=0);// inverse of the matrix
template<typename T> PFC_INLINE typename math<T>::scalar_t tr(const mat22<T>&);                   // trace of the matrix
template<typename T> PFC_INLINE void identity(mat22<T>&);                                         // set matrix to identity
template<typename T> PFC_INLINE void transpose(mat22<T>&);                                        // transpose of the matrix
template<typename T> PFC_INLINE void transpose(mat22<T> &res_, const mat22<T>&);                  // transpose of the matrix
template<typename T> PFC_INLINE void neg(mat22<T>&);                                              // negate the matrix
template<typename T> PFC_INLINE mat22<T> lerp(const mat22<T> &m0_,                                // linear interpolation of matrices: f(t=0)=m0, f(t=1)=m1
                                              const mat22<T> &m1_,
                                              typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE void lerp(mat22<T> &res_,                                         // linear interpolation of matrices: f(t=0)=m0, f(t=1)=m1
                                          const mat22<T> &m0_,
                                          const mat22<T> &m1_,
                                          typename math<T>::scalar_t t_);
template<typename T, typename U> PFC_INLINE mat22<T> to_mat22(const mat22<U>&);                   // convert between mat22 types
template<typename T> PFC_INLINE void normalize(mat22<T>&);                                        // normalize matrix vectors
// 3x3 matrix ops
template<typename T> PFC_INLINE bool is_zero(const mat33<T>&);                                    // test for zero-matrix, i.e. all components equal zero (exact)
template<typename T> PFC_INLINE bool is_orthogonal(const mat33<T>&);                              // test for orthogonal matrix
template<typename T> PFC_INLINE bool is_sat(const mat33<T>&);                                     // test for saturated matrix, i.e. all components are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const mat33<T>&);                                    // test for signed saturated matrix, i.e. all components are in range [-1, 1]
template<typename T> PFC_INLINE bool operator==(const mat33<T>&, const mat33<T>&);                // test for equality of matrices, i.e. all components of the matrices are equal (exact)
template<typename T> PFC_INLINE bool operator==(const mat33<T>&, typename math<T>::scalar_t);     // test for equality of matrix and scalar, i.e. all components of the matrix equals the scalar (exact)
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t, const mat33<T>&);     // test for equality of matrix and scalar, i.e. all components of the matrix equals the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(const mat33<T>&, const mat33<T>&);                // test for inequality of matrices, i.e. any of the components of the vectors are unequal (exact)
template<typename T> PFC_INLINE bool operator!=(const mat33<T>&, typename math<T>::scalar_t);     // test for inequality of matrix and scalar, i.e. any of the components of the matrix is unequal to the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t, const mat33<T>&);     // test for inequality of matrix and scalar, i.e. any of the components of the matrix is unequal to the scalar (exact)
template<typename T> PFC_INLINE void operator+=(mat33<T>&, const mat33<T>&);                      // add matrix to matrix
template<typename T> PFC_INLINE void operator+=(mat33<T>&, typename math<T>::scalar_t);           // add scalar to matrix
template<typename T> PFC_INLINE void operator-=(mat33<T>&, const mat33<T>&);                      // subtract matrix from matrix
template<typename T> PFC_INLINE void operator-=(mat33<T>&, typename math<T>::scalar_t);           // subtract scalar from matrix
template<typename T> PFC_INLINE void operator*=(mat33<T>&, const mat33<T>&);                      // multiply matrix by matrix
template<typename T> PFC_INLINE void operator*=(mat33<T>&, const quat<T>&);                       // multiply matrix by quaternion
template<typename T> PFC_INLINE void operator*=(mat33<T>&, typename math<T>::scalar_t);           // multiply matrix by scalar
template<typename T> PFC_INLINE void operator/=(mat33<T>&, typename math<T>::scalar_t);           // divide matrix by scalar
template<typename T> PFC_INLINE mat33<T> operator+(const mat33<T>&, const mat33<T>&);             // add matrix to matrix
template<typename T> PFC_INLINE mat33<T> operator+(const mat33<T>&, typename math<T>::scalar_t);  // add scalar to matrix
template<typename T> PFC_INLINE mat33<T> operator+(typename math<T>::scalar_t, const mat33<T>&);  // add matrix to scalar
template<typename T> PFC_INLINE mat33<T> operator-(const mat33<T>&, const mat33<T>&);             // subtract matrix from matrix
template<typename T> PFC_INLINE mat33<T> operator-(const mat33<T>&, typename math<T>::scalar_t);  // subtract scalar from matrix
template<typename T> PFC_INLINE mat33<T> operator-(typename math<T>::scalar_t, const mat33<T>&);  // subtract matrix from scalar
template<typename T> PFC_INLINE mat33<T> operator-(const mat33<T>&);                              // negate the matrix
template<typename T> PFC_INLINE mat33<T> operator*(const mat33<T>&, const mat33<T>&);             // multiply matrix by matrix
template<typename T> PFC_INLINE mat33<T> operator*(const mat33<T>&, const quat<T>&);              // multiply matrix by quaternion
template<typename T> PFC_INLINE mat33<T> operator*(const quat<T>&, const mat33<T>&);              // multiply quaternion by matrix
template<typename T> PFC_INLINE mat33<T> operator*(const mat33<T>&, typename math<T>::scalar_t);  // multiply matrix by scalar
template<typename T> PFC_INLINE mat33<T> operator*(typename math<T>::scalar_t, const mat33<T>&);  // multiply matrix by scalar
template<typename T> PFC_INLINE mat33<T> operator/(const mat33<T>&, typename math<T>::scalar_t);  // divide matrix by scalar
template<typename T> PFC_INLINE mat33<T> mul(const mat33<T> &m0_, const mat33<T> &m1_);           // component-wise multiply: m0_*m1_
template<typename T> PFC_INLINE mat33<T> madd(const mat33<T> &m0_,                                // component-wise multiply-add: m0_*m1+m2_
                                              const mat33<T> &m1_,
                                              const mat33<T> &m2_);
template<typename T> PFC_INLINE mat33<T> madd(const mat33<T> &m_,                                 // matrix-scalar-scalar multiply-add: m_*mul_+add_
                                              typename math<T>::scalar_t mul_,
                                              typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE mat33<T> madd(const mat33<T> &m_,                                 // matrix-matrix-scalar multiply-add: m_*mul_+add_
                                              const mat33<T> &mul_,
                                              typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE mat33<T> madd(const mat33<T> &m_,                                 // matrix-scalar-matrix multiply-add: m_*mul_+add_
                                              typename math<T>::scalar_t mul_,
                                              const mat33<T> &add_);
template<typename T> PFC_INLINE typename math<T>::scalar_t det(const mat33<T>&);                  // determinant of the matrix
template<typename T> PFC_INLINE mat33<T> inv(const mat33<T>&, typename math<T>::scalar_t *det_=0);// inverse of the matrix
template<typename T> PFC_INLINE typename math<T>::scalar_t tr(const mat33<T>&);                   // trace of the matrix
template<typename T> PFC_INLINE void identity(mat33<T>&);                                         // set matrix to identity
template<typename T> PFC_INLINE void transpose(mat33<T>&);                                        // transpose of the matrix
template<typename T> PFC_INLINE void transpose(mat33<T> &res_, const mat33<T>&);                  // transpose of the matrix
template<typename T> PFC_INLINE void neg(mat33<T>&);                                              // negate the matrix
template<typename T> PFC_INLINE mat33<T> lerp(const mat33<T> &m0_,                                // linear interpolation of matrices: f(t=0)=m0, f(t=1)=m1
                                              const mat33<T> &m1_,
                                              typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE void lerp(mat33<T> &res_,                                         // linear interpolation of matrices: f(t=0)=m0, f(t=1)=m1
                                          const mat33<T> &m0_,
                                          const mat33<T> &m1_,
                                          typename math<T>::scalar_t t_);
template<typename T, typename U> PFC_INLINE mat33<T> to_mat33(const mat33<U>&);                   // convert between mat33 types
template<typename T> PFC_INLINE void normalize(mat33<T>&);                                        // normalize matrix vectors
template<typename T> PFC_INLINE void orthonormalize(mat33<T>&);                                   // ortho-normalize the matrix
template<typename T> PFC_INLINE void set_rotation_xyz(mat33<T>&,                                  // set rotation matrix with angles in order Rx*Ry*Rz
                                                      typename math<T>::scalar_t x_,
                                                      typename math<T>::scalar_t y_,
                                                      typename math<T>::scalar_t z_);
template<typename T> PFC_INLINE void set_rotation_zyx(mat33<T>&,                                  // set rotation matrix with angles in order Rz*Ry*Rx
                                                      typename math<T>::scalar_t x_,
                                                      typename math<T>::scalar_t y_,
                                                      typename math<T>::scalar_t z_);
template<typename T> PFC_INLINE void set_rotation_zxz(mat33<T>&,                                  // set rotation matrix with angles in order Rz*Rx*Rz (Euler)
                                                      typename math<T>::scalar_t x_,
                                                      typename math<T>::scalar_t z_);
// 4x4 matrix ops
template<typename T> PFC_INLINE bool is_zero(const mat44<T>&);                                    // test for zero-matrix, i.e. all components equal zero (exact)
template<typename T> PFC_INLINE bool is_sat(const mat44<T>&);                                     // test for saturated matrix, i.e. all components are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const mat44<T>&);                                    // test for signed saturated matrix, i.e. all components are in range [-1, 1]
template<typename T> PFC_INLINE bool operator==(const mat44<T>&, const mat44<T>&);                // test for equality of matrices, i.e. all components of the matrices are equal (exact)
template<typename T> PFC_INLINE bool operator==(const mat44<T>&, typename math<T>::scalar_t);     // test for equality of matrix and scalar, i.e. all components of the matrix equals the scalar (exact)
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t, const mat44<T>&);     // test for equality of matrix and scalar, i.e. all components of the matrix equals the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(const mat44<T>&, const mat44<T>&);                // test for inequality of matrices, i.e. any of the components of the vectors are unequal (exact)
template<typename T> PFC_INLINE bool operator!=(const mat44<T>&, typename math<T>::scalar_t);     // test for inequality of matrix and scalar, i.e. any of the components of the matrix is unequal to the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t, const mat44<T>&);     // test for inequality of matrix and scalar, i.e. any of the components of the matrix is unequal to the scalar (exact)
template<typename T> PFC_INLINE void operator+=(mat44<T>&, const mat44<T>&);                      // add matrix to matrix
template<typename T> PFC_INLINE void operator+=(mat44<T>&, typename math<T>::scalar_t);           // add scalar to matrix
template<typename T> PFC_INLINE void operator-=(mat44<T>&, const mat44<T>&);                      // subtract matrix from matrix
template<typename T> PFC_INLINE void operator-=(mat44<T>&, typename math<T>::scalar_t);           // subtract scalar from matrix
template<typename T> PFC_INLINE void operator*=(mat44<T>&, const mat44<T>&);                      // multiply matrix by matrix
template<typename T> PFC_INLINE void operator*=(mat44<T>&, typename math<T>::scalar_t);           // multiply matrix by scalar
template<typename T> PFC_INLINE void operator/=(mat44<T>&, typename math<T>::scalar_t);           // divide matrix by scalar
template<typename T> PFC_INLINE mat44<T> operator+(const mat44<T>&, const mat44<T>&);             // add matrix to matrix
template<typename T> PFC_INLINE mat44<T> operator+(const mat44<T>&, typename math<T>::scalar_t);  // add scalar to matrix
template<typename T> PFC_INLINE mat44<T> operator+(typename math<T>::scalar_t, const mat44<T>&);  // add matrix to scalar
template<typename T> PFC_INLINE mat44<T> operator-(const mat44<T>&, const mat44<T>&);             // subtract matrix from matrix
template<typename T> PFC_INLINE mat44<T> operator-(const mat44<T>&, typename math<T>::scalar_t);  // subtract scalar from matrix
template<typename T> PFC_INLINE mat44<T> operator-(typename math<T>::scalar_t, const mat44<T>&);  // subtract matrix from scalar
template<typename T> PFC_INLINE mat44<T> operator-(const mat44<T>&);                              // negate the matrix
template<typename T> PFC_INLINE mat44<T> operator*(const mat44<T>&, const mat44<T>&);             // multiply matrix by matrix
template<typename T> PFC_INLINE mat44<T> operator*(const mat44<T>&, typename math<T>::scalar_t);  // multiply matrix by scalar
template<typename T> PFC_INLINE mat44<T> operator*(typename math<T>::scalar_t, const mat44<T>&);  // multiply matrix by scalar
template<typename T> PFC_INLINE mat44<T> operator/(const mat44<T>&, typename math<T>::scalar_t);  // divide matrix by scalar
template<typename T> PFC_INLINE mat44<T> mul(const mat44<T> &m0_, const mat44<T> &m1_);           // component-wise multiply: m0_*m1_
template<typename T> PFC_INLINE mat44<T> madd(const mat44<T> &m0_,                                // component-wise multiply-add: m0_*m1+m2_
                                              const mat44<T> &m1_,
                                              const mat44<T> &m2_);
template<typename T> PFC_INLINE mat44<T> madd(const mat44<T> &m_,                                 // matrix scalar multiply-add: v_*mul_+add_
                                              typename math<T>::scalar_t mul_,
                                              typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE mat44<T> madd(const mat44<T> &m_,                                 // matrix-matrix-scalar multiply-add: m_*mul_+add_
                                              const mat44<T> &mul_,
                                              typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE mat44<T> madd(const mat44<T> &m_,                                 // matrix-scalar-matrix multiply-add: m_*mul_+add_
                                              typename math<T>::scalar_t mul_,
                                              const mat44<T> &add_);
template<typename T> PFC_INLINE typename math<T>::scalar_t det(const mat44<T>&);                  // determinant of the matrix
template<typename T> PFC_INLINE mat44<T> inv(const mat44<T>&, typename math<T>::scalar_t *det_=0);// inverse of the matrix
template<typename T> PFC_INLINE typename math<T>::scalar_t tr(const mat44<T>&);                   // trace of the matrix
template<typename T> PFC_INLINE void identity(mat44<T>&);                                         // set matrix to identity
template<typename T> PFC_INLINE void transpose(mat44<T>&);                                        // transpose of the matrix
template<typename T> PFC_INLINE void transpose(mat44<T> &res_, const mat44<T>&);                  // transpose of the matrix
template<typename T> PFC_INLINE void neg(mat44<T>&);                                              // negate the matrix
template<typename T> PFC_INLINE mat44<T> lerp(const mat44<T> &m0_,                                // linear interpolation of matrices: f(t=0)=m0, f(t=1)=m1
                                              const mat44<T> &m1_,
                                              typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE void lerp(mat44<T> &res_,                                         // linear interpolation of matrices: f(t=0)=m0, f(t=1)=m1
                                          const mat44<T> &m0_,
                                          const mat44<T> &m1_,
                                          typename math<T>::scalar_t t_); 
template<typename T> PFC_INLINE void normalize(mat44<T>&);                                        // normalize matrix vectors
template<typename T, typename U> PFC_INLINE mat44<T> to_mat44(const mat44<U>&);                   // convert between mat44 types
// quaternion ops
template<typename T> PFC_INLINE bool is_zero(const quat<T>&);                                     // test for zero-quaternion, i.e. all components equal zero (exact)
template<typename T> PFC_INLINE bool is_sat(const quat<T>&);                                      // test for saturated quaternion, i.e. all components are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const quat<T>&);                                     // test for signed saturated quaternion, i.e. all components are in range [-1, 1]
template<typename T> PFC_INLINE bool operator==(const quat<T>&, const quat<T>&);                  // test for equality of quaternions, i.e. all components of the quaternions are equal (exact)
template<typename T> PFC_INLINE bool operator==(const quat<T>&, typename math<T>::scalar_t);      // test for equality of quaternion and scalar, i.e. all components of the quaternion equals the scalar (exact)
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t, const quat<T>&);      // test for equality of quaternion and scalar, i.e. all components of the quaternion equals the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(const quat<T>&, const quat<T>&);                  // test for inequality of quaternions, i.e. any of the components of the quaternions are unequal (exact)
template<typename T> PFC_INLINE bool operator!=(const quat<T>&, typename math<T>::scalar_t);      // test for inequality of quaternion and scalar, i.e. any of the components of the quaternion is unequal to the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t, const quat<T>&);      // test for inequality of quaternion and scalar, i.e. any of the components of the quaternion is unequal to the scalar (exact)
template<typename T> PFC_INLINE quat<T> operator<(const quat<T>&, const quat<T>&);                // component-wise quaternion less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE quat<T> operator<(const quat<T>&, typename math<T>::scalar_t);    // component-wise quaternion less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE quat<T> operator<(typename math<T>::scalar_t, const quat<T>&);    // component-wise quaternion less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE quat<T> operator>(const quat<T>&, const quat<T>&);                // component-wise quaternion greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE quat<T> operator>(const quat<T>&, typename math<T>::scalar_t);    // component-wise quaternion greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE quat<T> operator>(typename math<T>::scalar_t, const quat<T>&);    // component-wise quaternion greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE quat<T> operator<=(const quat<T>&, const quat<T>&);               // component-wise quaternion less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE quat<T> operator<=(const quat<T>&, typename math<T>::scalar_t);   // component-wise quaternion less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE quat<T> operator<=(typename math<T>::scalar_t, const quat<T>&);   // component-wise quaternion less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE quat<T> operator>=(const quat<T>&, const quat<T>&);               // component-wise quaternion greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE quat<T> operator>=(const quat<T>&, typename math<T>::scalar_t);   // component-wise quaternion greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE quat<T> operator>=(typename math<T>::scalar_t, const quat<T>&);   // component-wise quaternion greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE quat<T> sel_eq(const quat<T> &t0_, const quat<T> &t1_,            // component-wise equal quaternion select (t0_==t1_?q0_:q1_)
                                               const quat<T> &q0_, const quat<T> &q1_);
template<typename T> PFC_INLINE quat<T> sel_lt(const quat<T> &t0_, const quat<T> &t1_,            // component-wise less-than quaternion select (t0_<t1_?q0_:q1_)
                                               const quat<T> &q0_, const quat<T> &q1_);
template<typename T> PFC_INLINE quat<T> sel_le(const quat<T> &t0_, const quat<T> &t1_,            // component-wise less-or-equal quaternion select (t0_<=t1_?q0_:q1_)
                                               const quat<T> &q0_, const quat<T> &q1_);
template<typename T> PFC_INLINE quat<T> sel_eqz(const quat<T> &t_,                                // component-wise equal-to-zero quaternion select (t_==0?q0_:q1_)
                                                const quat<T> &q0_, const quat<T> &q1_);
template<typename T> PFC_INLINE quat<T> sel_ltz(const quat<T> &t_,                                // component-wise less-than-zero quaternion select (t_<0?q0_:q1_)
                                                const quat<T> &q0_, const quat<T> &q1_);
template<typename T> PFC_INLINE quat<T> sel_lez(const quat<T> &t_,                                // component-wise less-or-equal-to-zero quaternion select (t_<=0?q0_:q1_)
                                                const quat<T> &q0_, const quat<T> &q1_);
template<typename T> PFC_INLINE void operator+=(quat<T>&, const quat<T>&);                        // add quaternion to quaternion
template<typename T> PFC_INLINE void operator+=(quat<T>&, typename math<T>::scalar_t);            // add scalar to each component of the quaternion
template<typename T> PFC_INLINE void operator-=(quat<T>&, const quat<T>&);                        // subtract quaternion from quaternion
template<typename T> PFC_INLINE void operator-=(quat<T>&, typename math<T>::scalar_t);            // subtract scalar from each component of the quaternion
template<typename T> PFC_INLINE void operator*=(quat<T>&, const quat<T>&);                        // multiply quaternion by quaternion
template<typename T> PFC_INLINE void operator*=(quat<T>&, typename math<T>::scalar_t);            // quaternion by scalar multiplication
template<typename T> PFC_INLINE void operator/=(quat<T>&, typename math<T>::scalar_t);            // quaternion by scalar division
template<typename T> PFC_INLINE quat<T> operator+(const quat<T>&, const quat<T>&);                // add quaternion to quaternion
template<typename T> PFC_INLINE quat<T> operator+(const quat<T>&, typename math<T>::scalar_t);    // add scalar to each component of the quaternion
template<typename T> PFC_INLINE quat<T> operator+(typename math<T>::scalar_t, const quat<T>&);    // add each component of the quaternion to a scalar quaternion
template<typename T> PFC_INLINE quat<T> operator-(const quat<T>&, const quat<T>&);                // subtract quaternion from quaternion
template<typename T> PFC_INLINE quat<T> operator-(const quat<T>&, typename math<T>::scalar_t);    // subtract scalar from each component of the quaternion
template<typename T> PFC_INLINE quat<T> operator-(typename math<T>::scalar_t, const quat<T>&);    // subtract each component of the quaternion from a scalar quaternion
template<typename T> PFC_INLINE quat<T> operator-(const quat<T>&);                                // negate the quaternion
template<typename T> PFC_INLINE quat<T> operator*(const quat<T>&, const quat<T>&);                // multiply quaternion by quaternion
template<typename T> PFC_INLINE quat<T> operator*(const quat<T>&, typename math<T>::scalar_t);    // quaternion by scalar multiplication
template<typename T> PFC_INLINE quat<T> operator*(typename math<T>::scalar_t, const quat<T>&);    // quaternion by scalar multiplication
template<typename T> PFC_INLINE quat<T> operator/(const quat<T>&, typename math<T>::scalar_t);    // quaternion by scalar division
template<typename T> PFC_INLINE typename math<T>::scalar_t min(const quat<T>&);                   // minimum component value
template<typename T> PFC_INLINE quat<T> min(const quat<T>&, const quat<T>&);                      // component-wise minimum of the quaternions
template<typename T> PFC_INLINE quat<T> min(const quat<T>&, const quat<T>&, const quat<T>&);
template<typename T> PFC_INLINE quat<T> min(const quat<T>&, const quat<T>&, const quat<T>&, const quat<T>&);
template<typename T> PFC_INLINE quat<T> min(const quat<T>&, typename math<T>::scalar_t);          // component-wise minimum of the quaternion and scalar
template<typename T> PFC_INLINE quat<T> min(typename math<T>::scalar_t, const quat<T>&);          // component-wise minimum of the quaternion and scalar
template<typename T> PFC_INLINE typename math<T>::scalar_t max(const quat<T>&);                   // maximum component value
template<typename T> PFC_INLINE quat<T> max(const quat<T>&, const quat<T>&);                      // component-wise maximum of the quaternions
template<typename T> PFC_INLINE quat<T> max(const quat<T>&, const quat<T>&, const quat<T>&);
template<typename T> PFC_INLINE quat<T> max(const quat<T>&, const quat<T>&, const quat<T>&, const quat<T>&);
template<typename T> PFC_INLINE quat<T> max(const quat<T>&, typename math<T>::scalar_t);          // component-wise maximum of the quaternion and scalar
template<typename T> PFC_INLINE quat<T> max(typename math<T>::scalar_t, const quat<T>&);          // component-wise maximum of the quaternion and scalar
template<typename T> PFC_INLINE quat<T> mul(const quat<T> &q0_, const quat<T> &q1_);              // component-wise multiply: q0_*q1_
template<typename T> PFC_INLINE quat<T> madd(const quat<T> &q0_,                                  // component-wise multiply-add: q0_*q1+q2_
                                             const quat<T> &q1_,
                                             const quat<T> &q2_);
template<typename T> PFC_INLINE quat<T> madd(const quat<T> &q_,                                   // quaternion-scalar-scalar multiply-add: q_*mul_+add_
                                             typename math<T>::scalar_t mul_,
                                             typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE quat<T> madd(const quat<T> &q_,                                   // quaternion-quaternion-scalar multiply-add: q_*mul_+add_
                                             const quat<T> &mul_,
                                             typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE quat<T> madd(const quat<T> &q_,                                   // quaternion-scalar-quaternion multiply-add: q_*mul_+add_
                                             typename math<T>::scalar_t mul_,
                                             const quat<T> &add_);
template<typename T> PFC_INLINE quat<T> rcp(const quat<T>&);                                      // component-wise quaternion reciprocal
template<typename T> PFC_INLINE quat<T> rcp_z(const quat<T>&);                                    // component-wise quaternion reciprocal (set 0 for 0 components)
template<typename T> PFC_INLINE quat<T> floor(const quat<T>&);                                    // component-wise greatest integer less than or equal to the value
template<typename T> PFC_INLINE quat<T> ceil(const quat<T>&);                                     // component-wise smallest integer greater than or equal to the value
template<typename T> PFC_INLINE quat<T> trunc(const quat<T>&);                                    // component-wise truncate decimal part from the value
template<typename T> PFC_INLINE quat<T> frc(const quat<T>&);                                      // component-wise fractional part (for negative values returns 1-fractional part)
template<typename T> PFC_INLINE quat<T> mod(const quat<T>&, typename math<T>::scalar_t div_);     // component-wise modulo
template<typename T> PFC_INLINE quat<T> cycle(const quat<T>&, typename math<T>::scalar_t cycle_); // component-wise cycle
template<typename T> PFC_INLINE quat<T> cycle1(const quat<T>&);                                   // component-wise cycle1
template<typename T> PFC_INLINE quat<T> sat(const quat<T>&);                                      // component-wise quaternion saturate
template<typename T> PFC_INLINE quat<T> ssat(const quat<T>&);                                     // component-wise quaternion signed saturate
template<typename T> PFC_INLINE quat<T> clamp(const quat<T>&,                                     // component-wise clamp of the quaternion
                                              const quat<T> &min_,
                                              const quat<T> &max_);
template<typename T> PFC_INLINE quat<T> clamp(const quat<T>&,                                     // component-wise clamp of the quaternion with scalars
                                              typename math<T>::scalar_t min_,
                                              typename math<T>::scalar_t max_);
template<typename T> PFC_INLINE quat<T> abs(const quat<T>&);                                      // component-wise quaternion absolute
template<typename T> PFC_INLINE quat<T> sgn(const quat<T>&);                                      // component-wise signum (neg=-1, pos=+1, zero=0)
template<typename T> PFC_INLINE quat<T> sgn_zp(const quat<T>&);                                   // component-wise signum (neg=-1, pos&zero=+1)
template<typename T> PFC_INLINE quat<T> sqr(const quat<T>&);                                      // component-wise square: x*x
template<typename T> PFC_INLINE quat<T> cubic(const quat<T>&);                                    // component-wise cubic: x*x*x
template<typename T> PFC_INLINE quat<T> sqrt(const quat<T>&);                                     // component-wise quaternion square root
template<typename T> PFC_INLINE quat<T> sqrt_z(const quat<T>&);                                   // component-wise quaternion square root (set 0 for components less than zero)
template<typename T> PFC_INLINE quat<T> cbrt(const quat<T>&);                                     // component-wise cubic root
template<typename T> PFC_INLINE quat<T> rsqrt(const quat<T>&);                                    // component-wise quaternion reciprocal square root
template<typename T> PFC_INLINE quat<T> rsqrt_z(const quat<T>&);                                  // component-wise quaternion reciprocal square root (set 0 for components less than or equal to zero)
template<typename T> PFC_INLINE quat<T> rcbrt(const quat<T>&);                                    // component-wise reciprocal cubic root
template<typename T> PFC_INLINE quat<T> rcbrt_z(const quat<T>&);                                  // component-wise reciprocal cubic root (set 0 for components that are 0)
template<typename T> PFC_INLINE typename math<T>::scalar_t norm(const quat<T>&);                  // quaternion norm (length): |q|
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm(const quat<T>&);                 // reciprocal of the quaternion norm: 1/|q|
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_z(const quat<T>&);               // reciprocal of the quaternion norm: 1/|q| (return 0 if |q|=0)
template<typename T> PFC_INLINE typename math<T>::scalar_t norm2(const quat<T>&);                 // squared quaternion norm: |q|^2
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2(const quat<T>&);                // reciprocal of the squared vector norm: 1/|q|^2
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2_z(const quat<T>&);              // reciprocal of the squared vector norm: 1/|q|^2 (return 0 if |q|=0)
template<typename T> PFC_INLINE quat<T> unit(const quat<T>&);                                     // unit quaternion of the quaternion: q/|q|
template<typename T> PFC_INLINE quat<T> unit_z(const quat<T>&);                                   // unit quaternion of the quaternion (if |q|=0, return q=[v=0, w=1])
template<typename T> PFC_INLINE typename math<T>::scalar_t dot(const quat<T>&, const quat<T>&);   // quaternion dot-product
template<typename T> PFC_INLINE typename math<T>::scalar_t dot1(const quat<T>&);                  // quaternion dot-product with quaternion [1, 1, 1, 1] (component sum)
template<typename T> PFC_INLINE quat<T> cross(const quat<T>&, const quat<T>&);                    // cross-product of quaternions (or odd/Grassman outer product): q=[v0 x v1, 0]
template<typename T> PFC_INLINE quat<T> outer(const quat<T>&, const quat<T>&);                    // Euclidean outer-product of quaternions: q=[w0*v1-w1*v0-(v0 x v1), 0]
template<typename T> PFC_INLINE quat<T> even(const quat<T>&, const quat<T>&);                     // even-product (Grassman inner product) of quaternions: q=[w0*v1+w1*v0, w0*w1-dot(v0, v1)]
template<typename T> PFC_INLINE quat<T> conj(const quat<T>&);                                     // conjugate of the quaternion
template<typename T> PFC_INLINE quat<T> inv(const quat<T>&);                                      // inverse of the quaternion
template<typename T> PFC_INLINE quat<T> inv_u(const quat<T>&);                                    // inverse of the unit quaternion
template<typename T> PFC_INLINE quat<T> exp(const quat<T>&);                                      // natural exponent of the quaternion
template<typename T> PFC_INLINE quat<T> exp_u(const quat<T>&);                                    // natural exponent of the unit quaternion
template<typename T> PFC_INLINE quat<T> ln(const quat<T>&);                                       // natural logarithm of the quaternion
template<typename T> PFC_INLINE quat<T> ln_u(const quat<T>&);                                     // natural logarithm of the unit quaternion
template<typename T> PFC_INLINE quat<T> pow(const quat<T>&, typename math<T>::scalar_t);          // rise quaternion to a power
template<typename T> PFC_INLINE quat<T> pow_u(const quat<T>&, typename math<T>::scalar_t);        // rise unit quaternion to a power
template<typename T> PFC_INLINE typename math<T>::scalar_t arg(const quat<T>&);                   // argument of the quaternion
template<typename T> PFC_INLINE typename math<T>::scalar_t arg_u(const quat<T>&);                 // argument of the unit quaternion
template<typename T> PFC_INLINE void neg(quat<T>&);                                               // negate the quaternion
template<typename T, class Rng> PFC_INLINE void rand_u(quat<T>&, Rng&);                           // random unit quaternion
template<typename T, class Rng> PFC_INLINE void rand_real1(quat<T>&, Rng&);                       // random quaternion where each component is in range [-1, 1]
template<typename T, class Rng> PFC_INLINE void rand_ureal1(quat<T>&, Rng&);                      // random quaternion where each component is in range [0, 1]
template<typename T> PFC_INLINE quat<T> smoothstep(const quat<T>&);                               // component-wise smoothstep function
template<typename T> PFC_INLINE quat<T> smootherstep(const quat<T>&);                             // component-wise smootherstep function
template<typename T> PFC_INLINE quat<T> lerp(const quat<T> &q0_,                                  // linear interpolation of quaternions: f(t=0)=v0, f(t=1)=v1
                                             const quat<T> &q1_,
                                             typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE quat<T> nlerp(const quat<T> &q0_,                                 // normalized linear quaternion interpolation: f(t=0)=q0/|q0|, f(t=1)=q1/|q1|
                                              const quat<T> &q1_,
                                              typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE quat<T> nlerp_z(const quat<T> &q0_,                               // normalized linear quaternion interpolation: f(t=0)=q0/|q0|, f(t=1)=q1/|q1|. if |q|=0, return q=[v=0, w=1]
                                                const quat<T> &q1_,
                                                typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE quat<T> slerp(const quat<T> &q0_,                                 // spherical linear quaternion interpolation: f(t=0)=q0, f(t=1)=q1
                                              const quat<T> &q1_,
                                              typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE quat<T> rot_u(const vec3<T> &src_, const vec3<T> &dst_);          // generate quaternion rotation from unit source direction to unit destination direction
template<typename T> PFC_INLINE quat<T> zrot_u(const vec3<T> &dst_);                              // generate quaternion rotation from z-direction to unit destination direction
template<typename T> PFC_INLINE quat<T> axis_rot(const vec3<T> &axis_,                            // generate quaternion rotation from axis and angle (radians)
                                                 typename math<T>::scalar_t angle_);
template<typename T> PFC_INLINE quat<T> axis_rot_u(const vec3<T> &axis_,                          // generate quaternion rotation from unit axis and angle (radians)
                                                   typename math<T>::scalar_t angle_);
template<typename T> void convert_u(mat33<T>&, const quat<T>&);                                   // convert unit quaternion to left handed row-major 3x3 rotation matrix
template<typename T> void convert(mat33<T>&, const quat<T>&);                                     // convert (possibly non-unit) quaternion to left handed row-major 3x3 rotation matrix
template<typename T> void convert(quat<T>&, const mat33<T>&);                                     // convert left handed row-major 3x3 rotation matrix to quaternion
template<typename T, typename U> PFC_INLINE quat<T> to_quat(const quat<U>&);                      // convert between quat types
template<unsigned shuffle_, typename T> PFC_INLINE quat<T> shuffle(const quat<T>&);               // shuffle quaternion components (e.g. shuffle<2311>(q_) == quatf(v_.z, v_.w, v_.y, v_.y))
template<typename T> PFC_INLINE void pack_u1(quat_32&, const quat<T>&);                           // pack quat (components in range [0, 1]) to 32-bit quat
template<typename T> PFC_INLINE void pack_s1(quat_32&, const quat<T>&);                           // pack quat (components in range [-1, 1]) to 32-bit quat
template<typename T> PFC_INLINE void unpack_u1(quat<T>&, const quat_32&);                         // unpack 32-bit quat to quat (components in range [0, 1])
template<typename T> PFC_INLINE void unpack_s1(quat<T>&, const quat_32&);                         // unpack 32-bit quat to quat (components in range [-1, 1])
template<typename T> PFC_INLINE const vec3<T> &vec(const quat<T>&);                               // vector component of the quaternion
template<typename T> PFC_INLINE vec3<T> &vec(quat<T>&);                                           // vector component of the quaternion
// complex number ops
template<typename T> PFC_INLINE bool is_zero(const complex<T>&);                                        // test of zero-complex number, i.e. all components equal zero (exact)
template<typename T> PFC_INLINE bool is_sat(const complex<T>&);                                         // test for saturated complex number, i.e. all components are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const complex<T>&);                                        // test for signed saturated complex number, i.e. all components are in range [-1, 1]
template<typename T> PFC_INLINE bool operator==(const complex<T>&, const complex<T>&);                  // test for equality of complex numbers, i.e. all components of the complex numbers are equal (exact)
template<typename T> PFC_INLINE bool operator==(const complex<T>&, typename math<T>::scalar_t);         // test for equality of complex number and scalar, i.e. all components of the complex number equals the scalar (exact)
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t, const complex<T>&);         // test for equality of complex number and scalar, i.e. all components of the complex number equals the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(const complex<T>&, const complex<T>&);                  // test for inequality of complex numbers, i.e. any of the components of the complex numbers are unequal (exact)
template<typename T> PFC_INLINE bool operator!=(const complex<T>&, typename math<T>::scalar_t);         // test for inequality of complex number and scalar, i.e. any of the components of the complex number is unequal to the scalar (exact)
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t, const complex<T>&);         // test for inequality of complex number and scalar, i.e. any of the components of the complex number is unequal to the scalar (exact)
template<typename T> PFC_INLINE complex<T> operator<(const complex<T>&, const complex<T>&);             // component-wise complex number less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE complex<T> operator<(const complex<T>&, typename math<T>::scalar_t);    // component-wise complex number less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE complex<T> operator<(typename math<T>::scalar_t, const complex<T>&);    // component-wise complex number less-than comparison (false=0, true=1)
template<typename T> PFC_INLINE complex<T> operator>(const complex<T>&, const complex<T>&);             // component-wise complex number greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE complex<T> operator>(const complex<T>&, typename math<T>::scalar_t);    // component-wise complex number greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE complex<T> operator>(typename math<T>::scalar_t, const complex<T>&);    // component-wise complex number greater-than comparison (false=0, true=1)
template<typename T> PFC_INLINE complex<T> operator<=(const complex<T>&, const complex<T>&);            // component-wise complex number less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE complex<T> operator<=(const complex<T>&, typename math<T>::scalar_t);   // component-wise complex number less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE complex<T> operator<=(typename math<T>::scalar_t, const complex<T>&);   // component-wise complex number less-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE complex<T> operator>=(const complex<T>&, const complex<T>&);            // component-wise complex number greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE complex<T> operator>=(const complex<T>&, typename math<T>::scalar_t);   // component-wise complex number greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE complex<T> operator>=(typename math<T>::scalar_t, const complex<T>&);   // component-wise complex number greater-or-equal comparison (false=0, true=1)
template<typename T> PFC_INLINE complex<T> sel_eq(const complex<T> &t0_, const complex<T> &t1_,         // component-wise equal complex number select (t0_==t1_?c0_:c1_)
                                                  const complex<T> &c0_, const complex<T> &c1_);
template<typename T> PFC_INLINE complex<T> sel_lt(const complex<T> &t0_, const complex<T> &t1_,         // component-wise less-than complex number select (t0_<t1_?c0_:c1_)
                                                  const complex<T> &c0_, const complex<T> &c1_);
template<typename T> PFC_INLINE complex<T> sel_le(const complex<T> &t0_, const complex<T> &t1_,         // component-wise less-or-equal complex number select (t0_<=t1_?c0_:c1_)
                                                  const complex<T> &c0_, const complex<T> &c1_);
template<typename T> PFC_INLINE complex<T> sel_eqz(const complex<T> &t_,                                // component-wise equal-to-zero complex number select (t_==0?c0_:c1_)
                                                   const complex<T> &c0_, const complex<T> &c1_);
template<typename T> PFC_INLINE complex<T> sel_ltz(const complex<T> &t_,                                // component-wise less-than-zero complex number select (t_<0?c0_:c1_)
                                                   const complex<T> &c0_, const complex<T> &c1_);
template<typename T> PFC_INLINE complex<T> sel_lez(const complex<T> &t_,                                // component-wise less-or-equal-to-zero complex number select (t_<=0?c0_:c1_)
                                                   const complex<T> &c0_, const complex<T> &c1_);
template<typename T> PFC_INLINE void operator+=(complex<T>&, const complex<T>&);                        // add complex number to complex number
template<typename T> PFC_INLINE void operator+=(complex<T>&, typename math<T>::scalar_t);               // add scalar to each component of the complex number
template<typename T> PFC_INLINE void operator-=(complex<T>&, const complex<T>&);                        // subtract complex number from complex number
template<typename T> PFC_INLINE void operator-=(complex<T>&, typename math<T>::scalar_t);               // subtract scalar from each component of the complex number
template<typename T> PFC_INLINE void operator*=(complex<T>&, const complex<T>&);                        // multiply complex number by complex number
template<typename T> PFC_INLINE void operator*=(complex<T>&, typename math<T>::scalar_t);               // multiply complex number by scalar
template<typename T> PFC_INLINE void operator/=(complex<T>&, typename math<T>::scalar_t);               // divide complex number by scalar
template<typename T> PFC_INLINE complex<T> operator+(const complex<T>&, const complex<T>&);             // add complex number to complex number
template<typename T> PFC_INLINE complex<T> operator+(const complex<T>&, typename math<T>::scalar_t);    // add scalar to each component of the complex number
template<typename T> PFC_INLINE complex<T> operator+(typename math<T>::scalar_t, const complex<T>&);    // add each component of the complex number to a scalar complex number
template<typename T> PFC_INLINE complex<T> operator-(const complex<T>&, const complex<T>&);             // subtract complex number from complex number
template<typename T> PFC_INLINE complex<T> operator-(const complex<T>&, typename math<T>::scalar_t);    // subtract scalar from each component of the complex number
template<typename T> PFC_INLINE complex<T> operator-(typename math<T>::scalar_t, const complex<T>&);    // subtract each component of the complex number from a scalar complex number
template<typename T> PFC_INLINE complex<T> operator-(const complex<T>&);                                // negate the complex number
template<typename T> PFC_INLINE complex<T> operator*(const complex<T>&, const complex<T>&);             // multiply complex number by complex number
template<typename T> PFC_INLINE complex<T> operator*(const complex<T>&, typename math<T>::scalar_t);    // complex number by scalar multiplication
template<typename T> PFC_INLINE complex<T> operator*(typename math<T>::scalar_t, const complex<T>&);    // complex number by scalar multiplication
template<typename T> PFC_INLINE complex<T> operator/(const complex<T>&, typename math<T>::scalar_t);    // complex number by scalar division
template<typename T> PFC_INLINE typename math<T>::scalar_t min(const complex<T>&);                      // minimum component value
template<typename T> PFC_INLINE complex<T> min(const complex<T>&, const complex<T>&);                   // component-wise minimum of the complex numbers
template<typename T> PFC_INLINE complex<T> min(const complex<T>&, const complex<T>&, const complex<T>&);
template<typename T> PFC_INLINE complex<T> min(const complex<T>&, const complex<T>&, const complex<T>&, const complex<T>&);
template<typename T> PFC_INLINE complex<T> min(const complex<T>&, typename math<T>::scalar_t);          // component-wise minimum of the complex number and scalar
template<typename T> PFC_INLINE complex<T> min(typename math<T>::scalar_t, const complex<T>&);          // component-wise minimum of the complex number and scalar
template<typename T> PFC_INLINE typename math<T>::scalar_t max(const complex<T>&);                      // maximum component value
template<typename T> PFC_INLINE complex<T> max(const complex<T>&, const complex<T>&);                   // component-wise maximum of the complex numbers
template<typename T> PFC_INLINE complex<T> max(const complex<T>&, const complex<T>&, const complex<T>&);
template<typename T> PFC_INLINE complex<T> max(const complex<T>&, const complex<T>&, const complex<T>&, const complex<T>&);
template<typename T> PFC_INLINE complex<T> max(const complex<T>&, typename math<T>::scalar_t);          // component-wise maximum of the complex number and scalar
template<typename T> PFC_INLINE complex<T> max(typename math<T>::scalar_t, const complex<T>&);          // component-wise maximum of the complex number and scalar
template<typename T> PFC_INLINE complex<T> mul(const complex<T> &c0_, const complex<T> &c1_);           // component-wise multiply: c0_*c1_
template<typename T> PFC_INLINE complex<T> madd(const complex<T> &c0_,                                  // component-wise multiply-add: c0_*c1+c2_
                                                const complex<T> &c1_,
                                                const complex<T> &c2_);
template<typename T> PFC_INLINE complex<T> madd(const complex<T> &c_,                                   // complex-scalar-scalar multiply-add: c_*mul_+add_
                                                typename math<T>::scalar_t mul_,
                                                typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE complex<T> madd(const complex<T> &c_,                                   // complex-complex-scalar multiply-add: c_*mul_+add_
                                                const complex<T> &mul_,
                                                typename math<T>::scalar_t add_);
template<typename T> PFC_INLINE complex<T> madd(const complex<T> &c_,                                   // complex-scalar-complex multiply-add: c_*mul_+add_
                                                typename math<T>::scalar_t mul_,
                                                const complex<T> &add_);
template<typename T> PFC_INLINE complex<T> rcp(const complex<T>&);                                      // component-wise complex number reciprocal
template<typename T> PFC_INLINE complex<T> rcp_z(const complex<T>&);                                    // component-wise complex number reciprocal (set 0 for 0 components)
template<typename T> PFC_INLINE complex<T> floor(const complex<T>&);                                    // component-wise greatest integer less than or equal to the value
template<typename T> PFC_INLINE complex<T> ceil(const complex<T>&);                                     // component-wise smallest integer greater than or equal to the value
template<typename T> PFC_INLINE complex<T> trunc(const complex<T>&);                                    // component-wise truncate decimal part from the value
template<typename T> PFC_INLINE complex<T> frc(const complex<T>&);                                      // component-wise fractional part (for negative values returns 1-fractional part)
template<typename T> PFC_INLINE complex<T> mod(const complex<T>&, typename math<T>::scalar_t div_);     // component-wise modulo
template<typename T> PFC_INLINE complex<T> cycle(const complex<T>&, typename math<T>::scalar_t cycle_); // component-wise cycle
template<typename T> PFC_INLINE complex<T> cycle1(const complex<T>&);                                   // component-wise cycle1
template<typename T> PFC_INLINE complex<T> sat(const complex<T>&);                                      // component-wise complex number saturate
template<typename T> PFC_INLINE complex<T> ssat(const complex<T>&);                                     // component-wise complex number signed saturate
template<typename T> PFC_INLINE complex<T> clamp(const complex<T>&,                                     // component-wise clamp of the complex number
                                                 const complex<T> &min_,
                                                 const complex<T> &max_);
template<typename T> PFC_INLINE complex<T> clamp(const complex<T>&,                                     // component-wise clamp of the complex number with scalars
                                                 typename math<T>::scalar_t min_,
                                                 typename math<T>::scalar_t max_);
template<typename T> PFC_INLINE complex<T> abs(const complex<T>&);                                      // component-wise complex number absolute
template<typename T> PFC_INLINE complex<T> sgn(const complex<T>&);                                      // component-wise signum (neg=-1, pos=+1, zero=0)
template<typename T> PFC_INLINE complex<T> sgn_zp(const complex<T>&);                                   // component-wise signum (neg=-1, pos&zero=+1)
template<typename T> PFC_INLINE complex<T> sqr(const complex<T>&);                                      // component-wise square: x*x
template<typename T> PFC_INLINE complex<T> cubic(const complex<T>&);                                    // component-wise cubic: x*x*x
template<typename T> PFC_INLINE complex<T> sqrt(const complex<T>&);                                     // component-wise complex number square root
template<typename T> PFC_INLINE complex<T> sqrt_z(const complex<T>&);                                   // component-wise complex number square root (set 0 for components less than zero)
template<typename T> PFC_INLINE complex<T> cbrt(const complex<T>&);                                     // component-wise cubic root
template<typename T> PFC_INLINE complex<T> rsqrt(const complex<T>&);                                    // component-wise complex number reciprocal square root
template<typename T> PFC_INLINE complex<T> rsqrt_z(const complex<T>&);                                  // component-wise complex number reciprocal square root (set 0 for components less than or equal to zero)
template<typename T> PFC_INLINE complex<T> rcbrt(const complex<T>&);                                    // component-wise reciprocal cubic root
template<typename T> PFC_INLINE complex<T> rcbrt_z(const complex<T>&);                                  // component-wise reciprocal cubic root (set 0 for components that are 0)
template<typename T> PFC_INLINE typename math<T>::scalar_t norm(const complex<T>&);                     // complex number norm (length): |c| 
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm(const complex<T>&);                    // reciprocal of the complex number norm: 1/|c|
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_z(const complex<T>&);                  // reciprocal of the complex number norm: 1/|c| (return 0 if |c|=0)
template<typename T> PFC_INLINE typename math<T>::scalar_t norm2(const complex<T>&);                    // squared complex number norm: |c|^2
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2(const complex<T>&);                   // reciprocal of the squared vector norm: 1/|c|^2
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2_z(const complex<T>&);                 // reciprocal of the squared vector norm: 1/|c|^2 (return 0 if |c|=0)
template<typename T> PFC_INLINE complex<T> unit(const complex<T>&);                                     // unit complex number of the complex number: c/|c| 
template<typename T> PFC_INLINE complex<T> unit_z(const complex<T>&);                                   // unit complex number of the complex number (if |c|=0, return c=[0, 0])
template<typename T> PFC_INLINE complex<T> conj(const complex<T>&);                                     // conjugate of the complex number
template<typename T> PFC_INLINE typename math<T>::scalar_t dot(const complex<T>&, const complex<T>&);   // complex number dot-product
template<typename T> PFC_INLINE typename math<T>::scalar_t dot1(const complex<T>&);                     // complex number dot-product with complex number [1, 1] (component sum)
template<typename T> PFC_INLINE typename math<T>::scalar_t arg(const complex<T>&);                      // argument of the complex number
template<typename T> PFC_INLINE void neg(complex<T>&);                                                  // negate the complex number
template<typename T, class Rng> PFC_INLINE void rand_u(complex<T>&, Rng&);                              // random unit complex number
template<typename T, class Rng> PFC_INLINE void rand_real1(complex<T>&, Rng&);                          // random complex number where each component is in range [-1, 1]
template<typename T, class Rng> PFC_INLINE void rand_ureal1(complex<T>&, Rng&);                         // random complex number where each component is in range [0, 1]
template<typename T> PFC_INLINE complex<T> smoothstep(const complex<T>&);                               // component-wise smoothstep function
template<typename T> PFC_INLINE complex<T> smootherstep(const complex<T>&);                             // component-wise smootherstep function
template<typename T> PFC_INLINE complex<T> lerp(const complex<T> &c0_,                                  // linear interpolation of complex numbers: f(t=0)=c0, f(t=1)=c1 
                                                const complex<T> &c1_,
                                                typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE complex<T> nlerp(const complex<T> &c0_,                                 // normalized linear complex number interpolation: f(t=0)=c0/|c0|, f(t=1)=c1/|c1|
                                                 const complex<T> &c1_,
                                                 typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE complex<T> nlerp_z(const complex<T> &c0_,                               // normalized linear complex number interpolation: f(t=0)=c0/|c0|, f(t=1)=c1/|c1|. if |c|=0, return c=[0, 0]
                                                   const complex<T> &c1_,
                                                   typename math<T>::scalar_t t_);
template<typename T, typename U> PFC_INLINE complex<T> to_complex(const complex<U>&);                   // convert between complex number types
template<unsigned shuffle_, typename T> PFC_INLINE complex<T> shuffle(const complex<T>&);               // shuffle complex components (e.g. shuffle<11>(c_) == complexf(v_.y, v_.y))
//----------------------------------------------------------------------------


//============================================================================
// math constants
//============================================================================
template<typename T>
struct math
{
  // pi variants
  static const T pi;          // 3.14159265358979323846 
  static const T quarter_pi;  // 0.25*3.14159265358979323846
  static const T half_pi;     // 0.5*3.14159265358979323846
  static const T two_pi;      // 2.0*3.14159265358979323846
  static const T four_pi;     // 4.0*3.14159265358979323846
  static const T rpi;         // 1.0/3.14159265358979323846 
  static const T quarter_rpi; // 0.25/3.14159265358979323846
  static const T half_rpi;    // 0.5/3.14159265358979323846
  static const T two_rpi;     // 2.0/3.14159265358979323846
  // square root variants
  static const T sqrt2;       // 1.4142135623730950488016887242097
  static const T sqrt3;       // 1.7320508075688772935274463415059
  static const T rsqrt2;      // 1.0/1.4142135623730950488016887242097
  static const T rsqrt3;      // 1.0/1.7320508075688772935274463415059
  // angle conversion factors
  static const T deg_to_rad;  // 0.01745329251994329577
  static const T rad_to_deg;  // 57.29577951308232087680
  // type definitions
  typedef T scalar_t;
};
//----

// partial specializations for basic math components
template<typename T> struct math<vec2<T> >:math<T>    {};
template<typename T> struct math<vec3<T> >:math<T>    {};
template<typename T> struct math<vec4<T> >:math<T>    {};
template<typename T> struct math<mat22<T> >:math<T>   {};
template<typename T> struct math<mat33<T> >:math<T>   {};
template<typename T> struct math<mat44<T> >:math<T>   {};
template<typename T> struct math<quat<T> >:math<T>    {};
template<typename T> struct math<complex<T> >:math<T> {};
//----------------------------------------------------------------------------


//============================================================================
// vec2
//============================================================================
template<typename T>
struct vec2
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {dim=2};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE vec2();
  PFC_INLINE vec2(T s_);
  PFC_INLINE vec2(T x_, T y_);
  PFC_INLINE vec2(const vec3<T>&);
  PFC_INLINE vec2(const T*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const T &operator[](unsigned idx_) const;
  PFC_INLINE T &operator[](unsigned idx_);
  PFC_INLINE void set(T s_);
  PFC_INLINE void set(T x_, T y_);
  PFC_INLINE void set(const vec2<T>&);
  PFC_INLINE void set(const vec3<T>&);
  PFC_INLINE void set(const T*);
  //--------------------------------------------------------------------------

  static const vec2 s_zero;
  static const vec2 s_one;
  static const vec2 s_neg_one;
  T x, y;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, vec2<T>, is_type_vec, true);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, vec2<T>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, vec2<T>, is_type_pod_stream, is_type_pod_stream<T>::res);
//----------------------------------------------------------------------------


//============================================================================
// vec3
//============================================================================
template<typename T>
struct vec3
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {dim=3};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE vec3();
  PFC_INLINE vec3(T s_);
  PFC_INLINE vec3(T x_, T y_, T z_);
  PFC_INLINE vec3(const vec2<T>&, T z_);
  PFC_INLINE vec3(const vec4<T>&);
  PFC_INLINE vec3(const T*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const T &operator[](unsigned idx_) const;
  PFC_INLINE T &operator[](unsigned idx_);
  PFC_INLINE void set(T s_);
  PFC_INLINE void set(T x_, T y_, T z_);
  PFC_INLINE void set(const vec2<T>&, T z_);
  PFC_INLINE void set(const vec3<T>&);
  PFC_INLINE void set(const vec4<T>&);
  PFC_INLINE void set(const T*);
  //--------------------------------------------------------------------------

  static const vec3 s_zero;
  static const vec3 s_one;
  static const vec3 s_neg_one;
  T x, y, z;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, vec3<T>, is_type_vec, true);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, vec3<T>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, vec3<T>, is_type_pod_stream, is_type_pod_stream<T>::res);
//----------------------------------------------------------------------------


//============================================================================
// vec3<vec32_t>
//============================================================================
template<>
struct vec3<vec32_t>
{
  typedef vec32_t type_t;
  typedef uint8_t scalar_t;
  enum {dim=3};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE vec3();
  PFC_INLINE vec3(uint8_t s_);
  PFC_INLINE vec3(uint8_t x_, uint8_t y_, uint8_t z_);
  PFC_INLINE vec3(const vec2<uint8_t>&, uint8_t z_);
  PFC_INLINE vec3(const uint8_t*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const uint8_t &operator[](unsigned idx_) const;
  PFC_INLINE uint8_t &operator[](unsigned idx_);
  PFC_INLINE void set(uint8_t s_);
  PFC_INLINE void set(uint8_t x_, uint8_t y_, uint8_t z_);
  PFC_INLINE void set(const vec2<uint8_t>&, uint8_t z_);
  PFC_INLINE void set(const vec3<vec32_t>&);
  PFC_INLINE void set(const uint8_t*);
  //--------------------------------------------------------------------------

  static const vec3 s_zero;
  static const vec3 s_one;
  static const vec3 s_neg_one;
  PFC_ALIGN(4) uint8_t x;
  uint8_t y, z, dummy;
};
PFC_SET_TYPE_TRAIT(vec3<vec32_t>, is_type_pod, true);
PFC_SET_TYPE_TRAIT(vec3<vec32_t>, is_type_pod_stream, false);
//----------------------------------------------------------------------------


//============================================================================
// vec4
//============================================================================
template<typename T>
struct vec4
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {dim=4};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE vec4();
  PFC_INLINE vec4(T s_);
  PFC_INLINE vec4(T x_, T y_, T z_, T w_);
  PFC_INLINE vec4(const vec3<T>&, T w_);
  PFC_INLINE vec4(const T*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const T &operator[](unsigned idx_) const;
  PFC_INLINE T &operator[](unsigned idx_);
  PFC_INLINE void set(T s_);
  PFC_INLINE void set(T x_, T y_, T z_, T w_);
  PFC_INLINE void set(const vec3<T>&, T w_);
  PFC_INLINE void set(const vec4<T>&);
  PFC_INLINE void set(const T*);
  //--------------------------------------------------------------------------

  static const vec4 s_zero;
  static const vec4 s_one;
  static const vec4 s_neg_one;
  T x, y, z, w;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, vec4<T>, is_type_vec, true);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, vec4<T>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, vec4<T>, is_type_pod_stream, is_type_pod_stream<T>::res);
//----------------------------------------------------------------------------


//============================================================================
// vec4<vec32_t>
//============================================================================
template<>
struct vec4<vec32_t>
{
  typedef vec32_t type_t;
  typedef uint8_t scalar_t;
  enum {dim=4};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE vec4();
  PFC_INLINE vec4(uint8_t s_);
  PFC_INLINE vec4(uint8_t x_, uint8_t y_, uint8_t z_, uint8_t w_);
  PFC_INLINE vec4(const vec3<vec32_t>&, uint8_t w_);
  PFC_INLINE vec4(const uint8_t*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const uint8_t &operator[](unsigned idx_) const;
  PFC_INLINE uint8_t &operator[](unsigned idx_);
  PFC_INLINE void set(uint8_t s_);
  PFC_INLINE void set(uint8_t x_, uint8_t y_, uint8_t z_, uint8_t w_);
  PFC_INLINE void set(const vec3<vec32_t>&, uint8_t w_);
  PFC_INLINE void set(const vec4<vec32_t>&);
  PFC_INLINE void set(const uint8_t*);
  //--------------------------------------------------------------------------

  static const vec4 s_zero;
  static const vec4 s_one;
  static const vec4 s_neg_one;
  PFC_ALIGN(4) uint8_t x;
  uint8_t y, z, w;
};
PFC_SET_TYPE_TRAIT(vec4<vec32_t>, is_type_pod, true);
PFC_SET_TYPE_TRAIT(vec4<vec32_t>, is_type_pod_stream, true);
//----------------------------------------------------------------------------


//============================================================================
// mat22
//============================================================================
template<typename T>
struct mat22
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {dim_rows=2, dim_columns=2};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE mat22();
  PFC_INLINE mat22(T s_);
  PFC_INLINE mat22(T d0_, T d1_);
  PFC_INLINE mat22(T m00_, T m01_,
                   T m10_, T m11_);
  PFC_INLINE mat22(const vec2<T> &diag_);
  PFC_INLINE mat22(const vec2<T> &row0_,
                   const vec2<T> &row1_);
  PFC_INLINE mat22(const mat33<T>&);
  PFC_INLINE mat22(const T*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const vec2<T> &operator[](unsigned row_) const;
  PFC_INLINE vec2<T> &operator[](unsigned row_);
  PFC_INLINE void set(T s_);
  PFC_INLINE void set(T d0_, T d1_);
  PFC_INLINE void set(T m00_, T m01_,
                      T m10_, T m11_);
  PFC_INLINE void set(const vec2<T> &row0_,
                      const vec2<T> &row1_);
  PFC_INLINE void set(const mat22<T>&);
  PFC_INLINE void set(const mat33<T>&);
  PFC_INLINE void set(const T*);
  //--------------------------------------------------------------------------

  static const mat22 s_zero;
  static const mat22 s_one;
  static const mat22 s_neg_one;
  static const mat22 s_identity;
  vec2<T> x;
  vec2<T> y;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, mat22<T>, is_type_mat, true);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, mat22<T>, is_type_pod, is_type_pod<vec2<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, mat22<T>, is_type_pod_stream, is_type_pod_stream<vec2<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// mat33
//============================================================================
template<typename T>
struct mat33
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {dim_rows=3, dim_columns=3};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE mat33();
  PFC_INLINE mat33(T s_);
  PFC_INLINE mat33(T d0_, T d1_, T d2_);
  PFC_INLINE mat33(T m00_, T m01_, T m02_,
                   T m10_, T m11_, T m12_,
                   T m20_, T m21_, T m22_);
  PFC_INLINE mat33(const vec3<T> &diag_);
  PFC_INLINE mat33(const vec3<T> &row0_,
                   const vec3<T> &row1_,
                   const vec3<T> &row2_);
  PFC_INLINE mat33(const mat22<T>&);
  PFC_INLINE mat33(const mat44<T>&);
  PFC_INLINE mat33(const T*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const vec3<T> &operator[](unsigned row_) const;
  PFC_INLINE vec3<T> &operator[](unsigned row_);
  PFC_INLINE void set(T s_);
  PFC_INLINE void set(T d0_, T d1_, T d2_);
  PFC_INLINE void set(T m00_, T m01_, T m02_,
                      T m10_, T m11_, T m12_,
                      T m20_, T m21_, T m22_);
  PFC_INLINE void set(const vec3<T> &row0_,
                      const vec3<T> &row1_,
                      const vec3<T> &row2_);
  PFC_INLINE void set(const mat22<T>&);
  PFC_INLINE void set(const mat33<T>&);
  PFC_INLINE void set(const mat44<T>&);
  PFC_INLINE void set(const T*);
  //--------------------------------------------------------------------------

  static const mat33 s_zero;
  static const mat33 s_one;
  static const mat33 s_neg_one;
  static const mat33 s_identity;
  vec3<T> x;
  vec3<T> y;
  vec3<T> z;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, mat33<T>, is_type_mat, true);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, mat33<T>, is_type_pod, is_type_pod<vec3<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, mat33<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// mat44
//============================================================================
template<typename T>
struct mat44
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {dim_rows=4, dim_columns=4};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE mat44();
  PFC_INLINE mat44(T s_);
  PFC_INLINE mat44(T d0_, T d1_, T d2_, T d3_);
  PFC_INLINE mat44(T m00_, T m01_, T m02_, T m03_,
                   T m10_, T m11_, T m12_, T m13_,
                   T m20_, T m21_, T m22_, T m23_,
                   T m30_, T m31_, T m32_, T m33_);
  PFC_INLINE mat44(const vec4<T> &diag_);
  PFC_INLINE mat44(const vec4<T> &row0_,
                   const vec4<T> &row1_,
                   const vec4<T> &row2_,
                   const vec4<T> &row3_);
  PFC_INLINE mat44(const mat33<T>&);
  PFC_INLINE mat44(const T*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const vec4<T> &operator[](unsigned row_) const;
  PFC_INLINE vec4<T> &operator[](unsigned row_);
  PFC_INLINE void set(T s_);
  PFC_INLINE void set(T d0_, T d1_, T d2_, T d3_);
  PFC_INLINE void set(T m00_, T m01_, T m02_, T m03_,
                      T m10_, T m11_, T m12_, T m13_,
                      T m20_, T m21_, T m22_, T m23_,
                      T m30_, T m31_, T m32_, T m33_);
  PFC_INLINE void set(const vec4<T> &row0_,
                      const vec4<T> &row1_,
                      const vec4<T> &row2_,
                      const vec4<T> &row3_);
  PFC_INLINE void set(const mat33<T>&);
  PFC_INLINE void set(const mat44<T>&);
  PFC_INLINE void set(const T*);
  //--------------------------------------------------------------------------

  static const mat44 s_zero;
  static const mat44 s_one;
  static const mat44 s_neg_one;
  static const mat44 s_identity;
  vec4<T> x;
  vec4<T> y;
  vec4<T> z;
  vec4<T> w;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, mat44<T>, is_type_mat, true);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, mat44<T>, is_type_pod, is_type_pod<vec4<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, mat44<T>, is_type_pod_stream, is_type_pod_stream<vec4<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// quat
//============================================================================
template<typename T>
struct quat
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {dim=4};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE quat();
  PFC_INLINE quat(T s_);
  PFC_INLINE quat(T x_, T y_, T z_, T w_);
  PFC_INLINE quat(const vec3<T>&);
  PFC_INLINE quat(const vec3<T>&, T w_);
  PFC_INLINE quat(const vec4<T>&);
  PFC_INLINE quat(const T*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const T &operator[](unsigned idx_) const;
  PFC_INLINE T &operator[](unsigned idx_);
  PFC_INLINE void set(T s_);
  PFC_INLINE void set(T x_, T y_, T z_, T w_);
  PFC_INLINE void set(const vec3<T>&);
  PFC_INLINE void set(const vec3<T>&, T w_);
  PFC_INLINE void set(const vec4<T>&);
  PFC_INLINE void set(const quat<T>&);
  PFC_INLINE void set(const T*);
  //--------------------------------------------------------------------------

  static const quat s_zero;
  static const quat s_one;
  static const quat s_neg_one;
  static const quat s_identity;
  T x, y, z, w;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, quat<T>, is_type_quat, true);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, quat<T>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, quat<T>, is_type_pod_stream, is_type_pod_stream<T>::res);
//----------------------------------------------------------------------------


//============================================================================
// quat
//============================================================================
template<>
struct quat<vec32_t>
{
  typedef vec32_t type_t;
  typedef uint8_t scalar_t;
  enum {dim=4};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE quat();
  PFC_INLINE quat(uint8_t s_);
  PFC_INLINE quat(uint8_t x_, uint8_t y_, uint8_t z_, uint8_t w_);
  PFC_INLINE quat(const vec3<vec32_t>&);
  PFC_INLINE quat(const vec3<vec32_t>&, uint8_t w_);
  PFC_INLINE quat(const vec4<vec32_t>&);
  PFC_INLINE quat(const uint8_t*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const uint8_t &operator[](unsigned idx_) const;
  PFC_INLINE uint8_t &operator[](unsigned idx_);
  PFC_INLINE void set(uint8_t s_);
  PFC_INLINE void set(uint8_t x_, uint8_t y_, uint8_t z_, uint8_t w_);
  PFC_INLINE void set(const vec3<vec32_t>&);
  PFC_INLINE void set(const vec3<vec32_t>&, uint8_t w_);
  PFC_INLINE void set(const vec4<vec32_t>&);
  PFC_INLINE void set(const quat<vec32_t>&);
  PFC_INLINE void set(const uint8_t*);
  //--------------------------------------------------------------------------

  static const quat s_zero;
  static const quat s_one;
  static const quat s_neg_one;
  static const quat s_identity;
  PFC_ALIGN(4) uint8_t x;
  uint8_t y, z, w;
};
PFC_SET_TYPE_TRAIT(quat<vec32_t>, is_type_pod, true);
PFC_SET_TYPE_TRAIT(quat<vec32_t>, is_type_pod_stream, true);
//----------------------------------------------------------------------------


//============================================================================
// complex
//============================================================================
template<typename T>
struct complex
{
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {dim=2};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE complex();
  PFC_INLINE complex(T s_);
  PFC_INLINE complex(T real_, T imag_);
  PFC_INLINE complex(const T*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const T &operator[](unsigned idx_) const;
  PFC_INLINE T &operator[](unsigned idx_);
  PFC_INLINE void set(T s_);
  PFC_INLINE void set(T real_, T imag_);
  PFC_INLINE void set(const complex<T>&);
  PFC_INLINE void set(const T*);
  //--------------------------------------------------------------------------

  static const complex s_zero;
  static const complex s_one;
  static const complex s_neg_one;
  T real, imag;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, complex<T>, is_type_complex, true);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, complex<T>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, complex<T>, is_type_pod_stream, is_type_pod_stream<T>::res);
//----------------------------------------------------------------------------

//============================================================================
#include "math.inl"
} // namespace pfc
#endif
