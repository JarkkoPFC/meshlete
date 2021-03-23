//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================


//============================================================================
// radix_sort
//============================================================================
template<typename Iterator>
void radix_sort(Iterator seq_, Iterator tmp_seq_, usize_t num_values_)
{
  typedef typename iterator_trait<Iterator>::value_t value_t;
  radix_sort(seq_, tmp_seq_, num_values_, radix_sort_predicate<value_t>());
}
//----

template<typename Iterator, class Predicate>
void radix_sort(Iterator seq_, Iterator tmp_seq_, usize_t num_values_, Predicate pred_)
{
  // check inputs
  typedef typename iterator_trait<Iterator>::value_t value_t;
  PFC_ASSERT_MSG(is_valid(seq_), ("Input/output sequence not defined\r\n"));
  PFC_ASSERT_MSG(is_valid(tmp_seq_), ("Temporal storage sequence not defined\r\n"));
  enum {radix_range=Predicate::radix_range};
  enum {radix_passes=Predicate::radix_passes};
  PFC_CTF_ASSERT_MSG(radix_passes>0, number_of_radix_passes_must_be_greater_than_zero);
  PFC_CTF_ASSERT_MSG(radix_range>0, radix_range_must_be_greater_than_zero);

  // perform radix sort in multiple passes over the data
  unsigned indices[radix_range];
  Iterator src=seq_, dst=tmp_seq_;
  for(unsigned pass=0; pass<radix_passes; ++pass)
  {
    // count number of each radix
    mem_zero(indices, sizeof(indices));
    Iterator it=src;
    for(usize_t i=0; i<num_values_; ++i)
    {
      unsigned radix=pred_.radix(*it, pass);
      ++it;
      PFC_ASSERT_PEDANTIC_MSG(radix<radix_range, ("Radix out of range\r\n"));
      ++indices[radix];
    }

    // setup radix indices
    unsigned index=0;
    for(unsigned i=0; i<radix_range; ++i)
    {
      unsigned size=indices[i];
      indices[i]=index;
      index+=size;
    }

    // sort values to the destination buffer
    it=src;
    for(usize_t i=0; i<num_values_; ++i)
    {
      const value_t &v=*it;
      unsigned radix=pred_.radix(v, pass);
      dst[indices[radix]++]=v;
      ++it;
    }

    // swap destination and source buffers
    it=src;
    src=dst;
    dst=it;
  }

  // for odd number of passes, copy data to destination
  if(radix_passes&1)
    for(usize_t i=0; i<num_values_; ++i)
    {
      *dst=*src;
      ++dst;
      ++src;
    }
}
//----------------------------------------------------------------------------


//============================================================================
// insertion_sort
//============================================================================
template<typename Iterator, class Predicate>
void insertion_sort_impl(Iterator seq_, usize_t num_values_, Predicate pred_)
{
  // perform insertion sort of the sequence
  typedef typename iterator_trait<Iterator>::value_t value_t;
  Iterator it=seq_;
  ++it;
  for(usize_t i=1; i<num_values_; ++i)
  {
    // check if value needs to be moved from its current place
    value_t &lhv=*it;
    Iterator sit=it;
    --sit;
    if(pred_.before(lhv, *sit))
    {
      // find new place for the value
      while(sit!=seq_)
      {
        --sit;
        if(!pred_.before(lhv, *sit))
        {
          ++sit;
          break;
        }
      }

      // rotate data sequence to proper order
      rotate_sequence_right(sit==seq_?seq_:sit, it);
    }
    ++it;
  }
}
//----

template<typename Iterator>
void insertion_sort(Iterator seq_, usize_t num_values_)
{
  // check for input and sort the sequence
  typedef typename iterator_trait<Iterator>::value_t value_t;
  if(!num_values_)
    return;
  PFC_ASSERT_MSG(is_valid(seq_), ("Destination sequence not defined\r\n"));
  insertion_sort_impl(seq_, num_values_, compare_sort_predicate<value_t>());
}
//----

template<typename Iterator, class Predicate>
void insertion_sort(Iterator seq_, usize_t num_values_, Predicate pred_)
{
  // check for input and sort the sequence
  if(!num_values_)
    return;
  PFC_ASSERT_MSG(is_valid(seq_), ("Destination sequence not defined\r\n"));
  insertion_sort_impl(seq_, num_values_, pred_);
}
//----------------------------------------------------------------------------


