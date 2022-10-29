//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// bin_input_stream_base
//============================================================================
bin_input_stream_base::bin_input_stream_base()
{
  init();
}
//----

bin_input_stream_base::~bin_input_stream_base()
{
}
//----------------------------------------------------------------------------

template<typename T>
bin_input_stream_base &bin_input_stream_base::operator>>(T &v_)
{
  stream((remove_volatile<T>::res&)v_, meta_bool<is_type_pod_stream<T>::res>());
  return *this;
}
//----

template<typename T>
void bin_input_stream_base::read(T *p_, usize_t count_)
{
  PFC_ASSERT_PEDANTIC(p_!=0 || !count_);
  stream((remove_volatile<T>::res*)p_, count_, meta_bool<is_type_pod_stream<T>::res>());
}
//----

usize_t bin_input_stream_base::read_bytes(void *p_, usize_t num_bytes_, bool exact_)
{
  // copy data from the buffer to the array
  PFC_ASSERT_PEDANTIC(p_!=0 || !num_bytes_);
  if((m_data+=num_bytes_)>m_end)
    return update_buffer_nv(p_, num_bytes_, exact_);
  mem_copy(p_, m_data-num_bytes_, num_bytes_);
  return num_bytes_;
}
//----

usize_t bin_input_stream_base::read_cstr(char *s_, usize_t max_bytes_)
{
  // read c-string (ascii-z)
  PFC_ASSERT(s_!=0);
  char c;
  char *dst=s_, *end=s_+max_bytes_;
  do
  {
    if(m_data==m_end)
      update_buffer_nv(0, 0, true);
    c=*m_data++;
    *dst++=c;
  } while(c && dst<end);
  *--dst=0;
  return usize_t(dst-s_);
}
//----------------------------------------------------------------------------

bool bin_input_stream_base::is_eos() const
{
  return m_is_last && m_data==m_end;
}
//----

usize_t bin_input_stream_base::pos() const
{
  return usize_t(m_data-m_begin)+m_begin_pos;
}
//----

void bin_input_stream_base::rewind()
{
  // rewind to the beginning
  if(!m_is_first)
    rewind_nv();
  else
    m_data=m_begin;
}
//----

void bin_input_stream_base::rewind(usize_t num_bytes_)
{
  // rewind bytes
  if(m_data<m_begin+num_bytes_)
    rewind_nv(num_bytes_);
  else
    m_data-=num_bytes_;
}
//----

void bin_input_stream_base::skip(usize_t num_bytes_)
{
  // skip bytes
  if((m_data+=num_bytes_)>m_end)
    skip_nv();
}
//----

void bin_input_stream_base::seek(usize_t abs_pos_)
{
  // absolute seek
  if(abs_pos_<m_begin_pos || abs_pos_>usize_t(m_begin_pos+m_end-m_begin))
    seek_nv(abs_pos_);
  else
    m_data=m_begin+abs_pos_-m_begin_pos;
}
//----------------------------------------------------------------------------

void bin_input_stream_base::init()
{
  // initialize members
  m_begin=m_end=m_data=0;
  m_is_first=true;
  m_is_last=true;
  m_begin_pos=0;
}
//----------------------------------------------------------------------------

template<typename T>
void bin_input_stream_base::stream(T &v_, meta_bool<true> is_pod_stream_)
{
  // copy data from the buffer to the value
  if((m_data+=sizeof(T))>m_end)
    update_buffer_nv(&v_, sizeof(T), true);
  else
    mem_copy(&v_, m_data-sizeof(T), sizeof(T));
}
//----

template<class T>
void bin_input_stream_base::stream(T &v_, meta_bool<false> is_pod_stream_)
{
  PFC_CTF_ERROR(T, property_enumeration_not_implemented);
}
//----

template<typename T>
void bin_input_stream_base::stream(T *p_, usize_t count_, meta_bool<true> is_pod_stream_)
{
  // copy data from the buffer to the array
  usize_t num_bytes=sizeof(T)*count_;
  if((m_data+=num_bytes)>m_end)
    update_buffer_nv(p_, num_bytes, true);
  else
    mem_copy(p_, m_data-num_bytes, num_bytes);
}
//----

template<class T>
void bin_input_stream_base::stream(T *p_, usize_t count_, meta_bool<false> is_pod_stream_)
{
  PFC_CTF_ERROR(T, property_enumeration_not_implemented);
}
//----------------------------------------------------------------------------


