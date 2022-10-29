//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_H
#define PFC_CORE_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core/config.h"
#include <new>
#include <typeinfo>
#include <string.h>
#include <stdint.h>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define NOMINMAX
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <windows.h>
namespace pfc
{

// new
#define PFC_BIG_ENDIAN 0
// sized types
typedef uint16_t float16_t;
typedef uint16_t ufloat16_t;
typedef float float32_t;
typedef float ufloat32_t;
typedef double float64_t;
typedef double ufloat64_t;
// ranged types
typedef float ufloat_t;     // [0, +inf]
typedef float float1_t;     // [-1, 1]
typedef float ufloat1_t;    // [0, 1]
typedef double udouble_t;   // [0, +inf]
typedef double double1_t;   // [-1, 1]
typedef double udouble1_t;  // [0, 1]
// aligned types
struct align_type_1  {PFC_ALIGN(1) int8_t dummy;};
struct align_type_2  {PFC_ALIGN(2) int16_t dummy;};
struct align_type_4  {PFC_ALIGN(4) int32_t dummy;};
struct align_type_8  {PFC_ALIGN(8) int64_t dummy;};
struct align_type_16 {PFC_ALIGN(16) int64_t dummy[2];};
template<unsigned> struct align_type;
// pointer related types
enum {ptr_size=sizeof(void*)};
#ifdef PFC_PLATFORM_32BIT
typedef uint32_t usize_t;
typedef int32_t ssize_t;
typedef uint64_t usize2_t;
#define PFC_PTR_SIZE 4
#elif defined(PFC_PLATFORM_64BIT)
typedef uint64_t usize_t;
typedef int64_t ssize_t;
#define PFC_PTR_SIZE 8
#endif
// logging
void log(const char*);
void logf(const char*, ...);
void log_indention();
void warn(const char*);
void warnf(const char*, ...);
void warn_indention();
void error(const char*);
void errorf(const char*, ...);
void error_indention();
void set_logging_funcs(void(*logf_)(const char*, usize_t), void(*warnf_)(const char*, usize_t), void(*errorf_)(const char*, usize_t));
void default_logging_func(const char*, usize_t);
void indent_log();
void unindent_log();
// aborting
bool preabort();
void set_preabort_func(bool(*preabort_)());
#define PFC_ABORT() {if(pfc::preabort()) PFC_ABORT_FUNC();}
// low-level memory management
struct alloc_site_info;
template<unsigned> static PFC_INLINE const alloc_site_info &get_alloc_site_info(const char *filename_, const char *funcname_, unsigned line_);
PFC_INLINE void *mem_alloc(usize_t num_bytes_, const alloc_site_info *site_info_=0);
template<typename T> PFC_INLINE T *mem_alloc(const alloc_site_info *site_info_=0);
PFC_INLINE void mem_free(void*);
void log_allocated_memory();
PFC_INLINE void mem_copy(void*, const void*, usize_t num_bytes_);
PFC_INLINE void mem_move(void*, const void*, usize_t num_bytes_);
PFC_INLINE void mem_zero(void*, usize_t num_bytes_);
PFC_INLINE void mem_set(void*, unsigned char, usize_t num_bytes_);
PFC_INLINE bool mem_eq(const void*, const void*, usize_t num_bytes_);
PFC_INLINE bool is_mem_zero(void*, usize_t num_bytes_);
PFC_INLINE int mem_diff(const void*, const void*, usize_t num_bytes_);
class memory_allocator_base;
class default_memory_allocator;
// pointer ops
template<typename T> T *ptr(T*);
template<typename T> bool is_valid(T*);
// object construction and destruction
template<typename T> PFC_INLINE T *array_new(usize_t num_items_, const alloc_site_info *site_info_=0);
template<typename T> PFC_INLINE void array_delete(const T*);
template<typename T> PFC_INLINE usize_t array_size(const T*);
template<typename T> PFC_INLINE void *destruct(const T*);
// ownership "smart" pointers
template<typename T> class owner_ptr;
template<typename T> class owner_ref;
class owner_data;
// casting
template<typename T, typename U> PFC_INLINE T raw_cast(U);
template<typename T, typename U> union raw_cast_union;
// min/max
template<typename T> PFC_INLINE T min(T, T);
template<typename T> PFC_INLINE T min(T, T, T);
template<typename T> PFC_INLINE T min(T, T, T, T);
template<typename T> PFC_INLINE T max(T, T);
template<typename T> PFC_INLINE T max(T, T, T);
template<typename T> PFC_INLINE T max(T, T, T, T);
template<typename T> struct minmax_res {T min, max;};
template<typename T> PFC_INLINE minmax_res<T> minmax(T, T);
template<typename T> PFC_INLINE minmax_res<T> minmax(T, T, T);
template<typename T> PFC_INLINE minmax_res<T> minmax(T, T, T, T);
// exception handling constructs
template<typename> class eh_data;        // RAII data pointer
class eh_dtor;                           // RAII destructor
template<typename> struct eh_array_dtor; // RAII array destructor
// raw data
struct raw_data;
//----------------------------------------------------------------------------


//============================================================================
// alloc_site_info
//============================================================================
struct alloc_site_info
{
  // construction
  PFC_INLINE alloc_site_info(const char *filename_, const char *funcname_, unsigned line_);
  //--------------------------------------------------------------------------

