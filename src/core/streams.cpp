//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "streams.h"
#include "utils.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// bin_input_stream_base
//============================================================================
usize_t bin_input_stream_base::update_buffer_nv(void *p_, usize_t num_bytes_, bool exact_)
{
  // copy remaining data in the buffer to pointer and update the buffer
  PFC_ASSERT_MSG(!exact_ || !m_is_last, ("Binary input stream underflow\r\n"));
  m_data-=num_bytes_;
  uint8_t *p=reinterpret_cast<uint8_t*>(p_);
  usize_t left=usize_t(m_end-m_data);
  mem_copy(p_, m_data, left);
  return update_buffer_impl(p+left, num_bytes_-left, exact_)+left;
}
//----

void bin_input_stream_base::rewind_nv()
{
  rewind_impl();
}
//----

void bin_input_stream_base::rewind_nv(usize_t num_bytes_)
{
  PFC_ASSERT_MSG(!m_is_first, ("Trying to seek beyond the beginning of the stream\r\n"));
  rewind_impl(num_bytes_);
}
//----

void bin_input_stream_base::skip_nv()
{
  PFC_ASSERT_MSG(!m_is_last, ("Trying to seek beyond the end of the stream\r\n"));
  skip_impl();
}
//----

void bin_input_stream_base::seek_nv(usize_t abs_pos_)
{
  PFC_ASSERT_MSG(!m_is_last || abs_pos_<m_begin_pos, ("Trying to seek beyond the end of the stream\r\n"));
  seek_impl(abs_pos_);
}
//----------------------------------------------------------------------------


//============================================================================
// bin_output_stream_base
//============================================================================
void bin_output_stream_base::flush_buffer_nv(const void *a_, usize_t num_bytes_)
{
  m_data-=num_bytes_;
  flush_buffer_impl(a_, num_bytes_);
}
//----------------------------------------------------------------------------


//============================================================================
// mem_input_stream
//============================================================================
usize_t mem_input_stream::update_buffer_impl(void*, usize_t, bool exact_)
{
  m_data=m_end;
  return 0;
}
//----

void mem_input_stream::rewind_impl()
{
}
//----

void mem_input_stream::rewind_impl(usize_t)
{
}
//----

void mem_input_stream::skip_impl()
{
}
//----

void mem_input_stream::seek_impl(usize_t)
{
}
//----------------------------------------------------------------------------


//============================================================================
// mem_output_stream
//============================================================================
void mem_output_stream::flush_buffer_impl(const void*, usize_t size_)
{
  PFC_CHECK_MSG(!size_, ("Memory output stream overflow\r\n"));
}
//----------------------------------------------------------------------------


//============================================================================
// null_output_stream
//============================================================================
uint8_t null_output_stream::s_garbage_bin[garbage_bin_size];
//----------------------------------------------------------------------------

void null_output_stream::flush_buffer_impl(const void*, usize_t num_bytes_)
{
  // setup buffer
  m_begin_pos+=num_bytes_+garbage_bin_size-usize_t(m_end-m_data);
  m_begin=m_data=s_garbage_bin;
  m_end=s_garbage_bin+garbage_bin_size;
}
//----------------------------------------------------------------------------


//============================================================================
// text_input_stream
//============================================================================
usize_t text_input_stream::read_word(char *str_, usize_t max_bytes_, const char *extra_terminal_chars_, bool terminate_at_whitespace_, bool skip_terminal_chars_, bool skip_leading_whitespace_)
{
  // skip leading white spaces
  PFC_ASSERT(str_ && max_bytes_);
  char *begin=str_, *end=str_+max_bytes_-1;
  while(is_whitespace(m_next_char) && !m_stream.is_eos())
  {
    if(!skip_leading_whitespace_ && m_next_char && str_!=end)
      *str_++=m_next_char;
    m_stream>>m_next_char;
  }

  // read string and return the string length
  while(str_!=end)
  {
    // check for an extra terminal character
    if(extra_terminal_chars_)
    {
      const char *p=extra_terminal_chars_;
      while(*p)
      {
        if(m_next_char==*p)
        {
          *str_=0;
          if(skip_terminal_chars_)
            skip_whitespace(extra_terminal_chars_);
          return usize_t(str_-begin);
        }
        ++p;
      }
    }

    // add character and check for end of string by stream/whitespace
    *str_++=m_next_char;
    if(m_stream.is_eos())
    {
      m_next_char=0;
      break;
    }
    m_stream>>m_next_char;
    if(terminate_at_whitespace_ && is_whitespace(m_next_char))
      break;
  }
  *str_=0;
  if(skip_terminal_chars_)
    skip_whitespace(extra_terminal_chars_);
  return usize_t(str_-begin);
}
//----

