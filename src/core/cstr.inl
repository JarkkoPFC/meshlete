//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// owner_cstr
//============================================================================
owner_cstr::owner_cstr()
  :m_cstr(0)
  ,m_is_owned(false)
{
}
//----

owner_cstr::owner_cstr(const owner_cstr &str_)
  :m_cstr(str_.m_cstr)
  ,m_is_owned(str_.m_is_owned)
{
  str_.m_is_owned=false;
}
//----

owner_cstr::owner_cstr(const char *cstr_, bool is_owned_)
  :m_cstr(cstr_)
  ,m_is_owned(is_owned_)
{
}
//----

owner_cstr::~owner_cstr()
{
  if(m_is_owned)
    PFC_MEM_FREE((void*)m_cstr);
}
//----

void owner_cstr::operator=(const owner_cstr &str_)
{
  // release current string and move ownership from given string
  if(m_is_owned)
    PFC_MEM_FREE((void*)m_cstr);
  m_cstr=str_.m_cstr;
  m_is_owned=str_.m_is_owned;
  str_.m_is_owned=false;
}
//----

void owner_cstr::set(const char *cstr_, bool is_owned_)
{
  // release current string and set new c-string
  if(m_is_owned)
    PFC_MEM_FREE((void*)m_cstr);
  m_cstr=cstr_;
  m_is_owned=is_owned_;
}
//----

void owner_cstr::reset()
{
  if(m_is_owned)
    PFC_MEM_FREE((void*)m_cstr);
  m_cstr=0;
  m_is_owned=false;
}
//----------------------------------------------------------------------------

const char *owner_cstr::c_str()
{
  return m_cstr;
}
//----------------------------------------------------------------------------


//============================================================================
// c-string management functions
//============================================================================
PFC_INLINE char *str_alloc(const char *str_, const alloc_site_info *site_info_)
{
  usize_t l=str_size(str_)+1;
  char *str=(char*)mem_alloc(l, site_info_);
  mem_copy(str, str_, l);
  return str;
}
//----

PFC_INLINE usize_t str_size(const char *s_)
{
  PFC_ASSERT_PEDANTIC(s_!=0);
  return usize_t(::strlen(s_));
}
//----

PFC_INLINE usize_t str_size(const wchar_t *s_)
{
  PFC_ASSERT_PEDANTIC(s_!=0);
  return usize_t(::wcslen(s_));
}
//----

PFC_INLINE usize_t wcstr_to_cstr(char *dst_, const wchar_t *src_, usize_t max_chars_)
{
  return usize_t(::wcstombs(dst_, src_, (size_t)max_chars_));
}
//----

PFC_INLINE usize_t cstr_to_wcstr(wchar_t *dst_, const char *src_, usize_t max_chars_)
{
  return usize_t(::mbstowcs(dst_, src_, (size_t)max_chars_));
}
//----------------------------------------------------------------------------

PFC_INLINE int str_diff(const char *s0_, const char *s1_)
{
  PFC_ASSERT_PEDANTIC(s0_ && s1_);
  return ::strcmp(s0_, s1_);
}
//----

PFC_INLINE int str_diff(const wchar_t *s0_, const wchar_t *s1_)
{
  PFC_ASSERT_PEDANTIC(s0_ && s1_);
  return ::wcscmp(s0_, s1_);
}
//----

PFC_INLINE int str_idiff(const char *s0_, const char *s1_)
{
  PFC_ASSERT_PEDANTIC(s0_ && s1_);
  return PFC_STRICMP(s0_, s1_);
}
//----

PFC_INLINE int str_idiff(const wchar_t *s0_, const wchar_t *s1_)
{
  PFC_ASSERT_PEDANTIC(s0_ && s1_);
  return PFC_WCSICMP(s0_, s1_);
}
//----

PFC_INLINE bool str_eq(const char *s0_, const char *s1_)
{
  PFC_ASSERT_PEDANTIC(s0_ && s1_);
  return ::strcmp(s0_, s1_)==0;
}
//----

PFC_INLINE bool str_eq(const wchar_t *s0_, const wchar_t *s1_)
{
  PFC_ASSERT_PEDANTIC(s0_ && s1_);
  return ::wcscmp(s0_, s1_)==0;
}
//----

PFC_INLINE bool str_eq(const char *s0_, const char *s1_, usize_t num_chars_)
{
  PFC_ASSERT_PEDANTIC(!num_chars_ || (s0_ && s1_));
  return ::strncmp(s0_, s1_, (size_t)num_chars_)==0;
}
//----

PFC_INLINE bool str_eq(const wchar_t *s0_, const wchar_t *s1_, usize_t num_chars_)
{
  PFC_ASSERT_PEDANTIC(!num_chars_ || (s0_ && s1_));
  return ::wcsncmp(s0_, s1_, (size_t)num_chars_)==0;
}
//----

