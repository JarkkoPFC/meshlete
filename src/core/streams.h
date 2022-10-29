//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_STREAMS_H
#define PFC_CORE_STREAMS_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "str.h"
namespace pfc
{

// new
class bin_input_stream_base;
class bin_output_stream_base;
class mem_input_stream;
class mem_output_stream;
template<class Container> class container_input_stream;
template<class Container> class container_output_stream;
class null_output_stream;
class text_input_stream;
class text_output_stream;
class endian_input_stream;
class endian_output_stream;
class bit_input_stream;
template<class S> class auto_stream_seek;
static const struct ostream_cmd_flush {} oscmd_flush;
//----------------------------------------------------------------------------


//============================================================================
// bin_input_stream_base
//============================================================================
class bin_input_stream_base
{
public:
  // construction
  enum {is_big_endian=PFC_BIG_ENDIAN};
  PFC_INLINE bin_input_stream_base();
  virtual PFC_INLINE ~bin_input_stream_base()=0;
  //--------------------------------------------------------------------------

  // streaming
  template<typename T> PFC_INLINE bin_input_stream_base &operator>>(T&);
  template<typename T> PFC_INLINE void read(T*, usize_t count_);
  PFC_INLINE usize_t read_bytes(void*, usize_t num_bytes_, bool exact_=true);
  PFC_INLINE usize_t read_cstr(char*, usize_t max_bytes_);
  //--------------------------------------------------------------------------

  // accessors and seeking
  PFC_INLINE bool is_eos() const;
  PFC_INLINE usize_t pos() const;
  PFC_INLINE void rewind();
  PFC_INLINE void rewind(usize_t num_bytes_);
  PFC_INLINE void skip(usize_t num_bytes_);
  PFC_INLINE void seek(usize_t abs_pos_);
  //--------------------------------------------------------------------------

protected:
  PFC_INLINE void init();
  const uint8_t *m_begin, *m_end, *m_data;
  bool m_is_first, m_is_last;
  usize_t m_begin_pos;
  //--------------------------------------------------------------------------

private:
  void operator=(const bin_input_stream_base&); // not implemented
  template<class T> PFC_INLINE void stream(T&, meta_bool<true> is_pod_stream_);
  template<typename T> PFC_INLINE void stream(T&, meta_bool<false> is_pod_stream_);
  template<class T> PFC_INLINE void stream(T*, usize_t count_, meta_bool<true> is_pod_stream_);
  template<typename T> PFC_INLINE void stream(T*, usize_t count_, meta_bool<false> is_pod_stream_);
  usize_t update_buffer_nv(void*, usize_t num_bytes_, bool exact_);
  void rewind_nv();
  void rewind_nv(usize_t num_bytes_);
  void skip_nv();
  void seek_nv(usize_t abs_pos_);
  virtual usize_t update_buffer_impl(void*, usize_t num_bytes_, bool exact_)=0;
  virtual void rewind_impl()=0;
  virtual void rewind_impl(usize_t num_bytes_)=0;
  virtual void skip_impl()=0;
  virtual void seek_impl(usize_t abs_pos_)=0;
};
//----------------------------------------------------------------------------


//============================================================================
// bin_output_stream_base
//============================================================================
class bin_output_stream_base
{
public:
  // construction
  enum {is_big_endian=PFC_BIG_ENDIAN};
  PFC_INLINE bin_output_stream_base();
  virtual PFC_INLINE ~bin_output_stream_base()=0;
  //--------------------------------------------------------------------------

