//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_CONTAINERS_H
#define PFC_CORE_CONTAINERS_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core/utils.h"
#include "core/meta.h"
#include "core/iterators.h"
namespace pfc
{

// new
struct compare_predicate;
template<typename> class owner_array;
template<typename> class array;
template<typename, usize_t capacity> class sarray;
template<typename> class deque;
template<typename> class list;
template<typename T, class CmpPred=compare_predicate> class set;
template<typename K, typename T, class CmpPred=compare_predicate> class map;
template<typename T> class hash_table_array;
template<typename T, usize_t capacity> class hash_table_sarray;
template<typename T> class hash_table_deque;
template<class Func, template<class> class Table=hash_table_array> struct hash_config;
struct hash_table_info;
template<typename T, class Config=hash_config<hash_func<T> > > class hash_set;
template<typename K, typename T, class Config=hash_config<hash_func<K> > > class hash_map;
template<typename K, typename T, class KConfig=hash_config<hash_func<K> >, class VConfig=hash_config<hash_func<T> > > class hash_bimap;
// swap functions
template<typename T> PFC_INLINE void swap(owner_array<T>&, owner_array<T>&);
template<typename T> PFC_INLINE void swap(array<T>&, array<T>&);
template<typename T, usize_t capacity> PFC_INLINE void swap(sarray<T, capacity>&, sarray<T, capacity>&);
template<typename T> PFC_INLINE void swap(deque<T>&, deque<T>&);
template<typename T> PFC_INLINE void swap(list<T>&, list<T>&);
template<typename T, class CmpPred> PFC_INLINE void swap(set<T, CmpPred>&, set<T, CmpPred>&);
template<typename K, typename T, class CmpPred> PFC_INLINE void swap(map<K, T, CmpPred>&, map<K, T, CmpPred>&);
template<typename T, class Config> PFC_INLINE void swap(hash_set<T, Config>&, hash_set<T, Config>&);
template<typename K, typename T, class Config> PFC_INLINE void swap(hash_map<K, T, Config>&, hash_map<K, T, Config>&);
template<typename K, typename T, class KConfig, class VConfig> PFC_INLINE void swap(hash_bimap<K, T, KConfig, VConfig>&, hash_bimap<K, T, KConfig, VConfig>&);
//----------------------------------------------------------------------------


//============================================================================
// compare_predicate
//============================================================================
struct compare_predicate
{
  template<typename T, typename U> PFC_INLINE bool before(const T&, const U&) const;
  template<typename T, typename U> PFC_INLINE bool equal(const T&, const U&) const;
};
//----------------------------------------------------------------------------


//============================================================================
// owner_array
//============================================================================
template<typename T>
class owner_array
{
public:
  // construction
  PFC_INLINE owner_array();
  PFC_INLINE owner_array(T*, usize_t size_);
  PFC_INLINE owner_array(const owner_array&);
  PFC_INLINE void set(T*, usize_t size_);
  PFC_INLINE void operator=(const owner_array&);
  PFC_INLINE ~owner_array();
  PFC_INLINE void clear();
  PFC_INLINE void swap(owner_array&);
  owner_data steal_data();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE friend bool is_valid(const owner_array &arr_)  {return arr_.data!=0;}
  PFC_INLINE friend void *ptr(const owner_array &arr_)      {return arr_.data;}
  //--------------------------------------------------------------------------

  mutable usize_t size;
  mutable T *data;
  //--------------------------------------------------------------------------

private:
  template<class PE> void stream_array(PE&, meta_case<0> is_type_void_);
  template<class PE> void stream_array(PE&, meta_case<1> default_);
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, owner_array<T>, is_type_pod_def_ctor, true);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, owner_array<T>, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// array
//============================================================================
template<typename T>
class array
{
public:
  // nested types
  typedef const T *const_iterator;
  typedef T *iterator;
  typedef array_iterator<typename add_const<T>::res, false> const_reverse_iterator;
  typedef array_iterator<T, false> reverse_iterator;
  //--------------------------------------------------------------------------

