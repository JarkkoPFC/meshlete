//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================


//============================================================================
// slist_const_iterator
//============================================================================
template<typename T, T *(T::*next_mvar)>
slist_const_iterator<T, next_mvar>::slist_const_iterator()
{
  m_item=0;
}
//----

template<typename T, T *(T::*next_mvar)>
slist_const_iterator<T, next_mvar>::slist_const_iterator(const T *item_)
{
  m_item=item_;
}
//----

template<typename T, T *(T::*next_mvar)>
slist_const_iterator<T, next_mvar>::slist_const_iterator(const slist_iterator<T, next_mvar> &it_)
{
  m_item=it_.m_item;
}
//----------------------------------------------------------------------------

template<typename T, T *(T::*next_mvar)>
bool slist_const_iterator<T, next_mvar>::operator==(const slist_const_iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename T, T *(T::*next_mvar)>
bool slist_const_iterator<T, next_mvar>::operator==(const slist_iterator<T, next_mvar> &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename T, T *(T::*next_mvar)>
bool slist_const_iterator<T, next_mvar>::operator!=(const slist_const_iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename T, T *(T::*next_mvar)>
bool slist_const_iterator<T, next_mvar>::operator!=(const slist_iterator<T, next_mvar> &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename T, T *(T::*next_mvar)>
slist_const_iterator<T, next_mvar> &slist_const_iterator<T, next_mvar>::operator++()
{
  PFC_ASSERT_PEDANTIC(m_item);
  m_item=m_item->*next_mvar;
  return *this;
}
//----

template<typename T, T *(T::*next_mvar)>
const T &slist_const_iterator<T, next_mvar>::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return *m_item;
}
//----

template<typename T, T *(T::*next_mvar)>
const T *slist_const_iterator<T, next_mvar>::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item;
}
//----------------------------------------------------------------------------


//============================================================================
// slist_iterator
//============================================================================
template<typename T, T *(T::*next_mvar)>
slist_iterator<T, next_mvar>::slist_iterator()
{
  m_item=0;
}
//----

template<typename T, T *(T::*next_mvar)>
slist_iterator<T, next_mvar>::slist_iterator(T *item_)
{
  m_item=item_;
}
//----------------------------------------------------------------------------

template<typename T, T *(T::*next_mvar)>
bool slist_iterator<T, next_mvar>::operator==(const slist_const_iterator<T, next_mvar> &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename T, T *(T::*next_mvar)>
bool slist_iterator<T, next_mvar>::operator==(const slist_iterator &it_) const
{
  return m_item==it_.m_item;
}
//----

template<typename T, T *(T::*next_mvar)>
bool slist_iterator<T, next_mvar>::operator!=(const slist_const_iterator<T, next_mvar> &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename T, T *(T::*next_mvar)>
bool slist_iterator<T, next_mvar>::operator!=(const slist_iterator &it_) const
{
  return m_item!=it_.m_item;
}
//----

template<typename T, T *(T::*next_mvar)>
slist_iterator<T, next_mvar> &slist_iterator<T, next_mvar>::operator++()
{
  PFC_ASSERT_PEDANTIC(m_item);
  m_item=m_item->*next_mvar;
  return *this;
}
//----

template<typename T, T *(T::*next_mvar)>
T &slist_iterator<T, next_mvar>::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return *m_item;
}
//----

template<typename T, T *(T::*next_mvar)>
T *slist_iterator<T, next_mvar>::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_item);
  return m_item;
}
//----------------------------------------------------------------------------


//============================================================================
// array_iterator
//============================================================================
template<typename T, bool is_forward>
array_iterator<T, is_forward>::array_iterator()
{
  data=0;
}
//----

template<typename T, bool is_forward>
array_iterator<T, is_forward>::array_iterator(T *p_)
{
  data=p_;
}
//----

template<typename T, bool is_forward>
template<typename U>
array_iterator<T, is_forward>::array_iterator(const array_iterator<U, is_forward> &it_)
{
  data=it_.data;
}
//----------------------------------------------------------------------------

template<typename T, bool is_forward>
template<typename U>
bool array_iterator<T, is_forward>::operator==(const array_iterator<U, is_forward> &it_) const
{
  return data==it_.data;
}
//----

template<typename T, bool is_forward>
template<typename U>
bool array_iterator<T, is_forward>::operator!=(const array_iterator<U, is_forward> &it_) const
{
  return data==it_.data;
}
//----

template<typename T, bool is_forward>
array_iterator<T, is_forward> &array_iterator<T, is_forward>::operator++()
{
  data+=is_forward?1:-1;
  return *this;
}
//----

template<typename T, bool is_forward>
array_iterator<T, is_forward> &array_iterator<T, is_forward>::operator--()
{
  data+=is_forward?-1:1;
  return *this;
}
//----

template<typename T, bool is_forward>
array_iterator<T, is_forward> &array_iterator<T, is_forward>::operator+=(ssize_t offset_)
{
  data+=is_forward?offset_:-offset_;
  return *this;
}
//----

template<typename T, bool is_forward>
template<typename U>
array_iterator<T, is_forward> &array_iterator<T, is_forward>::operator+=(const array_iterator &it_)
{
  data+=is_forward?it_.data:-it_.data;
  return *this;
}
//----

template<typename T, bool is_forward>
array_iterator<T, is_forward> &array_iterator<T, is_forward>::operator-=(ssize_t offset_)
{
  data+=is_forward?-offset_:offset_;
  return *this;
}
//----

template<typename T, bool is_forward>
template<typename U>
array_iterator<T, is_forward> &array_iterator<T, is_forward>::operator-=(const array_iterator &it_)
{
  data+=is_forward?-it_.data:it_.data;
  return *this;
}
//----

template<typename T, bool is_forward>
array_iterator<T, is_forward> array_iterator<T, is_forward>::operator+(ssize_t offset_) const
{
  return array_iterator(data+(is_forward?offset_:-offset_));
}
//----

template<typename T, bool is_forward>
template<typename U>
array_iterator<T, is_forward> array_iterator<T, is_forward>::operator+(const array_iterator &it_) const
{
  return array_iterator(data+(is_forward?it_.data:-it_.data));
}
//----

template<typename T, bool is_forward>
array_iterator<T, is_forward> array_iterator<T, is_forward>::operator-(ssize_t offset_) const
{
  return array_iterator(data+(is_forward?-offset_:offset_));
}
//----

template<typename T, bool is_forward>
template<typename U>
array_iterator<T, is_forward> array_iterator<T, is_forward>::operator-(const array_iterator &it_) const
{
  return array_iterator(data+(is_forward?-it_.data:it_.data));
}
//----

template<typename T, bool is_forward>
T &array_iterator<T, is_forward>::operator[](usize_t index_) const
{
  return data[is_forward?index_:-index_];
}
//----

template<typename T, bool is_forward>
T &array_iterator<T, is_forward>::operator*() const
{
  return *data;
}
//----

template<typename T, bool is_forward>
T *array_iterator<T, is_forward>::operator->() const
{
  return data;
}
//----------------------------------------------------------------------------
