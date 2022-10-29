//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "core/cstr.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// low-level c-string management
//============================================================================
usize_t pfc::str_lines(const char *str_)
{
  // count number of lines in given length string
  const char *s=str_;
  usize_t num_lines=1;
  while(true)
  {
    s=str_find(s, '\n');
    if(!s)
      break;
    ++s;
    ++num_lines;
  }
  return num_lines;
}
//----

usize_t pfc::strn_lines(const char *str_, usize_t num_chars_)
{
  // count number of lines in given length string
  const char *s=str_;
  usize_t num_lines=1;
  while(true)
  {
    s=str_find(s, '\n');
    if(!s || usize_t(s-str_)>=num_chars_)
      break;
    ++s;
    ++num_lines;
  }
  return num_lines;
}
//----------------------------------------------------------------------------

usize_t pfc::str_copy(char *dst_, const char *src_, usize_t buffer_size_)
{
  // check for over sized source string
  PFC_ASSERT_PEDANTIC(!buffer_size_ || (dst_ && src_));
  usize_t srclen=(usize_t)::strlen(src_);
  if(srclen>=buffer_size_)
  {
    mem_copy(dst_, src_, buffer_size_-1);
    dst_[buffer_size_-1]=0;
    return buffer_size_-1;
  }

  // copy string
  mem_copy(dst_, src_, srclen+1);
  return srclen;
}
//----

usize_t pfc::str_copy(wchar_t *dst_, const wchar_t *src_, usize_t buffer_size_)
{
  // check for over sized source string
  PFC_ASSERT_PEDANTIC(!buffer_size_ || (dst_ && src_));
  usize_t srclen=(usize_t)::wcslen(src_);
  if(srclen>=buffer_size_)
  {
    mem_copy(dst_, src_, (buffer_size_-1)*sizeof(wchar_t));
    dst_[buffer_size_-1]=0;
    return buffer_size_-1;
  }

  // copy string
  mem_copy(dst_, src_, (srclen+1)*sizeof(wchar_t));
  return srclen;
}
//----------------------------------------------------------------------------

bool pfc::str_eq_wildcard(const char *s_, const char *match_pattern_)
{
  // iterate through the two strings checking matches with wild-card chars
  const char *asterisk_pos=0;
  while(*s_)
  {
    // update the most recent asterisk position in the match pattern
    if(*match_pattern_=='*')
      asterisk_pos=match_pattern_;

    // check matching or '?' wild-card character
    if(*s_==*match_pattern_ || *match_pattern_=='?')
    {
      ++s_;
      ++match_pattern_;
    }
    else
    {
      // check for active asterisk wild-card char
      if(!asterisk_pos)
        return false;

      // consume string char and also pattern char if it matches string
      match_pattern_=asterisk_pos;
      if(match_pattern_[1]==*s_)
        match_pattern_+=2;
      ++s_;
    }
  }

  // skip trailing '*' chars and return if both strings are consumed for match
  while(*match_pattern_=='*')
    ++match_pattern_;
  return !*s_ && !*match_pattern_;
}
//----

bool pfc::str_eq_wildcard(const wchar_t *s_, const wchar_t *match_pattern_)
{
  // iterate through the two strings checking matches with wild-card chars
  const wchar_t *asterisk_pos=0;
  while(*s_)
  {
    // update the most recent asterisk position in the match pattern
    if(*match_pattern_==L'*')
      asterisk_pos=match_pattern_;

    // check matching or '?' wild-card character
    if(*s_==*match_pattern_ || *match_pattern_==L'?')
    {
      ++s_;
      ++match_pattern_;
    }
    else
    {
      // check for active asterisk wild-card char
      if(!asterisk_pos)
        return false;

      // consume string char and also pattern char if it matches string
      match_pattern_=asterisk_pos;
      if(match_pattern_[1]==*s_)
        match_pattern_+=2;
      ++s_;
    }
  }

  // skip trailing '*' chars and return if both strings are consumed for match
  while(*match_pattern_==L'*')
    ++match_pattern_;
  return !*s_ && !*match_pattern_;
}
//----

bool pfc::str_ieq_wildcard(const char *s_, const char *match_pattern_)
{
  // iterate through the two strings checking matches with wild-card chars
  const char *asterisk_pos=0;
  while(*s_)
  {
    // update the most recent asterisk position in the match pattern
    if(*match_pattern_=='*')
      asterisk_pos=match_pattern_;

    // check matching or '?' wild-card character
    if(::tolower(*s_)==::tolower(*match_pattern_) || *match_pattern_=='?')
    {
      ++s_;
      ++match_pattern_;
    }
    else
    {
      // check for active asterisk wild-card char
      if(!asterisk_pos)
        return false;

      // consume string char and also pattern char if it matches string
      match_pattern_=asterisk_pos;
      if(::tolower(match_pattern_[1])==::tolower(*s_))
        match_pattern_+=2;
      ++s_;
    }
  }

  // skip trailing '*' chars and return if both strings are consumed for match
  while(*match_pattern_=='*')
    ++match_pattern_;
  return !*s_ && !*match_pattern_;
}
//----

