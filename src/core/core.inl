//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// align_type
//============================================================================
template<unsigned> struct align_type {PFC_CTC_ASSERT_MSG(0, given_alignment_doesnt_have_type);};
template<> struct align_type<0>  {typedef void res;};
template<> struct align_type<1>  {typedef align_type_1 res;};
template<> struct align_type<2>  {typedef align_type_2 res;};
template<> struct align_type<4>  {typedef align_type_4 res;};
template<> struct align_type<8>  {typedef align_type_8 res;};
template<> struct align_type<16> {typedef align_type_16 res;};
//----------------------------------------------------------------------------


//============================================================================
// alloc_site_info
//============================================================================
alloc_site_info::alloc_site_info(const char *filename_, const char *funcname_, unsigned line_)
  :filename(filename_)
  ,funcname(funcname_)
  ,line(line_)
{
}
//----

template<unsigned>
static PFC_INLINE const alloc_site_info &get_alloc_site_info(const char *filename_, const char *funcname_, unsigned line_)
{
  static const alloc_site_info s_site_info(filename_, funcname_, line_);
  return s_site_info;
}
//----------------------------------------------------------------------------


//============================================================================
// low-level memory management
//============================================================================
PFC_INLINE void *mem_alloc(usize_t num_bytes_, const alloc_site_info *site_info_)
{
#ifdef PFC_BUILDOP_MEMORY_TRACKING
  memory_info *info=(memory_info*)PFC_ALIGNED_MALLOC(num_bytes_+memory_info_size, memory_align);
  PFC_ASSERT_MSG(info, ("Memory allocation of %u bytes failed\r\n", num_bytes_+memory_info_size));
  info->site_info=site_info_;
  info->num_items=memory_flag_typeless|num_bytes_;
  extern void add_memory_info(memory_info&);
  add_memory_info(*info);
  return ((char*)info)+memory_info_size;
#else
  return PFC_ALIGNED_MALLOC(num_bytes_, memory_align);
#endif
}
//----

template<typename T>
PFC_INLINE T *mem_alloc(const alloc_site_info *site_info_)
{
#ifdef PFC_BUILDOP_MEMORY_TRACKING
  memory_info *info=(memory_info*)PFC_ALIGNED_MALLOC(sizeof(T)+memory_info_size, memory_align);
  PFC_ASSERT_MSG(info, ("Memory allocation of %u bytes failed\r\n", sizeof(T)+memory_info_size));
  info->num_items=usize_t(memory_flag_typeless)|sizeof(T);
  info->site_info=site_info_;
  extern void add_memory_info(memory_info&);
  add_memory_info(*info);
  return (T*)(((char*)info)+memory_info_size);
#else
  return (T*)PFC_ALIGNED_MALLOC(sizeof(T), memory_align);
#endif
}
//----

PFC_INLINE void mem_free(void *p_)
{
#ifdef PFC_BUILDOP_MEMORY_TRACKING
  if(p_)
  {
    memory_info *info=(memory_info*)(((char*)p_)-memory_info_size);
    extern void remove_memory_info(memory_info&);
    remove_memory_info(*info);
    PFC_ALIGNED_FREE(info);
  }
#else
  PFC_ALIGNED_FREE(p_);
#endif
}
//----

PFC_INLINE void mem_copy(void *dst_, const void *src_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || (dst_ && src_));
  PFC_ASSERT_PEDANTIC_MSG(!num_bytes_ || dst_==src_ || (dst_<src_ && ((char*)dst_)+num_bytes_<=src_) || (dst_>src_ && ((char*)src_)+num_bytes_<=dst_),
                          ("Overlapping memory regions for mem_copy() result in undefined behavior\r\n"));
  ::memcpy(dst_, src_, (size_t)num_bytes_);
}
//----

PFC_INLINE void mem_move(void *dst_, const void *src_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || (dst_ && src_));
  ::memmove(dst_, src_, (size_t)num_bytes_);
}
//----

PFC_INLINE void mem_zero(void *p_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || p_);
  ::memset(p_, 0, (size_t)num_bytes_);
}
//----

PFC_INLINE void mem_set(void *p_, unsigned char c_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || p_);
  ::memset(p_, c_, (size_t)num_bytes_);
}
//----