//============================================================================
// quick_sort
//============================================================================
template<typename Iterator, class Predicate>
void quick_sort_impl(Iterator seq_, usize_t num_values_, Predicate pred_)
{
  // check if sorting is needed
  enum {qsort_threshold=10};
  if(num_values_<=1)
    return;

  // setup initial iterators & swap pivot item with the last item
  typedef typename iterator_trait<Iterator>::value_t value_t;
  Iterator end=seq_+num_values_-1;
  Iterator pivot=seq_+((num_values_-1)>>1);
  swap(*end, *pivot);
  pivot=end;
  Iterator small_arr=seq_, large_arr=end-1;
  usize_t small_idx=0, large_idx=num_values_-2;

  // recursive quick sort of the array
  while(true)
  {
    // advance small and large item pointers
    while(pred_.before(*small_arr, *pivot))
    {
      ++small_arr;
      ++small_idx;
    }
    while(small_idx<large_idx && !pred_.before(*large_arr, *pivot))
    {
      --large_arr;
      --large_idx;
    }

    // check for end of partitioning
    if(small_idx>=large_idx)
    {
      // restore pivot item to its correct place
      large_arr=small_arr;
      large_idx=small_idx;
      swap(*small_arr, *pivot);

      // check for optimized sort for short small-item array
      if(small_idx<qsort_threshold)
        insertion_sort_impl(seq_, small_idx, pred_);
      else
        quick_sort_impl(seq_, small_idx, pred_);

      // check for optimized sort for short large-item array
      usize_t num_large_items=num_values_-1-large_idx;
      ++large_arr;
      ++large_idx;
      if(num_large_items<qsort_threshold)
        insertion_sort_impl(large_arr, num_large_items, pred_);
      else
        quick_sort_impl(large_arr, num_large_items, pred_);
      return;
    }

    // swap small & large items
    swap(*small_arr, *large_arr);
    ++small_arr;
    ++small_idx;
    --large_arr;
    --large_idx;
  }
}
//----

template<typename Iterator>
void quick_sort(Iterator seq_, usize_t num_values_)
{
  // check for input and sort the sequence
  PFC_ASSERT_MSG(is_valid(seq_) || !num_values_, ("Destination sequence not defined\r\n"));
  typedef typename iterator_trait<Iterator>::value_t value_t;
  quick_sort_impl(seq_, num_values_, compare_sort_predicate<value_t>());
}
//----

template<typename Iterator, class Predicate>
void quick_sort(Iterator seq_, usize_t num_values_, Predicate pred_)
{
  // check for input and sort the sequence
  PFC_ASSERT_MSG(is_valid(seq_) || !num_values_, ("Destination sequence not defined\r\n"));
  quick_sort_impl(seq_, num_values_, pred_);
}
//----------------------------------------------------------------------------


//============================================================================
// merge_sort
//============================================================================
template<typename Iterator, class Predicate>
void merge_sort_impl(Iterator seq_, usize_t num_values_, Predicate pred_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
}
//----

template<typename Iterator>
void merge_sort(Iterator seq_, usize_t num_values_)
{
  // check for input and sort the sequence
  PFC_ASSERT_MSG(is_valid(seq_) || !num_values_, ("Destination sequence not defined\r\n"));
  typedef typename iterator_trait<Iterator>::value_t value_t;
  merge_sort_impl(seq_, num_values_, compare_sort_predicate<value_t>());
}
//----

template<typename Iterator, class Predicate>
void merge_sort(Iterator seq_, usize_t num_values_, Predicate pred_)
{
  // check for input and sort the sequence
  PFC_ASSERT_MSG(is_valid(seq_) || !num_values_, ("Destination sequence not defined\r\n"));
  merge_sort_impl(seq_, num_values_, pred_);
}
//----------------------------------------------------------------------------


//============================================================================
// linear_search
//============================================================================
template<typename Iterator, typename U>
PFC_INLINE Iterator linear_search(Iterator seq_, Iterator end_, const U &value_)
{
  return linear_search(seq_, end_, value_, search_predicate<typename iterator_trait<Iterator>::value_t, U>());
}
//----

template<typename Iterator, typename U, class Predicate>
Iterator linear_search(Iterator seq_, Iterator end_, const U &value_, Predicate pred_)
{
  // check for empty sequence
  if(seq_==end_)
    return Iterator();

  // linearly search the value in the sequence
  do
  {
    if(pred_.equal(*seq_, value_))
      return seq_;
    ++seq_;
  } while(seq_!=end_);
  return Iterator();
}
//----