bool pfc::str_ieq_wildcard(const wchar_t *s_, const wchar_t *match_pattern_)
{
  // iterate through the two strings checking matches with wild-card chars
  const wchar_t *asterisk_pos=0;
  while(*s_)
  {
    // update the most recent asterisk position in the match pattern
    if(*match_pattern_==L'*')
      asterisk_pos=match_pattern_;

    // check matching or '?' wild-card character
    if(::tolower(*s_)==::tolower(*match_pattern_) || *match_pattern_==L'?')
    {
      ++s_;
      ++match_pattern_;
    }
    else
    {
      // check for active asterisk wild-card char
      if(!asterisk_pos)
        return false;

      // consume string char and also pattern char if it matches string
      match_pattern_=asterisk_pos;
      if(::tolower(match_pattern_[1])==::tolower(*s_))
        match_pattern_+=2;
      ++s_;
    }
  }

  // skip trailing '*' chars and return if both strings are consumed for match
  while(*match_pattern_==L'*')
    ++match_pattern_;
  return !*s_ && !*match_pattern_;
}
//----------------------------------------------------------------------------

const char *pfc::str_find(const char *s_, char c_)
{
  // search for character from the string
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_)
  {
    if(*s_==c_)
      return s_;
    ++s_;
  }
  return 0;
}
//----

const wchar_t *pfc::str_find(const wchar_t *s_, wchar_t c_)
{
  // search for character from the string
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_)
  {
    if(*s_==c_)
      return s_;
    ++s_;
  }
  return 0;
}
//----

char *pfc::str_find(char *s_, char c_)
{
  // search for character from the string
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_)
  {
    if(*s_==c_)
      return s_;
    ++s_;
  }
  return 0;
}
//----

wchar_t *pfc::str_find(wchar_t *s_, wchar_t c_)
{
  // search for character from the string
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_)
  {
    if(*s_==c_)
      return s_;
    ++s_;
  }
  return 0;
}
//----

const char *pfc::str_find(const char *s_, const char *chars_)
{
  // search for given characters from the string
  PFC_ASSERT(s_ && chars_);
  usize_t num_chars=(usize_t)::strlen(chars_);
  while(*s_)
  {
    char c=*s_;
    for(usize_t i=0; i<num_chars; ++i)
      if(chars_[i]==c)
        return s_;
    ++s_;
  }
  return 0;
}
//----

const wchar_t *pfc::str_find(const wchar_t *s_, const wchar_t *chars_)
{
  // search for given characters from the string
  PFC_ASSERT(s_ && chars_);
  usize_t num_chars=(usize_t)::wcslen(chars_);
  while(*s_)
  {
    wchar_t c=*s_;
    for(usize_t i=0; i<num_chars; ++i)
      if(chars_[i]==c)
        return s_;
    ++s_;
  }
  return 0;
}
//----

char *pfc::str_find(char *s_, const char *chars_)
{
  // search for given characters from the string
  PFC_ASSERT(s_ && chars_);
  usize_t num_chars=(usize_t)::strlen(chars_);
  while(*s_)
  {
    char c=*s_;
    for(usize_t i=0; i<num_chars; ++i)
      if(chars_[i]==c)
        return s_;
    ++s_;
  }
  return 0;
}
//----

wchar_t *pfc::str_find(wchar_t *s_, const wchar_t *chars_)
{
  // search for given characters from the string
  PFC_ASSERT(s_ && chars_);
  usize_t num_chars=(usize_t)::wcslen(chars_);
  while(*s_)
  {
    wchar_t c=*s_;
    for(usize_t i=0; i<num_chars; ++i)
      if(chars_[i]==c)
        return s_;
    ++s_;
  }
  return 0;
}
//----

const char *pfc::str_ifind(const char *s_, char c_)
{
  // search for character from the string
  PFC_ASSERT_PEDANTIC(s_);
  c_=(char)::tolower(c_);
  while(*s_)
  {
    if(::tolower(*s_)==c_)
      return s_;
    ++s_;
  }
  return 0;
}
//----

const wchar_t *pfc::str_ifind(const wchar_t *s_, wchar_t c_)
{
  // search for character from the string
  PFC_ASSERT_PEDANTIC(s_);
  c_=(wchar_t)::tolower(c_);
  while(*s_)
  {
    if(::tolower(*s_)==c_)
      return s_;
    ++s_;
  }
  return 0;
}
//----

char *pfc::str_ifind(char *s_, char c_)
{
  // search for character from the string
  PFC_ASSERT_PEDANTIC(s_);
  c_=(char)::tolower(c_);
  while(*s_)
  {
    if(::tolower(*s_)==c_)
      return s_;
    ++s_;
  }
  return 0;
}
//----

wchar_t *pfc::str_ifind(wchar_t *s_, wchar_t c_)
{
  // search for character from the string
  PFC_ASSERT_PEDANTIC(s_);
  c_=(wchar_t)::tolower(c_);
  while(*s_)
  {
    if(::tolower(*s_)==c_)
      return s_;
    ++s_;
  }
  return 0;
}
//----

