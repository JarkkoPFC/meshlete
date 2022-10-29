//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// swap
//============================================================================
namespace priv
{
  template<typename T>
  static PFC_INLINE void swap_impl(T &v0_, T &v1_, meta_case<0> is_type_non_class_)
  {
    // swap values
    T t=v0_;
    v0_=v1_;
    v1_=t;
  }
  //----

  template<typename T>
  static PFC_INLINE void swap_impl(T &v0_, T &v1_, meta_case<1> is_type_pod_move_)
  {
    // swap values
    char tmp[sizeof(T)];
    mem_copy(&tmp, &v0_, sizeof(T));
    mem_copy(&v0_, &v1_, sizeof(T));
    mem_copy(&v1_, &tmp, sizeof(T));
  }
  //----

  template<typename T>
  static PFC_INLINE void swap_impl(T &v0_, T &v1_, meta_case<2> default_)
  {
    // swap values
    T v=v0_;
    v0_.~T();
    PFC_PNEW(&v0_)T(v1_);
    v1_.~T();
    PFC_PNEW(&v1_)T(v);
  }
} // namespace priv
//----

template<typename T>
PFC_INLINE void swap(T &v0_, T &v1_)
{
  priv::swap_impl(v0_, v1_, meta_case<!is_type_class<T>::res?0:is_type_pod_move<T>::res?1:2>());
}
//----

template<typename T>
PFC_INLINE void swap(T *s0_, T *s1_, usize_t count_)
{
  // swap values between arrays
  if(count_)
  {
    T *end=s0_+count_;
    do
    {
      priv::swap_impl(*s0_++, *s1_++, meta_case<!is_type_class<T>::res?0:is_type_pod_move<T>::res?1:2>());
    } while(s0_<end);
  }
}
//----------------------------------------------------------------------------


//============================================================================
// swap_bytes
//============================================================================
namespace priv
{
  static PFC_INLINE uint8_t swap_bytes(const void *p_, meta_int<1>)
  {
    return *reinterpret_cast<const uint8_t*>(p_);
  }
  //----

  static PFC_INLINE uint16_t swap_bytes(const void *p_, meta_int<2>)
  {
#ifdef PFC_INTRINSIC_BSWAP16
    uint16_t v;
    PFC_INTRINSIC_BSWAP16(v, p_);
    return v;
#else
    uint16_t v=*reinterpret_cast<const uint16_t*>(p_);
    return v<<8|v>>8;
#endif
  }
  //----

  static PFC_INLINE uint32_t swap_bytes(const void *p_, meta_int<4>)
  {
#ifdef PFC_INTRINSIC_BSWAP32
    uint32_t v;
    PFC_INTRINSIC_BSWAP32(v, p_);
    return v;
#else
    uint32_t v=*reinterpret_cast<const uint32_t*>(p_);
    return (v<<24)|(v<<8&0xff0000)|(v>>8&0xff00)|(v>>24);
#endif
  }
  //----

  static PFC_INLINE uint64_t swap_bytes(const void *p_, meta_int<8>)
  {
#ifdef PFC_INTRINSIC_BSWAP64
    uint64_t v;
    PFC_INTRINSIC_BSWAP64(v, p_);
    return v;
#else
    uint64_t v=*reinterpret_cast<const uint64_t*>(p_);
    return  (v<<56)|(v>>56)|(v<<40&PFC_CONST_UINT64(0xff000000000000))
           |(v>>40&0xff00)|(v<<24&PFC_CONST_UINT64(0xff0000000000))
           |(v>>24&0xff0000)|(v<<8&PFC_CONST_UINT64(0xff00000000))
           |(v>>8&0xff000000);
#endif
  }
  //----

  static PFC_INLINE void swap_bytes(void *p_, usize_t count_, meta_int<1>)
  {
    return;
  }
  //----

  static PFC_INLINE void swap_bytes(void *p_, usize_t count_, meta_int<2>)
  {
    // swap bytes for an array of values
    uint16_t *p=(uint16_t*)p_, *end=p+count_;
    if(count_)
      do
      {
#ifdef PFC_INTRINSIC_BSWAP16
        PFC_INTRINSIC_BSWAP16(*p, p);
#else
        uint16_t v=*p;
        *p=v<<8 | v>>8;
#endif
        ++p;
      } while(p!=end);
  }
  //----

  static PFC_INLINE void swap_bytes(void *p_, usize_t count_, meta_int<4>)
  {
    // swap bytes for an array of values
    uint32_t *p=(uint32_t*)p_, *end=p+count_;
    if(count_)
      do
      {
#ifdef PFC_INTRINSIC_BSWAP32
        PFC_INTRINSIC_BSWAP32(*p, p);
#else
        uint32_t v=*p;
        *p=(v<<24) | (v<<8&0xff0000) | (v>>8&0xff00) | (v>>24);
#endif
        ++p;
      } while(p!=end);
  }
  //----

  static PFC_INLINE void swap_bytes(void *p_, usize_t count_, meta_int<8>)
  {
    // swap bytes for an array of values
    uint64_t *p=(uint64_t*)p_, *end=p+count_;
    if(count_)
      do
      {
#ifdef PFC_INTRINSIC_BSWAP64
        PFC_INTRINSIC_BSWAP64(*p, p);
#else
        uint64_t v=*p;
        *p= (v<<56)|(v>>56)|(v<<40&PFC_CONST_UINT64(0xff000000000000))
           |(v>>40&0xff00)|(v<<24&PFC_CONST_UINT64(0xff0000000000))
           |(v>>24&0xff0000)|(v<<8&PFC_CONST_UINT64(0xff00000000))
           |(v>>8&0xff000000);
#endif
        ++p;
      } while(p!=end);
  }
} // namespace priv
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE T swap_bytes(T v_)
{
  PFC_CTF_ASSERT_MSG(!is_type_class<T>::res, unable_to_swap_bytes_of_a_class_type);
  return raw_cast<T>(priv::swap_bytes(&v_, meta_int<sizeof(T)>()));
}
//----

template<typename T>
PFC_INLINE void swap_bytes(T *a_, usize_t count_)
{
  PFC_CTF_ASSERT_MSG(!is_type_class<T>::res, unable_to_swap_bytes_of_a_class_type);
  priv::swap_bytes(a_, count_, meta_int<sizeof(T)>());
}
//----------------------------------------------------------------------------


//============================================================================
// to_little/big_endian
//============================================================================
template<typename T>
PFC_INLINE T to_little_endian(T v_)
{
#if PFC_BIG_ENDIAN==0
  return v_;
#else
  return raw_cast<T>(priv::swap_bytes(&v_, meta_int<sizeof(T)>()));
#endif
}
//----