template<typename Iterator, typename U>
PFC_INLINE Iterator linear_search(Iterator seq_, usize_t num_values_, const U &value_)
{
  return linear_search(seq_, num_values_, value_, search_predicate<typename iterator_trait<Iterator>::value_t, U>());
}
//----

template<typename Iterator, typename U, class Predicate>
Iterator linear_search(Iterator seq_, usize_t num_values_, const U &value_, Predicate pred_)
{
  // check for no values
  if(!num_values_)
    return Iterator();

  // linearly search the value in the sequence
  do 
  {
    if(pred_.equal(*seq_, value_))
      return seq_;
    ++seq_;
  } while (--num_values_);
  return Iterator();
}
//----------------------------------------------------------------------------


//============================================================================
// binary_search
//============================================================================
template<typename Iterator, typename U>
PFC_INLINE Iterator binary_search(Iterator seq_, usize_t num_values_, const U &value_)
{
  return binary_search(seq_, num_values_, value_, search_predicate<typename iterator_trait<Iterator>::value_t, U>());
}
//----

template<typename Iterator, typename U, class Predicate>
Iterator binary_search(Iterator seq_, usize_t num_values_, const U &value_, Predicate pred_)
{
  // check for empty sequence
  PFC_ASSERT(!num_values_ || is_valid(seq_));
  if(!num_values_)
    return Iterator();

  // single comparison per iteration binary search
  usize_t low=0, high=num_values_;
  do
  {
    usize_t mid=low+((high-low)>>1);
    if(pred_.before(seq_[mid], value_))
      low=mid+1;
    else
      high=mid;
  } while(low<high);
  return (low<num_values_ && pred_.equal(seq_[low], value_))?seq_+int(low):Iterator();
}
//----------------------------------------------------------------------------


//============================================================================
// binary_search_lower_bound
//============================================================================
template<typename Iterator, typename U>
PFC_INLINE Iterator binary_search_lower_bound(Iterator seq_, usize_t num_values_, const U &value_)
{
  return binary_search_lower_bound(seq_, num_values_, value_, search_predicate<typename iterator_trait<Iterator>::value_t, U>());
}
//----

template<typename Iterator, typename U, class Predicate>
Iterator binary_search_lower_bound(Iterator seq_, usize_t num_values_, const U &value_, Predicate pred_)
{
  // check for empty sequence
  PFC_ASSERT(!num_values_ || is_valid(seq_));
  if(!num_values_)
    return Iterator();

  // single comparison per iteration binary search
  usize_t low=0, high=num_values_;
  do
  {
    usize_t mid=low+((high-low)>>1);
    if(pred_.before(seq_[mid], value_))
      low=mid+1;
    else
      high=mid;
  } while(low<high);
  return (low<num_values_ && pred_.equal(seq_[low], value_))?seq_+int(low):low?seq_+int(low-1):Iterator();
}
//----------------------------------------------------------------------------


//============================================================================
// binary_search_upper_bound
//============================================================================
template<typename Iterator, typename U>
PFC_INLINE Iterator binary_search_upper_bound(Iterator seq_, usize_t num_values_, const U &value_)
{
  return binary_search_upper_bound(seq_, num_values_, value_, search_predicate<typename iterator_trait<Iterator>::value_t, U>());
}
//----

template<typename Iterator, typename U, class Predicate>
Iterator binary_search_upper_bound(Iterator seq_, usize_t num_values_, const U &value_, Predicate pred_)
{
  // check for empty sequence
  PFC_ASSERT(!num_values_ || is_valid(seq_));
  if(!num_values_)
    return Iterator();

  // single comparison per iteration binary search
  usize_t low=0, high=num_values_;
  do
  {
    usize_t mid=low+((high-low)>>1);
    if(pred_.before(seq_[mid], value_))
      low=mid+1;
    else
      high=mid;
  } while(low<high);
  return low<num_values_?seq_+int(low):Iterator();
}
//----------------------------------------------------------------------------


//============================================================================
// find_min
//============================================================================
template<typename Iterator>
PFC_INLINE Iterator find_min(Iterator seq_, Iterator end_)
{
  typedef typename iterator_trait<Iterator>::value_t value_t;
  return find_min(seq_, end_, search_predicate<value_t, value_t>());
}
//----

