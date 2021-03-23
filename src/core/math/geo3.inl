//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================


//============================================================================
// seed_oobox3_discrete
//============================================================================
namespace priv
{
  template<typename T>
  seed_oobox3<T> find_discrete_seedbox3(const T *extremal_d_, const vec3<T> *extremal_pnts_, unsigned num_exts_, const vec3<T> *points_, usize_t num_points_, const uint32_t *point_indices_)
  {
    // predefined axes and their norms
    typedef typename math<T>::scalar_t scalar_t;
    seed_oobox3<T> seedbox;
    static const vec3<T> s_axes[]=
    {
      // 3-axes
      vec3<T>(1, 0, 0), vec3<T>(0, 1, 0), vec3<T>(0, 0, 1),
      // 7-axes
      vec3<T>(1, 1, 1), vec3<T>(1, 1, -1), vec3<T>(1, -1, 1), vec3<T>(1, -1, -1),
      // 13-axes
      vec3<T>(1, 1, 0), vec3<T>(1, -1, 0), vec3<T>(1, 0, 1), vec3<T>(1, 0, -1), vec3<T>(0, 1, 1), vec3<T>(0, 1, -1),
      // 49-axes
      vec3<T>(0, 1, 2), vec3<T>(0, 2, 1), vec3<T>(1, 0, 2), vec3<T>(2, 0, 1), vec3<T>(1, 2, 0), vec3<T>(2, 1, 0),
      vec3<T>(0, 1, -2), vec3<T>(0, 2, -1), vec3<T>(1, 0, -2), vec3<T>(2, 0, -1), vec3<T>(1, -2, 0), vec3<T>(2, -1, 0),
      vec3<T>(1, 1, 2), vec3<T>(2, 1, 1), vec3<T>(1, 2, 1), vec3<T>(1, -1, 2), vec3<T>(1, 1, -2), vec3<T>(1, -1, -2),
      vec3<T>(2, -1, 1), vec3<T>(2, 1, -1), vec3<T>(2, -1, -1), vec3<T>(1, -2, 1), vec3<T>(1, 2, -1), vec3<T>(1, -2, -1),
      vec3<T>(2, 2, 1), vec3<T>(1, 2, 2), vec3<T>(2, 1, 2), vec3<T>(2, -2, 1), vec3<T>(2, 2, -1), vec3<T>(2, -2, -1),
      vec3<T>(1, -2, 2), vec3<T>(1, 2, -2), vec3<T>(1, -2, -2), vec3<T>(2, -1, 2), vec3<T>(2, 1, -2), vec3<T>(2, -1, -2)
    };
    static const scalar_t s_rnorms[]=
    {
      scalar_t(1), scalar_t(1), scalar_t(1),
      math<T>::rsqrt3, math<T>::rsqrt3, math<T>::rsqrt3, math<T>::rsqrt3,
      math<T>::rsqrt2, math<T>::rsqrt2, math<T>::rsqrt2, math<T>::rsqrt2, math<T>::rsqrt2, math<T>::rsqrt2,
      scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595),
      scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595),
      scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829),
      scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829),
      scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333),
      scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333)
    };

    // find maximum and minimum diameter axes
    unsigned aidx=0, min_aidx=0, max_aidx=0;
    scalar_t mind=numeric_type<scalar_t>::range_max(), maxd=scalar_t(-1);
    for(unsigned i=0; i<num_exts_; i+=2, ++aidx)
    {
      scalar_t d=(extremal_d_[i+1]-extremal_d_[i])*s_rnorms[aidx];
      if(d>maxd)
      {
        maxd=d;
        max_aidx=aidx;
      }
    }
    aidx=0;
    for(unsigned i=0; i<num_exts_; i+=2, ++aidx)
    {
      scalar_t d=(extremal_d_[i+1]-extremal_d_[i])*s_rnorms[aidx];
      if(i!=max_aidx && d<mind)
      {
        mind=d;
        min_aidx=aidx;
      }
    }

    // setup min, med and max axes
    seedbox.max_ext[0]=extremal_pnts_[max_aidx*2+0];
    seedbox.max_ext[1]=extremal_pnts_[max_aidx*2+1];
    scalar_t maxp=scalar_t(0.5)*(extremal_d_[max_aidx*2+0]+extremal_d_[max_aidx*2+1]);
    maxp*=s_rnorms[max_aidx];
    const vec3<T> max_axis=s_axes[max_aidx]*s_rnorms[max_aidx];
    const vec3<T> min_axis=unit(s_axes[min_aidx]-max_axis*dot(s_axes[min_aidx], max_axis));
    const vec3<T> med_axis=cross(min_axis, max_axis);

    // calculate mesh extents on min and med axes
    scalar_t min_ext[2]={numeric_type<scalar_t>::range_max(), numeric_type<scalar_t>::range_min()};
    scalar_t med_ext[2]={numeric_type<scalar_t>::range_max(), numeric_type<scalar_t>::range_min()};
    if(point_indices_)
    {
      const uint32_t *end=point_indices_+num_points_;
      do
      {
        const vec3<T> &p=points_[*point_indices_];
        scalar_t dmin=dot(min_axis, p);
        if(dmin<min_ext[0])
          min_ext[0]=dmin;
        if(dmin>min_ext[1])
          min_ext[1]=dmin;
        scalar_t dmed=dot(med_axis, p);
        if(dmed<med_ext[0])
          med_ext[0]=dmed;
        if(dmed>med_ext[1])
          med_ext[1]=dmed;
      } while(++point_indices_!=end);
    }
    else
    {
      const vec3<T> *end=points_+num_points_;
      do
      {
        const vec3<T> &p=*points_;
        scalar_t dmin=dot(min_axis, p);
        if(dmin<min_ext[0])
          min_ext[0]=dmin;
        if(dmin>min_ext[1])
          min_ext[1]=dmin;
        scalar_t dmed=dot(med_axis, p);
        if(dmed<med_ext[0])
          med_ext[0]=dmed;
        if(dmed>med_ext[1])
          med_ext[1]=dmed;
      } while(++points_!=end);
    }
    scalar_t minp=scalar_t(0.5)*(min_ext[1]+min_ext[0]);
    mind=min_ext[1]-min_ext[0];
    scalar_t medp=scalar_t(0.5)*(med_ext[1]+med_ext[0]);
    scalar_t medd=med_ext[1]-med_ext[0];

    // calculate oobox from the max/min/med axes
    mat33<T> rot(max_axis, med_axis, min_axis);
    seedbox.oobox.pos=vec3<T>(maxp, medp, minp)*rot;
    seedbox.oobox.hsize=vec3<T>(maxd, medd, mind)*scalar_t(0.5);
    convert(seedbox.oobox.rot, rot);
    return seedbox;
  }
}
//----