usize_t text_input_stream::read_word(heap_str &str_, const char *extra_terminal_chars_, bool terminate_at_whitespace_, bool skip_terminal_chars_, bool skip_leading_whitespace_)
{
  // skip leading white spaces
  while(is_whitespace(m_next_char) && !m_stream.is_eos())
  {
    if(!skip_leading_whitespace_ && m_next_char)
      str_+=m_next_char;
    m_stream>>m_next_char;
  }

  // read string and return the string length
  usize_t orig_size=str_.size();
  while(true)
  {
    // check for an extra terminal character
    if(extra_terminal_chars_)
    {
      const char *p=extra_terminal_chars_;
      while(*p)
      {
        if(m_next_char==*p)
        {
          if(skip_terminal_chars_)
            skip_whitespace(extra_terminal_chars_);
          return str_.size()-orig_size;
        }
        ++p;
      }
    }

    // add character and check for end of string by stream/whitespace
    str_+=m_next_char;
    if(m_stream.is_eos())
      break;
    m_stream>>m_next_char;
    if(terminate_at_whitespace_ && is_whitespace(m_next_char))
      break;
  }
  if(skip_terminal_chars_)
    skip_whitespace(extra_terminal_chars_);
  return str_.size()-orig_size;
}
//----

usize_t text_input_stream::read_line(char *str_, usize_t max_bytes_, bool skip_leading_whitespace_)
{
  // skip white spaces
  PFC_ASSERT(str_ && max_bytes_);
  if(!m_next_char && !m_stream.is_eos())
    m_stream>>m_next_char;
  if(skip_leading_whitespace_)
    while(is_whitespace(m_next_char))
    {
      if(m_stream.is_eos())
      {
        m_next_char=0;
        *str_=0;
        return 0;
      }
      m_stream>>m_next_char;
    }

  // read line and return the line length
  char *begin=str_, *end=str_+max_bytes_-1;
  if(!m_stream.is_eos())
    while(str_!=end)
    {
      if(m_next_char=='\n' || m_next_char=='\r')
      {
        if(m_next_char=='\r')
        {
          if(m_stream.is_eos())
            m_next_char=0;
          else
            m_stream>>m_next_char;
        }
        if(m_next_char=='\n')
        {
          if(m_stream.is_eos())
            m_next_char=0;
          else
            m_stream>>m_next_char;
        }
        break;
      }
      *str_++=m_next_char;
      if(m_stream.is_eos())
      {
        m_next_char=0;
        break;
      }
      m_stream>>m_next_char;
    }
  *str_=0;
  return usize_t(str_-begin);
}
//----

usize_t text_input_stream::read_line(heap_str &str_, bool skip_leading_whitespace_)
{
  // skip white spaces
  if(!m_next_char && !m_stream.is_eos())
    m_stream>>m_next_char;
  if(skip_leading_whitespace_)
    while(is_whitespace(m_next_char))
    {
      if(m_stream.is_eos())
      {
        m_next_char=0;
        return 0;
      }
      m_stream>>m_next_char;
    }

  // read line and return the line length
  usize_t orig_size=str_.size();
  if(!m_stream.is_eos())
    while(true)
    {
      if(m_next_char=='\n' || m_next_char=='\r')
      {
        if(m_next_char=='\r')
        {
          if(m_stream.is_eos())
            m_next_char=0;
          else
            m_stream>>m_next_char;
        }
        if(m_next_char=='\n')
        {
          if(m_stream.is_eos())
            m_next_char=0;
          else
            m_stream>>m_next_char;
        }
        break;
      }
      str_+=m_next_char;
      if(m_stream.is_eos())
      {
        m_next_char=0;
        break;
      }
      m_stream>>m_next_char;
    }
  return str_.size()-orig_size;
}
//----------------------------------------------------------------------------

void text_input_stream::skip(usize_t num_bytes_)
{
  // skip stream given number of bytes
  if(m_next_char && num_bytes_)
  {
    --num_bytes_;
    m_next_char=0;
  }
  m_stream.skip(num_bytes_);
}
//----

void text_input_stream::skip(const char *chars_)
{
  // stream next character if not streamed
  if(!m_next_char)
  {
    if(!m_stream.is_eos())
      m_stream>>m_next_char;
    else
      return;
  }

  // skip given characters in the stream
  while(true)
  {
    const char *s=chars_;
    while(*s && *s!=m_next_char)
      ++s;
    if(!*s)
      return;
    if(m_stream.is_eos())
    {
      m_next_char=0;
      return;
    }
    m_stream>>m_next_char;
  }
}
//----

void text_input_stream::skip_line()
{
  // skip characters until CR/LF character
  while(!m_stream.is_eos() && m_next_char!=0xa && m_next_char!=0xd)
    m_stream>>m_next_char;

  // skip to the beginning of the next line
  if(!m_stream.is_eos())
  {
    char c;
    m_stream>>c;
    if((m_next_char==0xa && c==0xd) || (m_next_char==0xd && c==0xa))
      m_stream>>c;
    m_next_char=c;
  }
}
//----

void text_input_stream::skip_to(char c_, bool skip_char_)
{
  // stream next character if not streamed
  if(!m_next_char)
  {
    if(!m_stream.is_eos())
      m_stream>>m_next_char;
    else
      return;
  }

  // skip to given character in the stream
  while(m_next_char!=c_)
  {
    if(m_stream.is_eos())
    {
      m_next_char=0;
      return;
    }
    m_stream>>m_next_char;
  }
  if(skip_char_)
    m_next_char=0;
}
//----

