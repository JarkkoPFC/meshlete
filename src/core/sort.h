//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_SORT_H
#define PFC_CORE_SORT_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core/iterators.h"
#include "core/utils.h"
#include "core/cstr.h"
namespace pfc
{

// new
// sort functions
template<typename Iterator> void radix_sort(Iterator seq_, Iterator tmp_seq_, usize_t num_values_);
template<typename Iterator, class Predicate> void radix_sort(Iterator seq_ , Iterator tmp_seq_, usize_t num_values_, Predicate);
template<typename Iterator> void insertion_sort(Iterator seq_, usize_t num_values_);
template<typename Iterator, class Predicate> void insertion_sort(Iterator seq_, usize_t num_values_, Predicate);
template<typename Iterator> void quick_sort(Iterator seq_, usize_t num_values_);
template<typename Iterator, class Predicate> void quick_sort(Iterator seq_, usize_t num_values_, Predicate);
template<typename Iterator> void merge_sort(Iterator seg_, usize_t num_values_);
template<typename Iterator, class Predicate> void merge_sort(Iterator seg_, usize_t num_values_, Predicate);
// search functions
template<typename Iterator, typename U> PFC_INLINE Iterator linear_search(Iterator seq_, Iterator end_, const U&); // linearly search value from a sequence of (unsorted) values: O(n)
template<typename Iterator, typename U, class Predicate> Iterator linear_search(Iterator seq_, Iterator end_, const U&, Predicate);
template<typename Iterator, typename U> PFC_INLINE Iterator linear_search(Iterator seq_, usize_t num_values_, const U&);
template<typename Iterator, typename U, class Predicate> Iterator linear_search(Iterator seq_, usize_t num_values_, const U&, Predicate);
template<typename Iterator, typename U> PFC_INLINE Iterator binary_search(Iterator seq_, usize_t num_values_, const U&); // binary search value from a sorted sequence of values: O(log2(n))
template<typename Iterator, typename U, class Predicate> Iterator binary_search(Iterator seq_, usize_t num_values_, const U&, Predicate);
template<typename Iterator, typename U> PFC_INLINE Iterator binary_search_lower_bound(Iterator seg_, usize_t num_values_, const U&); // binary search value from a sorted sequence of values (return lower-bound value): O(log2(n))
template<typename Iterator, typename U, class Predicate> Iterator binary_search_lower_bound(Iterator seq_, usize_t num_values_, const U&, Predicate);
template<typename Iterator, typename U> PFC_INLINE Iterator binary_search_upper_bound(Iterator seg_, usize_t num_values_, const U&); // binary search value from a sorted sequence of values (return upper-bound value): O(log2(n))
template<typename Iterator, typename U, class Predicate> Iterator binary_search_upper_bound(Iterator seq_, usize_t num_values_, const U&, Predicate);
template<typename Iterator> PFC_INLINE Iterator find_min(Iterator seq_, Iterator end_);
template<typename Iterator, class Predicate> Iterator find_min(Iterator seq_, Iterator end_, Predicate);
template<typename Iterator> PFC_INLINE Iterator find_min(Iterator seq_, usize_t num_values_);
template<typename Iterator, class Predicate> Iterator find_min(Iterator seq_, usize_t num_values_, Predicate);
template<typename Iterator> PFC_INLINE Iterator find_max(Iterator seq_, Iterator end_);
template<typename Iterator, class Predicate> Iterator find_max(Iterator seq_, Iterator end_, Predicate);
template<typename Iterator> PFC_INLINE Iterator find_max(Iterator seq_, usize_t num_values_);
template<typename Iterator, class Predicate> Iterator find_max(Iterator seq_, usize_t num_values_, Predicate);
// predicates
template<typename T, bool ascending_=true> struct radix_sort_predicate;
template<typename T, bool ascending_=true> struct compare_sort_predicate;
template<typename T, typename U=T> struct search_predicate;
struct cstr_search_predicate;
//----------------------------------------------------------------------------


//============================================================================
// radix_sort_predicate
//============================================================================
template<typename T, bool ascending_>
struct radix_sort_predicate
{ PFC_CTC_ASSERT_MSG(!is_type_class<T>::res, radix_sort_predicate_not_usable_for_class_types);
  // radix sort predicate interface
  enum {radix_passes=sizeof(T)};
  enum {radix_range=256};
  PFC_INLINE unsigned radix(T, unsigned pass_) const;
};
//----------------------------------------------------------------------------


//============================================================================
// compare_sort_predicate
//============================================================================
template<typename T, bool ascending_>
struct compare_sort_predicate
{
  // compare sort predicate interface
  PFC_INLINE bool before(const T&, const T&) const;
};
//----------------------------------------------------------------------------


//============================================================================
// search_predicate
//============================================================================
template<typename T, typename U>
struct search_predicate
{
  // search predicate interface
  PFC_INLINE bool before(const T&, const U&) const;
  PFC_INLINE bool equal(const T&, const U&) const;
};
//----------------------------------------------------------------------------


//============================================================================
// cstr_search_predicate
//============================================================================
struct cstr_search_predicate
{
  // c-string search predicate interface
  PFC_INLINE bool before(const char*, const char*) const;
  PFC_INLINE bool equal(const char*, const char*) const;
};
//----------------------------------------------------------------------------

//============================================================================
#include "sort.inl"
} // namespace pfc
#endif