//============================================================================
// bin_output_stream_base
//============================================================================
bin_output_stream_base::bin_output_stream_base()
{
  init();
}
//----

bin_output_stream_base::~bin_output_stream_base()
{
}
//----------------------------------------------------------------------------

template<typename T>
bin_output_stream_base &bin_output_stream_base::operator<<(const T &v_)
{
  stream((remove_volatile<T>::res&)v_, meta_bool<is_type_pod_stream<T>::res>());
  return *this;
}
//----

bin_output_stream_base &bin_output_stream_base::operator<<(const char *str_)
{
  // copy string to the buffer
  PFC_ASSERT(str_!=0);
  usize_t l=str_size(str_);
  if((m_data+=l)>m_end)
    flush_buffer_nv(str_, l);
  else
    mem_copy(m_data-l, str_, l);
  return *this;
}
//----

bin_output_stream_base &bin_output_stream_base::operator<<(char *str_)
{
  // copy string to the buffer
  PFC_ASSERT(str_!=0);
  usize_t l=str_size(str_);
  if((m_data+=l)>m_end)
    flush_buffer_nv(str_, l);
  else
    mem_copy(m_data-l, str_, l);
  return *this;
}
//----

bin_output_stream_base &bin_output_stream_base::operator<<(const ostream_cmd_flush&)
{
  flush_buffer_impl(0, 0);
  return *this;
}
//----

template<typename T>
void bin_output_stream_base::write(const T *p_, usize_t count_)
{
  PFC_ASSERT_PEDANTIC(p_!=0 || !count_);
  stream((remove_volatile<T>::res*)p_, count_, meta_bool<is_type_pod_stream<T>::res>());
}
//----

void bin_output_stream_base::write_bytes(const void *p_, usize_t num_bytes_)
{
  // copy data from the array to the buffer
  PFC_ASSERT_PEDANTIC(p_!=0 || !num_bytes_);
  if((m_data+=num_bytes_)>m_end)
    flush_buffer_nv(p_, num_bytes_);
  else
    mem_copy(m_data-num_bytes_, p_, num_bytes_);
}
//----

void bin_output_stream_base::flush()
{
  flush_buffer_impl(0, 0);
}
//----------------------------------------------------------------------------

usize_t bin_output_stream_base::pos() const
{
  return usize_t(m_data-m_begin)+m_begin_pos;
}
//----------------------------------------------------------------------------

void bin_output_stream_base::init()
{
  // initialize members
  m_begin=m_end=m_data=0;
  m_begin_pos=0;
}
//----------------------------------------------------------------------------

template<class T>
void bin_output_stream_base::stream(const T &v_, meta_bool<true> is_pod_stream_)
{
  // copy data from the value to the buffer
  if((m_data+=sizeof(T))>m_end)
    flush_buffer_nv(&v_, sizeof(T));
  else
    mem_copy(m_data-sizeof(T), &v_, sizeof(T));
}
//----

template<typename T>
void bin_output_stream_base::stream(const T &v_, meta_bool<false> is_pod_stream_)
{
  PFC_CTF_ERROR(T, property_enumeration_not_implemented);
}
//----

template<class T>
void bin_output_stream_base::stream(const T *p_, usize_t count_, meta_bool<true> is_pod_stream_)
{
  // copy data from the array to the buffer
  usize_t num_bytes=sizeof(T)*count_;
  if((m_data+=num_bytes)>m_end)
    flush_buffer_nv(p_, num_bytes);
  else
    mem_copy(m_data-num_bytes, p_, num_bytes);
}
//----

template<typename T>
void bin_output_stream_base::stream(const T *p_, usize_t count_, meta_bool<false> is_pod_stream_)
{
  PFC_CTF_ERROR(T, property_enumeration_not_implemented);
}
//----------------------------------------------------------------------------


//============================================================================
// mem_input_stream
//============================================================================
mem_input_stream::mem_input_stream()
{
}
//----

mem_input_stream::mem_input_stream(const void *buf_)
{
  // setup buffer
  m_begin=m_data=reinterpret_cast<const uint8_t*>(buf_);
  m_end=reinterpret_cast<const uint8_t*>(-1);
}
//----

mem_input_stream::mem_input_stream(const void *buf_, usize_t num_bytes_)
{
  // setup buffer
  m_begin=m_data=reinterpret_cast<const uint8_t*>(buf_);
  m_end=m_data+num_bytes_;
}
//----