const char *pfc::str_ifind(const char *s_, const char *chars_)
{
  // convert search characters to low-case
  PFC_ASSERT(s_ && chars_);
  usize_t num_chars=(usize_t)::strlen(chars_);
  char *chars=(char*)PFC_STACK_MALLOC(num_chars);
  for(usize_t i=0; i<num_chars; ++i)
    chars[i]=(char)::tolower(chars_[i]);

  // search for given characters from the string
  while(*s_)
  {
    char c=(char)::tolower(*s_);
    for(usize_t i=0; i<num_chars; ++i)
      if(chars[i]==c)
        return s_;
    ++s_;
  }
  return 0;
}
//----

const wchar_t *pfc::str_ifind(const wchar_t *s_, const wchar_t *chars_)
{
  // convert search characters to low-case
  PFC_ASSERT(s_ && chars_);
  usize_t num_chars=(usize_t)::wcslen(chars_);
  wchar_t *chars=(wchar_t*)PFC_STACK_MALLOC(num_chars*sizeof(wchar_t));
  for(usize_t i=0; i<num_chars; ++i)
    chars[i]=(wchar_t)::tolower(chars_[i]);

  // search for given characters from the string
  while(*s_)
  {
    wchar_t c=(wchar_t)::tolower(*s_);
    for(usize_t i=0; i<num_chars; ++i)
      if(chars[i]==c)
        return s_;
    ++s_;
  }
  return 0;
}
//----

char *pfc::str_ifind(char *s_, const char *chars_)
{
  // convert search characters to low-case
  PFC_ASSERT(s_ && chars_);
  usize_t num_chars=(usize_t)::strlen(chars_);
  char *chars=(char*)PFC_STACK_MALLOC(num_chars);
  for(usize_t i=0; i<num_chars; ++i)
    chars[i]=(char)::tolower(chars_[i]);

  // search for given characters from the string
  while(*s_)
  {
    char c=(char)::tolower(*s_);
    for(usize_t i=0; i<num_chars; ++i)
      if(chars[i]==c)
        return s_;
    ++s_;
  }
  return 0;
}
//----

wchar_t *pfc::str_ifind(wchar_t *s_, const wchar_t *chars_)
{
  // convert search characters to low-case
  PFC_ASSERT(s_ && chars_);
  usize_t num_chars=(usize_t)::wcslen(chars_);
  wchar_t *chars=(wchar_t*)PFC_STACK_MALLOC(num_chars*sizeof(wchar_t));
  for(usize_t i=0; i<num_chars; ++i)
    chars[i]=(wchar_t)::tolower(chars_[i]);

  // search for given characters from the string
  while(*s_)
  {
    wchar_t c=(wchar_t)::tolower(*s_);
    for(usize_t i=0; i<num_chars; ++i)
      if(chars[i]==c)
        return s_;
    ++s_;
  }
  return 0;
}
//----

const char *pfc::str_find_substr(const char *s_, const char *substr_)
{
  // search for given sub-string
  PFC_ASSERT_PEDANTIC(s_ && substr_);
  usize_t substrsize=(usize_t)::strlen(substr_);
  while(const char *s=str_find(s_, *substr_))
  {
    if(str_eq(s, substr_, substrsize))
      return s;
    s_=s+1;
  }
  return 0;
}
//----

const wchar_t *pfc::str_find_substr(const wchar_t *s_, const wchar_t *substr_)
{
  // search for given sub-string
  PFC_ASSERT_PEDANTIC(s_ && substr_);
  usize_t substrsize=(usize_t)::wcslen(substr_);
  while(const wchar_t *s=str_find(s_, *substr_))
  {
    if(str_eq(s, substr_, substrsize))
      return s;
    s_=s+1;
  }
  return 0;
}
//----

char *pfc::str_find_substr(char *s_, const char *substr_)
{
  // search for given sub-string
  PFC_ASSERT_PEDANTIC(s_ && substr_);
  usize_t substrsize=(usize_t)::strlen(substr_);
  while(char *s=str_find(s_, *substr_))
  {
    if(str_eq(s, substr_, substrsize))
      return s;
    s_=s+1;
  }
  return 0;
}
//----

wchar_t *pfc::str_find_substr(wchar_t *s_, const wchar_t *substr_)
{
  // search for given sub-string
  PFC_ASSERT_PEDANTIC(s_ && substr_);
  usize_t substrsize=(usize_t)::wcslen(substr_);
  while(wchar_t *s=str_find(s_, *substr_))
  {
    if(str_eq(s, substr_, substrsize))
      return s;
    s_=s+1;
  }
  return 0;
}
//----

int pfc::str_find_substr(const char *s_, const char *const*strs_)
{
  PFC_ASSERT_PEDANTIC(s_ && strs_);
  const char *const*strs=strs_;
  while(*strs)
  {
    if(str_eq(s_, *strs))
      return int(strs-strs_);
    ++strs;
  }
  return -1;
}
//----

int pfc::str_find_substr(const wchar_t *s_, const wchar_t *const*strs_)
{
  PFC_ASSERT_PEDANTIC(s_ && strs_);
  const wchar_t *const*strs=strs_;
  while(*strs)
  {
    if(str_eq(s_, *strs))
      return int(strs-strs_);
    ++strs;
  }
  return -1;
}
//----

const char *pfc::str_ifind_substr(const char *s_, const char *substr_)
{
  // search for given sub-string
  PFC_ASSERT_PEDANTIC(s_ && substr_);
  usize_t substrsize=(usize_t)::strlen(substr_);
  while(const char *s=str_ifind(s_, *substr_))
  {
    if(str_ieq(s, substr_, substrsize))
      return s;
    s_=s+1;
  }
  return 0;
}
//----