  // construction
  array(memory_allocator_base *alloc_=0);
  array(const array&);
  array(const array&, memory_allocator_base*);
  explicit array(usize_t size_, memory_allocator_base *alloc_=0);
  array(usize_t size_, const T&, memory_allocator_base *alloc_=0);
  PFC_INLINE ~array();
  void operator=(const array&);
  void set_allocator(memory_allocator_base*);
  void clear();
  void reset_size(usize_t size_);
  void reset_size(usize_t size_, const T&);
  void resize(usize_t size_);
  void resize(usize_t size_, const T&);
  void resize_to_zero();
  void reserve(usize_t capacity_);
  void trim(usize_t permitted_slack_=0);
  PFC_INLINE void swap(array&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE memory_allocator_base &allocator() const;
  PFC_INLINE usize_t size() const;
  PFC_INLINE usize_t capacity() const;
  PFC_INLINE const T &operator[](usize_t idx_) const;
  PFC_INLINE T &operator[](usize_t idx_);
  PFC_INLINE const T &front() const;
  PFC_INLINE T &front();
  PFC_INLINE const T &back() const;
  PFC_INLINE T &back();
  PFC_INLINE const T *data() const;
  PFC_INLINE T *data();
  PFC_INLINE const_iterator begin() const;
  PFC_INLINE iterator begin();
  PFC_INLINE const_reverse_iterator rbegin() const;
  PFC_INLINE reverse_iterator rbegin();
  PFC_INLINE const_iterator last() const;
  PFC_INLINE iterator last();
  PFC_INLINE const_reverse_iterator rlast() const;
  PFC_INLINE reverse_iterator rlast();
  PFC_INLINE const_iterator end() const;
  PFC_INLINE iterator end();
  PFC_INLINE const_reverse_iterator rend() const;
  PFC_INLINE reverse_iterator rend();
  PFC_INLINE void get(usize_t start_idx_, T*, usize_t num_items_) const;
  PFC_INLINE void set(usize_t start_idx_, const T*, usize_t num_items_);
  PFC_INLINE void set(usize_t start_idx_, const T&, usize_t num_items_);
  PFC_INLINE void push_front(const T&);
  PFC_INLINE T &push_front();
  PFC_INLINE void push_back(const T&);
  PFC_INLINE T &push_back();
  PFC_INLINE void insert_front(usize_t num_items_);
  PFC_INLINE void insert_front(usize_t num_items_, const T&);
  PFC_INLINE void insert_front(usize_t num_items_, const T*);
  PFC_INLINE void insert_back(usize_t num_items_);
  PFC_INLINE void insert_back(usize_t num_items_, const T&);
  PFC_INLINE void insert_back(usize_t num_items_, const T*);
  PFC_INLINE void pop_front();
  PFC_INLINE void pop_back();
  PFC_INLINE void remove_front(usize_t num_items_);
  PFC_INLINE void remove_back(usize_t num_items_);
  PFC_INLINE void remove_at(usize_t idx_);
  PFC_INLINE void remove_at(usize_t idx_, usize_t num_items_);
  owner_array<T> steal_data();
  //--------------------------------------------------------------------------

private:
  void reserve(usize_t capacity_, usize_t offset_);
  //--------------------------------------------------------------------------

  memory_allocator_base *m_allocator;
  usize_t m_size;
  usize_t m_capacity;
  T *m_data;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, array<T>, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// sarray
//============================================================================
template<typename T, usize_t cap>
class sarray
{
public:
  // nested types
  typedef const T *const_iterator;
  typedef T *iterator;
  typedef array_iterator<typename add_const<T>::res, false> const_reverse_iterator;
  typedef array_iterator<T, false> reverse_iterator;
  //--------------------------------------------------------------------------

  // construction
  sarray();
  sarray(const sarray&);
  template<usize_t cap2> sarray(const sarray<T, cap2>&);
  explicit sarray(usize_t size_);
  sarray(usize_t size_, const T&);
  PFC_INLINE ~sarray();
  void operator=(const sarray&);
  template<usize_t cap2> void operator=(const sarray<T, cap2>&);
  void clear();
  void reset_size(usize_t size_);
  void reset_size(usize_t size_, const T&);
  void resize(usize_t size_);
  void resize(usize_t size_, const T&);
  void resize_to_zero();
  PFC_INLINE void swap(sarray&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE usize_t size() const;
  PFC_INLINE const T &operator[](usize_t idx_) const;
  PFC_INLINE T &operator[](usize_t idx_);
  PFC_INLINE const T &front() const;
  PFC_INLINE T &front();
  PFC_INLINE const T &back() const;
  PFC_INLINE T &back();
  PFC_INLINE const T *data() const;
  PFC_INLINE T *data();
  PFC_INLINE const_iterator begin() const;
  PFC_INLINE iterator begin();
  PFC_INLINE const_reverse_iterator rbegin() const;
  PFC_INLINE reverse_iterator rbegin();
  PFC_INLINE const_iterator last() const;
  PFC_INLINE iterator last();
  PFC_INLINE const_reverse_iterator rlast() const;
  PFC_INLINE reverse_iterator rlast();
  PFC_INLINE const_iterator end() const;
  PFC_INLINE iterator end();
  PFC_INLINE const_reverse_iterator rend() const;
  PFC_INLINE reverse_iterator rend();
  PFC_INLINE void get(usize_t start_idx_, T*, usize_t num_items_) const;
  PFC_INLINE void set(usize_t start_idx_, const T*, usize_t num_items_);
  PFC_INLINE void set(usize_t start_idx_, const T&, usize_t num_items_);
  PFC_INLINE void push_front(const T&);
  PFC_INLINE T &push_front();
  PFC_INLINE void push_back(const T&);
  PFC_INLINE T &push_back();
  PFC_INLINE void insert_front(usize_t num_items_);
  PFC_INLINE void insert_front(usize_t num_items_, const T&);
  PFC_INLINE void insert_front(usize_t num_items_, const T*);
  PFC_INLINE void insert_back(usize_t num_items_);
  PFC_INLINE void insert_back(usize_t num_items_, const T&);
  PFC_INLINE void insert_back(usize_t num_items_, const T*);
  PFC_INLINE void pop_front();
  PFC_INLINE void pop_back();
  PFC_INLINE void remove_front(usize_t num_items_);
  PFC_INLINE void remove_back(usize_t num_items_);
  //--------------------------------------------------------------------------

private:
  usize_t m_size;
  typename meta_storage<T>::res m_data[cap];
};
PFC_SET_TYPE_TRAIT_PARTIAL2(typename T, usize_t cap, sarray<T, cap>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL2(typename T, usize_t cap, sarray<T, cap>, is_type_pod_def_ctor, is_type_pod_def_ctor<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL2(typename T, usize_t cap, sarray<T, cap>, is_type_pod_dtor, is_type_pod_dtor<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL2(typename T, usize_t cap, sarray<T, cap>, is_type_pod_move, is_type_pod_move<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL2(typename T, usize_t cap, sarray<T, cap>, is_type_pod_copy, is_type_pod_copy<T>::res);
//----------------------------------------------------------------------------


//============================================================================
// deque
//============================================================================
template<typename T>
struct deque_traits
{
  // properties
  enum {sshift=meta_max<meta_log2<1024/sizeof(T)>::res, 4>::res,
        ssize=1<<sshift,
        smask=ssize-1,
        block_alloc_size=ssize*sizeof(T),
        block_alloc_align=meta_alignof<T>::res};
};
//----------------------------------------------------------------------------

template<typename T>
class deque
{
  template<bool is_forward> class const_iterator_impl;
  template<bool is_forward> class iterator_impl;
public:
  // nested types
  typedef const_iterator_impl<true> const_iterator;
  typedef const_iterator_impl<false> const_reverse_iterator;
  typedef iterator_impl<true> iterator;
  typedef iterator_impl<false> reverse_iterator;
  //--------------------------------------------------------------------------

  // construction
  deque(memory_allocator_base *alloc_=0);
  deque(const deque&);
  deque(const deque&, memory_allocator_base*);
  explicit deque(usize_t size_, memory_allocator_base *alloc_=0);
  deque(usize_t size_, const T&, memory_allocator_base *alloc_=0);
  PFC_INLINE ~deque();
  void operator=(const deque&);
  void set_allocator(memory_allocator_base*);
  void clear();
  void resize(usize_t size_);
  void resize(usize_t size_, const T&);
  PFC_INLINE void swap(deque&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE memory_allocator_base &allocator() const;
  PFC_INLINE usize_t size() const;
  PFC_INLINE const T &operator[](usize_t idx_) const;
  PFC_INLINE T &operator[](usize_t idx_);
  PFC_INLINE const T &front() const;
  PFC_INLINE T &front();
  PFC_INLINE const T &back() const;
  PFC_INLINE T &back();
  PFC_INLINE const_iterator begin() const;
  PFC_INLINE iterator begin();
  PFC_INLINE const_reverse_iterator rbegin() const;
  PFC_INLINE reverse_iterator rbegin();
  PFC_INLINE const_iterator last() const;
  PFC_INLINE iterator last();
  PFC_INLINE const_reverse_iterator rlast() const;
  PFC_INLINE reverse_iterator rlast();
  PFC_INLINE const_iterator end() const;
  PFC_INLINE iterator end();
  PFC_INLINE const_reverse_iterator rend() const;
  PFC_INLINE reverse_iterator rend();
  PFC_INLINE void get(usize_t start_idx_, T*, usize_t num_items_) const;
  PFC_INLINE void set(usize_t start_idx_, const T*, usize_t num_items_);
  PFC_INLINE void set(usize_t start_idx_, const T&, usize_t num_items_);
  PFC_INLINE void push_front(const T&);
  PFC_INLINE T &push_front();
  PFC_INLINE void push_back(const T&);
  PFC_INLINE T &push_back();
  PFC_INLINE void insert_front(usize_t num_items_);
  PFC_INLINE void insert_front(usize_t num_items_, const T&);
  PFC_INLINE void insert_front(usize_t num_items_, const T*);
  PFC_INLINE void insert_back(usize_t num_items_);
  PFC_INLINE void insert_back(usize_t num_items_, const T&);
  PFC_INLINE void insert_back(usize_t num_items_, const T*);
  PFC_INLINE void pop_front();
  PFC_INLINE void pop_back();
  PFC_INLINE void remove_front(usize_t num_items_);
  PFC_INLINE void remove_back(usize_t num_items_);
  //--------------------------------------------------------------------------

private:
  void cctor(const deque&);
  void alloc_stride_front();
  void alloc_stride_back();
  void dealloc_stride_front();
  void dealloc_stride_back();
  //--------------------------------------------------------------------------

  memory_allocator_base *m_allocator;
  usize_t m_size;
  usize_t m_offset;
  T *m_first, *m_last, *m_stride_last;
  array<T*> m_strides;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, deque<T>, is_type_pod_move, true);
//----------------------------------------------------------------------------

//============================================================================
// deque::const_iterator_impl
//============================================================================
template<typename T>
template<bool is_forward>
class deque<T>::const_iterator_impl
{
public:
  // nested types
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE const_iterator_impl();
  PFC_INLINE const_iterator_impl(const iterator_impl<is_forward>&);
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const const_iterator_impl &it_)  {return it_.m_deque && it_.m_index<it_.m_deque->size();}
  PFC_INLINE bool operator==(const const_iterator_impl&) const;
  PFC_INLINE bool operator==(const iterator_impl<is_forward>&) const;
  PFC_INLINE bool operator!=(const const_iterator_impl&) const;
  PFC_INLINE bool operator!=(const iterator_impl<is_forward>&) const;
  PFC_INLINE const_iterator_impl &operator++();
  PFC_INLINE const_iterator_impl &operator--();
  PFC_INLINE const_iterator_impl &operator+=(ssize_t offset_);
  PFC_INLINE const_iterator_impl &operator+=(const const_iterator_impl&);
  PFC_INLINE const_iterator_impl &operator+=(const iterator_impl<is_forward>&);
  PFC_INLINE const_iterator_impl &operator-=(ssize_t offset_);
  PFC_INLINE const_iterator_impl &operator-=(const const_iterator_impl&);
  PFC_INLINE const_iterator_impl &operator-=(const iterator_impl<is_forward>&);
  PFC_INLINE const_iterator_impl operator+(ssize_t offset_) const;
  PFC_INLINE const_iterator_impl operator+(const const_iterator_impl&) const;
  PFC_INLINE const_iterator_impl operator+(const iterator_impl<is_forward>&) const;
  PFC_INLINE const_iterator_impl operator-(ssize_t offset_) const;
  PFC_INLINE const_iterator_impl operator-(const const_iterator_impl&) const;
  PFC_INLINE const_iterator_impl operator-(const iterator_impl<is_forward>&) const;
  PFC_INLINE const T &operator[](usize_t index_) const;
  PFC_INLINE const T &operator*() const;
  PFC_INLINE const T *operator->() const;
  PFC_INLINE friend const T *ptr(const const_iterator_impl &it_)   {return it_.m_deque?&(*it_.m_deque)[it_.m_index]:0;}
  PFC_INLINE usize_t index() const;
  //--------------------------------------------------------------------------

private:
  friend class deque<T>;
  friend class iterator_impl<is_forward>;
  PFC_INLINE const_iterator_impl(const deque<T>&, usize_t index_);
  //--------------------------------------------------------------------------

  const deque<T> *m_deque;
  usize_t m_index;
};
//----------------------------------------------------------------------------

//============================================================================
// deque::iterator_impl
//============================================================================
template<typename T>
template<bool is_forward>
class deque<T>::iterator_impl
{
public:
  // nested types
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE iterator_impl();
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const iterator_impl &it_)  {return it_.m_deque && it_.m_index<it_.m_deque->size();}
  PFC_INLINE bool operator==(const const_iterator_impl<is_forward>&) const;
  PFC_INLINE bool operator==(const iterator_impl&) const;
  PFC_INLINE bool operator!=(const const_iterator_impl<is_forward>&) const;
  PFC_INLINE bool operator!=(const iterator_impl&) const;
  PFC_INLINE iterator_impl &operator++();
  PFC_INLINE iterator_impl &operator--();
  PFC_INLINE iterator_impl &operator+=(ssize_t offset_);
  PFC_INLINE iterator_impl &operator+=(const const_iterator_impl<is_forward>&);
  PFC_INLINE iterator_impl &operator+=(const iterator_impl&);
  PFC_INLINE iterator_impl &operator-=(ssize_t offset_);
  PFC_INLINE iterator_impl &operator-=(const const_iterator_impl<is_forward>&);
  PFC_INLINE iterator_impl &operator-=(const iterator_impl&);
  PFC_INLINE iterator_impl operator+(ssize_t offset_) const;
  PFC_INLINE iterator_impl operator+(const const_iterator_impl<is_forward>&) const;
  PFC_INLINE iterator_impl operator+(const iterator_impl&) const;
  PFC_INLINE iterator_impl operator-(ssize_t offset_) const;
  PFC_INLINE iterator_impl operator-(const const_iterator_impl<is_forward>&) const;
  PFC_INLINE iterator_impl operator-(const iterator_impl&) const;
  PFC_INLINE T &operator[](usize_t index_) const;
  PFC_INLINE T &operator*() const;
  PFC_INLINE T *operator->() const;
  PFC_INLINE friend T *ptr(const iterator_impl &it_)         {return it_.m_deque?&(*it_.m_deque)[it_.m_index]:0;}
  PFC_INLINE usize_t index() const;
  //--------------------------------------------------------------------------

private:
  friend class deque<T>;
  friend class const_iterator_impl<is_forward>;
  PFC_INLINE iterator_impl(deque<T>&, usize_t index_);
  PFC_INLINE friend void move_construct(const iterator_impl &dst_, const iterator_impl &src_, usize_t count_)  {move_construct_impl(dst_, src_, count_);}
  static void move_construct_impl(const iterator_impl &dst_, const iterator_impl &src_, usize_t count_);
  PFC_INLINE friend void rotate_sequence_left(const iterator_impl &first_, const iterator_impl &last_)  {rotate_sequence_left_impl(first_, last_);}
  static void rotate_sequence_left_impl(const iterator_impl &first_, const iterator_impl &last_);
  PFC_INLINE friend void rotate_sequence_right(const iterator_impl &first_, const iterator_impl &last_)  {rotate_sequence_right_impl(first_, last_);}
  static void rotate_sequence_right_impl(const iterator_impl &first_, const iterator_impl &last_);
  //--------------------------------------------------------------------------

  deque<T> *m_deque;
  usize_t m_index;
};
//----------------------------------------------------------------------------


//============================================================================
// list
//============================================================================
template<typename T>
struct list_traits
{
  // properties
  enum {block_alloc_size=sizeof(typename list<T>::item),
        block_alloc_align=meta_alignof<typename list<T>::item>::res};
};
//----------------------------------------------------------------------------

template<typename T>
class list
{
  template<bool is_forward> class const_iterator_impl;
  template<bool is_forward> class iterator_impl;
public:
  // nested types
  typedef const_iterator_impl<true> const_iterator;
  typedef const_iterator_impl<false> const_reverse_iterator;
  typedef iterator_impl<true> iterator;
  typedef iterator_impl<false> reverse_iterator;
  //--------------------------------------------------------------------------

  // construction
  list(memory_allocator_base *alloc_=0);
  list(const list&);
  list(const list&, memory_allocator_base*);
  explicit list(usize_t size_, memory_allocator_base *alloc_=0);
  list(usize_t size_, const T&, memory_allocator_base *alloc_=0);
  PFC_INLINE ~list();
  void operator=(const list&);
  void set_allocator(memory_allocator_base*);
  void clear();
  void resize(usize_t size_);
  void resize(usize_t size_, const T&);
  PFC_INLINE void swap(list&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE memory_allocator_base &allocator() const;
  PFC_INLINE usize_t size() const;
  PFC_INLINE const T &front() const;
  PFC_INLINE T &front();
  PFC_INLINE const T &back() const;
  PFC_INLINE T &back();
  PFC_INLINE const_iterator begin() const;
  PFC_INLINE iterator begin();
  PFC_INLINE const_reverse_iterator rbegin() const;
  PFC_INLINE reverse_iterator rbegin();
  PFC_INLINE const_iterator last() const;
  PFC_INLINE iterator last();
  PFC_INLINE const_reverse_iterator rlast() const;
  PFC_INLINE reverse_iterator rlast();
  PFC_INLINE const_iterator end() const;
  PFC_INLINE iterator end();
  PFC_INLINE const_reverse_iterator rend() const;
  PFC_INLINE reverse_iterator rend();
  PFC_INLINE void push_front(const T&);
  PFC_INLINE T &push_front();
  PFC_INLINE void push_back(const T&);
  PFC_INLINE T &push_back();
  PFC_INLINE void insert_front(usize_t num_items_);
  PFC_INLINE void insert_front(usize_t num_items_, const T&);
  PFC_INLINE void insert_front(usize_t num_items_, const T*);
  PFC_INLINE void insert_front(const list<T>&);
  PFC_INLINE void insert_back(usize_t num_items_);
  PFC_INLINE void insert_back(usize_t num_items_, const T&);
  PFC_INLINE void insert_back(usize_t num_items_, const T*);
  PFC_INLINE void insert_back(const list<T>&);
  PFC_INLINE void insert_before(iterator&, const T&);
  PFC_INLINE T &insert_before(iterator&);
  PFC_INLINE void insert_after(iterator&, const T&);
  PFC_INLINE T &insert_after(iterator&);
  PFC_INLINE void splice_front(list&);
  PFC_INLINE void splice_front(iterator&);
  PFC_INLINE void splice_back(list&);
  PFC_INLINE void splice_back(iterator&);
  PFC_INLINE void pop_front();
  PFC_INLINE void pop_back();
  PFC_INLINE void remove_front(usize_t num_items_);
  PFC_INLINE void remove_back(usize_t num_items_);
  template<bool is_forward> PFC_INLINE void erase(iterator_impl<is_forward> &it_);
  //--------------------------------------------------------------------------

private:
  void cctor(const list&);
  template<bool is_forward> PFC_INLINE void detach(iterator_impl<is_forward>&);
  //--------------------------------------------------------------------------

  //==========================================================================
  // list::item
  //==========================================================================
  class item
  {
  public:
    T data;
    item *prev, *next;
    //------------------------------------------------------------------------

  private:
    item(); // not implemented
    void operator=(const item&); // not implemented
  };
  //--------------------------------------------------------------------------

  friend struct list_traits<T>;
  memory_allocator_base *m_allocator;
  usize_t m_size;
  item *m_first, *m_last;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, list<T>, is_type_pod_move, true);
//----------------------------------------------------------------------------

//============================================================================
// list::const_iterator_impl
//============================================================================
template<typename T>
template<bool is_forward>
class list<T>::const_iterator_impl
{
public:
  // nested types
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE const_iterator_impl();
  PFC_INLINE const_iterator_impl(const iterator_impl<is_forward>&);
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const const_iterator_impl &it_)  {return it_.m_item!=0;}
  PFC_INLINE bool operator==(const const_iterator_impl&) const;
  PFC_INLINE bool operator==(const iterator_impl<is_forward>&) const;
  PFC_INLINE bool operator!=(const const_iterator_impl&) const;
  PFC_INLINE bool operator!=(const iterator_impl<is_forward>&) const;
  PFC_INLINE const_iterator_impl &operator++();
  PFC_INLINE const_iterator_impl &operator--();
  PFC_INLINE const T &operator*() const;
  PFC_INLINE const T *operator->() const;
  PFC_INLINE friend const T *ptr(const const_iterator_impl &it_)   {return it_.m_item?&it_.m_item->data:0;}
  //--------------------------------------------------------------------------

private:
  friend class list<T>;
  friend class iterator_impl<is_forward>;
  PFC_INLINE const_iterator_impl(item*);
  //--------------------------------------------------------------------------

  item *m_item;
};
//----------------------------------------------------------------------------

//============================================================================
// list::iterator_impl
//============================================================================
template<typename T>
template<bool is_forward>
class list<T>::iterator_impl
{
public:
  // nested types
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE iterator_impl();
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const iterator_impl &it_)  {return it_.m_item!=0;}
  PFC_INLINE bool operator==(const const_iterator_impl<is_forward>&) const;
  PFC_INLINE bool operator==(const iterator_impl&) const;
  PFC_INLINE bool operator!=(const const_iterator_impl<is_forward>&) const;
  PFC_INLINE bool operator!=(const iterator_impl&) const;
  PFC_INLINE iterator_impl &operator++();
  PFC_INLINE iterator_impl &operator--();
  PFC_INLINE T &operator*() const;
  PFC_INLINE T *operator->() const;
  PFC_INLINE friend T *ptr(const iterator_impl &it_)         {return it_.m_item?&it_.m_item->data:0;}
  //--------------------------------------------------------------------------

private:
  friend class list<T>;
  friend class const_iterator_impl<is_forward>;
  PFC_INLINE iterator_impl(list&, item*);
  PFC_INLINE void detach();
  PFC_INLINE friend void rotate_sequence_left(iterator_impl &first_, iterator_impl &last_)  {rotate_sequence_left_impl(first_, last_);}
  static void rotate_sequence_left_impl(iterator_impl &first_, iterator_impl &last_);
  PFC_INLINE friend void rotate_sequence_right(iterator_impl &first_, iterator_impl &last_)  {rotate_sequence_right_impl(first_, last_);}
  static void rotate_sequence_right_impl(iterator_impl &first_, iterator_impl &last_);
  //--------------------------------------------------------------------------

  list *m_list;
  item *m_item;
};
//----------------------------------------------------------------------------


//============================================================================
// set
//============================================================================
template<typename T, class CmpPred=compare_predicate>
struct set_traits
{
  // properties
  enum {block_alloc_size=sizeof(typename set<T, CmpPred>::node),
        block_alloc_align=meta_alignof<typename set<T, CmpPred>::node>::res};
};
//----------------------------------------------------------------------------

template<typename T, class CmpPred>
class set
{
public:
  // nested types
  class const_iterator;
  class iterator;
  struct inserter {iterator it; bool is_new;};
  //--------------------------------------------------------------------------

  // construction
  set(const CmpPred &cmp_pred_=CmpPred(), memory_allocator_base *alloc_=0);
  set(const set&);
  set(const set&, memory_allocator_base*);
  PFC_INLINE ~set();
  void operator=(const set&);
  void set_allocator(memory_allocator_base*);
  void clear();
  PFC_INLINE void swap(set&);
  void validate_rb_state() const;
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE memory_allocator_base &allocator() const;
  PFC_INLINE usize_t size() const;
  template<typename K> PFC_INLINE const_iterator find(const K&) const;
  template<typename K> PFC_INLINE iterator find(const K&);
  template<typename K> PFC_INLINE const_iterator lower_bound(const K&) const;
  template<typename K> PFC_INLINE iterator lower_bound(const K&);
  template<typename K> PFC_INLINE const_iterator upper_bound(const K&) const;
  template<typename K> PFC_INLINE iterator upper_bound(const K&);
  PFC_INLINE const_iterator begin() const;
  PFC_INLINE iterator begin();
  PFC_INLINE const_iterator end() const;
  PFC_INLINE iterator end();
  template<typename K> inserter insert(const K&, bool replace_=true);
  void erase(iterator&);
  //--------------------------------------------------------------------------

private:
  class node;
  void cctor(const set&);
  void copy_subtree(node&, node *parent_, node *&child_ptr_);
  void destroy_subtree(node&);
  void rotate_subtree(node&, bool rotate_right_);
  void restore_rb_property_after_insert(node*);
  void restore_rb_property_after_remove(node*, node *parent_, bool is_left_child_);
  void validate_rb_state(node *n_, unsigned depth_, unsigned &max_depth_) const;
  //--------------------------------------------------------------------------

  //==========================================================================
  // set::node
  //==========================================================================
  class node
  {
  public:
    T data;
    char color; // 0=black, 1=red
    node *parent;
    node *children[2]; // 0=left, 1=right
    //------------------------------------------------------------------------

  private:
    node(); // not implemented
    void operator=(const node&); // not implemented
  };
  //--------------------------------------------------------------------------

  friend struct set_traits<T, CmpPred>;
  const CmpPred m_cmp_pred;
  memory_allocator_base *m_allocator;
  usize_t m_size;
  node *m_root;
};
PFC_SET_TYPE_TRAIT_PARTIAL2(typename T, class CmpPred, set<T, CmpPred>, is_type_pod_move, true);
//----------------------------------------------------------------------------

//============================================================================
// set::const_iterator
//============================================================================
template<typename T, class CmpPred>
class set<T, CmpPred>::const_iterator
{
public:
  // nested types
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE const_iterator();
  PFC_INLINE const_iterator(const iterator&);
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const const_iterator &it_)  {return it_.m_node!=0;}
  PFC_INLINE bool operator==(const const_iterator&) const;
  PFC_INLINE bool operator==(const iterator&) const;
  PFC_INLINE bool operator!=(const const_iterator&) const;
  PFC_INLINE bool operator!=(const iterator&) const;
  PFC_INLINE const_iterator &operator++();
  PFC_INLINE const T &operator*() const;
  PFC_INLINE const T *operator->() const;
  PFC_INLINE friend const T *ptr(const const_iterator &it_)   {return it_.m_node?&it_.m_node->data:0;}
  //--------------------------------------------------------------------------

private:
  friend class set<T, CmpPred>;
  PFC_INLINE const_iterator(const node*);
  //--------------------------------------------------------------------------

  const node *m_node;
};
//----------------------------------------------------------------------------

//============================================================================
// set::iterator
//============================================================================
template<typename T, class CmpPred>
class set<T, CmpPred>::iterator
{
public:
  // nested types
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE iterator();
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const iterator &it_)  {return it_.m_node!=0;}
  PFC_INLINE bool operator==(const const_iterator&) const;
  PFC_INLINE bool operator==(const iterator&) const;
  PFC_INLINE bool operator!=(const const_iterator&) const;
  PFC_INLINE bool operator!=(const iterator&) const;
  PFC_INLINE iterator &operator++();
  PFC_INLINE const T &operator*() const;
  PFC_INLINE const T *operator->() const;
  PFC_INLINE friend const T *ptr(const iterator &it_)   {return it_.m_node?&it_.m_node->data:0;}
  //--------------------------------------------------------------------------

private:
  friend class set<T, CmpPred>;
  friend class const_iterator;
  PFC_INLINE iterator(node*);
  //--------------------------------------------------------------------------

  node *m_node;
};
//----------------------------------------------------------------------------


//============================================================================
// map
//============================================================================
template<typename K, typename T, class CmpPred=compare_predicate>
struct map_traits
{
  // properties
  enum {block_alloc_size=sizeof(typename map<K, T, CmpPred>::node),
        block_alloc_align=meta_alignof<typename map<K, T, CmpPred>::node>::res};
};
//----------------------------------------------------------------------------

template<typename K, typename T, class CmpPred>
class map
{
public:
  // nested types
  class const_iterator;
  class iterator;
  struct inserter {iterator it; bool is_new;};
  //--------------------------------------------------------------------------

  // construction
  map(const CmpPred &cmp_pred_=CmpPred(), memory_allocator_base *alloc_=0);
  map(const map&);
  map(const map&, memory_allocator_base*);
  PFC_INLINE ~map();
  void operator=(const map&);
  void set_allocator(memory_allocator_base*);
  void clear();
  PFC_INLINE void swap(map&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE memory_allocator_base &allocator() const;
  PFC_INLINE usize_t size() const;
  template<typename K1> PFC_INLINE const T &operator[](const K1&) const;
  template<typename K1> PFC_INLINE T &operator[](const K1&);
  template<typename K1> PFC_INLINE const_iterator find(const K1&) const;
  template<typename K1> PFC_INLINE iterator find(const K1&);
  template<typename K1> PFC_INLINE const_iterator lower_bound(const K1&) const;
  template<typename K1> PFC_INLINE iterator lower_bound(const K1&);
  template<typename K1> PFC_INLINE const_iterator upper_bound(const K1&) const;
  template<typename K1> PFC_INLINE iterator upper_bound(const K1&);
  PFC_INLINE const_iterator begin() const;
  PFC_INLINE iterator begin();
  PFC_INLINE const_iterator end() const;
  PFC_INLINE iterator end();
  inserter insert(const K&, const T&, bool replace_=true);
  inserter insert(const K&, bool replace_=true);
  void erase(iterator&);
  //--------------------------------------------------------------------------

private:
  class node;
  void cctor(const map&);
  void copy_subtree(node&, node *parent_, node *&child_ptr_);
  void destroy_subtree(node&);
  void rotate_subtree(node&, bool rotate_right_);
  void restore_rb_property_after_insert(node*);
  void restore_rb_property_after_remove(node*, node *parent_, bool is_left_child_);
  //--------------------------------------------------------------------------

  //==========================================================================
  // map::node
  //==========================================================================
  class node
  {
  public:
    K key;
    T val;
    char color; // 0=black, 1=red
    node *parent;
    node *children[2]; // 0=left, 1=right
    //------------------------------------------------------------------------

  private:
    node(); // not implemented
    void operator=(const node&); // not implemented
  };
  //--------------------------------------------------------------------------

  friend struct map_traits<K, T, CmpPred>;
  const CmpPred m_cmp_pred;
  memory_allocator_base *m_allocator;
  usize_t m_size;
  node *m_root;
};
PFC_SET_TYPE_TRAIT_PARTIAL3(typename T, typename K, class CmpPred, map<K, T, CmpPred>, is_type_pod_move, true);
//----------------------------------------------------------------------------

//============================================================================
// map::const_iterator
//============================================================================
template<typename K, typename T, class CmpPred>
class map<K, T, CmpPred>::const_iterator
{
public:
  // nested types
  typedef K key_t;
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE const_iterator();
  PFC_INLINE const_iterator(const iterator&);
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const const_iterator &it_)  {return it_.m_node!=0;}
  PFC_INLINE bool operator==(const const_iterator&) const;
  PFC_INLINE bool operator==(const iterator&) const;
  PFC_INLINE bool operator!=(const const_iterator&) const;
  PFC_INLINE bool operator!=(const iterator&) const;
  PFC_INLINE const_iterator &operator++();
  PFC_INLINE const T &operator*() const;
  PFC_INLINE const T *operator->() const;
  PFC_INLINE friend const T *ptr(const const_iterator &it_)   {return it_.m_node?&it_.m_node->data.second:0;}
  PFC_INLINE const K &key() const;
  //--------------------------------------------------------------------------

private:
  friend class map<K, T, CmpPred>;
  PFC_INLINE const_iterator(const node*);
  //--------------------------------------------------------------------------

  const node *m_node;
};
//----------------------------------------------------------------------------

//============================================================================
// map::iterator
//============================================================================
template<typename K, typename T, class CmpPred>
class map<K, T, CmpPred>::iterator
{
public:
  // nested types
  typedef K key_t;
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE iterator();
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const iterator &it_)  {return it_.m_node!=0;}
  PFC_INLINE bool operator==(const const_iterator&) const;
  PFC_INLINE bool operator==(const iterator&) const;
  PFC_INLINE bool operator!=(const const_iterator&) const;
  PFC_INLINE bool operator!=(const iterator&) const;
  PFC_INLINE iterator &operator++();
  PFC_INLINE T &operator*() const;
  PFC_INLINE T *operator->() const;
  PFC_INLINE friend T *ptr(const iterator &it_)         {return it_.m_node?&it_.m_node->data.second:0;}
  PFC_INLINE const K &key() const;
  //--------------------------------------------------------------------------

private:
  friend class map<K, T, CmpPred>;
  friend class const_iterator;
  PFC_INLINE iterator(node*);
  //--------------------------------------------------------------------------

  node *m_node;
};
//----------------------------------------------------------------------------


//============================================================================
// hash_table_array
//============================================================================
template<typename T>
class hash_table_array
{
public:
  // nested types
  typedef typename array<T>::iterator iterator;
  typedef typename array<T>::const_iterator const_iterator;
  //--------------------------------------------------------------------------

  // hash table interface
  PFC_INLINE hash_table_array();
  PFC_INLINE usize_t size() const;
  PFC_INLINE usize_t prev_size() const;
  PFC_INLINE usize_t next_size() const;
  PFC_INLINE usize_t min_load_limit() const;
  PFC_INLINE usize_t max_load_limit() const;
  PFC_INLINE void resize(usize_t size_);
  PFC_INLINE void clear();
  PFC_INLINE void zero();
  PFC_INLINE const T &operator[](usize_t index_) const;
  PFC_INLINE T &operator[](usize_t index_);
  PFC_INLINE const_iterator begin() const;
  PFC_INLINE iterator begin();
  PFC_INLINE const_iterator end() const;
  PFC_INLINE iterator end();
  PFC_INLINE const_iterator at(usize_t index_) const;
  PFC_INLINE iterator at(usize_t index_);
  //--------------------------------------------------------------------------

private:
  array<T> m_table;
  usize_t m_index_mask;
};
//----------------------------------------------------------------------------


//============================================================================
// hash_table_sarray
//============================================================================
template<typename T, usize_t capacity>
class hash_table_sarray
{
public:
  // nested types
  typedef typename sarray<T, capacity>::iterator iterator;
  typedef typename sarray<T, capacity>::const_iterator const_iterator;
  //--------------------------------------------------------------------------

  // hash table interface
  PFC_INLINE hash_table_sarray();
  PFC_INLINE usize_t size() const;
  PFC_INLINE usize_t prev_size() const;
  PFC_INLINE usize_t next_size() const;
  PFC_INLINE usize_t min_load_limit() const;
  PFC_INLINE usize_t max_load_limit() const;
  PFC_INLINE void resize(usize_t size_);
  PFC_INLINE void clear();
  PFC_INLINE void zero();
  PFC_INLINE const T &operator[](usize_t index_) const;
  PFC_INLINE T &operator[](usize_t index_);
  PFC_INLINE const_iterator begin() const;
  PFC_INLINE iterator begin();
  PFC_INLINE const_iterator end() const;
  PFC_INLINE iterator end();
  PFC_INLINE const_iterator at(usize_t index_) const;
  PFC_INLINE iterator at(usize_t index_);
  //--------------------------------------------------------------------------

private:
  sarray<T, capacity> m_table;
};
//----------------------------------------------------------------------------


//============================================================================
// hash_table_deque
//============================================================================
template<typename T>
class hash_table_deque
{
public:
  // nested types
  typedef typename deque<T>::iterator iterator;
  typedef typename deque<T>::const_iterator const_iterator;
  //--------------------------------------------------------------------------

  // hash table interface
  PFC_INLINE hash_table_deque();
  PFC_INLINE usize_t size() const;
  PFC_INLINE usize_t prev_size() const;
  PFC_INLINE usize_t next_size() const;
  PFC_INLINE usize_t min_load_limit() const;
  PFC_INLINE usize_t max_load_limit() const;
  PFC_INLINE void resize(usize_t size_);
  PFC_INLINE void clear();
  PFC_INLINE void zero();
  PFC_INLINE const T &operator[](usize_t index_) const;
  PFC_INLINE T &operator[](usize_t index_);
  PFC_INLINE const_iterator begin() const;
  PFC_INLINE iterator begin();
  PFC_INLINE const_iterator end() const;
  PFC_INLINE iterator end();
  PFC_INLINE const_iterator at(usize_t index_) const;
  PFC_INLINE iterator at(usize_t index_);
  //--------------------------------------------------------------------------

private:
  deque<T> m_table;
  usize_t m_index_mask;
};
//----------------------------------------------------------------------------


//============================================================================
// hash_config
//============================================================================
template<class Func, template<class T> class Table>
struct hash_config
{
  typedef Func hash_func_t;
  template<typename U> struct hash_table_t: Table<U> {};
};
//----------------------------------------------------------------------------


//============================================================================
// hash_table_info
//============================================================================
struct hash_table_info
{
  usize_t num_slots;
  usize_t num_used_slots;
  usize_t num_collisions;
  usize_t max_slot_collisions;
};
//----------------------------------------------------------------------------


//============================================================================
// hash_set
//============================================================================
template<typename T, class Config=hash_config<hash_func<T> > >
struct hash_set_traits
{
  // properties
  enum {block_alloc_size=sizeof(typename hash_set<T, Config>::item),
        block_alloc_align=meta_alignof<typename hash_set<T, Config>::item>::res};
};
//----------------------------------------------------------------------------

template<typename T, class Config>
class hash_set
{
public:
  // nested types
  class const_iterator;
  class iterator;
  struct inserter {iterator it; bool is_new;};
  //--------------------------------------------------------------------------

  // construction
  hash_set(memory_allocator_base *alloc_=0);
  hash_set(const hash_set&);
  hash_set(const hash_set&, memory_allocator_base*);
  PFC_INLINE ~hash_set();
  void operator=(const hash_set&);
  void set_allocator(memory_allocator_base*);
  void clear();
  PFC_INLINE void swap(hash_set&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE memory_allocator_base &allocator() const;
  PFC_INLINE usize_t size() const;
  template<typename K> PFC_INLINE const_iterator find(const K&) const;
  template<typename K> PFC_INLINE iterator find(const K&);
  PFC_INLINE const_iterator begin() const;
  PFC_INLINE iterator begin();
  PFC_INLINE const_iterator end() const;
  PFC_INLINE iterator end();
  void collect_table_stats(hash_table_info&) const;
  template<typename K> PFC_INLINE inserter insert(const K&, bool replace_=true);
  void erase(iterator&);
  //--------------------------------------------------------------------------

private:
  void cctor(const hash_set&);
  void rehash(bool grow_);
  //--------------------------------------------------------------------------

  //==========================================================================
  // hash_set::item
  //==========================================================================
  class item
  {
  public:
    T data;
    item *next;
    //------------------------------------------------------------------------

  private:
    item(); // not implemented
    void operator=(const item&); // not implemented
  };
  //--------------------------------------------------------------------------

  friend struct hash_set_traits<T, Config>;
  typedef typename Config::hash_func_t hash_func_t;
  typedef typename Config::template hash_table_t<item*> hash_table_t;
  memory_allocator_base *m_allocator;
  usize_t m_rehash_size_min, m_rehash_size_max;
  usize_t m_size;
  hash_table_t m_hash_table;
};
PFC_SET_TYPE_TRAIT_PARTIAL2(typename T, class Config, hash_set<T, Config>, is_type_pod_move, true);
//----------------------------------------------------------------------------

//============================================================================
// hash_set::const_iterator
//============================================================================
template<typename T, class Config>
class hash_set<T, Config>::const_iterator
{
public:
  // nested types
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE const_iterator();
  PFC_INLINE const_iterator(const iterator&);
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const const_iterator &it_)  {return it_.m_item!=0;}
  PFC_INLINE bool operator==(const const_iterator&) const;
  PFC_INLINE bool operator==(const iterator&) const;
  PFC_INLINE bool operator!=(const const_iterator&) const;
  PFC_INLINE bool operator!=(const iterator&) const;
  PFC_INLINE const_iterator &operator++();
  PFC_INLINE const T &operator*() const;
  PFC_INLINE const T *operator->() const;
  PFC_INLINE friend const T *ptr(const const_iterator &it_)   {return it_.m_item?&it_.m_item->data:0;}
  //--------------------------------------------------------------------------

private:
  friend class hash_set<T, Config>;
  PFC_INLINE const_iterator(const hash_set&, const item*);
  void next_stride();
  //--------------------------------------------------------------------------

  const hash_set *m_hset;
  const item *m_item;
};
//----------------------------------------------------------------------------

//============================================================================
// hash_set::iterator
//============================================================================
template<typename T, class Config>
class hash_set<T, Config>::iterator
{
public:
  // nested types
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE iterator();
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const iterator &it_)  {return it_.m_item!=0;}
  PFC_INLINE bool operator==(const const_iterator&) const;
  PFC_INLINE bool operator==(const iterator&) const;
  PFC_INLINE bool operator!=(const const_iterator&) const;
  PFC_INLINE bool operator!=(const iterator&) const;
  PFC_INLINE iterator &operator++();
  PFC_INLINE const T &operator*() const;
  PFC_INLINE const T *operator->() const;
  PFC_INLINE friend const T *ptr(const iterator &it_)   {return it_.m_item?&it_.m_item->data:0;}
  //--------------------------------------------------------------------------

private:
  friend class hash_set<T, Config>;
  friend class const_iterator;
  PFC_INLINE iterator(hash_set&, item*, item **prev_);
  void next_stride();
  //--------------------------------------------------------------------------

  hash_set *m_hset;
  item *m_item;
  item **m_prev;
};
//----------------------------------------------------------------------------


//============================================================================
// hash_map
//============================================================================
template<typename K, typename T, class Config=hash_config<hash_func<K> > >
struct hash_map_traits
{
  // properties
  enum {block_alloc_size=sizeof(typename hash_map<K, T, Config>::item),
        block_alloc_align=meta_alignof<typename hash_map<K, T, Config>::item>::res};
};
//----------------------------------------------------------------------------

template<typename K, typename T, class Config>
class hash_map
{
public:
  // nested types
  class const_iterator;
  class iterator;
  struct inserter {iterator it; bool is_new;};
  //--------------------------------------------------------------------------