  const char *filename;
  const char *funcname;
  unsigned line;
};
//----------------------------------------------------------------------------


//============================================================================
// memory management & new/delete
//============================================================================
#ifdef PFC_BUILDOP_MEMORY_TRACKING
#define PFC_MEM_TRACK_STACK() memory_stack_entry memstack_entry(PFC_FUNCTION)
#define PFC_MEM_ALLOC(bytes__) pfc::mem_alloc(bytes__, &pfc::get_alloc_site_info<__COUNTER__>(__FILE__, PFC_FUNCTION, __LINE__))
#define PFC_NEW(type__) new(pfc::mem_alloc<type__ >(&pfc::get_alloc_site_info<__COUNTER__>(__FILE__, PFC_FUNCTION, __LINE__)))type__
#define PFC_ARRAY_NEW(type__, num_items__) pfc::array_new<type__ >(num_items__, &pfc::get_alloc_site_info<__COUNTER__>(__FILE__, PFC_FUNCTION, __LINE__))
#else
#define PFC_MEM_TRACK_STACK()
#define PFC_MEM_ALLOC(bytes__) pfc::mem_alloc(bytes__)
#define PFC_NEW(type__) new(pfc::mem_alloc<type__ >())type__
#define PFC_ARRAY_NEW(type__, num_items__) pfc::array_new<type__ >(num_items__)
#endif
#define PFC_STACK_MALLOC(bytes__) PFC_ALLOCA(bytes__)
#define PFC_ALIGNED_STACK_MALLOC(bytes__, alignment__) ((void*)((usize_t(PFC_ALLOCA(bytes__+alignment__))+alignment__)&-alignment__))
#define PFC_MEM_FREE(ptr__) pfc::mem_free(ptr__)
#define PFC_DELETE(ptr__) pfc::mem_free(pfc::destruct(ptr__))
#define PFC_ARRAY_DELETE(ptr__) pfc::array_delete(ptr__)
#define PFC_ARRAY_SIZE(ptr__) pfc::array_size(ptr__)
#define PFC_CARRAY_SIZE(array__) (sizeof(array__)/sizeof(*array__))
#define PFC_FWD_DELETE(ptr__) fwd_delete(ptr__)
#define PFC_PNEW(ptr__) new(ptr__)
//----------------------------------------------------------------------------


//============================================================================
// logging/warnings/errors
//============================================================================
// logging
#ifdef PFC_BUILDOP_LOGS
#define PFC_LOG(msg__) {pfc::log_indention(); pfc::logf msg__;}
#define PFC_LOGF(...)  {pfc::log_indention(); pfc::logf(__VA_ARGS__);}
#define PFC_INDENT_LOG() {pfc::indent_log();}
#define PFC_UNINDENT_LOG() {pfc::unindent_log();}
#else
#define PFC_LOG(msg__) (void*)0
#define PFC_LOGF(...) (void*)0
#define PFC_INDENT_LOG() (void*)0
#define PFC_UNINDENT_LOG() (void*)0
#endif
// warnings
#ifdef PFC_BUILDOP_WARNINGS_FILEPATH
#define PFC_WARN_PREFIX(str__) {pfc::warn_indention(); pfc::warnf("%s(%i) : " str__, __FILE__, __LINE__);}
#else
#define PFC_WARN_PREFIX(str__) {pfc::warn_indention(); pfc::warn(str__);}
#endif
#ifdef PFC_BUILDOP_WARNINGS
#define PFC_WARN(msg__)      {PFC_WARN_PREFIX("warning : "); pfc::warnf msg__;}
#define PFC_WARN_ONCE(msg__) {static bool s_is_first=true; if(s_is_first) {s_is_first=false; PFC_WARN_PREFIX("warning : "); pfc::warnf msg__;}}
#else
#define PFC_WARN(msg__)      (void*)0
#define PFC_WARN_ONCE(msg__) (void*)0
#endif
// errors
#ifdef PFC_BUILDOP_ERRORS_FILEPATH
#define PFC_ERROR_PREFIX(str__) {pfc::error_indention(); pfc::errorf("%s(%i) : " str__, __FILE__, __LINE__);}
#else
#define PFC_ERROR_PREFIX(str__) {pfc::error_indention(); pfc::error(str__);}
#endif
#ifdef PFC_BUILDOP_ERRORS
#define PFC_ERROR(msg__)     {PFC_ERROR_PREFIX("error : "); pfc::errorf msg__; PFC_ABORT();}
#define PFC_ERROR_NOT_IMPL() {PFC_ERROR_PREFIX("error : Functionality not implemented\r\n"); PFC_ABORT();}
#else
#define PFC_ERROR(msg__)     (void*)0
#define PFC_ERROR_NOT_IMPL() (void*)0
#endif
//----------------------------------------------------------------------------


//============================================================================
// asserts/checks
//============================================================================
// compile-time asserts (CTF=function and CTC=class scope asserts)
#define PFC_CTF_ASSERT(e__)             {struct cterror {char compile_time_assert_failed:(e__);};}
#define PFC_CTF_ASSERT_MSG(e__, msg__)  {struct cterror {char msg__:(e__);};}
#define PFC_CTC_ASSERT(e__)             struct PFC_CAT2(ctassert_at_line_, __LINE__) {enum {is_ok=(e__)!=0}; char compile_time_assert_failed:is_ok;}
#define PFC_CTC_ASSERT_MSG(e__, msg__)  struct PFC_CAT2(ctassert_at_line_, __LINE__) {enum {is_ok=(e__)!=0}; char msg__:is_ok;}
#define PFC_CTF_ERROR(type__, msg__)    {struct cterror {char msg__:sizeof(type__)==0;};}
#define PFC_CTC_ERROR(type__, msg__)    static struct PFC_CAT2(ctassert_at_line_, __LINE__) {char msg__:sizeof(type__)==0;} PFC_CAT2(ctassert, __LINE__);
// run-time asserts
#ifdef PFC_BUILDOP_ASSERTS
#define PFC_ASSERT(e__)            {if(!(e__)) {PFC_ERROR_PREFIX("assert failed : "#e__"\r\n"); PFC_ABORT();}}
#define PFC_ASSERT_MSG(e__, msg__) {if(!(e__)) {PFC_ERROR_PREFIX("assert failed : "); pfc::errorf msg__; PFC_ABORT();}}
#define PFC_ASSERT_CALL(e__)       {e__;}
#else
#define PFC_ASSERT(e__)            {}
#define PFC_ASSERT_MSG(e__, msg__) {}
#define PFC_ASSERT_CALL(e__)       {}
#endif
// run-time checks
#ifdef PFC_BUILDOP_CHECKS
#define PFC_CHECK(e__)                   {if(!(e__)) {PFC_ERROR_PREFIX("check failed : "#e__"\r\n"); PFC_ABORT();}}
#define PFC_CHECK_MSG(e__, msg__)        {if(!(e__)) {PFC_ERROR_PREFIX("check failed : "); pfc::errorf msg__; PFC_ABORT();}}
#define PFC_CHECK_CALL(e__)              {e__;}
#define PFC_CHECK_WARN(e__, msg__)       {if(!(e__)) {PFC_WARN_PREFIX("warning : "); pfc::warnf msg__;}}
#define PFC_CHECK_WARN_ONCE(e__, msg__)  {static bool s_is_first=true; if(s_is_first && !(e__)) {s_is_first=false; PFC_WARN_PREFIX("warning : "); pfc::warnf msg__;}}
#define PFC_VERIFY(e__)                  PFC_CHECK(e__)
#define PFC_VERIFY_MSG(e__, msg__)       PFC_CHECK_MSG(e__, msg__)
#define PFC_VERIFY_WARN(e__, msg__)      PFC_CHECK_WARN(e__, msg__)
#define PFC_VERIFY_WARN_ONCE(e__, msg__) PFC_CHECK_WARN_ONCE(e__, msg__)
#else
#define PFC_CHECK(e__)                   {}
#define PFC_CHECK_MSG(e__, msg__)        {}
#define PFC_CHECK_CALL(e__)              {}
#define PFC_CHECK_WARN(e__, msg__)       {}
#define PFC_CHECK_WARN_ONCE(e__, msg__)  {}
#define PFC_VERIFY(e__)                  {(e__);}
#define PFC_VERIFY_MSG(e__, msg__)       {(e__);}
#define PFC_VERIFY_WARN(e__, msg__)      {(e__);}
#define PFC_VERIFY_WARN_ONCE(e__, msg__) {(e__);}
#endif
// pedantic asserts/checks
#ifdef PFC_BUILDOP_PEDANTIC
#define PFC_ASSERT_PEDANTIC(e__)            PFC_ASSERT(e__)
#define PFC_ASSERT_PEDANTIC_MSG(e__, msg__) PFC_ASSERT_MSG(e__, msg__)
#define PFC_ASSERT_PEDANTIC_CALL(e__)       PFC_ASSERT_CALL(e__)
#define PFC_CHECK_PEDANTIC(e__)             PFC_CHECK(e__)
#define PFC_CHECK_PEDANTIC_MSG(e__, msg__)  PFC_CHECK_MSG(e__, msg__)
#define PFC_CHECK_PEDANTIC_CALL(e__)        PFC_CHECK_CALL(e__)
#else
#define PFC_ASSERT_PEDANTIC(e__)            {}
#define PFC_ASSERT_PEDANTIC_MSG(e__, msg__) {}
#define PFC_ASSERT_PEDANTIC_CALL(e__)       {}
#define PFC_CHECK_PEDANTIC(e__)             {}
#define PFC_CHECK_PEDANTIC_MSG(e__, msg__)  {}
#define PFC_CHECK_PEDANTIC_CALL(e__)        {}
#endif
//----------------------------------------------------------------------------


//============================================================================
// misc
//============================================================================
#define PFC_OFFSETOF(type__, mvar__) ((usize_t)&(((type__*)0)->mvar__))
#define PFC_OFFSETOF_MVARPTR(type__, mvarptr__) ((usize_t)&(((type__*)0)->*mvarptr__))   /* todo: temp workaround of a gcc bug */
#define PFC_NOTHROW throw()
#define PFC_SAFE_ADDREF(v__) {if(v__) {(v__)->AddRef();}}
#define PFC_SAFE_RELEASE(v__) {if(v__) {(v__)->Release(); v__=0;}}
//----------------------------------------------------------------------------


//============================================================================
// memory tracking
//============================================================================
#define PFC_MEM_TRACK_STACK_DEPTH 4
enum {memory_align=16,
      max_memory_stack_depth=256};
//----------------------------------------------------------------------------

struct memory_info
{
  usize_t num_items;
#ifdef PFC_BUILDOP_MEMORY_TRACKING
  const alloc_site_info *site_info;
  memory_info *prev, *next;
#if PFC_MEM_TRACK_STACK_DEPTH>0
  const char *stack[PFC_MEM_TRACK_STACK_DEPTH];
#endif
  static memory_info s_head;
#endif
};
//----

enum {memory_info_size=((sizeof(memory_info)+memory_align-1)/memory_align)*memory_align,
      memory_flag_typeless=0x80000000};
//----------------------------------------------------------------------------

struct memory_stack_entry
{
  // construction
  PFC_INLINE memory_stack_entry(const char *func_);
  PFC_INLINE ~memory_stack_entry();
  //--------------------------------------------------------------------------