void mem_input_stream::set(const void *buf_)
{
  // setup buffer
  m_begin=m_data=reinterpret_cast<const uint8_t*>(buf_);
  m_end=reinterpret_cast<const uint8_t*>(-1);
}
//----

void mem_input_stream::set(const void *buf_, usize_t num_bytes_)
{
  // setup buffer
  m_begin=m_data=reinterpret_cast<const uint8_t*>(buf_);
  m_end=m_data+num_bytes_;
}
//----------------------------------------------------------------------------


//============================================================================
// mem_output_stream
//============================================================================
mem_output_stream::mem_output_stream()
{
}
//----

mem_output_stream::mem_output_stream(void *buf_, usize_t num_bytes_)
{
  // setup buffer
  PFC_ASSERT(buf_!=0 || !num_bytes_);
  m_begin=m_data=reinterpret_cast<uint8_t*>(buf_);
  m_end=m_data+num_bytes_;
}
//----

void mem_output_stream::set(void *buf_, usize_t num_bytes_)
{
  // setup buffer
  PFC_ASSERT(buf_!=0 || !num_bytes_);
  m_begin=m_data=reinterpret_cast<uint8_t*>(buf_);
  m_end=m_data+num_bytes_;
}
//----------------------------------------------------------------------------


//============================================================================
// container_input_stream
//============================================================================
template<class Container>
container_input_stream<Container>::container_input_stream()
  :m_container(0)
{
  bin_input_stream_base::init();
}
//----

template<class Container>
container_input_stream<Container>::container_input_stream(const Container &container_)
  :m_container(&container_)
{
  m_is_last=m_container->size()==0;
}
//----

template<class Container>
void container_input_stream<Container>::init(const Container &container_)
{
  // initialize the stream with new container
  bin_input_stream_base::init();
  m_container=&container_;
  m_is_last=m_container->size()==0;
}
//----------------------------------------------------------------------------

template<class Container>
usize_t container_input_stream<Container>::update_buffer_impl(void *p_, usize_t num_bytes_, bool exact_)
{
  // check for direct read
  usize_t read_pos=m_begin_pos+usize_t(m_end-m_begin);
  usize_t bytes_left=m_container->size()-read_pos;
  if(num_bytes_>buffer_size)
  {
    // read data directly to the pointer
    usize_t num_read=min(num_bytes_, bytes_left);
    PFC_CHECK_MSG(!exact_ || num_read==num_bytes_, ("Trying to read beyond the end of the stream\r\n"));
    m_container->get(read_pos, (uint8_t*)p_, num_read);
    m_is_first=false;
    m_begin_pos+=usize_t(m_end-m_begin)+num_read;
    m_is_last=m_begin_pos==m_container->size();
    m_begin=m_end=m_data=0;
    return num_read;
  }

  // read data to the buffer and copy it to the pointer
  usize_t num_read=min(usize_t(buffer_size), bytes_left);
  PFC_CHECK_MSG(!exact_ || num_read>=num_bytes_, ("Trying to read beyond the end of the stream\r\n"));
  m_container->get(read_pos, m_buffer, num_read);
  usize_t num_copied=min(num_read, num_bytes_);
  mem_copy(p_, m_buffer, num_copied);
  m_is_first=m_is_first&&m_begin!=0;
  m_is_last=num_read==bytes_left;
  m_begin_pos+=usize_t(m_end-m_begin);
  m_begin=m_buffer;
  m_end=m_buffer+num_read;
  m_data=m_begin+num_copied;
  return num_copied;
}
//----

template<class Container>
void container_input_stream<Container>::rewind_impl()
{
  // seek to the beginning of the stream
  PFC_ASSERT(m_is_first==false);
  m_is_first=true;
  m_is_last=false;
  m_begin_pos=0;
  m_begin=m_end=m_data=0;
}
//----

template<class Container>
void container_input_stream<Container>::rewind_impl(usize_t num_bytes_)
{
  PFC_ASSERT(num_bytes_);
  PFC_CHECK_MSG(num_bytes_<=usize_t(m_data-m_begin)+m_begin_pos, ("Trying to seek beyond the beginning of the stream\r\n"));
  m_is_first=false;
  m_is_last=false;
  m_begin_pos-=num_bytes_-usize_t(m_data-m_begin);
  m_begin=m_end=m_data=0;
}
//----