  // construction
  hash_map(memory_allocator_base *alloc_=0);
  hash_map(const hash_map&);
  hash_map(const hash_map&, memory_allocator_base*);
  PFC_INLINE ~hash_map();
  void operator=(const hash_map&);
  void set_allocator(memory_allocator_base*);
  void clear();
  PFC_INLINE void swap(hash_map&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE memory_allocator_base &allocator() const;
  PFC_INLINE usize_t size() const;
  PFC_INLINE const T &operator[](const K&) const;
  PFC_INLINE T &operator[](const K&);
  PFC_INLINE const_iterator find(const K&) const;
  PFC_INLINE iterator find(const K&);
  PFC_INLINE const_iterator begin() const;
  PFC_INLINE iterator begin();
  PFC_INLINE const_iterator end() const;
  PFC_INLINE iterator end();
  void collect_table_stats(hash_table_info&) const;
  inserter insert(const K&, const T&, bool replace_=true);
  inserter insert(const K&, bool replace_=true);
  void erase(iterator&);
  //--------------------------------------------------------------------------

private:
  void cctor(const hash_map&);
  void rehash(bool grow_);
  //--------------------------------------------------------------------------

  //==========================================================================
  // hash_map::item
  //==========================================================================
  class item
  {
  public:
    K key;
    T val;
    item *next;
    //------------------------------------------------------------------------

  private:
    item(); // not implemented
    void operator=(const item&); // not implemented
  };
  //--------------------------------------------------------------------------

  friend struct hash_map_traits<K, T, Config>;
  typedef typename Config::hash_func_t hash_func_t;
  typedef typename Config::template hash_table_t<item*> hash_table_t;
  memory_allocator_base *m_allocator;
  usize_t m_rehash_size_min, m_rehash_size_max;
  usize_t m_size;
  hash_table_t m_hash_table;
};
PFC_SET_TYPE_TRAIT_PARTIAL3(typename T, typename K, class Config, hash_map<K, T, Config>, is_type_pod_move, true);
//----------------------------------------------------------------------------

//============================================================================
// hash_map::const_iterator
//============================================================================
template<typename K, typename T, class Config>
class hash_map<K, T, Config>::const_iterator
{
public:
  // nested types
  typedef K key_t;
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE const_iterator();
  PFC_INLINE const_iterator(const iterator&);
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const const_iterator &it_)  {return it_.m_item!=0;}
  PFC_INLINE bool operator==(const const_iterator&) const;
  PFC_INLINE bool operator==(const iterator&) const;
  PFC_INLINE bool operator!=(const const_iterator&) const;
  PFC_INLINE bool operator!=(const iterator&) const;
  PFC_INLINE const_iterator &operator++();
  PFC_INLINE const T &operator*() const;
  PFC_INLINE const T *operator->() const;
  PFC_INLINE friend const T *ptr(const const_iterator &it_)   {return it_.m_item?&it_.m_item->val:0;}
  PFC_INLINE const K &key() const;
  //--------------------------------------------------------------------------

private:
  friend class hash_map<K, T, Config>;
  PFC_INLINE const_iterator(const hash_map&, const item*);
  void next_stride();
  //--------------------------------------------------------------------------