PFC_INLINE bool str_ieq(const char *s0_, const char *s1_)
{
  PFC_ASSERT_PEDANTIC(s0_ && s1_);
  return PFC_STRICMP(s0_, s1_)==0;
}
//----

PFC_INLINE bool str_ieq(const wchar_t *s0_, const wchar_t *s1_)
{
  PFC_ASSERT_PEDANTIC(s0_ && s1_);
  return PFC_WCSICMP(s0_, s1_)==0;
}
//----

PFC_INLINE bool str_ieq(const char *s0_, const char *s1_, usize_t num_chars_)
{
  PFC_ASSERT_PEDANTIC(!num_chars_ || (s0_ && s1_));
  return PFC_STRNICMP(s0_, s1_, (size_t)num_chars_)==0;
}
//----

PFC_INLINE bool str_ieq(const wchar_t *s0_, const wchar_t *s1_, usize_t num_chars_)
{
  PFC_ASSERT_PEDANTIC(!num_chars_ || (s0_ && s1_));
  return PFC_WCSNICMP(s0_, s1_, (size_t)num_chars_)==0;
}
//----------------------------------------------------------------------------

PFC_INLINE char to_lower(char c_)
{
  return (char)::tolower(c_);
}
//----

PFC_INLINE wchar_t to_lower(wchar_t c_)
{
  return (wchar_t)::towlower(c_);
}
//----

PFC_INLINE char to_upper(char c_)
{
  return (char)::toupper(c_);
}
//----

PFC_INLINE wchar_t to_upper(wchar_t c_)
{
  return (wchar_t)::towupper(c_);
}
//----

PFC_INLINE void str_lower(char *s_)
{
  PFC_ASSERT_PEDANTIC(s_);
#ifdef PFC_COMPILER_MSVC
  ::_strlwr(s_);
#else
  while(*s_)
  {
    *s_=(char)::tolower(*s_);
    ++s_;
  }
#endif
}
//----

PFC_INLINE void str_lower(wchar_t *s_)
{
  PFC_ASSERT_PEDANTIC(s_);
#ifdef PFC_COMPILER_MSVC
  ::_wcslwr(s_);
#else
  while(*s_)
  {
    *s_=(wchar_t)::towlower(*s_);
    ++s_;
  }
#endif
}
//----

PFC_INLINE void str_upper(char *s_)
{
  PFC_ASSERT_PEDANTIC(s_);
#ifdef PFC_COMPILER_MSVC
  ::_strupr(s_);
#else
  while(*s_)
  {
    *s_=(char)::toupper(*s_);
    ++s_;
  }
#endif
}
//----

PFC_INLINE void str_upper(wchar_t *s_)
{
  PFC_ASSERT_PEDANTIC(s_);
#ifdef PFC_COMPILER_MSVC
  ::_wcsupr(s_);
#else
  while(*s_)
  {
    *s_=(wchar_t)::towupper(*s_);
    ++s_;
  }
#endif
}
//----

PFC_INLINE void str_lower(char *s_, usize_t num_chars_)
{
  PFC_ASSERT_PEDANTIC(s_);
  char *end=s_+num_chars_;
  while(s_<end)
  {
    *s_=(char)::tolower(*s_);
    ++s_;
  }
}
//----

PFC_INLINE void str_lower(wchar_t *s_, usize_t num_chars_)
{
  PFC_ASSERT_PEDANTIC(s_);
  wchar_t *end=s_+num_chars_;
  while(s_<end)
  {
    *s_=(wchar_t)::towlower(*s_);
    ++s_;
  }
}
//----

PFC_INLINE void str_upper(char *s_, usize_t num_chars_)
{
  PFC_ASSERT_PEDANTIC(s_);
  char *end=s_+num_chars_;
  while(s_<end)
  {
    *s_=(char)::toupper(*s_);
    ++s_;
  }
}
//----

PFC_INLINE void str_upper(wchar_t *s_, usize_t num_chars_)
{
  PFC_ASSERT_PEDANTIC(s_);
  wchar_t *end=s_+num_chars_;
  while(s_<end)
  {
    *s_=(wchar_t)::towupper(*s_);
    ++s_;
  }
}
//----------------------------------------------------------------------------

PFC_INLINE const char *str_find_whitespace(const char *s_)
{
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_>' ')
    ++s_;
  return s_;
}
//----

PFC_INLINE const wchar_t *str_find_whitespace(const wchar_t *s_)
{
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_>L' ')
    ++s_;
  return s_;
}
//----

PFC_INLINE char *str_find_whitespace(char *s_)
{
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_>' ')
    ++s_;
  return s_;
}
//----

PFC_INLINE wchar_t *str_find_whitespace(wchar_t *s_)
{
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_>L' ')
    ++s_;
  return s_;
}
//----------------------------------------------------------------------------

PFC_INLINE const char *str_skip_whitespace(const char *s_)
{
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_ && *s_<=' ')
    ++s_;
  return s_;
}
//----