const wchar_t *pfc::str_ifind_substr(const wchar_t *s_, const wchar_t *substr_)
{
  // search for given sub-string
  PFC_ASSERT_PEDANTIC(s_ && substr_);
  usize_t substrsize=(usize_t)::wcslen(substr_);
  while(const wchar_t *s=str_ifind(s_, *substr_))
  {
    if(str_ieq(s, substr_, substrsize))
      return s;
    s_=s+1;
  }
  return 0;
}
//----

char *pfc::str_ifind_substr(char *s_, const char *substr_)
{
  // search for given sub-string
  PFC_ASSERT_PEDANTIC(s_ && substr_);
  usize_t substrsize=(usize_t)::strlen(substr_);
  while(char *s=str_ifind(s_, *substr_))
  {
    if(str_ieq(s, substr_, substrsize))
      return s;
    s_=s+1;
  }
  return 0;
}
//----

wchar_t *pfc::str_ifind_substr(wchar_t *s_, const wchar_t *substr_)
{
  // search for given sub-string
  PFC_ASSERT_PEDANTIC(s_ && substr_);
  usize_t substrsize=(usize_t)::wcslen(substr_);
  while(wchar_t *s=str_ifind(s_, *substr_))
  {
    if(str_ieq(s, substr_, substrsize))
      return s;
    s_=s+1;
  }
  return 0;
}
//----

const char *pfc::str_find_next_line(const char *s_)
{
  // return pointer to the next line
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_ && *s_!='\n')
    ++s_;
  return *s_?s_+1:s_;
}
//----

const wchar_t *pfc::str_find_next_line(const wchar_t *s_)
{
  // return pointer to the next line
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_ && *s_!='\n')
    ++s_;
  return *s_?s_+1:s_;
}
//----

char *pfc::str_find_next_line(char *s_)
{
  // return pointer to the next line
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_ && *s_!='\n')
    ++s_;
  return *s_?s_+1:s_;
}
//----

wchar_t *pfc::str_find_next_line(wchar_t *s_)
{
  // return pointer to the next line
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_ && *s_!='\n')
    ++s_;
  return *s_?s_+1:s_;
}
//----------------------------------------------------------------------------

const char *pfc::str_skip_whitespace(const char *s_, const char *extra_chars_)
{
  // skip whitespace and extra characters
  PFC_ASSERT_PEDANTIC(s_ && extra_chars_);
  const char *c;
  --s_;
  do
  {
    ++s_;
    while(*s_ && *s_<=' ')
      ++s_;
    c=extra_chars_;
    while(*c && *s_!=*c)
      ++c;
  } while(*c);
  return s_;
}
//----

const wchar_t *pfc::str_skip_whitespace(const wchar_t *s_, const wchar_t *extra_chars_)
{
  // skip whitespace and extra characters
  PFC_ASSERT_PEDANTIC(s_ && extra_chars_);
  const wchar_t *c;
  --s_;
  do
  {
    ++s_;
    while(*s_ && *s_<=L' ')
      ++s_;
    c=extra_chars_;
    while(*c && *s_!=*c)
      ++c;
  } while(*c);
  return s_;
}
//----

char *pfc::str_skip_whitespace(char *s_, const char *extra_chars_)
{
  // skip whitespace and extra characters
  PFC_ASSERT_PEDANTIC(s_ && extra_chars_);
  const char *c;
  --s_;
  do
  {
    ++s_;
    while(*s_ && *s_<=' ')
      ++s_;
    c=extra_chars_;
    while(*c && *s_!=*c)
      ++c;
  } while(*c);
  return s_;
}
//----

wchar_t *pfc::str_skip_whitespace(wchar_t *s_, const wchar_t *extra_chars_)
{
  // skip whitespace and extra characters
  PFC_ASSERT_PEDANTIC(s_ && extra_chars_);
  const wchar_t *c;
  --s_;
  do
  {
    ++s_;
    while(*s_ && *s_<=L' ')
      ++s_;
    c=extra_chars_;
    while(*s_!=*c)
      ++c;
  } while(*c);
  return s_;
}
//----------------------------------------------------------------------------

void pfc::str_replace(char *s_, char char_to_replace_, char replacement_)
{
  // replace given characters in the string with replacement
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_)
  {
    if(*s_==char_to_replace_)
      *s_=replacement_;
    ++s_;
  }
}
//----

void pfc::str_replace(wchar_t *s_, wchar_t char_to_replace_, wchar_t replacement_)
{
  // replace given characters in the string with replacement
  PFC_ASSERT_PEDANTIC(s_);
  while(*s_)
  {
    if(*s_==char_to_replace_)
      *s_=replacement_;
    ++s_;
  }
}
//----

char *pfc::str_split_words(char *s_)
{
  // add \0 the end of the current word and find the next word
  PFC_ASSERT_PEDANTIC(s_ && (!s_ || *s_>=' '));
  char *str=str_find_whitespace(s_);
  if(!*str)
    return str;
  *str++=0;
  return str_skip_whitespace(str);
}
//----