  const hash_map *m_hmap;
  const item *m_item;
};
//----------------------------------------------------------------------------

//============================================================================
// hash_map::iterator
//============================================================================
template<typename K, typename T, class Config>
class hash_map<K, T, Config>::iterator
{
public:
  // nested types
  typedef K key_t;
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE iterator();
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const iterator &it_)  {return it_.m_item!=0;}
  PFC_INLINE bool operator==(const const_iterator&) const;
  PFC_INLINE bool operator==(const iterator&) const;
  PFC_INLINE bool operator!=(const const_iterator&) const;
  PFC_INLINE bool operator!=(const iterator&) const;
  PFC_INLINE iterator &operator++();
  PFC_INLINE T &operator*() const;
  PFC_INLINE T *operator->() const;
  PFC_INLINE friend T *ptr(const iterator &it_)         {return it_.m_item?&it_.m_item->val:0;}
  PFC_INLINE const K &key() const;
  //--------------------------------------------------------------------------

private:
  friend class hash_map<K, T, Config>;
  friend class const_iterator;
  PFC_INLINE iterator(hash_map&, item*, item **prev_);
  void next_stride();
  //--------------------------------------------------------------------------

  hash_map *m_hmap;
  item *m_item;
  item **m_prev;
};
//----------------------------------------------------------------------------


//============================================================================
// hash_bimap
//============================================================================
template<typename K, typename T, class KConfig=hash_config<hash_func<K> >, class VConfig=hash_config<hash_func<T> > >
struct hash_bimap_traits
{
  // properties
  enum {block_alloc_size=sizeof(typename hash_bimap<K, T, KConfig, VConfig>::item),
        block_alloc_align=meta_alignof<typename hash_bimap<K, T, KConfig, VConfig>::item>::res};
};
//----------------------------------------------------------------------------

template<typename K, typename T, class KConfig, class VConfig>
class hash_bimap
{
public:
  // nested types
  class const_iterator;
  class iterator;
  struct inserter {const_iterator it; bool is_new;};
  //--------------------------------------------------------------------------