template<class Container>
void container_input_stream<Container>::skip_impl()
{
  // advance stream
  m_begin_pos+=usize_t(m_data-m_begin);
  PFC_CHECK_MSG(m_begin_pos<=m_container->size(), ("Trying to seek beyond the end of the stream\r\n"));
  m_is_first=false;
  m_is_last=m_begin_pos==m_container->size();
  m_begin=m_end=m_data=0;
}
//----

template<class Container>
void container_input_stream<Container>::seek_impl(usize_t abs_pos_)
{
  // set absolute stream position
  PFC_CHECK_MSG(abs_pos_<=m_container->size(), ("Trying to seek beyond the end of the stream\r\n"));
  m_is_first=abs_pos_==0;
  m_is_last=abs_pos_==m_container->size();
  m_begin_pos=abs_pos_;
  m_begin=m_end=m_data=0;
}
//----------------------------------------------------------------------------


//============================================================================
// container_output_stream
//============================================================================
template<class Container>
container_output_stream<Container>::container_output_stream()
  :m_container(0)
{
}
//----

template<class Container>
container_output_stream<Container>::container_output_stream(Container &container_)
{
  init(container_);
}
//----

template<class Container>
void container_output_stream<Container>::init(Container &container_)
{
  // initialize stream with new container
  m_container=&container_;
  m_begin=m_data=m_buffer;
  m_end=m_buffer+buffer_size;
  m_begin_pos=0;
}
//----

template<class Container>
container_output_stream<Container>::~container_output_stream()
{
  flush_buffer_impl(0, 0);
}
//----------------------------------------------------------------------------

