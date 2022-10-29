//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// numeric_type<char>
//============================================================================
template<>
struct numeric_type<char>
{
  // type properties
  enum
  {
    is_float  =false,
    is_int    =true,
    is_signed =char(-1)<0
  };
  //--------------------------------------------------------------------------

  static PFC_INLINE char range_min()  {return CHAR_MIN;}
  static PFC_INLINE char range_max()  {return CHAR_MAX;}
  static PFC_INLINE char zero()       {return 0;}
  static PFC_INLINE char float_one()  {return CHAR_MAX;}
};
//----------------------------------------------------------------------------


//============================================================================
// numeric_type<signed char>
//============================================================================
template<>
struct numeric_type<signed char>
{
  // type properties
  enum
  {
    is_float  =false,
    is_int    =true,
    is_signed =true
  };
  //--------------------------------------------------------------------------

  static PFC_INLINE signed char range_min()  {return SCHAR_MIN;}
  static PFC_INLINE signed char range_max()  {return SCHAR_MAX;}
  static PFC_INLINE signed char zero()       {return 0;}
  static PFC_INLINE signed char float_one()  {return SCHAR_MAX;}
};
//----------------------------------------------------------------------------


//============================================================================
// numeric_type<unsigned char>
//============================================================================
template<>
struct numeric_type<unsigned char>
{
  // type properties
  enum
  {
    is_float  =false,
    is_int    =true,
    is_signed =false
  };
  //--------------------------------------------------------------------------

  static PFC_INLINE unsigned char range_min()  {return 0;}
  static PFC_INLINE unsigned char range_max()  {return UCHAR_MAX;}
  static PFC_INLINE unsigned char zero()       {return 0;}
  static PFC_INLINE unsigned char float_one()  {return UCHAR_MAX;}
};
//----------------------------------------------------------------------------


//============================================================================
// numeric_type<signed short>
//============================================================================
template<>
struct numeric_type<signed short>
{
  // type properties
  enum
  {
    is_float  =false,
    is_int    =true,
    is_signed =true
  };
  //--------------------------------------------------------------------------

  static PFC_INLINE signed short range_min()  {return SHRT_MIN;}
  static PFC_INLINE signed short range_max()  {return SHRT_MAX;}
  static PFC_INLINE signed short zero()       {return 0;}
  static PFC_INLINE signed short float_one()  {return SHRT_MAX;}
};
//----------------------------------------------------------------------------


//============================================================================
// numeric_type<unsigned short>
//============================================================================
template<>
struct numeric_type<unsigned short>
{
  // type properties
  enum
  {
    is_float  =false,
    is_int    =true,
    is_signed =false
  };
  //--------------------------------------------------------------------------

  static PFC_INLINE unsigned short range_min()  {return 0;}
  static PFC_INLINE unsigned short range_max()  {return USHRT_MAX;}
  static PFC_INLINE unsigned short zero()       {return 0;}
  static PFC_INLINE unsigned short float_one()  {return USHRT_MAX;}
};
//----------------------------------------------------------------------------


//============================================================================
// numeric_type<signed int>
//============================================================================
template<>
struct numeric_type<signed int>
{
  // type properties
  enum
  {
    is_float  =false,
    is_int    =true,
    is_signed =true
  };
  //--------------------------------------------------------------------------

  static PFC_INLINE signed int range_min()  {return INT_MIN;}
  static PFC_INLINE signed int range_max()  {return INT_MAX;}
  static PFC_INLINE signed int zero()       {return 0;}
  static PFC_INLINE signed int float_one()  {return INT_MAX;}
};
//----------------------------------------------------------------------------


//============================================================================
// numeric_type<unsigned int>
//============================================================================
template<>
struct numeric_type<unsigned int>
{
  // type properties
  enum
  {
    is_float  =false,
    is_int    =true,
    is_signed =false
  };
  //--------------------------------------------------------------------------

  static PFC_INLINE unsigned int range_min()  {return 0;}
  static PFC_INLINE unsigned int range_max()  {return UINT_MAX;}
  static PFC_INLINE unsigned int zero()       {return 0;}
  static PFC_INLINE unsigned int float_one()  {return UINT_MAX;}
};
//----------------------------------------------------------------------------


//============================================================================
// numeric_type<signed long>
//============================================================================
template<>
struct numeric_type<signed long>
{
  // type properties
  enum
  {
    is_float  =false,
    is_int    =true,
    is_signed =true
  };
  //--------------------------------------------------------------------------

  static PFC_INLINE signed long range_min()  {return LONG_MIN;}
  static PFC_INLINE signed long range_max()  {return LONG_MAX;}
  static PFC_INLINE signed long zero()       {return 0;}
  static PFC_INLINE signed long float_one()  {return LONG_MAX;}
};
//----------------------------------------------------------------------------


//============================================================================
// numeric_type<unsigned long>
//============================================================================
template<>
struct numeric_type<unsigned long>
{
  // type properties
  enum
  {
    is_float  =false,
    is_int    =true,
    is_signed =false
  };
  //--------------------------------------------------------------------------

  static PFC_INLINE unsigned long range_min()  {return 0;}
  static PFC_INLINE unsigned long range_max()  {return ULONG_MAX;}
  static PFC_INLINE unsigned long zero()       {return 0;}
  static PFC_INLINE unsigned long float_one()  {return ULONG_MAX;}
};
//----------------------------------------------------------------------------


//============================================================================
// numeric_type<float>
//============================================================================
template<>
struct numeric_type<float>
{
  // type properties
  enum
  {
    is_float  =true,
    is_int    =false,
    is_signed =true
  };
  //--------------------------------------------------------------------------

  static PFC_INLINE float range_min()  {return -FLT_MAX;}
  static PFC_INLINE float range_max()  {return +FLT_MAX;}
  static PFC_INLINE float zero()       {return 0.0f;}
  static PFC_INLINE float float_one()  {return 1.0f;}
};
//----------------------------------------------------------------------------


//============================================================================
// numeric_type<double>
//============================================================================
template<>
struct numeric_type<double>
{
  // type properties
  enum
  {
    is_float  =true,
    is_int    =false,
    is_signed =true
  };
  //--------------------------------------------------------------------------

  static PFC_INLINE double range_min()  {return -DBL_MAX;}
  static PFC_INLINE double range_max()  {return +DBL_MAX;}
  static PFC_INLINE double zero()       {return 0.0;}
  static PFC_INLINE double float_one()  {return 1.0;}
};
//----------------------------------------------------------------------------


//============================================================================
// numeric_type<long double>
//============================================================================
template<>
struct numeric_type<long double>
{
  // type properties
  enum
  {
    is_float  =true,
    is_int    =false,
    is_signed =true
  };
  //--------------------------------------------------------------------------

  static PFC_INLINE long double range_min()  {return -LDBL_MAX;}
  static PFC_INLINE long double range_max()  {return +LDBL_MAX;}
  static PFC_INLINE long double zero()       {return 0.0;}
  static PFC_INLINE long double float_one()  {return 1.0;}
};
//----------------------------------------------------------------------------
