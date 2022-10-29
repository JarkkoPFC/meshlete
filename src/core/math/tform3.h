//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_TFORM3_H
#define PFC_CORE_MATH_TFORM3_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "prim3/prim3.h"
namespace pfc
{

// new
template<typename> struct tform3;
typedef tform3<float> tform3f;
typedef tform3<double> tform3d;
template<typename> struct tform_rt3;
typedef tform_rt3<float> tform_rt3f;
typedef tform_rt3<double> tform_rt3d;
template<typename> class camera;
typedef camera<float> cameraf;
typedef camera<double> camerad;
// compressed rotations
template<class Storage> class compressed_rotation_spi;
template<class Storage> class compressed_rotation_oct;
struct compressed_rotation_storage_24;
struct compressed_rotation_storage_32;
typedef compressed_rotation_spi<compressed_rotation_storage_24> compressed_rotation_spi24;  // max error (degrees): axis=0.509373, angle=0.703127
typedef compressed_rotation_oct<compressed_rotation_storage_24> compressed_rotation_oct24;  // max error (degrees): axis=0.550364, angle=0.703127
typedef compressed_rotation_spi<compressed_rotation_storage_32> compressed_rotation_spi32;  // max error (degrees): axis=0.094873, angle=0.087891
typedef compressed_rotation_oct<compressed_rotation_storage_32> compressed_rotation_oct32;  // max error (degrees): axis=0.128204, angle=0.087891
// tform3 operations
template<typename T> PFC_INLINE bool is_zero(const tform3<T>&);                                      // test for zero-transform, i.e. all components equal zero (exact)
template<typename T> PFC_INLINE bool is_orthogonal(const tform3<T>&);                                // test for orthogonal transform
template<typename T> PFC_INLINE bool is_sat(const tform3<T>&);                                       // test for saturated transform, i.e. all components are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const tform3<T>&);                                      // test for signed saturated transform, i.e. all components are in range [-1, 1]
template<typename T> PFC_INLINE bool operator==(const tform3<T>&, const tform3<T>&);                 // test for equality of transforms, i.e. all components of transforms are equal (exact)
template<typename T> PFC_INLINE bool operator!=(const tform3<T>&, const tform3<T>&);                 // test for inequality of transforms, i.e. any of the components of the transforms are unequal (exact)
template<typename T> PFC_INLINE void operator+=(tform3<T>&, const tform3<T>&);                       // add transform to transform
template<typename T> PFC_INLINE void operator-=(tform3<T>&, const tform3<T>&);                       // subtract transform from transform
template<typename T> PFC_INLINE void operator*=(tform3<T>&, const tform3<T>&);                       // multiply transform by transform
template<typename T> PFC_INLINE void operator*=(tform3<T>&, const quat<T>&);                         // multiply transform by quaternion
template<typename T> PFC_INLINE void operator*=(tform3<T>&, const mat33<T>&);                        // multiply transform by matrix
template<typename T> PFC_INLINE void operator*=(tform3<T>&, typename math<T>::scalar_t);             // multiply transform by scalar
template<typename T> PFC_INLINE void operator*=(vec3<T>&, const tform3<T>&);                         // multiply 3d vector by transform (assume w=1)
template<typename T> PFC_INLINE void operator*=(vec4<T>&, const tform3<T>&);                         // multiply 4d vector by transform
template<typename T> PFC_INLINE void operator*=(mat44<T>&, const tform3<T>&);                        // multiply 4x4 matrix by transform
template<typename T> PFC_INLINE void operator/=(tform3<T>&, typename math<T>::scalar_t);             // divide transform by scalar
template<typename T> PFC_INLINE tform3<T> operator+(const tform3<T>&, const tform3<T>&);             // add transform to transform
template<typename T> PFC_INLINE tform3<T> operator-(const tform3<T>&, const tform3<T>&);             // subtract transform from transform
template<typename T> PFC_INLINE tform3<T> operator-(const tform3<T>&);                               // negate the transform
template<typename T> PFC_INLINE tform3<T> operator*(const tform3<T>&, const tform3<T>&);             // multiply transform by transform
template<typename T> PFC_INLINE tform3<T> operator*(const tform3<T>&, const quat<T>&);               // multiply transform by quaternion
template<typename T> PFC_INLINE tform3<T> operator*(const tform3<T>&, const mat33<T>&);              // multiply transform by matrix
template<typename T> PFC_INLINE tform3<T> operator*(const tform3<T>&, typename math<T>::scalar_t);   // multiply transform by scalar
template<typename T> PFC_INLINE tform3<T> operator*(typename math<T>::scalar_t, const tform3<T>&);   // multiply transform by scalar
template<typename T> PFC_INLINE vec3<T> operator*(const vec3<T>&, const tform3<T>&);                 // multiply 3d vector by transform (assume w=1)
template<typename T> PFC_INLINE vec4<T> operator*(const vec4<T>&, const tform3<T>&);                 // multiply 4d vector by transform
template<typename T> PFC_INLINE vec3<T> operator*(const tform3<T>&, const vec3<T>&);                 // multiply transform by transposed 3d vector (assume w=1)
template<typename T> PFC_INLINE vec4<T> operator*(const tform3<T>&, const vec4<T>&);                 // multiply transform by transposed 4d vector
template<typename T> PFC_INLINE mat44<T> operator*(const mat44<T>&, const tform3<T>&);               // multiply 4x4 matrix by transform
template<typename T> PFC_INLINE mat44<T> operator*(const tform3<T>&, const mat44<T>&);               // multiply transform by 4x4 matrix
template<typename T> PFC_INLINE tform3<T> operator/(const tform3<T>&, typename math<T>::scalar_t);   // divide transform by scalar
template<typename T> PFC_INLINE tform3<T> madd(const tform3<T> &t0_,                                 // component-wise multiply-add: t0_*t1+t2_
                                               const tform3<T> &t1_,
                                               const tform3<T> &t2_);
template<typename T> PFC_INLINE typename math<T>::scalar_t det(const tform3<T>&);                    // determinant of the transform
template<typename T> PFC_INLINE tform3<T> inv(const tform3<T>&, typename math<T>::scalar_t *det_=0); // inverse of the transform
template<typename T> PFC_INLINE typename math<T>::scalar_t tr(const tform3<T>&);                     // trace of the transform
template<typename T> PFC_INLINE void identity(tform3<T>&);                                           // set transform to identity
template<typename T> PFC_INLINE void transpose_matrix33(tform3<T>&);                                 // transpose the 3x3 upper-left matrix of the transform
template<typename T> PFC_INLINE void transpose_matrix33(tform3<T>&, const tform3<T>&);               // transpose the 3x3 upper-left matrix of the transform
template<typename T> PFC_INLINE void neg(tform3<T>&);                                                // negate the transform
template<typename T> PFC_INLINE tform3<T> lerp(const tform3<T> &t0_,                                 // linear interpolation of transforms: f(t=0)=t0, f(t=1)=t1
                                               const tform3<T> &t1_,
                                               typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE void lerp(tform3<T> &tr_,                                            // linear interpolation of transforms: f(t=0)=t0, f(t=1)=t1
                                          const tform3<T> &t0_,
                                          const tform3<T> &t1_,
                                          typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE void zrot_u(tform3<T>&,                                              // setup transform from position and z-axis direction
                                            const vec3<T> &pos_,
                                            const vec3<T> &zdir_);
template<typename T> PFC_INLINE void zrot_u(tform3<T>&,                                              // setup transform from position, z-axis direction and up-vector
                                            const vec3<T> &pos_,
                                            const vec3<T> &zdir_,
                                            const vec3<T> &up_);
template<typename T> PFC_INLINE void axis_rot(tform3<T>&,                                            // setup transform from position and rotation about given axis
                                              const vec3<T> &pos_,
                                              const vec3<T> &axis_,
                                              typename math<T>::scalar_t angle_);
template<typename T> PFC_INLINE void axis_rot_u(tform3<T>&,                                          // setup transform from position and rotation about given unit axis
                                                const vec3<T> &pos_,
                                                const vec3<T> &axis_,
                                                typename math<T>::scalar_t angle_);
template<typename T, typename U> PFC_INLINE tform3<T> to_tform3(const tform3<U>&);                   // convert between tform3 types
template<typename T> PFC_INLINE void orthonormalize(tform3<T>&);                                     // ortho-normalize the transform
// tform_rt3 operations
template<typename T> PFC_INLINE bool is_zero(const tform_rt3<T>&);                                       // test for zero-transform, i.e. all components equal zero (exact)
template<typename T> PFC_INLINE bool is_sat(const tform3<T>&);                                           // test for saturated transform, i.e. all components are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const tform3<T>&);                                          // test for signed saturated transform, i.e. all components are in range [-1, 1]
template<typename T> PFC_INLINE bool operator==(const tform_rt3<T>&, const tform_rt3<T>&);               // test for equality of transforms, i.e. all components of transforms are equal (exact)
template<typename T> PFC_INLINE bool operator!=(const tform_rt3<T>&, const tform_rt3<T>&);               // test for inequality of transforms, i.e. any of the components of the transforms are unequal (exact)
template<typename T> PFC_INLINE void operator+=(tform_rt3<T>&, const tform_rt3<T>&);                     // add transform to transform
template<typename T> PFC_INLINE void operator-=(tform_rt3<T>&, const tform_rt3<T>&);                     // subtract transform from transform
template<typename T> PFC_INLINE void operator*=(tform_rt3<T>&, const tform_rt3<T>&);                     // multiply transform by transform
template<typename T> PFC_INLINE void operator*=(tform_rt3<T>&, const quat<T>&);                          // multiply transform by quaternion
template<typename T> PFC_INLINE void operator*=(tform_rt3<T>&, typename math<T>::scalar_t);              // multiply transform by scalar
template<typename T> PFC_INLINE void operator*=(vec3<T>&, const tform_rt3<T>&);                          // multiply 3d vector by transform (assume w=1)
template<typename T> PFC_INLINE void operator*=(vec4<T>&, const tform_rt3<T>&);                          // multiply 4d vector by transform
template<typename T> PFC_INLINE void operator*=(mat44<T>&, const tform_rt3<T>&);                         // multiply 4x4 matrix by transform
template<typename T> PFC_INLINE void operator/=(tform_rt3<T>&, typename math<T>::scalar_t);              // divide transform by scalar
template<typename T> PFC_INLINE tform_rt3<T> operator+(const tform_rt3<T>&, const tform_rt3<T>&);        // add transform to transform
template<typename T> PFC_INLINE tform_rt3<T> operator-(const tform_rt3<T>&, const tform_rt3<T>&);        // subtract transform from transform
template<typename T> PFC_INLINE tform_rt3<T> operator-(const tform_rt3<T>&);                             // negate the transform
template<typename T> PFC_INLINE tform_rt3<T> operator*(const tform_rt3<T>&, const tform_rt3<T>&);        // multiply transform by transform
template<typename T> PFC_INLINE tform_rt3<T> operator*(const tform_rt3<T>&, const quat<T>&);             // multiply transform by quaternion
template<typename T> PFC_INLINE tform_rt3<T> operator*(const tform_rt3<T>&, typename math<T>::scalar_t); // multiply transform by scalar
template<typename T> PFC_INLINE tform_rt3<T> operator*(typename math<T>::scalar_t, const tform_rt3<T>&); // multiply transform by scalar
template<typename T> PFC_INLINE vec3<T> operator*(const vec3<T>&, const tform_rt3<T>&);                  // multiply 3d vector by transform (assume w=1)
template<typename T> PFC_INLINE vec4<T> operator*(const vec4<T>&, const tform_rt3<T>&);                  // multiply 4d vector by transform
template<typename T> PFC_INLINE vec3<T> operator*(const tform_rt3<T>&, const vec3<T>&);                  // multiply transform by transposed 3d vector (assume w=1)
template<typename T> PFC_INLINE vec4<T> operator*(const tform_rt3<T>&, const vec4<T>&);                  // multiply transform by transposed 4d vector
template<typename T> PFC_INLINE mat44<T> operator*(const mat44<T>&, const tform_rt3<T>&);                // multiply 4x4 matrix by transform
template<typename T> PFC_INLINE mat44<T> operator*(const tform_rt3<T>&, const mat44<T>&);                // multiply transform by 4x4 matrix
template<typename T> PFC_INLINE tform_rt3<T> operator/(const tform_rt3<T>&, typename math<T>::scalar_t); // divide transform by scalar
template<typename T> PFC_INLINE tform_rt3<T> madd(const tform_rt3<T> &t0_,                               // component-wise multiply-add: t0_*t1+t2_
                                                  const tform_rt3<T> &t1_,
                                                  const tform_rt3<T> &t2_);
template<typename T> PFC_INLINE tform_rt3<T> inv(const tform_rt3<T>&);                                   // inverse of the transform
template<typename T> PFC_INLINE void identity(tform_rt3<T>&);                                            // set transform to identity
template<typename T> PFC_INLINE void neg(tform_rt3<T>&);                                                 // negate the transform
template<typename T> PFC_INLINE tform_rt3<T> lerp(const tform_rt3<T> &t0_,                               // linear interpolation of transforms: f(t=0)=t0, f(t=1)=t1
                                                  const tform_rt3<T> &t1_,
                                                  typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE tform_rt3<T> nlerp(const tform_rt3<T> &t0_,                              // linear interpolation of transforms with normalized rotation
                                                   const tform_rt3<T> &t1_,
                                                   typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE tform_rt3<T> nlerp_z(const tform_rt3<T> &t0_,                            // linear interpolation of transforms with normalized rotation, if |rotation|=0, rotation=[0, 0, 0, 1]
                                                     const tform_rt3<T> &t1_,
                                                     typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE tform_rt3<T> slerp(const tform_rt3<T> &t0_,                              // linear interpolation of translation with spherical rotation interpolation
                                                   const tform_rt3<T> &t1_,
                                                   typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE void zrot_u(tform_rt3<T>&,                                               // setup transform from position and z-axis direction
                                            const vec3<T> &pos_,
                                            const vec3<T> &zdir_);
template<typename T> PFC_INLINE void axis_rot(tform_rt3<T>&,                                             // setup transform from position and rotation about given axis
                                              const vec3<T> &pos_,
                                              const vec3<T> &axis_,
                                              typename math<T>::scalar_t angle_);
template<typename T> PFC_INLINE void axis_rot_u(tform_rt3<T>&,                                           // setup transform from position and rotation about given unit axis
                                                const vec3<T> &pos_,
                                                const vec3<T> &axis_,
                                                typename math<T>::scalar_t angle_);
template<typename T, typename U> PFC_INLINE tform_rt3<T> to_tform_rt3(const tform_rt3<U>&);              // convert between tform_rt3 types
// camera operations
template<typename T, typename U> PFC_INLINE camera<T> to_camera(const camera<U>&);                       // convert between camera types
// projection matrix setup
template<typename T> mat44<T> perspective_matrix(typename math<T>::scalar_t fov_width_, typename math<T>::scalar_t aspect_ratio_, typename math<T>::scalar_t near_, typename math<T>::scalar_t far_, bool reversed_=false);
template<typename T> mat44<T> orthogonal_matrix(typename math<T>::scalar_t width_, typename math<T>::scalar_t aspect_ratio_, typename math<T>::scalar_t near_, typename math<T>::scalar_t far_, bool reversed_=false);
template<typename T> PFC_INLINE typename math<T>::scalar_t fov_width(const mat44<T> &v2p_);  // return fov width angle from view->projection matrix
template<typename T> PFC_INLINE typename math<T>::scalar_t fov_height(const mat44<T> &v2p_); // return fov height angle from view->projection matrix
// miscellaneous
template<typename T> ray3<T> calculate_world_ray(const camera<T>&, typename math<T>::scalar_t screen_x_, typename math<T>::scalar_t screen_y_);  // calculates world space ray from screen coordinates in range [-1, 1] (origin at near plane)
template<typename T> vec3<T> calculate_world_pos(const camera<T>&, typename math<T>::scalar_t screen_x_, typename math<T>::scalar_t screen_y_, typename math<T>::scalar_t proj_z_);  // calculates world space position from screen coordinates in range [-1, 1] and projection space z in range [0, w]
template<typename T> void calculate_fov_planes(plane3<T> planes_[6], const mat44<T> &p2w_);  // calculate world space planes for given world->projection matrix. planes point away from FOV and are in order: left, right, bottom, top, near, far.
template<typename T> mat44<T> calculate_screen_to_world_matrix(const camera<T>&, typename math<T>::scalar_t vp_width_=1, typename math<T>::scalar_t vp_height_=1);
template<typename T> vec4<T> sphere_screen_extents(const vec3<T> &pos_, typename math<T>::scalar_t rad_, const mat44<T> &v2p_);
//----------------------------------------------------------------------------


//============================================================================
// tform3
//============================================================================
template<typename T>
struct tform3
{
  typedef typename math<T>::scalar_t scalar_t;
  // construction
  PFC_INLINE tform3();
  PFC_INLINE tform3(scalar_t s_);
  PFC_INLINE tform3(scalar_t sx_, scalar_t sy_, scalar_t sz_);
  PFC_INLINE tform3(const vec3<T> &translation_);
  PFC_INLINE tform3(const vec3<T> &x_,
                    const vec3<T> &y_,
                    const vec3<T> &z_);
  PFC_INLINE tform3(const vec3<T> &x_,
                    const vec3<T> &y_,
                    const vec3<T> &z_,
                    const vec3<T> &translation_);
  PFC_INLINE tform3(const vec4<T> &x_,
                    const vec4<T> &y_,
                    const vec4<T> &z_);
  PFC_INLINE tform3(scalar_t xx_, scalar_t xy_, scalar_t xz_, scalar_t xtrans_,
                    scalar_t yx_, scalar_t yy_, scalar_t yz_, scalar_t ytrans_,
                    scalar_t zx_, scalar_t zy_, scalar_t zz_, scalar_t ztrans_);
  PFC_INLINE tform3(const mat33<T>&);
  PFC_INLINE tform3(const mat33<T>&, const vec3<T> &translation_);
  PFC_INLINE tform3(const quat<T>&);
  PFC_INLINE tform3(const quat<T>&, const vec3<T> &translation_);
  PFC_INLINE tform3(const tform_rt3<T>&);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE const vec4<T> &operator[](unsigned vidx_) const;
  PFC_INLINE vec4<T> &operator[](unsigned vidx_);
  PFC_INLINE mat33<T> matrix33() const;
  PFC_INLINE mat44<T> matrix44() const;
  PFC_INLINE const vec3<T> &x_axis() const;
  PFC_INLINE const vec3<T> &y_axis() const;
  PFC_INLINE const vec3<T> &z_axis() const;
  PFC_INLINE vec3<T> translation() const;
  //--------------------------------------------------------------------------

  // mutators
  PFC_INLINE void set(scalar_t s_);
  PFC_INLINE void set(scalar_t sx_, scalar_t sy_, scalar_t sz_);
  PFC_INLINE void set(const vec3<T> &translation_);
  PFC_INLINE void set(const vec3<T> &x_,
                      const vec3<T> &y_,
                      const vec3<T> &z_);
  PFC_INLINE void set(const vec3<T> &x_,
                      const vec3<T> &y_,
                      const vec3<T> &z_,
                      const vec3<T> &translation_);
  PFC_INLINE void set(const vec4<T> &x_,
                      const vec4<T> &y_,
                      const vec4<T> &z_);
  PFC_INLINE void set(scalar_t xx_, scalar_t xy_, scalar_t xz_, scalar_t xtrans_,
                      scalar_t yx_, scalar_t yy_, scalar_t yz_, scalar_t ytrans_,
                      scalar_t zx_, scalar_t zy_, scalar_t zz_, scalar_t ztrans_);
  PFC_INLINE void set(const mat33<T>&);
  PFC_INLINE void set(const mat33<T>&, const vec3<T> &translation_);
  PFC_INLINE void set(const quat<T>&);
  PFC_INLINE void set(const quat<T>&, const vec3<T> &translation_);
  PFC_INLINE void set(const tform_rt3<T>&);
  PFC_INLINE void set_rotation(const mat33<T>&);
  PFC_INLINE void set_translation(const vec3<T>&);
  //--------------------------------------------------------------------------

  static const tform3 s_zero;
  static const tform3 s_identity;
  vec4<T> x;
  vec4<T> y;
  vec4<T> z;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, tform3<T>, is_type_pod, is_type_pod<vec4<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, tform3<T>, is_type_pod_stream, is_type_pod_stream<vec4<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// tform_rt3
//============================================================================
template<typename T>
struct tform_rt3
{
  typedef typename math<T>::scalar_t scalar_t;
  // construction
  PFC_INLINE tform_rt3();
  PFC_INLINE tform_rt3(const quat<T> &rotation_);
  PFC_INLINE tform_rt3(const vec3<T> &translation_);
  PFC_INLINE tform_rt3(const quat<T> &rotation_, const vec3<T> &translation_);
  PFC_INLINE tform_rt3(const tform3<T>&);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE mat33<T> matrix33() const;
  PFC_INLINE mat44<T> matrix44() const;
  //--------------------------------------------------------------------------

  // mutators
  PFC_INLINE void set(const quat<T> &rotation_);
  PFC_INLINE void set(const vec3<T> &translation_);
  PFC_INLINE void set(const quat<T> &rotation_, const vec3<T> &translation_);
  //--------------------------------------------------------------------------

  static const tform_rt3 s_zero;
  static const tform_rt3 s_identity;
  quat<T> rotation;
  vec3<T> translation;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, tform_rt3<T>, is_type_pod, is_type_pod<quat<T> >::res && is_type_pod<vec3<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, tform_rt3<T>, is_type_pod_stream, is_type_pod_stream<quat<T> >::res && is_type_pod_stream<vec3<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// camera
//============================================================================
template<typename T>
class camera
{
public:
  typedef typename math<T>::scalar_t scalar_t;
  // construction
  camera();
  camera(const mat44<T> &view_to_proj_, scalar_t near_, scalar_t far_);
  camera(const tform3<T> &view_to_world_, const mat44<T> &view_to_proj_, scalar_t near_, scalar_t far_);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE const mat44<T> &view_to_proj() const;
  PFC_INLINE const mat44<T> &proj_to_view() const;
  PFC_INLINE const tform3<T> &world_to_view() const;
  PFC_INLINE const tform3<T> &view_to_world() const;
  PFC_INLINE const mat44<T> &world_to_proj() const;
  PFC_INLINE const mat44<T> &proj_to_world() const;
  PFC_INLINE scalar_t near_plane() const;
  PFC_INLINE scalar_t far_plane() const;
  PFC_INLINE vec3<T> world_x() const;
  PFC_INLINE vec3<T> world_y() const;
  PFC_INLINE vec3<T> world_z() const;
  PFC_INLINE vec3<T> world_pos() const;
  //--------------------------------------------------------------------------

  // mutators
  PFC_INLINE void set_transform(const mat44<T> &view_to_proj_,
                                const tform3<T> &view_to_world_,
                                scalar_t near_,
                                scalar_t far_);
  PFC_INLINE void set_view_to_proj(const mat44<T>&, scalar_t near_, scalar_t far_);
  PFC_INLINE void set_view_to_world(const tform3<T>&);
  //--------------------------------------------------------------------------

private:
  void update_transforms();
  //--------------------------------------------------------------------------

  mat44<T> m_view_to_proj;
  mat44<T> m_proj_to_view;
  tform3<T> m_world_to_view;
  tform3<T> m_view_to_world;
  mat44<T> m_world_to_proj;
  mat44<T> m_proj_to_world;
  scalar_t m_near, m_far;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, camera<T>, is_type_pod, is_type_pod<mat44<T> >::res && is_type_pod<tform3<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// compressed_rotation_spi
//============================================================================
template<class Storage>
class compressed_rotation_spi
{
public:
  // construction
  PFC_INLINE compressed_rotation_spi();
  PFC_INLINE compressed_rotation_spi(const quatf&);
  PFC_INLINE compressed_rotation_spi(const vec3f &axis_, float angle_);
  PFC_INLINE bool init_precise(const quatf&);
  void init_precise(const vec3f&, float angle_);
  //--------------------------------------------------------------------------

  // rotation accessors
  PFC_INLINE vec3f axis() const PFC_NOTHROW;
  PFC_INLINE float angle() const;
  PFC_INLINE quatf quat() const;
  //--------------------------------------------------------------------------

private:
  Storage m_data;
};
PFC_SET_TYPE_TRAIT_PARTIAL(class Storage, compressed_rotation_spi<Storage>, is_type_pod, is_type_pod<Storage>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(class Storage, compressed_rotation_spi<Storage>, is_type_pod_stream, is_type_pod_stream<Storage>::res);
//----------------------------------------------------------------------------


//============================================================================
// compressed_rotation_oct
//============================================================================
template<class Storage>
class compressed_rotation_oct
{
public:
  // construction
  PFC_INLINE compressed_rotation_oct();
  PFC_INLINE compressed_rotation_oct(const quatf&);
  PFC_INLINE compressed_rotation_oct(const vec3f &axis_, float angle_);
  bool init_fast(const quatf&);
  void init_fast(const vec3f&, float angle_);
  //--------------------------------------------------------------------------

  // rotation accessors
  PFC_INLINE vec3f axis() const PFC_NOTHROW;
  PFC_INLINE float angle() const;
  PFC_INLINE quatf quat() const;
  //--------------------------------------------------------------------------

private:
  Storage m_data;
};
PFC_SET_TYPE_TRAIT_PARTIAL(class Storage, compressed_rotation_oct<Storage>, is_type_pod, is_type_pod<Storage>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(class Storage, compressed_rotation_oct<Storage>, is_type_pod_stream, is_type_pod_stream<Storage>::res);
//----------------------------------------------------------------------------


//============================================================================
// compressed_rotation_storage_24
//============================================================================
struct compressed_rotation_storage_24
{
  // config
  enum {num_rotation_axis_bits=16};   // number of bits used for axis representation
  enum {num_rotation_angle_bits=8};   // number of bits used for rotation angle representation
  enum {num_spiral_revolutions=210};  // number of spiral angle revolutions
  enum {num_oct_projection_x_bits=(num_rotation_axis_bits+1)/2};
  enum {num_oct_projection_y_bits=num_rotation_axis_bits-num_oct_projection_x_bits};
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE unsigned quant_rotation_angle() const;
  PFC_INLINE unsigned quant_spiral_angle() const;
  PFC_INLINE vec2i quant_oct_projection() const;
  PFC_INLINE void clear();
  PFC_INLINE void set_quant_spiral_angle(unsigned quant_spiral_angle_, unsigned quant_rot_angle_);
  PFC_INLINE void set_quant_oct_projection(unsigned quant_proj_x_, unsigned quant_proj_y_, unsigned quant_rot_angle_);
  //--------------------------------------------------------------------------

  uint8_t m_data[3];
};
PFC_SET_TYPE_TRAIT(compressed_rotation_storage_24, is_type_pod, true);
PFC_SET_TYPE_TRAIT(compressed_rotation_storage_24, is_type_pod_stream, true);
//----------------------------------------------------------------------------


//============================================================================
// compressed_rotation_storage_32
//============================================================================
struct compressed_rotation_storage_32
{
  // config
  enum {num_rotation_axis_bits=21};    // number of bits used for axis representation
  enum {num_rotation_angle_bits=11};   // number of bits used for rotation angle representation
  enum {num_spiral_revolutions=1185};  // number of spiral angle revolutions
  enum {num_oct_projection_x_bits=(num_rotation_axis_bits+1)/2};
  enum {num_oct_projection_y_bits=num_rotation_axis_bits-num_oct_projection_x_bits};
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE unsigned quant_rotation_angle() const;
  PFC_INLINE unsigned quant_spiral_angle() const;
  PFC_INLINE vec2i quant_oct_projection() const;
  PFC_INLINE void clear();
  PFC_INLINE void set_quant_spiral_angle(unsigned quant_spiral_angle_, unsigned quant_rot_angle_);
  PFC_INLINE void set_quant_oct_projection(unsigned quant_proj_x_, unsigned quant_proj_y_, unsigned quant_rot_angle_);
  //--------------------------------------------------------------------------

  uint32_t m_data;
};
PFC_SET_TYPE_TRAIT(compressed_rotation_storage_32, is_type_pod, true);
PFC_SET_TYPE_TRAIT(compressed_rotation_storage_32, is_type_pod_stream, true);
//----------------------------------------------------------------------------

//============================================================================
#include "tform3.inl"
} // namespace pfc
#endif
