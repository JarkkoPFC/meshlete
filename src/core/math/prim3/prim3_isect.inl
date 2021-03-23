//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================


//============================================================================
// intersection test routines
//============================================================================
template<typename T>
bool isect(const point3<T> &pnt_, const plane3<T> &plane_)
{
  return dot(plane_.normal, pnt_.pos)<plane_.d;
}
//----

template<typename T>
bool isect(const point3<T> &pnt_, const sphere3<T> &sphere_)
{
  return norm2(pnt_.pos-sphere_.pos)<sphere_.rad*sphere_.rad;
}
//----

template<typename T>
bool isect(const point3<T> &pnt_, const cylinder3<T> &cyl_)
{
  vec3<T> v=pnt_.pos-cyl_.pos;
  typename math<T>::scalar_t pl=dot(v, cyl_.dir);
  return    abs(pl)<cyl_.hlen
         && norm2(v-cyl_.dir*pl)<cyl_.rad*cyl_.rad;
}
//----

template<typename T>
bool isect(const point3<T> &pnt_, const capsule3<T> &cap_)
{
  vec3<T> v=pnt_.pos-cap_.pos;
  typename math<T>::scalar_t pl=clamp(dot(v, cap_.dir), -cap_.hlen, cap_.hlen);
  return norm2(v-cap_.dir*pl)<cap_.rad*cap_.rad;
}
//----

template<typename T>
bool isect(const point3<T> &pnt_, const cone3<T> &cone_)
{
  vec3<T> p=pnt_.pos-cone_.apex_pos;
  float p_dot_d=dot(p, cone_.dir);
  return p_dot_d<cone_.height && p_dot_d>cone_.cos_apex_hangle*norm(p);
}
//----

template<typename T>
bool isect(const point3<T> &pnt_, const aabox3<T> &aab_)
{
  vec3<T> v=abs(pnt_.pos-aab_.pos)-aab_.hsize;
  return v.x<0 && v.y<0 && v.z<0;
}
//----

template<typename T>
bool isect(const point3<T> &pnt_, const oobox3<T> &oob_)
{
  vec3<T> v=abs((pnt_.pos-oob_.pos)*inv_u(oob_.rot))-oob_.hsize;
  return v.x<0 && v.y<0 && v.z<0;
}
//----

