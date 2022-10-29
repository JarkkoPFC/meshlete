//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_CSTR_H
#define PFC_CORE_CSTR_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core/core.h"
#include <wchar.h>
#include <ctype.h>
#include <wctype.h>
namespace pfc
{

// new
class owner_cstr;
PFC_INLINE char *str_alloc(const char *str_, const alloc_site_info *site_info_=0);
PFC_INLINE usize_t str_size(const char*);
PFC_INLINE usize_t str_size(const wchar_t*);
usize_t str_lines(const char*);
usize_t strn_lines(const char*, usize_t num_chars_);
usize_t str_copy(char *dst_, const char *src_, usize_t buffer_size_);
usize_t str_copy(wchar_t *dst_, const wchar_t *src_, usize_t buffer_size_);
PFC_INLINE usize_t wcstr_to_cstr(char *dst_, const wchar_t *src_, usize_t max_chars_);
PFC_INLINE usize_t cstr_to_wcstr(wchar_t *dst_, const char *src_, usize_t max_chars_);
// comparison
PFC_INLINE int str_diff(const char*, const char*);
PFC_INLINE int str_diff(const wchar_t*, const wchar_t*);
PFC_INLINE int str_idiff(const char*, const char*);
PFC_INLINE int str_idiff(const wchar_t*, const wchar_t*);
PFC_INLINE bool str_eq(const char*, const char*);
PFC_INLINE bool str_eq(const wchar_t*, const wchar_t*);
PFC_INLINE bool str_eq(const char*, const char*, usize_t num_chars_);
PFC_INLINE bool str_eq(const wchar_t*, const wchar_t*, usize_t num_chars_);
PFC_INLINE bool str_ieq(const char*, const char*);
PFC_INLINE bool str_ieq(const wchar_t*, const wchar_t*);
PFC_INLINE bool str_ieq(const char*, const char*, usize_t num_chars_);
PFC_INLINE bool str_ieq(const wchar_t*, const wchar_t*, usize_t num_chars_);
bool str_eq_wildcard(const char*, const char *match_pattern_);
bool str_eq_wildcard(const wchar_t*, const wchar_t *match_pattern_);
bool str_ieq_wildcard(const char*, const char *match_pattern_);
bool str_ieq_wildcard(const wchar_t*, const wchar_t *match_pattern_);
// case conversion
PFC_INLINE char to_lower(char);
PFC_INLINE wchar_t to_lower(wchar_t);
PFC_INLINE char to_upper(char);
PFC_INLINE wchar_t to_upper(wchar_t);
PFC_INLINE void str_lower(char*);
PFC_INLINE void str_lower(wchar_t*);
PFC_INLINE void str_upper(char*);
PFC_INLINE void str_upper(wchar_t*);
PFC_INLINE void str_lower(char*, usize_t num_chars_);
PFC_INLINE void str_lower(wchar_t*, usize_t num_chars_);
PFC_INLINE void str_upper(char*, usize_t num_chars_);
PFC_INLINE void str_upper(wchar_t*, usize_t num_chars_);
// search
const char *str_find(const char*, char);
const wchar_t *str_find(const wchar_t*, wchar_t);
char *str_find(char*, char);
wchar_t *str_find(wchar_t*, wchar_t);
const char *str_find(const char*, const char *chars_);
const wchar_t *str_find(const wchar_t*, const wchar_t *chars_);
char *str_find(char*, const char *chars_);
wchar_t *str_find(wchar_t*, const wchar_t *chars_);
const char *str_ifind(const char*, char);
const wchar_t *str_ifind(const wchar_t*, wchar_t);
char *str_ifind(char*, char);
wchar_t *str_ifind(wchar_t*, wchar_t);
const char *str_ifind(const char*, const char *chars_);
const wchar_t *str_ifind(const wchar_t*, const wchar_t *chars_);
char *str_ifind(char*, const char *chars_);
wchar_t *str_ifind(wchar_t*, const wchar_t *chars_);
const char *str_find_substr(const char*, const char *substr_);
const wchar_t *str_find_substr(const wchar_t*, const wchar_t *substr_);
char *str_find_substr(char*, const char *substr_);
wchar_t *str_find_substr(wchar_t*, const wchar_t *substr_);
int str_find_substr(const char*, const char*const*);
int str_find_substr(const wchar_t*, const wchar_t*const*);
const char *str_ifind_substr(const char*, const char *substr_);
const wchar_t *str_ifind_substr(const wchar_t*, const wchar_t *substr_);
char *str_ifind_substr(char*, const char *substr_);
wchar_t *str_ifind_substr(wchar_t*, const wchar_t *substr_);
const char *str_find_next_line(const char*);
const wchar_t *str_find_next_line(const wchar_t*);
char *str_find_next_line(char*);
wchar_t *str_find_next_line(wchar_t*);
PFC_INLINE const char *str_find_whitespace(const char*);
PFC_INLINE const wchar_t *str_find_whitespace(const wchar_t*);
PFC_INLINE char *str_find_whitespace(char*);
PFC_INLINE wchar_t *str_find_whitespace(wchar_t*);
// skipping
PFC_INLINE const char *str_skip_whitespace(const char*);
const char *str_skip_whitespace(const char*, const char *extra_chars_);
PFC_INLINE const wchar_t *str_skip_whitespace(const wchar_t*);
const wchar_t *str_skip_whitespace(const wchar_t*, const wchar_t *extra_chars_);
PFC_INLINE char *str_skip_whitespace(char*);
char *str_skip_whitespace(char*, const char *extra_chars_);
PFC_INLINE wchar_t *str_skip_whitespace(wchar_t*);
wchar_t *str_skip_whitespace(wchar_t*, const wchar_t *extra_chars_);
// manipulation
void str_replace(char*, char char_to_replace_, char replacement_);
void str_replace(wchar_t*, wchar_t char_to_replace_, wchar_t replacement_);
char *str_split_words(char*);
wchar_t *str_split_words(wchar_t*);
usize_t str_strip_chars(char*, char);
usize_t str_strip_chars(wchar_t*, wchar_t);
usize_t str_strip_substrs(char*, const char*);
usize_t str_strip_substrs(wchar_t*, const wchar_t*);
usize_t str_strip_whitespace(char*);
usize_t str_strip_whitespace(wchar_t*);
usize_t str_strip_extra_chars(char*, char);
usize_t str_strip_extra_chars(wchar_t*, wchar_t);
usize_t str_strip_extra_substrs(char*, const char*);
usize_t str_strip_extra_substrs(wchar_t*, const wchar_t*);
usize_t str_strip_extra_whitespace(char*);
usize_t str_strip_extra_whitespace(wchar_t*);
usize_t str_strip_outer_chars(char*, char, bool strip_all_=false);
usize_t str_strip_outer_chars(wchar_t*, wchar_t, bool strip_all_=false);
usize_t str_strip_outer_substrs(char*, const char*, bool strip_all_=false);
usize_t str_strip_outer_substrs(wchar_t*, const wchar_t*, bool strip_all_=false);
usize_t str_strip_outer_whitespace(char*, bool strip_all_=false);
usize_t str_strip_outer_whitespace(wchar_t*, bool strip_all_=false);
// type check
PFC_INLINE bool is_ascii(char);
PFC_INLINE bool is_ascii(wchar_t);
bool is_ascii(char*);
bool is_ascii(wchar_t*);
bool is_ascii(char*, usize_t num_bytes_);
bool is_ascii(wchar_t*, usize_t num_bytes_);
PFC_INLINE bool is_decimal(char);
PFC_INLINE bool is_decimal(wchar_t);
PFC_INLINE bool is_hex(char);
PFC_INLINE bool is_hex(wchar_t);
PFC_INLINE bool is_latin_alphabet(char);
PFC_INLINE bool is_latin_alphabet(wchar_t);
PFC_INLINE bool is_latin_alphanumeric(char);
PFC_INLINE bool is_latin_alphanumeric(wchar_t);
PFC_INLINE bool is_whitespace(char);
PFC_INLINE bool is_whitespace(wchar_t);
PFC_INLINE bool is_whitespace(const char*);
PFC_INLINE bool is_whitespace(const wchar_t*);
// conversion to numerical value
usize_t str_to_float64(float64_t&, const char*);
PFC_INLINE usize_t str_to_float(float&, const char*);
usize_t str_to_int64(int64_t&, const char*);
PFC_INLINE usize_t str_to_int(int&, const char*);
int str_to_scalar64(float64_t&, int64_t&, const char*); // returns positive length for float, negative length for int
PFC_INLINE unsigned dec_char_to_uint(char);
PFC_INLINE unsigned dec_char_to_uint(wchar_t);
PFC_INLINE unsigned hex_char_to_uint(char);
PFC_INLINE unsigned hex_char_to_uint(wchar_t);
//----------------------------------------------------------------------------


//============================================================================
// memory management
//============================================================================
#ifdef PFC_BUILDOP_MEMORY_TRACKING
#define PFC_STR_ALLOC(str__) pfc::str_alloc(str__, &get_alloc_site_info<__COUNTER__>(__FILE__, PFC_FUNCTION, __LINE__))
#else
#define PFC_STR_ALLOC(str__) pfc::str_alloc(str__)
#endif
//----------------------------------------------------------------------------


//============================================================================
// owner_cstr
//============================================================================
class owner_cstr
{
public:
  // construction
  PFC_INLINE owner_cstr();
  PFC_INLINE owner_cstr(const owner_cstr&);
  PFC_INLINE owner_cstr(const char *cstr_, bool is_owned_);
  PFC_INLINE ~owner_cstr();
  PFC_INLINE void operator=(const owner_cstr&);
  PFC_INLINE void set(const char *cstr_, bool is_owned_);
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE const char *c_str();
  //--------------------------------------------------------------------------

private:
  const char *m_cstr;
  mutable bool m_is_owned;
};
//----------------------------------------------------------------------------

//============================================================================
#include "cstr.inl"
} // namespace pfc
#endif