wchar_t *pfc::str_split_words(wchar_t *s_)
{
  // add \0 the end of the current word and find the next word
  PFC_ASSERT_PEDANTIC(s_ && (!s_ || *s_>=L' '));
  wchar_t *str=str_find_whitespace(s_);
  if(!*str)
    return str;
  *str++=0;
  return str_skip_whitespace(str);
}
//----

usize_t pfc::str_strip_chars(char *s_, char c_)
{
  // strip all given characters from the string
  PFC_ASSERT_PEDANTIC(s_ && c_);
  char *sw=s_, *sr=s_;
  while(true)
  {
    while(!*sr || *sr==c_)
    {
      if(!*sr)
      {
        *sw=0;
        return usize_t(sw-s_);
      }
      ++sr;
    }
    *sw++=*sr++;
  }
  return 0;
}
//----

usize_t pfc::str_strip_chars(wchar_t *s_, wchar_t c_)
{
  // strip all given characters from the string
  PFC_ASSERT_PEDANTIC(s_ && c_);
  wchar_t *sw=s_, *sr=s_;
  while(true)
  {
    while(!*sr || *sr==c_)
    {
      if(!*sr)
      {
        *sw=0;
        return usize_t(sw-s_);
      }
      ++sr;
    }
    *sw++=*sr++;
  }
  return 0;
}
//----

usize_t pfc::str_strip_substrs(char *s_, const char *substr_)
{
  // strip all given sub-strings from the string
  PFC_ASSERT_PEDANTIC(s_ && substr_ && *substr_);
  char *sw=s_, *sr=s_;
  usize_t subssize=(usize_t)::strlen(substr_);
  while(true)
  {
    while(!*sr || ::strncmp(sr, substr_, subssize)==0)
    {
      if(!*sr)
      {
        *sw=0;
        return usize_t(sw-s_);
      }
      sr+=subssize;
    }
    *sw++=*sr++;
  }
  return 0;
}
//----

usize_t pfc::str_strip_substrs(wchar_t *s_, const wchar_t *substr_)
{
  // strip all given sub-strings from the string
  PFC_ASSERT_PEDANTIC(s_ && substr_ && *substr_);
  wchar_t *sw=s_, *sr=s_;
  usize_t subssize=(usize_t)::wcslen(substr_);
  while(true)
  {
    while(!*sr || ::wcsncmp(sr, substr_, subssize)==0)
    {
      if(!*sr)
      {
        *sw=0;
        return usize_t(sw-s_);
      }
      sr+=subssize;
    }
    *sw++=*sr++;
  }
  return 0;
}
//----

usize_t pfc::str_strip_whitespace(char *s_)
{
  // strip all whitespace characters from the string
  PFC_ASSERT_PEDANTIC(s_);
  char *sw=s_, *sr=s_;
  while(true)
  {
    while(is_whitespace(*sr))
    {
      if(!*sr)
      {
        *sw=0;
        return usize_t(sw-s_);
      }
      ++sr;
    }
    *sw++=*sr++;
  }
  return 0;
}
//----

usize_t pfc::str_strip_whitespace(wchar_t *s_)
{
  // strip all whitespace characters from the string
  PFC_ASSERT_PEDANTIC(s_);
  wchar_t *sw=s_, *sr=s_;
  while(true)
  {
    while(is_whitespace(*sr))
    {
      if(!*sr)
      {
        *sw=0;
        return usize_t(sw-s_);
      }
      ++sr;
    }
    *sw++=*sr++;
  }
  return 0;
}
//----

usize_t pfc::str_strip_extra_chars(char *s_, char c_)
{
  // strip leading, trailing and double characters
  PFC_ASSERT_PEDANTIC(s_ && c_);
  char *sw=s_, *sr=s_;
  while(*sr)
  {
    if(*sr==c_)
    {
      while(*++sr==c_ && *sr);
      if(!*sr)
        break;
      if(sw!=s_)
        *--sr=c_;
    }
    *sw++=*sr++;
  }

  // remove trailing characters & return new string length
  if(sw!=s_ && sw[-1]==c_)
    --sw;
  *sw=0;
  return usize_t(sw-s_);
}
//----

usize_t pfc::str_strip_extra_chars(wchar_t *s_, wchar_t c_)
{
  // strip leading, trailing and double whitespace characters
  PFC_ASSERT_PEDANTIC(s_ && c_);
  wchar_t *sw=s_, *sr=s_;
  while(*sr)
  {
    if(*sr==c_)
    {
      while(*++sr==c_ && *sr);
      if(!*sr)
        break;
      if(sw!=s_)
        *--sr=c_;
    }
    *sw++=*sr++;
  }

  // remove trailing whitespace & return new string length
  if(sw!=s_ && sw[-1]==c_)
    --sw;
  *sw=0;
  return usize_t(sw-s_);
}
//----