  // construction
  hash_bimap(memory_allocator_base *alloc_=0);
  hash_bimap(const hash_bimap&);
  hash_bimap(const hash_bimap&, memory_allocator_base*);
  PFC_INLINE ~hash_bimap();
  PFC_INLINE void operator=(const hash_bimap&);
  void set_allocator(memory_allocator_base*);
  void clear();
  PFC_INLINE void swap(hash_bimap&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE memory_allocator_base &allocator() const;
  PFC_INLINE usize_t size() const;
  PFC_INLINE const T &operator[](const K&) const;
  PFC_INLINE T &operator[](const K&);
  PFC_INLINE const_iterator find(const K&) const;
  PFC_INLINE iterator find(const K&);
  PFC_INLINE const_iterator find_val(const T&) const;
  PFC_INLINE iterator find_val(const T&);
  PFC_INLINE const_iterator begin() const;
  PFC_INLINE iterator begin();
  PFC_INLINE const_iterator end() const;
  PFC_INLINE iterator end();
  void collect_table_stats(hash_table_info &kinfo_, hash_table_info &vinfo_) const;
  inserter insert(const K&, const T&, bool replace_=true);
  //--------------------------------------------------------------------------

private:
  void cctor(const hash_bimap&);
  void rehash(bool grow_, bool rehash_ktable_, bool rehash_vtable_);
  //--------------------------------------------------------------------------

  //==========================================================================
  // hash_bimap::item
  //==========================================================================
  class item
  {
  public:
    K key;
    T val;
    item *next, *next_val;
    //------------------------------------------------------------------------

  private:
    item(); // not implemented
    void operator=(const item&); // not implemented
  };
  //--------------------------------------------------------------------------

  friend struct hash_bimap_traits<K, T, KConfig, VConfig>;
  typedef typename KConfig::hash_func_t hash_kfunc_t;
  typedef typename VConfig::hash_func_t hash_vfunc_t;
  typedef typename KConfig::template hash_table_t<item*> hash_ktable_t;
  typedef typename VConfig::template hash_table_t<item*> hash_vtable_t;
  memory_allocator_base *m_allocator;
  usize_t m_rehash_ksize_min, m_rehash_ksize_max;
  usize_t m_rehash_vsize_min, m_rehash_vsize_max;
  usize_t m_size;
  hash_ktable_t m_hash_ktable;
  hash_vtable_t m_hash_vtable;
};
PFC_SET_TYPE_TRAIT_PARTIAL4(typename T, typename K, class KConfig, class TConfig, hash_bimap<K, T, KConfig, TConfig>, is_type_pod_move, true);
//----------------------------------------------------------------------------

//============================================================================
// hash_bimap::const_iterator
//============================================================================
template<typename K, typename T, class KConfig, class VConfig>
class hash_bimap<K, T, KConfig, VConfig>::const_iterator
{
public:
  // construction
  PFC_INLINE const_iterator();
  PFC_INLINE const_iterator(const iterator&);
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const const_iterator &it_)  {return it_.m_item!=0;}
  PFC_INLINE bool operator==(const const_iterator&) const;
  PFC_INLINE bool operator==(const iterator&) const;
  PFC_INLINE bool operator!=(const const_iterator&) const;
  PFC_INLINE bool operator!=(const iterator&) const;
  PFC_INLINE const_iterator &operator++();
  PFC_INLINE const_iterator &next_val();
  PFC_INLINE const T &operator*() const;
  PFC_INLINE const T *operator->() const;
  PFC_INLINE friend const T *ptr(const const_iterator &it_)   {return it_.m_item?&it_.m_item->value.second:0;}
  PFC_INLINE const K &key() const;
  //--------------------------------------------------------------------------

private:
  friend class hash_bimap<K, T, KConfig, VConfig>;
  PFC_INLINE const_iterator(const hash_bimap&, const item*);
  void next_kstride();
  void next_vstride();
  //--------------------------------------------------------------------------