  // streaming
  template<typename T> PFC_INLINE bin_output_stream_base &operator<<(const T&);
  PFC_INLINE bin_output_stream_base &operator<<(const char*);
  PFC_INLINE bin_output_stream_base &operator<<(char*);
  PFC_INLINE bin_output_stream_base &operator<<(const ostream_cmd_flush&);
  template<typename T> PFC_INLINE void write(const T*, usize_t count_);
  PFC_INLINE void write_bytes(const void*, usize_t num_bytes_);
  PFC_INLINE void flush();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE usize_t pos() const;
  //--------------------------------------------------------------------------

protected:
  PFC_INLINE void init();
  uint8_t *m_begin, *m_end, *m_data;
  usize_t m_begin_pos;
  //--------------------------------------------------------------------------

private:
  void operator=(const bin_output_stream_base&); // not implemented
  template<class T> PFC_INLINE void stream(const T&, meta_bool<true> is_pod_stream_);
  template<typename T> PFC_INLINE void stream(const T&, meta_bool<false> is_pod_stream_);
  template<class T> PFC_INLINE void stream(const T*, usize_t count_, meta_bool<true> is_pod_stream_);
  template<typename T> PFC_INLINE void stream(const T*, usize_t count_, meta_bool<false> is_pod_stream_);
  void flush_buffer_nv(const void*, usize_t num_bytes_);
  virtual void flush_buffer_impl(const void*, usize_t num_bytes_)=0;
};
//----------------------------------------------------------------------------


//============================================================================
// mem_input_stream
//============================================================================
class mem_input_stream: public bin_input_stream_base
{
public:
  // construction
  PFC_INLINE mem_input_stream();
  PFC_INLINE mem_input_stream(const void*);
  PFC_INLINE mem_input_stream(const void*, usize_t num_bytes_);
  PFC_INLINE void set(const void*);
  PFC_INLINE void set(const void*, usize_t num_bytes_);
  //--------------------------------------------------------------------------

private:
  virtual usize_t update_buffer_impl(void*, usize_t num_bytes_, bool exact_);
  virtual void rewind_impl();
  virtual void rewind_impl(usize_t num_bytes_);
  virtual void skip_impl();
  virtual void seek_impl(usize_t abs_pos_);
};
//----------------------------------------------------------------------------


//============================================================================
// mem_output_stream
//============================================================================
class mem_output_stream: public bin_output_stream_base
{
public:
  // construction
  PFC_INLINE mem_output_stream();
  PFC_INLINE mem_output_stream(void*, usize_t num_bytes_);
  PFC_INLINE void set(void*, usize_t num_bytes_);
  //--------------------------------------------------------------------------

private:
  virtual void flush_buffer_impl(const void*, usize_t num_bytes_);
};
//----------------------------------------------------------------------------


//============================================================================
// container_input_stream
//============================================================================
template<class Container>
class container_input_stream: public bin_input_stream_base
{
public:
  // construction
  PFC_INLINE container_input_stream();
  PFC_INLINE container_input_stream(const Container&);
  PFC_INLINE void init(const Container&);
  //--------------------------------------------------------------------------

private:
  virtual usize_t update_buffer_impl(void*, usize_t num_bytes_, bool exact_);
  virtual void rewind_impl();
  virtual void rewind_impl(usize_t num_bytes_);
  virtual void skip_impl();
  virtual void seek_impl(usize_t abs_pos_);
  //--------------------------------------------------------------------------

  enum {buffer_size=256};
  const Container *m_container;
  uint8_t m_buffer[buffer_size];
};
//----------------------------------------------------------------------------


//============================================================================
// container_output_stream
//============================================================================
template<class Container>
class container_output_stream: public bin_output_stream_base
{
public:
  // construction
  PFC_INLINE container_output_stream();
  PFC_INLINE container_output_stream(Container&);
  PFC_INLINE void init(Container&);
  PFC_INLINE ~container_output_stream();
  //--------------------------------------------------------------------------

private:
  virtual void flush_buffer_impl(const void*, usize_t num_bytes_);
  //--------------------------------------------------------------------------

  enum {buffer_size=256};
  Container *m_container;
  uint8_t m_buffer[buffer_size];
};
//----------------------------------------------------------------------------


//============================================================================
// null_output_stream
//============================================================================
class null_output_stream: public bin_output_stream_base
{
public:
  // construction
  PFC_INLINE null_output_stream();
  //--------------------------------------------------------------------------

private:
  virtual void flush_buffer_impl(const void*, usize_t num_bytes_);
  //--------------------------------------------------------------------------

  enum {garbage_bin_size=256};
  static uint8_t s_garbage_bin[garbage_bin_size];
};
//----------------------------------------------------------------------------


//============================================================================
// text_input_stream
//============================================================================
class text_input_stream
{
public:
  // construction
  enum {is_big_endian=PFC_BIG_ENDIAN};
  PFC_INLINE text_input_stream(bin_input_stream_base&);
  //--------------------------------------------------------------------------