template<typename T>
bool isect(const point3<T> &pnt_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const tri3<T> &tri_)
{
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> v=tri_.a-line_.pos;
  scalar_t a=dot(line_.dir, cross(tri_.b-tri_.a, v));
  scalar_t b=dot(line_.dir, cross(tri_.a-tri_.c, v));
  scalar_t c=dot(line_.dir, cross(tri_.c-tri_.b, tri_.b-line_.pos));
  return a*b>0 && a*c>0;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const tri3<T> &tri_, typename math<T>::scalar_t &t_)
{
  // check if line penetrates the triangle
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> v=tri_.a-line_.pos;
  vec3<T> e0=tri_.b-tri_.a;
  vec3<T> e1=tri_.a-tri_.c;
  scalar_t a=dot(line_.dir, cross(e0, v));
  scalar_t b=dot(line_.dir, cross(e1, v));
  scalar_t c=dot(line_.dir, cross(tri_.c-tri_.b, tri_.b-line_.pos));
  if(a*b<0 || a*c<0)
    return false;

  // calculate the line t-value at the triangle plane
  vec3<T> n=cross(e0, e1);
  t_=dot(v, n)/dot(line_.dir, n);
  return true;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const rect3<T> &rect_)
{
  // check for no plane intersection (perpendicular rect and line)
  typedef typename math<T>::scalar_t scalar_t;
  mat33<T> m;
  convert_u(m, rect_.rot);
  scalar_t d=dot(line_.dir, m.z);
  if(d==0)
    return false;

  // project intersection vector x to the rect and check if it's within the rect
  vec3<T> pd=rect_.pos-line_.pos;
  vec3<T> x=(dot(pd, m.z)/d)*line_.dir-pd;
  scalar_t s=dot(x, m.x), t=dot(x, m.y);
  return abs(s)<rect_.hsize.x && abs(t)<rect_.hsize.y;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const rect3<T> &rect_, typename math<T>::scalar_t &t_)
{
  // check for no plane intersection (perpendicular rect and line)
  typedef typename math<T>::scalar_t scalar_t;
  mat33<T> m;
  convert_u(m, rect_.rot);
  scalar_t d=dot(line_.dir, m.z);
  if(d==0)
    return false;

  // calculate line's t-value that intersects the rect plane
  vec3<T> pd=rect_.pos-line_.pos;
  t_=dot(pd, m.z)/d;

  // project intersection vector x to the rect and check if it's within the rect
  vec3<T> x=t_*line_.dir-pd;
  scalar_t u=dot(x, m.x), v=dot(x, m.y);
  return abs(u)<rect_.hsize.x && abs(v)<rect_.hsize.y;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const rect3<T> &rect_, typename math<T>::scalar_t &t_, typename math<T>::scalar_t &u_, typename math<T>::scalar_t &v_)
{
  // check for no plane intersection (perpendicular rect and line)
  typedef typename math<T>::scalar_t scalar_t;
  mat33<T> m;
  convert_u(m, rect_.rot);
  scalar_t d=dot(line_.dir, m.z);
  if(d==0)
    return false;

  // calculate line's t-value that intersects the rect plane
  vec3<T> pd=rect_.pos-line_.pos;
  t_=dot(pd, m.z)/d;

  // project intersection vector x to the rect and check if it's within the rect
  vec3<T> x=t_*line_.dir-pd;
  u_=dot(x, m.x), v_=dot(x, m.y);
  return abs(u_)<rect_.hsize.x && abs(v_)<rect_.hsize.y;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const disc3<T> &disc_)
{
  // check for no plane intersection (perpendicular disc normal and line)
  typename math<T>::scalar_t d=dot(line_.dir, disc_.normal);
  if(d==0)
    return false;

  // calculate line-plane intersection and distance of the point from the disc center
  vec3<T> p=disc_.pos-line_.pos;
  float t=dot(p, disc_.normal)/d;
  return norm2(t*line_.dir-p)<disc_.rad*disc_.rad;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const disc3<T> &disc_, typename math<T>::scalar_t &t_)
{
  // check for no plane intersection (perpendicular disc normal and line)
  typename math<T>::scalar_t d=dot(line_.dir, disc_.normal);
  if(d==0)
    return false;

  // calculate t-value at line-plane intersection and check disc intersection
  vec3<T> p=disc_.pos-line_.pos;
  t_=dot(p, disc_.normal)/d;
  return norm2(t_*line_.dir-p)<disc_.rad*disc_.rad;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const plane3<T> &plane_, typename math<T>::scalar_t &t_)
{
  // check for no intersection (perpendicular plane normal and line)
  typename math<T>::scalar_t d=dot(line_.dir, plane_.normal);
  if(d==0)
    return false;

  // calculate t-value at line-plane intersection
  t_=(plane_.d-dot(line_.pos, plane_.normal))/d;
  return true;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const sphere3<T> &sphere_)
{
  const vec3<T> v=line_.pos-sphere_.pos;
  typename math<T>::scalar_t b=dot(line_.dir, v);
  return b*b-norm2(v)+sphere_.rad*sphere_.rad>=0;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const sphere3<T> &sphere_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  // check for intersection
  typedef typename math<T>::scalar_t scalar_t;
  const vec3<T> v=sphere_.pos-line_.pos;
  scalar_t b=dot(line_.dir, v);
  scalar_t s2=b*b-norm2(v)+sphere_.rad*sphere_.rad;
  if(s2<0)
    return false;

  // return min and max t for intersections
  scalar_t s=sqrt(s2);
  min_t_=b-s;
  max_t_=b+s;
  return true;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const cylinder3<T> &cyl_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  // calculate intersection against infinite cylinder
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> m=line_.pos-cyl_.pos;
  scalar_t nd=dot(line_.dir, cyl_.dir);
  scalar_t md=dot(m, cyl_.dir);
  scalar_t a=scalar_t(1)-nd*nd;
  scalar_t b=dot(m, line_.dir)-nd*md;
  scalar_t c=dot(m, m)-cyl_.rad*cyl_.rad-md*md;
  scalar_t s=b*b-a*c;
  if(s<scalar_t(0) || (!a && c>scalar_t(0)))
    return false;
  scalar_t mint=numeric_type<scalar_t>::range_min(), maxt=numeric_type<scalar_t>::range_max();
  if(a)
  {
    scalar_t ss=sqrt(s);
    scalar_t ra=scalar_t(1)/a;
    mint=(-ss-b)*ra;
    maxt=(ss-b)*ra;
  }

  // clamp mint and maxt to the cylinder range
  scalar_t rnd=scalar_t(1)/nd;
  scalar_t hlen=rnd<scalar_t(0)?-cyl_.hlen:cyl_.hlen;
  scalar_t cmint=(-md-hlen)*rnd;
  scalar_t cmaxt=(-md+hlen)*rnd;
  mint=max(mint, cmint);
  maxt=min(maxt, cmaxt);
  if(mint>=maxt)
    return false;
  min_t_=mint;
  max_t_=maxt;
  return true;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const capsule3<T> &cap_)
{
  // check distance of closest point on capsule segment from the line
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> pv=cap_.pos-line_.pos;
  scalar_t a=dot(line_.dir, cap_.dir);
  scalar_t t=(dot(line_.dir, pv)*a-dot(pv, cap_.dir))/(cap_.hlen*(scalar_t(1)-a*a));
  vec3<T> nv=pv+(ssat(t)*cap_.hlen)*cap_.dir;
  return norm2(nv-line_.dir*dot(line_.dir, nv))<(cap_.rad*cap_.rad);
}
//----

