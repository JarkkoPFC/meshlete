//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_CONFIG_H
#define PFC_CORE_CONFIG_H
//----------------------------------------------------------------------------


//============================================================================
// build option config
//============================================================================
#define PFC_BUILDOP_INTRINSICS               // use compiler intrinsics
// per build config
#define PFC_BUILDOP_MEMORY_TRACKING          // track memory usage
#define PFC_BUILDOP_EXCEPTIONS               // support exceptions
#define PFC_BUILDOP_LOGS                     // enable logging
#define PFC_BUILDOP_WARNINGS                 // enable warnings
#define PFC_BUILDOP_WARNINGS_FILEPATH        // write file-path in warning messages
#define PFC_BUILDOP_ERRORS                   // enable errors
#define PFC_BUILDOP_ERRORS_FILEPATH          // write file-path in error messages
#define PFC_BUILDOP_ASSERTS                  // enable asserts
#define PFC_BUILDOP_CHECKS                   // enable checks
#define PFC_BUILDOP_PEDANTIC                 // enable pedantic asserts & checks
#define PFC_BUILDOP_PROFILING                // enable performance profiling
#define PFC_BUILDOP_SAFE_CASTS               // validate safe_cast results (otherwise just static_cast)
#define PFC_BUILDOP_SHADER_RELOAD            // support run-time shader reloading
#define PFC_BUILDOP_SHADER_RESOURCE_CHECKS   // check for valid shader resource
//----
#ifdef PFC_RETAIL
// retail build options
#undef PFC_BUILDOP_MEMORY_TRACKING
#undef PFC_BUILDOP_EXCEPTIONS
#undef PFC_BUILDOP_LOGS
#undef PFC_BUILDOP_WARNINGS
#undef PFC_BUILDOP_ERRORS
#undef PFC_BUILDOP_ASSERTS
#undef PFC_BUILDOP_CHECKS
#undef PFC_BUILDOP_PEDANTIC
#undef PFC_BUILDOP_PROFILING
#undef PFC_BUILDOP_SAFE_CASTS
#undef PFC_BUILDOP_SHADER_RELOAD
#undef PFC_BUILDOP_SHADER_RESOURCE_CHECKS
#endif
// debug options
#define PFC_BUILDOP_HEAP_CHECKS
//----------------------------------------------------------------------------



//============================================================================
// build, platform and compiler strings
//============================================================================
#ifdef PFC_DEBUG
#define PFC_BUILD_STR debug
#elif defined(PFC_RELEASE)
#define PFC_BUILD_STR release
#elif defined(PFC_RETAIL)
#define PFC_BUILD_STR retail
#else
#error Target build not specified.
#endif
//----

#ifdef PFC_PLATFORM_WIN32
#define PFC_PLATFORM_STR win32
#define PFC_PLATFORM_SRC_STR win
#define PFC_PLATFORM_32BIT
#elif defined(PFC_PLATFORM_WIN64)
#define PFC_PLATFORM_STR win64
#define PFC_PLATFORM_SRC_STR win
#define PFC_PLATFORM_64BIT
#elif defined(PFC_PLATFORM_LINUX32)
#undef linux
#define PFC_PLATFORM_STR linux32
#define PFC_PLATFORM_SRC_STR linux
#define PFC_PLATFORM_32BIT
#elif defined(PFC_PLATFORM_LINUX64)
#undef linux
#define PFC_PLATFORM_STR linux64
#define PFC_PLATFORM_SRC_STR linux
#define PFC_PLATFORM_64BIT
#else
#error Target platform not specified.
#endif
//----

#ifdef PFC_COMPILER_MSVC2008
#define PFC_COMPILER_MSVC
#define PFC_COMPILER_STR vs2008
#define PFC_COMPILER_SRC_STR msvc
#define PFC_COMPILER_LIB_EXT .lib
#undef PFC_ENGINEOP_D3D12
#elif defined(PFC_COMPILER_MSVC2010)
#define PFC_COMPILER_MSVC
#define PFC_COMPILER_STR vs2010
#define PFC_COMPILER_SRC_STR msvc
#define PFC_COMPILER_LIB_EXT .lib
#undef PFC_ENGINEOP_D3D12
#elif defined(PFC_COMPILER_MSVC2012)
#define PFC_COMPILER_MSVC
#define PFC_COMPILER_STR vs2012
#define PFC_COMPILER_SRC_STR msvc
#define PFC_COMPILER_LIB_EXT .lib
#undef PFC_ENGINEOP_D3D12
#elif defined(PFC_COMPILER_MSVC2013)
#define PFC_COMPILER_MSVC
#define PFC_COMPILER_STR vs2013
#define PFC_COMPILER_SRC_STR msvc
#define PFC_COMPILER_LIB_EXT .lib
#elif defined(PFC_COMPILER_MSVC2015)
#define PFC_COMPILER_MSVC
#define PFC_COMPILER_STR vs2015
#define PFC_COMPILER_SRC_STR msvc
#define PFC_COMPILER_LIB_EXT .lib
#elif defined(PFC_COMPILER_MSVC2017)
#define PFC_COMPILER_MSVC
#define PFC_COMPILER_STR vs2017
#define PFC_COMPILER_SRC_STR msvc
#define PFC_COMPILER_LIB_EXT .lib
#elif defined(PFC_COMPILER_MSVC2019)
#define PFC_COMPILER_MSVC
#define PFC_COMPILER_STR vs2019
#define PFC_COMPILER_SRC_STR msvc
#define PFC_COMPILER_LIB_EXT .lib
#elif defined(PFC_COMPILER_GCC)
#define PFC_COMPILER_GCC
#define PFC_COMPILER_STR gcc
#define PFC_COMPILER_SRC_STR gcc
#define PFC_COMPILER_LIB_EXT .a
#else
#error Target compiler not supported.
#endif
//----------------------------------------------------------------------------