template<class Container>
void container_output_stream<Container>::flush_buffer_impl(const void *p_, usize_t num_bytes_)
{
  // flush content of the data written to the buffer and handle remaining data
  if(m_container)
    m_container->insert_back(usize_t(m_data-m_begin), m_buffer);
  if(num_bytes_>buffer_size)
  {
    // insert data directly to the container
    m_container->insert_back(num_bytes_, (const uint8_t*)p_);
    m_begin_pos+=usize_t(m_data-m_begin)+num_bytes_;
    m_begin=m_end=m_data=0;
  }
  else
  {
    // write data to the buffer
    mem_copy(m_buffer, p_, num_bytes_);
    m_begin_pos+=usize_t(m_data-m_begin);
    m_begin=m_buffer;
    m_end=m_buffer+buffer_size;
    m_data=m_begin+num_bytes_;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// null_output_stream
//============================================================================
null_output_stream::null_output_stream()
{
  // setup buffer
  m_begin=m_data=s_garbage_bin;
  m_end=s_garbage_bin+garbage_bin_size;
}
//----------------------------------------------------------------------------


//============================================================================
// text_input_stream
//============================================================================
text_input_stream::text_input_stream(bin_input_stream_base &s_)
  :m_stream(s_)
{
  m_next_char=0;
  m_numeric_parsing_error=false;
}
//----------------------------------------------------------------------------

template<typename T>
text_input_stream &text_input_stream::operator>>(T &v_)
{
  stream(v_, meta_case<is_type_float<T>::res?0:is_type_int<T>::res?1:is_type_class<T>::res?2:-1>());
  return *this;
}
//----

template<typename T>
bool text_input_stream::read(T &v_)
{
  m_numeric_parsing_error=false;
  stream(v_, meta_case<is_type_float<T>::res?0:is_type_int<T>::res?1:is_type_class<T>::res?2:-1>());
  return !m_numeric_parsing_error;
}
//----

template<typename T>
usize_t text_input_stream::read(T *p_, usize_t count_)
{
  PFC_ASSERT(p_!=0 || !count_);
  usize_t num_numeric_parsing_ok=0;
  T *end=p_+count_;
  while(p_!=end)
  {
    m_numeric_parsing_error=false;
    stream(*p_++, meta_case<is_type_float<T>::res?0:is_type_int<T>::res?1:is_type_class<T>::res?2:-1>());
    if(!m_numeric_parsing_error)
      ++num_numeric_parsing_ok;
  }
  return num_numeric_parsing_ok;
}
//----

usize_t text_input_stream::read_bytes(void *p_, usize_t num_bytes_, bool exact_)
{
  // read given number of bytes
  if(m_next_char && num_bytes_)
  {
    --num_bytes_;
    *(char*)p_=m_next_char;
    ++(char*&)p_;
    m_next_char=0;
  }
  return m_stream.read_bytes(p_, num_bytes_, exact_);
}
//----

char text_input_stream::read_char()
{
  // read one character
  if(m_next_char)
  {
    char c=m_next_char;
    m_next_char=0;
    return c;
  }
  char c;
  m_stream>>c;
  return c;
}
//----------------------------------------------------------------------------

bool text_input_stream::is_eos() const
{
  return !m_next_char && m_stream.is_eos();
}
//----

usize_t text_input_stream::pos() const
{
  return m_stream.pos()-(m_next_char?1:0);
}
//----

void text_input_stream::rewind()
{
  m_next_char=0;
  m_stream.rewind();
}
//----

void text_input_stream::rewind(usize_t num_bytes_)
{
  // rewind stream given number of bytes
  if(m_next_char && num_bytes_)
  {
    ++num_bytes_;
    m_next_char=0;
  }
  m_stream.rewind(num_bytes_);
}
//----

char text_input_stream::next_char() const
{
  // return the next character in the stream
  if(!m_next_char && !m_stream.is_eos())
    m_stream>>m_next_char;
  return m_next_char;
}
//----------------------------------------------------------------------------

template<typename T>
void text_input_stream::stream(T &v_, meta_case<0> is_type_float_)
{
  v_=T(read_double());
}
//----

template<typename T>
void text_input_stream::stream(T &v_, meta_case<1> is_type_int_)
{
  // round to closest integral value
  double v=read_double();
  v_=T(v+(v<0.0?-0.5:0.5));
}
//----

void text_input_stream::stream(char &v_, meta_case<1> is_type_int_)
{
  // read one character from the stream
  if(m_next_char)
  {
    v_=m_next_char;
    m_next_char=0;
  }
  else
    m_stream>>v_;
}
//----

void text_input_stream::stream(bool &v_, meta_case<1> is_type_int_)
{
  double v=read_double();
  v_=!!v;
}
//----

template<class T>
void text_input_stream::stream(T &v_, meta_case<2> is_type_class_)
{
  PFC_CTF_ERROR(T, property_enumeration_not_implemented);
}
//----

template<typename T>
void text_input_stream::stream(T&, meta_case<-1> default_)
{
  PFC_CTF_ERROR(T, unable_to_deserialize_the_type);
}
//----------------------------------------------------------------------------


//============================================================================
// text_output_stream
//============================================================================
text_output_stream::text_output_stream(bin_output_stream_base &s_, char separator_)
  :m_stream(s_)
  ,m_separator(separator_)
  ,m_float_format("%f")
  ,m_int_format("%i")
  ,m_unsigned_format("%u")
{
}
//----------------------------------------------------------------------------

template<typename T>
text_output_stream &text_output_stream::operator<<(const T &v_)
{
  stream(v_, meta_case<is_type_float<T>::res?0:
                       is_type_signed<T>::res?1:
                       is_type_unsigned<T>::res?2:
                       is_type_class<T>::res?3:
                       -1>());
  return *this;
}
//----

text_output_stream &text_output_stream::operator<<(const char *str_)
{
  m_stream<<str_;
  return *this;
}
//----

text_output_stream &text_output_stream::operator<<(char *str_)
{
  m_stream<<str_;
  return *this;
}
//----

template<typename T>
void text_output_stream::write(const T *p_, usize_t count_)
{
  PFC_ASSERT(p_!=0 || count_);
  while(count_--)
    *this<<(*p_++);
}
//----

void text_output_stream::write_bytes(const void *p_, usize_t num_bytes_)
{
  m_stream.write_bytes(p_, num_bytes_);
}
//----------------------------------------------------------------------------

void text_output_stream::set_float_format(const char *format_)
{
  m_float_format=format_;
}
//----

void text_output_stream::set_int_format(const char *format_)
{
  m_int_format=format_;
}
//----

void text_output_stream::set_unsigned_format(const char *format_)
{
  m_unsigned_format=format_;
}
//----------------------------------------------------------------------------

usize_t text_output_stream::pos() const
{
  return m_stream.pos();
}
//----------------------------------------------------------------------------

template<typename T>
void text_output_stream::stream(T v_, meta_case<0> is_type_float_)
{
  // float formatting
  stack_str64 buf;
  buf.format(m_float_format.c_str(), v_);
  m_stream<<buf.c_str();
  if(m_separator)
    m_stream<<m_separator;
}
//----

template<typename T>
void text_output_stream::stream(T v_, meta_case<1> is_type_signed_)
{
  // signed int formatting
  stack_str64 buf;
  buf.format(m_int_format.c_str(), v_);
  m_stream<<buf.c_str();
  if(m_separator)
    m_stream<<m_separator;
}
//----

void text_output_stream::stream(char v_, meta_case<1> is_type_signed_)
{
  m_stream<<v_;
}
//----

template<typename T>
void text_output_stream::stream(T v_, meta_case<2> is_type_unsigned_)
{
  // unsigned int formatting
  stack_str64 buf;
  buf.format(m_unsigned_format.c_str(), v_, m_separator);
  m_stream<<buf.c_str();
  if(m_separator)
    m_stream<<m_separator;
}
//----

void text_output_stream::stream(bool v_, meta_case<2> is_type_unsigned_)
{
  m_stream<<(v_?"true":"false");
  if(m_separator)
    m_stream<<m_separator;
}
//----

template<class T>
void text_output_stream::stream(const T &v_, meta_case<3> is_type_class_)
{
  PFC_CTF_ERROR(T, property_enumeration_not_implemented);
}
//----

template<typename T>
void text_output_stream::stream(const T &v_, meta_case<-1> default_)
{
  PFC_CTF_ERROR(T, unable_to_serialize_the_type);
}
//----------------------------------------------------------------------------


//============================================================================
// endian_input_stream
//============================================================================
endian_input_stream::endian_input_stream(bin_input_stream_base &s_)
  :m_stream(s_)
{
}
//----------------------------------------------------------------------------

template<typename T>
endian_input_stream &endian_input_stream::operator>>(T &v_)
{
  stream(v_, meta_bool<is_type_class<T>::res>());
  return *this;
}
//----

template<typename T>
void endian_input_stream::read(T *p_, usize_t count_)
{
  PFC_ASSERT_PEDANTIC(p_!=0 || !count_);
  stream(p_, count_, meta_bool<is_type_class<T>::res>());
}
//----

usize_t endian_input_stream::read_bytes(void *p_, usize_t num_bytes_, bool exact_)
{
  return m_stream.read_bytes(p_, num_bytes_, exact_);
}
//----

usize_t endian_input_stream::read_cstr(char *s_, usize_t max_bytes_)
{
  return m_stream.read_cstr(s_, max_bytes_);
}
//----------------------------------------------------------------------------

bool endian_input_stream::is_eos() const
{
  return m_stream.is_eos();
}
//----

usize_t endian_input_stream::pos() const
{
  return m_stream.pos();
}
//----

void endian_input_stream::rewind()
{
  m_stream.rewind();
}
//----

void endian_input_stream::rewind(usize_t num_bytes_)
{
  m_stream.rewind(num_bytes_);
}
//----

void endian_input_stream::skip(usize_t num_bytes_)
{
  m_stream.skip(num_bytes_);
}
//----------------------------------------------------------------------------

template<typename T>
void endian_input_stream::stream(T &v_, meta_bool<false> is_class_)
{
  // read value from stream and emit byte-swapped value
  T v;
  m_stream>>v;
  v_=swap_bytes(v);
}
//----

template<class T>
void endian_input_stream::stream(T &v_, meta_bool<true> is_class_)
{
  PFC_CTF_ERROR(T, property_enumeration_not_implemented);
}
//----

template<typename T>
void endian_input_stream::stream(T *p_, usize_t count_, meta_bool<false> is_class_)
{
  // read values from the stream and emit byte-swapped values
  T *end=p_+count_;
  if(count_)
    do
    {
      T v;
      m_stream>>v;
      *p_=swap_bytes(v);
    } while(++p_<end);
}
//----

template<class T>
void endian_input_stream::stream(T *p_, usize_t count_, meta_bool<true> is_class_)
{
  PFC_CTF_ERROR(T, property_enumeration_not_implemented);
}
//----------------------------------------------------------------------------


//============================================================================
// endian_output_stream
//============================================================================
endian_output_stream::endian_output_stream(bin_output_stream_base &s_)
  :m_stream(s_)
{
}
//----------------------------------------------------------------------------

template<typename T>
endian_output_stream &endian_output_stream::operator<<(const T &v_)
{
  stream(v_, meta_bool<is_type_class<T>::res>());
  return *this;
}
//----

endian_output_stream &endian_output_stream::operator<<(const char *str_)
{
  m_stream<<str_;
  return *this;
}
//----

endian_output_stream &endian_output_stream::operator<<(char *str_)
{
  m_stream<<str_;
  return *this;
}
//----

template<typename T>
void endian_output_stream::write(const T *p_, usize_t count_)
{
  PFC_ASSERT_PEDANTIC(p_!=0 || !count_);
  stream(p_, count_, meta_bool<is_type_class<T>::res>());
}
//----

void endian_output_stream::write_bytes(const void *p_, usize_t num_bytes_)
{
  m_stream.write_bytes(p_, num_bytes_);
}
//----------------------------------------------------------------------------

usize_t endian_output_stream::pos() const
{
  return m_stream.pos();
}
//----------------------------------------------------------------------------

template<typename T>
void endian_output_stream::stream(const T &v_, meta_bool<false> is_class_)
{
  // swap bytes of the value to the stream
  m_stream<<swap_bytes(v_);
}
//----

template<class T>
void endian_output_stream::stream(const T &v_, meta_bool<true> is_class_)
{
  PFC_CTF_ERROR(T, property_enumeration_not_implemented);
}
//----

template<typename T>
void endian_output_stream::stream(const T *p_, usize_t count_, meta_bool<false> is_class_)
{
  // swap bytes in the array
  const T *end=p_+count_;
  if(count_)
    do
    {
      m_stream<<swap_bytes(*p_);
    } while(++p_<end);
}
//----

template<class T>
void endian_output_stream::stream(const T *p_, usize_t count_, meta_bool<true> is_class_)
{
  PFC_CTF_ERROR(T, property_enumeration_not_implemented);
}
//----------------------------------------------------------------------------


//============================================================================
// bit_input_stream
//============================================================================
void bit_input_stream::read_bits(uint32_t &res_, unsigned num_bits_)
{
  // extract num_bits_ from cache
  PFC_ASSERT_PEDANTIC(num_bits_<=24);
  if(m_cache_bit_pos>=(cache_size-max_type_size)*8)
    update_cache();
  uint32_t v;
  memcpy(&v, m_cache+(m_cache_bit_pos>>3), 4);
  res_=(v>>(m_cache_bit_pos&7))&((1<<num_bits_)-1);
  m_cache_bit_pos+=num_bits_;
}
//----

void bit_input_stream::read_bits(int32_t &res_, unsigned num_bits_)
{
  // extract num_bits_ from cache
  PFC_ASSERT_PEDANTIC(num_bits_<=24);
  if(m_cache_bit_pos>=(cache_size-max_type_size)*8)
    update_cache();
  int32_t v;
  memcpy(&v, m_cache+(m_cache_bit_pos>>3), 4);
  unsigned sh=32-num_bits_;
  res_=int32_t(v<<(sh-(m_cache_bit_pos&7)))>>sh;
  m_cache_bit_pos+=num_bits_;
}
//----------------------------------------------------------------------------

usize_t bit_input_stream::length() const
{
  return m_bit_stream_length;
}
//----

bool bit_input_stream::is_eos() const
{
  return m_cache_start_bit_pos+m_cache_bit_pos>=m_bit_stream_length;
}
//----

usize_t bit_input_stream::bit_pos() const
{
  usize_t bpos=m_cache_start_bit_pos+m_cache_bit_pos;
  return bpos<m_bit_stream_length?bpos:m_bit_stream_length;
}
//----

void bit_input_stream::skip_bits(usize_t num_bits_)
{
  m_cache_bit_pos+=(unsigned)num_bits_;
}
//----------------------------------------------------------------------------


//============================================================================
// auto_stream_seek
//============================================================================
template<class S>
auto_stream_seek<S>::auto_stream_seek(S &s_, usize_t size_)
  :m_stream(s_)
{
  m_size=size_;
  m_begin_pos=s_.pos();
}
//----

template<class S>
auto_stream_seek<S>::~auto_stream_seek()
{
  // set stream to the pre-defined position
  usize_t current_pos=m_stream.pos();
  usize_t new_pos=m_size+m_begin_pos;
  if(new_pos<current_pos)
    m_stream.rewind(current_pos-new_pos);
  else
    m_stream.skip(new_pos-current_pos);
}
//----

template<class S>
void auto_stream_seek<S>::reset()
{
  // reset stream skip
  m_begin_pos=m_stream.pos();
  m_size=0;
}
//----------------------------------------------------------------------------