usize_t pfc::str_strip_extra_substrs(char *s_, const char *substr_)
{
  // strip leading, trailing and double sub-strings
  PFC_ASSERT_PEDANTIC(s_ && substr_ && *substr_);
  char *sw=s_, *sr=s_;
  usize_t subssize=(usize_t)::strlen(substr_);
  while(*sr)
  {
    if(::strncmp(sr, substr_, subssize)==0)
    {
      do
      {
        sr+=subssize;
      } while(::strncmp(sr, substr_, subssize)==0);
      if(!*sr)
        break;
      if(sw!=s_)
      {
        mem_copy(sw, substr_, subssize);
        sw+=subssize;
      }
    }
    else
      *sw++=*sr++;
  }

  // remove trailing sub-string & return new string length
  if(sw>=s_+subssize && ::strncmp(sw-subssize, substr_, subssize)==0)
    sw-=subssize;
  *sw=0;
  return usize_t(sw-s_);
}
//----

usize_t pfc::str_strip_extra_substrs(wchar_t *s_, const wchar_t *substr_)
{
  // strip leading, trailing and double sub-strings
  PFC_ASSERT_PEDANTIC(s_ && substr_ && *substr_);
  wchar_t *sw=s_, *sr=s_;
  usize_t subssize=(usize_t)::wcslen(substr_);
  while(*sr)
  {
    if(::wcsncmp(sr, substr_, subssize)==0)
    {
      do
      {
        sr+=subssize;
      } while(::wcsncmp(sr, substr_, subssize)==0);
      if(!*sr)
        break;
      if(sw!=s_)
      {
        mem_copy(sw, substr_, subssize*sizeof(wchar_t));
        sw+=subssize;
      }
    }
    else
      *sw++=*sr++;
  }

  // remove trailing sub-string & return new string length
  if(sw>=s_+subssize && ::wcsncmp(sw-subssize, substr_, subssize)==0)
    sw-=subssize;
  *sw=0;
  return usize_t(sw-s_);
}
//----

usize_t pfc::str_strip_extra_whitespace(char *s_)
{
  // strip leading, trailing and double whitespace characters
  PFC_ASSERT_PEDANTIC(s_);
  char *sw=s_, *sr=s_;
  while(*sr)
  {
    if(is_whitespace(*sr))
    {
      char ws=*sr;
      while(is_whitespace(*++sr) && *sr);
      if(!*sr)
        break;
      if(sw!=s_)
        *--sr=ws;
    }
    *sw++=*sr++;
  }

  // remove trailing whitespace & return new string length
  if(sw!=s_ && is_whitespace(sw[-1]))
    --sw;
  *sw=0;
  return usize_t(sw-s_);
}
//----

usize_t pfc::str_strip_extra_whitespace(wchar_t *s_)
{
  // strip leading, trailing and double whitespace characters
  PFC_ASSERT_PEDANTIC(s_);
  wchar_t *sw=s_, *sr=s_;
  while(*sr)
  {
    if(is_whitespace(*sr))
    {
      wchar_t ws=*sr;
      while(is_whitespace(*++sr) && *sr);
      if(!*sr)
        break;
      if(sw!=s_)
        *--sr=ws;
    }
    *sw++=*sr++;
  }

  // remove trailing whitespace & return new string length
  if(sw!=s_ && is_whitespace(sw[-1]))
    --sw;
  *sw=0;
  return usize_t(sw-s_);
}
//----

usize_t pfc::str_strip_outer_chars(char *s_, char c_, bool strip_all_)
{
  // strip given character(s) from beginning and end of the string
  PFC_ASSERT_PEDANTIC(s_ && c_);
  usize_t ssize=(usize_t)::strlen(s_);
  if(ssize && s_[ssize-1]==c_)
  {
    // strip character(s) from the end
    char *tc=s_+ssize, *rc=tc-1;
    if(strip_all_)
    {
      while(rc>s_ && *--rc==c_);
      if(*rc!=c_)
        ++rc;
    }
    *rc=0;
    ssize-=usize_t(tc-rc);
  }
  if(*s_==c_)
  {
    // strip character(s) from the beginning
    char *rc=s_+1;
    if(strip_all_)
      while(*rc==c_)
        ++rc;
    ssize-=usize_t(rc-s_);
    mem_move(s_, rc, ssize+1);
  }
  return ssize;
}
//----

usize_t pfc::str_strip_outer_chars(wchar_t *s_, wchar_t c_, bool strip_all_)
{
  // strip given character(s) from beginning and end of the string
  PFC_ASSERT_PEDANTIC(s_ && c_);
  usize_t ssize=(usize_t)::wcslen(s_);
  if(ssize && s_[ssize-1]==c_)
  {
    // strip character(s) from the end
    wchar_t *tc=s_+ssize, *rc=tc-1;
    if(strip_all_)
    {
      while(rc>s_ && *--rc==c_);
      if(*rc!=c_)
        ++rc;
    }
    *rc=0;
    ssize-=usize_t(tc-rc);
  }
  if(*s_==c_)
  {
    // strip character(s) from the beginning
    wchar_t *rc=s_+1;
    if(strip_all_)
      while(*rc==c_)
        ++rc;
    ssize-=usize_t(rc-s_);
    mem_move(s_, rc, (ssize+1)*sizeof(wchar_t));
  }
  return ssize;
}
//----