//============================================================================
// pre-compiler macros
//============================================================================
#define PFC_COMMA ,
// stringify, e.g. PFC_STR(x) => "x"
#define PFC_STR(x__) PFC_STR_DO(x__)
#define PFC_STR_DO(x__) #x__
// concatenation of 2-10 values, e.g. PFC_CAT3(a, b, c) => abc
#define PFC_CAT2(a__, b__) PFC_CAT2_DO(a__, b__)
#define PFC_CAT2_DO(a__, b__) a__##b__
#define PFC_CAT3(a__, b__, c__) PFC_CAT3_DO(a__, b__, c__)
#define PFC_CAT3_DO(a__, b__, c__) a__##b__##c__
#define PFC_CAT4(a__, b__, c__, d__) PFC_CAT4_DO(a__, b__, c__, d__)
#define PFC_CAT4_DO(a__, b__, c__, d__) a__##b__##c__##d__
#define PFC_CAT5(a__, b__, c__, d__, e__) PFC_CAT5_DO(a__, b__, c__, d__, e__)
#define PFC_CAT5_DO(a__, b__, c__, d__, e__) a__##b__##c__##d__##e__
#define PFC_CAT6(a__, b__, c__, d__, e__, f__) PFC_CAT6_DO(a__, b__, c__, d__, e__, f__)
#define PFC_CAT6_DO(a__, b__, c__, d__, e__, f__) a__##b__##c__##d__##e__##f__
#define PFC_CAT7(a__, b__, c__, d__, e__, f__, g__) PFC_CAT7_DO(a__, b__, c__, d__, e__, f__, g__)
#define PFC_CAT7_DO(a__, b__, c__, d__, e__, f__, g__) a__##b__##c__##d__##e__##f__##g__
#define PFC_CAT8(a__, b__, c__, d__, e__, f__, g__, h__) PFC_CAT8_DO(a__, b__, c__, d__, e__, f__, g__, h__)
#define PFC_CAT8_DO(a__, b__, c__, d__, e__, f__, g__, h__) a__##b__##c__##d__##e__##f__##g__##h__
#define PFC_CAT9(a__, b__, c__, d__, e__, f__, g__, h__, i__) PFC_CAT9_DO(a__, b__, c__, d__, e__, f__, g__, h__, i__)
#define PFC_CAT9_DO(a__, b__, c__, d__, e__, f__, g__, h__, i__) a__##b__##c__##d__##e__##f__##g__##h__##i__
#define PFC_CAT10(a__, b__, c__, d__, e__, f__, g__, h__, i__, j__) PFC_CAT10_DO(a__, b__, c__, d__, e__, f__, g__, h__, i__, j__)
#define PFC_CAT10_DO(a__, b__, c__, d__, e__, f__, g__, h__, i__, j__) a__##b__##c__##d__##e__##f__##g__##h__##i__##j__
//----------------------------------------------------------------------------


//============================================================================
// compile specific defines
//============================================================================
// MSVC
#if defined(PFC_COMPILER_MSVC)
#define NOMINMAX
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#define PFC_INLINE __forceinline
#ifdef PFC_DEBUG
#define PFC_ABORT_FUNC() {__debugbreak();}
#else
#define PFC_ABORT_FUNC() {exit(-1);}
#endif
#define PFC_STRICMP ::_stricmp
#define PFC_WCSICMP ::_wcsicmp
#define PFC_STRNICMP ::_strnicmp
#define PFC_WCSNICMP ::_wcsnicmp
#define PFC_FUNCTION __FUNCTION__
#define PFC_ALIGN(v__) __declspec(align(v__))
#define PFC_ALIGN_CACHE __declspec(align(128))
#define PFC_ALIGNED_MALLOC(size__, align__) _aligned_malloc((size_t)size__, align__)
#define PFC_ALIGNED_FREE(ptr__) _aligned_free(ptr__)
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#define PFC_CONST_INT64(v__) int64_t(v__)
#define PFC_CONST_UINT64(v__) uint64_t(v__)
#define PFC_SNPRINTF _snprintf
#define PFC_ALLOCA _alloca
#define PFC_THREAD_VAR __declspec(thread)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <intrin.h>

