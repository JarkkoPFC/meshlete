//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_ITERATORS_H
#define PFC_CORE_ITERATORS_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core.h"
namespace pfc
{

// new
template<typename> struct iterator_trait;
template<typename T, T *(T::*next_mvar)> class slist_const_iterator;
template<typename T, T *(T::*next_mvar)> class slist_iterator;
template<typename T, bool is_forward> class array_iterator;
//----------------------------------------------------------------------------


//============================================================================
// iterator_trait
//============================================================================
template<typename T> struct iterator_trait
{
  typedef typename T::value_t value_t;
};
//----

template<typename T> struct iterator_trait<T*> {typedef T value_t;};
//----------------------------------------------------------------------------


//============================================================================
// slist_const_iterator
//============================================================================
template<typename T, T *(T::*next_mvar)=&T::next>
class slist_const_iterator
{
public:
  // nested types
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE slist_const_iterator();
  PFC_INLINE slist_const_iterator(const T*);
  PFC_INLINE slist_const_iterator(const slist_iterator<T, next_mvar>&);
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const slist_const_iterator &it_)  {return it_.m_item!=0;}
  PFC_INLINE bool operator==(const slist_const_iterator&) const;
  PFC_INLINE bool operator==(const slist_iterator<T, next_mvar>&) const;
  PFC_INLINE bool operator!=(const slist_const_iterator&) const;
  PFC_INLINE bool operator!=(const slist_iterator<T, next_mvar>&) const;
  PFC_INLINE slist_const_iterator &operator++();
  PFC_INLINE const T &operator*() const;
  PFC_INLINE const T *operator->() const;
  PFC_INLINE friend const T *ptr(const slist_const_iterator &it_)   {return it_.m_item;}
  //--------------------------------------------------------------------------

private:
  friend class slist_iterator<T, next_mvar>;
  const T *m_item;
};
//----------------------------------------------------------------------------


//============================================================================
// slist_iterator
//============================================================================
template<typename T, T *(T::*next_mvar)=&T::next>
class slist_iterator
{
public:
  // nested types
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE slist_iterator();
  PFC_INLINE slist_iterator(T*);
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const slist_iterator &it_)  {return it_.m_item!=0;}
  PFC_INLINE bool operator==(const slist_const_iterator<T, next_mvar>&) const;
  PFC_INLINE bool operator==(const slist_iterator&) const;
  PFC_INLINE bool operator!=(const slist_const_iterator<T, next_mvar>&) const;
  PFC_INLINE bool operator!=(const slist_iterator&) const;
  PFC_INLINE slist_iterator &operator++();
  PFC_INLINE T &operator*() const;
  PFC_INLINE T *operator->() const;
  PFC_INLINE friend T *ptr(const slist_iterator &it_)         {return it_.m_item;}
  //--------------------------------------------------------------------------

private:
  friend class slist_const_iterator<T, next_mvar>;
  T *m_item;
};
//----------------------------------------------------------------------------


//============================================================================
// array_iterator
//============================================================================
template<typename T, bool is_forward>
class array_iterator
{
public:
  // nested types
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE array_iterator();
  PFC_INLINE array_iterator(T*);
  template<typename U> PFC_INLINE array_iterator(const array_iterator<U, is_forward>&);
  //--------------------------------------------------------------------------

  // iteration and accessors
  PFC_INLINE friend bool is_valid(const array_iterator &it_)  {return it_.data!=0;}
  template<typename U> PFC_INLINE bool operator==(const array_iterator<U, is_forward>&) const;
  template<typename U> PFC_INLINE bool operator!=(const array_iterator<U, is_forward>&) const;
  PFC_INLINE array_iterator &operator++();
  PFC_INLINE array_iterator &operator--();
  PFC_INLINE array_iterator &operator+=(ssize_t offset_);
  template<typename U> PFC_INLINE array_iterator &operator+=(const array_iterator&);
  PFC_INLINE array_iterator &operator-=(ssize_t offset_);
  template<typename U> PFC_INLINE array_iterator &operator-=(const array_iterator&);
  PFC_INLINE array_iterator operator+(ssize_t offset_) const;
  template<typename U> PFC_INLINE array_iterator operator+(const array_iterator&) const;
  PFC_INLINE array_iterator operator-(ssize_t offset_) const;
  template<typename U> PFC_INLINE array_iterator operator-(const array_iterator&) const;
  PFC_INLINE T &operator[](usize_t index_) const;
  PFC_INLINE T &operator*() const;
  PFC_INLINE T *operator->() const;
  PFC_INLINE friend T *ptr(const array_iterator &it_)         {return it_.data;}
  //--------------------------------------------------------------------------

  T *data;
};
//----------------------------------------------------------------------------

//============================================================================
#include "iterators.inl"
} // namespace pfc
#endif