template<typename Iterator, class Predicate>
Iterator find_min(Iterator seq_, Iterator end_, Predicate pred_)
{
  // check for empty sequence
  if(seq_==end_)
    return Iterator();

  // search for the minimum value in the sequence
  Iterator min_it=seq_;
  ++seq_;
  if(seq_!=end_)
    do
    {
      if(pred_.before(*seq_, *min_it))
        min_it=seq_;
      ++seq_;
    } while(seq_!=end_);
  return min_it;
}
//----

template<typename Iterator>
PFC_INLINE Iterator find_min(Iterator seq_, usize_t num_values_)
{
  typedef typename iterator_trait<Iterator>::value_t value_t;
  return find_min(seq_, num_values_, search_predicate<value_t, value_t>());
}
//----

template<typename Iterator, class Predicate>
Iterator find_min(Iterator seq_, usize_t num_values_, Predicate pred_)
{
  // check for empty sequence
  if(!num_values_)
    return Iterator();

  // search for the minimum value in the sequence
  Iterator min_it=seq_;
  ++seq_;
  if(--num_values_)
    do
    {
      if(pred_.before(*seq_, *min_it))
        min_it=seq_;
      ++seq_;
    } while(--num_values_);
  return min_it;
}
//----------------------------------------------------------------------------


//============================================================================
// find_max
//============================================================================
template<typename Iterator>
PFC_INLINE Iterator find_max(Iterator seq_, Iterator end_)
{
  typedef typename iterator_trait<Iterator>::value_t value_t;
  return find_max(seq_, end_, search_predicate<value_t, value_t>());
}
//----

template<typename Iterator, class Predicate>
Iterator find_max(Iterator seq_, Iterator end_, Predicate pred_)
{
  // check for empty sequence
  if(seq_==end_)
    return Iterator();

  // search for the maximum value in the sequence
  Iterator max_it=seq_;
  ++seq_;
  if(seq_!=end_)
    do
    {
      if(pred_.before(*max_it, *seq_))
        max_it=seq_;
      ++seq_;
    } while(seq_!=end_);
  return max_it;
}
//----

template<typename Iterator>
PFC_INLINE Iterator find_max(Iterator seq_, usize_t num_values_)
{
  typedef typename iterator_trait<Iterator>::value_t value_t;
  return find_max(seq_, num_values_, search_predicate<value_t, value_t>());
}
//----

template<typename Iterator, class Predicate>
Iterator find_max(Iterator seq_, usize_t num_values_, Predicate pred_)
{
  // check for empty sequence
  if(!num_values_)
    return Iterator();

  // search for the maximum value in the sequence
  Iterator max_it=seq_;
  ++seq_;
  if(--num_values_)
    do
    {
      if(pred_.before(*max_it, *seq_))
        max_it=seq_;
      ++seq_;
    } while(--num_values_);
  return max_it;
}
//----------------------------------------------------------------------------


//============================================================================
// radix_sort_predicate
//============================================================================
template<typename T, bool ascending_>
unsigned radix_sort_predicate<T, ascending_>::radix(T v_, unsigned pass_) const
{
  typedef typename meta_type_array<int8_t, int16_t, int32_t, int64_t>::get<meta_log2<sizeof(T)>::res>::res cast_type;
  return ((ascending_?(cast_type&)v_:-(cast_type&)v_)>>(pass_*8))&0xff;
}
//----------------------------------------------------------------------------


//============================================================================
// compare_sort_predicate
//============================================================================
template<typename T, bool ascending_>
bool compare_sort_predicate<T, ascending_>::before(const T &v0_, const T &v1_) const
{
  return ascending_?v0_<v1_:v1_<v0_;
}
//----------------------------------------------------------------------------


//============================================================================
// search_predicate
//============================================================================
template<typename T, typename U>
bool search_predicate<T, U>::before(const T &v0_, const U &v1_) const
{
  return v0_<v1_;
}
//----

template<typename T, typename U>
bool search_predicate<T, U>::equal(const T &v0_, const U &v1_) const
{
  return v0_==v1_;
}
//----------------------------------------------------------------------------


//============================================================================
// cstr_search_predicate
//============================================================================
bool cstr_search_predicate::before(const char *str0_, const char *str1_) const
{
  return str_diff(str0_, str1_)<0;
}
//----

bool cstr_search_predicate::equal(const char *str0_, const char *str1_) const
{
  return str_eq(str0_, str1_);
}
//----------------------------------------------------------------------------
