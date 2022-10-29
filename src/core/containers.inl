//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// compare_predicate
//============================================================================
template<typename T, typename U>
bool compare_predicate::before(const T &v0_, const U &v1_) const
{
  return v0_<v1_;
}
//----

template<typename T, typename U>
bool compare_predicate::equal(const T &v0_, const U &v1_) const
{
  return v0_==v1_;
}
//----------------------------------------------------------------------------


//============================================================================
// owner_array
//============================================================================
template<typename T>
owner_array<T>::owner_array()
{
  size=0;
  data=0;
}
//----

template<typename T>
owner_array<T>::owner_array(T *data_, usize_t size_)
{
  size=size_;
  data=data_;
}
//----

template<typename T>
owner_array<T>::owner_array(const owner_array &arr_)
{
  size=arr_.size;
  data=arr_.data;
  arr_.size=0;
  arr_.data=0;
}
//----

template<typename T>
void owner_array<T>::set(T *data_, usize_t size_)
{
  if(data!=data_)
  {
    reverse_destruct(data, size);
    size=size_;
    data=data_;
  }
}
//----

template<typename T>
void owner_array<T>::operator=(const owner_array &arr_)
{
  if(this!=&arr_)
  {
    reverse_destruct(data, size);
    size=arr_.size;
    data=arr_.data;
    arr_.size=0;
    arr_.data=0;
  }
}
//----

template<typename T>
owner_array<T>::~owner_array()
{
  reverse_destruct(data, size);
  PFC_MEM_FREE(data);
}
//----

template<typename T>
void owner_array<T>::clear()
{
  reverse_destruct(data, size);
  PFC_MEM_FREE(data);
  data=0;
  size=0;
}
//----

template<typename T>
void owner_array<T>::swap(owner_array<T> &arr_)
{
  pfc::swap(size, arr_.size);
  pfc::swap(data, arr_.data);
}
//----

template<typename T>
owner_data owner_array<T>::steal_data()
{
  PFC_CTF_ASSERT_MSG(is_type_pod<T>::res, unable_to_get_data_of_non_pod_type);
  owner_data d(data);
  size=0;
  data=0;
  return d;
}
//----------------------------------------------------------------------------

template<typename T>
template<class PE>
void owner_array<T>::stream_array(PE &pe_, meta_case<0> is_type_void_)
{
  pe_.data(data, size);
}
//----

template<typename T>
template<class PE>
void owner_array<T>::stream_array(PE &pe_, meta_case<1> default_)
{
  pe_.avar(data, size, mvarflag_mutable|mvarflag_mutable_ptr);
}
//----------------------------------------------------------------------------


//============================================================================
// array
//============================================================================
template<typename T>
array<T>::array(memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  m_size=0;
  m_capacity=0;
  m_data=0;
}
//----

template<typename T>
array<T>::array(const array &a_)
  :m_allocator(a_.m_allocator)
{
  // copy-construct the array from array
  PFC_MEM_TRACK_STACK();
  eh_data<T> p(*m_allocator, a_.m_size, meta_alignof<T>::res);
  m_data=p.data;
  copy_construct(m_data, a_.m_data, a_.m_size);
  m_size=m_capacity=a_.m_size;
  p.reset();
}
//----

template<typename T>
array<T>::array(const array &a_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // copy-construct the array from array
  PFC_MEM_TRACK_STACK();
  eh_data<T> p(*m_allocator, a_.m_size, meta_alignof<T>::res);
  m_data=p.data;
  copy_construct(m_data, a_.m_data, a_.m_size);
  m_size=m_capacity=a_.m_size;
  p.reset();
}
//----

template<typename T>
array<T>::array(usize_t size_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // default construct the array
  PFC_MEM_TRACK_STACK();
  eh_data<T> p(*m_allocator, size_, meta_alignof<T>::res);
  m_data=p.data;
  default_construct(m_data, size_);
  m_size=m_capacity=size_;
  p.reset();
}
//----

template<typename T>
array<T>::array(usize_t size_, const T &v_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // copy-construct the array from value
  PFC_MEM_TRACK_STACK();
  eh_data<T> p(*m_allocator, size_, meta_alignof<T>::res);
  m_data=p.data;
  copy_construct(m_data, v_, size_);
  m_size=m_capacity=size_;
  p.reset();
}
//----

template<typename T>
array<T>::~array()
{
  clear();
}
//----

template<typename T>
void array<T>::operator=(const array &a_)
{
  array<T> a(a_);
  swap(a);
}
//----

template<typename T>
void array<T>::set_allocator(memory_allocator_base *alloc_)
{
  PFC_ASSERT_MSG(!m_data, ("Unable to change the allocator of an array with capacity\r\n"));
  m_allocator=alloc_?alloc_:&default_memory_allocator::inst();
}
//----

template<typename T>
void array<T>::clear()
{
  // clear the array
  reverse_destruct(m_data, m_size);
  if(m_data)
    m_allocator->free(m_data);
  m_size=0;
  m_capacity=0;
  m_data=0;
}
//----

template<typename T>
void array<T>::reset_size(usize_t size_)
{
  // reset array size to given size
  PFC_MEM_TRACK_STACK();
  clear();
  eh_data<T> p(*m_allocator, size_, meta_alignof<T>::res);
  m_data=p.data;
  default_construct(m_data, size_);
  m_size=m_capacity=size_;
  p.reset();
}
//----

template<typename T>
void array<T>::reset_size(usize_t size_, const T &v_)
{
  // reset array size to given size of given value
  PFC_MEM_TRACK_STACK();
  clear();
  eh_data<T> p(*m_allocator, size_, meta_alignof<T>::res);
  m_data=p.data;
  copy_construct(m_data, v_, size_);
  m_size=m_capacity=size_;
  p.reset();
}
//----

template<typename T>
void array<T>::resize(usize_t size_)
{
  // resize the array to given size
  if(size_>m_size)
  {
    PFC_MEM_TRACK_STACK();
    if(m_capacity<size_)
      reserve(size_, 0);
    default_construct(m_data+m_size, size_-m_size);
  }
  else
    reverse_destruct(m_data+size_, m_size-size_);
  m_size=size_;
}
//----

template<typename T>
void array<T>::resize(usize_t size_, const T &v_)
{
  // resize the array to given size
  if(size_>m_size)
  {
    PFC_MEM_TRACK_STACK();
    if(m_capacity<size_)
      reserve(size_, 0);
    copy_construct(m_data+m_size, v_, size_-m_size);
  }
  else
    reverse_destruct(m_data+size_, m_size-size_);
  m_size=size_;
}
//----

template<typename T>
void array<T>::resize_to_zero()
{
  reverse_destruct(m_data, m_size);
  m_size=0;
}
//----

template<typename T>
void array<T>::reserve(usize_t capacity_)
{
  if(m_capacity<capacity_)
  {
    // move content of the array to new memory location
    PFC_MEM_TRACK_STACK();
    eh_data<T> p(*m_allocator, capacity_, meta_alignof<T>::res);
    move_construct(p.data, m_data, m_size);
    m_allocator->free(m_data);
    m_data=p.data;
    m_capacity=capacity_;
    p.reset();
  }
}
//----

template<typename T>
void array<T>::trim(usize_t permitted_slack_)
{
  // trim array capacity
  if(m_size<m_capacity+permitted_slack_)
  {
    array a(*this, m_allocator);
    swap(a);
  }
}
//----

template<typename T>
void array<T>::swap(array &a_)
{
  pfc::swap(m_allocator, a_.m_allocator);
  pfc::swap(m_size, a_.m_size);
  pfc::swap(m_capacity, a_.m_capacity);
  pfc::swap(m_data, a_.m_data);
}
//----------------------------------------------------------------------------

template<typename T>
memory_allocator_base &array<T>::allocator() const
{
  return *m_allocator;
}
//----

template<typename T>
usize_t array<T>::size() const
{
  return m_size;
}
//----

template<typename T>
usize_t array<T>::capacity() const
{
  return m_capacity;
}
//----

template<typename T>
const T &array<T>::operator[](usize_t idx_) const
{
  PFC_ASSERT_PEDANTIC_MSG(idx_<m_size, ("Trying to access element at index %u of array<%s> (size=%u)\r\n", idx_, typeid(T).name(), m_size));
  return m_data[idx_];
}
//----

template<typename T>
T &array<T>::operator[](usize_t idx_)
{
  PFC_ASSERT_PEDANTIC_MSG(idx_<m_size, ("Trying to access element at index %u of array<%s> (size=%u)\r\n", idx_, typeid(T).name(), m_size));
  return m_data[idx_];
}
//----

template<typename T>
const T &array<T>::front() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return *m_data;
}
//----

template<typename T>
T &array<T>::front()
{
  PFC_ASSERT_PEDANTIC(m_size);
  return *m_data;
}
//----

template<typename T>
const T &array<T>::back() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return m_data[m_size-1];
}
//----

template<typename T>
T &array<T>::back()
{
  PFC_ASSERT_PEDANTIC(m_size);
  return m_data[m_size-1];
}
//----

template<typename T>
const T *array<T>::data() const
{
  return m_data;
}
//----

template<typename T>
T *array<T>::data()
{
  return m_data;
}
//----

template<typename T>
typename array<T>::const_iterator array<T>::begin() const
{
  return m_data;
}
//----

template<typename T>
typename array<T>::iterator array<T>::begin()
{
  return m_data;
}
//----

template<typename T>
typename array<T>::const_reverse_iterator array<T>::rbegin() const
{
  return m_data+m_size-1;
}
//----

template<typename T>
typename array<T>::reverse_iterator array<T>::rbegin()
{
  return m_data+m_size-1;
}
//----

template<typename T>
typename array<T>::const_iterator array<T>::last() const
{
  return m_data+m_size-1;
}
//----

template<typename T>
typename array<T>::iterator array<T>::last()
{
  return m_data+m_size-1;
}
//----

template<typename T>
typename array<T>::const_reverse_iterator array<T>::rlast() const
{
  return m_data;
}
//----

template<typename T>
typename array<T>::reverse_iterator array<T>::rlast()
{
  return m_data;
}
//----

template<typename T>
typename array<T>::const_iterator array<T>::end() const
{
  return m_data+m_size;
}
//----

template<typename T>
typename array<T>::iterator array<T>::end()
{
  return m_data+m_size;
}
//----

template<typename T>
typename array<T>::const_reverse_iterator array<T>::rend() const
{
  return m_data-1;
}
//----

template<typename T>
typename array<T>::reverse_iterator array<T>::rend()
{
  return m_data-1;
}
//----

template<typename T>
void array<T>::get(usize_t start_idx_, T *p_, usize_t num_items_) const
{
  // get items to the given array from the container
  PFC_ASSERT_MSG(start_idx_+num_items_<=m_size, ("Reading values past the end of the container\r\n"));
  destruct(p_, num_items_);
  copy_construct(p_, m_data+start_idx_, num_items_);
}
//----

template<typename T>
void array<T>::set(usize_t start_idx_, const T *p_, usize_t num_items_)
{
  // set items from the given array to the container
  PFC_ASSERT_MSG(start_idx_+num_items_<=m_size, ("Writing values past the end of the container\r\n"));
  destruct(m_data+start_idx_, num_items_);
  copy_construct(m_data+start_idx_, p_, num_items_);
}
//----

template<typename T>
void array<T>::set(usize_t start_idx_, const T &v_, usize_t num_items_)
{
  // set items from the given array to the container
  PFC_ASSERT_MSG(start_idx_+num_items_<=m_size, ("Writing values past the end of the container\r\n"));
  destruct(m_data+start_idx_, num_items_);
  copy_construct(m_data+start_idx_, v_, num_items_);
}
//----

template<typename T>
void array<T>::push_front(const T &v_)
{
  // push the value to the beginning of the array
  if(m_size==m_capacity)
  {
    PFC_MEM_TRACK_STACK();
    reserve(m_size?m_size*2:4, 1);
  }
  else
    move_construct(m_data+1, m_data, m_size);
  PFC_PNEW(m_data)T(v_);
  ++m_size;
}
//----

template<typename T>
T &array<T>::push_front()
{
  // push default to the beginning of the array
  if(m_size==m_capacity)
  {
    PFC_MEM_TRACK_STACK();
    reserve(m_size?m_size*2:4, 1);
  }
  else
    move_construct(m_data+1, m_data, m_size);
  PFC_PNEW(m_data)T;
  ++m_size;
  return *m_data;
}
//----

template<typename T>
void array<T>::push_back(const T &v_)
{
  // push the value to the end of the array
  if(m_size==m_capacity)
  {
    PFC_MEM_TRACK_STACK();
    reserve(m_size?m_size*2:4, 0);
  }
  PFC_PNEW(m_data+m_size)T(v_);
  ++m_size;
}
//----

template<typename T>
T &array<T>::push_back()
{
  // push default value to the end of the array
  if(m_size==m_capacity)
  {
    PFC_MEM_TRACK_STACK();
    reserve(m_size?m_size*2:4, 0);
  }
  PFC_PNEW(m_data+m_size)T;
  return m_data[m_size++];
}
//----

template<typename T>
void array<T>::insert_front(usize_t num_items_)
{
  // insert items to the beginning of the array
  usize_t new_size=m_size+num_items_;
  if(m_capacity<new_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve(max(usize_t(4), new_size, m_size*2), num_items_);
  }
  else
    move_construct(m_data+num_items_, m_data, m_size);
  default_construct(m_data, num_items_);
  m_size=new_size;
}
//----

template<typename T>
void array<T>::insert_front(usize_t num_items_, const T &v_)
{
  // insert items to the beginning of the array
  usize_t new_size=m_size+num_items_;
  if(m_capacity<new_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve(max(usize_t(4), new_size, m_size*2), num_items_);
  }
  else
    move_construct(m_data+num_items_, m_data, m_size);
  copy_construct(m_data, v_, num_items_);
  m_size=new_size;
}
//----

template<typename T>
void array<T>::insert_front(usize_t num_items_, const T *v_)
{
  // insert items to the beginning of the array
  usize_t new_size=m_size+num_items_;
  if(m_capacity<new_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve(max(usize_t(4), new_size, m_size*2), num_items_);
  }
  else
    move_construct(m_data+num_items_, m_data, m_size);
  copy_construct(m_data, v_, num_items_);
  m_size=new_size;
}
//----

template<typename T>
void array<T>::insert_back(usize_t num_items_)
{
  // insert items to the end of the array
  usize_t new_size=m_size+num_items_;
  if(m_capacity<new_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve(max(usize_t(4), new_size, m_size*2), 0);
  }
  default_construct(m_data+m_size, num_items_);
  m_size=new_size;
}
//----

template<typename T>
void array<T>::insert_back(usize_t num_items_, const T &v_)
{
  // insert items to the end of the array
  usize_t new_size=m_size+num_items_;
  if(m_capacity<new_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve(max(usize_t(4), new_size, m_size*2), 0);
  }
  copy_construct(m_data+m_size, v_, num_items_);
  m_size=new_size;
}
//----

template<typename T>
void array<T>::insert_back(usize_t num_items_, const T *v_)
{
  // insert items to the end of the array
  usize_t new_size=m_size+num_items_;
  if(m_capacity<new_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve(max(usize_t(4), new_size, m_size*2), 0);
  }
  copy_construct(m_data+m_size, v_, num_items_);
  m_size=new_size;
}
//----

template<typename T>
void array<T>::pop_front()
{
  // remove the first element from the beginning of the array
  PFC_ASSERT_PEDANTIC(m_size);
  m_data[0].~T();
  move_construct(m_data, m_data+1, --m_size);
}
//----

template<typename T>
void array<T>::pop_back()
{
  // remove the last element from the end of the array
  PFC_ASSERT_PEDANTIC(m_size);
  --m_size;
  m_data[m_size].~T();
}
//----

template<typename T>
void array<T>::remove_front(usize_t num_items_)
{
  // remove given number of items from the beginning of the array
  PFC_ASSERT_PEDANTIC(m_size>=num_items_);
  m_size-=num_items_;
  destruct(m_data, num_items_);
  move_construct(m_data, m_data+num_items_, m_size);
}
//----

template<typename T>
void array<T>::remove_back(usize_t num_items_)
{
  // remove given number of items from the end of the array
  PFC_ASSERT_PEDANTIC(m_size>=num_items_);
  reverse_destruct(m_data+m_size-num_items_, num_items_);
  m_size-=num_items_;
}
//----

template<typename T>
void array<T>::remove_at(usize_t idx_)
{
  // remove item at given index
  PFC_ASSERT_PEDANTIC(idx_<m_size);
  m_data[idx_].~T();
  move_construct(m_data+idx_, m_data+idx_+1, m_size-idx_-1);
  --m_size;
}
//----

template<typename T>
void array<T>::remove_at(usize_t idx_, usize_t num_items_)
{
  // remove given number of items starting at given index
  PFC_ASSERT_PEDANTIC(idx_+num_items_<=m_size);
  destruct(m_data+idx_, num_items_);
  move_construct(m_data+idx_, m_data+idx_+num_items_, m_size-idx_-num_items_);
  m_size-=num_items_;
}
//----

template<typename T>
owner_array<T> array<T>::steal_data()
{
  // pass ownership of the data to the caller
  owner_array<T> arr(m_data, m_size);
  m_size=0;
  m_capacity=0;
  m_data=0;
  return arr;
}
//----------------------------------------------------------------------------

template<typename T>
void array<T>::reserve(usize_t capacity_, usize_t offset_)
{
  // move content of the array to new memory location
  eh_data<T> p(*m_allocator, capacity_, meta_alignof<T>::res);
  move_construct(p.data+offset_, m_data, m_size);
  m_allocator->free(m_data);
  m_data=p.data;
  m_capacity=capacity_;
  p.reset();
}
//----------------------------------------------------------------------------


//============================================================================
// sarray
//============================================================================
template<typename T, usize_t cap>
sarray<T, cap>::sarray()
  :m_size(0)
{
}
//----

template<typename T, usize_t cap>
sarray<T, cap>::sarray(const sarray &a_)
  :m_size(a_.m_size)
{
  // copy-construct the array from array
  copy_construct((T*)m_data, (T*)a_.m_data, m_size);
}
//----

template<typename T, usize_t cap>
template<usize_t cap2>
sarray<T, cap>::sarray(const sarray<T, cap2> &a_)
  :m_size(a_.size())
{
  // copy-construct the array from array
  PFC_ASSERT(m_size<=cap);
  copy_construct((T*)m_data, a_.data(), m_size);
}
//----

template<typename T, usize_t cap>
sarray<T, cap>::sarray(usize_t size_)
  :m_size(size_)
{
  // default construct the array
  PFC_ASSERT(size_<=cap);
  default_construct((T*)m_data, size_);
}
//----

template<typename T, usize_t cap>
sarray<T, cap>::sarray(usize_t size_, const T &v_)
  :m_size(size_)
{
  // copy-construct the array from value
  PFC_ASSERT(size_<=cap);
  copy_construct((T*)m_data, v_, size_);
}
//----

