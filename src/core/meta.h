//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_META_H
#define PFC_CORE_META_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core.h"
namespace pfc
{

// new
// type traits
template<typename> struct is_type_fund;          // fundamental types: char, int, float, etc.
template<typename> struct is_type_int;           // fundamental integral types: unsigned char, int, etc.
template<typename> struct is_type_float;         // fundamental float types: float, double, etc.
template<typename> struct is_type_signed;        // fundamental signed types: char, int, float, etc.
template<typename> struct is_type_unsigned;      // fundamental unsigned types: unsigned char, unsigned int, etc.
template<typename> struct is_type_ptr;           // pointers: char*, const void*, etc.
template<typename> struct is_type_array;         // c arrays: char[], int[4], etc.
template<typename> struct is_type_ref;           // references: char&, const int&, etc.
template<typename> struct is_type_enum;          // enumerations
template<typename> struct is_type_const;         // const types: const char, void *const, etc.
template<typename> struct is_type_volatile;      // volatile types: volatile char, void *volatile, etc.
template<typename> struct is_type_cv;            // const-volatile types: const volatile char, etc.
template<typename> struct is_type_class;         // class/struct types
template<typename> struct is_type_union;         // rs: unions
template<typename> struct is_type_pod;           // rs: plain-old-data (POD) types (enables all POD traits, except streaming)
template<typename> struct is_type_pod_def_ctor;  // rs: POD semantics for default ctor (can be initialized with mem_zero() without call to default-ctor)
template<typename> struct is_type_pod_dtor;      // rs: POD semantics for default dtor (can be deleted without call to destructor)
template<typename> struct is_type_pod_move;      // rs: POD semantics for memory moves (can be moved with mem_copy() without calls to copy-ctor/dtor)
template<typename> struct is_type_pod_copy;      // rs: POD semantics for copying (can be copied with mem_copy() without call to copy-ctor)
template<typename> struct is_type_pod_stream;    // rs: POD semantics for streaming (can be read/written from/to binary stream as plain data)
template<typename> struct is_type_copyable;      // rs: public copy-constructor
template<typename> struct is_type_mono;          // monomorphic types (types without v-table)
template<typename> struct is_type_poly;          // polymorphic types (classes with v-table)
template<typename> struct is_type_abstract;      // abstract classes (i.e. classes with pure-virtual functions)
#define PFC_SET_TYPE_TRAIT(type__, trait__, value__)  template<> struct trait__<type__ > {enum{res=value__};};\
                                                      template<> struct trait__<const type__ > {enum{res=value__};};\
                                                      template<> struct trait__<volatile type__ > {enum{res=value__};};\
                                                      template<> struct trait__<const volatile type__ > {enum{res=value__};};
#define PFC_SET_TYPE_TRAIT2(type__, trait0__, trait1__, value__) PFC_SET_TYPE_TRAIT(type__, trait0__, value__); PFC_SET_TYPE_TRAIT(type__, trait1__, value__);
#define PFC_SET_TYPE_TRAIT3(type__, trait0__, trait1__, trait2__, value__) PFC_SET_TYPE_TRAIT2(type__, trait0__, trait1__, value__); PFC_SET_TYPE_TRAIT(type__, trait2__, value__);
#define PFC_SET_TYPE_TRAIT4(type__, trait0__, trait1__, trait2__, trait3__, value__) PFC_SET_TYPE_TRAIT2(type__, trait0__, trait1__, value__); PFC_SET_TYPE_TRAIT2(type__, trait2__, trait3__, value__);
#define PFC_SET_TYPE_TRAIT5(type__, trait0__, trait1__, trait2__, trait3__, trait4__, value__) PFC_SET_TYPE_TRAIT4(type__, trait0__, trait1__, trait2__, trait3__, value__); PFC_SET_TYPE_TRAIT(type__, trait4__, value__);
#define PFC_SET_TYPE_TRAIT6(type__, trait0__, trait1__, trait2__, trait3__, trait4__, trait5__, value__) PFC_SET_TYPE_TRAIT4(type__, trait0__, trait1__, trait2__, trait3__, value__); PFC_SET_TYPE_TRAIT2(type__, trait4__, trait5__, value__);
#define PFC_SET_TYPE_TRAIT7(type__, trait0__, trait1__, trait2__, trait3__, trait4__, trait5__, trait6__, value__) PFC_SET_TYPE_TRAIT4(type__, trait0__, trait1__, trait2__, trait3__, value__); PFC_SET_TYPE_TRAIT3(type__, trait4__, trait5__, trait6__, value__);
#define PFC_SET_TYPE_TRAIT8(type__, trait0__, trait1__, trait2__, trait3__, trait4__, trait5__, trait6__, trait7__, value__) PFC_SET_TYPE_TRAIT4(type__, trait0__, trait1__, trait2__, trait3__, value__); PFC_SET_TYPE_TRAIT4(type__, trait4__, trait5__, trait6__, trait7__, value__);
#define PFC_SET_TYPE_TRAIT9(type__, trait0__, trait1__, trait2__, trait3__, trait4__, trait5__, trait6__, trait7__, trait8__, value__) PFC_SET_TYPE_TRAIT8(type__, trait0__, trait1__, trait2__, trait3__, trait4__, trait5__, trait6__, trait7__, value__); PFC_SET_TYPE_TRAIT(type__, trait8__, value__);
#define PFC_SET_TYPE_TRAIT10(type__, trait0__, trait1__, trait2__, trait3__, trait4__, trait5__, trait6__, trait7__, trait8__, trait9__, value__) PFC_SET_TYPE_TRAIT8(type__, trait0__, trait1__, trait2__, trait3__, trait4__, trait5__, trait6__, trait7__, value__); PFC_SET_TYPE_TRAIT2(type__, trait8__, trait9__, value__);
#define PFC_SET_TYPE_TRAIT_PARTIAL(t0__, type__, trait__, value__)\
                                                template<t0__> struct trait__<type__ > {enum{res=value__};};\
                                                template<t0__> struct trait__<const type__ > {enum{res=value__};};\
                                                template<t0__> struct trait__<volatile type__ > {enum{res=value__};};\
                                                template<t0__> struct trait__<const volatile type__ > {enum{res=value__};};
#define PFC_SET_TYPE_TRAIT_PARTIAL2(t0__, t1__, tp0__, tp1__, trait__, value__) PFC_SET_TYPE_TRAIT_PARTIAL(t0__ PFC_COMMA t1__, tp0__ PFC_COMMA tp1__, trait__, value__)
#define PFC_SET_TYPE_TRAIT_PARTIAL3(t0__, t1__, t2__, tp0__, tp1__, tp2__, trait__, value__) PFC_SET_TYPE_TRAIT_PARTIAL(t0__ PFC_COMMA t1__ PFC_COMMA t2__, tp0__ PFC_COMMA tp1__ PFC_COMMA tp2__, trait__, value__)
#define PFC_SET_TYPE_TRAIT_PARTIAL4(t0__, t1__, t2__, t3__, tp0__, tp1__, tp2__, tp3__, trait__, value__) PFC_SET_TYPE_TRAIT_PARTIAL(t0__ PFC_COMMA t1__ PFC_COMMA t2__ PFC_COMMA t3__, tp0__ PFC_COMMA tp1__ PFC_COMMA tp2__ PFC_COMMA tp3__, trait__, value__)
#define PFC_SET_TYPE_TRAIT_PARTIAL5(t0__, t1__, t2__, t3__, t4__, tp0__, tp1__, tp2__, tp3__, tp4__, trait__, value__) PFC_SET_TYPE_TRAIT_PARTIAL(t0__ PFC_COMMA t1__ PFC_COMMA t2__ PFC_COMMA t3__ PFC_COMMA t4__, tp0__ PFC_COMMA tp1__ PFC_COMMA tp2__ PFC_COMMA tp3__ PFC_COMMA tp4__, trait__, value__)
#define PFC_SET_TYPE_TRAIT_PARTIAL6(t0__, t1__, t2__, t3__, t4__, t5__, tp0__, tp1__, tp2__, tp3__, tp4__, tp5__, trait__, value__) PFC_SET_TYPE_TRAIT_PARTIAL(t0__ PFC_COMMA t1__ PFC_COMMA t2__ PFC_COMMA t3__ PFC_COMMA t4__ PFC_COMMA t5__, tp0__ PFC_COMMA tp1__ PFC_COMMA tp2__ PFC_COMMA tp3__ PFC_COMMA tp4__ PFC_COMMA tp5__, trait__, value__)
#define PFC_SET_TYPE_TRAIT_PARTIAL7(t0__, t1__, t2__, t3__, t4__, t5__, t6__, tp0__, tp1__, tp2__, tp3__, tp4__, tp5__, tp6__, trait__, value__) PFC_SET_TYPE_TRAIT_PARTIAL(t0__ PFC_COMMA t1__ PFC_COMMA t2__ PFC_COMMA t3__ PFC_COMMA t4__ PFC_COMMA t5__ PFC_COMMA t6__, tp0__ PFC_COMMA tp1__ PFC_COMMA tp2__ PFC_COMMA tp3__ PFC_COMMA tp4__ PFC_COMMA tp5__ PFC_COMMA tp6__, trait__, value__)
#define PFC_SET_TYPE_TRAIT_PARTIAL8(t0__, t1__, t2__, t3__, t4__, t5__, t6__, t7__, tp0__, tp1__, tp2__, tp3__, tp4__, tp5__, tp6__, tp7__, trait__, value__) PFC_SET_TYPE_TRAIT_PARTIAL(t0__ PFC_COMMA t1__ PFC_COMMA t2__ PFC_COMMA t3__ PFC_COMMA t4__ PFC_COMMA t5__ PFC_COMMA t6__ PFC_COMMA t7__, tp0__ PFC_COMMA tp1__ PFC_COMMA tp2__ PFC_COMMA tp3__ PFC_COMMA tp4__ PFC_COMMA tp5__ PFC_COMMA tp6__ PFC_COMMA tp7__, trait__, value__)
#define PFC_SET_TYPE_TRAIT_PARTIAL9(t0__, t1__, t2__, t3__, t4__, t5__, t6__, t7__, t8__, tp0__, tp1__, tp2__, tp3__, tp4__, tp5__, tp6__, tp7__, tp8__, trait__, value__) PFC_SET_TYPE_TRAIT_PARTIAL(t0__ PFC_COMMA t1__ PFC_COMMA t2__ PFC_COMMA t3__ PFC_COMMA t4__ PFC_COMMA t5__ PFC_COMMA t6__ PFC_COMMA t7__ PFC_COMMA t8__, tp0__ PFC_COMMA tp1__ PFC_COMMA tp2__ PFC_COMMA tp3__ PFC_COMMA tp4__ PFC_COMMA tp5__ PFC_COMMA tp6__ PFC_COMMA tp7__ PFC_COMMA tp8__, trait__, value__)
#define PFC_SET_TYPE_TRAIT_PARTIAL10(t0__, t1__, t2__, t3__, t4__, t5__, t6__, t7__, t8__, t9__, tp0__, tp1__, tp2__, tp3__, tp4__, tp5__, tp6__, tp7__, tp8__, tp9__, trait__, value__) PFC_SET_TYPE_TRAIT_PARTIAL(t0__ PFC_COMMA t1__ PFC_COMMA t2__ PFC_COMMA t3__ PFC_COMMA t4__ PFC_COMMA t5__ PFC_COMMA t6__ PFC_COMMA t7__ PFC_COMMA t8__ PFC_COMMA t9__, tp0__ PFC_COMMA tp1__ PFC_COMMA tp2__ PFC_COMMA tp3__ PFC_COMMA tp4__ PFC_COMMA tp5__ PFC_COMMA tp6__ PFC_COMMA tp7__ PFC_COMMA tp8__ PFC_COMMA tp9__, trait__, value__)
// pointer traits
template<typename> struct is_ptr_complete;     // pointers to complete types
template<typename> struct is_ptr_fund;         // pointers to fundamentals: int*, etc.
template<typename> struct is_ptr_int;          // pointers to integrals: unsigned char*, int*, etc.
template<typename> struct is_ptr_float;        // pointers to floats: float*, double*, etc.
template<typename> struct is_ptr_signed;       // pointers to signed: char*, float*, etc.
template<typename> struct is_ptr_unsigned;     // pointers to unsigned: unsigned char*, unsigned int*, etc.
template<typename> struct is_ptr_ptr;          // pointers to pointers: int**, etc.
template<typename> struct is_ptr_enum;         // pointers to enumerations
template<typename> struct is_ptr_const;        // pointers to const types: const int*, etc.
template<typename> struct is_ptr_volatile;     // pointers to volatile types: volatile int*, etc.
template<typename> struct is_ptr_cv;           // pointers to const volatile types: const volatile int*, etc.
template<typename> struct is_ptr_class;        // pointers to class/struct types
template<typename> struct is_ptr_union;        // pointers to unions
template<typename> struct is_ptr_pod;          // pointers to POD types
template<typename> struct is_ptr_pod_def_ctor; // pointers to types with POD semantics for default construction
template<typename> struct is_ptr_pod_dtor;     // pointers to types with POD semantics for destruction
template<typename> struct is_ptr_pod_move;     // pointers to types with POD semantics for moving
template<typename> struct is_ptr_pod_copy;     // pointers to types with POD semantics for copying
template<typename> struct is_ptr_pod_stream;   // pointers to types with POD semantics for streaming
template<typename> struct is_ptr_copyable;     // pointers to types with public copy-constructor
template<typename> struct is_ptr_mono;         // pointers to monomorphic types
template<typename> struct is_ptr_poly;         // pointers to polymorphic types
template<typename> struct is_ptr_abstract;     // pointers to abstract classes
// reference traits
template<typename> struct is_ref_complete;     // references to complete types
template<typename> struct is_ref_fund;         // references to fundamentals: int&, etc.
template<typename> struct is_ref_int;          // references to integrals: unsigned char&, int&, etc.
template<typename> struct is_ref_float;        // references to floats: float&, double&, etc.
template<typename> struct is_ref_signed;       // references to signed: char&, float&, etc.
template<typename> struct is_ref_unsigned;     // references to unsigned: unsigned char&, unsigned int&, etc.
template<typename> struct is_ref_ptr;          // references to pointers: int*&, etc.
template<typename> struct is_ref_enum;         // references to enumerations
template<typename> struct is_ref_const;        // references to const types: const int&, etc.
template<typename> struct is_ref_volatile;     // references to volatile types: volatile int&, etc.
template<typename> struct is_ref_cv;           // references to const volatile types: const volatile int&, etc.
template<typename> struct is_ref_class;        // references to class/struct types
template<typename> struct is_ref_union;        // references to unions
template<typename> struct is_ref_pod;          // references to POD types
template<typename> struct is_ref_pod_def_ctor; // references to types with POD semantics for default construction
template<typename> struct is_ref_pod_dtor;     // references to types with POD semantics for destruction
template<typename> struct is_ref_pod_move;     // references to types with POD semantics for moving
template<typename> struct is_ref_pod_copy;     // references to types with POD semantics for copying
template<typename> struct is_ref_pod_stream;   // references to types with POD semantics for streaming
template<typename> struct is_ref_copyable;     // references to types with public copy-constructor
template<typename> struct is_ref_mono;         // references to monomorphic types
template<typename> struct is_ref_poly;         // references to polymorphic types
template<typename> struct is_ref_abstract;     // references to abstract classes
// type relation traits
template<typename, typename> struct is_type_equal;       // test for equality of types (const-volatile insensitive)
template<typename, typename> struct is_type_cvequal;     // test for equality of types (const-volatile sensitive)
template<typename T, typename U> struct is_type_derived; // test if T is equal or publicly derived from U (directly or indirectly)
// type mutators
template<typename> struct add_const;
template<typename> struct add_volatile;
template<typename> struct add_cv;
template<typename> struct add_ptr;
template<typename> struct add_ref;
template<typename> struct remove_const;
template<typename> struct remove_volatile;
template<typename> struct remove_cv;
template<typename> struct remove_ptr;
template<typename> struct remove_ref;
// basic meta-programming components
template<bool, typename Then, typename Else> struct meta_if;
template<int> struct meta_case;
template<bool> struct meta_bool;
template<int> struct meta_int;
template<typename> struct meta_type;
struct meta_void {};
template<int, int, int, int, int, int, int, int, int, int> struct meta_min;
template<int, int, int, int, int, int, int, int, int, int> struct meta_max;
template<unsigned> struct meta_log2;     // base-2 log of a value (rounds down)
// bit math
template<uint32_t> struct meta_next_pow2;  // next power-of-2 value. if value is power-of-2, returns the value
template<uint32_t> struct meta_is_pow2;    // check if the value is power-of-2
template<uint32_t> struct meta_num_bits;   // number of set bits
template<uint32_t> struct meta_bitpos;     // position of the bit of a power-of-2 value
template<uint32_t> struct meta_lsb;        // the least significant set bit
template<uint32_t> struct meta_msb;        // the most significant set bit
template<unsigned size, unsigned pos=0, typename T=uint32_t, unsigned dw32_idx=0> struct meta_mask;   // generate bit mask of given size and type at given position (i.e. all bits 0, set bits [pos, pos+size-1])
template<unsigned size, unsigned pos=0, typename T=uint32_t, unsigned dw32_idx=0> struct meta_imask;  // generate inverse bit mask of given size and type at given position (i.e. all bits 1, unset bits [pos, pos+size-1])
template<uint32_t, int shift> struct meta_bit_shift; // shift bits with signed value: negative values shift to the right and positive to the left
// type size & alignment
template<typename> struct meta_sizeof;   // regular sizeof for types but works with voids (=0)
template<typename> struct meta_alignof;  // alignment requirement of the type: char=1, int=4, etc.
template<unsigned> struct meta_align_n;  // pod type with the given alignment requirement
template<typename> struct meta_align_t;  // pod type with the same alignment as the given type
template<typename> struct meta_storage;  // pod type with the same alignment and size as the given type
// data structures
template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9> struct meta_type_array;
template<int v0, int v1, int v2, int v3, int v4,
         int v5, int v6, int v7, int v8, int v9> struct meta_int_array;
//----------------------------------------------------------------------------


//============================================================================
// meta_type_array
//============================================================================
template<typename T0,           typename T1=meta_void, typename T2=meta_void, typename T3=meta_void, typename T4=meta_void,
         typename T5=meta_void, typename T6=meta_void, typename T7=meta_void, typename T8=meta_void, typename T9=meta_void>
struct meta_type_array
{
  // array ops
  enum {size=!is_type_equal<T0, meta_void>::res+!is_type_equal<T1, meta_void>::res+
             !is_type_equal<T2, meta_void>::res+!is_type_equal<T3, meta_void>::res+
             !is_type_equal<T4, meta_void>::res+!is_type_equal<T5, meta_void>::res+
             !is_type_equal<T6, meta_void>::res+!is_type_equal<T7, meta_void>::res+
             !is_type_equal<T8, meta_void>::res+!is_type_equal<T9, meta_void>::res};
  template<unsigned index_> struct get;
  template<typename T> struct find;
  static const uint32_t s_ids[];
};
//----------------------------------------------------------------------------


//============================================================================
// meta_int_array
//============================================================================
template<int v0,   int v1=0, int v2=0, int v3=0, int v4=0,
         int v5=0, int v6=0, int v7=0, int v8=0, int v9=0>
struct meta_int_array
{
  // array ops
  template<unsigned index_> struct get;
  template<int v> struct find;
};
//----------------------------------------------------------------------------


//============================================================================
// core class traits
//============================================================================
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, owner_ptr<T>, is_type_pod_move, true);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, owner_ref<T>, is_type_pod_move, true);
PFC_SET_TYPE_TRAIT(owner_data, is_type_pod_move, true);
//----------------------------------------------------------------------------

//============================================================================
#include "meta.inl"
} // namespace pfc
#endif