void text_input_stream::skip_to(const char *chars_, bool skip_char_)
{
  // stream next character if not streamed
  PFC_ASSERT(chars_);
  if(!m_next_char)
  {
    if(!m_stream.is_eos())
      m_stream>>m_next_char;
    else
      return;
  }

  // skip to one of the given characters in the stream
  usize_t num_chars=str_size(chars_);
  while(true)
  {
    // check if the next character is one of the skip-to characters
    for(usize_t i=0; i<num_chars; ++i)
      if(m_next_char==chars_[i])
      {
        if(skip_char_)
          m_next_char=0;
        return;
      }

    // read next char if not end of stream
    if(m_stream.is_eos())
    {
      m_next_char=0;
      return;
    }
    m_stream>>m_next_char;
  }
}
//----

void text_input_stream::skip_whitespace(const char *extra_chars_)
{
  // stream next character if not streamed
  if(!m_next_char)
  {
    if(!m_stream.is_eos())
      m_stream>>m_next_char;
    else
      return;
  }

  if(extra_chars_)
  {
    // skip whitespace and extra characters
    while(true)
    {
      const char *s=extra_chars_;
      while(*s && *s!=m_next_char)
        ++s;
      if(!*s && !is_whitespace(m_next_char))
        return;

      // stream next character
      if(m_stream.is_eos())
      {
        m_next_char=0;
        return;
      }
      m_stream>>m_next_char;
    }
  }
  else
  {
    // skip only whitespace
    while(is_whitespace(m_next_char))
    {
      if(m_stream.is_eos())
      {
        m_next_char=0;
        return;
      }
      m_stream>>m_next_char;
    }
  }
}
//----------------------------------------------------------------------------

double text_input_stream::read_double()
{
  // skip white spaces
  while(is_whitespace(m_next_char))
    m_stream>>m_next_char;

  // read the value
  double v=0, ve=0, dec_fact=0;
  char sign=0, signe=0;
  bool is_number=false, is_dec=false, is_exp=false, is_parsing=true;
  do
  {
    if(is_decimal(m_next_char))
    {
      if(is_dec)
      {
        dec_fact*=0.1;
        v+=double(dec_char_to_uint(m_next_char))*dec_fact;
      }
      else
        v=v*10.0+double(dec_char_to_uint(m_next_char));
      sign=sign?sign:'+';
      is_number=true;
    }
    else
      switch(m_next_char)
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
          sign=m_next_char;
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

    // read next character if available
    if(m_stream.is_eos())
    {
      m_next_char=0;
      break;
    }
    m_stream>>m_next_char;
  } while(is_parsing);

  // return the value
  if(is_exp)
  {
    swap(sign, signe);
    swap(v, ve);
  }
  m_numeric_parsing_error|=!is_number;
  return (sign=='-'?-1.0:1.0)*v*pow(10.0, (signe=='-'?-1.0:1.0)*ve);
}
//----------------------------------------------------------------------------


//============================================================================
// bit_input_stream
//============================================================================
bit_input_stream::bit_input_stream(bin_input_stream_base &s_, usize_t bit_stream_length_)
  :m_stream(s_)
  ,m_bit_stream_length(bit_stream_length_)
{
  mem_zero(m_cache, sizeof(m_cache));
  m_cache_start_bit_pos=unsigned(-cache_size*8);
  m_cache_bit_pos=cache_size*8;
}
//----

bit_input_stream::bit_input_stream(bin_input_stream_base &s_)
  :m_stream(s_)
  ,m_bit_stream_length(usize_t(-1))
{
  mem_zero(m_cache, sizeof(m_cache));
  m_cache_start_bit_pos=unsigned(-cache_size*8);
  m_cache_bit_pos=cache_size*8;
}
//----------------------------------------------------------------------------

void bit_input_stream::update_cache()
{
  // update cache with new data from data stream
  if(int(m_cache_start_bit_pos)<int(m_bit_stream_length))
  {
    int num_tail_bytes=cache_size*8-m_cache_bit_pos;
    int num_cache_fill_bytes;
    if(num_tail_bytes<0)
    {
      num_tail_bytes=(num_tail_bytes-7)/8;
      m_stream.skip(-num_tail_bytes);
      m_cache_start_bit_pos-=num_tail_bytes*8;
      num_tail_bytes=0;
      num_cache_fill_bytes=cache_size;
    }
    else
    {
      num_tail_bytes=(num_tail_bytes+7)/8;
      memcpy(m_cache, m_cache+(m_cache_bit_pos>>3), num_tail_bytes);
      num_cache_fill_bytes=max(0, (int)min((m_bit_stream_length-bit_pos()+7)/8, usize_t(cache_size))-num_tail_bytes);
    }
    m_stream.read_bytes(m_cache+num_tail_bytes, num_cache_fill_bytes);
    mem_zero(m_cache+num_tail_bytes+num_cache_fill_bytes, cache_size-num_tail_bytes-num_cache_fill_bytes);
    m_cache_bit_pos&=7;
    m_cache_start_bit_pos+=cache_size*8;
  }
}
//----------------------------------------------------------------------------