template<typename T>
seed_oobox3<T> seed_oobox3_discrete(const vec3<T> *points_, usize_t num_points_, e_discrete_axes3 axes_, const uint32_t *point_indices_)
{
  // define discrete axis tests
  #define PFC_DISCRETE_AXIS_TEST(idx__, v__)\
  {\
    scalar_t v=v__;\
    if(v<extremal_d[idx__])\
    {\
      extremal_d[idx__]=v;\
      extremal_pnts[idx__]=*p;\
    }\
    if(v>extremal_d[idx__+1])\
    {\
      extremal_d[idx__+1]=v;\
      extremal_pnts[idx__+1]=*p;\
    }\
  }
  #define PFC_DISCRETE_AXES_001() PFC_DISCRETE_AXIS_TEST(0, p->x);\
                                  PFC_DISCRETE_AXIS_TEST(2, p->y);\
                                  PFC_DISCRETE_AXIS_TEST(4, p->z);
  #define PFC_DISCRETE_AXES_111() scalar_t p1xp1y=p->x+p->y, p1xn1y=p->x-p->y;\
                                  PFC_DISCRETE_AXIS_TEST(6, p1xp1y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(8, p1xp1y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(10, p1xn1y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(12, p1xn1y-p->z);
  #define PFC_DISCRETE_AXES_011() PFC_DISCRETE_AXIS_TEST(14, p1xp1y);\
                                  PFC_DISCRETE_AXIS_TEST(16, p1xn1y);\
                                  PFC_DISCRETE_AXIS_TEST(18, p->x+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(20, p->x-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(22, p->y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(24, p->y-p->z);
  #define PFC_DISCRETE_AXES_012() vec3<T> p2=*p+*p;\
                                  scalar_t p1xp2y=p->x+p2.y, p1xn2y=p->x-p2.y, p2xp1y=p2.x+p->y, p2xn1y=p2.x-p->y;\
                                  PFC_DISCRETE_AXIS_TEST(26, p->y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(28, p2.y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(30, p->x+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(32, p2.x+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(34, p1xp2y);\
                                  PFC_DISCRETE_AXIS_TEST(36, p2xp1y);\
                                  PFC_DISCRETE_AXIS_TEST(38, p->y-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(40, p2.y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(42, p->x-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(44, p2.x-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(46, p1xn2y);\
                                  PFC_DISCRETE_AXIS_TEST(48, p2xn1y);
  #define PFC_DISCRETE_AXES_112() PFC_DISCRETE_AXIS_TEST(50, p1xp1y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(52, p2xp1y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(54, p1xp2y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(56, p1xn1y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(58, p1xp1y-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(60, p1xn1y-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(62, p2xn1y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(64, p2xp1y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(66, p2xn1y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(68, p1xn2y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(70, p1xp2y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(72, p1xn2y-p->z);
  #define PFC_DISCRETE_AXES_122() PFC_DISCRETE_AXIS_TEST(74, p2.x+p2.y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(76, p1xp2y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(78, p2xp1y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(80, p2.x-p2.y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(82, p2.x+p2.y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(84, p2.x-p2.y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(86, p1xn2y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(88, p1xp2y-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(90, p1xn2y-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(92, p2xn1y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(94, p2xp1y-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(96, p2xn1y-p2.z);

  // find extremal points along given predefined axes
  PFC_ASSERT(points_ && num_points_);
  typedef typename math<T>::scalar_t scalar_t;
  switch(axes_)
  {
    // 3-axes test
    case discrete_axes3_3:
    {
      // init extremal values
      enum {num_exts=6};
      vec3<T> extremal_pnts[num_exts];
      scalar_t extremal_d[num_exts];
      for(unsigned i=0; i<num_exts; i+=2)
      {
        extremal_d[i]=numeric_type<scalar_t>::range_max();
        extremal_d[i+1]=numeric_type<scalar_t>::range_min();
      }

      // find extremal values for the 3 axes
      if(point_indices_)
      {
        const uint32_t *idx=point_indices_, *end=point_indices_+num_points_;
        do
        {
          const vec3<T> *p=points_+*idx;
          PFC_DISCRETE_AXES_001();
        } while(++idx!=end);
      }
      else
      {
        const vec3<T> *p=points_, *end=points_+num_points_;
        do
        {
          PFC_DISCRETE_AXES_001();
        } while(++p!=end);
      }
      return priv::find_discrete_seedbox3(extremal_d, extremal_pnts, num_exts, points_, num_points_, point_indices_);
    } break;

    // 7-axes test
    case discrete_axes3_7:
    {
      // init extremal values
      enum {num_exts=14};
      vec3<T> extremal_pnts[num_exts];
      scalar_t extremal_d[num_exts];
      for(unsigned i=0; i<num_exts; i+=2)
      {
        extremal_d[i]=numeric_type<scalar_t>::range_max();
        extremal_d[i+1]=numeric_type<scalar_t>::range_min();
      }

      // find extremal values for the 7 axes
      if(point_indices_)
      {
        const uint32_t *idx=point_indices_, *end=point_indices_+num_points_;
        do
        {
          const vec3<T> *p=points_+*idx;
          PFC_DISCRETE_AXES_001();
          PFC_DISCRETE_AXES_111();
        } while(++idx!=end);
      }
      else
      {
        const vec3<T> *p=points_, *end=points_+num_points_;
        do
        {
          PFC_DISCRETE_AXES_001();
          PFC_DISCRETE_AXES_111();
        } while(++p!=end);
      }
      return priv::find_discrete_seedbox3(extremal_d, extremal_pnts, num_exts, points_, num_points_, point_indices_);
    } break;

    // 13-axes test
    case discrete_axes3_13:
    {
      // init extremal values
      enum {num_exts=26};
      vec3<T> extremal_pnts[num_exts];
      scalar_t extremal_d[num_exts];
      for(unsigned i=0; i<num_exts; i+=2)
      {
        extremal_d[i]=numeric_type<scalar_t>::range_max();
        extremal_d[i+1]=numeric_type<scalar_t>::range_min();
      }

      // find extremal values for the 13 axes
      if(point_indices_)
      {
        const uint32_t *idx=point_indices_, *end=point_indices_+num_points_;
        do
        {
          const vec3<T> *p=points_+*idx;
          PFC_DISCRETE_AXES_001();
          PFC_DISCRETE_AXES_111();
          PFC_DISCRETE_AXES_011();
        } while(++idx!=end);
      }
      else
      {
        const vec3<T> *p=points_, *end=points_+num_points_;
        do
        {
          PFC_DISCRETE_AXES_001();
          PFC_DISCRETE_AXES_111();
          PFC_DISCRETE_AXES_011();
        } while(++p!=end);
      }
      return priv::find_discrete_seedbox3(extremal_d, extremal_pnts, num_exts, points_, num_points_, point_indices_);
    } break;

    // 49-axes test
    case discrete_axes3_49:
    {
      // init extremal values
      enum {num_exts=98};
      vec3<T> extremal_pnts[num_exts];
      scalar_t extremal_d[num_exts];
      for(unsigned i=0; i<num_exts; i+=2)
      {
        extremal_d[i]=numeric_type<scalar_t>::range_max();
        extremal_d[i+1]=numeric_type<scalar_t>::range_min();
      }

      // find extremal values for the 49 axes
      if(point_indices_)
      {
        const uint32_t *idx=point_indices_, *end=point_indices_+num_points_;
        do
        {
          const vec3<T> *p=points_+*idx;
          PFC_DISCRETE_AXES_001();
          PFC_DISCRETE_AXES_111();
          PFC_DISCRETE_AXES_011();
          PFC_DISCRETE_AXES_012();
          PFC_DISCRETE_AXES_112();
          PFC_DISCRETE_AXES_122();
        } while(++idx!=end);
      }
      else
      {
        const vec3<T> *p=points_, *end=points_+num_points_;
        do
        {
          PFC_DISCRETE_AXES_001();
          PFC_DISCRETE_AXES_111();
          PFC_DISCRETE_AXES_011();
          PFC_DISCRETE_AXES_012();
          PFC_DISCRETE_AXES_112();
          PFC_DISCRETE_AXES_122();
        } while(++p!=end);
      }
      return priv::find_discrete_seedbox3(extremal_d, extremal_pnts, num_exts, points_, num_points_, point_indices_);
    } break;

    // unknown precision
//    default: PFC_ERROR(("Unsupported discrete axis configuration\r\n"));
  }

  // undef discrete axis tests
  #undef PFC_DISCRETE_AXIS_TEST
  #undef PFC_DISCRETE_AXES_001
  #undef PFC_DISCRETE_AXES_111
  #undef PFC_DISCRETE_AXES_011
  #undef PFC_DISCRETE_AXES_012
  #undef PFC_DISCRETE_AXES_112
  #undef PFC_DISCRETE_AXES_122
  seed_oobox3<T> seedbox={oobox3<T>(vec3<T>::s_zero, vec3<T>::s_zero, quat<T>::s_identity), {vec3<T>::s_zero, vec3<T>::s_zero}};
  return seedbox;
}
//----------------------------------------------------------------------------


//============================================================================
// bounding_sphere3_exp
//============================================================================
template<typename T>
sphere3<T> bounding_sphere3_exp(const vec3<T> *points_, usize_t num_points_, const seed_oobox3<T> &seed_, bool use_oobox_, const uint32_t *point_indices_)
{
  // setup initial sphere and adjust the sphere to contain all points
  PFC_ASSERT(points_ && num_points_);
  typedef typename math<T>::scalar_t scalar_t;
  sphere3<T> sphere(use_oobox_?seed_.oobox.pos:(seed_.max_ext[0]+seed_.max_ext[1])*scalar_t(0.5),
                    use_oobox_?seed_.oobox.hsize.x:norm(seed_.max_ext[0]-seed_.max_ext[1])*scalar_t(0.5));

  // expand the sphere with the next point outside the sphere
  scalar_t srad2=sphere.rad*sphere.rad;
  if(point_indices_)
  {
    const uint32_t *end=point_indices_+num_points_;
    do
    {
      // check for outside point
      const vec3<T> &p=points_[*point_indices_];
      scalar_t d2=norm2(p-sphere.pos);
      if(d2>srad2)
      {
        // adjust the sphere to contain the old sphere & outside point
        scalar_t d=std::sqrt(d2), old_rad=sphere.rad;
        sphere.rad=(sphere.rad+d)*scalar_t(0.5);
        srad2=sphere.rad*sphere.rad;
        sphere.pos+=(p-sphere.pos)*((sphere.rad-old_rad)/d);
      }
    } while(++point_indices_!=end);
  }
  else
  {
    const vec3<T> *p=points_, *end=points_+num_points_;
    do
    {
      // check for outside point
      scalar_t d2=norm2(*p-sphere.pos);
      if(d2>srad2)
      {
        // adjust the sphere to contain the old sphere & outside point
        scalar_t d=sqrt(d2), old_rad=sphere.rad;
        sphere.rad=(sphere.rad+d)*scalar_t(0.5);
        srad2=sphere.rad*sphere.rad;
        sphere.pos+=(*p-sphere.pos)*((sphere.rad-old_rad)/d);
      }
    } while(++p!=end);
  }

  // return the bounding sphere
  return sphere;
}
//----------------------------------------------------------------------------


//============================================================================
// triangle_mesh_topology
//============================================================================
usize_t triangle_mesh_topology::num_vertices() const
{
  return m_vertices.size();
}
//----

usize_t triangle_mesh_topology::num_edges() const
{
  return m_edges.size();
}
//----

usize_t triangle_mesh_topology::num_triangles() const
{
  return m_triangles.size();
}
//----

usize_t triangle_mesh_topology::num_clusters() const
{
  return m_clusters.size();
}
//----

usize_t triangle_mesh_topology::num_cluster_tris(uint32_t cluster_idx_) const
{
  return m_clusters[cluster_idx_].num_tris;
}
//----------------------------------------------------------------------------

uint32_t triangle_mesh_topology::add_cluster()
{
  uint32_t cid=(uint32_t)m_clusters.size();
  cluster c;
  c.tri_list=0xffffffff;
  c.num_tris=0;
  m_clusters.push_back(c);
  return cid;
}
//----

void triangle_mesh_topology::add_cluster_tri(uint32_t tri_idx_, uint32_t cluster_idx_)
{
  triangle &tri=m_triangles[tri_idx_];
  PFC_ASSERT_PEDANTIC(tri.cidx==0xffffffff);
  cluster &c=m_clusters[cluster_idx_];
  tri.cidx=cluster_idx_;
  tri.next_cluster_tri=c.tri_list;
  c.tri_list=tri_idx_;
  ++c.num_tris;
}
//----------------------------------------------------------------------------

const uint32_t *triangle_mesh_topology::tri_vidx(uint32_t tri_idx_) const
{
  return m_triangles[tri_idx_].vidx;
}
//----

const uint32_t *triangle_mesh_topology::tri_eidx(uint32_t tri_idx_) const
{
  return m_triangles[tri_idx_].eidx;
}
//----

uint32_t triangle_mesh_topology::tri_cluster(uint32_t tri_idx_) const
{
  return m_triangles[tri_idx_].cidx;
}
//----

void triangle_mesh_topology::set_tri_cluster(uint32_t tri_idx_, uint32_t cluster_idx_)
{
  m_triangles[tri_idx_].cidx=cluster_idx_;
}
//----------------------------------------------------------------------------

// Iterates through all triangles attached to the given vertex
template<class Pred>
void triangle_mesh_topology::for_each_vtx_tri(uint32_t vtx_idx_, Pred &pred_) const
{
  // iterate through all edges attached to the vertex
  uint32_t pass_id=++m_pass_id;
  const triangle *triangles_data=m_triangles.data();
  const edge *edges_data=m_edges.data();
  const vertex *vertices_data=m_vertices.data();
  uint32_t elst=vertices_data[vtx_idx_].edge_list;
  do
  {
    // iterate through all triangles attached to the edge
    uint32_t eidx=elst>>1;
    const edge &e=edges_data[eidx];
    uint32_t tlst=e.tri_list;
    do
    {
      uint32_t tidx=tlst>>2;
      const triangle &tri=triangles_data[tidx];
      if(tri.pass_id!=pass_id)
      {
        tri.pass_id=pass_id;
        pred_(tidx);
      }
      tlst=tri.next_edge_tri[tlst&3];
    } while(tlst!=0xffffffff);
    elst=e.next_vtx_edge[elst&1];
  } while(elst!=0xffffffff);
}
//----

// Iterates through all triangles attached to the given edge
template<class Pred>
void triangle_mesh_topology::for_each_edge_tri(uint32_t edge_idx_, Pred &pred_) const
{
  const triangle *triangles_data=m_triangles.data();
  const edge *edges_data=m_edges.data();
  uint32_t tlst=edges_data[edge_idx_].tri_list;
  do
  {
    uint32_t tidx=tlst>>2;
    unsigned tvidx=tlst&3;
    pred_(tidx, tvidx);
    const triangle &tri=triangles_data[tidx];
    tlst=tri.next_edge_tri[tvidx];
  } while(tlst!=0xffffffff);
}
//----

// Iterates through all triangles attached to the 3 triangle edges (excluding
// the given triangle)
template<class Pred>
void triangle_mesh_topology::for_each_tri_vtx_tri(uint32_t tri_idx_, Pred &pred_) const
{
  // process all 3 triangle vertices
  uint32_t pass_id=++m_pass_id;
  const triangle *triangles_data=m_triangles.data();
  const edge *edges_data=m_edges.data();
  const vertex *vertices_data=m_vertices.data();
  const triangle &tri=triangles_data[tri_idx_];
  tri.pass_id=pass_id;
  for(unsigned tvi=0; tvi<3; ++tvi)
  {
    // iterate through all edges attached to the vertex
    uint32_t elst=vertices_data[tri.vidx[tvi]].edge_list;
    do
    {
      // iterate through all triangles attached to the edge
      uint32_t eidx=elst>>1;
      const edge &e=edges_data[eidx];
      if(e.pass_id!=pass_id)
      {
        e.pass_id=pass_id;
        uint32_t tlst=e.tri_list;
        do
        {
          uint32_t tidx=tlst>>2;
          const triangle &tri=triangles_data[tidx];
          if(tri.pass_id!=pass_id)
          {
            tri.pass_id=pass_id;
            pred_(tidx, tlst&3, tvi);
          }
          tlst=tri.next_edge_tri[tlst&3];
        } while(tlst!=0xffffffff);
      }
      elst=e.next_vtx_edge[elst&1];
    } while(elst!=0xffffffff);
  }
}
//----

// Iterates through all triangles attached to the 3 triangle edges (excluding
// the given triangle)
template<class Pred>
void triangle_mesh_topology::for_each_tri_edge_tri(uint32_t tri_idx_, Pred &pred_) const
{
  const triangle *triangles_data=m_triangles.data();
  const edge *edges_data=m_edges.data();
  const triangle &tri=triangles_data[tri_idx_];
  for(unsigned tei=0; tei<3; ++tei)
  {
    // iterate through triangles attached to the edge
    const edge &e=edges_data[tri.eidx[tei]];
    uint32_t tlst=e.tri_list;
    do
    {
      uint32_t tidx=tlst>>2;
      if(tidx!=tri_idx_)
        pred_(tidx, tlst&3);
      const triangle &tri=triangles_data[tidx];
      tlst=tri.next_edge_tri[tlst&3];
    } while(tlst!=0xffffffff);
  }
}
//----

// Iterates through all vertices assigned to triangles in the given cluster
template<class Pred>
void triangle_mesh_topology::for_each_cluster_vtx(uint32_t cluster_idx_, Pred &pred_) const
{
  const uint32_t pass_id=++m_pass_id;
  const triangle *triangle_data=m_triangles.data();
  const vertex *vertices_data=m_vertices.data();
  uint32_t tlst=m_clusters[cluster_idx_].tri_list;
  while(tlst!=0xffffffff)
  {
    const triangle &tri=triangle_data[tlst];
    for(unsigned tvi=0; tvi<3; ++tvi)
    {
      uint32_t vidx=tri.vidx[tvi];
      const vertex &vtx=vertices_data[vidx];
      if(vtx.pass_id!=pass_id)
      {
        vtx.pass_id=pass_id;
        pred_(vidx);
      }
    }
    tlst=tri.next_cluster_tri;
  }
}
//----

// Iterates through all triangles assigned to the given cluster
template<class Pred>
void triangle_mesh_topology::for_each_cluster_tri(uint32_t cluster_idx_, Pred &pred_) const
{
  // iterate through all triangles in the cluster
  const triangle *triangle_data=m_triangles.data();
  uint32_t tlst=m_clusters[cluster_idx_].tri_list;
  while(tlst!=0xffffffff)
  {
    pred_(tlst);
    const triangle &tri=triangle_data[tlst];
    tlst=tri.next_cluster_tri;
  }
}
//----

// Iterates through all triangles that are directly or indirectly connected to
// the given triangle via edges, including the given starting triangle. This
// effectively performs flood fill on a triangle mesh.
template<class Pred>
void triangle_mesh_topology::for_each_edge_connected_cluster_tri(uint32_t start_tri_idx_, Pred &pred_) const
{
  // setup edge-connected mesh cluster traversal
  const uint32_t pass_id=++m_pass_id;
  const triangle *triangles_data=m_triangles.data();
  const triangle &start_tri=triangles_data[start_tri_idx_];
  const uint32_t cidx=start_tri.cidx;
  const edge *edges_data=m_edges.data();
  const vertex *vertices_data=m_vertices.data();
  array<uint32_t> active_cluster_edges;
  for(unsigned i=0; i<3; ++i)
  {
    edges_data[start_tri.eidx[i]].pass_id=pass_id;
    vertices_data[start_tri.vidx[i]].pass_id=pass_id;
  }

  // process active cluster edges until none left
  uint32_t num_vtx=3, num_edge=3;
  active_cluster_edges.insert_back(3, start_tri.eidx);
  do
  {
    const edge &e=edges_data[active_cluster_edges.back()];
    active_cluster_edges.pop_back();
    uint32_t tlst=e.tri_list;
    do
    {
      uint32_t tidx=tlst>>2;
      const triangle &tri=triangles_data[tidx];
      if(tri.cidx==cidx && tri.pass_id!=pass_id)
      {
        pred_(tidx);
        tri.pass_id=pass_id;
        for(unsigned tvei=0; tvei<3; ++tvei)
        {
          const edge &e=edges_data[tri.eidx[i]];
          if(e.pass_id!=pass_id)
          {
            e.pass_id=pass_id;
            active_cluster_edges.push_back(tri.eidx[tvei]);
            ++num_edge;
          }
          const vertex &vtx=vertices_data[tri.vidx[tvei]];
          if(vtx.pass_id!=pass_id)
          {
            vtx.pass_id=pass_id;
            ++num_vtx;
          }
        }
      }
      tlst=tri.next_edge_tri[tlst&3];
    } while(tlst!=0xffffffff);
  } while(active_cluster_edges.size());
}
//----------------------------------------------------------------------------