PFC_INLINE bool mem_eq(const void *p0_, const void *p1_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || (p0_ && p1_));
  return ::memcmp(p0_, p1_, (size_t)num_bytes_)==0;
}
//----

PFC_INLINE bool is_mem_zero(void *p_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || p_);
  const char *p=(const char*)p_;
  return *p==0 && ::memcmp(p, p+1, num_bytes_-1)==0;
}
//----

PFC_INLINE int mem_diff(const void *p0_, const void *p1_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || (p0_ && p1_));
  return ::memcmp(p0_, p1_, (size_t)num_bytes_);
}
//----------------------------------------------------------------------------


//============================================================================
// memory tracking
//============================================================================
memory_stack_entry::memory_stack_entry(const char *func_)
{
  PFC_ASSERT_PEDANTIC(s_stack_depth<max_memory_stack_depth);
  s_stack[s_stack_depth++]=func_;
}
//----

memory_stack_entry::~memory_stack_entry()
{
  --s_stack_depth;
}
//----------------------------------------------------------------------------


//============================================================================
// memory_allocator_base
//============================================================================
memory_allocator_base::memory_allocator_base()
{
}
//----

memory_allocator_base::~memory_allocator_base()
{
}
//----------------------------------------------------------------------------


//============================================================================
// default_memory_allocator
//============================================================================
PFC_INLINE default_memory_allocator &default_memory_allocator::inst()
{
  static default_memory_allocator s_allocator;
  return s_allocator;
}
//----------------------------------------------------------------------------


//============================================================================
// pointer ops
//============================================================================
template<typename T> T *ptr(T *p_)
{
  return p_;
}
//----

template<typename T> bool is_valid(T *p_)
{
  return p_!=0;
}
//----------------------------------------------------------------------------


//============================================================================
// owner_ptr
//============================================================================
template<typename T>
owner_ptr<T>::owner_ptr()
  :data(0)
{
}
//----

template<typename T>
owner_ptr<T>::owner_ptr(T *p_)
  :data(p_)
{
}
//----

template<typename T>
owner_ptr<T>::owner_ptr(const owner_ptr &ptr_)
  :data(ptr_.data)
{
  ptr_.data=0;
}
//----

template<typename T>
template<typename U>
owner_ptr<T>::owner_ptr(const owner_ptr<U> &ptr_)
  :data(ptr_.data)
{
  ptr_.data=0;
}
//----

template<typename T>
template<typename U>
owner_ptr<T>::owner_ptr(const owner_ref<U> &ref_)
  :data(ref_.data)
{
  PFC_ASSERT_PEDANTIC(ref_.data);
  ref_.data=0;
}
//----

template<typename T>
void owner_ptr<T>::operator=(T *p_)
{
  if(data!=p_)
  {
    priv::delete_helper<is_type_fwd_delete<T>::res>::delete_ptr(data);
    data=p_;
  }
}
//----

template<typename T>
void owner_ptr<T>::operator=(const owner_ptr &ptr_)
{
  if(this!=&ptr_)
  {
    priv::delete_helper<is_type_fwd_delete<T>::res>::delete_ptr(data);
    data=ptr_.data;
    ptr_.data=0;
  }
}
//----

template<typename T>
template<typename U>
void owner_ptr<T>::operator=(const owner_ptr<U> &ptr_)
{
  priv::delete_helper<is_type_fwd_delete<T>::res>::delete_ptr(data);
  data=ptr_.data;
  ptr_.data=0;
}
//----

template<typename T>
template<typename U>
void owner_ptr<T>::operator=(const owner_ref<U> &ref_)
{
  PFC_ASSERT_PEDANTIC(ref_.data);
  priv::delete_helper<is_type_fwd_delete<T>::res>::delete_ptr(data);
  data=ref_.data;
  ref_.data=0;
}
//----

template<typename T>
owner_ptr<T>::~owner_ptr()
{
  priv::delete_helper<is_type_fwd_delete<T>::res>::delete_ptr(data);
}
//----------------------------------------------------------------------------

template<typename T>
T *owner_ptr<T>::operator->() const
{
  PFC_ASSERT_PEDANTIC_MSG(data, ("Dereferencing \"%s\" NULL pointer\r\n", typeid(T).name()));
  return data;
}
//----

template<typename T>
T &owner_ptr<T>::operator*() const
{
  PFC_ASSERT_PEDANTIC_MSG(data, ("Dereferencing \"%s\" NULL pointer\r\n", typeid(T).name()));
  return *data;
}
//----------------------------------------------------------------------------