template<typename T, usize_t cap>
sarray<T, cap>::~sarray()
{
  clear();
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::operator=(const sarray &a_)
{
  // replace content with the content of the given array
  if(this!=&a_)
  {
    clear();
    copy_construct((T*)m_data, (T*)a_.m_data, a_.m_size);
    m_size=a_.m_size;
  }
}
//----

template<typename T, usize_t cap>
template<usize_t cap2>
void sarray<T, cap>::operator=(const sarray<T, cap2> &a_)
{
  // replace content with the content of the given array
  if(this!=&a_)
  {
    clear();
    usize_t size=a_.size();
    copy_construct((T*)m_data, a_.data(), size);
    m_size=size;
  }
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::clear()
{
  // clear the array
  reverse_destruct((T*)m_data, m_size);
  m_size=0;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::reset_size(usize_t size_)
{
  // reset array size to given size
  clear();
  default_construct(((T*)m_data), size_);
  m_size=size_;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::reset_size(usize_t size_, const T &v_)
{
  // reset array size to given size
  clear();
  copy_construct(((T*)m_data), v_, size_);
  m_size=size_;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::resize(usize_t size_)
{
  // resize the array to given size
  PFC_ASSERT(size_<=cap);
  if(size_>m_size)
    default_construct(((T*)m_data)+m_size, size_-m_size);
  else
    reverse_destruct(((T*)m_data)+size_, m_size-size_);
  m_size=size_;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::resize(usize_t size_, const T &v_)
{
  // resize the array to given size
  PFC_ASSERT(size_<=cap);
  if(size_>m_size)
    copy_construct(((T*)m_data)+m_size, v_, size_-m_size);
  else
    reverse_destruct(((T*)m_data)+size_, m_size-size_);
  m_size=size_;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::resize_to_zero()
{
  // clear the array
  reverse_destruct((T*)m_data, m_size);
  m_size=0;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::swap(sarray &a_)
{
  // get short and long array for swapping
  T *short_arr=(T*)m_data;
  T *long_arr=(T*)a_.m_data;
  usize_t short_arr_size=m_size;
  usize_t long_arr_size=a_.m_size;
  if(long_arr_size<short_arr_size)
  {
    pfc::swap(short_arr, long_arr);
    pfc::swap(short_arr_size, long_arr_size);
  }

  // swap contents of the arrays
  pfc::swap(short_arr, long_arr, short_arr_size);
  move_construct(short_arr+short_arr_size, long_arr+short_arr_size, long_arr_size-short_arr_size);
  pfc::swap(m_size, a_.m_size);
}
//----------------------------------------------------------------------------

template<typename T, usize_t cap>
usize_t sarray<T, cap>::size() const
{
  return m_size;
}
//----

template<typename T, usize_t cap>
const T &sarray<T, cap>::operator[](usize_t idx_) const
{
  PFC_ASSERT_PEDANTIC_MSG(idx_<m_size, ("Trying to access element at index %u of sarray<%s> (size=%u)\r\n", idx_, typeid(T).name(), m_size));
  return ((T*)m_data)[idx_];
}
//----

template<typename T, usize_t cap>
T &sarray<T, cap>::operator[](usize_t idx_)
{
  PFC_ASSERT_PEDANTIC_MSG(idx_<m_size, ("Trying to access element at index %u of sarray<%s> (size=%u)\r\n", idx_, typeid(T).name(), m_size));
  return ((T*)m_data)[idx_];
}
//----

template<typename T, usize_t cap>
const T &sarray<T, cap>::front() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return *(T*)m_data;
}
//----

template<typename T, usize_t cap>
T &sarray<T, cap>::front()
{
  PFC_ASSERT_PEDANTIC(m_size);
  return *(T*)m_data;
}
//----

template<typename T, usize_t cap>
const T &sarray<T, cap>::back() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return ((T*)m_data)[m_size-1];
}
//----

template<typename T, usize_t cap>
T &sarray<T, cap>::back()
{
  PFC_ASSERT_PEDANTIC(m_size);
  return ((T*)m_data)[m_size-1];
}
//----

template<typename T, usize_t cap>
const T *sarray<T, cap>::data() const
{
  return (T*)m_data;
}
//----

template<typename T, usize_t cap>
T *sarray<T, cap>::data()
{
  return (T*)m_data;
}
//----

template<typename T, usize_t cap>
typename sarray<T, cap>::const_iterator sarray<T, cap>::begin() const
{
  return (T*)m_data;
}
//----

template<typename T, usize_t cap>
typename sarray<T, cap>::iterator sarray<T, cap>::begin()
{
  return (T*)m_data;
}
//----

template<typename T, usize_t cap>
typename sarray<T, cap>::const_reverse_iterator sarray<T, cap>::rbegin() const
{
  return (T*)m_data+m_size-1;
}
//----

template<typename T, usize_t cap>
typename sarray<T, cap>::reverse_iterator sarray<T, cap>::rbegin()
{
  return (T*)m_data+m_size-1;
}
//----

template<typename T, usize_t cap>
typename sarray<T, cap>::const_iterator sarray<T, cap>::last() const
{
  return (T*)m_data+m_size-1;
}
//----

template<typename T, usize_t cap>
typename sarray<T, cap>::iterator sarray<T, cap>::last()
{
  return (T*)m_data+m_size-1;
}
//----

template<typename T, usize_t cap>
typename sarray<T, cap>::const_reverse_iterator sarray<T, cap>::rlast() const
{
  return (T*)m_data;
}
//----

template<typename T, usize_t cap>
typename sarray<T, cap>::reverse_iterator sarray<T, cap>::rlast()
{
  return (T*)m_data;
}
//----

template<typename T, usize_t cap>
typename sarray<T, cap>::const_iterator sarray<T, cap>::end() const
{
  return (T*)m_data+m_size;
}
//----

template<typename T, usize_t cap>
typename sarray<T, cap>::iterator sarray<T, cap>::end()
{
  return (T*)m_data+m_size;
}
//----

template<typename T, usize_t cap>
typename sarray<T, cap>::const_reverse_iterator sarray<T, cap>::rend() const
{
  return (T*)m_data-1;
}
//----

template<typename T, usize_t cap>
typename sarray<T, cap>::reverse_iterator sarray<T, cap>::rend()
{
  return (T*)m_data-1;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::get(usize_t start_idx_, T *p_, usize_t num_items_) const
{
  // get items to the given array from the container
  PFC_ASSERT_MSG(start_idx_+num_items_<=m_size, ("Reading values past the end of the container\r\n"));
  destruct(p_, num_items_);
  copy_construct(p_, (const T*)m_data+start_idx_, num_items_);
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::set(usize_t start_idx_, const T *p_, usize_t num_items_)
{
  // set items from the given array to the container
  PFC_ASSERT_MSG(start_idx_+num_items_<=m_size, ("Writing values past the end of the container\r\n"));
  destruct((T*)m_data+start_idx_, num_items_);
  copy_construct((T*)m_data+start_idx_, p_, num_items_);
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::set(usize_t start_idx_, const T &v_, usize_t num_items_)
{
  // set items from the given array to the container
  PFC_ASSERT_MSG(start_idx_+num_items_<=m_size, ("Writing values past the end of the container\r\n"));
  destruct((T*)m_data+start_idx_, num_items_);
  copy_construct((T*)m_data+start_idx_, v_, num_items_);
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::push_front(const T &v_)
{
  // push item to the beginning of the array
  PFC_ASSERT_PEDANTIC(m_size<cap);
  move_construct((T*)m_data+1, (T*)m_data, m_size);
  PFC_PNEW(m_data)T(v_);
  ++m_size;
}
//----

template<typename T, usize_t cap>
T &sarray<T, cap>::push_front()
{
  // push item to the beginning of the array
  PFC_ASSERT_PEDANTIC(m_size<cap);
  move_construct((T*)m_data+1, (T*)m_data, m_size);
  PFC_PNEW(m_data)T;
  ++m_size;
  return *(T*)m_data;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::push_back(const T &v_)
{
  // push the value to the end of the array
  PFC_ASSERT_PEDANTIC(m_size<cap);
  PFC_PNEW(((T*)m_data)+m_size)T(v_);
  ++m_size;
}
//----

template<typename T, usize_t cap>
T &sarray<T, cap>::push_back()
{
  // push default value to the end of the array
  PFC_ASSERT_PEDANTIC(m_size<cap);
  PFC_PNEW(((T*)m_data)+m_size)T;
  return ((T*)m_data)[m_size++];
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::insert_front(usize_t num_items_)
{
  // insert items to the beginning of the array
  PFC_ASSERT(m_size+num_items_<=cap);
  move_construct((T*)m_data+num_items_, (T*)m_data, m_size);
  default_construct((T*)m_data, num_items_);
  m_size+=num_items_;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::insert_front(usize_t num_items_, const T &v_)
{
  // insert items to the beginning of the array
  PFC_ASSERT(m_size+num_items_<=cap);
  move_construct((T*)m_data+num_items_, (T*)m_data, m_size);
  default_construct((T*)m_data, v_, num_items_);
  m_size+=num_items_;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::insert_front(usize_t num_items_, const T *v_)
{
  // insert items to the beginning of the array
  PFC_ASSERT(m_size+num_items_<=cap);
  move_construct((T*)m_data+num_items_, (T*)m_data, m_size);
  default_construct((T*)m_data, v_, num_items_);
  m_size+=num_items_;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::insert_back(usize_t num_items_)
{
  // insert items to the end of the array
  PFC_ASSERT(m_size+num_items_<=cap);
  default_construct(((T*)m_data)+m_size, num_items_);
  m_size+=num_items_;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::insert_back(usize_t num_items_, const T &v_)
{
  // insert items to the end of the array
  PFC_ASSERT(m_size+num_items_<=cap);
  copy_construct(((T*)m_data)+m_size, v_, num_items_);
  m_size+=num_items_;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::insert_back(usize_t num_items_, const T *v_)
{
  // insert items to the end of the array
  PFC_ASSERT(m_size+num_items_<=cap);
  copy_construct(((T*)m_data)+m_size, v_, num_items_);
  m_size+=num_items_;
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::pop_front()
{
  // remove the first element from the beginning of the array
  PFC_ASSERT_PEDANTIC(m_size);
  ((T*)m_data)[0].~T();
  move_construct((T*)m_data, (T*)m_data+1, --m_size);
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::pop_back()
{
  // remove the last element from the end of the array
  PFC_ASSERT_PEDANTIC(m_size);
  ((T*)m_data)[--m_size].~T();
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::remove_front(usize_t num_items_)
{
  // remove given number of items from the beginning of the array
  PFC_ASSERT_PEDANTIC(m_size>=num_items_);
  m_size-=num_items_;
  destruct((T*)m_data, num_items_);
  move_construct((T*)m_data, (T*)m_data+num_items_, m_size);
}
//----

template<typename T, usize_t cap>
void sarray<T, cap>::remove_back(usize_t num_items_)
{
  // remove given number of items from the end of the array
  PFC_ASSERT_PEDANTIC(m_size>=num_items_);
  reverse_destruct(((T*)m_data)+m_size-num_items_, num_items_);
  m_size-=num_items_;
}
//----------------------------------------------------------------------------


//============================================================================
// deque
//============================================================================
template<typename T>
deque<T>::deque(memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
  ,m_size(0)
  ,m_offset(0)
  ,m_first(0)
  ,m_last(0)
  ,m_stride_last(0)
{
  PFC_ASSERT_CALL(m_allocator->check_allocator(deque_traits<T>::block_alloc_size, deque_traits<T>::block_alloc_align));
}
//----

template<typename T>
deque<T>::deque(const deque &dq_)
  :m_allocator(&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  cctor(dq_);
}
//----

template<typename T>
deque<T>::deque(const deque &dq_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(deque_traits<T>::block_alloc_size, deque_traits<T>::block_alloc_align));
  cctor(dq_);
}
//----

template<typename T>
deque<T>::deque(usize_t size_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // default construct the deque
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(deque_traits<T>::block_alloc_size, deque_traits<T>::block_alloc_align));
  m_size=0;
  m_offset=0;
  m_strides.resize((size_+deque_traits<T>::smask)>>deque_traits<T>::sshift);
  PFC_EDTOR(*this, &deque<T>::clear);
  usize_t idx=0;
  while(m_size<size_)
  {
    // construct a stride
    eh_data<T> p(*m_allocator, deque_traits<T>::ssize, deque_traits<T>::block_alloc_align);
    m_strides[idx++]=p.data;
    usize_t num_vals=min<usize_t>(size_-m_size, deque_traits<T>::ssize);
    default_construct(p.data, num_vals);
    p.reset();
    m_size+=num_vals;
  }
  PFC_EDTOR_RESET();

  // setup first & last pointers
  if(m_size)
  {
    m_first=m_strides.front()+m_offset;
    m_last=m_strides.back()+((m_size-1)&deque_traits<T>::smask);
    m_stride_last=m_strides.back()+deque_traits<T>::smask;
  }
  else
    m_first=m_last=m_stride_last=0;
}
//----

template<typename T>
deque<T>::deque(usize_t size_, const T &v_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // copy-construct the deque from the value
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(deque_traits<T>::block_alloc_size, deque_traits<T>::block_alloc_align));
  m_size=0;
  m_offset=0;
  m_strides.resize((size_+deque_traits<T>::smask)>>deque_traits<T>::sshift);
  PFC_EDTOR(*this, &deque<T>::clear);
  usize_t idx=0;
  while(m_size<size_)
  {
    // construct a stride
    eh_data<T> p(*m_allocator, deque_traits<T>::ssize, deque_traits<T>::block_alloc_align);
    m_strides[idx++]=p.data;
    usize_t num_vals=min<usize_t>(size_-m_size, deque_traits<T>::ssize);
    copy_construct(p.data, v_, num_vals);
    p.reset();
    m_size+=num_vals;
  }
  PFC_EDTOR_RESET();

  // setup first & last pointers
  if(m_size)
  {
    m_first=m_strides.front()+m_offset;
    m_last=m_strides.back()+((m_size-1)&deque_traits<T>::smask);
    m_stride_last=m_strides.back()+deque_traits<T>::smask;
  }
  else
    m_first=m_last=m_stride_last=0;
}
//----

template<typename T>
deque<T>::~deque()
{
  clear();
}
//----

template<typename T>
void deque<T>::operator=(const deque &dq_)
{
  deque<T> dq(dq_);
  swap(dq);
}
//----

template<typename T>
void deque<T>::set_allocator(memory_allocator_base *alloc_)
{
  PFC_ASSERT_MSG(!m_size, ("Unable to change the allocator of a non-empty deque\r\n"));
  m_allocator=alloc_?alloc_:&default_memory_allocator::inst();
  PFC_ASSERT_CALL(m_allocator->check_allocator(deque_traits<T>::block_alloc_size, deque_traits<T>::block_alloc_align));
}
//----

template<typename T>
void deque<T>::clear()
{
  // clear the deque
  usize_t idx=0;
  while(m_size)
  {
    usize_t num_vals=min(m_size, deque_traits<T>::ssize-m_offset);
    destruct(m_strides[idx]+m_offset, num_vals);
    m_allocator->free(m_strides[idx]);
    m_size-=num_vals;
    m_offset=0;
    ++idx;
  }
  m_first=m_last=m_stride_last=0;
  m_strides.clear();
}
//----

template<typename T>
void deque<T>::resize(usize_t size_)
{
  PFC_MEM_TRACK_STACK();
  if(size_<m_size)
  {
    // release elements from the end of the deque until the size matches
    do
    {
      usize_t num_vals=min(((m_offset+m_size-1)&deque_traits<T>::smask)+1, m_size-size_);
      m_size-=num_vals;
      usize_t offset=(m_offset+m_size)&deque_traits<T>::smask;
      reverse_destruct(m_strides.back()+offset, num_vals);
      if(!offset || !m_size)
        dealloc_stride_back();
    } while(m_size>size_);
    if(!size_)
      m_offset=0;
  }
  else
  {
    // add elements to the end of the deque until the size matches
    while(m_size<size_)
    {
      usize_t offset=(m_offset+m_size)&deque_traits<T>::smask;
      usize_t num_vals=min(deque_traits<T>::ssize-offset, size_-m_size);
      if(!offset)
        alloc_stride_back();
      default_construct(m_strides.back()+offset, num_vals);
      m_size+=num_vals;
    }
  }

  // setup first & last pointers
  if(m_size)
  {
    m_first=m_strides.front()+m_offset;
    m_last=m_strides.back()+((m_size-1)&deque_traits<T>::smask);
    m_stride_last=m_strides.back()+deque_traits<T>::smask;
  }
  else
    m_first=m_last=m_stride_last=0;
}
//----

template<typename T>
void deque<T>::resize(usize_t size_, const T &v_)
{
  PFC_MEM_TRACK_STACK();
  if(size_<m_size)
  {
    // release elements from the end of the deque until the size matches
    do
    {
      usize_t num_vals=min(((m_offset+m_size-1)&deque_traits<T>::smask)+1, m_size-size_);
      m_size-=num_vals;
      usize_t offset=(m_offset+m_size)&deque_traits<T>::smask;
      reverse_destruct(m_strides.back()+offset, num_vals);
      if(!offset || !m_size)
        dealloc_stride_back();
    } while(m_size>size_);
    if(!size_)
      m_offset=0;
  }
  else
  {
    // add elements to the end of the deque until the size matches
    while(m_size<size_)
    {
      usize_t offset=(m_offset+m_size)&deque_traits<T>::smask;
      usize_t num_vals=min(deque_traits<T>::ssize-offset, size_-m_size);
      if(!offset)
        alloc_stride_back();
      copy_construct(m_strides.back()+offset, v_, num_vals);
      m_size+=num_vals;
    }
  }

  // setup first & last pointers
  if(m_size)
  {
    m_first=m_strides.front()+m_offset;
    m_last=m_strides.back()+((m_size-1)&deque_traits<T>::smask);
    m_stride_last=m_strides.back()+deque_traits<T>::smask;
  }
  else
    m_first=m_last=m_stride_last=0;
}
//----

template<typename T>
void deque<T>::swap(deque &dq_)
{
  // swap content of deques
  pfc::swap(m_allocator, dq_.m_allocator);
  pfc::swap(m_size, dq_.m_size);
  pfc::swap(m_offset, dq_.m_offset);
  pfc::swap(m_first, dq_.m_first);
  pfc::swap(m_last, dq_.m_last);
  pfc::swap(m_stride_last, dq_.m_stride_last);
  m_strides.swap(dq_.m_strides);
}
//----------------------------------------------------------------------------

template<typename T>
memory_allocator_base &deque<T>::allocator() const
{
  return *m_allocator;
}
//----

template<typename T>
usize_t deque<T>::size() const
{
  return m_size;
}
//----

template<typename T>
const T &deque<T>::operator[](usize_t idx_) const
{
  // return nth element in the deque
  PFC_ASSERT_PEDANTIC_MSG(idx_<m_size, ("Trying to access element at index %u of deque<%s> (size=%u)\r\n", idx_, typeid(T).name(), m_size));
  idx_+=m_offset;
  return m_strides[idx_>>deque_traits<T>::sshift][idx_&deque_traits<T>::smask];
}
//----

template<typename T>
T &deque<T>::operator[](usize_t idx_)
{
  // return nth element in the deque
  PFC_ASSERT_PEDANTIC_MSG(idx_<m_size, ("Trying to access element at index %u of deque<%s> (size=%u)\r\n", idx_, typeid(T).name(), m_size));
  idx_+=m_offset;
  return m_strides[idx_>>deque_traits<T>::sshift][idx_&deque_traits<T>::smask];
}
//----

template<typename T>
const T &deque<T>::front() const
{
  // return the first element in the deque
  PFC_ASSERT_PEDANTIC(m_size);
  return *m_first;
}
//----

template<typename T>
T &deque<T>::front()
{
  // return the first element in the deque
  PFC_ASSERT_PEDANTIC(m_size);
  return *m_first;
}
//----

template<typename T>
const T &deque<T>::back() const
{
  // return the last element in the deque
  PFC_ASSERT_PEDANTIC(m_size);
  return *m_last;
}
//----

template<typename T>
T &deque<T>::back()
{
  // return the last element in the deque
  PFC_ASSERT_PEDANTIC(m_size);
  return *m_last;
}
//----

template<typename T>
typename deque<T>::const_iterator deque<T>::begin() const
{
  return const_iterator(*this, 0);
}
//----

template<typename T>
typename deque<T>::iterator deque<T>::begin()
{
  return iterator(*this, 0);
}
//----

template<typename T>
typename deque<T>::const_reverse_iterator deque<T>::rbegin() const
{
  return const_reverse_iterator(*this, m_size-1);
}
//----

template<typename T>
typename deque<T>::reverse_iterator deque<T>::rbegin()
{
  return reverse_iterator(*this, m_size-1);
}
//----

template<typename T>
typename deque<T>::const_iterator deque<T>::last() const
{
  return const_iterator(*this, m_size?m_size-1:0);
}
//----

template<typename T>
typename deque<T>::iterator deque<T>::last()
{
  return iterator(*this, m_size?m_size-1:0);
}
//----

template<typename T>
typename deque<T>::const_reverse_iterator deque<T>::rlast() const
{
  return const_reverse_iterator(*this, 0);
}
//----

template<typename T>
typename deque<T>::reverse_iterator deque<T>::rlast()
{
  return reverse_iterator(*this, 0);
}
//----

template<typename T>
typename deque<T>::const_iterator deque<T>::end() const
{
  return const_iterator(*this, m_size);
}
//----

template<typename T>
typename deque<T>::iterator deque<T>::end()
{
  return iterator(*this, m_size);
}
//----

template<typename T>
typename deque<T>::const_reverse_iterator deque<T>::rend() const
{
  return const_reverse_iterator(*this, usize_t(-1));
}
//----

template<typename T>
typename deque<T>::reverse_iterator deque<T>::rend()
{
  return reverse_iterator(*this, usize_t(-1));
}
//----

template<typename T>
void deque<T>::get(usize_t start_idx_, T *p_, usize_t num_items_) const
{
  // get items to the given array from the container
  PFC_ASSERT_MSG(start_idx_+num_items_<=m_size, ("Reading values past the end of the container\r\n"));
  destruct(p_, num_items_);
  start_idx_+=m_offset;
  while(num_items_)
  {
    // copy items in the stride to the given array
    usize_t num_stride_items=min(num_items_, deque_traits<T>::ssize-(start_idx_&deque_traits<T>::smask));
    copy_construct(p_, m_strides[start_idx_>>deque_traits<T>::sshift]+(start_idx_&deque_traits<T>::smask), num_stride_items);
    start_idx_+=num_stride_items;
    p_+=num_stride_items;
    num_items_-=num_stride_items;
  }
}
//----

template<typename T>
void deque<T>::set(usize_t start_idx_, const T *p_, usize_t num_items_)
{
  // set items from the given array to the container
  PFC_ASSERT_MSG(start_idx_+num_items_<=m_size, ("Writing values past the end of the container\r\n"));
  start_idx_+=m_offset;
  while(num_items_)
  {
    // copy items to the stride from the given array
    usize_t num_stride_items=min(num_items_, deque_traits<T>::ssize-(start_idx_&deque_traits<T>::smask));
    T *data=m_strides[start_idx_>>deque_traits<T>::sshift]+(start_idx_&deque_traits<T>::smask);
    destruct(data, num_stride_items);
    copy_construct(data, p_, num_stride_items);
    start_idx_+=num_stride_items;
    p_+=num_stride_items;
    num_items_-=num_stride_items;
  }
}
//----

template<typename T>
void deque<T>::set(usize_t start_idx_, const T &v_, usize_t num_items_)
{
  // set array of given item to the container
  PFC_ASSERT_MSG(start_idx_+num_items_<=m_size, ("Writing values past the end of the container\r\n"));
  start_idx_+=m_offset;
  while(num_items_)
  {
    // copy items to the stride from the given array
    usize_t num_stride_items=min(num_items_, deque_traits<T>::ssize-(start_idx_&deque_traits<T>::smask));
    T *data=m_strides[start_idx_>>deque_traits<T>::sshift]+(start_idx_&deque_traits<T>::smask);
    destruct(data, num_stride_items);
    copy_construct(data, v_, num_stride_items);
    start_idx_+=num_stride_items;
    num_items_-=num_stride_items;
  }
}
//----

template<typename T>
void deque<T>::push_front(const T &v_)
{
  // push new element to the beginning of the deque
  PFC_MEM_TRACK_STACK();
  if(!m_offset)
    alloc_stride_front();
  --m_offset;
  PFC_PNEW(--m_first)T(v_);  // todo: handle exceptions
  ++m_size;
}
//----

template<typename T>
T &deque<T>::push_front()
{
  // push default value to the beginning of the deque
  PFC_MEM_TRACK_STACK();
  if(!m_offset)
    alloc_stride_front();
  --m_offset;
  PFC_PNEW(--m_first)T;  // todo: handle exceptions
  ++m_size;
  return *m_first;
}
//----

template<typename T>
void deque<T>::push_back(const T &v_)
{
  // push new element to the end of the deque
  PFC_MEM_TRACK_STACK();
  if(m_last==m_stride_last)
    alloc_stride_back();
  PFC_PNEW(++m_last)T(v_);  // todo: handle exceptions
  ++m_size;
}
//----

template<typename T>
T &deque<T>::push_back()
{
  // push default value to the end of the deque
  PFC_MEM_TRACK_STACK();
  if(m_last==m_stride_last)
    alloc_stride_back();
  PFC_PNEW(++m_last)T;  // todo: handle exceptions
  ++m_size;
  return *m_last;
}
//----

template<typename T>
void deque<T>::insert_front(usize_t num_items_)
{
  // insert given number of default constructed items to the front of the deque
  PFC_MEM_TRACK_STACK();
  m_size+=num_items_;
  while(num_items_)
  {
    if(!m_offset)
      alloc_stride_front();
    usize_t ni=min(m_offset, num_items_);
    num_items_-=ni;
    m_first-=ni;
    m_offset-=ni;
    reverse_default_construct(m_first, ni);
  }
}
//----

template<typename T>
void deque<T>::insert_front(usize_t num_items_, const T &v_)
{
  // insert given number of given items to the front of the deque
  PFC_MEM_TRACK_STACK();
  m_size+=num_items_;
  while(num_items_)
  {
    if(!m_offset)
      alloc_stride_front();
    usize_t ni=min(m_offset, num_items_);
    num_items_-=ni;
    m_first-=ni;
    m_offset-=ni;
    reverse_copy_construct(m_first, v_, ni);
  }
}
//----

template<typename T>
void deque<T>::insert_front(usize_t num_items_, const T *v_)
{
  // insert given number of given items to the front of the deque
  PFC_MEM_TRACK_STACK();
  m_size+=num_items_;
  while(num_items_)
  {
    if(!m_offset)
      alloc_stride_front();
    usize_t ni=min(m_offset, num_items_);
    num_items_-=ni;
    m_first-=ni;
    m_offset-=ni;
    reverse_copy_construct(m_first, v_, ni);
    v_+=ni;
  }
}
//----

template<typename T>
void deque<T>::insert_back(usize_t num_items_)
{
  PFC_MEM_TRACK_STACK();
  resize(m_size+num_items_);
}
//----

template<typename T>
void deque<T>::insert_back(usize_t num_items_, const T &v_)
{
  PFC_MEM_TRACK_STACK();
  resize(m_size+num_items_, v_);
}
//----

template<typename T>
void deque<T>::insert_back(usize_t num_items_, const T *v_)
{
  // insert array of values to the deque
  PFC_MEM_TRACK_STACK();
  for(usize_t i=0; i<num_items_; ++i)
  {
    if(m_last==m_stride_last)
      alloc_stride_back();
    PFC_PNEW(++m_last)T(*v_++);  // todo: handle exceptions
  }
  m_size+=num_items_;
}
//----

template<typename T>
void deque<T>::pop_front()
{
  // remove the first element from the beginning of the deque
  PFC_ASSERT_PEDANTIC(m_size);
  --m_size;
  m_first++->~T();
  if(!((++m_offset)&deque_traits<T>::smask))
    dealloc_stride_front();
}
//----

template<typename T>
void deque<T>::pop_back()
{
  // remove the last element from the end of the deque
  PFC_ASSERT_PEDANTIC(m_size);
  --m_size;
  m_last--->~T();
  if(m_last==m_stride_last-deque_traits<T>::ssize)
    dealloc_stride_back();
}
//----

template<typename T>
void deque<T>::remove_front(usize_t num_items_)
{
  // remove given number of items from the beginning of the deque
  PFC_ASSERT_PEDANTIC(m_size>=num_items_);
  m_size-=num_items_;
  while(num_items_)
  {
    usize_t ni=min(num_items_, deque_traits<T>::ssize-m_offset);
    num_items_-=ni;
    destruct(m_first, ni);
    m_first+=ni;
    m_offset+=ni;
    if(!(m_offset&deque_traits<T>::smask))
      dealloc_stride_front();
  }
}
//----

template<typename T>
void deque<T>::remove_back(usize_t num_items_)
{
  // remove given number of items from the end of the deque
  PFC_ASSERT_PEDANTIC(m_size>=num_items_);
  m_size-=num_items_;
  while(num_items_)
  {
    usize_t ni=min(num_items_, usize_t(m_last-(m_stride_last-deque_traits<T>::ssize)));
    num_items_-=ni;
    m_last-=ni,
    reverse_destruct(m_last+1, ni);
    if(m_last==m_stride_last-deque_traits<T>::ssize)
      dealloc_stride_back();
  }
}
//----------------------------------------------------------------------------

template<typename T>
void deque<T>::cctor(const deque &dq_)
{
  // copy-construct the deque
  m_size=0;
  m_offset=dq_.m_offset;
  m_strides.resize(dq_.m_strides.size());
  usize_t idx=0, offset=m_offset;
  PFC_EDTOR(*this, &deque<T>::clear);
  while(m_size<dq_.m_size)
  {
    eh_data<T> p(*m_allocator, deque_traits<T>::ssize, deque_traits<T>::block_alloc_align);
    m_strides[idx]=p.data;
    usize_t num_vals=min(deque_traits<T>::ssize-offset, dq_.m_size-m_size);
    copy_construct(m_strides[idx]+offset, dq_.m_strides[idx]+offset, num_vals);
    p.reset();
    offset=0;
    ++idx;
    m_size+=num_vals;
  }
  PFC_EDTOR_RESET();

  // setup first & last pointers
  if(m_size)
  {
    m_first=m_strides.front()+m_offset;
    m_last=m_strides.back()+((m_size-1)&deque_traits<T>::smask);
    m_stride_last=m_strides.back()+deque_traits<T>::smask;
  }
  else
    m_first=m_last=m_stride_last=0;
}
//----

template<typename T>
void deque<T>::alloc_stride_front()
{
  // allocate new first stride
  eh_data<T> p(*m_allocator, deque_traits<T>::ssize, deque_traits<T>::block_alloc_align);
  m_strides.push_back(0);
  mem_move(m_strides.data()+1, m_strides.data(), sizeof(T*)*(m_strides.size()-1));
  m_strides.front()=p.data;
  m_first=p.data+deque_traits<T>::ssize;
  if(!m_size)
    m_last=m_stride_last=m_first-1;
  m_offset=deque_traits<T>::ssize;
  p.reset();
}
//----

template<typename T>
void deque<T>::alloc_stride_back()
{
  // allocate new last stride
  eh_data<T> p(*m_allocator, deque_traits<T>::ssize, deque_traits<T>::block_alloc_align);
  m_strides.push_back(p.data);
  m_last=p.data-1;
  m_stride_last=p.data+deque_traits<T>::smask;
  if(!m_size)
    m_first=p.data;
  p.reset();
}
//----

template<typename T>
void deque<T>::dealloc_stride_front()
{
  // deallocate first stride
  m_allocator->free(m_strides.front());
  mem_move(m_strides.data(), m_strides.data()+1, sizeof(T*)*(m_strides.size()-1));
  m_strides.pop_back();
  m_offset=0;
  if(!m_size)
    m_first=m_last=m_stride_last=0;
  else
    m_first=m_strides.front();
}
//----

template<typename T>
void deque<T>::dealloc_stride_back()
{
  // deallocate last stride
  m_allocator->free(m_strides.back());
  m_strides.pop_back();
  if(!m_size)
    m_first=m_last=m_stride_last=0;
  else
    m_last=m_stride_last=m_strides.back()+deque_traits<T>::smask;
}
//----------------------------------------------------------------------------


//============================================================================
// deque::const_iterator_impl
//============================================================================
template<typename T>
template<bool is_forward>
deque<T>::const_iterator_impl<is_forward>::const_iterator_impl()
  :m_deque(0)
  ,m_index(0)
{
}
//----

template<typename T>
template<bool is_forward>
deque<T>::const_iterator_impl<is_forward>::const_iterator_impl(const iterator_impl<is_forward> &it_)
  :m_deque(it_.m_deque)
  ,m_index(it_.m_index)
{
}
//----

template<typename T>
template<bool is_forward>
void deque<T>::const_iterator_impl<is_forward>::reset()
{
  m_deque=0;
  m_index=0;
}
//----------------------------------------------------------------------------

template<typename T>
template<bool is_forward>
bool deque<T>::const_iterator_impl<is_forward>::operator==(const const_iterator_impl &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return m_index==it_.m_index;
}
//----

template<typename T>
template<bool is_forward>
bool deque<T>::const_iterator_impl<is_forward>::operator==(const iterator_impl<is_forward> &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return m_index==it_.m_index;
}
//----

template<typename T>
template<bool is_forward>
bool deque<T>::const_iterator_impl<is_forward>::operator!=(const const_iterator_impl &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return m_index!=it_.m_index;
}
//----

template<typename T>
template<bool is_forward>
bool deque<T>::const_iterator_impl<is_forward>::operator!=(const iterator_impl<is_forward> &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return m_index!=it_.m_index;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> &deque<T>::const_iterator_impl<is_forward>::operator++()
{
  m_index+=is_forward?1:usize_t(-1);
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> &deque<T>::const_iterator_impl<is_forward>::operator--()
{
  m_index+=is_forward?usize_t(-1):1;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> &deque<T>::const_iterator_impl<is_forward>::operator+=(ssize_t offset_)
{
  m_index+=is_forward?offset_:-offset_;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> &deque<T>::const_iterator_impl<is_forward>::operator+=(const const_iterator_impl &it_)
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  m_index+=is_forward?it_.m_index:m_deque->m_size-1-it_.m_index;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> &deque<T>::const_iterator_impl<is_forward>::operator+=(const iterator_impl<is_forward> &it_)
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  m_index+=is_forward?it_.m_index:m_deque->m_size-1-it_.m_index;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> &deque<T>::const_iterator_impl<is_forward>::operator-=(ssize_t offset_)
{
  m_index+=is_forward?-offset_:offset_;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> &deque<T>::const_iterator_impl<is_forward>::operator-=(const const_iterator_impl &it_)
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  m_index+=is_forward?-it_.m_index:it_.m_index-m_deque->m_size+1;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> &deque<T>::const_iterator_impl<is_forward>::operator-=(const iterator_impl<is_forward> &it_)
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  m_index+=is_forward?-it_.m_index:it_.m_index-m_deque->m_size+1;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> deque<T>::const_iterator_impl<is_forward>::operator+(ssize_t offset_) const
{
  return const_iterator_impl(*m_deque, m_index+(is_forward?offset_:-offset_));
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> deque<T>::const_iterator_impl<is_forward>::operator+(const const_iterator_impl &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return const_iterator_impl(*m_deque, m_index+(is_forward?it_.m_index:m_deque->m_size-1-it_.m_index));
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> deque<T>::const_iterator_impl<is_forward>::operator+(const iterator_impl<is_forward> &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return const_iterator_impl(*m_deque, m_index+(is_forward?it_.m_index:m_deque->m_size-1-it_.m_index));
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> deque<T>::const_iterator_impl<is_forward>::operator-(ssize_t offset_) const
{
  return const_iterator_impl(*m_deque, m_index+(is_forward?-offset_:offset_));
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> deque<T>::const_iterator_impl<is_forward>::operator-(const const_iterator_impl &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return const_iterator_impl(*m_deque, m_index+(is_forward?-it_.m_index:it_.m_index-m_deque->m_size+1));
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::const_iterator_impl<is_forward> deque<T>::const_iterator_impl<is_forward>::operator-(const iterator_impl<is_forward> &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return const_iterator_impl(*m_deque, m_index+(is_forward?-it_.m_index:it_.m_index-m_deque->m_size+1));
}
//----

template<typename T>
template<bool is_forward>
const T &deque<T>::const_iterator_impl<is_forward>::operator[](usize_t index_) const
{
  return (*m_deque)[m_index+index_];
}
//----

template<typename T>
template<bool is_forward>
const T &deque<T>::const_iterator_impl<is_forward>::operator*() const
{
  return (*m_deque)[m_index];
}
//----

template<typename T>
template<bool is_forward>
const T *deque<T>::const_iterator_impl<is_forward>::operator->() const
{
  return &(*m_deque)[m_index];
}
//----

template<typename T>
template<bool is_forward>
usize_t deque<T>::const_iterator_impl<is_forward>::index() const
{
  return m_index;
}
//----------------------------------------------------------------------------

template<typename T>
template<bool is_forward>
deque<T>::const_iterator_impl<is_forward>::const_iterator_impl(const deque<T> &deque_, usize_t index_)
  :m_deque(&deque_)
  ,m_index(index_)
{
}
//----------------------------------------------------------------------------


//============================================================================
// deque::iterator_impl
//============================================================================
template<typename T>
template<bool is_forward>
deque<T>::iterator_impl<is_forward>::iterator_impl()
  :m_deque(0)
  ,m_index(0)
{
}
//----

template<typename T>
template<bool is_forward>
void deque<T>::iterator_impl<is_forward>::reset()
{
  m_deque=0;
  m_index=0;
}
//----------------------------------------------------------------------------

template<typename T>
template<bool is_forward>
bool deque<T>::iterator_impl<is_forward>::operator==(const const_iterator_impl<is_forward> &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return m_index==it_.m_index;
}
//----

template<typename T>
template<bool is_forward>
bool deque<T>::iterator_impl<is_forward>::operator==(const iterator_impl &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return m_index==it_.m_index;
}
//----

template<typename T>
template<bool is_forward>
bool deque<T>::iterator_impl<is_forward>::operator!=(const const_iterator_impl<is_forward> &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return m_index!=it_.m_index;
}
//----

template<typename T>
template<bool is_forward>
bool deque<T>::iterator_impl<is_forward>::operator!=(const iterator_impl &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return m_index!=it_.m_index;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> &deque<T>::iterator_impl<is_forward>::operator++()
{
  m_index+=is_forward?1:usize_t(-1);
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> &deque<T>::iterator_impl<is_forward>::operator--()
{
  m_index+=is_forward?usize_t(-1):1;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> &deque<T>::iterator_impl<is_forward>::operator+=(ssize_t offset_)
{
  m_index+=is_forward?offset_:-offset_;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> &deque<T>::iterator_impl<is_forward>::operator+=(const const_iterator_impl<is_forward> &it_)
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  m_index+=is_forward?it_.m_index:m_deque->m_size-1-it_.m_index;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> &deque<T>::iterator_impl<is_forward>::operator+=(const iterator_impl &it_)
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  m_index+=is_forward?it_.m_index:m_deque->m_size-1-it_.m_index;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> &deque<T>::iterator_impl<is_forward>::operator-=(ssize_t offset_)
{
  m_index-=offset_;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> &deque<T>::iterator_impl<is_forward>::operator-=(const const_iterator_impl<is_forward> &it_)
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  m_index+=is_forward?-it_.m_index:it_.m_index-m_deque->m_size+1;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> &deque<T>::iterator_impl<is_forward>::operator-=(const iterator_impl &it_)
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  m_index+=is_forward?-it_.m_index:it_.m_index-m_deque->m_size+1;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> deque<T>::iterator_impl<is_forward>::operator+(ssize_t offset_) const
{
  return iterator_impl(*m_deque, m_index+(is_forward?offset_:-offset_));
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> deque<T>::iterator_impl<is_forward>::operator+(const const_iterator_impl<is_forward> &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return iterator_impl(*m_deque, m_index+(is_forward?it_.m_index:m_deque->m_size-1-it_.m_index));
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> deque<T>::iterator_impl<is_forward>::operator+(const iterator_impl &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return iterator(*m_deque, m_index+(is_forward?it_.m_index:m_deque->m_size-1-it_.m_index));
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> deque<T>::iterator_impl<is_forward>::operator-(ssize_t offset_) const
{
  return iterator_impl(*m_deque, m_index+(is_forward?-offset_:offset_));
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> deque<T>::iterator_impl<is_forward>::operator-(const const_iterator_impl<is_forward> &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return iterator_impl(*m_deque, m_index+(is_forward?-it_.m_index:it_.m_index-m_deque->m_size+1));
}
//----

template<typename T>
template<bool is_forward>
typename deque<T>::iterator_impl<is_forward> deque<T>::iterator_impl<is_forward>::operator-(const iterator_impl &it_) const
{
  PFC_ASSERT_PEDANTIC(m_deque==it_.m_deque);
  return iterator_impl(*m_deque, m_index+(is_forward?-it_.m_index:it_.m_index-m_deque->m_size+1));
}
//----

template<typename T>
template<bool is_forward>
T &deque<T>::iterator_impl<is_forward>::operator[](usize_t index_) const
{
  return (*m_deque)[m_index+index_];
}
//----

template<typename T>
template<bool is_forward>
T &deque<T>::iterator_impl<is_forward>::operator*() const
{
  return (*m_deque)[m_index];
}
//----

template<typename T>
template<bool is_forward>
T *deque<T>::iterator_impl<is_forward>::operator->() const
{
  return &(*m_deque)[m_index];
}
//----

template<typename T>
template<bool is_forward>
usize_t deque<T>::iterator_impl<is_forward>::index() const
{
  return m_index;
}
//----------------------------------------------------------------------------

template<typename T>
template<bool is_forward>
deque<T>::iterator_impl<is_forward>::iterator_impl(deque<T> &deque_, usize_t index_)
  :m_deque(&deque_)
  ,m_index(index_)
{
}
//----------------------------------------------------------------------------

template<typename T>
template<bool is_forward>
void deque<T>::iterator_impl<is_forward>::move_construct_impl(const iterator_impl &dst_, const iterator_impl &src_, usize_t count_)
{
  if(count_)
  {
    // move-construct deque sequence in passes
    PFC_ASSERT(dst_.m_deque && src_.m_deque);
    usize_t dst_idx=dst_.m_index+dst_.m_deque->m_offset;
    usize_t src_idx=src_.m_index+src_.m_deque->m_offset;
    if(src_idx>dst_idx)
    {
      // move items starting from the beginning of the deque
      do
      {
        // copy longest continuous sequence from source to target deque
        enum {smask=deque_traits<T>::smask, ssize=deque_traits<T>::ssize, sshift=deque_traits<T>::sshift};
        usize_t dst_stride_idx=dst_idx&smask;
        usize_t dst_stride_left=ssize-dst_stride_idx;
        usize_t src_stride_idx=src_idx&smask;
        usize_t src_stride_left=ssize-src_stride_idx;
        usize_t num_pass_values=min(dst_stride_left, src_stride_left, count_);
        move_construct(dst_.m_deque->m_strides[dst_idx>>sshift]+dst_stride_idx,
                       src_.m_deque->m_strides[src_idx>>sshift]+src_stride_idx,
                       num_pass_values);
        dst_idx+=num_pass_values;
        src_idx+=num_pass_values;
        count_-=num_pass_values;
      } while(count_);
    }
    else
    {
      // move items starting from the end of the deque
      dst_idx+=count_-1;
      src_idx+=count_-1;
      do
      {
        // copy longest continuous sequence from source to target deque
        enum {smask=deque_traits<T>::smask, ssize=deque_traits<T>::ssize, sshift=deque_traits<T>::sshift};
        usize_t dst_stride_idx=dst_idx&smask;
        usize_t src_stride_idx=src_idx&smask;
        usize_t num_pass_values=min(dst_stride_idx+1, src_stride_idx+1, count_);
        move_construct(dst_.m_deque->m_strides[dst_idx>>sshift]+dst_stride_idx-num_pass_values+1,
                       src_.m_deque->m_strides[src_idx>>sshift]+src_stride_idx-num_pass_values+1,
                       num_pass_values);
        dst_idx-=num_pass_values;
        src_idx-=num_pass_values;
        count_-=num_pass_values;
      } while(count_);
    }
  }
}
//----

template<typename T>
template<bool is_forward>
void deque<T>::iterator_impl<is_forward>::rotate_sequence_left_impl(const iterator_impl &first_, const iterator_impl &last_)
{
  // rotate deque data sequence to the left
  PFC_ASSERT_PEDANTIC_MSG(first_.m_deque && first_.m_deque==last_.m_deque, ("Iterators must be valid and of the same deque (first: %p, last: %p)\r\n", first_.m_deque, last_.m_deque));
  PFC_ASSERT_PEDANTIC_MSG(first_.m_index<=last_.m_index, ("deque first iterator must precede last iterator (first: %u, last: %u)\r\n", first_.m_index, last_.m_index));
  T &first=(*first_.m_deque)[first_.m_index], tmp(first);
  first.~T();
  move_construct_impl(first_, iterator_impl(*first_.m_deque, first_.m_index+1), last_.m_index-first_.m_index);
  PFC_PNEW(&(*last_.m_deque)[last_.m_index])T(tmp);
}
//----

template<typename T>
template<bool is_forward>
void deque<T>::iterator_impl<is_forward>::rotate_sequence_right_impl(const iterator_impl &first_, const iterator_impl &last_)
{
  // rotate deque data sequence to the right
  PFC_ASSERT_PEDANTIC_MSG(first_.m_deque && first_.m_deque==last_.m_deque, ("Iterators must be valid and of the same deque (first: %p, last: %p)\r\n", first_.m_deque, last_.m_deque));
  PFC_ASSERT_PEDANTIC_MSG(first_.m_index<=last_.m_index, ("deque first iterator must precede last iterator (first: %u, last: %u)\r\n", first_.m_index, last_.m_index));
  T &last=(*last_.m_deque)[last_.m_index], tmp(last);
  last.~T();
  move_construct_impl(iterator_impl(*first_.m_deque, first_.m_index+1), first_, last_.m_index-first_.m_index);
  PFC_PNEW(&(*first_.m_deque)[first_.m_index])T(tmp);
}
//----------------------------------------------------------------------------


//============================================================================
// list
//============================================================================
template<typename T>
list<T>::list(memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
  ,m_size(0)
  ,m_first(0)
  ,m_last(0)
{
  PFC_ASSERT_CALL(m_allocator->check_allocator(list_traits<T>::block_alloc_size, list_traits<T>::block_alloc_align));
}
//----

template<typename T>
list<T>::list(const list &l_)
  :m_allocator(&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  cctor(l_);
}
//----

template<typename T>
list<T>::list(const list &l_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(list_traits<T>::block_alloc_size, list_traits<T>::block_alloc_align));
  cctor(l_);
}
//----

template<typename T>
list<T>::list(usize_t size_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // construct the list
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(list_traits<T>::block_alloc_size, list_traits<T>::block_alloc_align));
  item **next=&m_first, *i=0;
  if((m_size=size_)!=0)
  {
    PFC_EDTOR(*this, &list<T>::clear);
    item *prev=0;
    do
    {
      // add new item to the list
      eh_data<item> p(*m_allocator, 1, list_traits<T>::block_alloc_align);
      i=p.data;
      PFC_PNEW(&i->data)T;
      p.reset();
      i->prev=prev;
      *next=i;
      prev=i;
      next=&i->next;
    } while(--size_);
    PFC_EDTOR_RESET();
  }
  *next=0;
  m_last=i;
}
//----

template<typename T>
list<T>::list(usize_t size_, const T &v_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // construct the list
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(list_traits<T>::block_alloc_size, list_traits<T>::block_alloc_align));
  item **next=&m_first, *i=0;
  if((m_size=size_)!=0)
  {
    PFC_EDTOR(*this, &list<T>::clear);
    item *prev=0;
    do
    {
      // add new item to the list
      eh_data<item> p(*m_allocator, 1, list_traits<T>::block_alloc_align);
      i=p.data;
      PFC_PNEW(&i->data)T(v_);
      p.reset();
      i->prev=prev;
      *next=i;
      prev=i;
      next=&i->next;
    } while(--size_);
    PFC_EDTOR_RESET();
  }
  *next=0;
  m_last=i;
}
//----

template<typename T>
list<T>::~list()
{
  clear();
}
//----

template<typename T>
void list<T>::set_allocator(memory_allocator_base *alloc_)
{
  PFC_ASSERT_MSG(!m_size, ("Unable to change the allocator for a non-empty list\r\n"));
  m_allocator=alloc_?alloc_:&default_memory_allocator::inst();
  PFC_ASSERT_CALL(m_allocator->check_allocator(list_traits<T>::block_alloc_size, list_traits<T>::block_alloc_align));
}
//----

template<typename T>
void list<T>::operator=(const list &l_)
{
  list<T> l(l_);
  swap(l);
}
//----

template<typename T>
void list<T>::clear()
{
  // clear the list
  item *i=m_last;
  if(i)
  {
    do
    {
      i->data.~T();
      item *prev=i->prev;
      m_allocator->free(i);
      i=prev;
    } while(i);
    m_first=m_last=0;
    m_size=0;
  }
}
//----

template<typename T>
void list<T>::resize(usize_t size_)
{
  if(size_<m_size)
  {
    // release elements from the end of the list to match given size
    usize_t count=m_size-size_;
    item *it=m_last;
    do
    {
      it->data.~T();
      item *prev=it->prev;
      m_allocator->free(it);
      it=prev;
    } while(--count);
    m_size=size_;
    m_last=it;
    if(it)
      m_last->next=0;
    else
      m_first=0;
  }
  else
  {
    // add elements to the end of the list to match given size
    PFC_MEM_TRACK_STACK();
    usize_t count=size_-m_size;
    if(count)
    {
      item *prev=m_last, **next=m_last?&m_last->next:&m_first, *i;
      do
      {
        // add new item to the list
        eh_data<item> p(*m_allocator, 1, list_traits<T>::block_alloc_align);
        i=p.data;
        PFC_PNEW(&i->data)T;
        p.reset();
        i->prev=prev;
        *next=i;
        prev=i;
        next=&i->next;
      } while(--count);
      m_size=size_;
      *next=0;
      m_last=i;
    }
  }
}
//----

template<typename T>
void list<T>::resize(usize_t size_, const T &v_)
{
  if(size_<m_size)
  {
    // release elements from the end of the list to match given size
    usize_t count=m_size-size_;
    item *it=m_last;
    do
    {
      it->data.~T();
      item *prev=it->prev;
      m_allocator->free(it);
      it=prev;
    } while(--count);
    m_size=size_;
    m_last=it;
    if(it)
      m_last->next=0;
    else
      m_first=0;
  }
  else
  {
    // add elements to the end of the list to match given size
    PFC_MEM_TRACK_STACK();
    usize_t count=size_-m_size;
    if(count)
    {
      item *prev=m_last, **next=m_last?&m_last->next:&m_first, *i;
      do
      {
        // add new item to the list
        eh_data<item> p(*m_allocator, 1, list_traits<T>::block_alloc_align);
        i=p.data;
        PFC_PNEW(&i->data)T(v_);
        p.reset();
        i->prev=prev;
        *next=i;
        prev=i;
        next=&i->next;
      } while(--count);
      m_size=size_;
      *next=0;
      m_last=i;
    }
  }
}
//----

template<typename T>
void list<T>::swap(list &l_)
{
  // swap content of the lists
  pfc::swap(m_allocator, l_.m_allocator);
  pfc::swap(m_size, l_.m_size);
  pfc::swap(m_first, l_.m_first);
  pfc::swap(m_last, l_.m_last);
}
//----------------------------------------------------------------------------

template<typename T>
memory_allocator_base &list<T>::allocator() const
{
  return *m_allocator;
}
//----

template<typename T>
usize_t list<T>::size() const
{
  return m_size;
}
//----

template<typename T>
const T &list<T>::front() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return m_first->data;
}
//----

template<typename T>
T &list<T>::front()
{
  PFC_ASSERT_PEDANTIC(m_size);
  return m_first->data;
}
//----

template<typename T>
const T &list<T>::back() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return m_last->data;
}
//----

template<typename T>
T &list<T>::back()
{
  PFC_ASSERT_PEDANTIC(m_size);
  return m_last->data;
}
//----

template<typename T>
typename list<T>::const_iterator list<T>::begin() const
{
  return m_first;
}
//----

template<typename T>
typename list<T>::iterator list<T>::begin()
{
  return iterator(*this, m_first);
}
//----

template<typename T>
typename list<T>::const_reverse_iterator list<T>::rbegin() const
{
  return m_last;
}
//----

template<typename T>
typename list<T>::reverse_iterator list<T>::rbegin()
{
  return reverse_iterator(*this, m_last);
}
//----

template<typename T>
typename list<T>::const_iterator list<T>::last() const
{
  return const_iterator(m_last);
}
//----

template<typename T>
typename list<T>::iterator list<T>::last()
{
  return iterator(*this, m_last);
}
//----

template<typename T>
typename list<T>::const_reverse_iterator list<T>::rlast() const
{
  return const_reverse_iterator(m_first);
}
//----

template<typename T>
typename list<T>::reverse_iterator list<T>::rlast()
{
  return reverse_iterator(*this, m_first);
}
//----

template<typename T>
typename list<T>::const_iterator list<T>::end() const
{
  return const_iterator();
}
//----

template<typename T>
typename list<T>::iterator list<T>::end()
{
  return iterator();
}
//----

template<typename T>
typename list<T>::const_reverse_iterator list<T>::rend() const
{
  return const_reverse_iterator();
}
//----

template<typename T>
typename list<T>::reverse_iterator list<T>::rend()
{
  return reverse_iterator();
}
//----

template<typename T>
void list<T>::push_front(const T &v_)
{
  // push an element to the beginning of the list
  PFC_MEM_TRACK_STACK();
  eh_data<item> p(*m_allocator, 1, list_traits<T>::block_alloc_align);
  item *i=p.data;
  PFC_PNEW(&p.data->data)T(v_);
  p.reset();
  i->prev=0;
  i->next=m_first;
  if(!m_last)
    m_last=i;
  else
    m_first->prev=i;
  m_first=i;
  ++m_size;
}
//----

template<typename T>
T &list<T>::push_front()
{
  // push default value to the beginning of the list
  PFC_MEM_TRACK_STACK();
  eh_data<item> p(*m_allocator, 1, list_traits<T>::block_alloc_align);
  item *i=p.data;
  PFC_PNEW(&p.data->data)T;
  p.reset();
  i->prev=0;
  i->next=m_first;
  if(!m_last)
    m_last=i;
  else
    m_first->prev=i;
  m_first=i;
  ++m_size;
  return m_first->data;
}
//----

template<typename T>
void list<T>::push_back(const T &v_)
{
  // push an element to the end of the list
  PFC_MEM_TRACK_STACK();
  eh_data<item> p(*m_allocator, 1, list_traits<T>::block_alloc_align);
  item *i=p.data;
  PFC_PNEW(&i->data)T(v_);
  p.reset();
  i->prev=m_last;
  i->next=0;
  if(!m_first)
    m_first=i;
  else
    m_last->next=i;
  m_last=i;
  ++m_size;
}
//----

template<typename T>
T &list<T>::push_back()
{
  // push an element to the end of the list
  PFC_MEM_TRACK_STACK();
  eh_data<item> p(*m_allocator, 1, list_traits<T>::block_alloc_align);
  item *i=p.data;
  PFC_PNEW(&i->data)T;
  p.reset();
  i->prev=m_last;
  i->next=0;
  if(!m_first)
    m_first=i;
  else
    m_last->next=i;
  m_last=i;
  ++m_size;
  return m_last->data;
}
//----

template<typename T>
void list<T>::insert_front(usize_t num_items_)
{
  PFC_MEM_TRACK_STACK();
  while(num_items_--)
    push_front();
}
//----

template<typename T>
void list<T>::insert_front(usize_t num_items_, const T &v_)
{
  PFC_MEM_TRACK_STACK();
  while(num_items_--)
    push_front(v_);
}
//----

template<typename T>
void list<T>::insert_front(usize_t num_items_, const T *v_)
{
  PFC_MEM_TRACK_STACK();
  while(num_items_--)
    push_front(*v_++);
}
//----

template<typename T>
void list<T>::insert_front(const list<T> &l_)
{
  list<T> l(l_);
  splice_front(l);
}
//----

template<typename T>
void list<T>::insert_back(usize_t num_items_)
{
  PFC_MEM_TRACK_STACK();
  resize(m_size+num_items_);
}
//----

template<typename T>
void list<T>::insert_back(usize_t num_items_, const T &v_)
{
  PFC_MEM_TRACK_STACK();
  resize(m_size+num_items_, v_);
}
//----

template<typename T>
void list<T>::insert_back(usize_t num_items_, const T *v_)
{
  PFC_MEM_TRACK_STACK();
  for(usize_t i=0; i<num_items_; ++i)
    push_back(*v_++);
}
//----

template<typename T>
void list<T>::insert_back(const list<T> &l_)
{
  list<T> l(l_);
  splice_back(l);
}
//----

template<typename T>
void list<T>::insert_before(iterator &it_, const T &v_)
{
  // insert given item before the iterator
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_PEDANTIC(it_.m_item);
  eh_data<item> p(*m_allocator, 1, list_traits<T>::block_alloc_align);
  item *i=p.data;
  PFC_PNEW(&i->data)T(v_);
  p.reset();
  if(it_.m_item->prev)
  {
    it_.m_item->prev->next=i;
    i->prev=it_.m_item->prev;
  }
  else
    m_first=i;
  it_.m_item->prev=i;
  i->next=it_.m_item;
  ++m_size;
}
//----

template<typename T>
T &list<T>::insert_before(iterator &it_)
{
  // insert default-constructed item before the iterator
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_PEDANTIC(it_.m_item);
  eh_data<item> p(*m_allocator, 1, list_traits<T>::block_alloc_align);
  item *i=p.data;
  PFC_PNEW(&i->data)T;
  p.reset();
  if(it_.m_item->prev)
  {
    it_.m_item->prev->next=i;
    i->prev=it_.m_item->prev;
  }
  else
  {
    m_first=i;
    i->prev=0;
  }
  it_.m_item->prev=i;
  i->next=it_.m_item;
  ++m_size;
  return i->data;
}
//----

template<typename T>
void list<T>::insert_after(iterator &it_, const T &v_)
{
  // insert given item after the iterator
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_PEDANTIC(it_.m_item);
  eh_data<item> p(*m_allocator, 1, list_traits<T>::block_alloc_align);
  item *i=p.data;
  PFC_PNEW(&i->data)T(v_);
  p.reset();
  if(it_.m_item->next)
  {
    it_.m_item->next->prev=i;
    i->next=it_.m_item->next;
  }
  else
  {
    m_last=i;
    i->next=0;
  }
  it_.m_item->next=i;
  i->prev=it_.m_item;
  ++m_size;
}
//----

template<typename T>
T &list<T>::insert_after(iterator &it_)
{
  // insert default-constructed item after the iterator
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_PEDANTIC(it_.m_item);
  eh_data<item> p(*m_allocator, 1, list_traits<T>::block_alloc_align);
  item *i=p.data;
  PFC_PNEW(&i->data)T;
  p.reset();
  if(it_.m_item->next)
  {
    it_.m_item->next->prev=i;
    i->next=it_.m_item->next;
  }
  else
    m_last=i;
  it_.m_item->next=i;
  i->prev=it_.m_item;
  ++m_size;
  return i->data;
}
//----

template<typename T>
void list<T>::splice_front(list &l_)
{
  // push a list to the beginning of the list
  PFC_ASSERT(m_allocator==l_.m_allocator);
  m_size+=l_.m_size;
  if(!m_first)
  {
    m_first=l_.m_first;
    m_last=l_.m_last;
  }
  else
  {
    m_first->prev=l_.m_last;
    if(l_.m_last)
    {
      l_.m_last->next=m_first;
      m_first=l_.m_first;
    }
  }

  // clear the source list
  l_.m_size=0;
  l_.m_first=0;
  l_.m_last=0;
}
//----

template<typename T>
void list<T>::splice_front(iterator &it_)
{
  if(it_.m_item)
  {
    // remove item from its list and add to the beginning of this list
    PFC_ASSERT(m_allocator==it_.m_list->m_allocator);
    it_.m_list->detach(it_);
    it_.m_item->next=m_first;
    it_.m_item->prev=0;
    if(m_first)
      m_first->prev=it_.m_item;
    else
      m_last=it_.m_item;
    m_first=it_.m_item;
    ++m_size;
  }
}
//----

template<typename T>
void list<T>::splice_back(list &l_)
{
  // push a list to the end of the list
  PFC_ASSERT(m_allocator==l_.m_allocator);
  m_size+=l_.m_size;
  if(!m_first)
  {
    m_first=l_.m_first;
    m_last=l_.m_last;
  }
  else
  {
    m_last->next=l_.m_first;
    if(l_.m_first)
    {
      l_.m_first->prev=m_last;
      m_last=l_.m_last;
    }
  }

  // clear the source list
  l_.m_size=0;
  l_.m_first=0;
  l_.m_last=0;
}
//----

template<typename T>
void list<T>::splice_back(iterator &it_)
{
  if(it_.m_item)
  {
    // remove item from its list and add to the end of this list
    PFC_ASSERT(m_allocator==it_.m_list->m_allocator);
    it_.m_list->detach(it_);
    it_.m_item->next=0;
    it_.m_item->prev=m_last;
    if(m_last)
      m_last->next=it_.m_item;
    else
      m_first=it_.m_item;
    m_last=it_.m_item;
    ++m_size;
  }
}
//----

template<typename T>
void list<T>::pop_front()
{
  // remove element from the beginning of the list
  PFC_ASSERT_PEDANTIC(m_size);
  item *i=m_first;
  m_first=i->next;
  if(!--m_size)
    m_last=0;
  else
    m_first->prev=0;
  i->data.~T();
  m_allocator->free(i);
}
//----

template<typename T>
void list<T>::pop_back()
{
  // remove element from the end of the list
  PFC_ASSERT_PEDANTIC(m_size);
  item *i=m_last;
  m_last=i->prev;
  if(!--m_size)
    m_first=0;
  else
    m_last->next=0;
  i->data.~T();
  m_allocator->free(i);
}
//----

template<typename T>
void list<T>::remove_front(usize_t num_items_)
{
  // remove given number of items from the beginning of the list
  PFC_ASSERT(m_size>=num_items_);
  for(usize_t i=0; i<num_items_; ++i)
  {
    item *next=m_first->next;
    m_first->data.~T();
    m_allocator->free(m_first);
    m_first=next;
  }
  m_size-=num_items_;
  if(!m_size)
    m_last=0;
}
//----

template<typename T>
void list<T>::remove_back(usize_t num_items_)
{
  // remove given number of items from the end of the list
  PFC_ASSERT(m_size>=num_items_);
  for(usize_t i=0; i<num_items_; ++i)
  {
    item *prev=m_last->prev;
    m_last->data.~T();
    m_allocator->free(m_last);
    m_last=prev;
  }
  m_size-=num_items_;
  if(!m_size)
    m_first=0;
}
//----

template<typename T>
template<bool is_forward>
void list<T>::erase(iterator_impl<is_forward> &it_)
{
  // remove item from the list and destroy it
  PFC_ASSERT_PEDANTIC(it_.m_item);
  detach(it_);
  it_.m_item->data.~T();
  item *next=is_forward?it_.m_item->next:it_.m_item->prev;
  m_allocator->free(it_.m_item);
  it_.m_item=next;
}
//----------------------------------------------------------------------------

template<typename T>
void list<T>::cctor(const list &l_)
{
  // copy-construct the list
  item **next=&m_first, *i=0;
  if((m_size=l_.m_size)!=0)
  {
    PFC_EDTOR(*this, &list<T>::clear);
    item *it=l_.m_first, *prev=0;
    do
    {
      // add new item to the list
      eh_data<item> p(*m_allocator, 1, list_traits<T>::block_alloc_align);
      i=p.data;
      PFC_PNEW(&i->data)T(it->data);
      p.reset();
      i->prev=prev;
      *next=i;
      prev=i;
      next=&i->next;
    } while((it=it->next)!=0);
    PFC_EDTOR_RESET();
  }
  *next=0;
  m_last=i;
}
//----

template<typename T>
template<bool is_forward>
void list<T>::detach(iterator_impl<is_forward> &it_)
{
  // detach item from the list
  if(!it_.m_item->prev)
    m_first=it_.m_item->next;
  else
    it_.m_item->prev->next=it_.m_item->next;
  if(!it_.m_item->next)
    m_last=it_.m_item->prev;
  else
    it_.m_item->next->prev=it_.m_item->prev;
  --m_size;
}
//----------------------------------------------------------------------------


//============================================================================
// list::const_iterator_impl
//============================================================================
template<typename T>
template<bool is_forward>
list<T>::const_iterator_impl<is_forward>::const_iterator_impl()
  :m_item(0)
{
}
//----

template<typename T>
template<bool is_forward>
list<T>::const_iterator_impl<is_forward>::const_iterator_impl(const iterator_impl<is_forward> &it_)
  :m_item(it_.m_item)
{
}
//----

template<typename T>
template<bool is_forward>
void list<T>::const_iterator_impl<is_forward>::reset()
{
  m_item=0;
}
//----------------------------------------------------------------------------

template<typename T>
template<bool is_forward>
bool list<T>::const_iterator_impl<is_forward>::operator==(const const_iterator_impl &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename T>
template<bool is_forward>
bool list<T>::const_iterator_impl<is_forward>::operator==(const iterator_impl<is_forward> &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename T>
template<bool is_forward>
bool list<T>::const_iterator_impl<is_forward>::operator!=(const const_iterator_impl &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename T>
template<bool is_forward>
bool list<T>::const_iterator_impl<is_forward>::operator!=(const iterator_impl<is_forward> &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename T>
template<bool is_forward>
typename list<T>::const_iterator_impl<is_forward> &list<T>::const_iterator_impl<is_forward>::operator++()
{
  PFC_ASSERT_PEDANTIC(m_item);
  m_item=is_forward?m_item->next:m_item->prev;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename list<T>::const_iterator_impl<is_forward> &list<T>::const_iterator_impl<is_forward>::operator--()
{
  PFC_ASSERT_PEDANTIC(m_item);
  m_item=is_forward?m_item->prev:m_item->next;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
const T &list<T>::const_iterator_impl<is_forward>::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item->data;
}
//----

template<typename T>
template<bool is_forward>
const T *list<T>::const_iterator_impl<is_forward>::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return &m_item->data;
}
//----------------------------------------------------------------------------

template<typename T>
template<bool is_forward>
list<T>::const_iterator_impl<is_forward>::const_iterator_impl(item *i_)
{
  m_item=i_;
}
//----------------------------------------------------------------------------


//============================================================================
// list::iterator_impl
//============================================================================
template<typename T>
template<bool is_forward>
list<T>::iterator_impl<is_forward>::iterator_impl()
  :m_list(0)
  ,m_item(0)
{
}
//----

template<typename T>
template<bool is_forward>
void list<T>::iterator_impl<is_forward>::reset()
{
  m_list=0;
  m_item=0;
}
//----------------------------------------------------------------------------

template<typename T>
template<bool is_forward>
bool list<T>::iterator_impl<is_forward>::operator==(const const_iterator_impl<is_forward> &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename T>
template<bool is_forward>
bool list<T>::iterator_impl<is_forward>::operator==(const iterator_impl &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename T>
template<bool is_forward>
bool list<T>::iterator_impl<is_forward>::operator!=(const const_iterator_impl<is_forward> &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename T>
template<bool is_forward>
bool list<T>::iterator_impl<is_forward>::operator!=(const iterator_impl &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename T>
template<bool is_forward>
typename list<T>::iterator_impl<is_forward> &list<T>::iterator_impl<is_forward>::operator++()
{
  PFC_ASSERT_PEDANTIC(m_item);
  m_item=is_forward?m_item->next:m_item->prev;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
typename list<T>::iterator_impl<is_forward> &list<T>::iterator_impl<is_forward>::operator--()
{
  PFC_ASSERT_PEDANTIC(m_item);
  m_item=is_forward?m_item->prev:m_item->next;
  return *this;
}
//----

template<typename T>
template<bool is_forward>
T &list<T>::iterator_impl<is_forward>::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item->data;
}
//----

template<typename T>
template<bool is_forward>
T *list<T>::iterator_impl<is_forward>::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return &m_item->data;
}
//----------------------------------------------------------------------------

template<typename T>
template<bool is_forward>
list<T>::iterator_impl<is_forward>::iterator_impl(list &l_, item *i_)
  :m_list(&l_)
  ,m_item(i_)
{
}
//----

template<typename T>
template<bool is_forward>
void list<T>::iterator_impl<is_forward>::rotate_sequence_left_impl(iterator_impl &first_, iterator_impl &last_)
{
  PFC_ASSERT_PEDANTIC_MSG(first_.m_item && last_.m_item && first_.m_list==last_.m_list,
                          ("Iterators must be valid and of the same list (first: %p, last: %p)\r\n", first_.m_item?first_.m_list:0, last_.m_item?last_.m_list:0));
  list<T> *l=first_.m_list;
  list<T>::item *fi=first_.m_item, *li=last_.m_item;
  if(fi==li)
    return;
  first_.m_item=fi->next;
  last_.m_item=fi;
  if(fi->prev)
    fi->prev->next=fi->next;
  else
    l->m_first=fi->next;
  if(li->next)
    li->next->prev=fi;
  else
    l->m_last=fi;
  fi->next->prev=fi->prev;
  fi->prev=li;
  fi->next=li->next;
  li->next=fi;
}
//----

template<typename T>
template<bool is_forward>
void list<T>::iterator_impl<is_forward>::rotate_sequence_right_impl(iterator_impl &first_, iterator_impl &last_)
{
  PFC_ASSERT_PEDANTIC_MSG(first_.m_item && last_.m_item && first_.m_list==last_.m_list,
                          ("Iterators must be valid and of the same list (first: %p, last: %p)\r\n", first_.m_item?first_.m_list:0, last_.m_item?last_.m_list:0));
  list<T> *l=first_.m_list;
  list<T>::item *fi=first_.m_item, *li=last_.m_item;
  if(fi==li)
    return;
  first_.m_item=li;
  last_.m_item=li->prev;
  if(li->next)
    li->next->prev=li->prev;
  else
    l->m_last=li->prev;
  if(fi->prev)
    fi->prev->next=li;
  else
    l->m_first=li;
  li->prev->next=li->next;
  li->next=fi;
  li->prev=fi->prev;
  fi->prev=li;
}
//----------------------------------------------------------------------------


//============================================================================
// set
//============================================================================
template<typename T, class CmpPred>
set<T, CmpPred>::set(const CmpPred &cmp_pred_, memory_allocator_base *alloc_)
  :m_cmp_pred(cmp_pred_)
  ,m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(set_traits<T, CmpPred>::block_alloc_size, set_traits<T, CmpPred>::block_alloc_align));
  m_size=0;
  m_root=0;
}
//----

template<typename T, class CmpPred>
set<T, CmpPred>::set(const set &s_)
  :m_cmp_pred(s_.m_cmp_pred)
  ,m_allocator(&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  cctor(s_);
}
//----

template<typename T, class CmpPred>
set<T, CmpPred>::set(const set &s_, memory_allocator_base *alloc_)
  :m_cmp_pred(s_.m_cmp_pred)
  ,m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(set_traits<T, CmpPred>::block_alloc_size, set_traits<T, CmpPred>::block_alloc_align));
  cctor(s_);
}
//----

template<typename T, class CmpPred>
set<T, CmpPred>::~set()
{
  clear();
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::operator=(const set &s_)
{
  set s(s_);
  swap(s);
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::set_allocator(memory_allocator_base *alloc_)
{
  PFC_ASSERT_MSG(!m_size, ("Unable to change the allocator of a non-empty set\r\n"));
  m_allocator=alloc_?alloc_:&default_memory_allocator::inst();
  PFC_ASSERT_CALL(m_allocator->check_allocator(set_traits<T, CmpPred>::block_alloc_size, set_traits<T, CmpPred>::block_alloc_align));
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::clear()
{
  // recursively destroy nodes
  if(m_root)
  {
    destroy_subtree(*m_root);
    m_root=0;
    m_size=0;
  }
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::swap(set &s_)
{
  // swap content of sets
  pfc::swap(m_cmp_pred, s_.m_cmp_pred);
  pfc::swap(m_allocator, s_.m_allocator);
  pfc::swap(m_size, s_.m_size);
  pfc::swap(m_root, s_.m_root);
}
//----------------------------------------------------------------------------

template<typename T, class CmpPred>
memory_allocator_base &set<T, CmpPred>::allocator() const
{
  return *m_allocator;
}
//----

template<typename T, class CmpPred>
usize_t set<T, CmpPred>::size() const
{
  return m_size;
}
//----

template<typename T, class CmpPred>
template<typename K>
typename set<T, CmpPred>::const_iterator set<T, CmpPred>::find(const K &k_) const
{
  // search from value from the set
  const node *n=m_root;
  while(n && !m_cmp_pred.equal(n->data, k_))
    n=n->children[m_cmp_pred.before(n->data, k_)];
  return const_iterator(n);
}
//----

template<typename T, class CmpPred>
template<typename K>
typename set<T, CmpPred>::iterator set<T, CmpPred>::find(const K &k_)
{
  // search from value from the set
  node *n=m_root;
  while(n && !m_cmp_pred.equal(n->data, k_))
    n=n->children[m_cmp_pred.before(n->data, k_)];
  return iterator(n);
}
//----

template<typename T, class CmpPred>
template<typename K>
typename set<T, CmpPred>::const_iterator set<T, CmpPred>::lower_bound(const K &k_) const
{
  // return iterator to the closest less-or-equal value in the set
  const node *n=m_root, *prev=0;
  while(n)
    if(m_cmp_pred.before(k_, n->data))
      n=n->children[0];
    else
    {
      prev=n;
      if(!m_cmp_pred.before(n->data, k_))
        break;
      n=n->children[1];
    }
  return const_iterator(prev);
}
//----

template<typename T, class CmpPred>
template<typename K>
typename set<T, CmpPred>::iterator set<T, CmpPred>::lower_bound(const K &k_)
{
  // return iterator to the closest less-or-equal value in the set
  node *n=m_root, *prev=0;
  while(n)
    if(m_cmp_pred.before(k_, n->data))
      n=n->children[0];
    else
    {
      prev=n;
      if(!m_cmp_pred.before(n->data, k_))
        break;
      n=n->children[1];
    }
  return iterator(prev);
}
//----

template<typename T, class CmpPred>
template<typename K>
typename set<T, CmpPred>::const_iterator set<T, CmpPred>::upper_bound(const K &k_) const
{
  // return iterator to the closest greater value in the set
  const node *n=m_root, *prev=0;
  while(n)
    if(!m_cmp_pred.before(k_, n->data))
      n=n->children[1];
    else
    {
      prev=n;
      n=n->children[0];
    }
  return const_iterator(prev);
}
//----

template<typename T, class CmpPred>
template<typename K>
typename set<T, CmpPred>::iterator set<T, CmpPred>::upper_bound(const K &k_)
{
  // return iterator to the closest greater value in the set
  node *n=m_root, *prev=0;
  while(n)
    if(!m_cmp_pred.before(k_, n->data))
      n=n->children[1];
    else
    {
      prev=n;
      n=n->children[0];
    }
  return iterator(prev);
}
//----

template<typename T, class CmpPred>
typename set<T, CmpPred>::const_iterator set<T, CmpPred>::begin() const
{
  // return iterator to the left-most node
  const node *n=m_root, *prev=0;
  while(n)
  {
    prev=n;
    n=n->children[0];
  }
  return const_iterator(prev);
}
//----

template<typename T, class CmpPred>
typename set<T, CmpPred>::iterator set<T, CmpPred>::begin()
{
  // return iterator to the left-most node
  node *n=m_root, *prev=0;
  while(n)
  {
    prev=n;
    n=n->children[0];
  }
  return iterator(prev);
}
//----

template<typename T, class CmpPred>
typename set<T, CmpPred>::const_iterator set<T, CmpPred>::end() const
{
  return const_iterator(0);
}
//----

template<typename T, class CmpPred>
typename set<T, CmpPred>::iterator set<T, CmpPred>::end()
{
  return iterator(0);
}
//----

template<typename T, class CmpPred>
template<typename K>
typename set<T, CmpPred>::inserter set<T, CmpPred>::insert(const K &k_, bool replace_)
{
  // search for the leaf node where to add the value
  node *n=m_root, *parent=0, **parent_childptr=&m_root;
  while(n && !m_cmp_pred.equal(n->data, k_))
  {
    if(m_cmp_pred.equal(n->data, k_))
    {
      inserter ins={iterator(*this, n), false};
      return ins;
    }
    parent=n;
    parent_childptr=&n->children[m_cmp_pred.before(n->data, k_)];
    n=*parent_childptr;
  }

  bool is_new=!n;
  if(is_new)
  {
    // add new node
    eh_data<node> p(*m_allocator, 1, set_traits<T, CmpPred>::block_alloc_align);
    n=p.data;
    PFC_PNEW(&n->data)T(k_);
    n->color=1;
    n->parent=parent;
    n->children[0]=0;
    n->children[1]=0;
    *parent_childptr=n;
    p.reset();
    ++m_size;
    restore_rb_property_after_insert(n);
  }
  else
    if(replace_)
    {
      // replace existing node data with new one
      n->data.~T();
      PFC_PNEW(&n->data)T(k_);
    }
  inserter ins={iterator(n), is_new};
  return ins;
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::erase(iterator &it_)
{
  PFC_ASSERT_PEDANTIC(it_.m_node);
  node *y=it_.m_node;
  if(y->children[0] && y->children[1])
  {
    // search the left-most child from the right sub-tree
    y=y->children[1];
    while(node *child=y->children[0])
      y=child;
  }

  // remove y from parent chain
  node *x=y->children[0]?y->children[0]:y->children[1];
  if(x)
    x->parent=y->parent;
  bool is_left_parent=false;
  if(y->parent)
  {
    is_left_parent=y==y->parent->children[0];
    y->parent->children[!is_left_parent]=x;
  }
  else
    m_root=x;

  // restore RB-property if removing black node
  if(!y->color)
    restore_rb_property_after_remove(x, y->parent, is_left_parent);
  if(y!=it_.m_node)
  {
    // replace m_node with y
    if((y->parent=it_.m_node->parent)!=0)
      y->parent->children[it_.m_node==y->parent->children[1]]=y;
    else
      m_root=y;
    y->color=it_.m_node->color;
    if((y->children[0]=it_.m_node->children[0])!=0)
      y->children[0]->parent=y;
    if((y->children[1]=it_.m_node->children[1])!=0)
      y->children[1]->parent=y;
  }

  // delete node
  it_.m_node->data.~T();
  m_allocator->free(it_.m_node);
  --m_size;
}
//----------------------------------------------------------------------------

template<typename T, class CmpPred>
void set<T, CmpPred>::cctor(const set &s_)
{
  // copy-construct the set
  m_size=s_.m_size;
  m_root=0;
  if(s_.m_root)
    copy_subtree(*s_.m_root, 0, m_root);
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::copy_subtree(node &n_, node *parent_, node *&child_ptr_)
{
  // recursively copy the sub-tree
  eh_data<node> p(*m_allocator, 1, set_traits<T, CmpPred>::block_alloc_align);
  node *n=p.data;
  PFC_PNEW(&n->data)T(n_.data);
  n->color=n_.color;
  n->parent=parent_;
  n->children[0]=0;
  n->children[1]=0;
  p.reset();
  child_ptr_=n;
  if(n_.children[0])
    copy_subtree(*n_.children[0], n, n->children[0]);
  if(n_.children[1])
    copy_subtree(*n_.children[1], n, n->children[1]);
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::destroy_subtree(node &n_)
{
  // destroy children
  if(n_.children[0])
    destroy_subtree(*n_.children[0]);
  if(n_.children[1])
    destroy_subtree(*n_.children[1]);
  n_.data.~T();
  m_allocator->free(&n_);
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::rotate_subtree(node &n_, bool rotate_right_)
{
  // rotate sub-tree left/right about the node
  unsigned idx0=rotate_right_, idx1=!rotate_right_;
  node *y=n_.children[idx1];
  if((n_.children[idx1]=y->children[idx0])!=0)
    y->children[idx0]->parent=&n_;
  node *parent=n_.parent;
  if((y->parent=parent)!=0)
    parent->children[&n_==parent->children[idx0]?idx0:idx1]=y;
  else
    m_root=y;
  y->children[idx0]=&n_;
  n_.parent=y;
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::restore_rb_property_after_insert(node *n_)
{
  // restore RB-tree property after node insertion
  while(n_!=m_root && n_->parent->color)
  {
    node *grandparent=n_->parent->parent;
    bool is_left_parent=n_->parent==grandparent->children[0];
    node *y=grandparent->children[is_left_parent];
    if(y && y->color)
    {
      // change colors
      n_->parent->color=0;
      y->color=0;
      grandparent->color=1;
      n_=grandparent;
    }
    else
    {
      if(n_==n_->parent->children[is_left_parent])
      {
        // move node up and rotate
        n_=n_->parent;
        rotate_subtree(*n_, !is_left_parent);
        grandparent=n_->parent->parent;
      }
      n_->parent->color=0;
      grandparent->color=1;
      rotate_subtree(*grandparent, is_left_parent);
    }
  }
  m_root->color=0;
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::validate_rb_state(node *n_, unsigned depth_, unsigned &max_depth_) const
{
  if(!n_)
    return;
  max_depth_=max(depth_, max_depth_);
  if(n_->color)
  {
    PFC_ASSERT(   (!n_->children[0] || !n_->children[0]->color)
               && (!n_->children[1] || !n_->children[1]->color));
  }
  validate_rb_state(n_->children[0], depth_+1, max_depth_);
  validate_rb_state(n_->children[1], depth_+1, max_depth_);
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::validate_rb_state() const
{
  unsigned max_depth=0;
  validate_rb_state(m_root, 1, max_depth);
  PFC_ASSERT(max_depth<=2.0f*std::log(m_size+1)*1.44269504089f);
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::restore_rb_property_after_remove(node *n_, node *parent_, bool is_left_child_)
{
  // restore RB-tree property after node removal
  while(n_!=m_root && (!n_ || !n_->color))
  {
    node *w=parent_->children[is_left_child_];
    if(w->color)
    {
      w->color=0;
      parent_->color=1;
      rotate_subtree(*parent_, !is_left_child_);
      w=parent_->children[is_left_child_];
    }
    bool is_child0_black=!w->children[is_left_child_] || !w->children[is_left_child_]->color;
    if(is_child0_black && (!w->children[!is_left_child_] || !w->children[!is_left_child_]->color))
    {
      w->color=1;
      n_=parent_;
      parent_=n_->parent;
      if(parent_)
        is_left_child_=n_==parent_->children[0];
    }
    else
    {
      if(is_child0_black)
      {
        w->children[!is_left_child_]->color=0;
        w->color=1;
        rotate_subtree(*w, is_left_child_);
        w=parent_->children[is_left_child_];
      }
      w->color=parent_->color;
      parent_->color=0;
      w->children[is_left_child_]->color=0;
      rotate_subtree(*parent_, !is_left_child_);
      n_=m_root;
    }
  }
  if(n_)
    n_->color=0;
}
//----------------------------------------------------------------------------


//============================================================================
// set::const_iterator
//============================================================================
template<typename T, class CmpPred>
set<T, CmpPred>::const_iterator::const_iterator()
  :m_node(0)
{
}
//----

template<typename T, class CmpPred>
set<T, CmpPred>::const_iterator::const_iterator(const iterator &it_)
  :m_node(it_.m_node)
{
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::const_iterator::reset()
{
  m_node=0;
}
//----------------------------------------------------------------------------

template<typename T, class CmpPred>
bool set<T, CmpPred>::const_iterator::operator==(const const_iterator &it_) const
{
  return m_node==it_.m_node;
}
//----

template<typename T, class CmpPred>
bool set<T, CmpPred>::const_iterator::operator==(const iterator &it_) const
{
  return m_node==it_.m_node;
}
//----

template<typename T, class CmpPred>
bool set<T, CmpPred>::const_iterator::operator!=(const const_iterator &it_) const
{
  return m_node!=it_.m_node;
}
//----

template<typename T, class CmpPred>
bool set<T, CmpPred>::const_iterator::operator!=(const iterator &it_) const
{
  return m_node!=it_.m_node;
}
//----

template<typename T, class CmpPred>
typename set<T, CmpPred>::const_iterator &set<T, CmpPred>::const_iterator::operator++()
{
  PFC_ASSERT_PEDANTIC(m_node);
  const node *n=m_node->children[1];
  if(n)
  {
    // find left-most node under right child
    do
    {
      m_node=n;
      n=n->children[0];
    } while(n);
  }
  else
  {
    // traverse right sub-tree up
    while(m_node->parent && m_node->parent->children[1]==m_node)
      m_node=m_node->parent;
    m_node=m_node->parent;
  }
  return *this;
}
//----

template<typename T, class CmpPred>
const T &set<T, CmpPred>::const_iterator::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_node);
  return m_node->data;
}
//----

template<typename T, class CmpPred>
const T *set<T, CmpPred>::const_iterator::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_node);
  return &m_node->data;
}
//----------------------------------------------------------------------------

template<typename T, class CmpPred>
set<T, CmpPred>::const_iterator::const_iterator(const node *n_)
  :m_node(n_)
{
}
//----------------------------------------------------------------------------


//============================================================================
// set::iterator
//============================================================================
template<typename T, class CmpPred>
set<T, CmpPred>::iterator::iterator()
  :m_node(0)
{
}
//----

template<typename T, class CmpPred>
void set<T, CmpPred>::iterator::reset()
{
  m_node=0;
}
//----------------------------------------------------------------------------

template<typename T, class CmpPred>
bool set<T, CmpPred>::iterator::operator==(const const_iterator &it_) const
{
  return m_node==it_.m_node;
}
//----

template<typename T, class CmpPred>
bool set<T, CmpPred>::iterator::operator==(const iterator &it_) const
{
  return m_node==it_.m_node;
}
//----

template<typename T, class CmpPred>
bool set<T, CmpPred>::iterator::operator!=(const const_iterator &it_) const
{
  return m_node!=it_.m_node;
}
//----

template<typename T, class CmpPred>
bool set<T, CmpPred>::iterator::operator!=(const iterator &it_) const
{
  return m_node!=it_.m_node;
}
//----

template<typename T, class CmpPred>
typename set<T, CmpPred>::iterator &set<T, CmpPred>::iterator::operator++()
{
  PFC_ASSERT_PEDANTIC(m_node);
  node *n=m_node->children[1];
  if(n)
  {
    // find left-most node under right child
    do
    {
      m_node=n;
      n=n->children[0];
    } while(n);
  }
  else
  {
    // traverse right sub-tree up
    while(m_node->parent && m_node->parent->children[1]==m_node)
      m_node=m_node->parent;
    m_node=m_node->parent;
  }
  return *this;
}
//----

template<typename T, class CmpPred>
const T &set<T, CmpPred>::iterator::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_node);
  return m_node->data;
}
//----

template<typename T, class CmpPred>
const T *set<T, CmpPred>::iterator::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_node);
  return &m_node->data;
}
//----------------------------------------------------------------------------

template<typename T, class CmpPred>
set<T, CmpPred>::iterator::iterator(node *n_)
  :m_node(n_)
{
}
//----------------------------------------------------------------------------


//============================================================================
// map
//============================================================================
template<typename K, typename T, class CmpPred>
map<K, T, CmpPred>::map(const CmpPred &cmp_pred_, memory_allocator_base *alloc_)
  :m_cmp_pred(cmp_pred_)
  ,m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // init empty map
  PFC_ASSERT_CALL(m_allocator->check_allocator(map_traits<K, T, CmpPred>::block_alloc_size, map_traits<K, T, CmpPred>::block_alloc_align));
  m_size=0;
  m_root=0;
}
//----

template<typename K, typename T, class CmpPred>
map<K, T, CmpPred>::map(const map &m_)
  :m_cmp_pred(m_.m_cmp_pred)
  ,m_allocator(&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  cctor(m_);
}
//----

template<typename K, typename T, class CmpPred>
map<K, T, CmpPred>::map(const map &m_, memory_allocator_base *alloc_)
  :m_cmp_pred(m_.m_cmp_pred)
  ,m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(map_traits<K, T, CmpPred>::block_alloc_size, map_traits<K, T, CmpPred>::block_alloc_align));
  cctor(m_);
}
//----

template<typename K, typename T, class CmpPred>
map<K, T, CmpPred>::~map()
{
  clear();
}
//----

template<typename K, typename T, class CmpPred>
void map<K, T, CmpPred>::operator=(const map &m_)
{
  map m(m_);
  swap(m);
}
//----

template<typename K, typename T, class CmpPred>
void map<K, T, CmpPred>::set_allocator(memory_allocator_base *alloc_)
{
  PFC_ASSERT_MSG(!m_size, ("Unable to change the allocator of a non-empty map\r\n"));
  m_allocator=alloc_?alloc_:&default_memory_allocator::inst();
  PFC_ASSERT_CALL(m_allocator->check_allocator(map_traits<K, T, CmpPred>::block_alloc_size, map_traits<K, T, CmpPred>::block_alloc_align));
}
//----

template<typename K, typename T, class CmpPred>
void map<K, T, CmpPred>::clear()
{
  // recursively destroy nodes
  if(m_root)
  {
    destroy_subtree(*m_root);
    m_root=0;
    m_size=0;
  }
}
//----

template<typename K, typename T, class CmpPred>
void map<K, T, CmpPred>::swap(map &m_)
{
  // swap content of maps
  pfc::swap(m_cmp_pred, s_.m_cmp_pred);
  pfc::swap(m_allocator, s_.m_allocator);
  pfc::swap(m_size, s_.m_size);
  pfc::swap(m_root, s_.m_root);
}
//----------------------------------------------------------------------------

template<typename K, typename T, class CmpPred>
memory_allocator_base &map<K, T, CmpPred>::allocator() const
{
  return *m_allocator;
}
//----

template<typename K, typename T, class CmpPred>
usize_t map<K, T, CmpPred>::size() const
{
  return m_size;
}
//----

template<typename K, typename T, class CmpPred>
template<typename K1>
const T &map<K, T, CmpPred>::operator[](const K1 &k_) const
{
  // search key from the map and return the associated value
  const node *n=m_root;
  while(n && !m_cmp_pred.equal(n->key, k_))
    n=n->children[m_cmp_pred.before(n->key, k_)];
  PFC_ASSERT_MSG(n, ("Key not found from the map\r\n"));
  return n->val;
}
//----

template<typename K, typename T, class CmpPred>
template<typename K1>
T &map<K, T, CmpPred>::operator[](const K1 &k_)
{
  // search key from the map and return the associated value
  node *n=m_root;
  while(n && !m_cmp_pred.equal(n->key, k_))
    n=n->children[m_cmp_pred.before(n->key, k_)];
  PFC_ASSERT_MSG(n, ("Key not found from the map\r\n"));
  return n->val;
}
//----

template<typename K, typename T, class CmpPred>
template<typename K1>
typename map<K, T, CmpPred>::const_iterator map<K, T, CmpPred>::find(const K1 &k_) const
{
  // search key from the map and return iteration that points to it
  const node *n=m_root;
  while(n && !m_cmp_pred.equal(n->key, k_))
    n=n->children[m_cmp_pred.before(n->key, k_)];
  return const_iterator(n);
}
//----

template<typename K, typename T, class CmpPred>
template<typename K1>
typename map<K, T, CmpPred>::iterator map<K, T, CmpPred>::find(const K1 &k_)
{
  // search key from the map and return iteration that points to it
  node *n=m_root;
  while(n && !m_cmp_pred.equal(n->key, k_))
    n=n->children[m_cmp_pred.before(n->key, k_)];
  return iterator(n);
}
//----

template<typename K, typename T, class CmpPred>
template<typename K1>
typename map<K, T, CmpPred>::const_iterator map<K, T, CmpPred>::lower_bound(const K1 &k_) const
{
  // return iterator to the closest less-or-equal value in the set
  const node *n=m_root, *prev=0;
  while(n)
    if(m_cmp_pred.before(k_, n->key))
      n=n->children[0];
    else
    {
      prev=n;
      if(!m_cmp_pred.before(n->key, k_))
        break;
      n=n->children[1];
    }
  return const_iterator(prev);
}
//----

template<typename K, typename T, class CmpPred>
template<typename K1>
typename map<K, T, CmpPred>::iterator map<K, T, CmpPred>::lower_bound(const K1 &k_)
{
  // return iterator to the closest less-or-equal value in the set
  node *n=m_root, *prev=0;
  while(n)
    if(m_cmp_pred.before(k_, n->key))
      n=n->children[0];
    else
    {
      prev=n;
      if(!m_cmp_pred.before(n->key, k_))
        break;
      n=n->children[1];
    }
  return iterator(prev);
}
//----

template<typename K, typename T, class CmpPred>
template<typename K1>
typename map<K, T, CmpPred>::const_iterator map<K, T, CmpPred>::upper_bound(const K1 &k_) const
{
  // return iterator to the closest greater value in the set
  const node *n=m_root, *prev=0;
  while(n)
    if(!m_cmp_pred.before(k_, n->key))
      n=n->children[1];
    else
    {
      prev=n;
      n=n->children[0];
    }
  return const_iterator(prev);
}
//----

template<typename K, typename T, class CmpPred>
template<typename K1>
typename map<K, T, CmpPred>::iterator map<K, T, CmpPred>::upper_bound(const K1 &k_)
{
  // return iterator to the closest greater value in the set
  node *n=m_root, *prev=0;
  while(n)
    if(!m_cmp_pred.before(k_, n->key))
      n=n->children[1];
    else
    {
      prev=n;
      n=n->children[0];
    }
  return iterator(prev);
}
//----

template<typename K, typename T, class CmpPred>
typename map<K, T, CmpPred>::const_iterator map<K, T, CmpPred>::begin() const
{
  // return iterator to the left-most node
  const node *n=m_root, *prev=0;
  while(n)
  {
    prev=n;
    n=n->children[0];
  }
  return const_iterator(prev);
}
//----

template<typename K, typename T, class CmpPred>
typename map<K, T, CmpPred>::iterator map<K, T, CmpPred>::begin()
{
  // return iterator to the left-most node
  node *n=m_root, *prev=0;
  while(n)
  {
    prev=n;
    n=n->children[0];
  }
  return iterator(prev);
}
//----

template<typename K, typename T, class CmpPred>
typename map<K, T, CmpPred>::const_iterator map<K, T, CmpPred>::end() const
{
  return const_iterator(0);
}
//----

template<typename K, typename T, class CmpPred>
typename map<K, T, CmpPred>::iterator map<K, T, CmpPred>::end()
{
  return iterator(0);
}
//----

template<typename K, typename T, class CmpPred>
typename map<K, T, CmpPred>::inserter map<K, T, CmpPred>::insert(const K &k_, const T &v_, bool replace_)
{
  // search for the leaf node where to add the data
  node *n=m_root, *parent=0, **parent_childptr=&m_root;
  while(n && !m_cmp_pred.equal(n->key, k_))
  {
    parent=n;
    parent_childptr=&n->children[m_cmp_pred.before(n->key, k_)];
    n=*parent_childptr;
  }

  bool is_new=!n;
  if(is_new)
  {
    // add new node
    eh_data<node> p(*m_allocator, 1, map_traits<K, T, CmpPred>::block_alloc_align);
    n=p.data;
    PFC_PNEW(&n->key)K(k_);
    PFC_PNEW(&n->val)T(v_);
    n->color=1;
    n->parent=parent;
    n->children[0]=0;
    n->children[1]=0;
    *parent_childptr=n;
    p.reset();
    ++m_size;
    restore_rb_property_after_insert(n);
  }
  else
    if(replace_)
    {
      // replace existing node data with new one
      n->val.~T();
      PFC_PNEW(&n->val)T(v_);
    }
  inserter ins={iterator(n), is_new};
  return ins;
}
//----

template<typename K, typename T, class CmpPred>
typename map<K, T, CmpPred>::inserter map<K, T, CmpPred>::insert(const K &k_, bool replace_)
{
  // search for the leaf node where to add the data
  node *n=m_root, *parent=0, **parent_childptr=&m_root;
  while(n && !m_cmp_pred.equal(n->key, k_))
  {
    parent=n;
    parent_childptr=&n->children[m_cmp_pred.before(n->key, k_)];
    n=*parent_childptr;
  }

  bool is_new=!n;
  if(is_new)
  {
    // add new node
    eh_data<node> p(*m_allocator, 1, map_traits<K, T, CmpPred>::block_alloc_align);
    n=p.data;
    PFC_PNEW(&n->key)K(k_);
    PFC_PNEW(&n->val)T;
    n->color=1;
    n->parent=parent;
    n->children[0]=0;
    n->children[1]=0;
    *parent_childptr=n;
    p.reset();
    ++m_size;
    restore_rb_property_after_insert(n);
  }
  else
    if(replace_)
    {
      // replace existing node value with new one
      n->val.~T();
      PFC_PNEW(&n->val)T(v_);
    }
  inserter ins={iterator(n), is_new};
  return ins;
}
//----

template<typename K, typename T, class CmpPred>
void map<K, T, CmpPred>::erase(iterator &it_)
{
  PFC_ASSERT_PEDANTIC(it_.m_node);
  node *y=it_.m_node;
  if(y->children[0] && y->children[1])
  {
    // search the left-most child from the right sub-tree
    y=y->children[1];
    while(node *child=y->children[0])
      y=child;
  }

  // remove y from parent chain
  node *x=y->children[0]?y->children[0]:y->children[1];
  if(x)
    x->parent=y->parent;
  bool is_left_parent=false;
  if(y->parent)
  {
    is_left_parent=y==y->parent->children[0];
    y->parent->children[!is_left_parent]=x;
  }
  else
    m_root=x;

  // restore RB-property if removing black node
  if(!y->color)
    restore_rb_property_after_remove(x, y->parent, is_left_parent);
  if(y!=it_.m_node)
  {
    // replace m_node with y
    if((y->parent=it_.m_node->parent)!=0)
      y->parent->children[it_.m_node==y->parent->children[1]]=y;
    else
      m_root=y;
    y->color=it_.m_node->color;
    if((y->children[0]=it_.m_node->children[0])!=0)
      y->children[0]->parent=y;
    if((y->children[1]=it_.m_node->children[1])!=0)
      y->children[1]->parent=y;
  }

  // delete node
  it_.m_node->val.~T();
  it_.m_node->key.~K();
  m_allocator->free(it_.m_node);
  --m_size;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class CmpPred>
void map<K, T, CmpPred>::cctor(const map &m_)
{
  // copy-construct the map
  m_size=m_.m_size;
  m_root=0;
  if(m_.m_root)
    copy_subtree(*m_.m_root, 0, m_root);
}
//----

template<typename K, typename T, class CmpPred>
void map<K, T, CmpPred>::copy_subtree(node &n_, node *parent_, node *&child_ptr_)
{
  // recursively copy the sub-tree
  eh_data<node> p(*m_allocator, 1, map_traits<K, T, CmpPred>::block_alloc_align);
  node *n=p.data;
  PFC_PNEW(&n->key)K(n_.key);
  PFC_PNEW(&n->val)T(n_.val);
  n->color=n_.color;
  n->parent=parent_;
  n->children[0]=0;
  n->children[1]=0;
  p.reset();
  child_ptr_=n;
  if(n_.children[0])
    copy_subtree(*n_.children[0], n, n->children[0]);
  if(n_.children[1])
    copy_subtree(*n_.children[1], n, n->children[1]);
}
//----

template<typename K, typename T, class CmpPred>
void map<K, T, CmpPred>::destroy_subtree(node &n_)
{
  // destroy children
  if(n_.children[0])
    destroy_subtree(*n_.children[0]);
  if(n_.children[1])
    destroy_subtree(*n_.children[1]);
  n_.val.~T();
  n_.key.~K();
  m_allocator->free(&n_);
}
//----

template<typename K, typename T, class CmpPred>
void map<K, T, CmpPred>::rotate_subtree(node &n_, bool rotate_right_)
{
  // rotate sub-tree left/right about the node
  unsigned idx0=rotate_right_, idx1=!rotate_right_;
  node *y=n_.children[idx1];
  if((n_.children[idx1]=y->children[idx0])!=0)
    y->children[idx0]->parent=&n_;
  node *parent=n_.parent;
  if((y->parent=parent)!=0)
    parent->children[&n_==parent->children[idx0]?idx0:idx1]=y;
  else
    m_root=y;
  y->children[idx0]=&n_;
  n_.parent=y;
}
//----

template<typename K, typename T, class CmpPred>
void map<K, T, CmpPred>::restore_rb_property_after_insert(node *n_)
{
  // restore RB-tree property after node insertion
  while(n_!=m_root && n_->parent->color)
  {
    node *grandparent=n_->parent->parent;
    bool is_left_parent=n_->parent==grandparent->children[0];
    node *y=grandparent->children[is_left_parent];
    if(y && y->color)
    {
      // change colors
      n_->parent->color=0;
      y->color=0;
      grandparent->color=1;
      n_=grandparent;
    }
    else
    {
      if(n_==n_->parent->children[is_left_parent])
      {
        // move node up and rotate
        n_=n_->parent;
        rotate_subtree(*n_, !is_left_parent);
        grandparent=n_->parent->parent;
      }
      n_->parent->color=0;
      grandparent->color=1;
      rotate_subtree(*grandparent, is_left_parent);
    }
  }
  m_root->color=0;
}
//----

template<typename K, typename T, class CmpPred>
void map<K, T, CmpPred>::restore_rb_property_after_remove(node *n_, node *parent_, bool is_left_child_)
{
  // restore RB-tree property after node removal
  while(n_!=m_root && (!n_ || !n_->color))
  {
    node *w=parent_->children[is_left_child_];
    if(w->color)
    {
      w->color=0;
      parent_->color=1;
      rotate_subtree(*parent_, !is_left_child_);
      w=parent_->children[is_left_child_];
    }
    bool is_child0_black=!w->children[is_left_child_] || !w->children[is_left_child_]->color;
    if(is_child0_black && (!w->children[!is_left_child_] || !w->children[!is_left_child_]->color))
    {
      w->color=1;
      n_=parent_;
      parent_=n_->parent;
      if(parent_)
        is_left_child_=n_==parent_->children[0];
    }
    else
    {
      if(is_child0_black)
      {
        w->children[!is_left_child_]->color=0;
        w->color=1;
        rotate_subtree(*w, is_left_child_);
        w=parent_->children[is_left_child_];
      }
      w->color=parent_->color;
      parent_->color=0;
      w->children[is_left_child_]->color=0;
      rotate_subtree(*parent_, !is_left_child_);
      n_=m_root;
    }
  }
  if(n_)
    n_->color=0;
}
//----------------------------------------------------------------------------


//============================================================================
// map::const_iterator
//============================================================================
template<typename K, typename T, class CmpPred>
map<K, T, CmpPred>::const_iterator::const_iterator()
  :m_node(0)
{
}
//----

template<typename K, typename T, class CmpPred>
map<K, T, CmpPred>::const_iterator::const_iterator(const iterator &it_)
  :m_node(it_.m_node)
{
}
//----

template<typename K, typename T, class CmpPred>
void map<K, T, CmpPred>::const_iterator::reset()
{
  m_node=0;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class CmpPred>
bool map<K, T, CmpPred>::const_iterator::operator==(const const_iterator &it_) const
{
  return m_node==it_.m_node;
}
//----

template<typename K, typename T, class CmpPred>
bool map<K, T, CmpPred>::const_iterator::operator==(const iterator &it_) const
{
  return m_node==it_.m_node;
}
//----

template<typename K, typename T, class CmpPred>
bool map<K, T, CmpPred>::const_iterator::operator!=(const const_iterator &it_) const
{
  return m_node!=it_.m_node;
}
//----

template<typename K, typename T, class CmpPred>
bool map<K, T, CmpPred>::const_iterator::operator!=(const iterator &it_) const
{
  return m_node!=it_.m_node;
}
//----

template<typename K, typename T, class CmpPred>
typename map<K, T, CmpPred>::const_iterator &map<K, T, CmpPred>::const_iterator::operator++()
{
  PFC_ASSERT_PEDANTIC(m_node);
  if(const node *n=m_node->children[1])
  {
    // find left-most node under right child
    while(n)
    {
      m_node=n;
      n=n->children[0];
    }
  }
  else
  {
    // traverse right sub-tree up
    while(m_node->parent && m_node->parent->children[1]==m_node)
      m_node=m_node->parent;
    m_node=m_node->parent;
  }
  return *this;
}
//----

template<typename K, typename T, class CmpPred>
const T &map<K, T, CmpPred>::const_iterator::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_node);
  return m_node->val;
}
//----

template<typename K, typename T, class CmpPred>
const T *map<K, T, CmpPred>::const_iterator::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_node);
  return &m_node->val;
}
//----

template<typename K, typename T, class CmpPred>
const K &map<K, T, CmpPred>::const_iterator::key() const
{
  PFC_ASSERT_PEDANTIC(m_node);
  return m_node->key;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class CmpPred>
map<K, T, CmpPred>::const_iterator::const_iterator(const node *n_)
  :m_node(n_)
{
}
//----------------------------------------------------------------------------


//============================================================================
// map::iterator
//============================================================================
template<typename K, typename T, class CmpPred>
map<K, T, CmpPred>::iterator::iterator()
  :m_node(0)
{
}
//----

template<typename K, typename T, class CmpPred>
void map<K, T, CmpPred>::iterator::reset()
{
  m_node=0;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class CmpPred>
bool map<K, T, CmpPred>::iterator::operator==(const const_iterator &it_) const
{
  return m_node==it_.m_node;
}
//----

template<typename K, typename T, class CmpPred>
bool map<K, T, CmpPred>::iterator::operator==(const iterator &it_) const
{
  return m_node==it_.m_node;
}
//----

template<typename K, typename T, class CmpPred>
bool map<K, T, CmpPred>::iterator::operator!=(const const_iterator &it_) const
{
  return m_node!=it_.m_node;
}
//----

template<typename K, typename T, class CmpPred>
bool map<K, T, CmpPred>::iterator::operator!=(const iterator &it_) const
{
  return m_node!=it_.m_node;
}
//----

template<typename K, typename T, class CmpPred>
typename map<K, T, CmpPred>::iterator &map<K, T, CmpPred>::iterator::operator++()
{
  PFC_ASSERT_PEDANTIC(m_node);
  if(node *n=m_node->children[1])
  {
    // find left-most node under right child
    while(n)
    {
      m_node=n;
      n=n->children[0];
    }
  }
  else
  {
    // traverse right sub-tree up
    while(m_node->parent && m_node->parent->children[1]==m_node)
      m_node=m_node->parent;
    m_node=m_node->parent;
  }
  return *this;
}
//----

template<typename K, typename T, class CmpPred>
T &map<K, T, CmpPred>::iterator::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_node);
  return m_node->val;
}
//----

template<typename K, typename T, class CmpPred>
T *map<K, T, CmpPred>::iterator::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_node);
  return &m_node->val;
}
//----

template<typename K, typename T, class CmpPred>
const K &map<K, T, CmpPred>::iterator::key() const
{
  PFC_ASSERT_PEDANTIC(m_node);
  return m_node->key;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class CmpPred>
map<K, T, CmpPred>::iterator::iterator(node *n_)
  :m_node(n_)
{
}
//----------------------------------------------------------------------------


//============================================================================
// hash_table_array
//============================================================================
template<typename T>
hash_table_array<T>::hash_table_array()
{
  m_index_mask=0;
}
//----

template<typename T>
usize_t hash_table_array<T>::size() const
{
  return m_table.size();
}
//----

template<typename T>
usize_t hash_table_array<T>::prev_size() const
{
  usize_t s=m_table.size();
  return s>256?s/2:256;
}
//----

template<typename T>
usize_t hash_table_array<T>::next_size() const
{
  usize_t s=m_table.size();
  return s?s*2:256;
}
//----

template<typename T>
usize_t hash_table_array<T>::min_load_limit() const
{
  return m_table.size()>256?usize_t(m_table.size()*0.25f):usize_t(-1);
}
//----

template<typename T>
usize_t hash_table_array<T>::max_load_limit() const
{
  return usize_t(m_table.size()*0.75f);
}
//----

template<typename T>
void hash_table_array<T>::resize(usize_t size_)
{
  PFC_ASSERT_PEDANTIC_MSG((size_&(size_-1))==0, ("The new size (%i) must be power-of-2\r\n", size_));
  m_table.resize(size_);
  m_index_mask=size_-1;
}
//----

template<typename T>
void hash_table_array<T>::clear()
{
  m_table.clear();
  m_index_mask=0;
}
//----

template<typename T>
void hash_table_array<T>::zero()
{
  mem_zero(m_table.data(), m_table.size()*sizeof(T));
}
//----

template<typename T>
const T &hash_table_array<T>::operator[](usize_t index_) const
{
  return m_table[index_&m_index_mask];
}
//----

template<typename T>
T &hash_table_array<T>::operator[](usize_t index_)
{
  return m_table[index_&m_index_mask];
}
//----

template<typename T>
typename hash_table_array<T>::const_iterator hash_table_array<T>::begin() const
{
  return m_table.begin();
}
//----

template<typename T>
typename hash_table_array<T>::iterator hash_table_array<T>::begin()
{
  return m_table.begin();
}
//----

template<typename T>
typename hash_table_array<T>::const_iterator hash_table_array<T>::end() const
{
  return m_table.end();
}
//----

template<typename T>
typename hash_table_array<T>::iterator hash_table_array<T>::end()
{
  return m_table.end();
}
//----

template<typename T>
typename hash_table_array<T>::const_iterator hash_table_array<T>::at(usize_t index_) const
{
  return m_table.begin()+(index_&m_index_mask);
}
//----

template<typename T>
typename hash_table_array<T>::iterator hash_table_array<T>::at(usize_t index_)
{
  return m_table.begin()+(index_&m_index_mask);
}
//----------------------------------------------------------------------------


//============================================================================
// hash_table_sarray
//============================================================================
template<typename T, usize_t capacity>
hash_table_sarray<T, capacity>::hash_table_sarray()
{
}
//----

template<typename T, usize_t capacity>
usize_t hash_table_sarray<T, capacity>::size() const
{
  return m_table.size();
}
//----

template<typename T, usize_t capacity>
usize_t hash_table_sarray<T, capacity>::prev_size() const
{
  return capacity;
}
//----

template<typename T, usize_t capacity>
usize_t hash_table_sarray<T, capacity>::next_size() const
{
  return capacity;
}
//----

template<typename T, usize_t capacity>
usize_t hash_table_sarray<T, capacity>::min_load_limit() const
{
  return usize_t(-1);
}
//----

template<typename T, usize_t capacity>
usize_t hash_table_sarray<T, capacity>::max_load_limit() const
{
  return usize_t(-1);
}
//----

template<typename T, usize_t capacity>
void hash_table_sarray<T, capacity>::resize(usize_t size_)
{
  PFC_ASSERT_PEDANTIC(size_==capacity);
  m_table.resize(size_);
}
//----

template<typename T, usize_t capacity>
void hash_table_sarray<T, capacity>::clear()
{
  m_table.clear();
}
//----

template<typename T, usize_t capacity>
void hash_table_sarray<T, capacity>::zero()
{
  mem_zero(m_table.data(), m_table.size()*sizeof(T));
}
//----

template<typename T, usize_t capacity>
const T &hash_table_sarray<T, capacity>::operator[](usize_t index_) const
{
  return m_table[index_%capacity];
}
//----

template<typename T, usize_t capacity>
T &hash_table_sarray<T, capacity>::operator[](usize_t index_)
{
  return m_table[index_%capacity];
}
//----

template<typename T, usize_t capacity>
typename hash_table_sarray<T, capacity>::const_iterator hash_table_sarray<T, capacity>::begin() const
{
  return m_table.begin();
}
//----

template<typename T, usize_t capacity>
typename hash_table_sarray<T, capacity>::iterator hash_table_sarray<T, capacity>::begin()
{
  return m_table.begin();
}
//----

template<typename T, usize_t capacity>
typename hash_table_sarray<T, capacity>::const_iterator hash_table_sarray<T, capacity>::end() const
{
  return m_table.end();
}
//----

template<typename T, usize_t capacity>
typename hash_table_sarray<T, capacity>::iterator hash_table_sarray<T, capacity>::end()
{
  return m_table.end();
}
//----

template<typename T, usize_t capacity>
typename hash_table_sarray<T, capacity>::const_iterator hash_table_sarray<T, capacity>::at(usize_t index_) const
{
  return m_table.begin()+(index_%capacity);
}
//----

template<typename T, usize_t capacity>
typename hash_table_sarray<T, capacity>::iterator hash_table_sarray<T, capacity>::at(usize_t index_)
{
  return m_table.begin()+(index_%capacity);
}
//----------------------------------------------------------------------------


//============================================================================
// hash_table_deque
//============================================================================
template<typename T>
hash_table_deque<T>::hash_table_deque()
{
  m_index_mask=0;
}
//----

template<typename T>
usize_t hash_table_deque<T>::size() const
{
  return m_table.size();
}
//----

template<typename T>
usize_t hash_table_deque<T>::prev_size() const
{
  usize_t s=m_table.size();
  return s>deque_traits<T>::ssize?s/2:deque_traits<T>::ssize;
}
//----

template<typename T>
usize_t hash_table_deque<T>::next_size() const
{
  usize_t s=m_table.size();
  return s?s*2:deque_traits<T>::ssize;
}
//----

template<typename T>
usize_t hash_table_deque<T>::min_load_limit() const
{
  return m_table.size()>deque_traits<T>::ssize?usize_t(m_table.size()*0.25f):usize_t(-1);
}
//----

template<typename T>
usize_t hash_table_deque<T>::max_load_limit() const
{
  return usize_t(m_table.size()*0.75f);
}
//----

template<typename T>
void hash_table_deque<T>::resize(usize_t size_)
{
  PFC_ASSERT_PEDANTIC_MSG((size_&(size_-1))==0, ("The new size (%i) must be power-of-2\r\n", size_));
  m_table.resize(size_);
  m_index_mask=size_-1;
}
//----

template<typename T>
void hash_table_deque<T>::clear()
{
  m_table.clear();
  m_index_mask=0;
}
//----

template<typename T>
void hash_table_deque<T>::zero()
{
  m_table.set(0, (T*)0, m_table.size());
}
//----

template<typename T>
const T &hash_table_deque<T>::operator[](usize_t index_) const
{
  return m_table[index_&m_index_mask];
}
//----

template<typename T>
T &hash_table_deque<T>::operator[](usize_t index_)
{
  return m_table[index_&m_index_mask];
}
//----

template<typename T>
typename hash_table_deque<T>::const_iterator hash_table_deque<T>::begin() const
{
  return m_table.begin();
}
//----

template<typename T>
typename hash_table_deque<T>::iterator hash_table_deque<T>::begin()
{
  return m_table.begin();
}
//----

template<typename T>
typename hash_table_deque<T>::const_iterator hash_table_deque<T>::end() const
{
  return m_table.end();
}
//----

template<typename T>
typename hash_table_deque<T>::iterator hash_table_deque<T>::end()
{
  return m_table.end();
}
//----

template<typename T>
typename hash_table_deque<T>::const_iterator hash_table_deque<T>::at(usize_t index_) const
{
  return m_table.begin()+(index_&m_index_mask);
}
//----

template<typename T>
typename hash_table_deque<T>::iterator hash_table_deque<T>::at(usize_t index_)
{
  return m_table.begin()+(index_&m_index_mask);
}
//----------------------------------------------------------------------------


//============================================================================
// hash_set
//============================================================================
template<typename T, class Config>
hash_set<T, Config>::hash_set(memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // init empty hash_set
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(hash_set_traits<T, Config>::block_alloc_size, hash_set_traits<T, Config>::block_alloc_align));
  m_size=0;
  m_rehash_size_min=0;
  m_rehash_size_max=0;
}
//----

template<typename T, class Config>
hash_set<T, Config>::hash_set(const hash_set &hs_)
  :m_allocator(&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  cctor(hs_);
}
//----

template<typename T, class Config>
hash_set<T, Config>::hash_set(const hash_set &hs_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(hash_set_traits<T, Config>::block_alloc_size, hash_set_traits<T, Config>::block_alloc_align));
  cctor(hs_);
}
//----

template<typename T, class Config>
hash_set<T, Config>::~hash_set()
{
  clear();
}
//----

template<typename T, class Config>
void hash_set<T, Config>::operator=(const hash_set &hs_)
{
  hash_set hs(hs_);
  swap(hs);
}
//----

template<typename T, class Config>
void hash_set<T, Config>::set_allocator(memory_allocator_base *alloc_)
{
  PFC_ASSERT_MSG(!m_size, ("Unable to change the allocator of a non-empty hash_set\r\n"));
  m_allocator=alloc_?alloc_:&default_memory_allocator::inst();
  PFC_ASSERT_CALL(m_allocator->check_allocator(hash_set_traits<T, Config>::block_alloc_size, hash_set_traits<T, Config>::block_alloc_align));
}
//----

template<typename T, class Config>
void hash_set<T, Config>::clear()
{
  // clear the content of the hash_set
  m_size=0;
  typename hash_table_t::iterator it=m_hash_table.begin(), it_end=m_hash_table.end();
  while(it!=it_end)
  {
    item *i=*it;
    while(i)
    {
      // destroy the hash_set item
      item *next=i->next;
      i->data.~T();
      m_allocator->free(i);
      i=next;
    }
    ++it;
  }
  m_hash_table.clear();
  m_rehash_size_min=0;
  m_rehash_size_max=0;
}
//----

template<typename T, class Config>
void hash_set<T, Config>::swap(hash_set &hs_)
{
  // swap content of hash_sets
  pfc::swap(m_allocator, hs_.m_allocator);
  pfc::swap(m_rehash_size_min, hs_.m_rehash_size_min);
  pfc::swap(m_rehash_size_max, hs_.m_rehash_size_max);
  pfc::swap(m_size, hs_.m_size);
  pfc::swap(m_hash_table, hs_.m_hash_table);
}
//----------------------------------------------------------------------------

template<typename T, class Config>
memory_allocator_base &hash_set<T, Config>::allocator() const
{
  return *m_allocator;
}
//----

template<typename T, class Config>
usize_t hash_set<T, Config>::size() const
{
  return m_size;
}
//----

template<typename T, class Config>
template<typename K>
typename hash_set<T, Config>::const_iterator hash_set<T, Config>::find(const K &k_) const
{
  // search key from the hash_set and return iteration that points to it
  const item *i=m_size?m_hash_table[hash_func_t::index(k_)]:0;
  while(i && i->data!=k_)
    i=i->next;
  return const_iterator(*this, i);
}
//----

template<typename T, class Config>
template<typename K>
typename hash_set<T, Config>::iterator hash_set<T, Config>::find(const K &k_)
{
  // search key from the hash_set and return iteration that points to it
  static item *s_null=0;
  item **prev=m_size?&m_hash_table[hash_func_t::index(k_)]:&s_null, *i=*prev;
  while(i && i->data!=k_)
    i=*(prev=&i->next);
  return iterator(*this, i, prev);
}
//----

template<typename T, class Config>
typename hash_set<T, Config>::const_iterator hash_set<T, Config>::begin() const
{
  // search first key from the hash_set
  typename hash_table_t::const_iterator it=m_hash_table.begin(), it_end=m_hash_table.end();
  while(it!=it_end)
  {
    if(const item *i=*it)
      return const_iterator(*this, i);
    ++it;
  }
  return const_iterator(*this, 0);
}
//----

template<typename T, class Config>
typename hash_set<T, Config>::iterator hash_set<T, Config>::begin()
{
  // search first key from the hash_set
  typename hash_table_t::iterator it=m_hash_table.begin(), it_end=m_hash_table.end();
  while(it!=it_end)
  {
    if(item *&i=*it)
      return iterator(*this, i, &i);
    ++it;
  }
  return iterator(*this, 0, 0);
}
//----

template<typename T, class Config>
typename hash_set<T, Config>::const_iterator hash_set<T, Config>::end() const
{
  return const_iterator(*this, 0);
}
//----

template<typename T, class Config>
typename hash_set<T, Config>::iterator hash_set<T, Config>::end()
{
  return iterator(*this, 0, 0);
}
//----

template<typename T, class Config>
void hash_set<T, Config>::collect_table_stats(hash_table_info &info_) const
{
  // reset info
  info_.num_slots=m_hash_table.size();
  info_.num_used_slots=0;
  info_.num_collisions=0;
  info_.max_slot_collisions=0;

  // collect hash table info
  typename hash_table_t::const_iterator it=m_hash_table.begin(), it_end=m_hash_table.end();
  while(it!=it_end)
  {
    if(item *i=*it)
    {
      usize_t num_slot_collisions=0;
      while(i->next)
      {
        ++num_slot_collisions;
        i=i->next;
      }
      ++info_.num_used_slots;
      info_.num_collisions+=num_slot_collisions;
      info_.max_slot_collisions=max(info_.max_slot_collisions, num_slot_collisions);
    }
    ++it;
  }
}
//----

template<typename T, class Config>
template<typename K>
typename hash_set<T, Config>::inserter hash_set<T, Config>::insert(const K &k_, bool replace_)
{
  // check for rehashing
  PFC_MEM_TRACK_STACK();
  if(m_size==m_rehash_size_max)
    rehash(true);

  // find item with matching the key
  item **prev=&m_hash_table[hash_func_t::index(k_)], *n=*prev;
  while(n && n->data!=k_)
    n=*(prev=&n->next);

  bool is_new=!n;
  if(is_new)
  {
    // add new item to the hash_set
    eh_data<item> p(*m_allocator, 1, hash_set_traits<T, Config>::block_alloc_align);
    n=p.data;
    PFC_PNEW(&n->data)T(k_);
    p.reset();
    *prev=n;
    n->next=0;
    ++m_size;
  }
  else
    if(replace_)
    {
      // replace existing node data with new one
      n->data.~T();
      PFC_PNEW(&n->data)T(k_);
    }
  inserter ins={iterator(*this, n, prev), is_new};
  return ins;
}
//----

template<typename T, class Config>
void hash_set<T, Config>::erase(iterator &it_)
{
  // remove item from the hash_set
  PFC_ASSERT_PEDANTIC(it_.m_item);
  item *next=it_.m_item->next;
  *it_.m_prev=next;
  if(!next)
  {
    // search for the next used stride
    typename hash_table_t::iterator it=m_hash_table.at(hash_func_t::index(it_.m_item->data)), it_end=m_hash_table.end();
    while(++it!=it_end)
      if((next=*it)!=0)
      {
        it_.m_prev=&*it;
        break;
      }
  }
  it_.m_item->data.~T();
  m_allocator->free(it_.m_item);
  it_.m_item=next;
  if(--m_size==m_rehash_size_min)
    rehash(false);
}
//----------------------------------------------------------------------------

template<typename T, class Config>
void hash_set<T, Config>::cctor(const hash_set &hs_)
{
  // copy-construct hash_set
  m_rehash_size_min=hs_.m_rehash_size_min;
  m_rehash_size_max=hs_.m_rehash_size_max;
  m_size=hs_.m_size;
  m_hash_table.resize(hs_.m_hash_table.size());
  typename hash_table_t::const_iterator it_src=hs_.m_hash_table.begin(), it_src_end=hs_.m_hash_table.end();
  typename hash_table_t::iterator it_dst=m_hash_table.begin();
  while(it_src!=it_src_end)
  {
    // copy a hash stride
    item *i=*it_src;
    item *&dst=*it_dst;
    while(i)
    {
      eh_data<item> p(*m_allocator, 1, hash_set_traits<T, Config>::block_alloc_align);
      PFC_PNEW(p.data)item(*i);
      p.data->next=dst;
      dst=p.data;
      p.reset();
      i=i->next;
    }
    ++it_src;
    ++it_dst;
  }
}
//----

template<typename T, class Config>
void hash_set<T, Config>::rehash(bool grow_)
{
  // setup tables for re-hashing
  hash_table_t ht(m_hash_table); /*todo: alloc from temp memory pool*/
  if(grow_)
  {
    m_hash_table.zero();
    m_hash_table.resize(m_hash_table.next_size());
  }
  else
  {
    m_hash_table.resize(m_hash_table.prev_size());
    m_hash_table.zero();
  }
  m_rehash_size_min=m_hash_table.min_load_limit();
  m_rehash_size_max=m_hash_table.max_load_limit();

  // re-hash items to the new table
  typename hash_table_t::const_iterator it=ht.begin(), it_end=ht.end();
  while(it!=it_end)
  {
    item *i=*it;
    while(i)
    {
      item *&h=m_hash_table[hash_func_t::index(i->data)];
      item *next=i->next;
      i->next=h;
      h=i;
      i=next;
    }
    ++it;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// hash_set::const_iterator
//============================================================================
template<typename T, class Config>
hash_set<T, Config>::const_iterator::const_iterator()
  :m_hset(0)
  ,m_item(0)
{
}
//----

template<typename T, class Config>
hash_set<T, Config>::const_iterator::const_iterator(const iterator &it_)
  :m_hset(it_.m_hset)
  ,m_item(it_.m_item)
{
}
//----

template<typename T, class Config>
void hash_set<T, Config>::const_iterator::reset()
{
  m_hset=0;
  m_item=0;
}
//----------------------------------------------------------------------------

template<typename T, class Config>
bool hash_set<T, Config>::const_iterator::operator==(const const_iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename T, class Config>
bool hash_set<T, Config>::const_iterator::operator==(const iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename T, class Config>
bool hash_set<T, Config>::const_iterator::operator!=(const const_iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename T, class Config>
bool hash_set<T, Config>::const_iterator::operator!=(const iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename T, class Config>
typename hash_set<T, Config>::const_iterator &hash_set<T, Config>::const_iterator::operator++()
{
  // advance the iterator
  PFC_ASSERT_PEDANTIC(m_item);
  if(!m_item->next)
    next_stride();
  else
    m_item=m_item->next;
  return *this;
}
//----

template<typename T, class Config>
const T &hash_set<T, Config>::const_iterator::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item->data;
}
//----

template<typename T, class Config>
const T *hash_set<T, Config>::const_iterator::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return &m_item->data;
}
//----------------------------------------------------------------------------

template<typename T, class Config>
hash_set<T, Config>::const_iterator::const_iterator(const hash_set &hs_, const item *i_)
  :m_hset(&hs_)
  ,m_item(i_)
{
}
//----

template<typename T, class Config>
void hash_set<T, Config>::const_iterator::next_stride()
{
  // search the next used stride
  typename hash_table_t::const_iterator it=m_hset->m_hash_table.at(hash_func_t::index(m_item->data)), it_end=m_hset->m_hash_table.end();
  m_item=0;
  while(++it!=it_end && (m_item=*it)==0);
}
//----------------------------------------------------------------------------


//============================================================================
// hash_set::iterator
//============================================================================
template<typename T, class Config>
hash_set<T, Config>::iterator::iterator()
  :m_hset(0)
  ,m_item(0)
{
}
//----

template<typename T, class Config>
void hash_set<T, Config>::iterator::reset()
{
  m_hset=0;
  m_item=0;
}
//----------------------------------------------------------------------------

template<typename T, class Config>
bool hash_set<T, Config>::iterator::operator==(const const_iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename T, class Config>
bool hash_set<T, Config>::iterator::operator==(const iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename T, class Config>
bool hash_set<T, Config>::iterator::operator!=(const const_iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename T, class Config>
bool hash_set<T, Config>::iterator::operator!=(const iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename T, class Config>
typename hash_set<T, Config>::iterator &hash_set<T, Config>::iterator::operator++()
{
  // advance the iterator
  PFC_ASSERT_PEDANTIC(m_item);
  if(!m_item->next)
    next_stride();
  else
    m_item=*(m_prev=&m_item->next);
  return *this;
}
//----

template<typename T, class Config>
const T &hash_set<T, Config>::iterator::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item->data;
}
//----

template<typename T, class Config>
const T *hash_set<T, Config>::iterator::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return &m_item->data;
}
//----------------------------------------------------------------------------

template<typename T, class Config>
hash_set<T, Config>::iterator::iterator(hash_set &hs_, item *i_, item **prev_)
  :m_hset(&hs_)
  ,m_item(i_)
  ,m_prev(prev_)
{
}
//----

template<typename T, class Config>
void hash_set<T, Config>::iterator::next_stride()
{
  // search the next used stride
  typename hash_table_t::iterator it=m_hset->m_hash_table.at(hash_func_t::index(m_item->data)), it_end=m_hset->m_hash_table.end();
  m_item=0;
  while(++it!=it_end)
    if((m_item=*it)!=0)
    {
      m_prev=&*it;
      break;
    }
}
//----------------------------------------------------------------------------


//============================================================================
// hash_map
//============================================================================
template<typename K, typename T, class Config>
hash_map<K, T, Config>::hash_map(memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // init empty hash_map
  PFC_ASSERT_CALL(m_allocator->check_allocator(hash_map_traits<K, T, Config>::block_alloc_size, hash_map_traits<K, T, Config>::block_alloc_align));
  m_size=0;
  m_rehash_size_min=0;
  m_rehash_size_max=0;
}
//----

template<typename K, typename T, class Config>
hash_map<K, T, Config>::hash_map(const hash_map &hm_)
  :m_allocator(&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  cctor(hm_);
}
//----

template<typename K, typename T, class Config>
hash_map<K, T, Config>::hash_map(const hash_map &hm_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(hash_map_traits<K, T, Config>::block_alloc_size, hash_map_traits<K, T, Config>::block_alloc_align));
  cctor(hm_);
}
//----

template<typename K, typename T, class Config>
hash_map<K, T, Config>::~hash_map()
{
  clear();
}
//----

template<typename K, typename T, class Config>
void hash_map<K, T, Config>::operator=(const hash_map &hm_)
{
  hash_map hm(hm_);
  swap(hm);
}
//----

template<typename K, typename T, class Config>
void hash_map<K, T, Config>::set_allocator(memory_allocator_base *alloc_)
{
  PFC_ASSERT_MSG(!m_size, ("Unable to change the allocator of a non-empty hash_map\r\n"));
  m_allocator=alloc_?alloc_:&default_memory_allocator::inst();
  PFC_ASSERT_CALL(m_allocator->check_allocator(hash_map_traits<K, T, Config>::block_alloc_size, hash_map_traits<K, T, Config>::block_alloc_align));
}
//----

template<typename K, typename T, class Config>
void hash_map<K, T, Config>::clear()
{
  // clear the content of the hash_map
  m_size=0;
  typename hash_table_t::iterator it=m_hash_table.begin(), it_end=m_hash_table.end();
  while(it!=it_end)
  {
    item *i=*it;
    while(i)
    {
      // destroy the hash_map item
      item *next=i->next;
      i->~item();
      m_allocator->free(i);
      i=next;
    }
    ++it;
  }
  m_hash_table.clear();
  m_rehash_size_min=0;
  m_rehash_size_max=0;
}
//----

template<typename K, typename T, class Config>
void hash_map<K, T, Config>::swap(hash_map &hm_)
{
  // swap content of hash_maps
  pfc::swap(m_allocator, hm_.m_allocator);
  pfc::swap(m_rehash_size_min, hm_.m_rehash_size_min);
  pfc::swap(m_rehash_size_max, hm_.m_rehash_size_max);
  pfc::swap(m_size, hm_.m_size);
  pfc::swap(m_hash_table, hm_.m_hash_table);
}
//----------------------------------------------------------------------------

template<typename K, typename T, class Config>
memory_allocator_base &hash_map<K, T, Config>::allocator() const
{
  return *m_allocator;
}
//----

template<typename K, typename T, class Config>
usize_t hash_map<K, T, Config>::size() const
{
  return m_size;
}
//----

template<typename K, typename T, class Config>
const T &hash_map<K, T, Config>::operator[](const K &k_) const
{
  // search key from the hash_map and return the associated value
  item *i=m_hash_table[hash_func_t::index(k_)];
  while(i && i->key!=k_)
    i=i->next;
  PFC_ASSERT_MSG(i, ("Key not found from the hash_map\r\n"));
  return i->val;
}
//----

template<typename K, typename T, class Config>
T &hash_map<K, T, Config>::operator[](const K &k_)
{
  // search key from the hash_map and return the associated value
  item *i=m_hash_table[hash_func_t::index(k_)];
  while(i && i->key!=k_)
    i=i->next;
  PFC_ASSERT_MSG(i, ("Key not found from the hash_map\r\n"));
  return i->val;
}
//----

template<typename K, typename T, class Config>
typename hash_map<K, T, Config>::const_iterator hash_map<K, T, Config>::find(const K &k_) const
{
  // search key from the hash_map and return iteration that points to it
  const item *i=m_size?m_hash_table[hash_func_t::index(k_)]:0;
  while(i && i->key!=k_)
    i=i->next;
  return const_iterator(*this, i);
}
//----

template<typename K, typename T, class Config>
typename hash_map<K, T, Config>::iterator hash_map<K, T, Config>::find(const K &k_)
{
  // search key from the hash_map and return iteration that points to it
  static item *s_null=0;
  item **prev=m_size?&m_hash_table[hash_func_t::index(k_)]:&s_null, *i=*prev;
  while(i && i->key!=k_)
    i=*(prev=&i->next);
  return iterator(*this, i, prev);
}
//----

template<typename K, typename T, class Config>
typename hash_map<K, T, Config>::const_iterator hash_map<K, T, Config>::begin() const
{
  // search first key from the hash_map
  typename hash_table_t::const_iterator it=m_hash_table.begin(), it_end=m_hash_table.end();
  while(it!=it_end)
  {
    if(const item *i=*it)
      return const_iterator(*this, i);
    ++it;
  }
  return const_iterator(*this, 0);
}
//----

template<typename K, typename T, class Config>
typename hash_map<K, T, Config>::iterator hash_map<K, T, Config>::begin()
{
  // search first key from the hash_map
  typename hash_table_t::iterator it=m_hash_table.begin(), it_end=m_hash_table.end();
  while(it!=it_end)
  {
    if(item *&i=*it)
      return iterator(*this, i, &i);
    ++it;
  }
  return iterator(*this, 0, 0);
}
//----

template<typename K, typename T, class Config>
typename hash_map<K, T, Config>::const_iterator hash_map<K, T, Config>::end() const
{
  return const_iterator(*this, 0);
}
//----

template<typename K, typename T, class Config>
typename hash_map<K, T, Config>::iterator hash_map<K, T, Config>::end()
{
  return iterator(*this, 0, 0);
}
//----

template<typename K, typename T, class Config>
void hash_map<K, T, Config>::collect_table_stats(hash_table_info &info_) const
{
  // reset info
  info_.num_slots=m_hash_table.size();
  info_.num_used_slots=0;
  info_.num_collisions=0;
  info_.max_slot_collisions=0;

  // collect hash table info
  typename hash_table_t::const_iterator it=m_hash_table.begin(), it_end=m_hash_table.end();
  while(it!=it_end)
  {
    if(item *i=*it)
    {
      usize_t num_slot_collisions=0;
      while(i->next)
      {
        ++num_slot_collisions;
        i=i->next;
      }
      ++info_.num_used_slots;
      info_.num_collisions+=num_slot_collisions;
      info_.max_slot_collisions=max(info_.max_slot_collisions, num_slot_collisions);
    }
    ++it;
  }
}
//----

template<typename K, typename T, class Config>
typename hash_map<K, T, Config>::inserter hash_map<K, T, Config>::insert(const K &k_, const T &v_, bool replace_)
{
  // check for rehashing
  PFC_MEM_TRACK_STACK();
  if(m_size==m_rehash_size_max)
    rehash(true);

  // find item with matching the key
  item **prev=&m_hash_table[hash_func_t::index(k_)], *n=*prev;
  while(n && n->key!=k_)
    n=*(prev=&n->next);

  bool is_new=!n;
  if(is_new)
  {
    // add new item to the hash_map
    eh_data<item> p(*m_allocator, 1, hash_map_traits<K, T, Config>::block_alloc_align);
    n=p.data;
    PFC_PNEW(&n->key)K(k_);
    PFC_PNEW(&n->val)T(v_);
    p.reset();
    *prev=n;
    n->next=0;
    ++m_size;
  }
  else
    if(replace_)
    {
      // replace existing item with new one
      n->val.~T();
      PFC_PNEW(&n->val)T(v_);
    }

  // return iterator to the added item
  inserter ins={iterator(*this, n, prev), is_new};
  return ins;
}
//----

template<typename K, typename T, class Config>
typename hash_map<K, T, Config>::inserter hash_map<K, T, Config>::insert(const K &k_, bool replace_)
{
  // check for rehashing
  PFC_MEM_TRACK_STACK();
  if(m_size==m_rehash_size_max)
    rehash(true);

  // find item with matching the key
  item **prev=&m_hash_table[hash_func_t::index(k_)], *i=*prev;
  while(i && i->key!=k_)
    i=*(prev=&i->next);

  bool is_new=!i;
  if(is_new)
  {
    // add new item to the hash_map
    eh_data<item> p(*m_allocator, 1, hash_map_traits<K, T, Config>::block_alloc_align);
    i=p.data;
    PFC_PNEW(&i->key)K(k_);
    PFC_PNEW(&i->val)T;
    p.reset();
    *prev=i;
    i->next=0;
    ++m_size;
  }
  else
    if(replace_)
    {
      // replace existing item with new one
      i->val.~T();
      PFC_PNEW(&i->val)T;
    }

  // return iterator to the added item
  inserter ins={iterator(*this, i, prev), is_new};
  return ins;
}
//----

template<typename K, typename T, class Config>
void hash_map<K, T, Config>::erase(iterator &it_)
{
  // remove item from the hash_map
  PFC_ASSERT_PEDANTIC(it_.m_item);
  item *next=it_.m_item->next;
  *it_.m_prev=next;
  if(!next)
  {
    // search for the next used stride
    typename hash_table_t::iterator it=m_hash_table.at(hash_func_t::index(it_.m_item->key)), it_end=m_hash_table.end();
    while(++it!=it_end)
      if((next=*it)!=0)
      {
        it_.m_prev=&*it;
        break;
      }
  }
  it_.m_item->val.~T();
  it_.m_item->key.~K();
  m_allocator->free(it_.m_item);
  it_.m_item=next;
  --m_size;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class Config>
void hash_map<K, T, Config>::cctor(const hash_map &hm_)
{
  // copy-construct hash_map
  m_rehash_size_min=hm_.m_rehash_size_min;
  m_rehash_size_max=hm_.m_rehash_size_max;
  m_size=hm_.m_size;
  m_hash_table.resize(hm_.m_hash_table.size());
  typename hash_table_t::const_iterator it_src=hm_.m_hash_table.begin(), it_src_end=hm_.m_hash_table.end();
  typename hash_table_t::iterator it_dst=m_hash_table.begin();
  while(it_src!=it_src_end)
  {
    // copy a hash stride
    item *i=*it_src;
    item *&dst=*it_dst;
    while(i)
    {
      eh_data<item> p(*m_allocator, 1, hash_map_traits<K, T, Config>::block_alloc_align);
      PFC_PNEW(p.data)item(*i);
      p.data->next=dst;
      dst=p.data;
      p.reset();
      i=i->next;
    }
    ++it_src;
    ++it_dst;
  }
}
//----

template<typename K, typename T, class Config>
void hash_map<K, T, Config>::rehash(bool grow_)
{
  // setup tables for re-hashing
  hash_table_t ht(m_hash_table); /*todo: alloc from temp memory pool*/
  if(grow_)
  {
    m_hash_table.zero();
    m_hash_table.resize(m_hash_table.next_size());
  }
  else
  {
    m_hash_table.resize(m_hash_table.prev_size());
    m_hash_table.zero();
  }
  m_rehash_size_min=m_hash_table.min_load_limit();
  m_rehash_size_max=m_hash_table.max_load_limit();

  // re-hash items to the new table
  typename hash_table_t::const_iterator it=ht.begin(), it_end=ht.end();
  while(it!=it_end)
  {
    item *i=*it;
    while(i)
    {
      item *&h=m_hash_table[hash_func_t::index(i->key)];
      item *next=i->next;
      i->next=h;
      h=i;
      i=next;
    }
    ++it;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// hash_map::const_iterator
//============================================================================
template<typename K, typename T, class Config>
hash_map<K, T, Config>::const_iterator::const_iterator()
  :m_hmap(0)
  ,m_item(0)
{
}
//----

template<typename K, typename T, class Config>
hash_map<K, T, Config>::const_iterator::const_iterator(const iterator &it_)
  :m_hmap(it_.m_hmap)
  ,m_item(it_.m_item)
{
}

template<typename K, typename T, class Config>
void hash_map<K, T, Config>::const_iterator::reset()
{
  m_hmap=0;
  m_item=0;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class Config>
bool hash_map<K, T, Config>::const_iterator::operator==(const const_iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename K, typename T, class Config>
bool hash_map<K, T, Config>::const_iterator::operator==(const iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename K, typename T, class Config>
bool hash_map<K, T, Config>::const_iterator::operator!=(const const_iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename K, typename T, class Config>
bool hash_map<K, T, Config>::const_iterator::operator!=(const iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename K, typename T, class Config>
typename hash_map<K, T, Config>::const_iterator &hash_map<K, T, Config>::const_iterator::operator++()
{
  // advance the iterator
  PFC_ASSERT_PEDANTIC(m_item);
  if(!m_item->next)
    next_stride();
  else
    m_item=m_item->next;
  return *this;
}
//----

template<typename K, typename T, class Config>
const T &hash_map<K, T, Config>::const_iterator::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item->val;
}
//----

template<typename K, typename T, class Config>
const T *hash_map<K, T, Config>::const_iterator::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return &m_item->val;
}
//----

template<typename K, typename T, class Config>
const K &hash_map<K, T, Config>::const_iterator::key() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item->key;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class Config>
hash_map<K, T, Config>::const_iterator::const_iterator(const hash_map &hm_, const item *i_)
  :m_hmap(&hm_)
  ,m_item(i_)
{
}
//----

template<typename K, typename T, class Config>
void hash_map<K, T, Config>::const_iterator::next_stride()
{
  // search the next used stride
  typename hash_table_t::const_iterator it=m_hmap->m_hash_table.at(hash_func_t::index(m_item->key)), it_end=m_hmap->m_hash_table.end();
  m_item=0;
  while(++it!=it_end && (m_item=*it)==0);
}
//----------------------------------------------------------------------------


//============================================================================
// hash_map::iterator
//============================================================================
template<typename K, typename T, class Config>
hash_map<K, T, Config>::iterator::iterator()
  :m_hmap(0)
  ,m_item(0)
{
}
//----

template<typename K, typename T, class Config>
void hash_map<K, T, Config>::iterator::reset()
{
  m_hmap=0;
  m_item=0;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class Config>
bool hash_map<K, T, Config>::iterator::operator==(const const_iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename K, typename T, class Config>
bool hash_map<K, T, Config>::iterator::operator==(const iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename K, typename T, class Config>
bool hash_map<K, T, Config>::iterator::operator!=(const const_iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename K, typename T, class Config>
bool hash_map<K, T, Config>::iterator::operator!=(const iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename K, typename T, class Config>
typename hash_map<K, T, Config>::iterator &hash_map<K, T, Config>::iterator::operator++()
{
  // advance the iterator
  PFC_ASSERT_PEDANTIC(m_item);
  if(!m_item->next)
    next_stride();
  else
    m_item=*(m_prev=&m_item->next);
  return *this;
}
//----

template<typename K, typename T, class Config>
T &hash_map<K, T, Config>::iterator::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item->val;
}
//----

template<typename K, typename T, class Config>
T *hash_map<K, T, Config>::iterator::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return &m_item->val;
}
//----

template<typename K, typename T, class Config>
const K &hash_map<K, T, Config>::iterator::key() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item->key;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class Config>
hash_map<K, T, Config>::iterator::iterator(hash_map &hm_, item *i_, item **prev_)
  :m_hmap(&hm_)
  ,m_item(i_)
  ,m_prev(prev_)
{
}
//----

template<typename K, typename T, class Config>
void hash_map<K, T, Config>::iterator::next_stride()
{
  // search the next used stride
  typename hash_table_t::iterator it=m_hmap->m_hash_table.at(hash_func_t::index(m_item->key)), it_end=m_hmap->m_hash_table.end();
  m_item=0;
  while(++it!=it_end)
    if((m_item=*it)!=0)
    {
      m_prev=&*it;
      break;
    }
}
//----------------------------------------------------------------------------


//============================================================================
// hash_bimap
//============================================================================
template<typename K, typename T, class KConfig, class VConfig>
hash_bimap<K, T, KConfig, VConfig>::hash_bimap(memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(hash_bimap_traits<K, T, KConfig, VConfig>::block_alloc_size, hash_bimap_traits<K, T, KConfig, VConfig>::block_alloc_align));
  m_size=0;
  m_rehash_ksize_min=0;
  m_rehash_ksize_max=0;
  m_rehash_vsize_min=0;
  m_rehash_vsize_max=0;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
hash_bimap<K, T, KConfig, VConfig>::hash_bimap(const hash_bimap &hm_)
  :m_allocator(&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  cctor(hm_);
}
//----

template<typename K, typename T, class KConfig, class VConfig>
hash_bimap<K, T, KConfig, VConfig>::hash_bimap(const hash_bimap &hm_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  PFC_MEM_TRACK_STACK();
  PFC_ASSERT_CALL(m_allocator->check_allocator(hash_bimap_traits<K, T, KConfig, VConfig>::block_alloc_size, hash_bimap_traits<K, T, KConfig, VConfig>::block_alloc_align));
  cctor(hm_);
}
//----

template<typename K, typename T, class KConfig, class VConfig>
hash_bimap<K, T, KConfig, VConfig>::~hash_bimap()
{
  clear();
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::operator=(const hash_bimap &hm_)
{
  hash_bimap hm(hm_);
  swap(hm);
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::set_allocator(memory_allocator_base *alloc_)
{
  PFC_ASSERT_MSG(!m_size, ("Unable to change the allocator of a non-empty hash_bimap\r\n"));
  m_allocator=alloc_?alloc_:&default_memory_allocator::inst();
  PFC_ASSERT_CALL(m_allocator->check_allocator(hash_bimap_traits<K, T, KConfig, VConfig>::block_alloc_size, hash_bimap_traits<K, T, KConfig, VConfig>::block_alloc_align));
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::clear()
{
  // clear the content of the hash_bimap
  m_size=0;
  typename hash_ktable_t::iterator it=m_hash_ktable.begin(), it_end=m_hash_ktable.end();
  while(it!=it_end)
  {
    item *i=*it;
    while(i)
    {
      // destroy the hash_bimap item
      item *next=i->next;
      i->~item();
      m_allocator->free(i);
      i=next;
    }
    ++it;
  }
  m_hash_ktable.clear();
  m_hash_vtable.clear();
  m_rehash_ksize_min=0;
  m_rehash_ksize_max=0;
  m_rehash_vsize_min=0;
  m_rehash_vsize_max=0;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::swap(hash_bimap &hm_)
{
  pfc::swap(m_allocator, hm_.m_allocator);
  pfc::swap(m_rehash_ksize_min, hm_.m_rehash_ksize_min);
  pfc::swap(m_rehash_ksize_max, hm_.m_rehash_ksize_max);
  pfc::swap(m_rehash_vsize_min, hm_.m_rehash_vsize_min);
  pfc::swap(m_rehash_vsize_max, hm_.m_rehash_vsize_max);
  pfc::swap(m_size, hm_.m_size);
  pfc::swap(m_hash_ktable, hm_.m_hash_ktable);
  pfc::swap(m_hash_vtable, hm_.m_hash_vtable);
}
//----------------------------------------------------------------------------

template<typename K, typename T, class KConfig, class VConfig>
memory_allocator_base &hash_bimap<K, T, KConfig, VConfig>::allocator() const
{
  return *m_allocator;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
usize_t hash_bimap<K, T, KConfig, VConfig>::size() const
{
  return m_size;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
const T &hash_bimap<K, T, KConfig, VConfig>::operator[](const K &k_) const
{
  // search key from the hash_bimap and return the associated value
  item *i=m_hash_ktable[hash_kfunc_t::index(k_)];
  while(i && i->key!=k_)
    i=i->next;
  PFC_ASSERT_MSG(i, ("Key not found from the hash_bimap\r\n"));
  return i->val;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
T &hash_bimap<K, T, KConfig, VConfig>::operator[](const K &k_)
{
  // search key from the hash_bimap and return the associated value
  item *i=m_hash_ktable[hash_kfunc_t::index(k_)];
  while(i && i->key!=k_)
    i=i->next;
  PFC_ASSERT_MSG(i, ("Key not found from the hash_bimap\r\n"));
  return i->val;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
typename hash_bimap<K, T, KConfig, VConfig>::const_iterator hash_bimap<K, T, KConfig, VConfig>::find(const K &k_) const
{
  // search key from the hash_bimap and return iteration that points to it
  const item *i=m_size?m_hash_ktable[hash_kfunc_t::index(k_)]:0;
  while(i && i->key!=k_)
    i=i->next;
  return const_iterator(*this, i);
}
//----

template<typename K, typename T, class KConfig, class VConfig>
typename hash_bimap<K, T, KConfig, VConfig>::iterator hash_bimap<K, T, KConfig, VConfig>::find(const K &k_)
{
  // search key from the hash_bimap and return iteration that points to it
  static item *s_null=0;
  item **prev=m_size?&m_hash_ktable[hash_kfunc_t::index(k_)]:&s_null, *i=*prev;
  while(i && i->key!=k_)
    i=*(prev=&i->next);
  return iterator(*this, i, prev, 0);
}
//----

template<typename K, typename T, class KConfig, class VConfig>
typename hash_bimap<K, T, KConfig, VConfig>::const_iterator hash_bimap<K, T, KConfig, VConfig>::find_val(const T &v_) const
{
  // search value from the hash_bimap and return iteration that points to it
  const item *i=m_size?m_hash_vtable[hash_vfunc_t::index(v_)]:0;
  while(i && i->val!=v_)
    i=i->next_val;
  return const_iterator(*this, i);
}
//----

template<typename K, typename T, class KConfig, class VConfig>
typename hash_bimap<K, T, KConfig, VConfig>::iterator hash_bimap<K, T, KConfig, VConfig>::find_val(const T &v_)
{
  // search value from the hash_bimap and return iteration that points to it
  static item *s_null=0;
  item **prev=m_size?&m_hash_vtable[hash_vfunc_t::index(v_)]:&s_null, *i=*prev;
  while(i && i->val!=v_)
    i=*(prev=&i->next_val);
  return iterator(*this, i, 0, prev);
}
//----

template<typename K, typename T, class KConfig, class VConfig>
typename hash_bimap<K, T, KConfig, VConfig>::const_iterator hash_bimap<K, T, KConfig, VConfig>::begin() const
{
  // search first key from the hash_bimap
  typename hash_ktable_t::const_iterator it=m_hash_ktable.begin(), it_end=m_hash_ktable.end();
  while(it!=it_end)
  {
    if(const item *i=*it)
      return const_iterator(*this, i);
    ++it;
  }
  return const_iterator(*this, 0);
}
//----

template<typename K, typename T, class KConfig, class VConfig>
typename hash_bimap<K, T, KConfig, VConfig>::iterator hash_bimap<K, T, KConfig, VConfig>::begin()
{
  // search first key from the hash_bimap
  typename hash_ktable_t::iterator it=m_hash_ktable.begin(), it_end=m_hash_ktable.end();
  while(it!=it_end)
  {
    if(item *&i=*it)
      return iterator(*this, i, &i, 0);
    ++it;
  }
  return iterator(*this, 0, 0, 0);
}
//----

template<typename K, typename T, class KConfig, class VConfig>
typename hash_bimap<K, T, KConfig, VConfig>::const_iterator hash_bimap<K, T, KConfig, VConfig>::end() const
{
  return const_iterator(*this, 0);
}
//----

template<typename K, typename T, class KConfig, class VConfig>
typename hash_bimap<K, T, KConfig, VConfig>::iterator hash_bimap<K, T, KConfig, VConfig>::end()
{
  return const_iterator(*this, 0, 0, 0);
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::collect_table_stats(hash_table_info &kinfo_, hash_table_info &vinfo_) const
{
  // reset info
  kinfo_.num_slots=m_hash_ktable.size();
  kinfo_.num_used_slots=0;
  kinfo_.num_collisions=0;
  kinfo_.max_slot_collisions=0;
  vinfo_.num_slots=m_hash_vtable.size();
  vinfo_.num_used_slots=0;
  vinfo_.num_collisions=0;
  vinfo_.max_slot_collisions=0;

  // collect hash key table info
  {
    typename hash_ktable_t::const_iterator it=m_hash_ktable.begin(), it_end=m_hash_ktable.end();
    while(it!=it_end)
    {
      if(item *i=*it)
      {
        usize_t num_slot_collisions=0;
        while(i->next)
        {
          ++num_slot_collisions;
          i=i->next;
        }
        ++kinfo_.num_used_slots;
        kinfo_.num_collisions+=num_slot_collisions;
        kinfo_.max_slot_collisions=max(kinfo_.max_slot_collisions, num_slot_collisions);
      }
      ++it;
    }
  }

  // collect hash value table info
  {
    typename hash_vtable_t::const_iterator it=m_hash_vtable.begin(), it_end=m_hash_vtable.end();
    while(it!=it_end)
    {
      if(item *i=*it)
      {
        usize_t num_slot_collisions=0;
        while(i->next_val)
        {
          ++num_slot_collisions;
          i=i->next_val;
        }
        ++vinfo_.num_used_slots;
        vinfo_.num_collisions+=num_slot_collisions;
        vinfo_.max_slot_collisions=max(vinfo_.max_slot_collisions, num_slot_collisions);
      }
      ++it;
    }
  }
}
//----

template<typename K, typename T, class KConfig, class VConfig>
typename hash_bimap<K, T, KConfig, VConfig>::inserter hash_bimap<K, T, KConfig, VConfig>::insert(const K &k_, const T &v_, bool replace_)
{
  // check for rehashing
  PFC_MEM_TRACK_STACK();
  if(m_size==m_rehash_ksize_max || m_size==m_rehash_vsize_max)
    rehash(true, m_size==m_rehash_ksize_max, m_size==m_rehash_vsize_max);

  // find item with matching the key
  item *&kdst=m_hash_ktable[hash_kfunc_t::index(k_)];
  item **prev=&kdst, *i=*prev;
  while(i && i->key!=k_)
    i=*(prev=&i->next);

  bool is_new=!i;
  if(is_new)
  {
    // add new item to the hash_bimap
    eh_data<item> p(*m_allocator, 1, hash_bimap_traits<K, T, KConfig, VConfig>::block_alloc_align);
    i=p.data;
    PFC_PNEW(&i->key)K(k_);
    PFC_PNEW(&i->val)T(v_);
    p.reset();
    i->next=kdst;
    kdst=i;
    item *&vdst=m_hash_vtable[hash_vfunc_t::index(v_)];
    i->next_val=vdst;
    vdst=i;
    ++m_size;
  }
  else
    if(replace_)
    {
      // replace existing item with new one
      item **prev=&m_hash_vtable[hash_vfunc_t::index(i->val)], *vi=*prev;
      while(vi!=i)
      {
        prev=&vi->next_val;
        vi=vi->next_val;
      }
      *prev=vi->next_val;
      i->val.~T();
      PFC_PNEW(&i->val)T(v_);
      item *&vdst=m_hash_vtable[hash_vfunc_t::index(v_)];
      i->next_val=vdst;
      vdst=i;
    }

  // return iterator to the added item
  inserter ins={const_iterator(*this, i), is_new};
  return ins;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::cctor(const hash_bimap &hm_)
{
  // copy-construct hash_bimap
  m_rehash_ksize_min=hm_.m_rehash_ksize_min;
  m_rehash_ksize_max=hm_.m_rehash_ksize_max;
  m_rehash_vsize_min=hm_.m_rehash_vsize_min;
  m_rehash_vsize_max=hm_.m_rehash_vsize_max;
  m_size=hm_.m_size;
  m_hash_ktable.resize(hm_.m_hash_ktable.size());
  m_hash_vtable.resize(hm_.m_hash_vtable.size());
  typename hash_ktable_t::const_iterator it_src=hm_.m_hash_ktable.begin(), it_src_end=hm_.m_hash_ktable.end();
  typename hash_ktable_t::iterator it_dst=m_hash_ktable.begin();
  while(it_src!=it_src_end)
  {
    // copy a hash stride
    item *i=*it_src;
    item *&dst=*it_dst;
    while(i)
    {
      eh_data<item> p(*m_allocator, 1, hash_bimap_traits<K, T, KConfig, VConfig>::block_alloc_align);
      PFC_PNEW(p.data)item(*i);
      p.data->next=dst;
      dst=p.data;
      item *&vdst=m_hash_vtable[hash_vfunc_t::index(p.data->val)];
      p.data->next_val=vdst;
      vdst=p.data;
      p.reset();
      i=i->next;
    }
    ++it_src;
    ++it_dst;
  }
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::rehash(bool grow_, bool rehash_ktable_, bool rehash_vtable_)
{
  if(rehash_ktable_ && rehash_vtable_)
  {
    // setup tables for re-hashing
    hash_ktable_t ht(m_hash_ktable); /*todo: alloc from temp memory pool*/
    if(grow_)
    {
      m_hash_ktable.zero();
      m_hash_ktable.resize(m_hash_ktable.next_size());
      m_hash_vtable.zero();
      m_hash_vtable.resize(m_hash_vtable.next_size());
    }
    else
    {
      m_hash_ktable.resize(m_hash_ktable.prev_size());
      m_hash_ktable.zero();
      m_hash_vtable.resize(m_hash_vtable.prev_size());
      m_hash_vtable.zero();
    }
    m_rehash_ksize_min=m_hash_ktable.min_load_limit();
    m_rehash_ksize_max=m_hash_ktable.max_load_limit();
    m_rehash_vsize_min=m_hash_vtable.min_load_limit();
    m_rehash_vsize_max=m_hash_vtable.max_load_limit();

    // re-hash items to the new tables
    typename hash_ktable_t::const_iterator it=ht.begin(), it_end=ht.end();
    while(it!=it_end)
    {
      item *i=*it;
      while(i)
      {
        item *&hks=m_hash_ktable[hash_kfunc_t::index(i->key)];
        item *&hvs=m_hash_vtable[hash_vfunc_t::index(i->val)];
        item *next=i->next;
        i->next=hks;
        i->next_val=hvs;
        hks=i;
        hvs=i;
        i=next;
      }
      ++it;
    }
    return;
  }

  if(rehash_ktable_)
  {
    // setup tables for key table re-hashing
    if(grow_)
    {
      m_hash_ktable.zero();
      m_hash_ktable.resize(m_hash_ktable.next_size());
    }
    else
    {
      m_hash_ktable.resize(m_hash_ktable.prev_size());
      m_hash_ktable.zero();
    }
    m_rehash_ksize_min=m_hash_ktable.min_load_limit();
    m_rehash_ksize_max=m_hash_ktable.max_load_limit();

    // re-hash items to the new key table
    typename hash_vtable_t::const_iterator it=m_hash_vtable.begin(), it_end=m_hash_vtable.end();
    while(it!=it_end)
    {
      item *i=*it;
      while(i)
      {
        item *&hks=m_hash_ktable[hash_kfunc_t::index(i->key)];
        item *next=i->next;
        i->next=hks;
        hks=i;
        i=next;
      }
      ++it;
    }
    return;
  }

  // setup tables for value table re-hashing
  if(grow_)
  {
    m_hash_vtable.zero();
    m_hash_vtable.resize(m_hash_vtable.next_size());
  }
  else
  {
    m_hash_vtable.resize(m_hash_vtable.prev_size());
    m_hash_vtable.zero();
  }
  m_rehash_vsize_min=m_hash_vtable.min_load_limit();
  m_rehash_vsize_max=m_hash_vtable.max_load_limit();

  // re-hash items to the new value table
  typename hash_ktable_t::const_iterator it=m_hash_ktable.begin(), it_end=m_hash_ktable.end();
  while(it!=it_end)
  {
    item *i=*it;
    while(i)
    {
      item *&hvs=m_hash_vtable[hash_vfunc_t::index(i->val)];
      item *next=i->next_val;
      i->next_val=hvs;
      hvs=i;
      i=next;
    }
    ++it;
  }

}
//----------------------------------------------------------------------------


//============================================================================
// hash_bimap::const_iterator
//============================================================================
template<typename K, typename T, class KConfig, class VConfig>
hash_bimap<K, T, KConfig, VConfig>::const_iterator::const_iterator()
  :m_hmap(0)
  ,m_item(0)
{
}
//----

template<typename K, typename T, class KConfig, class VConfig>
hash_bimap<K, T, KConfig, VConfig>::const_iterator::const_iterator(const iterator &it_)
  :m_hmap(it_.m_hmap)
  ,m_item(it_.m_item)
{
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::const_iterator::reset()
{
  m_hmap=0;
  m_item=0;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class KConfig, class VConfig>
bool hash_bimap<K, T, KConfig, VConfig>::const_iterator::operator==(const const_iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
bool hash_bimap<K, T, KConfig, VConfig>::const_iterator::operator==(const iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
bool hash_bimap<K, T, KConfig, VConfig>::const_iterator::operator!=(const const_iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
bool hash_bimap<K, T, KConfig, VConfig>::const_iterator::operator!=(const iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
typename hash_bimap<K, T, KConfig, VConfig>::const_iterator &hash_bimap<K, T, KConfig, VConfig>::const_iterator::operator++()
{
  // advance the iterator
  PFC_ASSERT_PEDANTIC(m_item);
  if(!m_item->next)
    next_kstride();
  else
    m_item=m_item->next;
  return *this;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
typename hash_bimap<K, T, KConfig, VConfig>::const_iterator &hash_bimap<K, T, KConfig, VConfig>::const_iterator::next_val()
{
  // advance the iterator
  if(!m_item->next)
    next_vstride();
  else
    m_item=m_item->next_val;
  return *this;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
const T &hash_bimap<K, T, KConfig, VConfig>::const_iterator::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item->val;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
const T *hash_bimap<K, T, KConfig, VConfig>::const_iterator::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return &m_item->val;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
const K &hash_bimap<K, T, KConfig, VConfig>::const_iterator::key() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item->key;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class KConfig, class VConfig>
hash_bimap<K, T, KConfig, VConfig>::const_iterator::const_iterator(const hash_bimap &hm_, const item *i_)
  :m_hmap(&hm_)
  ,m_item(i_)
{
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::const_iterator::next_kstride()
{
  // search next used key stride
  typename hash_ktable_t::const_iterator it=m_hmap->m_hash_ktable.at(hash_kfunc_t::index(m_item->key)), it_end=m_hmap->m_hash_ktable.end();
  m_item=0;
  while(++it!=it_end && (m_item=*it)==0);
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::const_iterator::next_vstride()
{
  // search next used value stride
  typename hash_vtable_t::const_iterator it=m_hmap->m_hash_vtable.at(hash_vfunc_t::index(m_item->val)), it_end=m_hmap->m_hash_vtable.end();
  m_item=0;
  while(++it!=it_end && (m_item=*it)==0);
}
//----------------------------------------------------------------------------


//============================================================================
// hash_bimap::iterator
//============================================================================
template<typename K, typename T, class KConfig, class VConfig>
hash_bimap<K, T, KConfig, VConfig>::iterator::iterator()
  :m_hmap(0)
  ,m_item(0)
{
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::iterator::reset()
{
  m_hmap=0;
  m_item=0;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class KConfig, class VConfig>
bool hash_bimap<K, T, KConfig, VConfig>::iterator::operator==(const const_iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
bool hash_bimap<K, T, KConfig, VConfig>::iterator::operator==(const iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
bool hash_bimap<K, T, KConfig, VConfig>::iterator::operator!=(const const_iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
bool hash_bimap<K, T, KConfig, VConfig>::iterator::operator!=(const iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
typename hash_bimap<K, T, KConfig, VConfig>::iterator &hash_bimap<K, T, KConfig, VConfig>::iterator::operator++()
{
  // advance the iterator
  PFC_ASSERT_PEDANTIC(m_item);
  if(!m_item->next)
    next_kstride();
  else
  {
    m_prev=&m_item->next;
    m_prev_val=0;
    m_item=m_item->next;
  }
  return *this;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
typename hash_bimap<K, T, KConfig, VConfig>::iterator &hash_bimap<K, T, KConfig, VConfig>::iterator::next_val()
{
  // advance the iterator
  if(!m_item->next)
    next_vstride();
  else
  {
    m_prev=0;
    m_prev_val=&m_item->next;
    m_item=m_item->next_val;
  }
  return *this;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
const T &hash_bimap<K, T, KConfig, VConfig>::iterator::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item->val;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
const T *hash_bimap<K, T, KConfig, VConfig>::iterator::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return &m_item->val;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
const K &hash_bimap<K, T, KConfig, VConfig>::iterator::key() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item->key;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::iterator::remove()
{
  // find previous key pointer if not setup
  PFC_ASSERT_PEDANTIC(m_item);
  if(!m_prev)
  {
    m_prev=&m_hmap->m_hash_ktable[hash_kfunc_t::index(m_item->key)];
    while((*m_prev)!=m_item)
      m_prev=&(*m_prev)->next;
  }

  // find previous value pointer if not setup
  if(!m_prev_val)
  {
    m_prev_val=m_hmap->m_hash_vtable[hash_vfunc_t::index(m_item->val)];
    while((*m_prev_val)!=m_item)
      m_prev_val=&(*m_prev_val)->next_val;
  }

  // remove item from the hash_bimap
  *m_prev_val=m_item->next_val;
  item *next=m_item->next;
  *m_prev=next;
  if(!next)
  {
    // search for the next used stride
    typename hash_ktable_t::iterator it=m_hmap->m_hash_ktable.at(hash_kfunc_t::index(m_item->key)), it_end=m_hmap->m_hash_ktable.end();
    while(++it!=it_end)
      if((next=*it)!=0)
      {
        m_prev=&*it;
        break;
      }
  }

  // destruct the item
  m_item->val.~T();
  m_item->key.~K();
  m_hmap->m_allocator->free(m_item);
  m_item=next;
  m_prev_val=0;
  --m_hmap->m_size;
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::iterator::remove_val()
{
  // find previous key pointer if not setup
  PFC_ASSERT_PEDANTIC(m_item);
  if(!m_prev)
  {
    m_prev=&m_hmap->m_hash_ktable[hash_kfunc_t::index(m_item->key)];
    while((*m_prev)!=m_item)
      m_prev=&(*m_prev)->next;
  }

  // find previous value pointer if not setup
  if(!m_prev_val)
  {
    m_prev_val=&m_hmap->m_hash_vtable[hash_vfunc_t::index(m_item->val)];
    while((*m_prev_val)!=m_item)
      m_prev_val=&(*m_prev_val)->next_val;
  }

  // remove item from the hash_bimap
  *m_prev=m_item->next;
  item *next_val=m_item->next_val;
  *m_prev_val=next_val;
  if(!next_val)
  {
    // search for the next used stride
    typename hash_vtable_t::iterator it=m_hmap->m_hash_vtable.at(hash_vfunc_t::index(m_item->val)), it_end=m_hmap->m_hash_vtable.end();
    while(++it!=it_end)
      if((next_val=*it)!=0)
      {
        m_prev_val=&*it;
        break;
      }
  }

  // destruct the item
  m_item->val.~T();
  m_item->key.~K();
  m_hmap->m_allocator->free(m_item);
  m_item=next_val;
  m_prev=0;
  --m_hmap->m_size;
}
//----------------------------------------------------------------------------

template<typename K, typename T, class KConfig, class VConfig>
hash_bimap<K, T, KConfig, VConfig>::iterator::iterator(hash_bimap &hbm_, item *i_, item **prev_, item **prev_val_)
  :m_hmap(&hbm_)
  ,m_item(i_)
  ,m_prev(prev_)
  ,m_prev_val(prev_val_)
{
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::iterator::next_kstride()
{
  // search next used key stride
  typename hash_ktable_t::iterator it=m_hmap->m_hash_ktable.at(hash_kfunc_t::index(m_item->key)), it_end=m_hmap->m_hash_ktable.end();
  m_item=0;
  while(++it!=it_end)
    if((m_item=*it)!=0)
    {
      m_prev=&*it;
      m_prev_val=0;
      break;
    }
}
//----

template<typename K, typename T, class KConfig, class VConfig>
void hash_bimap<K, T, KConfig, VConfig>::iterator::next_vstride()
{
  // search next used value stride
  typename hash_vtable_t::iterator it=m_hmap->m_hash_vtable.at(hash_vfunc_t::index(m_item->val)), it_end=m_hmap->m_hash_vtable.end();
  m_item=0;
  while(++it!=it_end)
    if((m_item=*it)!=0)
    {
      m_prev=0;
      m_prev_val=&*it;
      break;
    }
}
//----------------------------------------------------------------------------


//============================================================================
// swap functions
//============================================================================
template<typename T>
PFC_INLINE void swap(owner_array<T> &a0_, owner_array<T> &a1_)
{
  a0_.swap(a1_);
}
//----

template<typename T>
PFC_INLINE void swap(array<T> &a0_, array<T> &a1_)
{
  a0_.swap(a1_);
}
//----

template<typename T, usize_t capacity>
PFC_INLINE void swap(sarray<T, capacity> &a0_, sarray<T, capacity> &a1_)
{
  a0_.swap(a1_);
}
//----

template<typename T>
PFC_INLINE void swap(deque<T> &d0_, deque<T> &d1_)
{
  d0_.swap(d1_);
}
//----

template<typename T>
PFC_INLINE void swap(list<T> &l0_, list<T> &l1_)
{
  l0_.swap(l1_);
}
//----

template<typename T>
PFC_INLINE void swap(set<T> &s0_, set<T> &s1_)
{
  s0_.swap(s1_);
}
//----

template<typename K, typename T, class CmpPred>
PFC_INLINE void swap(map<K, T> &m0_, map<K, T> &m1_)
{
  m0_.swap(m1_);
}
//----

template<typename T>
PFC_INLINE void swap(hash_set<T> &hs0_, hash_set<T> &hs1_)
{
  hs0_.swap(hs1_);
}
//----

template<typename K, typename T>
PFC_INLINE void swap(hash_map<K, T> &hm0_, hash_map<K, T> &hm1_)
{
  hm0_.swap(hm1_);
}
//----

template<typename K, typename T>
PFC_INLINE void swap(hash_bimap<K, T> &hbm0_, hash_bimap<K, T> &hbm1_)
{
  hbm0_.swap(hbm1_);
}
//----------------------------------------------------------------------------