template<typename T>
PFC_INLINE T to_big_endian(T v_)
{
#if PFC_BIG_ENDIAN==0
  return raw_cast<T>(priv::swap_bytes(&v_, meta_int<sizeof(T)>()));
#else
  return v_;
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// array construction/destruction
//============================================================================
namespace priv
{
  //==========================================================================
  // default_construct
  //==========================================================================
  template<typename T>
  PFC_INLINE void default_construct(T *dst_, usize_t count_, meta_bool<true> is_type_pod_def_ctor_)
  {
    mem_zero(dst_, sizeof(T)*count_);
  }
  //----

  template<typename T>
  PFC_INLINE void default_construct(T *dst_, usize_t count_, meta_bool<false> is_type_pod_def_ctor_)
  {
    // default construct an array of values
    if(count_)
    {
      eh_array_dtor<T> v(dst_, dst_);
      T *end=dst_+count_;
      do
      {
        PFC_PNEW(v.dst)T;
      } while(++v.dst!=end);
      v.begin=0;
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // copy_construct
  //==========================================================================
  template<typename T>
  PFC_INLINE void copy_construct(T *dst_, const T *src_, usize_t count_, meta_bool<true> is_type_pod_copy_)
  {
    mem_copy(dst_, src_, sizeof(T)*count_);
  }
  //----

  template<typename T>
  PFC_INLINE void copy_construct(T *dst_, const T *src_, usize_t count_, meta_bool<false> is_type_pod_copy_)
  {
    // copy construct an array of values from an array
    if(count_)
    {
      eh_array_dtor<T> v(dst_, dst_);
      T *end=dst_+count_;
      do
      {
        PFC_PNEW(v.dst)T(*src_++);
      } while(++v.dst!=end);
      v.begin=0;
    }
  }
  //----

  template<typename T>
  PFC_INLINE void copy_construct(T *dst_, const T &v_, usize_t count_, meta_bool<true> is_type_pod_copy_)
  {
    // copy construct an array of values from an value
    if(count_)
    {
      T *end=dst_+count_;
      do
      {
        PFC_PNEW(dst_)T(v_);
      } while(++dst_!=end);
    }
  }
  //----

  template<typename T>
  PFC_INLINE void copy_construct(T *dst_, const T &v_, usize_t count_, meta_bool<false> is_type_pod_copy_)
  {
    // copy construct an array of values from an value
    if(count_)
    {
      eh_array_dtor<T> v(dst_, dst_);
      T *end=dst_+count_;
      do
      {
        PFC_PNEW(v.dst)T(v_);
      } while(++v.dst!=end);
      v.begin=0;
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // move_construct
  //==========================================================================
  template<typename T>
  PFC_INLINE void move_construct(T *dst_, T *src_, usize_t count_, meta_bool<true> is_type_pod_move_)
  {
    mem_move(dst_, src_, sizeof(T)*count_);
  }
  //----

  template<typename T>
  PFC_INLINE void move_construct(T *dst_, T *src_, usize_t count_, meta_bool<false> is_type_pod_move_)
  {
    // move construct an array of values
    if(count_)
    {
      if(dst_<src_)
      {
        // move items starting from the begin of the array
        T *end=src_+count_;
        do
        {
          PFC_PNEW(dst_++)T(*src_);
          src_->~T();
        } while(++src_!=end);
      }
      else
      {
        // move items starting from the end of the array
        T *end=src_;
        dst_+=count_;
        src_+=count_;
        do
        {
          PFC_PNEW(--dst_)T(*--src_);
          src_->~T();
        } while(src_!=end);
      }
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // rotate_sequence_left
  //==========================================================================
  template<typename T>
  PFC_INLINE void rotate_sequence_left(T *first_, T *last_, meta_bool<true> is_type_pod_move_)
  {
    // rotate sequence of move-POD values to the left
    char tmp[sizeof(T)];
    mem_copy(&tmp, first_, sizeof(T));
    mem_move(first_, first_+1, usize_t(last_-first_)*sizeof(T));
    mem_copy(last_, &tmp, sizeof(T));
  }
  //----

  template<typename T>
  PFC_INLINE void rotate_sequence_left(T *first_, T *last_, meta_bool<false> is_type_pod_move_)
  {
    // rotate sequence of values to the left
    T tmp(*first_);
    first_->~T();
    while(first_!=last_)
    {
      PFC_PNEW(first_)T(*(first_+1));
      (++first_)->~T();
    }
    PFC_PNEW(last_)T(tmp);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // rotate_sequence_right
  //==========================================================================
  template<typename T>
  PFC_INLINE void rotate_sequence_right(T *first_, T *last_, meta_bool<true> is_type_pod_move_)
  {
    // rotate sequence of move-POD values to the right
    char tmp[sizeof(T)];
    mem_copy(&tmp, last_, sizeof(T));
    mem_move(first_+1, first_, usize_t(last_-first_)*sizeof(T));
    mem_copy(first_, &tmp, sizeof(T));
  }
  //----

  template<typename T>
  PFC_INLINE void rotate_sequence_right(T *first_, T *last_, meta_bool<false> is_type_pod_move_)
  {
    // rotate sequence of values to the right
    T tmp(*last_);
    last_->~T();
    while(last_!=first_)
    {
      PFC_PNEW(last_)T(*(last_-1));
      (--last_)->~T();
    }
    PFC_PNEW(last_)T(tmp);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // destruct
  //==========================================================================
  PFC_INLINE void destruct(void*, usize_t, meta_bool<true> is_type_pod_dtor_)
  {
  }
  //----

  template<typename T>
  PFC_INLINE void destruct(T *dst_, usize_t count_, meta_bool<false> is_type_pod_dtor_)
  {
    // destruct an array of values
    if(count_)
    {
      T *end=dst_+count_;
      do
      {
        dst_->~T();
      } while(++dst_!=end);
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // reverse_default_construct
  //==========================================================================
  template<typename T>
  PFC_INLINE void reverse_default_construct(T *dst_, usize_t count_, meta_bool<true> is_type_pod_def_ctor_)
  {
    mem_zero(dst_, sizeof(T)*count_);
  }
  //----

  template<typename T>
  PFC_INLINE void reverse_default_construct(T *dst_, usize_t count_, meta_bool<false> is_type_pod_def_ctor_)
  {
    // default construct an array of values in reverse order
    if(count_)
    {
      dst_+=count_-1;
      eh_array_dtor<T> v(dst_, dst_);
      T *end=dst_-count_;
      do
      {
        PFC_PNEW(v.dst)T;
      } while(--v.dst!=end);
      v.begin=0;
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // reverse_copy_construct
  //==========================================================================
  template<typename T>
  PFC_INLINE void reverse_copy_construct(T *dst_, const T *src_, usize_t count_, meta_bool<true> is_type_pod_copy_)
  {
    // copy construct an array of values from an array in reverse order
    if(count_)
    {
      dst_+=count_-1;
      T *end=dst_-count_;
      do
      {
        PFC_PNEW(dst_)T(*src_++);
      } while(--dst_!=end);
    }
  }
  //----

  template<typename T>
  PFC_INLINE void reverse_copy_construct(T *dst_, const T *src_, usize_t count_, meta_bool<false> is_type_pod_copy_)
  {
    // copy construct an array of values from an array in reverse order
    if(count_)
    {
      dst_+=count_-1;
      eh_array_dtor<T> v(dst_, dst_);
      T *end=dst_-count_;
      do
      {
        PFC_PNEW(v.dst)T(*src_++);
      } while(--v.dst!=end);
      v.begin=0;
    }
  }
  //----

  template<typename T>
  PFC_INLINE void reverse_copy_construct(T *dst_, const T &v_, usize_t count_, meta_bool<true> is_type_pod_copy_)
  {
    // copy construct an array of value from an value in reverse order
    if(count_)
    {
      dst_+=count_-1;
      T *end=dst_-count_;
      do
      {
        PFC_PNEW(dst_)T(v_);
      } while(--dst_!=end);
    }
  }
  //----

  template<typename T>
  PFC_INLINE void reverse_copy_construct(T *dst_, const T &v_, usize_t count_, meta_bool<false> is_type_pod_copy_)
  {
    // copy construct an array of value from an value in reverse order
    if(count_)
    {
      dst_+=count_-1;
      eh_array_dtor<T> v(dst_, dst_);
      T *end=dst_-count_;
      do
      {
        PFC_PNEW(v.dst)T(v_);
      } while(--v.dst!=end);
      v.begin=0;
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // reverse_move_construct
  //==========================================================================
  template<typename T>
  PFC_INLINE void reverse_move_construct(T *dst_, T *src_, usize_t count_, meta_bool<true> is_type_pod_move_)
  {
    // move construct an array of values in reverse order
    if(count_)
    {
      dst_+=count_;
      T *end=src_+count_;
      do
      {
        PFC_PNEW(--dst_)T(*src_);
      } while(++src_!=end);
    }
  }
  //----

  template<typename T>
  PFC_INLINE void reverse_move_construct(T *dst_, T *src_, usize_t count_, meta_bool<false> is_type_pod_move_)
  {
    // move construct an array of values in reverse order
    if(count_)
    {
      dst_+=count_;
      T *end=src_+count_;
      do
      {
        PFC_PNEW(--dst_)T(*src_);
        src_->~T();
      } while(++src_!=end);
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // reverse_destruct
  //==========================================================================
  PFC_INLINE void reverse_destruct(void*, usize_t, meta_bool<true> is_type_pod_dtor_)
  {
  }
  //----

  template<typename T>
  PFC_INLINE void reverse_destruct(T *dst_, usize_t count_, meta_bool<false> is_type_pod_dtor_)
  {
    // destruct an array of values in reverse order
    if(count_)
    {
      T *end=dst_;
      dst_+=count_;
      do
      {
        (--dst_)->~T();
      } while(dst_!=end);
    }
  }
  //--------------------------------------------------------------------------
} // namespace priv
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE void default_construct(T *dst_, usize_t count_)
{
  // default construct an array
  priv::default_construct(dst_, count_, meta_bool<is_type_pod_def_ctor<T>::res>());
}
//----

template<typename T>
PFC_INLINE void copy_construct(T *dst_, const T *src_, usize_t count_)
{
  // copy construct an array from an array
  PFC_ASSERT_PEDANTIC_MSG(dst_+count_<=src_ || src_+count_<=dst_, ("Memory regions may not overlap\r\n"));
  priv::copy_construct(dst_, src_, count_, meta_bool<is_type_pod_copy<T>::res>());
}
//----

template<typename T>
PFC_INLINE void copy_construct(T *dst_, const T &v_, usize_t count_)
{
  // copy construct an array from a value
  PFC_ASSERT_PEDANTIC_MSG(dst_+count_<=&v_ || dst_>&v_, ("Target array overwrites the source value\r\n"));
  if(count_)
    priv::copy_construct(dst_, v_, count_, meta_bool<is_type_pod_copy<T>::res>());
}
//----

template<typename T>
PFC_INLINE void move_construct(T *dst_, T *src_, usize_t count_)
{
  // move construct an array
  priv::move_construct(dst_, src_, count_, meta_bool<is_type_pod_move<T>::res>());
}
//----

template<typename T>
PFC_INLINE void rotate_sequence_left(T *first_, T *last_)
{
  // rotate sequence of values one item to the left
  PFC_ASSERT_PEDANTIC_MSG(first_ && first_<=last_, ("First pointer must be non-zero and precede the last pointer (first: %p, last: %p)\r\n", first_, last_));
  priv::rotate_sequence_left(first_, last_, meta_bool<is_type_pod_move<T>::res>());
}
//----

template<typename T>
PFC_INLINE void rotate_sequence_right(T *first_, T *last_)
{
  // rotate sequence of values one item to the right
  PFC_ASSERT_PEDANTIC_MSG(first_ && first_<=last_, ("First pointer must be non-zero and precede the last pointer (first: %p, last: %p)\r\n", first_, last_));
  priv::rotate_sequence_right(first_, last_, meta_bool<is_type_pod_move<T>::res>());
}
//----

template<typename T>
PFC_INLINE void destruct(T *dst_, usize_t count_)
{
  // destruct an array
  priv::destruct(dst_, count_, meta_bool<is_type_pod_dtor<T>::res>());
}
//----------------------------------------------------------------------------


template<typename T>
PFC_INLINE void reverse_default_construct(T *dst_, usize_t count_)
{
  // default construct an array in reverse order
  priv::reverse_default_construct(dst_, count_, meta_bool<is_type_pod_def_ctor<T>::res>());
}
//----

template<typename T>
PFC_INLINE void reverse_copy_construct(T *dst_, const T *src_, usize_t count_)
{
  // copy construct an array from an array in reverse order
  PFC_ASSERT_PEDANTIC_MSG(dst_+count_<=src_ || src_+count_<=dst_, ("Memory regions may not overlap\r\n"));
  priv::reverse_copy_construct(dst_, src_, count_, meta_bool<is_type_pod_copy<T>::res>());
}
//----

template<typename T>
PFC_INLINE void reverse_copy_construct(T *dst_, const T &v_, usize_t count_)
{
  // copy construct an array from a value in reverse order
  PFC_ASSERT_PEDANTIC_MSG(dst_+count_<=&v_ || dst_>&v_, ("Target array overwrites the source value\r\n"));
  if(count_)
    priv::reverse_copy_construct(dst_, v_, count_, meta_bool<is_type_pod_copy<T>::res>());
}
//----

template<typename T>
PFC_INLINE void reverse_move_construct(T *dst_, T *src_, usize_t count_)
{
  // move construct an array in reverse order
  PFC_ASSERT_PEDANTIC_MSG(dst_+count_<=src_ || src_+count_<=dst_, ("Memory regions may not overlap\r\n"));
  priv::reverse_move_construct(dst_, src_, count_, meta_bool<is_type_pod_move<T>::res>());
}
//----

template<typename T>
PFC_INLINE void reverse_destruct(T *dst_, usize_t count_)
{
  // destruct an array in reverse order
  priv::reverse_destruct(dst_, count_, meta_bool<is_type_pod_dtor<T>::res>());
}
//----------------------------------------------------------------------------


//============================================================================
// rng_simple
//============================================================================
rng_simple::rng_simple(uint32_t seed_)
{
  set_seed(seed_);
}
//----

void rng_simple::set_seed(uint32_t seed_)
{
  m_w=seed_^0x82e9b275;
  m_z=seed_^0x2eb15b0f;
  if(!m_w || m_w==0x464fffff)
    ++m_w;
  if(!m_z || m_z==0x9068ffff)
    ++m_z;
}
//----

ufloat1_t rng_simple::rand_ureal1() const
{
  // return random (unsigned) real value in range [0, 1]
  m_z=36969*(m_z&65535)+(m_z>>16);
  m_w=18000*(m_w&65535)+(m_w>>16);
  return raw_cast<ufloat1_t>((((m_z<<16)+m_w)&0x007fffff)|0x3f800000)-1.0f;
}
//----

float1_t rng_simple::rand_real1() const
{
  // return random real value in range [-1, 1]
  m_z=36969*(m_z&65535)+(m_z>>16);
  m_w=18000*(m_w&65535)+(m_w>>16);
  return raw_cast<ufloat1_t>((((m_z<<16)+m_w)&0x007fffff)|0x3f800000)*2.0f-3.0f;
}
//----------------------------------------------------------------------------


//============================================================================
// hash_func
//============================================================================
namespace priv
{
  PFC_INLINE unsigned hash_func_idx(const volatile void *p_, meta_int<1>)
  {
    // return index for 8-bit value
    return *reinterpret_cast<const volatile uint8_t*>(p_);
  }
  //----

  PFC_INLINE unsigned hash_func_idx(const volatile void *p_, meta_int<2>)
  {
    // return index for 16-bit value (by Thomas Wang)
    uint32_t k=*reinterpret_cast<const volatile uint16_t*>(p_);
    k=~k+(k<<15);
    k=k^(k>>12);
    k=k+(k<<2);
    k=k^(k>>4);
    k=k*2057; // k=(k+(k<<3))+(k<<11);
    return k^(k>>16);
  }
  //----

  PFC_INLINE unsigned hash_func_idx(const volatile void *p_, meta_int<4>)
  {
    // return index for 32-bit value (by Thomas Wang)
    uint32_t k=*reinterpret_cast<const volatile uint32_t*>(p_);
    k=~k+(k<<15);
    k=k^(k>>12);
    k=k+(k<<2);
    k=k^(k>>4);
    k=k*2057; // k=(k+(k<<3))+(k<<11);
    return k^(k>>16);
  }
  //----

  PFC_INLINE unsigned hash_func_idx(const volatile void *p_, meta_int<8>)
  {
    // return index for 64-bit value (by Thomas Wang)
    uint64_t k=*reinterpret_cast<const volatile uint64_t*>(p_);
    k=(~k)+(k<<18);
    k=k^(k>>31);
    k=k*21; // k=(k+(k<<2))+(k<<4);
    k=k^(k>>11);
    k=k+(k<<6);
    return unsigned(k^(k>>22));
  }
} // namespace priv
//----------------------------------------------------------------------------

template<typename K>
unsigned hash_func<K>::index(K k_)
{
  PFC_CTF_ASSERT_MSG(!is_type_class<K>::res, hash_func_must_be_specialized_for_class_types);
  return priv::hash_func_idx(&k_, meta_int<sizeof(K)>());
}
//----------------------------------------------------------------------------

template<typename T>
unsigned hash_func<T*>::index(const volatile T *p_)
{
  usize_t pv=usize_t(p_)>>meta_log2<meta_alignof<T>::res>::res;
  return priv::hash_func_idx(&pv, meta_int<sizeof(usize_t)>());
}
//----------------------------------------------------------------------------


//============================================================================
// fourcc_id
//============================================================================
fourcc_id::fourcc_id()
{
  m_id=0;
}
//----

fourcc_id::fourcc_id(uint32_t id32_)
{
  PFC_ASSERT_PEDANTIC_MSG(!id32_ || id32_==filter_id32(id32_), ("FourCC ID contains invalid characters\r\n"));
  m_id=id32_;
}
//----

fourcc_id::fourcc_id(const char *str_)
{
  set(str_);
}
//----

void fourcc_id::set(uint32_t id32_)
{
  PFC_ASSERT_PEDANTIC_MSG(!id32_ || id32_==filter_id32(id32_), ("FourCC ID contains invalid characters\r\n"));
  m_id=id32_;
}
//----

void fourcc_id::set(const char *str_)
{
  // set FourCC from string
  m_id=0;
  for(unsigned i=0; i<4; ++i)
  {
    uint8_t c=*str_++;
    if(!c)
      break;
    m_id=(m_id<<8)|c;
  }
  m_id=filter_id32(m_id);
}
//----------------------------------------------------------------------------

bool fourcc_id::operator==(const fourcc_id &id_) const
{
  return m_id==id_.m_id;
}
//----

bool fourcc_id::operator!=(const fourcc_id &id_) const
{
  return m_id!=id_.m_id;
}
//----

bool fourcc_id::operator==(uint32_t id32_) const
{
  return m_id==id32_;
}
//----

bool fourcc_id::operator!=(uint32_t id32_) const
{
  return m_id!=id32_;
}
//----

uint32_t fourcc_id::id32() const
{
  return m_id;
}
//----

void fourcc_id::c_str(fourcc_cstr str_) const
{
  // return string for the id
  str_[0]=m_id>>24;
  str_[1]=(m_id>>16)&255;
  str_[2]=(m_id>>8)&255;
  str_[3]=m_id&255;
  str_[4]=0;
}
//----------------------------------------------------------------------------


//============================================================================
// pair
//============================================================================
template<typename T, typename U>
pair<T, U>::pair()
{
}
//----

template<typename T, typename U>
pair<T, U>::pair(const T &first_, const U &second_)
  :first(first_)
  ,second(second_)
{
}
//----------------------------------------------------------------------------

template<typename T, typename U>
PFC_INLINE pair<T, U> make_pair(const T &p0_, const U &p1_)
{
  return pair<T, U>(p0_, p1_);
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(const pair<T, U> &p0_, const pair<T, U> &p1_)
{
  return p0_.first==p1_.first && p0_.second==p1_.second;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(const pair<T, U> &p_, const T &v_)
{
  return p_.first==v_;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(const pair<T, U> &p0_, const pair<T, U> &p1_)
{
  return p0_.first!=p1_.first || p0_.second!=p1_.second;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(const pair<T, U> &p_, const T &v_)
{
  return p_.first!=v_;
}
//----------------------------------------------------------------------------


//============================================================================
// hash_func<pair>
//============================================================================
template<typename T, typename U>
struct hash_func<pair<T, U> >
{
  static PFC_INLINE unsigned index(const pair<T, U> &p_)
  {
    return (hash_func<T>::index(p_.first)+hash_func<U>::index(p_.second));
  }
};
//----------------------------------------------------------------------------


//============================================================================
// radix_sort_predicate<pair>
//============================================================================
template<typename T, typename U, bool ascending_>
unsigned radix_sort_predicate<pair<T, U>, ascending_>::radix(const pair<T, U> &v_, unsigned pass_) const
{
  typedef typename meta_type_array<int8_t, int16_t, int32_t, int64_t>::get<meta_log2<sizeof(T)>::res>::res cast_type;
  return ((ascending_?(cast_type&)v_.first:-(cast_type&)v_.first)>>(pass_*8))&0xff;
}
//----------------------------------------------------------------------------


//============================================================================
// compare_sort_predicate<pair>
//============================================================================
template<typename T, typename U, bool ascending_>
bool compare_sort_predicate<pair<T, U>, ascending_>::before(const pair<T, U> &v0_, const pair<T, U> &v1_) const
{
  return ascending_?v0_.first<v1_.first:v1_.first<v0_.first;
}
//----------------------------------------------------------------------------


//============================================================================
// functor
//============================================================================
template<typename R>
functor<R()>::functor()
  :m_this(0)
  ,m_func(0)
{
}
//----

template<typename R>
functor<R()>::functor(R(*func_)())
  :m_this(0)
  ,m_func((void*)func_)
{
}
//----

template<typename R>
template<class T, class U>
functor<R()>::functor(T &this_, R(*func_)(U&))
  :m_this((void*)static_cast<U*>(&this_))
  ,m_func((void*)func_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<T, U>::res), object_does_not_have_compatible_type_with_the_function_signature);
}
//----

template<typename R>
R functor<R()>::operator()() const
{
  // call member/free function
  PFC_ASSERT_PEDANTIC(m_func!=0);
  return m_this?(*(R(*)(void*))m_func)(m_this):(*(R(*)())m_func)();
}
//----

template<typename R>
functor<R()>::operator bool() const
{
  return m_func!=0;
}
//----

template<typename R>
void functor<R()>::clear()
{
  m_func=0;
}
//----------------------------------------------------------------------------

template<typename R>
template<class T, R(T::*mem_fun)()>
R functor<R()>::call_mem_func(T &this_)
{
  return (this_.*mem_fun)();
}
//----

template<typename R>
template<class T, R(T::*mem_fun)() const>
R functor<R()>::call_cmem_func(const T &this_)
{
  return (this_.*mem_fun)();
}
//----

template<typename R>
template<class T, R(T::*mem_fun)() volatile>
R functor<R()>::call_vmem_func(volatile T &this_)
{
  return (this_.*mem_fun)();
}
//----

template<typename R>
template<class T, R(T::*mem_fun)() const volatile>
R functor<R()>::call_cvmem_func(const volatile T &this_)
{
  return (this_.*mem_fun)();
}
//----------------------------------------------------------------------------

template<class T, class U, typename R>
PFC_INLINE functor<R()> make_functor(T &v_, R(*func_)(U&))
{
  return functor<R()>(v_, func_);
}
//----------------------------------------------------------------------------

#define PFC_FUNCTOR_TMPL()\
  template<typename R, PFC_FUNCTOR_TEMPLATE_ARG_LIST>\
  class functor<R(PFC_FUNCTOR_TYPE_LIST)>\
  {\
  public:\
    PFC_INLINE functor()                                                                           :m_this(0), m_func(0) {}\
    PFC_INLINE functor(R(*func_)(PFC_FUNCTOR_TYPE_LIST))                                           :m_this(0), m_func((void*)func_) {}\
    template<class T, class U> PFC_INLINE functor(T &this_, R(*func_)(U&, PFC_FUNCTOR_TYPE_LIST))  :m_this((void*)static_cast<U*>(&this_)), m_func((void*)func_) {PFC_CTF_ASSERT_MSG((is_type_derived<T, U>::res), object_does_not_have_compatible_type_with_the_function_signature);}\
    inline R operator()(PFC_FUNCTOR_PROTO_ARG_LIST) const                                          {PFC_ASSERT_PEDANTIC(m_func!=0); return m_this?(*(R(*)(void*, PFC_FUNCTOR_TYPE_LIST))m_func)(m_this, PFC_FUNCTOR_ARG_LIST):(*(R(*)(PFC_FUNCTOR_TYPE_LIST))m_func)(PFC_FUNCTOR_ARG_LIST);}\
    PFC_INLINE operator bool() const                                                               {return m_func!=0;}\
    PFC_INLINE void clear()                                                                        {m_func=0;}\
    template<class T, R(T::*mem_fun)(PFC_FUNCTOR_TYPE_LIST)> static R call_mem_func(T &this_, PFC_FUNCTOR_PROTO_ARG_LIST) {return (this_.*mem_fun)(PFC_FUNCTOR_ARG_LIST);}\
    template<class T, R(T::*mem_fun)(PFC_FUNCTOR_TYPE_LIST) const> static R call_cmem_func(const T &this_, PFC_FUNCTOR_PROTO_ARG_LIST) {return (this_.*mem_fun)(PFC_FUNCTOR_ARG_LIST);}\
    template<class T, R(T::*mem_fun)(PFC_FUNCTOR_TYPE_LIST) volatile> static R call_vmem_func(volatile T &this_, PFC_FUNCTOR_PROTO_ARG_LIST) {return (this_.*mem_fun)(PFC_FUNCTOR_ARG_LIST);}\
    template<class T, R(T::*mem_fun)(PFC_FUNCTOR_TYPE_LIST) const volatile> static R call_cvmem_func(const volatile T &this_, PFC_FUNCTOR_PROTO_ARG_LIST) {return (this_.*mem_fun)(PFC_FUNCTOR_ARG_LIST);}\
  private:\
    void *m_this;\
    void *m_func;\
  };\
  template<class T, class U, typename R, PFC_FUNCTOR_TEMPLATE_ARG_LIST> functor<R(PFC_FUNCTOR_TYPE_LIST)> make_functor(T &v_, R(*func_)(U&, PFC_FUNCTOR_TYPE_LIST)) {return functor<R(PFC_FUNCTOR_TYPE_LIST)>(v_, func_);}
//----

// functor 1 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0
#define PFC_FUNCTOR_TYPE_LIST A0
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_
#define PFC_FUNCTOR_ARG_LIST a0_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 2 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1
#define PFC_FUNCTOR_TYPE_LIST A0, A1
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 3 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 4 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 5 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3, typename A4
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3, A4
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_, a4_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 6 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3, typename A4, typename A5
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3, A4, A5
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_, a4_, a5_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 7 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3, A4, A5, A6
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_, a4_, a5_, a6_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 8 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3, A4, A5, A6, A7
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_, a4_, a5_, a6_, a7_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 9 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3, A4, A5, A6, A7, A8
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_, A8 a8_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 10 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3, A4, A5, A6, A7, A8, A9
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_, A8 a8_, A9 a9_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_, a9_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
//----
#undef PFC_FUNCTOR_TMPL
//----------------------------------------------------------------------------


//============================================================================
// mem_func/cmem_func
//============================================================================
template<typename R>
mem_func<R()>::mem_func()
  :m_mem_func(0)
{
}
//----

template<typename R>
template<class T>
mem_func<R()>::mem_func(R(T::*mf_)())
  :m_mem_func(reinterpret_cast<R(mem_func::*)()>(mf_))
{
}
//----

template<typename R>
template<class T>
R mem_func<R()>::operator()(T &v_) const
{
  PFC_ASSERT_PEDANTIC(m_mem_func!=0);
  return (v_.*reinterpret_cast<R(T::*)()>(m_mem_func))();
}
//----

template<typename R>
mem_func<R()>::operator bool() const
{
  return m_mem_func!=0;
}
//----------------------------------------------------------------------------

template<typename R>
cmem_func<R()>::cmem_func()
  :m_mem_func(0)
{
}
//----

template<typename R>
cmem_func<R()>::cmem_func(const mem_func<R()> &mf_)
  :m_mem_func(reinterpret_cast<R(cmem_func::*)()>(mf_.m_mem_func))
{
}
//----

template<typename R>
template<class T>
cmem_func<R()>::cmem_func(R(T::*mf_)() const)
  :m_mem_func(reinterpret_cast<R(cmem_func::*)() const>(mf_))
{
}
//----

template<typename R>
template<class T>
R cmem_func<R()>::operator()(const T &v_) const
{
  PFC_ASSERT_PEDANTIC(m_mem_func!=0);
  return (v_.*reinterpret_cast<R(T::*)() const>(m_mem_func))();
}
//----

template<typename R>
cmem_func<R()>::operator bool() const
{
  return m_mem_func!=0;
}
//----------------------------------------------------------------------------

template<class T, typename R>
PFC_INLINE mem_func<R()> make_mem_func(R(T::*mf_)())
{
  return mem_func<R()>(mf_);
}
//----

template<class T, typename R>
PFC_INLINE cmem_func<R()> make_mem_func(R(T::*mf_)() const)
{
  return cmem_func<R()>(mf_);
}
//----------------------------------------------------------------------------

#define PFC_MEM_FUNC_TMPL(type_list__, proto_arg_list__, cproto_arg_list__, arg_list__)\
  template<typename R, PFC_MEM_FUNC_ARG>\
  class mem_func<R type_list__>\
  {\
  public:\
    PFC_INLINE mem_func()                                            :m_mem_func(0) {}\
    template<class T> PFC_INLINE mem_func(R(T::*mf_)type_list__)     :m_mem_func(reinterpret_cast<R(mem_func::*)type_list__>(mf_)) {}\
    template<class T> inline R operator()proto_arg_list__ const      {PFC_ASSERT_PEDANTIC(m_mem_func!=0); return (v_.*reinterpret_cast<R(T::*)type_list__>(m_mem_func))arg_list__;}\
    PFC_INLINE operator bool() const                                 {return m_mem_func!=0;}\
  private:\
    friend class cmem_func<R type_list__>;\
    R(mem_func::*m_mem_func)type_list__;\
  };\
  template<typename R, PFC_MEM_FUNC_ARG>\
  class cmem_func<R type_list__>\
  {\
  public:\
    PFC_INLINE cmem_func()                                               :m_mem_func(0) {}\
    PFC_INLINE cmem_func(const mem_func<R type_list__> &mf_)             :m_mem_func(reinterpret_cast<R(cmem_func::*)type_list__ const>(mf_.m_mem_func)) {}\
    template<class T> PFC_INLINE cmem_func(R(T::*mf_)type_list__ const)  :m_mem_func(reinterpret_cast<R(cmem_func::*)type_list__ const>(mf_)) {}\
    template<class T> inline R operator()cproto_arg_list__ const         {PFC_ASSERT_PEDANTIC(m_mem_func!=0); return (v_.*reinterpret_cast<R(T::*)type_list__ const>(m_mem_func))arg_list__;}\
    PFC_INLINE operator bool() const                                     {return m_mem_func!=0;}\
  private:\
    R(cmem_func::*m_mem_func)type_list__ const;\
  };\
  template<class T, typename R, PFC_MEM_FUNC_ARG> PFC_INLINE  mem_func<R type_list__> make_mem_func(R(T::*mf_)type_list__)        {return mem_func<R type_list__>(mf_);}\
  template<class T, typename R, PFC_MEM_FUNC_ARG> PFC_INLINE cmem_func<R type_list__> make_mem_func(R(T::*mf_)type_list__ const)  {return cmem_func<R type_list__>(mf_);}
//----

#define PFC_MEM_FUNC_ARG typename A0
PFC_MEM_FUNC_TMPL((A0), (T &v_, A0 a0_), (const T &v_, A0 a0_), (a0_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1
PFC_MEM_FUNC_TMPL((A0, A1), (T &v_, A0 a0_, A1 a1_), (const T &v_, A0 a0_, A1 a1_), (a0_, a1_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2
PFC_MEM_FUNC_TMPL((A0, A1, A2), (T &v_, A0 a0_, A1 a1_, A2 a2_), (const T &v_, A0 a0_, A1 a1_, A2 a2_), (a0_, a1_, a2_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_), (a0_, a1_, a2_, a3_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3, typename A4
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3, A4), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_), (a0_, a1_, a2_, a3_, a4_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3, typename A4, typename A5
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3, A4, A5), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_), (a0_, a1_, a2_, a3_, a4_, a5_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3, A4, A5, A6), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_), (a0_, a1_, a2_, a3_, a4_, a5_, a6_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3, A4, A5, A6, A7), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_), (a0_, a1_, a2_, a3_, a4_, a5_, a6_, a7_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3, A4, A5, A6, A7, A8), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_, A8 a8_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_, A8 a8_), (a0_, a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_, A8 a8_, A9 a9_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_, A8 a8_, A9 a9_), (a0_, a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_, a9_));
#undef PFC_MEM_FUNC_ARG
#undef PFC_MEM_FUNC_TMPL
//----------------------------------------------------------------------------


//============================================================================
// variant
//============================================================================
namespace priv
{
  template<typename T>
  PFC_INLINE void variant_copy_ctor(void *dst_, const void *src_)
  {
    PFC_PNEW(dst_)T(*static_cast<const T*>(src_));
  }
  //----

  template<>
  PFC_INLINE void variant_copy_ctor<void>(void *dst_, const void *src_)
  {
    PFC_ERROR(("Variant type doesn't have copy-constructor\r\n"));
  }
  //----

  template<typename T>
  PFC_INLINE void variant_dtor(void *dst_)
  {
    ((T*)dst_)->~T();
  }
  //----

  template<>
  PFC_INLINE void variant_dtor<void>(void *dst_)
  {
    PFC_ERROR(("Variant type doesn't have destructor\r\n"));
  }
} // namespace priv
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
const typename variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::structor variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::s_structors[]=
{
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T0>::res, T0, void>::res>, priv::variant_dtor<T0>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T1>::res, T1, void>::res>, priv::variant_dtor<T1>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T2>::res, T2, void>::res>, priv::variant_dtor<T2>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T3>::res, T3, void>::res>, priv::variant_dtor<T3>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T4>::res, T4, void>::res>, priv::variant_dtor<T4>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T5>::res, T5, void>::res>, priv::variant_dtor<T5>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T6>::res, T6, void>::res>, priv::variant_dtor<T6>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T7>::res, T7, void>::res>, priv::variant_dtor<T7>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T8>::res, T8, void>::res>, priv::variant_dtor<T8>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T9>::res, T9, void>::res>, priv::variant_dtor<T9>},
};
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::variant()
  :m_type_index(0)
{
  PFC_PNEW(m_data)T0;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::variant(const variant &v_)
  :m_type_index(v_.m_type_index)
{
  s_structors[m_type_index].copy_ctor(m_data, v_.m_data);
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::variant(const T &v_)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  m_type_index=uint8_t(id);
  PFC_PNEW(m_data)T(v_);
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::variant(meta_type<T>)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  m_type_index=uint8_t(id);
  PFC_PNEW(m_data)T;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::operator=(const variant &v_)
{
  if(this!=&v_)
  {
    s_structors[m_type_index].dtor(m_data);
    m_type_index=v_.m_type_index;
    s_structors[m_type_index].copy_ctor(m_data, v_.m_data);
  }
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::operator=(const T &v_)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  s_structors[m_type_index].dtor(m_data);
  m_type_index=uint8_t(id);
  PFC_PNEW(m_data)T(v_);
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::operator=(meta_type<T>)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  s_structors[m_type_index].dtor(m_data);
  m_type_index=uint8_t(id);
  PFC_PNEW(m_data)T;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::~variant()
{
  s_structors[m_type_index].dtor(m_data);
}
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
unsigned variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type_index() const
{
  return m_type_index;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
const void *variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::data() const
{
  return m_data;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
T &type_set(variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  v_.s_structors[v_.m_type_index].dtor(v_.m_data);
  v_.m_type_index=uint8_t(id);
  PFC_PNEW(v_.m_data)T;
  return *reinterpret_cast<T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
T &type_ref(variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const T &type_ref(const variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<remove_cv<T>::res>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<const T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
volatile T &type_ref(volatile variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<remove_cv<T>::res>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<volatile T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const volatile T &type_ref(const volatile variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<remove_cv<T>::res>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<const volatile T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
T *type_ptr(variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<T*>(v_.m_data):0;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const T *type_ptr(const variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<remove_cv<T>::res>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<const T*>(v_.m_data):0;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
volatile T *type_ptr(volatile variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<remove_cv<T>::res>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<volatile T*>(v_.m_data):0;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const volatile T *type_ptr(const volatile variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<remove_cv<T>::res>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<const volatile T*>(v_.m_data):0;
}
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE, typename T>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::read_value(PE &pe_, const meta_type<T>&, uint8_t)
{
  // set given type and read the value
  operator=(meta_type<T>());
  pe_.var(*reinterpret_cast<T*>(m_data));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::read_value(PE &pe_, const meta_type<void>&, uint8_t type_index_)
{
  PFC_ERROR(("No type defined for given type ID (%i)\r\n", type_index_));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE, typename T>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::write_value(PE &pe_, const meta_type<T>&)
{
  // write given value type
  pe_.var(*reinterpret_cast<T*>(m_data));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::write_value(PE &pe_, const meta_type<void>&)
{
  PFC_ERROR(("Invalid variant type ID (%i)\r\n", m_type_index));
}
//----------------------------------------------------------------------------


//============================================================================
// pod_variant
//============================================================================
template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::pod_variant()
  :m_type_index(0)
{
  PFC_PNEW(m_data)T0;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::pod_variant(const T &v_)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  m_type_index=uint8_t(id);
  mem_copy(m_data, &v_, sizeof(T));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::pod_variant(meta_type<T>)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  m_type_index=uint8_t(id);
  PFC_PNEW(m_data)T;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
void pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::operator=(const T &v_)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  m_type_index=uint8_t(id);
  mem_copy(m_data, &v_, sizeof(T));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
void pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::operator=(meta_type<T>)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  m_type_index=uint8_t(id);
  PFC_PNEW(m_data)T;
}
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
unsigned pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type_index() const
{
  return m_type_index;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
const void *pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::data() const
{
  return m_data;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
T &type_set(pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  v_.m_type_index=uint8_t(id);
  PFC_PNEW(v_.m_data)T;
  return *reinterpret_cast<T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
T &type_ref(pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const T &type_ref(const pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<remove_cv<T>::res>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<const T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
volatile T &type_ref(volatile pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<remove_cv<T>::res>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<volatile T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const volatile T &type_ref(const volatile pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<remove_cv<T>::res>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<const volatile T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
T *type_ptr(pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<T>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<T*>(v_.m_data):0;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const T *type_ptr(const pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<remove_cv<T>::res>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<const T*>(v_.m_data):0;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
volatile T *type_ptr(volatile pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<remove_cv<T>::res>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<volatile T*>(v_.m_data):0;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const volatile T *type_ptr(const volatile pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<remove_cv<T>::res>::res};
  PFC_CTF_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<const volatile T*>(v_.m_data):0;
}
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE, typename T>
void pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::read_value(PE &pe_, const meta_type<T>&, uint8_t)
{
  // set given type and read the value
  operator=(meta_type<T>());
  pe_.var(*reinterpret_cast<T*>(m_data));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE>
void pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::read_value(PE &pe_, const meta_type<void>&, uint8_t type_index_)
{
  PFC_ERROR(("No type defined for given type ID (%i)\r\n", type_index_));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE, typename T>
void pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::write_value(PE &pe_, const meta_type<T>&)
{
  // write given value type
  pe_.var(*reinterpret_cast<T*>(m_data));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE>
void pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::write_value(PE &pe_, const meta_type<void>&)
{
  PFC_ERROR(("Invalid variant type ID (%i)\r\n", m_type_index));
}
//----------------------------------------------------------------------------


//============================================================================
// poly_variant
//============================================================================
template<class B, unsigned max_size, unsigned align>
poly_variant<B, max_size, align>::poly_variant()
  :m_is_initialized(false)
{
}
//----

template<class B, unsigned max_size, unsigned align>
poly_variant<B, max_size, align>::poly_variant(const poly_variant &pv_)
  :m_is_initialized(true)
{
  // copy-construct poly-variant object from another
  reinterpret_cast<const B*>(pv_.m_data)->clone(reinterpret_cast<B*>(m_data));
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
poly_variant<B, max_size, align>::poly_variant(const C &v_)
  :m_is_initialized(true)
{
  // construct poly-variant object from a value
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_CTF_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_CTF_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_class);
  PFC_PNEW(m_data)C(v_);
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
poly_variant<B, max_size, align>::poly_variant(meta_type<C>)
  :m_is_initialized(true)
{
  // construct poly-variant object from a value
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_CTF_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_CTF_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_class);
  PFC_PNEW(m_data)C;
}
//----

template<class B, unsigned max_size, unsigned align>
void poly_variant<B, max_size, align>::operator=(const poly_variant &pv_)
{
  // destruct old poly-variant object and construct new one from another
  if(this!=&pv_)
  {
    if(m_is_initialized)
      reinterpret_cast<B*>(m_data)->~B();
    if(pv_.m_is_initialized)
      reinterpret_cast<B*>(pv_.m_data)->clone(reinterpret_cast<B*>(m_data));
    m_is_initialized=pv_.m_is_initialized;
  }
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
void poly_variant<B, max_size, align>::operator=(const C &v_)
{
  // destruct old poly-variant object and construct new one from a value
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_CTF_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_CTF_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_object);
  if(m_is_initialized)
    reinterpret_cast<B*>(m_data)->~B();
  PFC_PNEW(m_data)C(v_);
  m_is_initialized=true;
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
void poly_variant<B, max_size, align>::operator=(meta_type<C>)
{
  // destruct old poly-variant object and construct new one from a value
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_CTF_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_CTF_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_object);
  if(m_is_initialized)
    reinterpret_cast<B*>(m_data)->~B();
  PFC_PNEW(m_data)C;
  m_is_initialized=true;
}
//----

template<class B, unsigned max_size, unsigned align>
void poly_variant<B, max_size, align>::release()
{
  // destruct the object
  if(m_is_initialized)
  {
    reinterpret_cast<B*>(m_data)->~B();
    m_is_initialized=false;
  }
}
//----

template<class B, unsigned max_size, unsigned align>
poly_variant<B, max_size, align>::~poly_variant()
{
  // destruct the object
  if(m_is_initialized)
    reinterpret_cast<B*>(m_data)->~B();
}
//----------------------------------------------------------------------------

template<class B, unsigned max_size, unsigned align>
bool poly_variant<B, max_size, align>::is_initialized() const
{
  return m_is_initialized;
}
//----

template<class B, unsigned max_size, unsigned align>
const B *poly_variant<B, max_size, align>::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_is_initialized)
  return reinterpret_cast<const B*>(m_data);
}
//----

template<class B, unsigned max_size, unsigned align>
B *poly_variant<B, max_size, align>::operator->()
{
  PFC_ASSERT_PEDANTIC(m_is_initialized)
  return reinterpret_cast<B*>(m_data);
}
//----

template<class B, unsigned max_size, unsigned align>
const B &poly_variant<B, max_size, align>::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_is_initialized)
  return *reinterpret_cast<const B*>(m_data);
}
//----

template<class B, unsigned max_size, unsigned align>
B &poly_variant<B, max_size, align>::operator*()
{
  PFC_ASSERT_PEDANTIC(m_is_initialized)
  return *reinterpret_cast<B*>(m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
C &type_set(poly_variant<B, max_size, align> &pv_)
{
  // construct poly-variant object from a value
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), set_class_must_be_derived_from_the_base_class);
  PFC_CTF_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_CTF_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_class);
  if(pv_.m_is_initialized)
    reinterpret_cast<B*>(pv_.m_data)->~B();
  PFC_PNEW(pv_.m_data)C;
  pv_.m_is_initialized=true;
  return *(C*)pv_.m_data;
}
//----

template<class C, class B, unsigned max_size, unsigned align>
C &type_ref(poly_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const C &type_ref(const poly_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
volatile C &type_ref(volatile poly_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const volatile C &type_ref(const volatile poly_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
C *type_ptr(poly_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const C *type_ptr(const poly_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
volatile C *type_ptr(volatile poly_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const volatile C *type_ptr(const volatile poly_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----------------------------------------------------------------------------


//============================================================================
// poly_pod_variant
//============================================================================
template<class B, unsigned max_size, unsigned align>
poly_pod_variant<B, max_size, align>::poly_pod_variant()
  :m_is_initialized(false)
{
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
poly_pod_variant<B, max_size, align>::poly_pod_variant(const C &v_)
  :m_is_initialized(true)
{
  // construct poly-variant object from a value
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_CTF_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_CTF_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_class);
  mem_copy(m_data, &v_, sizeof(C));
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
poly_pod_variant<B, max_size, align>::poly_pod_variant(meta_type<C>)
  :m_is_initialized(true)
{
  // construct poly-variant object from a value
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_CTF_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_CTF_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_class);
  PFC_PNEW(m_data)C;
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
void poly_pod_variant<B, max_size, align>::operator=(const C &v_)
{
  // construct poly-variant object from a value
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_CTF_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_CTF_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_object);
  mem_copy(m_data, &v_, sizeof(C));
  m_is_initialized=true;
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
void poly_pod_variant<B, max_size, align>::operator=(meta_type<C>)
{
  // construct poly-variant object from a value
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_CTF_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_CTF_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_object);
  PFC_PNEW(m_data)C;
  m_is_initialized=true;
}
//----

template<class B, unsigned max_size, unsigned align>
void poly_pod_variant<B, max_size, align>::release()
{
  m_is_initialized=false;
}
//----------------------------------------------------------------------------

template<class B, unsigned max_size, unsigned align>
bool poly_pod_variant<B, max_size, align>::is_initialized() const
{
  return m_is_initialized;
}
//----

template<class B, unsigned max_size, unsigned align>
const B *poly_pod_variant<B, max_size, align>::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_is_initialized);
  return reinterpret_cast<const B*>(m_data);
}
//----

template<class B, unsigned max_size, unsigned align>
B *poly_pod_variant<B, max_size, align>::operator->()
{
  PFC_ASSERT_PEDANTIC(m_is_initialized);
  return reinterpret_cast<B*>(m_data);
}
//----

template<class B, unsigned max_size, unsigned align>
const B &poly_pod_variant<B, max_size, align>::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_is_initialized);
  return *reinterpret_cast<const B*>(m_data);
}
//----

template<class B, unsigned max_size, unsigned align>
B &poly_pod_variant<B, max_size, align>::operator*()
{
  PFC_ASSERT_PEDANTIC(m_is_initialized);
  return *reinterpret_cast<B*>(m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
C &type_set(poly_pod_variant<B, max_size, align> &pv_)
{
  // construct poly-POD variant object from a value
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), set_class_must_be_derived_from_the_base_class);
  PFC_CTF_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_pod_variant_object);
  PFC_CTF_ASSERT_MSG(meta_alignof<C>::res<=align, poly_pod_variant_object_doesnt_comply_alignment_requirements_of_the_class);
  PFC_PNEW(pv_.m_data)C;
  pv_.m_is_initialized=true;
  return *(C*)pv_.m_data;
}
//----

template<class C, class B, unsigned max_size, unsigned align>
C &type_ref(poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const C &type_ref(const poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
volatile C &type_ref(volatile poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const volatile C &type_ref(const volatile poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
C *type_ptr(poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const C *type_ptr(const poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
volatile C *type_ptr(volatile poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const volatile C *type_ptr(const volatile poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_CTF_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----------------------------------------------------------------------------