template<typename T>
bool isect(const line3<T> &line_, const capsule3<T> &cap_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const cone3<T> &cone_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const aabox3<T> &aab_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const oobox3<T> &oob_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const line3<T> &line_, const frustum3<T> &frustum_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const tri3<T> &tri_)
{
  // check if line penetrates the triangle
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> v=tri_.a-ray_.pos;
  vec3<T> e0=tri_.b-tri_.a;
  vec3<T> e1=tri_.a-tri_.c;
  vec3<T> n=cross(e0, e1);
  float tn=dot(v, n), td=dot(ray_.dir, n);
  if(tn*td<=0)
    return false;
  scalar_t a=dot(ray_.dir, cross(e0, v));
  scalar_t b=dot(ray_.dir, cross(e1, v));
  scalar_t c=dot(ray_.dir, cross(tri_.c-tri_.b, tri_.b-ray_.pos));
  return a*b>0 && a*c>0;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const tri3<T> &tri_, typename math<T>::scalar_t &t_)
{
  // check if line penetrates the triangle
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> v=tri_.a-ray_.pos;
  vec3<T> e0=tri_.b-tri_.a;
  vec3<T> e1=tri_.a-tri_.c;
  vec3<T> n=cross(e0, e1);
  float tn=dot(v, n), td=dot(ray_.dir, n);
  if(tn*td<=0)
    return false;
  scalar_t a=dot(ray_.dir, cross(e0, v));
  scalar_t b=dot(ray_.dir, cross(e1, v));
  scalar_t c=dot(ray_.dir, cross(tri_.c-tri_.b, tri_.b-ray_.pos));
  if(a*b<0 || a*c<0)
    return false;

  // calculate the line t-value at the triangle plane
  t_=tn/td;
  return true;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const rect3<T> &rect_)
{
  // check for no plane intersection and potential intersection in positive side of the ray
  typedef typename math<T>::scalar_t scalar_t;
  mat33<T> m;
  convert_u(m, rect_.rot);
  vec3<T> pd=rect_.pos-ray_.pos;
  scalar_t d=dot(ray_.dir, m.z), a=dot(pd, m.z);
  if(d*a<=0)
    return false;

  // project intersection vector x to the rect and check if it's within the rect
  vec3<T> x=(a/d)*ray_.dir-pd;
  scalar_t u=dot(x, m.x), v=dot(x, m.y);
  return abs(u)<rect_.hsize.x && abs(v)<rect_.hsize.y;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const rect3<T> &rect_, typename math<T>::scalar_t &t_)
{
  // check for no plane intersection and potential intersection in positive side of the ray
  typedef typename math<T>::scalar_t scalar_t;
  mat33<T> m;
  convert_u(m, rect_.rot);
  vec3<T> pd=rect_.pos-ray_.pos;
  scalar_t d=dot(ray_.dir, m.z), a=dot(pd, m.z);
  if(d*a<=0)
    return false;

  // project intersection vector x to the rect and check if it's within the rect
  t_=a/d;
  vec3<T> x=t_*ray_.dir-pd;
  scalar_t u=dot(x, m.x), v=dot(x, m.y);
  return abs(u)<rect_.hsize.x && abs(v)<rect_.hsize.y;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const rect3<T> &rect_, typename math<T>::scalar_t &t_, typename math<T>::scalar_t &u_, typename math<T>::scalar_t &v_)
{
  // check for no plane intersection and potential intersection in positive side of the ray
  typedef typename math<T>::scalar_t scalar_t;
  mat33<T> m;
  convert_u(m, rect_.rot);
  vec3<T> pd=rect_.pos-ray_.pos;
  scalar_t d=dot(ray_.dir, m.z), a=dot(pd, m.z);
  if(d*a<=0)
    return false;

  // project intersection vector x to the rect and check if it's within the rect
  t_=a/d;
  vec3<T> x=t_*ray_.dir-pd;
  u_=dot(x, m.x), v_=dot(x, m.y);
  return abs(u_)<rect_.hsize.x && abs(v_)<rect_.hsize.y;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const disc3<T> &disc_)
{
  // check for no plane intersection (perpendicular disc normal and ray)
  vec3<T> p=disc_.pos-ray_.pos;
  typename math<T>::scalar_t d=dot(ray_.dir, disc_.normal), a=dot(p, disc_.normal);
  if(d*a<=0)
    return false;

  // calculate line-plane intersection and distance of the point from the disc center
  float t=a/d;
  return norm2(t*ray_.dir-p)<disc_.rad*disc_.rad;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const disc3<T> &disc_, typename math<T>::scalar_t &t_)
{
  // check for no plane intersection (perpendicular disc normal and ray)
  vec3<T> p=disc_.pos-ray_.pos;
  typename math<T>::scalar_t d=dot(ray_.dir, disc_.normal), a=dot(p, disc_.normal);
  if(d*a<=0)
    return false;

  // calculate line-plane intersection and distance of the point from the disc center
  t_=a/d;
  return norm2(t_*ray_.dir-p)<disc_.rad*disc_.rad;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const plane3<T> &plane_)
{
  // check for intersection (ray pointing plane direction)
  typename math<T>::scalar_t d=dot(ray_.dir, plane_.normal), a=plane_.d-dot(ray_.pos, plane_.normal);
  return a*d>0;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const plane3<T> &plane_, typename math<T>::scalar_t &t_)
{
  // check for intersection (ray pointing plane direction)
  typename math<T>::scalar_t d=dot(ray_.dir, plane_.normal), a=plane_.d-dot(ray_.pos, plane_.normal);
  if(d*a<=0)
    return false;
  t_=a/d;
  return true;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const sphere3<T> &sphere_)
{
  const vec3<T> v=ray_.pos-sphere_.pos;
  typename math<T>::scalar_t b=dot(ray_.dir, v);
  return b<0.0f && b*b-norm2(v)+sphere_.rad*sphere_.rad>=0;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const sphere3<T> &sphere_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const cylinder3<T> &cyl_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  // calculate intersection against infinite cylinder
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> m=ray_.pos-cyl_.pos;
  scalar_t nd=dot(ray_.dir, cyl_.dir);
  scalar_t md=dot(m, cyl_.dir);
  scalar_t a=scalar_t(1)-nd*nd;
  scalar_t b=dot(m, ray_.dir)-nd*md;
  scalar_t c=dot(m, m)-cyl_.rad*cyl_.rad-md*md;
  scalar_t s=b*b-a*c;
  if(s<scalar_t(0) || (!a && c>scalar_t(0)))
    return false;
  scalar_t mint=numeric_type<scalar_t>::range_min(), maxt=numeric_type<scalar_t>::range_max();
  if(a)
  {
    scalar_t ss=sqrt(s);
    scalar_t ra=scalar_t(1)/a;
    mint=(-ss-b)*ra;
    maxt=(ss-b)*ra;
  }

  // clamp mint and maxt to the cylinder range
  scalar_t rnd=scalar_t(1)/nd;
  scalar_t hlen=rnd<scalar_t(0)?-cyl_.hlen:cyl_.hlen;
  scalar_t cmint=(-md-hlen)*rnd;
  scalar_t cmaxt=(-md+hlen)*rnd;
  mint=max(mint, cmint);
  maxt=min(maxt, cmaxt);
  if(maxt<0 || mint>=maxt)
    return false;
  min_t_=max(scalar_t(0), mint);
  max_t_=maxt;
  return true;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const capsule3<T> &cap_)
{
  // check distance of closest point on capsule segment from the ray
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> pv=cap_.pos-ray_.pos;
  scalar_t a=dot(ray_.dir, cap_.dir);
  scalar_t t=(dot(ray_.dir, pv)*a-dot(pv, cap_.dir))/(cap_.hlen*(scalar_t(1)-a*a));
  vec3<T> nv=pv+(ssat(t)*cap_.hlen)*cap_.dir;
  scalar_t b=dot(ray_.dir, nv);
  return b>0.0f && norm2(nv-ray_.dir*b)<(cap_.rad*cap_.rad);
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const capsule3<T> &cap_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const cone3<T> &cone_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const aabox3<T> &aab_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const oobox3<T> &oob_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray3<T> &ray_, const frustum3<T> &frustum_, typename math<T>::scalar_t &min_t_, typename math<T>::scalar_t &max_t_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment3<T> &seg_, const tri3<T> &tri_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment3<T> &seg_, const rect3<T> &rect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment3<T> &seg_, const disc3<T> &disc_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment3<T> &seg_, const plane3<T> &plane_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment3<T> &seg_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment3<T> &seg_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment3<T> &seg_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment3<T> &seg_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment3<T> &seg_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment3<T> &seg_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment3<T> &seg_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const tri3<T> &tri0_, const tri3<T> &tri1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const tri3<T> &tri_, const rect3<T> &rect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const tri3<T> &tri_, const disc3<T> &disc_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const tri3<T> &tri_, const plane3<T> &plane_)
{
  return    dot(plane_.normal, tri_.a)<plane_.d
         || dot(plane_.normal, tri_.b)<plane_.d
         || dot(plane_.normal, tri_.c)<plane_.d;
}
//----