  const hash_bimap *m_hmap;
  const item *m_item;
};
//----------------------------------------------------------------------------

//============================================================================
// hash_bimap::iterator
//============================================================================
template<typename K, typename T, class KConfig, class VConfig>
class hash_bimap<K, T, KConfig, VConfig>::iterator
{
public:
  // nested types
  typedef K key_t;
  typedef T value_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE iterator();
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE friend bool is_valid(const iterator &it_)  {return it_.m_item!=0;}
  PFC_INLINE bool operator==(const const_iterator&) const;
  PFC_INLINE bool operator==(const iterator&) const;
  PFC_INLINE bool operator!=(const const_iterator&) const;
  PFC_INLINE bool operator!=(const iterator&) const;
  PFC_INLINE iterator &operator++();
  PFC_INLINE iterator &next_val();
  PFC_INLINE const T &operator*() const;
  PFC_INLINE const T *operator->() const;
  PFC_INLINE friend const T *ptr(const iterator &it_)   {return it_.m_item?&it_.m_item->value.second:0;}
  PFC_INLINE const K &key() const;
  PFC_INLINE void remove();
  PFC_INLINE void remove_val();
  //--------------------------------------------------------------------------

private:
  friend class hash_bimap<K, T, KConfig, VConfig>;
  friend class const_iterator;
  PFC_INLINE iterator(hash_bimap&, item*, item **prev_, item **prev_val_);
  void next_kstride();
  void next_vstride();
  //--------------------------------------------------------------------------

  hash_bimap *m_hmap;
  item *m_item;
  item **m_prev, **m_prev_val;
};
//----------------------------------------------------------------------------

//============================================================================
#include "containers.inl"
} // namespace pfc
#endif