PFC_INLINE const wchar_t *str_skip_whitespace(const wchar_t *s_)
{
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_ && *s_<=L' ')
    ++s_;
  return s_;
}
//----

PFC_INLINE char *str_skip_whitespace(char *s_)
{
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_ && *s_<=' ')
    ++s_;
  return s_;
}
//----

PFC_INLINE wchar_t *str_skip_whitespace(wchar_t *s_)
{
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_ && *s_<=L' ')
    ++s_;
  return s_;
}
//----------------------------------------------------------------------------

PFC_INLINE bool is_ascii(char c_)
{
  return unsigned(c_)<0x80;
}
//----

PFC_INLINE bool is_ascii(wchar_t c_)
{
  return unsigned(c_)<0x80;
}
//----

PFC_INLINE bool is_decimal(char c_)
{
  return c_>='0' && c_<='9';
}
//----

PFC_INLINE bool is_decimal(wchar_t c_)
{
  return c_>=L'0' && c_<=L'9';
}
//----

PFC_INLINE bool is_hex(char c_)
{
  return (c_>='0' && c_<='9') || (c_>='a' && c_<='f') || (c_>='A' && c_<='F');
}
//----

PFC_INLINE bool is_hex(wchar_t c_)
{
  return (c_>=L'0' && c_<=L'9') || (c_>=L'a' && c_<=L'f') || (c_>=L'A' && c_<=L'F');
}
//----

PFC_INLINE bool is_latin_alphabet(char c_)
{
  return (c_>='A' && c_<='Z') || (c_>='a' && c_<='z');
}
//----

PFC_INLINE bool is_latin_alphabet(wchar_t c_)
{
  return (c_>=L'A' && c_<=L'Z') || (c_>=L'a' && c_<=L'z');
}
//----

PFC_INLINE bool is_latin_alphanumeric(char c_)
{
  return (c_>='0' && c_<='9') || (c_>='A' && c_<='Z') || (c_>='a' && c_<='z');
}
//----

PFC_INLINE bool is_latin_alphanumeric(wchar_t c_)
{
  return (c_>=L'0' && c_<=L'9') || (c_>=L'A' && c_<=L'Z') || (c_>=L'a' && c_<=L'z');
}
//----

PFC_INLINE bool is_whitespace(char c_)
{
  return c_<=' ';
}
//----

PFC_INLINE bool is_whitespace(wchar_t c_)
{
  return c_<=L' ';
}
//----

PFC_INLINE bool is_whitespace(const char *s_)
{
  // check if all characters in the string are whitespace 
  while(*s_)
    if(*s_++>' ')
      return false;
  return true;
}
//----

PFC_INLINE bool is_whitespace(const wchar_t *s_)
{
  // check if all characters in the string are whitespace 
  while(*s_)
    if(*s_++>L' ')
      return false;
  return true;
}
//----------------------------------------------------------------------------

PFC_INLINE usize_t str_to_float(float &v_, const char *s_)
{
    float64_t v;
    usize_t s=str_to_float64(v, s_);
    v_=(float)v;
    return s;
}
//----

PFC_INLINE usize_t str_to_int(int &v_, const char *s_)
{
    int64_t v;
    usize_t s=str_to_int64(v, s_);
    v_=(int)v;
    return s;
}
//---

PFC_INLINE unsigned dec_char_to_uint(char c_)
{
  // convert decimal character to 
  PFC_ASSERT_PEDANTIC_MSG(c_>='0' && c_<='9', ("Invalid character '%c' for decical char->value conversion\r\n", c_));
  return c_-'0';
}
//----

PFC_INLINE unsigned dec_char_to_uint(wchar_t c_)
{
  // convert decimal character to 
  PFC_ASSERT_PEDANTIC_MSG(c_>=L'0' && c_<=L'9', ("Invalid character '%c' for decical char->value conversion\r\n", c_));
  return char(c_)-'0';
}
//----

PFC_INLINE unsigned hex_char_to_uint(char c_)
{
  if(c_>='0' && c_<='9')
    return c_-'0';
  if(c_>='a' && c_<='f')
    return c_-'a'+10;
  if(c_>='A' && c_<='F')
    return c_-'A'+10;
  PFC_ASSERT_PEDANTIC_MSG(false, ("Invalid character '%c' for hex char->value conversion\r\n", c_));
  return 0;
}
//----

PFC_INLINE unsigned hex_char_to_uint(wchar_t c_)
{
  if(c_>=L'0' && c_<=L'9')
    return char(c_)-'0';
  if(c_>=L'a' && c_<=L'f')
    return char(c_)-L'a'+10;
  if(c_>=L'A' && c_<=L'F')
    return char(c_)-'A'+10;
  PFC_ASSERT_PEDANTIC_MSG(false, ("Invalid character '%c' for hex char->value conversion\r\n", c_));
  return 0;
}
//----------------------------------------------------------------------------