//============================================================================
// owner_ref
//============================================================================
template<typename T>
owner_ref<T>::owner_ref(T *p_)
  :data(p_)
{
  PFC_ASSERT_PEDANTIC(p_);
}
//----

template<typename T>
owner_ref<T>::owner_ref(const owner_ref &ref_)
  :data(ref_.data)
{
  PFC_ASSERT_PEDANTIC(ref_.data);
  ref_.data=0;
}
//----

template<typename T>
template<typename U>
owner_ref<T>::owner_ref(const owner_ref<U> &ref_)
  :data(ref_.data)
{
  PFC_ASSERT_PEDANTIC(ref_.data);
  ref_.data=0;
}
//----

template<typename T>
template<typename U>
owner_ref<T>::owner_ref(const owner_ptr<U> &ptr_)
  :data(ptr_.data)
{
  PFC_ASSERT_PEDANTIC(ptr_.data);
  ptr_.data=0;
}
//----

template<typename T>
owner_ref<T>::~owner_ref()
{
  priv::delete_helper<is_type_fwd_delete<T>::res>::delete_ptr(data);
}
//----------------------------------------------------------------------------

template<typename T>
T *owner_ref<T>::operator->() const
{
  PFC_ASSERT_PEDANTIC_MSG(data, ("Dereferencing \"%s\" NULL pointer\r\n", typeid(T).name()));
  return data;
}
//----

template<typename T>
T &owner_ref<T>::operator*() const
{
  PFC_ASSERT_PEDANTIC_MSG(data, ("Dereferencing \"%s\" NULL pointer\r\n", typeid(T).name()));
  return *data;
}
//----------------------------------------------------------------------------


//============================================================================
// owner_data
//============================================================================
owner_data::owner_data()
{
  data=0;
}
//----

owner_data::owner_data(void *p_)
{
  data=p_;
}
//----

owner_data::owner_data(const owner_data &ptr_)
{
  data=ptr_.data;
  ptr_.data=0;
}
//----

void owner_data::operator=(void *p_)
{
  if(data!=p_)
  {
    PFC_MEM_FREE(data);
    data=p_;
  }
}
//----

void owner_data::operator=(const owner_data &ptr_)
{
  if(this!=&ptr_)
  {
    PFC_MEM_FREE(data);
    data=ptr_.data;
    ptr_.data=0;
  }
}
//----

owner_data::~owner_data()
{
  PFC_MEM_FREE(data);
}
//----------------------------------------------------------------------------


//============================================================================
// raw_cast
//============================================================================
template<typename T, typename U>
PFC_INLINE T raw_cast(U v_)
{
  PFC_CTF_ASSERT_MSG(sizeof(T)==sizeof(U), source_and_destination_types_must_have_equal_size);
  return reinterpret_cast<const T&>(v_);
}
//----------------------------------------------------------------------------


//============================================================================
// min/max
//============================================================================
template<typename T>
PFC_INLINE T min(T v0_, T v1_)
{
  // return minimum of the two
  return v0_<v1_?v0_:v1_;
}
//----

template<typename T>
PFC_INLINE T min(T v0_, T v1_, T v2_)
{
  // return minimum of the three
  T v=v0_<v1_?v0_:v1_;
  return v<v2_?v:v2_;
}
//----

template<typename T>
PFC_INLINE T min(T v0_, T v1_, T v2_, T v3_)
{
  // return minimum of the four
  T v=v0_<v1_?v0_:v1_;
  v=v<v2_?v:v2_;
  return v<v3_?v:v3_;
}
//----

template<typename T>
PFC_INLINE T max(T v0_, T v1_)
{
  // return maximum of the two
  return v1_<v0_?v0_:v1_;
}
//----

template<typename T>
PFC_INLINE T max(T v0_, T v1_, T v2_)
{
  // return maximum of the three
  T v=v1_<v0_?v0_:v1_;
  return v2_<v?v:v2_;
}
//----

template<typename T>
PFC_INLINE T max(T v0_, T v1_, T v2_, T v3_)
{
  // return maximum of the four
  T v=v1_<v0_?v0_:v1_;
  v=v2_<v?v:v2_;
  return v3_<v?v:v3_;
}
//----