  static PFC_THREAD_VAR const char *s_stack[max_memory_stack_depth];
  static PFC_THREAD_VAR unsigned s_stack_depth;
};
//----------------------------------------------------------------------------


//============================================================================
// memory_allocator_base
//============================================================================
class memory_allocator_base
{
public:
  // construction
  PFC_INLINE memory_allocator_base();
  virtual PFC_INLINE ~memory_allocator_base();
  virtual void check_allocator(usize_t num_bytes_, usize_t mem_align_)=0;
  //--------------------------------------------------------------------------

  // memory management
  virtual void *alloc(usize_t num_bytes_, usize_t mem_align_=memory_align)=0;
  virtual void free(void*)=0;
  //--------------------------------------------------------------------------

private:
  memory_allocator_base (const memory_allocator_base&); // not implemented
  void operator=(const memory_allocator_base&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// default_memory_allocator
//============================================================================
class default_memory_allocator: public memory_allocator_base
{
public:
  // construction
  static PFC_INLINE default_memory_allocator& inst();
  virtual void check_allocator(usize_t num_bytes_, usize_t mem_align_);
  //--------------------------------------------------------------------------

  // memory management
  virtual void *alloc(usize_t num_bytes_, usize_t mem_align_=memory_align);
  virtual void free(void*);
  //--------------------------------------------------------------------------

private:
  default_memory_allocator();
  virtual ~default_memory_allocator();
  default_memory_allocator(const default_memory_allocator&); // not implemented
  void operator=(const default_memory_allocator&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// raw_cast_union
//============================================================================
template<typename T, typename U>
union raw_cast_union
{
  T first;
  U second;
};
//----------------------------------------------------------------------------


//============================================================================
// owner_ptr
//============================================================================
template<typename T>
class owner_ptr
{
public:
  // nested types
  typedef T type;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE owner_ptr();
  PFC_INLINE owner_ptr(T*);
  PFC_INLINE owner_ptr(const owner_ptr&);
  template<typename U> PFC_INLINE owner_ptr(const owner_ptr<U>&);
  template<typename U> PFC_INLINE owner_ptr(const owner_ref<U>&);
  PFC_INLINE void operator=(T*);
  PFC_INLINE void operator=(const owner_ptr&);
  template<typename U> PFC_INLINE void operator=(const owner_ptr<U>&);
  template<typename U> PFC_INLINE void operator=(const owner_ref<U>&);
  PFC_INLINE ~owner_ptr();
  //--------------------------------------------------------------------------
  
  // accessors
  PFC_INLINE friend bool is_valid(const owner_ptr &ptr_)  {return ptr_.data!=0;}
  PFC_INLINE T *operator->() const;
  PFC_INLINE T &operator*() const;
  PFC_INLINE friend T *ptr(const owner_ptr &ptr_)         {return ptr_.data;}
  //--------------------------------------------------------------------------

  mutable T *data;
};
//----------------------------------------------------------------------------


//============================================================================
// owner_ref
//============================================================================
template<typename T>
class owner_ref
{
public:
  // nested types
  typedef T type;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE owner_ref(T*);
  PFC_INLINE owner_ref(const owner_ref&);
  template<typename U> PFC_INLINE owner_ref(const owner_ref<U>&);
  template<typename U> PFC_INLINE owner_ref(const owner_ptr<U>&);
  PFC_INLINE ~owner_ref();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE T *operator->() const;
  PFC_INLINE T &operator*() const;
  PFC_INLINE friend T *ptr(const owner_ref &ref_)  {return ref_.data;}
  //--------------------------------------------------------------------------

  mutable T *data;
  //--------------------------------------------------------------------------

private:
  void operator=(const owner_ref&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// owner_data
//============================================================================
class owner_data
{
public:
  // construction
  PFC_INLINE owner_data();
  PFC_INLINE owner_data(void*);
  PFC_INLINE owner_data(const owner_data&);
  PFC_INLINE void operator=(void*);
  PFC_INLINE void operator=(const owner_data&);
  PFC_INLINE ~owner_data();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE friend bool is_valid(const owner_data &data_)  {return data_.data!=0;}
  PFC_INLINE friend void *ptr(const owner_data &data_)      {return data_.data;}
  //--------------------------------------------------------------------------

  mutable void *data;
};
//----------------------------------------------------------------------------


//============================================================================
// eh_data
//============================================================================
template<typename T>
class eh_data
{
public:
  // construction
  PFC_INLINE eh_data(memory_allocator_base&, usize_t size_, usize_t align_); /* todo: instead of passing alignment, should use meta_alignof<T>::res in implementation, but not done due to meta.h dependency*/
  PFC_INLINE ~eh_data();
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  T *data;
  //--------------------------------------------------------------------------

private:
  eh_data(const eh_data&); // not implemented
  void operator=(const eh_data&); // not implemented
  //--------------------------------------------------------------------------

#ifdef PFC_BUILDOP_EXCEPTIONS
  memory_allocator_base &m_allocator;
#endif
};
//----------------------------------------------------------------------------


//============================================================================
// eh_dtor
//============================================================================
#ifdef PFC_BUILDOP_EXCEPTIONS
#define PFC_EDTOR(dtor__, method__) pfc::eh_dtor exception_destructor(dtor__, method__)
#define PFC_EDTOR_RESET() {exception_destructor.reset();}
#else
#define PFC_EDTOR(dtor__, method__) {}
#define PFC_EDTOR_RESET() {}
#endif
//----------------------------------------------------------------------------

class eh_dtor
{
public:
  // construction
  template<typename T> PFC_INLINE eh_dtor(T &dtor_, void(T::*method_)());
  PFC_INLINE ~eh_dtor();
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

private:
#ifdef PFC_BUILDOP_EXCEPTIONS
  eh_dtor *m_dtor;
  void(eh_dtor::*m_method)();
#endif
};
//----------------------------------------------------------------------------


//============================================================================
// eh_array_dtor
//============================================================================
template<typename T>
struct eh_array_dtor
{
  // destruction
  PFC_INLINE eh_array_dtor();
  PFC_INLINE eh_array_dtor(T *begin_, T *dst_);
  PFC_INLINE ~eh_array_dtor();
  //----

  T *begin, *dst;
};
//----------------------------------------------------------------------------


//============================================================================
// raw_data
//============================================================================
struct raw_data
{
  // construction
  PFC_INLINE raw_data();
  PFC_INLINE raw_data(usize_t bytes_);
  PFC_INLINE ~raw_data();
  PFC_INLINE void alloc(usize_t num_bytes_);
  PFC_INLINE void free();
  PFC_INLINE void swap(raw_data&);
  //--------------------------------------------------------------------------

  usize_t size;
  void *data;
  //--------------------------------------------------------------------------

private:
  raw_data(const raw_data&); // not implemented
  void operator=(const raw_data&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
#include "core.inl"
} // namespace pfc
#endif
