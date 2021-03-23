//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================


//============================================================================
// hammersley
//============================================================================
template<typename T>
PFC_INLINE vec2<T> hammersley(unsigned idx_, unsigned num_samples_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return vec2<T>((idx_+1)/scalar_t(num_samples_), reverse_bits(uint16_t(idx_+1))/scalar_t(65536));
}
//----------------------------------------------------------------------------


//============================================================================
// cone_solid_angle
//============================================================================
// Returns solid angle for a cone with given apex angle: https://en.wikipedia.org/wiki/Solid_angle
template<typename T>
PFC_INLINE T cone_solid_angle(T cos_half_apex_angle_)
{
  return math<T>::two_pi*(T(1)-cos_half_apex_angle_);
}
//----------------------------------------------------------------------------


//============================================================================
// cone_uniform_vector
//============================================================================
// Returns uniformly distributed unit vector on a [0, 0, 1] oriented cone of
// given apex angle and uniform random vector xi ([x, y] in range [0, 1]).
// e.g. cos_half_apex_angle = 0 returns samples on a hemisphere (cos(pi/2)=0),
// while cos_half_apex_angle = -1 returns samples on a sphere (cos(pi)=-1)
template<typename T>
PFC_INLINE vec3<T> cone_uniform_vector(const vec2<T> &xi_,
                                       typename math<T>::scalar_t cos_half_apex_angle_)
{
  // return uniformly distributed vector within the cone
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t z=scalar_t(1)-(scalar_t(1)-cos_half_apex_angle_)*xi_.x;
  scalar_t r=sqrt(scalar_t(1)-z*z);
  scalar_t sphi, cphi;
  sincos(sphi, cphi, xi_.y*math<T>::two_pi);
  return vec3<T>(r*cphi, r*sphi, z);
}
//----------------------------------------------------------------------------


//============================================================================
// cone_strata_vector
//============================================================================
// Returns ith strata vector for a cone with given apex angle using
// "golden angle spiral method" described here: http://blog.marmakoide.org/?p=1
template<typename T>
PFC_INLINE vec3<T> cone_strata_vector(unsigned sample_idx_, unsigned num_samples_, typename math<T>::scalar_t cos_half_apex_angle_)
{
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t z=scalar_t(1)-(scalar_t(1)-cos_half_apex_angle_)*(sample_idx_+scalar_t(0.5))/num_samples_;
  scalar_t r=sqrt(scalar_t(1)-z*z);
  scalar_t sphi, cphi;
  sincos(sphi, cphi, sample_idx_*(math<T>::pi*(scalar_t(3)-sqrt(scalar_t(5)))));
  return vec3<T>(r*cphi, r*sphi, z);
}
//----------------------------------------------------------------------------


//============================================================================
// cone_strata_half_angle
//============================================================================
PFC_INLINE ufloat_t cone_strata_half_angle(unsigned num_samples_, ufloat_t cos_half_apex_angle_)
{
  // return strata cone apex half-angle for given number of samples and cone with given apex angle
  return acos(1.0f-(1.0f-cos_half_apex_angle_)/num_samples_);
}
//----------------------------------------------------------------------------


//============================================================================
// mc_solid_angle_stratified
//============================================================================
// Use stratified sampling over the given cone (position, direction, angle)
// to calculate solid angle for given primitive.
template<class PrimitiveType>
typename PrimitiveType::scalar_t mc_solid_angle_stratified(const PrimitiveType &prim_, const vec3<typename PrimitiveType::type_t> &pos_, const vec3<typename PrimitiveType::type_t> &dir_, typename PrimitiveType::scalar_t cos_half_apex_angle_, unsigned num_samples_)
{
  // create rotation matrix for given cone direction
  typedef typename PrimitiveType::type_t type_t;
  typedef typename PrimitiveType::scalar_t scalar_t;
  mat33<type_t> srot;
  convert_u(srot, zrot_u(dir_));

  // count number of sample rays hitting the primitive in the cone
  scalar_t cos_strata_half_angle=cos(cone_strata_half_angle(num_samples_, cos_half_apex_angle_));
  unsigned num_hit_samples=0;
  rng_simple rng;
  for(unsigned i=0; i<num_samples_; ++i)
  {
    // generate random light center oriented sample direction and test for light intersection
    vec2f xi;
    rand_ureal1(xi, rng);
    vec3<type_t> s=uniform_cone_vector(xi, cos_strata_half_angle);
    s*=zrot_u(cone_strata_vector(i, num_samples_, cos_half_apex_angle_));
    s*=srot;
    num_hit_samples+=isect(ray3<type_t>(pos_, s), prim_);
  }

  // calculate solid angle based on number of ray hits
  return num_hit_samples*(math<type_t>::two_pi/num_samples_)*(scalar_t(1)-cos_half_apex_angle_);
}
//----------------------------------------------------------------------------