  // streaming
  template<typename T> PFC_INLINE text_input_stream &operator>>(T&);
  template<typename T> PFC_INLINE bool read(T&);
  template<typename T> PFC_INLINE usize_t read(T*, usize_t count_);
  PFC_INLINE usize_t read_bytes(void*, usize_t num_bytes_, bool exact_=true);
  usize_t read_word(char*, usize_t max_bytes_, const char *extra_terminal_chars_=0, bool terminate_at_whitespace_=true, bool skip_terminal_chars_=false, bool skip_leading_whitespace_=true);
  usize_t read_word(heap_str&, const char *extra_terminal_chars_=0, bool terminate_at_whitespace_=true, bool skip_terminal_chars_=false, bool skip_leading_whitespace_=true);
  usize_t read_line(char*, usize_t max_bytes_, bool skip_leading_whitespace_=true);
  usize_t read_line(heap_str&, bool skip_leading_whitespace_=true);
  PFC_INLINE char read_char();
  //--------------------------------------------------------------------------

  // accessors and seeking
  PFC_INLINE bool is_eos() const;
  PFC_INLINE usize_t pos() const;
  PFC_INLINE void rewind();
  PFC_INLINE void rewind(usize_t num_bytes_);
  void skip(usize_t num_bytes_);
  void skip(const char *chars_);
  void skip_line();
  void skip_to(char, bool skip_char_=false);
  void skip_to(const char *chars_, bool skip_char_=false);
  void skip_whitespace(const char *extra_chars_=0);
  PFC_INLINE char next_char() const;
  //--------------------------------------------------------------------------

private:
  void operator=(const text_input_stream&); // not implemented
  double read_double();
  template<typename T> PFC_INLINE void stream(T&, meta_case<0> is_type_float_);
  template<typename T> PFC_INLINE void stream(T&, meta_case<1> is_type_int_);
  PFC_INLINE void stream(char&, meta_case<1> is_type_int_);
  PFC_INLINE void stream(bool&, meta_case<1> is_type_int_);
  template<class T> PFC_INLINE void stream(T&, meta_case<2> is_type_class_);
  template<typename T> PFC_INLINE void stream(T&, meta_case<-1> default_);
  //--------------------------------------------------------------------------

  bin_input_stream_base &m_stream;
  mutable char m_next_char;
  bool m_numeric_parsing_error;
};
//----------------------------------------------------------------------------


//============================================================================
// text_output_stream
//============================================================================
class text_output_stream
{
public:
  // construction
  enum {is_big_endian=PFC_BIG_ENDIAN};
  PFC_INLINE text_output_stream(bin_output_stream_base&, char separator_=0);
  //--------------------------------------------------------------------------

  // streaming
  template<typename T> PFC_INLINE text_output_stream &operator<<(const T&);
  PFC_INLINE text_output_stream &operator<<(const char*);
  PFC_INLINE text_output_stream &operator<<(char*);
  template<typename T> PFC_INLINE void write(const T*, usize_t count_);
  PFC_INLINE void write_bytes(const void*, usize_t num_bytes_);
  //--------------------------------------------------------------------------

  // output formatting
  PFC_INLINE void set_float_format(const char *format_);
  PFC_INLINE void set_int_format(const char *format_);
  PFC_INLINE void set_unsigned_format(const char *format_);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE usize_t pos() const;
  //--------------------------------------------------------------------------

private:
  void operator=(const text_output_stream&); // not implemented
  template<typename T> PFC_INLINE void stream(T, meta_case<0> is_type_float_);
  template<typename T> PFC_INLINE void stream(T, meta_case<1> is_type_signed_);
  PFC_INLINE void stream(char, meta_case<1> is_type_signed_);
  template<typename T> PFC_INLINE void stream(T, meta_case<2> is_type_unsigned_);
  PFC_INLINE void stream(bool, meta_case<2> is_type_unsigned_);
  template<class T> PFC_INLINE void stream(const T&, meta_case<3> is_type_class_);
  template<typename T> PFC_INLINE void stream(const T&, meta_case<-1> default_);
  //--------------------------------------------------------------------------

  bin_output_stream_base &m_stream;
  const char m_separator;
  stack_str8 m_float_format;
  stack_str8 m_int_format;
  stack_str8 m_unsigned_format;
};
//----------------------------------------------------------------------------


//============================================================================
// endian_input_stream
//============================================================================
class endian_input_stream
{
public:
  // construction
  enum {is_big_endian=!PFC_BIG_ENDIAN};
  PFC_INLINE endian_input_stream(bin_input_stream_base&);
  //--------------------------------------------------------------------------

