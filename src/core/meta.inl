//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// type trait global helpers
//============================================================================
namespace priv
{
  template<typename T> struct is_type_trait_obj            {static T &val;};
  template<typename T> struct is_type_trait_obj<T&>        {static int val;};
  template<typename T> struct is_type_trait_obj<T[]>       {static T val[];};
  template<> struct is_type_trait_obj<void>                {static int val;};
  template<> struct is_type_trait_obj<const void>          {static int val;};
  template<> struct is_type_trait_obj<volatile void>       {static int val;};
  template<> struct is_type_trait_obj<const volatile void> {static int val;};
} // namespace priv
//----------------------------------------------------------------------------


//============================================================================
// is_type_fund
//============================================================================
namespace priv
{
  template<typename> struct is_type_fund_hlp                         {enum {res=false};};
  template<> struct is_type_fund_hlp<const volatile void>            {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile bool>            {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile char>            {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile signed char>     {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile unsigned char>   {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile signed short>    {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile unsigned short>  {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile signed int>      {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile unsigned int>    {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile signed long>     {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile unsigned long>   {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile int64_t>         {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile uint64_t>        {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile float>           {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile double>          {enum {res=true};};
  template<> struct is_type_fund_hlp<const volatile long double>     {enum {res=true};};
} // namespace priv
//----

template<typename T>
struct is_type_fund
{
  enum {res=priv::is_type_fund_hlp<typename add_cv<T>::res>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_int
//============================================================================
namespace priv
{
  template<typename> struct is_type_int_hlp                         {enum {res=false};};
  template<> struct is_type_int_hlp<const volatile bool>            {enum {res=true};};
  template<> struct is_type_int_hlp<const volatile char>            {enum {res=true};};
  template<> struct is_type_int_hlp<const volatile signed char>     {enum {res=true};};
  template<> struct is_type_int_hlp<const volatile unsigned char>   {enum {res=true};};
  template<> struct is_type_int_hlp<const volatile signed short>    {enum {res=true};};
  template<> struct is_type_int_hlp<const volatile unsigned short>  {enum {res=true};};
  template<> struct is_type_int_hlp<const volatile signed int>      {enum {res=true};};
  template<> struct is_type_int_hlp<const volatile unsigned int>    {enum {res=true};};
  template<> struct is_type_int_hlp<const volatile signed long>     {enum {res=true};};
  template<> struct is_type_int_hlp<const volatile unsigned long>   {enum {res=true};};
  template<> struct is_type_int_hlp<const volatile int64_t>         {enum {res=true};};
  template<> struct is_type_int_hlp<const volatile uint64_t>        {enum {res=true};};
} // namespace priv
//----

template<typename T>
struct is_type_int
{
  enum {res=priv::is_type_int_hlp<typename add_cv<T>::res>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_float
//============================================================================
namespace priv
{
  template<typename> struct is_type_float_hlp                      {enum {res=false};};
  template<> struct is_type_float_hlp<const volatile float>        {enum {res=true};};
  template<> struct is_type_float_hlp<const volatile double>       {enum {res=true};};
  template<> struct is_type_float_hlp<const volatile long double>  {enum {res=true};};
} // namespace priv
//----

template<typename T>
struct is_type_float
{
  enum {res=priv::is_type_float_hlp<typename add_cv<T>::res>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_signed
//============================================================================
namespace priv
{
  template<typename> struct is_type_signed_hlp                       {enum {res=false};};
  template<> struct is_type_signed_hlp<const volatile char>          {enum {res=true};};
  template<> struct is_type_signed_hlp<const volatile signed char>   {enum {res=true};};
  template<> struct is_type_signed_hlp<const volatile signed short>  {enum {res=true};};
  template<> struct is_type_signed_hlp<const volatile signed int>    {enum {res=true};};
  template<> struct is_type_signed_hlp<const volatile signed long>   {enum {res=true};};
  template<> struct is_type_signed_hlp<const volatile int64_t>       {enum {res=true};};
  template<> struct is_type_signed_hlp<const volatile float>         {enum {res=true};};
  template<> struct is_type_signed_hlp<const volatile double>        {enum {res=true};};
  template<> struct is_type_signed_hlp<const volatile long double>   {enum {res=true};};
} // namespace priv
//----

template<typename T>
struct is_type_signed
{
  enum {res=priv::is_type_signed_hlp<typename add_cv<T>::res>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_unsigned
//============================================================================
namespace priv
{
  template<typename> struct is_type_unsigned_hlp                         {enum {res=false};};
  template<> struct is_type_unsigned_hlp<const volatile bool>            {enum {res=true};};
  template<> struct is_type_unsigned_hlp<const volatile unsigned char>   {enum {res=true};};
  template<> struct is_type_unsigned_hlp<const volatile unsigned short>  {enum {res=true};};
  template<> struct is_type_unsigned_hlp<const volatile unsigned int>    {enum {res=true};};
  template<> struct is_type_unsigned_hlp<const volatile unsigned long>   {enum {res=true};};
  template<> struct is_type_unsigned_hlp<const volatile uint64_t>        {enum {res=true};};
} // namespace priv
//----

template<typename T>
struct is_type_unsigned
{
  enum {res=priv::is_type_unsigned_hlp<typename add_cv<T>::res>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_ptr
//============================================================================
template<typename T>
struct is_type_ptr
{
  enum {res=false};
};
//----

template<typename T> struct is_type_ptr<T*>               {enum {res=true};};
template<typename T> struct is_type_ptr<T*const>          {enum {res=true};};
template<typename T> struct is_type_ptr<T*volatile>       {enum {res=true};};
template<typename T> struct is_type_ptr<T*const volatile> {enum {res=true};};
//----------------------------------------------------------------------------


//============================================================================
// is_type_array
//============================================================================
template<typename T>
struct is_type_array
{
  enum {res=false};
};
//----

template<typename T> struct is_type_array<T[]>                    {enum {res=true};};
template<typename T, unsigned size> struct is_type_array<T[size]> {enum {res=true};};
//----------------------------------------------------------------------------


//============================================================================
// is_type_ref
//============================================================================
template<typename T>
struct is_type_ref
{
  enum {res=false};
};
//----

template<typename T>
struct is_type_ref<T&>
{
  enum {res=true};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_enum
//============================================================================
namespace priv
{
  enum e_is_type_enum_hlp {};
  template<typename T, unsigned> struct is_type_enum_hlp {enum {res=false};};
  template<typename T>
  struct is_type_enum_hlp<T, sizeof(e_is_type_enum_hlp)>
  {
    struct converter
    {
      converter(char);
      converter(unsigned char);
      converter(signed char);
      converter(signed short);
      converter(unsigned short);
      converter(signed int);
      converter(unsigned int);
      converter(signed long);
      converter(unsigned long);
      converter(int64_t);
      converter(uint64_t);
      converter(float);
      converter(double);
      converter(long double);
    };
    static char enum_test(const converter&);
    static int enum_test(...);
    enum {res=   !is_type_fund<T>::res
              && !is_type_ref<T>::res
              && 1==sizeof(enum_test(is_type_trait_obj<T>::val))};
  };
} // namespace priv
//----

template<typename T>
struct is_type_enum
{
  enum {res=priv::is_type_enum_hlp<T, meta_sizeof<typename meta_if<!is_type_ref<T>::res, T, char>::res>::res>::res};
};
//----

template<typename T> struct is_type_enum<T[]> {enum{res=false};};
//----------------------------------------------------------------------------


//============================================================================
// is_type_const
//============================================================================
template<typename T>
struct is_type_const
{
  enum {res=false};
};
//----

template<typename T> struct is_type_const<const T>                      {enum {res=true};};
template<typename T> struct is_type_const<const T[]>                    {enum {res=true};};
template<typename T, unsigned size> struct is_type_const<const T[size]> {enum {res=true};};
//----------------------------------------------------------------------------


//============================================================================
// is_type_volatile
//============================================================================
template<typename T>
struct is_type_volatile
{
  enum {res=false};
};
//----

template<typename T> struct is_type_volatile<volatile T>                      {enum {res=true};};
template<typename T> struct is_type_volatile<volatile T[]>                    {enum {res=true};};
template<typename T, unsigned size> struct is_type_volatile<volatile T[size]> {enum {res=true};};
//----------------------------------------------------------------------------


//============================================================================
// is_type_cv
//============================================================================
template<typename T>
struct is_type_cv
{
  enum {res=false};
};
//----

template<typename T> struct is_type_cv<const volatile T>                      {enum {res=true};};
template<typename T> struct is_type_cv<const volatile T[]>                    {enum {res=true};};
template<typename T, unsigned size> struct is_type_cv<const volatile T[size]> {enum {res=true};};
//----------------------------------------------------------------------------


//============================================================================
// is_type_class
//============================================================================
template<typename T>
struct is_type_class
{
  enum {res=   !is_type_fund<T>::res
            && !is_type_ref<T>::res
            && !is_type_ptr<T>::res
            && !is_type_array<T>::res
            && !is_type_enum<T>::res
            && !is_type_union<T>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_union
//============================================================================
template<typename T>
struct is_type_union
{
  enum {res=false};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_pod
//============================================================================
template<typename T>
struct is_type_pod
{
  enum {res=!is_type_class<T>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_pod_def_ctor
//============================================================================
template<typename T>
struct is_type_pod_def_ctor
{
  enum {res=is_type_pod<T>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_pod_dtor
//============================================================================
template<typename T>
struct is_type_pod_dtor
{
  enum {res=is_type_pod<T>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_pod_move
//============================================================================
template<typename T>
struct is_type_pod_move
{
  enum {res=is_type_pod_copy<T>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_pod_copy
//============================================================================
template<typename T>
struct is_type_pod_copy
{
  enum {res=is_type_pod<T>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_pod_stream
//============================================================================
template<typename T>
struct is_type_pod_stream
{
  enum {res=!is_type_class<T>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_copyable
//============================================================================
template<typename T>
struct is_type_copyable
{
  enum {res=true};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_mono
//============================================================================
template<typename T>
struct is_type_mono
{
  enum {res=!is_type_poly<T>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_poly
//============================================================================
namespace priv
{
  template<bool, typename T> struct is_type_poly_hlp1: T {is_type_poly_hlp1(); virtual ~is_type_poly_hlp1();};
  template<bool, typename T> struct is_type_poly_hlp2: T {is_type_poly_hlp2();};
  template<typename T> struct is_type_poly_hlp1<false, T> {};
  template<typename T> struct is_type_poly_hlp2<false, T> {};
} // namespace priv
//----

template<typename T>
struct is_type_poly
{
  enum {res=   is_type_class<T>::res
            && sizeof(priv::is_type_poly_hlp1<is_type_class<T>::res, T>)==sizeof(priv::is_type_poly_hlp2<is_type_class<T>::res, T>)};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_abstract
//============================================================================
namespace priv
{
  template<typename T> int is_type_abstract_hlp(T(*)[1]);
  template<typename T> char is_type_abstract_hlp(...);
} // namespace priv
//----

template<typename T>
struct is_type_abstract
{
  enum {res=!is_type_array<T>::res && 1==sizeof(priv::is_type_abstract_hlp<T>(0))};
};
//----

template<> struct is_type_abstract<void>                {enum {res=false};};
template<> struct is_type_abstract<const void>          {enum {res=false};};
template<> struct is_type_abstract<volatile void>       {enum {res=false};};
template<> struct is_type_abstract<const volatile void> {enum {res=false};};
template<typename T> struct is_type_abstract<T&>        {enum {res=false};};
//----------------------------------------------------------------------------


//============================================================================
// pointer traits
//============================================================================
template<typename T>
struct is_ptr_fund
{
  enum {res=is_type_ptr<T>::res && is_type_fund<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_int
{
  enum {res=is_type_ptr<T>::res && is_type_int<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_float
{
  enum {res=is_type_ptr<T>::res && is_type_float<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_signed
{
  enum {res=is_type_ptr<T>::res && is_type_signed<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_unsigned
{
  enum {res=is_type_ptr<T>::res && is_type_unsigned<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_ptr
{
  enum {res=is_type_ptr<T>::res && is_type_ptr<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_enum
{
  enum {res=is_type_ptr<T>::res && is_type_enum<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_const
{
  enum {res=is_type_ptr<T>::res && is_type_const<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_volatile
{
  enum {res=is_type_ptr<T>::res && is_type_volatile<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_cv
{
  enum {res=is_type_ptr<T>::res && is_type_cv<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_class
{
  enum {res=is_type_ptr<T>::res && is_type_class<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_union
{
  enum {res=is_type_ptr<T>::res && is_type_union<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_pod
{
  enum {res=is_type_ptr<T>::res && is_type_pod<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_pod_def_ctor
{
  enum {res=is_type_ptr<T>::res && is_type_pod_def_ctor<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_pod_dtor
{
  enum {res=is_type_ptr<T>::res && is_type_pod_dtor<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_pod_move
{
  enum {res=is_type_ptr<T>::res && is_type_pod_move<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_pod_copy
{
  enum {res=is_type_ptr<T>::res && is_type_pod_copy<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_pod_stream
{
  enum {res=is_type_ptr<T>::res && is_type_pod_stream<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_copyable
{
  enum {res=is_type_ptr<T>::res && is_type_copyable<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_mono
{
  enum {res=is_type_ptr<T>::res && is_type_mono<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_poly
{
  enum {res=is_type_ptr<T>::res && is_type_poly<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ptr_abstract
{
  enum {res=is_type_ptr<T>::res && is_type_abstract<typename remove_ptr<T>::res>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// reference traits
//============================================================================
template<typename T>
struct is_ref_fund
{
  enum {res=is_type_ref<T>::res && is_type_fund<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_int
{
  enum {res=is_type_ref<T>::res && is_type_int<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_float
{
  enum {res=is_type_ref<T>::res && is_type_ref<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_signed
{
  enum {res=is_type_ref<T>::res && is_type_signed<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_unsigned
{
  enum {res=is_type_ref<T>::res && is_type_unsigned<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_ptr
{
  enum {res=is_type_ref<T>::res && is_type_ptr<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_enum
{
  enum {res=is_type_ref<T>::res && is_type_enum<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_const
{
  enum {res=is_type_ref<T>::res && is_type_const<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_volatile
{
  enum {res=is_type_ref<T>::res && is_type_volatile<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_cv
{
  enum {res=is_type_ref<T>::res && is_type_cv<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_class
{
  enum {res=is_type_ref<T>::res && is_type_class<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_union
{
  enum {res=is_type_ref<T>::res && is_type_union<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_pod
{
  enum {res=is_type_ref<T>::res && is_type_pod<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_pod_def_ctor
{
  enum {res=is_type_ref<T>::res && is_type_pod_def_ctor<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_pod_dtor
{
  enum {res=is_type_ref<T>::res && is_type_pod_dtor<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_pod_move
{
  enum {res=is_type_ref<T>::res && is_type_pod_move<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_pod_copy
{
  enum {res=is_type_ref<T>::res && is_type_pod_copy<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_pod_stream
{
  enum {res=is_type_ref<T>::res && is_type_pod_stream<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_copyable
{
  enum {res=is_type_ref<T>::res && is_type_copyable<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_mono
{
  enum {res=is_type_ref<T>::res && is_type_mono<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_poly
{
  enum {res=is_type_ref<T>::res && is_type_poly<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------

template<typename T>
struct is_ref_abstract
{
  enum {res=is_type_ref<T>::res && is_type_abstract<typename remove_ref<T>::res>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_equal
//============================================================================
template<typename T, typename U>
struct is_type_equal
{
  enum {res=is_type_cvequal<typename add_cv<T>::res, typename add_cv<U>::res>::res};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_cvequal
//============================================================================
template<typename T, typename U>
struct is_type_cvequal
{
  enum {res=false};
};
//----

template<typename T>
struct is_type_cvequal<T, T>
{
  enum {res=true};
};
//----------------------------------------------------------------------------


//============================================================================
// is_type_derived
//============================================================================
namespace priv
{
  template<typename T> char is_type_derived_hlp(T*);
  template<typename T> char is_type_derived_hlp(const T*);
  template<typename T> char is_type_derived_hlp(volatile T*);
  template<typename T> char is_type_derived_hlp(const volatile T*);
  template<typename T> int is_type_derived_hlp(...);
} // namespace priv
//----

template<typename T, typename U>
struct is_type_derived
{
  enum {res=1==sizeof(priv::is_type_derived_hlp<U>((T*)0))};
};
//----------------------------------------------------------------------------


//============================================================================
// add_const
//============================================================================
template<typename T>
struct add_const
{
  typedef const T res;
};
//----

template<typename T>
struct add_const<T&>
{
  typedef T &res;
};
//----------------------------------------------------------------------------


//============================================================================
// add_volatile
//============================================================================
template<typename T>
struct add_volatile
{
  typedef volatile T res;
};
//----

template<typename T>
struct add_volatile<T&>
{
  typedef T &res;
};
//----------------------------------------------------------------------------


//============================================================================
// add_cv
//============================================================================
template<typename T>
struct add_cv
{
  typedef const volatile T res;
};
//----

template<typename T>
struct add_cv<T&>
{
  typedef T &res;
};
//----------------------------------------------------------------------------


//============================================================================
// add_ptr
//============================================================================
template<typename T>
struct add_ptr
{
  typedef T *res;
};
//----

template<typename T>
struct add_ptr<T&>
{
  typedef T &res;
};
//----------------------------------------------------------------------------


//============================================================================
// add_ref
//============================================================================
template<typename T>
struct add_ref
{
  typedef T &res;
};
//----

template<typename T>
struct add_ref<T&>
{
  typedef T &res;
};
//----

template<> struct add_ref<void>                {typedef void res;};
template<> struct add_ref<const void>          {typedef const void res;};
template<> struct add_ref<volatile void>       {typedef volatile void res;};
template<> struct add_ref<const volatile void> {typedef const volatile void res;};
//----------------------------------------------------------------------------


//============================================================================
// remove_const
//============================================================================
template<typename T>
struct remove_const
{
  typedef T res;
};
//----

template<typename T> struct remove_const<const T>          {typedef T res;};
template<typename T> struct remove_const<const volatile T> {typedef volatile T res;};
//----------------------------------------------------------------------------


//============================================================================
// remove_volatile
//============================================================================
template<typename T>
struct remove_volatile
{
  typedef T res;
};
//----

template<typename T> struct remove_volatile<volatile T>       {typedef T res;};
template<typename T> struct remove_volatile<const volatile T> {typedef const T res;};
//----------------------------------------------------------------------------


//============================================================================
// remove_cv
//============================================================================
template<typename T>
struct remove_cv
{
  typedef T res;
};
//----

template<typename T> struct remove_cv<const T>          {typedef T res;};
template<typename T> struct remove_cv<volatile T>       {typedef T res;};
template<typename T> struct remove_cv<const volatile T> {typedef T res;};
//----------------------------------------------------------------------------


//============================================================================
// remove_ptr
//============================================================================
template<typename T>
struct remove_ptr
{
  typedef T res;
};
//----

template<typename T>
struct remove_ptr<T*>
{
  typedef T res;
};
//----

template<typename T>
struct remove_ptr<T*const>
{
  typedef T res;
};
//----

template<typename T>
struct remove_ptr<T*volatile>
{
  typedef T res;
};
//----

template<typename T>
struct remove_ptr<T*const volatile>
{
  typedef T res;
};
//----------------------------------------------------------------------------


//============================================================================
// remove_ref
//============================================================================
template<typename T>
struct remove_ref
{
  typedef T res;
};
//----

template<typename T>
struct remove_ref<T&>
{
  typedef T res;
};
//----------------------------------------------------------------------------


//============================================================================
// type
//============================================================================
template<typename T>
struct type
{
  typedef typename meta_if<is_type_class<T>::res, const T&, T>::res arg;
};
//----------------------------------------------------------------------------


//============================================================================
// meta_if
//============================================================================
template<bool, typename Then, typename Else>
struct meta_if
{
  typedef Then res;
};
//----

template<typename Then, typename Else>
struct meta_if<false, Then, Else>
{
  typedef Else res;
};
//----------------------------------------------------------------------------


//============================================================================
// meta_case
//============================================================================
template<int v>
struct meta_case
{
  enum {res=v};
};
//----------------------------------------------------------------------------


//============================================================================
// meta_bool
//============================================================================
template<bool b>
struct meta_bool
{
  enum {res=b};
};
//----------------------------------------------------------------------------


//============================================================================
// meta_int
//============================================================================
template<int v>
struct meta_int
{
  enum {res=v};
};
//----------------------------------------------------------------------------


//============================================================================
// meta_type
//============================================================================
template<typename T>
struct meta_type
{
  typedef T res;
};
//----------------------------------------------------------------------------


//============================================================================
// meta_min
//============================================================================
template<int v0_,     int v1_,     int v2_=v0_, int v3_=v0_, int v4_=v0_,
         int v5_=v0_, int v6_=v0_, int v7_=v0_, int v8_=v0_, int v9_=v0_>
struct meta_min
{
  enum {r0=v0_<v1_?v0_:v1_, r1=r0<v2_?r0:v2_, r2=r1<v3_?r1:v3_, r3=r2<v4_?r2:v4_,
        r4=r3<v5_?r3:v5_, r5=r4<v6_?r4:v6_, r6=r5<v7_?r5:v7_, r7=r6<v8_?r6:v8_};
  enum {res=r7<v9_?r7:v9_};
};
//----------------------------------------------------------------------------


//============================================================================
// meta_max
//============================================================================
template<int v0_,     int v1_,     int v2_=v0_, int v3_=v0_, int v4_=v0_,
         int v5_=v0_, int v6_=v0_, int v7_=v0_, int v8_=v0_, int v9_=v0_>
struct meta_max
{
  enum {r0=v0_>v1_?v0_:v1_, r1=r0>v2_?r0:v2_, r2=r1>v3_?r1:v3_, r3=r2>v4_?r2:v4_,
        r4=r3>v5_?r3:v5_, r5=r4>v6_?r4:v6_, r6=r5>v7_?r5:v7_, r7=r6>v8_?r6:v8_};
  enum {res=r7>v9_?r7:v9_};
};
//----------------------------------------------------------------------------


//============================================================================
// meta_log2
//============================================================================
template<unsigned v>
struct meta_log2
{
  enum {r0=v>0xffff?16:0, r1=r0+(v>>r0>0xff?8:0), r2=r1+(v>>r1>0xf?4:0), r3=r2+(v>>r2>0x3?2:0),
        res=r3+(v>>r3>0x1?1:0)};
};
//----------------------------------------------------------------------------


//============================================================================
// meta_next_pow2
//============================================================================
template<uint32_t v>
struct meta_next_pow2
{
  // the next power-of-2 of the value (if v_ is pow-of-2 returns v_)
  enum {res=(v&(v-1))==0?v:meta_msb<v>::res<<1};
};
//----------------------------------------------------------------------------


//============================================================================
// meta_is_pow2
//============================================================================
template<uint32_t v>
struct meta_is_pow2
{
  enum {res=(v&(v-1))==0};
};
//----------------------------------------------------------------------------


//============================================================================
// meta_num_bits
//============================================================================
template<uint32_t v>
struct meta_num_bits
{
  // count the number of set bits with SWAR algorithm
  enum {r0=v-((v>>1)&0x55555555),
        r1=((r0>>2)&0x33333333)+(r0&0x33333333),
        r2=((r1>>4)+r1)&0x0f0f0f0f,
        r3=r2+(r2>>8),
        res=(r3+(r3>>16))&0x3f};
};
//----------------------------------------------------------------------------


//============================================================================
// meta_bitpos
//============================================================================
template<uint32_t v>
struct meta_bitpos
{
  // find the bit with binary search
  PFC_CTC_ASSERT_MSG((v&(v-1))==0, the_value_must_be_zero_or_power_of_2);
  enum {r0=v&0xffff0000?16:0,
        r1=r0+((v>>r0)&0xff00?8:0),
        r2=r1+((v>>r1)&0xf0?4:0),
        r3=r2+((v>>r2)&0x0c?2:0),
        res=r3+((v>>r3)&0x02?1:0)};
};
//----------------------------------------------------------------------------


//============================================================================
// meta_lsb
//============================================================================
template<uint32_t v>
struct meta_lsb
{
  // return the least significant set bit of the value
  enum {res=v&(0-v)};
};
//----------------------------------------------------------------------------


//============================================================================
// meta_msb
//============================================================================
template<uint32_t v>
struct meta_msb
{
  // return the most significant set bit of the value
  enum {r0=v|(v>>1), r1=r0|(uint32_t(r0)>>2), r2=r1|(uint32_t(r1)>>4),
        r3=r2|(uint32_t(r2)>>8), r4=r3|(uint32_t(r3)>>16),
        res=r4&~(uint32_t(r4)>>1)};
};
//----------------------------------------------------------------------------


//============================================================================
// meta_mask
//============================================================================
template<unsigned size_, unsigned pos_, typename T, unsigned dw32_idx_>
struct meta_mask
{
  // generates bit mask of given size (i.e. set bits [pos_, pos_+size_-1] to 1 and the rest to 0)
  enum e_test_enum {};
  PFC_CTC_ASSERT_MSG(sizeof(e_test_enum)==4, meta_mask_assumes_enum_size_of_32_bits);
  PFC_CTC_ASSERT_MSG(sizeof(T)<=sizeof(e_test_enum), meta_mask_must_be_specialized_for_mask_types_with_size_greater_than_32_bits);
  enum {dw32_pos=int(pos_)-32*int(dw32_idx_), dw32_size=int(size_)+(dw32_pos<0?dw32_pos:0)};
  enum {res=dw32_pos<32&&dw32_size>0?(~(dw32_size<32?0xffffffff<<(dw32_size<32&&dw32_size>0?dw32_size:0):0))<<(dw32_pos<0?0:dw32_pos>31?0:dw32_pos):0};
};
//----

template<unsigned mask_size_, unsigned mask_pos_, unsigned dw32_idx_>
struct meta_mask<mask_size_, mask_pos_, int64_t, dw32_idx_>
{
  enum {mask_pos=mask_pos_-dw32_idx_*32};
  static const int64_t res=mask_pos<64?(mask_size_<64?(~(uint64_t(-1)<<(mask_size_<64?mask_size_:0))):0xffffffffffffffff)<<(mask_pos<64?mask_pos:0):0;
};
//----

template<unsigned mask_size_, unsigned mask_pos_, unsigned dw32_idx_>
struct meta_mask<mask_size_, mask_pos_, uint64_t, dw32_idx_>
{
  enum {mask_pos=mask_pos_-dw32_idx_*32};
  static const uint64_t res=mask_pos<64?(mask_size_<64?(~(uint64_t(-1)<<(mask_size_<64?mask_size_:0))):0xffffffffffffffff)<<(mask_pos<64?mask_pos:0):0;
};
//----------------------------------------------------------------------------


//============================================================================
// meta_imask
//============================================================================
template<unsigned size, unsigned pos, typename T, unsigned dw32_idx_>
struct meta_imask
{
  // generate inverse bit mask of given size (i.e. set bits [pos_, pos_+size_-1] to 0 and the rest to 1)
  enum e_test_enum {};
  PFC_CTC_ASSERT_MSG(sizeof(e_test_enum)==4, meta_imask_assumes_enum_size_of_32_bits);
  PFC_CTC_ASSERT_MSG(sizeof(T)<=4, meta_imask_must_be_specialized_for_mask_types_with_size_greater_than_enum_type);
  enum {res=~meta_mask<size, pos, T, dw32_idx_>::res};
};
//----

template<unsigned mask_size_, unsigned mask_pos_, unsigned dw32_idx_>
struct meta_imask<mask_size_, mask_pos_, int64_t, dw32_idx_>
{
  static const int64_t res=~meta_mask<mask_size_, mask_pos_, int64_t, dw32_idx_>::res;
};
//----

template<unsigned mask_size_, unsigned mask_pos_, unsigned dw32_idx_>
struct meta_imask<mask_size_, mask_pos_, uint64_t, dw32_idx_>
{
  static const uint64_t res=~meta_mask<mask_size_, mask_pos_, uint64_t, dw32_idx_>::res;
};
//----------------------------------------------------------------------------


//============================================================================
// meta_bit_shift
//============================================================================
template<uint32_t v, int shift>
struct meta_bit_shift
{
  enum {s=shift<0?-shift:shift,
        res=shift<0?v>>s:v<<s};
};
//----------------------------------------------------------------------------


//============================================================================
// meta_sizeof
//============================================================================
template<typename T>
struct meta_sizeof
{
  enum {res=sizeof(T)};
};
//----

template<> struct meta_sizeof<void>                {enum {res=0};};
template<> struct meta_sizeof<const void>          {enum {res=0};};
template<> struct meta_sizeof<volatile void>       {enum {res=0};};
template<> struct meta_sizeof<const volatile void> {enum {res=0};};
//----------------------------------------------------------------------------


//============================================================================
// meta_alignof
//============================================================================
namespace priv
{
  template<typename T>
  struct meta_alignof_hlp {meta_alignof_hlp(); void operator=(const meta_alignof_hlp&); char x; T y;};
} // namespace priv
//----

template<typename T>
struct meta_alignof
{
  enum {res=sizeof(priv::meta_alignof_hlp<T>)-sizeof(T)};
};
//----

template<> struct meta_alignof<void>                {enum {res=0};};
template<> struct meta_alignof<const void>          {enum {res=0};};
template<> struct meta_alignof<volatile void>       {enum {res=0};};
template<> struct meta_alignof<const volatile void> {enum {res=0};};
//----------------------------------------------------------------------------


//============================================================================
// meta_align_n
//============================================================================
template<unsigned alignment>
struct meta_align_n
{
  typedef typename align_type<alignment>::res res;
};
//----------------------------------------------------------------------------


//============================================================================
// meta_align_t
//============================================================================
template<typename T>
struct meta_align_t
{
  typedef typename meta_align_n<meta_alignof<T>::res>::res res;
};
//----------------------------------------------------------------------------


//============================================================================
// meta_storage
//============================================================================
template<typename T>
struct meta_storage
{
  typedef typename meta_align_t<T>::res align_type_t;
  typedef align_type_t res[(sizeof(T)+sizeof(align_type_t)-1)/sizeof(align_type_t)];
};
//----------------------------------------------------------------------------


//============================================================================
// meta_type_array
//============================================================================
template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<unsigned index_>
struct meta_type_array<T0, T1, T2, T3 ,T4, T5, T6, T7, T8, T9>::get
{
  PFC_CTC_ASSERT_MSG(index_<size, index_out_of_range);
  typedef typename meta_if<index_==0, T0,
          typename meta_if<index_==1, T1,
          typename meta_if<index_==2, T2,
          typename meta_if<index_==3, T3,
          typename meta_if<index_==4, T4,
          typename meta_if<index_==5, T5,
          typename meta_if<index_==6, T6,
          typename meta_if<index_==7, T7,
          typename meta_if<index_==8, T8,
          typename meta_if<index_==9, T9, meta_void>::res
          >::res>::res>::res>::res>::res>::res>::res>::res>::res res;
};
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
struct meta_type_array<T0, T1, T2, T3 ,T4, T5, T6, T7, T8, T9>::find
{
  enum {res=is_type_cvequal<T, T0>::res?0:is_type_cvequal<T, T1>::res?1:
            is_type_cvequal<T, T2>::res?2:is_type_cvequal<T, T3>::res?3:
            is_type_cvequal<T, T4>::res?4:is_type_cvequal<T, T5>::res?5:
            is_type_cvequal<T, T6>::res?6:is_type_cvequal<T, T7>::res?7:
            is_type_cvequal<T, T8>::res?8:is_type_cvequal<T, T9>::res?9:
            -1};
};
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
const uint32_t meta_type_array<T0, T1, T2, T3 ,T4, T5, T6, T7, T8, T9>::s_ids[]=
{
  is_type_equal<T0, meta_void>::res?0:type_id<T0>::id,
  is_type_equal<T1, meta_void>::res?0:type_id<T1>::id,
  is_type_equal<T2, meta_void>::res?0:type_id<T2>::id,
  is_type_equal<T3, meta_void>::res?0:type_id<T3>::id,
  is_type_equal<T4, meta_void>::res?0:type_id<T4>::id,
  is_type_equal<T5, meta_void>::res?0:type_id<T5>::id,
  is_type_equal<T6, meta_void>::res?0:type_id<T6>::id,
  is_type_equal<T7, meta_void>::res?0:type_id<T7>::id,
  is_type_equal<T8, meta_void>::res?0:type_id<T8>::id,
  is_type_equal<T9, meta_void>::res?0:type_id<T9>::id,
  0
};
//----------------------------------------------------------------------------


//============================================================================
// meta_int_array
//============================================================================
template<int v0, int v1, int v2, int v3, int v4,
         int v5, int v6, int v7, int v8, int v9>
template<unsigned index_>
struct meta_int_array<v0, v1, v2, v3, v4, v5, v6, v7, v8, v9>::get
{
  enum {res=index_==0?v0:index_==1?v1:index_==2?v2:index_==3?v3:index_==4?v4:
            index_==5?v5:index_==6?v6:index_==7?v7:index_==8?v8:index_==9?v9:0};
};
//----

template<int v0, int v1, int v2, int v3, int v4,
         int v5, int v6, int v7, int v8, int v9>
template<int v>
struct meta_int_array<v0, v1, v2, v3, v4, v5, v6, v7, v8, v9>::find
{
  enum {res=v==v0?0:v==v1?1:v==v2?2:v==v3?3:v==v4?4:
            v==v5?5:v==v6?6:v==v7?7:v==v8?8:v==v9?9:-1};
};
//----------------------------------------------------------------------------
