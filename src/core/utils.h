//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_UTILS_H
#define PFC_CORE_UTILS_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "meta.h"
//#include "cstr.h"
namespace pfc
{
template<typename T, bool ascending_> struct radix_sort_predicate;
template<typename T, bool ascending_> struct compare_sort_predicate;

// new
// data swapping
template<typename T> PFC_INLINE void swap(T&, T&);
template<typename T> PFC_INLINE void swap(T*, T*, usize_t count_);
template<typename T> PFC_INLINE T swap_bytes(T);
template<typename T> PFC_INLINE void swap_bytes(T*, usize_t count_);
template<typename T> PFC_INLINE T to_little_endian(T);
template<typename T> PFC_INLINE T to_big_endian(T);
// array construction/destruction
template<typename T> PFC_INLINE void default_construct(T*, usize_t count_);
template<typename T> PFC_INLINE void copy_construct(T*, const T*, usize_t count_);
template<typename T> PFC_INLINE void copy_construct(T*, const T&, usize_t count_);
template<typename T> PFC_INLINE void move_construct(T*, T*, usize_t count_);
template<typename T> PFC_INLINE void rotate_sequence_left(T *first_, T *last_);
template<typename T> PFC_INLINE void rotate_sequence_right(T *first_, T *last_);
template<typename T> PFC_INLINE void destruct(T*, usize_t count_);
template<typename T> PFC_INLINE void reverse_default_construct(T*, usize_t count_);
template<typename T> PFC_INLINE void reverse_copy_construct(T*, const T*, usize_t count_);
template<typename T> PFC_INLINE void reverse_copy_construct(T*, const T&, usize_t count_);
template<typename T> PFC_INLINE void reverse_move_construct(T*, T*, usize_t count_);
template<typename T> PFC_INLINE void reverse_destruct(T*, usize_t count_);
// randomization
class rng_simple;
// hash key and functions
template<typename> struct hash_func;
uint32_t crc32(const void*, usize_t num_bytes_, uint32_t seed_=0xffffffff);
uint32_t crc32(const char*, uint32_t seed_=0xffffffff);
// id classes
class fourcc_id;
typedef char fourcc_cstr[5];
#define PFC_BE_FOURCC_ID(c0__, c1__, c2__, c3__) uint32_t(uint32_t(c0__)<<24|uint32_t(c1__)<<16|uint32_t(c2__)<<8|uint32_t(c3__))
#define PFC_LE_FOURCC_ID(c0__, c1__, c2__, c3__) uint32_t(uint32_t(c0__)|uint32_t(c1__)<<8|uint32_t(c2__)<<16|uint32_t(c3__)<<24)
// pair
template<typename, typename> struct pair;
template<typename T, typename U> PFC_INLINE pair<T, U> make_pair(const T&, const U&);
template<typename T, typename U> PFC_INLINE bool operator==(const pair<T, U>&, const pair<T, U>&);
template<typename T, typename U> PFC_INLINE bool operator==(const pair<T, U>&, const T&);
template<typename T, typename U> PFC_INLINE bool operator!=(const pair<T, U>&, const pair<T, U>&);
template<typename T, typename U> PFC_INLINE bool operator!=(const pair<T, U>&, const T&);
// functor
template<typename FS> class functor;
template<class T, class U, typename R> PFC_INLINE functor<R()> make_functor(T&, R(*)(U&));
#define PFC_MAKE_MEM_FUNCTOR(functor_t__, obj__, class__, mem_func__) functor_t__(obj__, functor_t__::call_mem_func<class__, &class__::mem_func__>)
#define PFC_MAKE_CMEM_FUNCTOR(functor_t__, obj__, class__, mem_func__) functor_t__(obj__, functor_t__::call_cmem_func<class__, &class__::mem_func__>)
#define PFC_MAKE_VMEM_FUNCTOR(functor_t__, obj__, class__, mem_func__) functor_t__(obj__, functor_t__::call_vmem_func<class__, &class__::mem_func__>)
#define PFC_MAKE_CVMEM_FUNCTOR(functor_t__, obj__, class__, mem_func__) functor_t__(obj__, functor_t__::call_cvmem_func<class__, &class__::mem_func__>)
// class member function wrappers
template<typename FS> class mem_func;
template<typename FS> class cmem_func;
template<class T, typename R> PFC_INLINE mem_func<R()> make_mem_func(R(T::*)());
template<class T, typename R> PFC_INLINE cmem_func<R()> make_mem_func(R(T::*)() const);
// variants
template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9> class variant;
template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9> class pod_variant;
template<class B, unsigned max_size=sizeof(B), unsigned align=ptr_size> class poly_variant;
template<class B, unsigned max_size=sizeof(B), unsigned align=ptr_size> class poly_pod_variant;
//----------------------------------------------------------------------------


//============================================================================
// rng_simple
//============================================================================
// Uses George Marsaglia's "Multiply with carry" RNG algorithm
class rng_simple
{
public:
  // construction
  PFC_INLINE rng_simple(uint32_t seed_=0);
  PFC_INLINE void set_seed(uint32_t seed_);
  PFC_INLINE ufloat1_t rand_ureal1() const;
  PFC_INLINE float1_t rand_real1() const;
  //--------------------------------------------------------------------------

private:
  mutable uint32_t m_w, m_z;
};
PFC_SET_TYPE_TRAIT(rng_simple, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// hash_func
//============================================================================
template<typename K>
struct hash_func
{
  static PFC_INLINE unsigned index(K);
};
//----

template<typename T>
struct hash_func<T*>
{
  static PFC_INLINE unsigned index(const volatile T*);
};
//----------------------------------------------------------------------------


//============================================================================
// fourcc_id
//============================================================================
class fourcc_id
{
public:
  // construction
  PFC_INLINE fourcc_id();
  PFC_INLINE fourcc_id(uint32_t id32_);
  PFC_INLINE fourcc_id(const char*);
  PFC_INLINE void set(uint32_t id32_);
  PFC_INLINE void set(const char*);
  //--------------------------------------------------------------------------

  // comparison and accessors
  PFC_INLINE bool operator==(const fourcc_id&) const;
  PFC_INLINE bool operator!=(const fourcc_id&) const;
  PFC_INLINE bool operator==(uint32_t) const;
  PFC_INLINE bool operator!=(uint32_t) const;
  PFC_INLINE uint32_t id32() const;
  PFC_INLINE void c_str(fourcc_cstr) const;
  //--------------------------------------------------------------------------

private:
  uint32_t filter_id32(uint32_t) const;
  //--------------------------------------------------------------------------

  uint32_t m_id;
};
PFC_SET_TYPE_TRAIT(fourcc_id, is_type_pod, true);
//----------------------------------------------------------------------------


//============================================================================
// pair
//============================================================================
template<typename T, typename U>
struct pair
{
  // construction
  PFC_INLINE pair();
  PFC_INLINE pair(const T&, const U&);
  //--------------------------------------------------------------------------

  T first;
  U second;
};
PFC_SET_TYPE_TRAIT_PARTIAL2(typename T, typename U, pair<T, U>, is_type_pod_move, is_type_pod_move<T>::res && is_type_pod_move<U>::res);
//----------------------------------------------------------------------------


//============================================================================
// radix_sort_predicate<pair>
//============================================================================
template<typename T, typename U, bool ascending_>
struct radix_sort_predicate<pair<T, U>, ascending_>
{ PFC_CTC_ASSERT_MSG(!is_type_class<T>::res, pair_first_type_can_not_be_class_type_for_radix_sort_predicate);
  enum {radix_passes=sizeof(T)};
  enum {radix_range=256};
  PFC_INLINE unsigned radix(const pair<T, U>&, unsigned pass_) const;
};
//----------------------------------------------------------------------------

//============================================================================
// compare_sort_predicate<pair>
//============================================================================
template<typename T, typename U, bool ascending_>
struct compare_sort_predicate<pair<T, U>, ascending_>
{
  PFC_INLINE bool before(const pair<T, U>&, const pair<T, U>&) const;
};
//----------------------------------------------------------------------------


//============================================================================
// functor
//============================================================================
// functor takes a function signature as a template argument, e.g.
//   int trunc(float f_)  {return int(f_);}
//   functor<int(float)> f(trunc);
// for member functions use cv-qualifier matching call_*mem_func function, e.g.
//   struct foo {int trunc(float f_) const {return int(f_);}};
//   foo obj;
//   functor<int(float)> f(obj, functor<int(float)>::call_cmem_func<foo, &foo::trunc>);
// and to reduce some redundancy there's helper macro:
//   auto f=PFC_MAKE_CMEM_FUNCTOR(functor<int(float)>, obj, foo, trunc);
// note: function signatures up to 10 arguments are supported
template<typename R>
class functor<R()>
{
public:
  // construction and execution
  PFC_INLINE functor();
  PFC_INLINE functor(R(*)());
  template<class T, class U> PFC_INLINE functor(T&, R(*)(U&));
  inline R operator()() const;
  PFC_INLINE operator bool() const;
  PFC_INLINE void clear();
  //--------------------------------------------------------------------------

  // member function call functions
  template<class T, R(T::*mem_fun)()> static R call_mem_func(T&);
  template<class T, R(T::*mem_fun)() const> static R call_cmem_func(const T&);
  template<class T, R(T::*mem_fun)() volatile> static R call_vmem_func(volatile T&);
  template<class T, R(T::*mem_fun)() const volatile> static R call_cvmem_func(const volatile T&);
  //--------------------------------------------------------------------------

private:
  void *m_this;
  void *m_func;
};
//----------------------------------------------------------------------------


//============================================================================
// mem_func/cmem_func
//============================================================================
// mem_func takes a function signature as a template argument, e.g.
//   int foo::bar(float);
//   mem_func<int(float)> f(&foo::bar);
//  note: member function signatures up to 10 arguments are supported
//        for const member functions use cmem_func
template<typename R>
class mem_func<R()>
{
public:
  // construction and execution
  PFC_INLINE mem_func();
  template<class T> PFC_INLINE mem_func(R(T::*)());
  template<class T> inline R operator()(T&) const;
  PFC_INLINE operator bool() const;
  //--------------------------------------------------------------------------

private:
  friend class cmem_func<R()>;
  R(mem_func::*m_mem_func)();
};
//----

template<typename R>
class cmem_func<R()>
{
public:
  // construction and execution
  PFC_INLINE cmem_func();
  PFC_INLINE cmem_func(const mem_func<R()>&);
  template<class T> PFC_INLINE cmem_func(R(T::*)() const);
  template<class T> inline R operator()(const T&) const;
  PFC_INLINE operator bool() const;
  //--------------------------------------------------------------------------

private:
  R(cmem_func::*m_mem_func)() const;
};
//----------------------------------------------------------------------------


//============================================================================
// variant
//============================================================================
template<typename T0,      typename T1=void, typename T2=void, typename T3=void, typename T4=void,
         typename T5=void, typename T6=void, typename T7=void, typename T8=void, typename T9=void>
class variant
{
public:
  template<typename T> struct find_type;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE variant();
  PFC_INLINE variant(const variant&);
  template<typename T> PFC_INLINE variant(const T&);
  template<typename T> PFC_INLINE variant(meta_type<T>);
  PFC_INLINE void operator=(const variant&);
  template<typename T> PFC_INLINE void operator=(const T&);
  template<typename T> PFC_INLINE void operator=(meta_type<T>);
  PFC_INLINE ~variant();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE unsigned type_index() const;
  PFC_INLINE const void *data() const;
  #define PFC_VARIANT_TFS template<typename U, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
  PFC_VARIANT_TFS friend U &type_set(variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend U &type_ref(variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend const U &type_ref(const variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend volatile U &type_ref(volatile variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend const volatile U &type_ref(const volatile variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend U *type_ptr(variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend const U *type_ptr(const variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend volatile U *type_ptr(volatile variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend const volatile U *type_ptr(const volatile variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  #undef PFC_VARIANT_TFS
  //--------------------------------------------------------------------------

private:
  template<class PE, typename T> PFC_INLINE void read_value(PE&, const meta_type<T>&, uint8_t type_index_);
  template<class PE> PFC_INLINE void read_value(PE&, const meta_type<void>&, uint8_t type_index_);
  template<class PE, typename T> PFC_INLINE void write_value(PE&, const meta_type<T>&);
  template<class PE> PFC_INLINE void write_value(PE&, const meta_type<void>&);
  //--------------------------------------------------------------------------

  typedef meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> tarray_t;
  enum {max_size=meta_max<meta_sizeof<T0>::res, meta_sizeof<T1>::res,
                          meta_sizeof<T2>::res, meta_sizeof<T3>::res,
                          meta_sizeof<T4>::res, meta_sizeof<T5>::res,
                          meta_sizeof<T6>::res, meta_sizeof<T7>::res,
                          meta_sizeof<T8>::res, meta_sizeof<T9>::res>::res};
  enum {max_align=meta_max<meta_alignof<T0>::res, meta_alignof<T1>::res,
                           meta_alignof<T2>::res, meta_alignof<T3>::res,
                           meta_alignof<T4>::res, meta_alignof<T5>::res,
                           meta_alignof<T6>::res, meta_alignof<T7>::res,
                           meta_alignof<T8>::res, meta_alignof<T9>::res>::res};
  typedef typename meta_align_n<max_align>::res atype_t;
  //--------------------------------------------------------------------------

  struct structor {void(*copy_ctor)(void*, const void*); void(*dtor)(void*);};
  static const structor s_structors[];
  uint8_t m_type_index;
  atype_t m_data[(max_size+sizeof(atype_t)-1)/sizeof(atype_t)];
};
PFC_SET_TYPE_TRAIT_PARTIAL10(typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9,
                             variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>,
                             is_type_pod_move,
                             is_type_pod_move<T0>::res && is_type_pod_move<T1>::res && is_type_pod_move<T2>::res && is_type_pod_move<T3>::res && is_type_pod_move<T4>::res && is_type_pod_move<T5>::res && is_type_pod_move<T6>::res && is_type_pod_move<T7>::res && is_type_pod_move<T8>::res && is_type_pod_move<T9>::res);
//----------------------------------------------------------------------------

//============================================================================
// variant::find_type
//============================================================================
template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
struct variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::find_type
{
  enum {res=tarray_t::template find<T>::res};
  PFC_CTC_ASSERT_MSG(res!=-1, type_not_found_from_the_variant);
};
//----------------------------------------------------------------------------


//============================================================================
// pod_variant
//============================================================================
template<typename T0,      typename T1=void, typename T2=void, typename T3=void, typename T4=void,
         typename T5=void, typename T6=void, typename T7=void, typename T8=void, typename T9=void>
class pod_variant
{
public:
  template<typename T> struct find_type;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE pod_variant();
  template<typename T> PFC_INLINE pod_variant(const T&);
  template<typename T> PFC_INLINE pod_variant(meta_type<T>);
  template<typename T> PFC_INLINE void operator=(const T&);
  template<typename T> PFC_INLINE void operator=(meta_type<T>);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE unsigned type_index() const;
  PFC_INLINE const void *data() const;
  #define PFC_POD_VARIANT_TFS template<typename U, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
  PFC_POD_VARIANT_TFS friend U &type_set(variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend U &type_ref(pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend const U &type_ref(const pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend volatile U &type_ref(volatile pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend const volatile U &type_ref(const volatile pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend U *type_ptr(pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend const U *type_ptr(const pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend volatile U *type_ptr(volatile pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend const volatile U *type_ptr(const volatile pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  #undef PFC_POD_VARIANT_TFS
  //--------------------------------------------------------------------------

private:
  template<class PE, typename T> PFC_INLINE void read_value(PE&, const meta_type<T>&, uint8_t type_index_);
  template<class PE> PFC_INLINE void read_value(PE&, const meta_type<void>&, uint8_t type_index_);
  template<class PE, typename T> PFC_INLINE void write_value(PE&, const meta_type<T>&);
  template<class PE> PFC_INLINE void write_value(PE&, const meta_type<void>&);
  //--------------------------------------------------------------------------

  typedef meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> tarray_t;
  enum {max_size=meta_max<meta_sizeof<T0>::res, meta_sizeof<T1>::res,
                          meta_sizeof<T2>::res, meta_sizeof<T3>::res,
                          meta_sizeof<T4>::res, meta_sizeof<T5>::res,
                          meta_sizeof<T6>::res, meta_sizeof<T7>::res,
                          meta_sizeof<T8>::res, meta_sizeof<T9>::res>::res};
  enum {max_align=meta_max<meta_alignof<T0>::res, meta_alignof<T1>::res,
                           meta_alignof<T2>::res, meta_alignof<T3>::res,
                           meta_alignof<T4>::res, meta_alignof<T5>::res,
                           meta_alignof<T6>::res, meta_alignof<T7>::res,
                           meta_alignof<T8>::res, meta_alignof<T9>::res>::res};
  typedef typename meta_align_n<max_align>::res atype_t;
  //--------------------------------------------------------------------------

  uint8_t m_type_index;
  atype_t m_data[(max_size+sizeof(atype_t)-1)/sizeof(atype_t)];
};
PFC_SET_TYPE_TRAIT_PARTIAL10(typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9,
                             pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, is_type_pod, true);
//----------------------------------------------------------------------------

//============================================================================
// pod_variant::find_type
//============================================================================
template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
struct pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::find_type
{
  enum {res=tarray_t::template find<T>::res};
  PFC_CTC_ASSERT_MSG(res!=-1, type_not_found_from_the_variant);
};
//----------------------------------------------------------------------------


//============================================================================
// poly_variant
//============================================================================
template<class B, unsigned max_size, unsigned align>
class poly_variant
{
public:
  // construction
  PFC_INLINE poly_variant();
  PFC_INLINE poly_variant(const poly_variant&);
  template<class C> PFC_INLINE poly_variant(const C&);
  template<class C> PFC_INLINE poly_variant(meta_type<C>);
  PFC_INLINE void operator=(const poly_variant&);
  template<class C> PFC_INLINE void operator=(const C&);
  template<class C> PFC_INLINE void operator=(meta_type<C>);
  PFC_INLINE void release();
  PFC_INLINE ~poly_variant();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE bool is_initialized() const;
  PFC_INLINE const B *operator->() const;
  PFC_INLINE B *operator->();
  PFC_INLINE const B &operator*() const;
  PFC_INLINE B &operator*();
  #define PFC_POLY_VARIANT_TFS template<class C, class B, unsigned max_size, unsigned align>
  PFC_POLY_VARIANT_TFS friend C &type_set(poly_variant<B, max_size, align>&);
  PFC_POLY_VARIANT_TFS friend C &type_ref(poly_variant<B, max_size, align>&);
  PFC_POLY_VARIANT_TFS friend const C &type_ref(const poly_variant<B, max_size, align>&);
  PFC_POLY_VARIANT_TFS friend volatile C &type_ref(volatile poly_variant<B, max_size, align>&);
  PFC_POLY_VARIANT_TFS friend const volatile C &type_ref(const volatile poly_variant<B, max_size, align>&);
  PFC_POLY_VARIANT_TFS friend C *type_ptr(poly_variant<B, max_size, align>&);
  PFC_POLY_VARIANT_TFS friend const C *type_ptr(const poly_variant<B, max_size, align>&);
  PFC_POLY_VARIANT_TFS friend volatile C *type_ptr(volatile poly_variant<B, max_size, align>&);
  PFC_POLY_VARIANT_TFS friend const volatile C *type_ptr(const volatile poly_variant<B, max_size, align>&);
  #undef PFC_POLY_VARIANT_TFS
  //--------------------------------------------------------------------------

private:
  PFC_CTC_ASSERT_MSG(is_type_poly<B>::res, base_class_must_be_polymorphic);
  PFC_CTC_ASSERT_MSG(max_size>=sizeof(B), max_size_must_be_greater_or_equal_to_base_class_size);
  //--------------------------------------------------------------------------

  typedef typename meta_align_n<align>::res atype_t;
  bool m_is_initialized;
  atype_t m_data[(max_size+sizeof(atype_t)-1)/sizeof(atype_t)];
};
PFC_SET_TYPE_TRAIT_PARTIAL3(class B, unsigned max_size, unsigned align, poly_variant<B, max_size, align>, is_type_pod_def_ctor, true);
//----------------------------------------------------------------------------


//============================================================================
// poly_pod_variant
//============================================================================
template<class B, unsigned max_size, unsigned align>
class poly_pod_variant
{
public:
  // construction
  PFC_INLINE poly_pod_variant();
  template<class C> PFC_INLINE poly_pod_variant(const C&);
  template<class C> PFC_INLINE poly_pod_variant(meta_type<C>);
  template<class C> PFC_INLINE void operator=(const C&);
  template<class C> PFC_INLINE void operator=(meta_type<C>);
  PFC_INLINE void release();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE bool is_initialized() const;
  PFC_INLINE const B *operator->() const;
  PFC_INLINE B *operator->();
  PFC_INLINE const B &operator*() const;
  PFC_INLINE B &operator*();
  #define PFC_POLY_POD_VARIANT_TFS template<class C, class B, unsigned max_size, unsigned align>
  PFC_POLY_POD_VARIANT_TFS friend C &type_set(poly_pod_variant<B, max_size, align>&);
  PFC_POLY_POD_VARIANT_TFS friend C &type_ref(poly_pod_variant<B, max_size, align>&);
  PFC_POLY_POD_VARIANT_TFS friend const C &type_ref(const poly_pod_variant<B, max_size, align>&);
  PFC_POLY_POD_VARIANT_TFS friend volatile C &type_ref(volatile poly_pod_variant<B, max_size, align>&);
  PFC_POLY_POD_VARIANT_TFS friend const volatile C &type_ref(const volatile poly_pod_variant<B, max_size, align>&);
  PFC_POLY_POD_VARIANT_TFS friend C *type_ptr(poly_pod_variant<B, max_size, align>&);
  PFC_POLY_POD_VARIANT_TFS friend const C *type_ptr(const poly_pod_variant<B, max_size, align>&);
  PFC_POLY_POD_VARIANT_TFS friend volatile C *type_ptr(volatile poly_pod_variant<B, max_size, align>&);
  PFC_POLY_POD_VARIANT_TFS friend const volatile C *type_ptr(const volatile poly_pod_variant<B, max_size, align>&);
  #undef PFC_POLY_POD_VARIANT_TFS
  //--------------------------------------------------------------------------

private:
  PFC_CTC_ASSERT_MSG(is_type_poly<B>::res, base_class_must_be_polymorphic);
  PFC_CTC_ASSERT_MSG(max_size>=sizeof(B), max_size_must_be_greater_or_equal_to_base_class_size);
  //--------------------------------------------------------------------------

  typedef typename meta_align_n<align>::res atype_t;
  bool m_is_initialized;
  atype_t m_data[(max_size+sizeof(atype_t)-1)/sizeof(atype_t)];
};
PFC_SET_TYPE_TRAIT_PARTIAL3(class B, unsigned max_size, unsigned align, poly_pod_variant<B, max_size, align>, is_type_pod, true);
//----------------------------------------------------------------------------

//============================================================================
#include "utils.inl"
} // namespace pfc
#endif