template<typename T>
PFC_INLINE minmax_res<T> minmax(T v0_, T v1_)
{
  minmax_res<T> res;
  if(v0_<v1_)
  {
    res.min=v0_;
    res.max=v1_;
  }
  else
  {
    res.min=v1_;
    res.max=v0_;
  }
  return res;
}
//----

template<typename T>
PFC_INLINE minmax_res<T> minmax(T v0_, T v1_, T v2_)
{
  minmax_res<T> res;
  if(v0_<v1_)
  {
    res.min=v0_;
    res.max=v1_;
  }
  else
  {
    res.min=v1_;
    res.max=v0_;
  }
  if(v2_<res.min)
    res.min=v2_;
  else
    if(res.max<v2_)
      res.max=v2_;
  return res;
}
//----

template<typename T>
PFC_INLINE minmax_res<T> minmax(T v0_, T v1_, T v2_, T v3_)
{
  minmax_res<T> res;
  if(v0_<v1_)
  {
    res.min=v0_;
    res.max=v1_;
  }
  else
  {
    res.min=v1_;
    res.max=v0_;
  }
  if(v2_<res.min)
    res.min=v2_;
  else
    if(res.max<v2_)
      res.max=v2_;
  if(v3_<res.min)
    res.min=v3_;
  else
    if(res.max<v3_)
      res.max=v3_;
  return res;
}
//----------------------------------------------------------------------------


//============================================================================
// eh_data
//============================================================================
template<typename T>
eh_data<T>::eh_data(memory_allocator_base &alloc_, usize_t size_, usize_t align_)
#ifdef PFC_BUILDOP_EXCEPTIONS
  :m_allocator(alloc_)
#endif
{
  data=size_?(T*)alloc_.alloc(sizeof(T)*size_, align_):0;
}
//----

template<typename T>
eh_data<T>::~eh_data()
{
#ifdef PFC_BUILDOP_EXCEPTIONS
  m_allocator.free(data);
#endif
}
//----

template<typename T>
void eh_data<T>::reset()
{
#ifdef PFC_BUILDOP_EXCEPTIONS
  data=0;
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// eh_dtor
//============================================================================
template<typename T>
eh_dtor::eh_dtor(T &dtor_, void(T::*method_)())
{
#ifdef PFC_BUILDOP_EXCEPTIONS
  m_dtor=(eh_dtor*)&dtor_;
  m_method=(void(eh_dtor::*)())method_;
#endif
}
//----

eh_dtor::~eh_dtor()
{
#ifdef PFC_BUILDOP_EXCEPTIONS
  if(m_dtor)
    (m_dtor->*m_method)();
#endif
}
//----

void eh_dtor::reset()
{
#ifdef PFC_BUILDOP_EXCEPTIONS
  m_dtor=0;
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// eh_array_dtor
//============================================================================
template<typename T>
eh_array_dtor<T>::eh_array_dtor()
{
  begin=0;
  dst=0;
}
//----

template<typename T>
eh_array_dtor<T>::eh_array_dtor(T *begin_, T *dst_)
{
  begin=begin_;
  dst=dst_;
}
//----

template<typename T>
eh_array_dtor<T>::~eh_array_dtor()
{
#ifdef PFC_BUILDOP_EXCEPTIONS
  if(begin)
  {
    if(dst>begin)
      while(dst--!=begin)
        dst->~T();
    else
      while(dst++!=begin)
        dst->~T();
  }
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// raw_data
//============================================================================
raw_data::raw_data()
{
  size=0;
  data=0;
}
//----

raw_data::raw_data(usize_t bytes_)
{
  size=bytes_;
  data=PFC_MEM_ALLOC(bytes_);
}
//----

raw_data::~raw_data()
{
  PFC_MEM_FREE(data);
}
//----

void raw_data::alloc(usize_t num_bytes_)
{
  if(size!=num_bytes_)
  {
    free();
    size=num_bytes_;
    data=size?PFC_MEM_ALLOC(size):0;
  }
}
//----

void raw_data::free()
{
  PFC_MEM_FREE(data);
  data=0;
  size=0;
}
//----

void raw_data::swap(raw_data &data_)
{
  // swap raw data contents
  usize_t temp_size=size;
  void *temp_data=data;
  size=data_.size;
  data=data_.data;
  data_.size=temp_size;
  data_.data=temp_data;
}
//----------------------------------------------------------------------------