usize_t pfc::str_strip_outer_substrs(char *s_, const char *substr_, bool strip_all_)
{
  // strip given sub-string(s) from beginning and end of the string
  PFC_ASSERT_PEDANTIC(s_ && substr_ && *substr_);
  usize_t ssize=(usize_t)::strlen(s_), subssize=(usize_t)::strlen(substr_);
  if(ssize>=subssize && ::strncmp(s_+ssize-subssize, substr_, subssize)==0)
  {
    // strip sub-string(s) from the end
    char *tc=s_+ssize, *rc=tc-subssize;
    if(strip_all_)
    {
      while(rc>=s_+subssize && ::strncmp(rc-=subssize, substr_, subssize)==0);
      if(::strncmp(rc, substr_, subssize)!=0)
        rc+=subssize;
    }
    *rc=0;
    ssize-=usize_t(tc-rc);
  }
  if(::strncmp(s_, substr_, subssize)==0)
  {
    // strip sub-string(s) from the beginning
    char *rc=s_+subssize;
    if(strip_all_)
      while(::strncmp(rc, substr_, subssize)==0)
        rc+=subssize;
    ssize-=usize_t(rc-s_);
    mem_move(s_, rc, ssize+subssize);
  }
  return ssize;
}
//----

usize_t pfc::str_strip_outer_substrs(wchar_t *s_, const wchar_t *substr_, bool strip_all_)
{
  // strip given sub-string(s) from beginning and end of the string
  PFC_ASSERT_PEDANTIC(s_ && substr_ && *substr_);
  usize_t ssize=(usize_t)::wcslen(s_), subssize=(usize_t)::wcslen(substr_);
  if(ssize>=subssize && ::wcsncmp(s_+ssize-subssize, substr_, subssize)==0)
  {
    // strip sub-string(s) from the end
    wchar_t *tc=s_+ssize, *rc=tc-subssize;
    if(strip_all_)
    {
      while(rc>=s_+subssize && ::wcsncmp(rc-=subssize, substr_, subssize)==0);
      if(::wcsncmp(rc, substr_, subssize)!=0)
        rc+=subssize;
    }
    *rc=0;
    ssize-=usize_t(tc-rc);
  }
  if(::wcsncmp(s_, substr_, subssize)==0)
  {
    // strip sub-string(s) from the beginning
    wchar_t *rc=s_+subssize;
    if(strip_all_)
      while(::wcsncmp(rc, substr_, subssize)==0)
        rc+=subssize;
    ssize-=usize_t(rc-s_);
    mem_move(s_, rc, (ssize+subssize)*sizeof(wchar_t));
  }
  return ssize;
}
//----

usize_t pfc::str_strip_outer_whitespace(char *s_, bool strip_all_)
{
  // strip given character(s) from beginning and end of the string
  PFC_ASSERT_PEDANTIC(s_);
  usize_t ssize=(usize_t)::strlen(s_);
  if(ssize && s_[ssize-1]<=' ')
  {
    // strip character(s) from the end
    char *tc=s_+ssize, *rc=tc-1;
    if(strip_all_)
    {
      while(rc>s_ && *--rc<=' ');
      if(*rc>' ')
        ++rc;
    }
    *rc=0;
    ssize-=usize_t(tc-rc);
  }
  if(*s_<=' ')
  {
    // strip character(s) from the beginning
    char *rc=s_+1;
    if(strip_all_)
      while(*rc<=' ')
        ++rc;
    ssize-=usize_t(rc-s_);
    mem_move(s_, rc, ssize+1);
  }
  return ssize;
}
//----

usize_t pfc::str_strip_outer_whitespace(wchar_t *s_, bool strip_all_)
{
  // strip given character(s) from beginning and end of the string
  PFC_ASSERT_PEDANTIC(s_);
  usize_t ssize=(usize_t)::wcslen(s_);
  if(ssize && s_[ssize-1]<=L' ')
  {
    // strip character(s) from the end
    wchar_t *tc=s_+ssize, *rc=tc-1;
    if(strip_all_)
    {
      while(rc>s_ && *--rc<=L' ');
      if(*rc>L' ')
        ++rc;
    }
    *rc=0;
    ssize-=usize_t(tc-rc);
  }
  if(*s_<=L' ')
  {
    // strip character(s) from the beginning
    wchar_t *rc=s_+1;
    if(strip_all_)
      while(*rc<=L' ')
        ++rc;
    ssize-=usize_t(rc-s_);
    mem_move(s_, rc, (ssize+1)*sizeof(wchar_t));
  }
  return ssize;
}
//----------------------------------------------------------------------------

bool pfc::is_ascii(char *str_)
{
  // check if c-string is ascii
  PFC_ASSERT(str_);
  while(*str_)
  {
    if(unsigned(*str_)>=0x80)
      return false;
    ++str_;
  }
  return true;
}
//----

bool pfc::is_ascii(wchar_t *str_)
{
  // check if c-string is ascii
  PFC_ASSERT(str_);
  while(*str_)
  {
    if(unsigned(*str_)>=0x80)
      return false;
    ++str_;
  }
  return true;
}
//----

bool pfc::is_ascii(char *str_, usize_t num_bytes_)
{
  // check if given number of characters are all ascii
  for(usize_t i=0; i<num_bytes_; ++i)
    if(unsigned(str_[i])>=0x80)
      return false;
  return true;
}
//----

bool pfc::is_ascii(wchar_t *str_, usize_t num_bytes_)
{
  // check if given number of characters are all ascii
  for(usize_t i=0; i<num_bytes_; ++i)
    if(unsigned(str_[i])>=0x80)
      return false;
  return true;
}
//----------------------------------------------------------------------------