// instrinsics
#ifdef PFC_BUILDOP_INTRINSICS
// up to 32-bit intrinsics
#define PFC_INTRINSIC_LSB32(res__, v__)           {unsigned long __intrinsic_res; _BitScanForward(&__intrinsic_res, v__); res__=uint32_t(1)<<uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_MSB32(res__, v__)           {unsigned long __intrinsic_res; _BitScanReverse(&__intrinsic_res, v__); res__=uint32_t(1)<<uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_LSBPOS32(res__, v__)        {unsigned long __intrinsic_res; _BitScanForward(&__intrinsic_res, v__); res__=uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_MSBPOS32(res__, v__)        {unsigned long __intrinsic_res; _BitScanReverse(&__intrinsic_res, v__); res__=uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_BSWAP32(res__, v__)         {res__=(uint32_t)_byteswap_ulong(*reinterpret_cast<const volatile uint32_t*>(v__));}
#define PFC_INTRINSIC_BSWAP16(res__, v__)         {res__=(uint16_t)_byteswap_ushort(*reinterpret_cast<const volatile uint16_t*>(v__));}
#define PFC_INTRINSIC_ROL32(res__, v__, shift__)  {res__=_rotl(v__, shift__);}
#define PFC_INTRINSIC_ROR32(res__, v__, shift__)  {res__=_rotr(v__, shift__);}
#define PFC_INTRINSIC_ROL16(res__, v__, shift__)  {res__=_rotl16(v__, shift__);}
#define PFC_INTRINSIC_ROR16(res__, v__, shift__)  {res__=_rotr16(v__, shift__);}
#define PFC_INTRINSIC_ROL8(res__, v__, shift__)   {res__=_rotl8(v__, shift__);}
#define PFC_INTRINSIC_ROR8(res__, v__, shift__)   {res__=_rotr8(v__, shift__);}
#ifdef PFC_PLATFORM_64BIT
// 64-bit intrinsics
#define PFC_INTRINSIC_LSB64(res__, v__)           {unsigned long __intrinsic_res; _BitScanForward64(&__intrinsic_res, v__); res__=uint64_t(1)<<uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_MSB64(res__, v__)           {unsigned long __intrinsic_res; _BitScanReverse64(&__intrinsic_res, v__); res__=uint64_t(1)<<uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_LSBPOS64(res__, v__)        {unsigned long __intrinsic_res; _BitScanForward64(&__intrinsic_res, v__); res__=uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_MSBPOS64(res__, v__)        {unsigned long __intrinsic_res; _BitScanReverse64(&__intrinsic_res, v__); res__=uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_BSWAP64(res__, v__)         {res__=(uint64_t)_byteswap_uint64(*reinterpret_cast<const volatile uint64_t*>(v__));}
#define PFC_INTRINSIC_ROL64(res__, v__, shift__)  {res__=_rotl64(v__, shift__);}
#define PFC_INTRINSIC_ROR64(res__, v__, shift__)  {res__=_rotr64(v__, shift__);}
#endif
#endif

// disable some compiler warnings
#pragma warning(disable:4100)  // "'identifier' : unreferenced formal parameter"
#pragma warning(disable:4127)  // "conditional expression is constant"
#pragma warning(disable:4324)  // "structure was padded due to __declspec(align())"
#pragma warning(disable:4505)  // "'function' : unreferenced local function has been removed"
#pragma warning(disable:4996)  // "'function' : was declared deprecated"
#pragma warning(disable:6326)  // "potential comparison of a constant with another constant"
#if defined(PFC_RELEASE) || defined(PFC_RETAIL)
#pragma warning(disable:4702)  // "unreachable code"
#endif
#ifdef PFC_RETAIL
#pragma warning(disable:4930)  // "'prototype': prototyped function not called (was a variable definition intended?)"
#endif

// GCC
#elif defined(PFC_COMPILER_GCC)
#define PFC_INLINE __attribute__((always_inline))
#ifdef PFC_DEBUG
#define PFC_ABORT_FUNC() {__builtin_trap();}
#else
#define PFC_ABORT_FUNC() {exit(-1);}
#endif
#define PFC_STRICMP ::strcasecmp
#define PFC_WCSICMP ::wcscasecmp
#define PFC_STRNICMP ::strncasecmp
#define PFC_WCSNICMP ::wcsncasecmp
#define PFC_FUNCTION __PRETTY_FUNCTION__
#define PFC_ALIGN(v__) __attribute__((aligned(v__)))
#define PFC_ALIGN_CACHE __attribute__((aligned(128)))
#define PFC_ALIGNED_MALLOC(size__, align__) _mm_malloc(size__, align__)
#define PFC_ALIGNED_FREE(ptr__) _mm_free(ptr__)
typedef long long int64_t;
typedef unsigned long long uint64_t;
#define PFC_CONST_INT64(v__) int64_t(v__##LL)
#define PFC_CONST_UINT64(v__) uint64_t(v__##LLU)
#define PFC_SNPRINTF snprintf
#define PFC_ALLOCA alloca
#define PFC_THREAD_VAR __thread
#endif
//----------------------------------------------------------------------------

//============================================================================
#endif