template<typename T>
bool isect(const tri3<T> &tri_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const tri3<T> &tri_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const tri3<T> &tri_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const tri3<T> &tri_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const tri3<T> &tri_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const tri3<T> &tri_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const tri3<T> &tri_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T> bool isect(const rect3<T> &r0_, const rect3<T> &r1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T> bool isect(const rect3<T> &rect_, const disc3<T> &disc_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T> bool isect(const rect3<T> &rect_, const plane3<T> &plane_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T> bool isect(const rect3<T> &rect_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T> bool isect(const rect3<T> &rect_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T> bool isect(const rect3<T> &rect_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T> bool isect(const rect3<T> &rect_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T> bool isect(const rect3<T> &rect_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T> bool isect(const rect3<T> &rect_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T> bool isect(const rect3<T> &rect_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const disc3<T> &d0_, const disc3<T> &d1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const disc3<T> &disc_, const plane3<T> &plane_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const disc3<T> &disc_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const disc3<T> &disc_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const disc3<T> &disc_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const disc3<T> &disc_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const disc3<T> &disc_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const disc3<T> &disc_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const disc3<T> &disc_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const plane3<T> &plane_, const sphere3<T> &sphere_)
{
  return dot(sphere_.pos, plane_.normal)-plane_.d<sphere_.rad;
}
//----

template<typename T>
bool isect(const plane3<T> &plane_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const plane3<T> &plane_, const capsule3<T> &cap_)
{
  return dot(plane_.normal, cap_.pos-cap_.dir*(sgn_zp(dot(plane_.normal, cap_.dir))*cap_.hlen))<plane_.d+cap_.rad;
}
//----

template<typename T>
bool isect(const plane3<T> &plane_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const plane3<T> &plane_, const aabox3<T> &aab_)
{
  return dot(aab_.pos+sel_lez(plane_.normal, aab_.hsize, -aab_.hsize), plane_.normal)<plane_.d;
}
//----

template<typename T>
bool isect(const plane3<T> &plane_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const plane3<T> &plane_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const sphere3<T> &s0_, const sphere3<T> &s1_)
{
  typename math<T>::scalar_t r=s0_.rad+s1_.rad;
  return norm2(s0_.pos-s1_.pos)<r*r;
}
//----

template<typename T>
bool isect(const sphere3<T> &sphere_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const sphere3<T> &sphere_, const capsule3<T> &cap_)
{
  vec3<T> v=sphere_.pos-cap_.pos;
  return norm2(v-cap_.dir*clamp(dot(v, cap_.dir), -cap_.hlen, cap_.hlen))<sqr(cap_.rad+sphere_.rad);
}
//----

template<typename T>
bool isect(const sphere3<T> &sphere_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const sphere3<T> &sphere_, const aabox3<T> &aab_)
{
  return norm2(max(abs(sphere_.pos-aab_.pos)-aab_.hsize, typename math<T>::scalar_t(0)))<sphere_.rad*sphere_.rad;
}
//----

template<typename T>
bool isect(const sphere3<T> &sphere_, const oobox3<T> &oob_)
{
  return norm2(max(abs((sphere_.pos-oob_.pos)*inv_u(oob_.rot))-oob_.hsize, typename math<T>::scalar_t(0)))<sphere_.rad*sphere_.rad;
}
//----

template<typename T>
bool isect(const sphere3<T> &sphere_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const cylinder3<T> &cyl0_, const cylinder3<T> &cyl1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const cylinder3<T> &cyl_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const cylinder3<T> &cyl_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const cylinder3<T> &cyl_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const cylinder3<T> &cyl_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const cylinder3<T> &cyl_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const capsule3<T> &cap0_, const capsule3<T> &cap1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const capsule3<T> &cap_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const capsule3<T> &cap_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const capsule3<T> &cap_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const cone3<T> &cone0_, const cone3<T> &cone1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const cone3<T> &cone_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const cone3<T> &cone_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const cone3<T> &cone_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const aabox3<T> &aab0_, const aabox3<T> &aab1_)
{
  vec3<T> v=abs(aab0_.pos-aab1_.pos)-aab0_.hsize-aab1_.hsize;
  return v.x<0 && v.y<0 && v.z<0;
}
//----

template<typename T>
bool isect(const aabox3<T> &aab_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const aabox3<T> &aab_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const oobox3<T> &oob0_, const oobox3<T> &oob1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const oobox3<T> &oob_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const frustum3<T> &f0_, const frustum3<T> &f1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----------------------------------------------------------------------------


//============================================================================
// intersection type routines
//============================================================================
template<typename T>
e_isect_type isect_type(const tri3<T> &tri_, const plane3<T> &plane_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const tri3<T> &tri_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const tri3<T> &tri_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const tri3<T> &tri_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const tri3<T> &tri_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const tri3<T> &tri_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const tri3<T> &tri_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const tri3<T> &tri_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T> e_isect_type isect_type(const rect3<T> &rect_, const plane3<T> &plane_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T> e_isect_type isect_type(const rect3<T> &rect_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T> e_isect_type isect_type(const rect3<T> &rect_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T> e_isect_type isect_type(const rect3<T> &rect_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T> e_isect_type isect_type(const rect3<T> &rect_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T> e_isect_type isect_type(const rect3<T> &rect_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T> e_isect_type isect_type(const rect3<T> &rect_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T> e_isect_type isect_type(const rect3<T> &rect_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const disc3<T> &disc_, const plane3<T> &plane_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const disc3<T> &disc_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const disc3<T> &disc_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const disc3<T> &disc_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const disc3<T> &disc_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const disc3<T> &disc_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const disc3<T> &disc_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const disc3<T> &disc_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const sphere3<T> &sphere_, const plane3<T> &plane_)
{
  typename math<T>::scalar_t d=dot(sphere_.pos, plane_.normal)-plane_.d;
  return e_isect_type((d<sphere_.rad?isect_type_in:isect_type_out)|(d<-sphere_.rad?isect_type_in:isect_type_out));
}
//----

template<typename T>
e_isect_type isect_type(const sphere3<T> &s0_, const sphere3<T> &s1_)
{
  typename math<T>::scalar_t d2=norm2(s0_.pos-s1_.pos);
  typename math<T>::scalar_t fd=s1_.rad-s0_.rad;
  return e_isect_type((d2<fd*abs(fd)?isect_type_in:isect_type_out)|(d2<sqr(s0_.rad+s1_.rad)?isect_type_in:isect_type_out));
}
//----

template<typename T>
e_isect_type isect_type(const sphere3<T> &sphere_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const sphere3<T> &sphere_, const capsule3<T> &cap_)
{
  vec3<T> v=sphere_.pos-cap_.pos;
  typename math<T>::scalar_t d2=norm2(v-cap_.dir*clamp(dot(v, cap_.dir), -cap_.hlen, cap_.hlen));
  typename math<T>::scalar_t fd=cap_.rad-sphere_.rad;
  return e_isect_type((d2<fd*abs(fd)?isect_type_in:isect_type_out)|(d2<sqr(cap_.rad+sphere_.rad)?isect_type_in:isect_type_out));
}
//----

template<typename T>
e_isect_type isect_type(const sphere3<T> &sphere_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const sphere3<T> &sphere_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const sphere3<T> &sphere_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const sphere3<T> &sphere_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cylinder3<T> &cyl_, const plane3<T> &plane_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cylinder3<T> &cyl_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cylinder3<T> &cyl0_, const cylinder3<T> &cyl1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cylinder3<T> &cyl_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cylinder3<T> &cyl_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cylinder3<T> &cyl_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cylinder3<T> &cyl_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cylinder3<T> &cyl_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const capsule3<T> &cap_, const plane3<T> &plane_)
{
  typename math<T>::scalar_t d=dot(plane_.normal, cap_.pos-cap_.dir*(sgn_zp(dot(plane_.normal, cap_.dir))*cap_.hlen))-plane_.d;
  return e_isect_type((d<cap_.rad?isect_type_in:isect_type_out)|(d<-cap_.rad?isect_type_in:isect_type_out));
}
//----

template<typename T>
e_isect_type isect_type(const capsule3<T> &cap_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const capsule3<T> &cap_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const capsule3<T> &cap0_, const capsule3<T> &cap1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const capsule3<T> &cap_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const capsule3<T> &cap_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const capsule3<T> &cap_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const capsule3<T> &cap_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cone3<T> &cone_, const plane3<T> &plane_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cone3<T> &cone_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cone3<T> &cone_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cone3<T> &cone_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cone3<T> &cone0_, const cone3<T> &cone1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cone3<T> &cone_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cone3<T> &cone_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const cone3<T> &cone_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const aabox3<T> &aab_, const plane3<T> &plane_)
{
  typename math<T>::scalar_t d=dot(aab_.pos, plane_.normal)-plane_.d;
  typename math<T>::scalar_t dp=dot(sel_lez(plane_.normal, aab_.hsize, -aab_.hsize), plane_.normal);
  return e_isect_type((d<dp?isect_type_in:isect_type_out)|(d<-dp?isect_type_in:isect_type_out));
}
//----

template<typename T>
e_isect_type isect_type(const aabox3<T> &aab_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const aabox3<T> &aab_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const aabox3<T> &aab_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const aabox3<T> &aab_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const aabox3<T> &aab0_, const aabox3<T> &aab1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const aabox3<T> &aab_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const aabox3<T> &aab_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const oobox3<T> &oob_, const plane3<T> &plane_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const oobox3<T> &oob_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const oobox3<T> &oob_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const oobox3<T> &oob_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const oobox3<T> &oob_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const oobox3<T> &oob_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const oobox3<T> &oob0_, const oobox3<T> &oob1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const oobox3<T> &oob_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const frustum3<T> &frustum_, const plane3<T> &plane_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const frustum3<T> &frustum_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const frustum3<T> &frustum_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const frustum3<T> &frustum_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const frustum3<T> &frustum_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const frustum3<T> &frustum_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const frustum3<T> &frustum_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----

template<typename T>
e_isect_type isect_type(const frustum3<T> &f0_, const frustum3<T> &f1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return isect_type_none;
}
//----------------------------------------------------------------------------