  // streaming
  template<typename T> PFC_INLINE endian_input_stream &operator>>(T&);
  template<typename T> PFC_INLINE void read(T*, usize_t count_);
  PFC_INLINE usize_t read_bytes(void*, usize_t num_bytes_, bool exact_=true);
  PFC_INLINE usize_t read_cstr(char*, usize_t max_bytes_);
  //--------------------------------------------------------------------------

  // accessors and seeking
  PFC_INLINE bool is_eos() const;
  PFC_INLINE usize_t pos() const;
  PFC_INLINE void rewind();
  PFC_INLINE void rewind(usize_t num_bytes_);
  PFC_INLINE void skip(usize_t num_bytes_);
  //--------------------------------------------------------------------------

private:
  void operator=(const endian_input_stream&); // not implemented
  template<typename T> PFC_INLINE void stream(T&, meta_bool<false> is_class_);
  template<class T> PFC_INLINE void stream(T&, meta_bool<true> is_class_);
  template<typename T> PFC_INLINE void stream(T*, usize_t count_, meta_bool<false> is_class_);
  template<class T> PFC_INLINE void stream(T*, usize_t count_, meta_bool<true> is_class_);
  //--------------------------------------------------------------------------

  bin_input_stream_base &m_stream;
};
//----------------------------------------------------------------------------


//============================================================================
// endian_output_stream
//============================================================================
class endian_output_stream
{
public:
  // construction
  enum {is_big_endian=!PFC_BIG_ENDIAN};
  PFC_INLINE endian_output_stream(bin_output_stream_base&);
  //--------------------------------------------------------------------------

  // streaming
  template<typename T> PFC_INLINE endian_output_stream &operator<<(const T&);
  PFC_INLINE endian_output_stream &operator<<(const char*);
  PFC_INLINE endian_output_stream &operator<<(char*);
  template<typename T> PFC_INLINE void write(const T*, usize_t count_);
  PFC_INLINE void write_bytes(const void*, usize_t num_bytes_);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE usize_t pos() const;
  //--------------------------------------------------------------------------

private:
  void operator=(const endian_output_stream&); // not implemented
  template<typename T> PFC_INLINE void stream(const T&, meta_bool<false> is_class_);
  template<class T> PFC_INLINE void stream(const T&, meta_bool<true> is_class_);
  template<typename T> PFC_INLINE void stream(const T*, usize_t count_, meta_bool<false> is_class_);
  template<class T> PFC_INLINE void stream(const T*, usize_t count_, meta_bool<true> is_class_);
  //--------------------------------------------------------------------------

  bin_output_stream_base &m_stream;
};
//----------------------------------------------------------------------------


//============================================================================
// bit_input_stream
//============================================================================
class bit_input_stream
{
public:
  // construction
  bit_input_stream(bin_input_stream_base&, usize_t bit_stream_length_);
  bit_input_stream(bin_input_stream_base&);
  //--------------------------------------------------------------------------

  // bit read ops
  PFC_INLINE void read_bits(uint32_t&, unsigned num_bits_);
  PFC_INLINE void read_bits(int32_t&, unsigned num_bits_);
  //--------------------------------------------------------------------------

  // accessors and seeking
  PFC_INLINE usize_t length() const;
  PFC_INLINE bool is_eos() const;
  PFC_INLINE usize_t bit_pos() const;
  PFC_INLINE void skip_bits(usize_t num_bits_);
  //--------------------------------------------------------------------------

private:
  bit_input_stream(const bit_input_stream&); // not implemented
  void operator=(const bit_input_stream&); // not implemented
  void update_cache();
  //--------------------------------------------------------------------------

  enum {cache_size=32};
  enum {max_type_size=4};
  bin_input_stream_base &m_stream;
  const usize_t m_bit_stream_length;
  uint8_t m_cache[cache_size];
  unsigned m_cache_start_bit_pos;
  unsigned m_cache_bit_pos;
};
//----------------------------------------------------------------------------


//============================================================================
// auto_stream_seek
//============================================================================
template<class S>
class auto_stream_seek
{
public:
  // construction
  PFC_INLINE auto_stream_seek(S&, usize_t size_=0);
  PFC_INLINE ~auto_stream_seek();
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

private:
  auto_stream_seek(const auto_stream_seek&); // not implemented
  void operator=(const auto_stream_seek&); // not implemented
  //----

  S &m_stream;
  usize_t m_size;
  usize_t m_begin_pos;
};
//----------------------------------------------------------------------------

//============================================================================
#include "streams.inl"
} // namespace pfc
#endif