usize_t pfc::str_to_float64(float64_t &v_, const char *s_)
{
  // skip white spaces
  const char *str=s_;
  while(*str && is_whitespace(*str))
    ++str;

  // parse the value
  float64_t v=0, ve=0, dec_fact=0;
  char sign=0, signe=0;
  bool is_number=false, is_dec=false, is_exp=false, is_parsing=true;
  do
  {
    if(is_decimal(*str))
    {
      if(is_dec)
      {
        dec_fact*=0.1;
        v+=float64_t(dec_char_to_uint(*str))*dec_fact;
      }
      else
        v=v*10.0+float64_t(dec_char_to_uint(*str));
      sign=sign?sign:'+';
      is_number=true;
    }
    else
      switch(*str)
      {
        // parse exponent
        case 'e':
        case 'E':
        {
          if(!sign || is_exp)
          {
            is_parsing=false;
            continue;
          }
          is_dec=false;
          is_exp=true;
          ve=v;
          v=0;
          signe=sign;
          sign=0;
        } break;

        // parse sign
        case '+':
        case '-':
        {
          if(sign)
          {
            is_parsing=false;
            continue;
          }
          sign=*str;
        } break;

        // parse decimal point
        case '.':
        {
          if(is_dec)
          {
            is_parsing=false;
            continue;
          }
          dec_fact=1.0;
          is_dec=true;
        } break;

        default: is_parsing=false; continue;
      }

    // proceed to the next char
    ++str;
  } while(is_parsing);

  // return the value and float string length
  if(is_exp)
  {
    char tmp_sign=sign;
    sign=signe;
    signe=tmp_sign;
    float64_t tmp_v=v;
    v=ve;
    ve=tmp_v;
  }
  if(is_number)
    v_=(sign=='-'?-1.0:1.0)*v*pow(10.0, (signe=='-'?-1.0:1.0)*ve);
  return is_number?usize_t(str-s_):0;
}
//----

usize_t pfc::str_to_int64(int64_t &v_, const char *s_)
{
  // skip white spaces
  const char *str=s_;
  while(*str && is_whitespace(*str))
    ++str;

  // parse the value
  int64_t v=0;
  char sign=0;
  bool is_number=false, is_parsing=true;
  do
  {
    if(is_decimal(*str))
    {
      v=v*10+int(dec_char_to_uint(*str));
      sign=sign?sign:'+';
      is_number=true;
    }
    else
      switch(*str)
      {
        // parse sign
        case '+':
        case '-':
        {
          if(sign)
          {
            is_parsing=false;
            continue;
          }
          sign=*str;
        } break;

        default: is_parsing=false; continue;
      }

    // proceed to the next char
    ++str;
  } while(is_parsing);

  // return the value and int string length
  if(is_number)
    v_=sign=='-'?-v:v;
  return is_number?usize_t(str-s_):0;
}
//----

int pfc::str_to_scalar64(float64_t &vf_, int64_t &vi_, const char *s_)
{
  // skip white spaces
  const char *str=s_;
  while(*str && is_whitespace(*str))
    ++str;

  // parse the value
  int64_t vi=0, vd=0, vei=0, ved=0;
  float64_t dec_fact=0;
  char sign=0, signe=0;
  bool is_number=false, is_dec=false, is_exp=false, is_parsing=true;
  do
  {
    if(is_decimal(*str))
    {
      if(is_dec)
      {
        dec_fact*=0.1;
        vd+=10*vd+int64_t(dec_char_to_uint(*str));
      }
      else
        vi=vi*10+int64_t(dec_char_to_uint(*str));
      sign=sign?sign:'+';
      is_number=true;
    }
    else
      switch(*str)
      {
        // parse exponent
        case 'e':
        case 'E':
        {
          if(!sign || is_exp)
          {
            is_parsing=false;
            continue;
          }
          is_dec=false;
          is_exp=true;
          vei=vi;
          ved=vd;
          vi=0;
          vd=0;
          signe=sign;
          sign=0;
        } break;

        // parse sign
        case '+':
        case '-':
        {
          if(sign)
          {
            is_parsing=false;
            continue;
          }
          sign=*str;
        } break;

        // parse decimal point
        case '.':
        {
          if(is_dec)
          {
            is_parsing=false;
            continue;
          }
          dec_fact=1.0;
          is_dec=true;
        } break;

        default: is_parsing=false; continue;
      }

    // proceed to the next char
    ++str;
  } while(is_parsing);

  // return the value & scalar string length
  if(is_exp)
  {
    char tmp_sign=sign;
    sign=signe;
    signe=tmp_sign;
    int64_t tmp_vi=vi, tmp_vd=vd;
    vi=vei;
    vd=ved;
    vei=tmp_vi;
    ved=tmp_vd;
  }
  if(is_number)
  {
    if(dec_fact || is_exp)
    {
      vf_=(sign=='-'?-1.0:1.0)*(vi+vd*dec_fact)*pow(10.0, (signe=='-'?-1.0:1.0)*vei);
      return int(str-s_);
    }
    vi_=sign=='-'?-vi:vi;
    return int(s_-str);
  }
  return 0;
}
//----------------------------------------------------------------------------
