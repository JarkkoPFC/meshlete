//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================


//============================================================================
// str_base
//============================================================================
template<class S>
void str_base<S>::operator=(const str_base &str_)
{
  static_cast<S*>(this)->operator=(str_);
}
//----

template<class S>
template<class S2>
void str_base<S>::operator=(const str_base<S2> &str_)
{
  static_cast<S*>(this)->operator=(str_);
}
//----

template<class S>
void str_base<S>::operator=(const char *cstr_)
{
  static_cast<S*>(this)->operator=(cstr_);
}
//----

template<class S>
void str_base<S>::set(const char *str_, usize_t num_chars_)
{
  static_cast<S*>(this)->set(str_, num_chars_);
}
//----

template<class S>
void str_base<S>::clear()
{
  static_cast<S*>(this)->clear();
}
//----------------------------------------------------------------------------

template<class S>
usize_t str_base<S>::size() const
{
  return static_cast<const S*>(this)->size();
}
//----

template<class S>
usize_t str_base<S>::capacity() const
{
  return static_cast<const S*>(this)->capacity();
}
//----

template<class S>
const char &str_base<S>::operator[](usize_t idx_) const
{
  return static_cast<const S*>(this)->operator[](idx_);
}
//----

template<class S>
char &str_base<S>::operator[](usize_t idx_)
{
  return static_cast<S*>(this)->operator[](idx_);
}
//----

template<class S>
const char &str_base<S>::front() const
{
  return static_cast<const S*>(this)->front();
}
//----

template<class S>
char &str_base<S>::front()
{
  return static_cast<S*>(this)->front();
}
//----

template<class S>
const char &str_base<S>::back() const
{
  return static_cast<const S*>(this)->back();
}
//----

template<class S>
char &str_base<S>::back()
{
  return static_cast<S*>(this)->back();
}
//----

template<class S>
const char *str_base<S>::c_str() const
{
  return static_cast<const S*>(this)->c_str();
}
//----

template<class S>
char *str_base<S>::c_str()
{
  return static_cast<S*>(this)->c_str();
}
//----

template<class S>
const char *str_base<S>::data() const
{
  return static_cast<const S*>(this)->data();
}
//----

template<class S>
char *str_base<S>::data()
{
  return static_cast<S*>(this)->data();
}
//----

template<class S>
template<class S2>
void str_base<S>::operator+=(const str_base<S2> &str_)
{
  static_cast<S*>(this)->operator+=(str_);
}
//----

template<class S>
void str_base<S>::operator+=(const char *cstr_)
{
  static_cast<S*>(this)->operator+=(cstr_);
}
//----

template<class S>
void str_base<S>::operator+=(char c_)
{
  static_cast<S*>(this)->operator+=(c_);
}
//----

template<class S>
void str_base<S>::format(const char *cstr_, ...)
{
  // setup formatted string
  char buf[max_format_str_size];
  va_list args;
  va_start(args, cstr_);
  int new_size=vsnprintf(buf, sizeof(buf), cstr_, args);
  PFC_ASSERT(new_size!=-1);
  static_cast<S*>(this)->set(buf, new_size);
}
//----

template<class S>
void str_base<S>::push_front(char c_)
{
  static_cast<S*>(this)->push_front(c_);
}
//----

template<class S>
void str_base<S>::push_front(char c_, usize_t num_chars_)
{
  static_cast<S*>(this)->push_front(c_, num_chars_);
}
//----

template<class S>
void str_base<S>::push_front(const char *cstr_)
{
  static_cast<S*>(this)->push_back(cstr_);
}
//----

template<class S>
void str_base<S>::push_front(const char *str_, usize_t num_chars_)
{
  static_cast<S*>(this)->push_back(str_, num_chars_);
}
//----

template<class S>
void str_base<S>::push_back(char c_)
{
  static_cast<S*>(this)->push_back(c_);
}
//----

template<class S>
void str_base<S>::push_back(char c_, usize_t num_chars_)
{
  static_cast<S*>(this)->push_back(c_, num_chars_);
}
//----

template<class S>
void str_base<S>::push_back(const char *str_, usize_t num_chars_)
{
  static_cast<S*>(this)->push_back(str_, num_chars_);
}
//----

template<class S>
void str_base<S>::push_back_format(const char *cstr_, ...)
{
  // append formatted string to the string
  char buf[max_format_str_size];
  va_list args;
  va_start(args, cstr_);
  int size=vsnprintf(buf, sizeof(buf), cstr_, args);
  PFC_ASSERT(size!=-1);
  static_cast<S*>(this)->push_back(buf, size);
}
//----

template<class S>
void str_base<S>::remove_front(usize_t num_chars_)
{
  static_cast<S*>(this)->remove_front(num_chars_);
}
//----

template<class S>
void str_base<S>::remove_back(usize_t num_chars_)
{
  static_cast<S*>(this)->remove_back(num_chars_);
}
//----------------------------------------------------------------------------

template<class S>
str_base<S>::str_base()
{
}
//----

template<class S>
str_base<S>::str_base(const str_base&)
{
}
//----

template<class S>
str_base<S>::~str_base()
{
}
//----------------------------------------------------------------------------


//============================================================================
// is_type_str
//============================================================================
namespace priv
{
  template<typename T> int is_type_str_hlp(const str_base<T>&);
  char is_type_str_hlp(...);
} // namespace priv
//----------------------------------------------------------------------------

template<typename T>
struct is_type_str
{
  enum {res=1!=sizeof(priv::is_type_str_hlp(*(T*)0))};
};
//----------------------------------------------------------------------------


//============================================================================
// heap_str
//============================================================================
heap_str::heap_str(memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // initialize heap string
  m_data=0;
  m_size=0;
  m_capacity=0;
}
//----

heap_str::heap_str(const heap_str &str_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // construct heap string from another heap string
  usize_t len=str_.m_size;
  m_size=len;
  m_capacity=len;
  m_data=len?(char*)m_allocator->alloc(m_capacity+1):0;
  mem_copy(m_data, str_.m_data, len);
}
//----

template<class S>
heap_str::heap_str(const str_base<S> &str_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // construct heap string from the base string
  usize_t len=static_cast<const S&>(str_).size();
  m_size=len;
  m_capacity=len;
  m_data=len?(char*)m_allocator->alloc(m_capacity+1):0;
  mem_copy(m_data, static_cast<const S&>(str_).data(), len);
}
//----

heap_str::heap_str(const char *cstr_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // construct heap string from the c-string
  usize_t len=str_size(cstr_);
  m_size=len;
  m_capacity=len;
  m_data=len?(char*)m_allocator->alloc(m_capacity+1):0;
  mem_copy(m_data, cstr_, len);
}
//----

heap_str::heap_str(const char *str_, usize_t num_chars_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // construct heap string from given size c-string
  m_size=num_chars_;
  m_capacity=num_chars_;
  m_data=num_chars_?(char*)m_allocator->alloc(num_chars_+1):0;
  mem_copy(m_data, str_, num_chars_);
}
//----

heap_str::heap_str(char c_, memory_allocator_base *alloc_)
  :m_allocator(alloc_?alloc_:&default_memory_allocator::inst())
{
  // construct heap string from a character
  m_size=1;
  m_capacity=1;
  m_data=(char*)m_allocator->alloc(2);
  *m_data=c_;
}
//----

heap_str::~heap_str()
{
  // release string data
  m_allocator->free(m_data);
}
//----

void heap_str::set_allocator(memory_allocator_base *alloc_)
{
  PFC_ASSERT_MSG(!m_data, ("Unable to change the allocator of heap_str with capacity\r\n"));
  m_allocator=alloc_?alloc_:&default_memory_allocator::inst();
}
//----

void heap_str::operator=(const heap_str &str_)
{
  // assign string from another heap string
  PFC_MEM_TRACK_STACK();
  usize_t new_size=str_.m_size;
  if(m_capacity<new_size)
    reserve_offset(new_size, 0);
  mem_copy(m_data, str_.m_data, new_size);
  m_size=new_size;
}
//----

template<class S>
void heap_str::operator=(const str_base<S> &str_)
{
  // assign string from a base string
  PFC_MEM_TRACK_STACK();
  usize_t new_size=static_cast<const S&>(str_).size();
  if(m_capacity<new_size)
    reserve_offset(new_size, 0);
  mem_copy(m_data, static_cast<const S&>(str_).data(), new_size);
  m_size=new_size;
}
//----

void heap_str::operator=(const char *cstr_)
{
  // assign string from the c-string
  PFC_MEM_TRACK_STACK();
  usize_t new_size=cstr_?str_size(cstr_):0;
  if(m_capacity<new_size)
    reserve_offset(new_size, 0);
  mem_copy(m_data, cstr_, new_size);
  m_size=new_size;
}
//----

void heap_str::set(const char *str_, usize_t num_chars_)
{
  // assign string of given size to the string
  if(m_capacity<num_chars_)
    reserve_offset(num_chars_, 0);
  mem_copy(m_data, str_, num_chars_);
  m_size=num_chars_;
}
//----

void heap_str::clear()
{
  // clear string content
  m_allocator->free(m_data);
  m_data=0;
  m_size=0;
  m_capacity=0;
}
//----

void heap_str::reset_size(usize_t size_)
{
  // reallocate string
  PFC_MEM_TRACK_STACK();
  if(m_size!=size_)
  {
    m_allocator->free(m_data);
    m_data=(char*)m_allocator->alloc(size_);
    m_size=m_capacity=size_;
  }
}
//----

void heap_str::resize(usize_t size_)
{
  // resize string
  PFC_MEM_TRACK_STACK();
  if(m_capacity<size_)
    reserve_offset(size_, 0);
  m_size=size_;
}
//----

void heap_str::reserve(usize_t capacity_)
{
  if(m_capacity<capacity_)
  {
    // copy string to a new buffer with given capacity
    char *data=(char*)m_allocator->alloc(capacity_+1);
    m_capacity=capacity_;
    mem_copy(data, m_data, m_size);
    m_allocator->free(m_data);
    m_data=data;
  }
}
//----------------------------------------------------------------------------

memory_allocator_base &heap_str::allocator() const
{
  return *m_allocator;
}
//----

usize_t heap_str::size() const
{
  return m_size;
}
//----

usize_t heap_str::capacity() const
{
  return m_capacity;
}
//----

const char &heap_str::operator[](usize_t idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<m_size);
  return m_data[idx_];
}
//----

char &heap_str::operator[](usize_t idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<m_size);
  return m_data[idx_];
}
//----

const char &heap_str::front() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return *m_data;
}
//----

char &heap_str::front()
{
  PFC_ASSERT_PEDANTIC(m_size);
  return *m_data;
}
//----

const char &heap_str::back() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return m_data[m_size-1];
}
//----

char &heap_str::back()
{
  PFC_ASSERT_PEDANTIC(m_size);
  return m_data[m_size-1];
}
//----

const char *heap_str::c_str() const
{
  // return c-string of the string
  if(!m_data)
    return "";
  const_cast<char&>(m_data[m_size])=0;
  return m_data;
}
//----

char *heap_str::c_str()
{
  // return c-string of the string
  if(!m_data)
  {
    static char c=0;
    return &c;
  }
  m_data[m_size]=0;
  return m_data;
}
//----

const char *heap_str::data() const
{
  return m_data;
}
//----

char *heap_str::data()
{
  return m_data;
}
//----

template<class S> void heap_str::operator+=(const str_base<S> &str_)
{
  // append base string to the string
  usize_t size=static_cast<const S&>(str_).size();
  usize_t new_size=m_size+size;
  if(m_capacity<new_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve_offset(max(usize_t(min_grow_alloc), new_size, m_size*2), 0);
  }
  mem_copy(m_data+m_size, static_cast<const S&>(str_).data(), size);
  m_size=new_size;
}
//----

void heap_str::operator+=(const char *cstr_)
{
  // append c-string to the string
  usize_t size=str_size(cstr_);
  usize_t new_size=m_size+size;
  if(m_capacity<new_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve_offset(max(usize_t(min_grow_alloc), new_size, m_size*2), 0);
  }
  mem_copy(m_data+m_size, cstr_, size);
  m_size=new_size;
}
//----

void heap_str::operator+=(char c_)
{
  // append character to the string
  if(m_capacity==m_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve_offset(max(usize_t(min_grow_alloc), m_size*2), 0);
  }
  m_data[m_size++]=c_;
}
//----

void heap_str::push_front(char c_)
{
  // prepend character to the string
  usize_t new_size=m_size+1;
  if(m_capacity<new_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve_offset(max(usize_t(min_grow_alloc), new_size, m_size*2), 1);
  }
  else
    mem_move(m_data+1, m_data, m_size);
  *m_data=c_;
  m_size=new_size;
}
//----

void heap_str::push_front(char c_, usize_t num_chars_)
{
  // prepend given number of characters to the string
  usize_t new_size=m_size+num_chars_;
  if(m_capacity<new_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve_offset(max(usize_t(min_grow_alloc), new_size, m_size*2), num_chars_);
  }
  else
    mem_move(m_data+num_chars_, m_data, m_size);
  mem_set(m_data, c_, num_chars_);
  m_size=new_size;
}
//----

void heap_str::push_front(const char *cstr_)
{
  // prepend c-string to the string
  if(cstr_)
  {
    usize_t size=str_size(cstr_);
    push_front(cstr_, size);
  }
}
//----

void heap_str::push_front(const char *str_, usize_t num_chars_)
{
  // prepend string of given size to the string
  PFC_ASSERT(str_ || !num_chars_);
  usize_t new_size=m_size+num_chars_;
  if(m_capacity<new_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve_offset(max(usize_t(min_grow_alloc), new_size, m_size*2), num_chars_);
  }
  else
    mem_move(m_data+num_chars_, m_data, m_size);
  mem_copy(m_data, str_, num_chars_);
  m_size=new_size;
}
//----

void heap_str::push_back(char c_)
{
  // append character to the string
  if(m_capacity==m_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve_offset(max(usize_t(min_grow_alloc), m_size*2), 0);
  }
  m_data[m_size++]=c_;
}
//----

void heap_str::push_back(char c_, usize_t num_chars_)
{
  // append given number of characters to the string
  usize_t new_size=m_size+num_chars_;
  if(m_capacity<new_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve(max(usize_t(min_grow_alloc), new_size, m_size*2));
  }
  mem_set(m_data+m_size, c_, num_chars_);
  m_size=new_size;
}
//----

void heap_str::push_back(const char *str_, usize_t num_chars_)
{
  // append string of given size of the string
  usize_t new_size=m_size+num_chars_;
  if(m_capacity<new_size)
  {
    PFC_MEM_TRACK_STACK();
    reserve(max(usize_t(min_grow_alloc), new_size, m_size*2));
  }
  mem_copy(m_data+m_size, str_, num_chars_);
  m_size=new_size;
}
//----

void heap_str::remove_front(usize_t num_chars_)
{
  // remove given number of characters from the beginning of the string
  PFC_ASSERT(m_size>=num_chars_);
  usize_t new_size=m_size-num_chars_;
  mem_move(m_data, m_data+num_chars_, new_size);
  m_size=new_size;
}
//----

void heap_str::remove_back(usize_t num_chars_)
{
  // remove given number of characters from the end of the string
  PFC_ASSERT(m_size>=num_chars_);
  m_size-=num_chars_;
}
//----------------------------------------------------------------------------

void heap_str::reserve_offset(usize_t capacity_, usize_t offset_)
{
  // copy string to a new buffer with given capacity & offset
  char *data=(char*)m_allocator->alloc(capacity_+1);
  m_capacity=capacity_;
  mem_copy(data+offset_, m_data, m_size);
  m_allocator->free(m_data);
  m_data=data;
}
//----------------------------------------------------------------------------


//============================================================================
// hash_func<heap_str>
//============================================================================
template<>
struct hash_func<heap_str>
{
  static unsigned index(const heap_str &str_)
  {
    extern uint32_t crc32(const void*, usize_t num_bytes_, uint32_t seed_=0xffffffff);
    return crc32(str_.data(), str_.size());
  }
};
//----------------------------------------------------------------------------


//============================================================================
// stack_str
//============================================================================
template<unsigned cap>
stack_str<cap>::stack_str()
  :m_size(0)
{
}
//----

template<unsigned cap>
stack_str<cap>::stack_str(const stack_str &str_)
  :m_size(str_.m_size)
{
  mem_copy(m_data, str_.m_data, m_size);
}
//----

template<unsigned cap>
template<class S>
stack_str<cap>::stack_str(const str_base<S> &str_)
  :m_size(size_type(static_cast<const S&>(str_).size()))
{
  PFC_ASSERT_PEDANTIC(static_cast<const S&>(str_).size()<=cap);
  mem_copy(m_data, static_cast<const S&>(str_).data(), m_size);
}
//----

template<unsigned cap>
stack_str<cap>::stack_str(const char *cstr_)
{
  // construct string from the c-string
  usize_t l=cstr_?str_size(cstr_):0;
  PFC_ASSERT_PEDANTIC(l<=cap);
  m_size=size_type(l);
  mem_copy(m_data, cstr_, l);
}
//----

template<unsigned cap>
stack_str<cap>::stack_str(char c_)
{
  // construct string from a character
  m_size=1;
  *m_data=c_;
}
//----

template<unsigned cap>
void stack_str<cap>::operator=(const stack_str &str_)
{
  m_size=str_.m_size;
  mem_copy(m_data, str_.m_data, m_size);
}
//----

template<unsigned cap>
template<class S>
void stack_str<cap>::operator=(const str_base<S> &str_)
{                                                       
  m_size=size_type(static_cast<const S&>(str_).size());
  PFC_ASSERT_PEDANTIC(static_cast<const S&>(str_).size()<=cap);
  mem_copy(m_data, static_cast<const S&>(str_).data(), m_size);
}
//----

template<unsigned cap>
void stack_str<cap>::operator=(const char *cstr_)
{
  usize_t l=cstr_?str_size(cstr_):0;
  PFC_ASSERT_PEDANTIC(l<=cap);
  m_size=size_type(l);
  mem_copy(m_data, cstr_, l);
}
//----

template<unsigned cap>
void stack_str<cap>::set(const char *str_, usize_t num_chars_)
{
  // assign string of given size to the string
  PFC_ASSERT_PEDANTIC(num_chars_<=cap);
  mem_copy(m_data, str_, num_chars_);
  m_size=size_type(num_chars_);
}
//----

template<unsigned cap>
void stack_str<cap>::clear()
{
  m_size=0;
}
//----

template<unsigned cap>
void stack_str<cap>::resize(usize_t size_)
{
  PFC_ASSERT(size_<=cap);
  m_size=size_type(size_);
}
//----------------------------------------------------------------------------

template<unsigned cap>
usize_t stack_str<cap>::size() const
{
  return m_size;
}
//----

template<unsigned cap>
usize_t stack_str<cap>::capacity() const
{
  return cap;
}
//----

template<unsigned cap>
const char &stack_str<cap>::operator[](usize_t idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<m_size);
  return m_data[idx_];
}
//----

template<unsigned cap>
char &stack_str<cap>::operator[](usize_t idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<m_size);
  return m_data[idx_];
}
//----

template<unsigned cap>
const char &stack_str<cap>::front() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return *m_data;
}
//----

template<unsigned cap>
char &stack_str<cap>::front()
{
  PFC_ASSERT_PEDANTIC(m_size);
  return *m_data;
}
//----

template<unsigned cap>
const char &stack_str<cap>::back() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return m_data[m_size-1];
}
//----

template<unsigned cap>
char &stack_str<cap>::back()
{
  PFC_ASSERT_PEDANTIC(m_size);
  return m_data[m_size-1];
}
//----

template<unsigned cap>
const char *stack_str<cap>::c_str() const
{
  const_cast<char&>(m_data[m_size])=0;
  return m_data;
}
//----

template<unsigned cap>
char *stack_str<cap>::c_str()
{
  m_data[m_size]=0;
  return m_data;
}
//----

template<unsigned cap>
const char *stack_str<cap>::data() const
{
  return m_data;
}
//----

template<unsigned cap>
char *stack_str<cap>::data()
{
  return m_data;
}
//----

template<unsigned cap>
template<class S>
void stack_str<cap>::operator+=(const str_base<S> &str_)
{
  // append base string to the string
  usize_t l=static_cast<const S&>(str_).size();
  PFC_ASSERT_PEDANTIC(m_size+l<=cap);
  mem_copy(m_data+m_size, static_cast<const S&>(str_).data(), l);
  m_size=m_size+size_type(l);
}
//----

template<unsigned cap>
void stack_str<cap>::operator+=(const char *cstr_)
{
  // append c-string to the string
  usize_t l=str_size(cstr_);
  PFC_ASSERT_PEDANTIC(m_size+l<=cap);
  mem_copy(m_data+m_size, cstr_, l);
  m_size=m_size+size_type(l);
}
//----

template<unsigned cap>
void stack_str<cap>::operator+=(char c_)
{
  // append character to the string
  PFC_ASSERT_PEDANTIC(m_size<cap);
  m_data[m_size++]=c_;
}
//----

template<unsigned cap>
void stack_str<cap>::push_front(char c_)
{
  // prepend character to the string
  PFC_ASSERT(m_size<cap);
  mem_move(m_data+1, m_data, m_size);
  *m_data=c_;
  ++m_size;
}
//----

template<unsigned cap>
void stack_str<cap>::push_front(char c_, usize_t num_chars_)
{
  // prepend given number of characters to the string
  usize_t new_size=m_size+num_chars_;
  PFC_ASSERT(new_size<=cap);
  mem_move(m_data+num_chars_, m_data, m_size);
  mem_set(m_data, c_, num_chars_);
  m_size=size_type(new_size);
}
//----

template<unsigned cap>
void stack_str<cap>::push_front(const char *cstr_)
{
  // prepend c-string to the string
  if(cstr_)
  {
    usize_t size=str_size(cstr_);
    push_front(cstr_, size);
  }
}
//----

template<unsigned cap>
void stack_str<cap>::push_front(const char *str_, usize_t num_chars_)
{
  // prepend string of given size to the string
  PFC_ASSERT(str_ || !num_chars_);
  usize_t new_size=m_size+num_chars_;
  PFC_ASSERT(new_size<=cap);
  mem_move(m_data+num_chars_, m_data, m_size);
  mem_copy(m_data, str_, num_chars_);
  m_size=size_type(new_size);
}
//----

template<unsigned cap>
void stack_str<cap>::push_back(char c_)
{
  // append character to the string
  PFC_ASSERT_PEDANTIC(m_size<cap);
  m_data[m_size++]=c_;
}
//----

template<unsigned cap>
void stack_str<cap>::push_back(char c_, usize_t num_chars_)
{
  // append given number of characters to the string
  PFC_ASSERT(m_size+num_chars_<=cap);
  mem_set(m_data+m_size, c_, num_chars_);
  m_size+=size_type(num_chars_);
}
//----

template<unsigned cap>
void stack_str<cap>::push_back(const char *str_, usize_t num_chars_)
{
  // append string of given size to the string
  PFC_ASSERT(m_size+num_chars_<=cap);
  mem_copy(m_data+m_size, str_, num_chars_);
  m_size+=size_type(num_chars_);
}
//----

template<unsigned cap>
void stack_str<cap>::remove_front(usize_t num_chars_)
{
  // remove given number of characters from the beginning of the string
  PFC_ASSERT(m_size>=num_chars_);
  usize_t new_size=m_size-num_chars_;
  mem_move(m_data, m_data+num_chars_, new_size);
  m_size=size_type(new_size);
}
//----

template<unsigned cap>
void stack_str<cap>::remove_back(usize_t num_chars_)
{
  // remove given number of characters from the end of the string
  PFC_ASSERT(m_size>=num_chars_);
  m_size-=size_type(num_chars_);
}
//----------------------------------------------------------------------------


//============================================================================
// hash_func<stack_str>
//============================================================================
template<unsigned cap>
struct hash_func<stack_str<cap> >
{
  static PFC_INLINE unsigned index(const stack_str<cap> &str_)
  {
    extern uint32_t crc32(const void*, usize_t num_bytes_, uint32_t seed_=0xffffffff);
    return crc32(str_.data(), str_.size());
  }
};
//----------------------------------------------------------------------------


//============================================================================
// string operations
//============================================================================
template<class S0, class S1>
PFC_INLINE bool operator==(const str_base<S0> &str0_, const str_base<S1> &str1_)
{
  // test for equality of base strings
  usize_t size=static_cast<const S0&>(str0_).size();
  return (void*)&str0_==(void*)&str1_ || (   static_cast<const S1&>(str1_).size()==size
                                          && mem_eq(static_cast<const S0&>(str0_).data(), static_cast<const S1&>(str1_).data(), size));
}
//----

template<class S>
PFC_INLINE bool operator==(const str_base<S> &str_, const char *cstr_)
{
  // test for equality of base string and c-string
  usize_t size=str_size(cstr_);
  const char *data=static_cast<const S&>(str_).data();
  return data==cstr_ || (static_cast<const S&>(str_).size()==size && mem_eq(data, cstr_, size));
}
//----

template<class S>
PFC_INLINE bool operator==(const char *cstr_, const str_base<S> &str_)
{
  // test for equality of base string and c-string
  usize_t size=str_size(cstr_);
  const char *data=static_cast<const S&>(str_).data();
  return data==cstr_ || (static_cast<const S&>(str_).size()==size && mem_eq(data, cstr_, size));
}
//----

template<class S>
PFC_INLINE bool operator==(const str_base<S> &str_, char c_)
{
  // test for equality of base string and char
  usize_t size=c_?1:0;
  return static_cast<const S&>(str_).size()==size && (!size || static_cast<const S&>(str_).front()==c_);
}
//----

template<class S>
PFC_INLINE bool operator==(char c_, const str_base<S> &str_)
{
  // test for equality of base string and char
  usize_t size=c_?1:0;
  return static_cast<const S&>(str_).size()==size && (!size || static_cast<const S&>(str_).front()==c_);
}
//----

template<class S0, class S1>
PFC_INLINE bool operator!=(const str_base<S0> &str0_, const str_base<S1> &str1_)
{
  // test for inequality of base strings
  usize_t size=static_cast<const S0&>(str0_).size();
  return (void*)&str0_!=(void*)&str1_ && (   static_cast<const S1&>(str1_).size()!=size
                                          || !mem_eq(static_cast<const S0&>(str0_).data(), static_cast<const S1&>(str1_).data(), size));
}
//----

template<class S>
PFC_INLINE bool operator!=(const str_base<S> &str_, const char *cstr_)
{
  // test for inequality of base strings and c-string
  usize_t size=str_size(cstr_);
  const char *data=static_cast<const S&>(str_).data();
  return data!=cstr_ && (static_cast<const S&>(str_).size()!=size || !mem_eq(data, cstr_, size));
}
//----

template<class S>
PFC_INLINE bool operator!=(const char *cstr_, const str_base<S> &str_)
{
  // test for inequality of base strings and c-string
  usize_t size=str_size(cstr_);
  const char *data=static_cast<const S&>(str_).data();
  return data!=cstr_ && (static_cast<const S&>(str_).size()!=size || !mem_eq(data, cstr_, size));
}
//----

template<class S>
PFC_INLINE bool operator!=(const str_base<S> &str_, char c_)
{
  // test for inequality of base string and char
  usize_t size=c_?1:0;
  return static_cast<const S&>(str_).size()!=size || (size && static_cast<const S&>(str_).front()!=c_);
}
//----

template<class S>
PFC_INLINE bool operator!=(char c_, const str_base<S> &str_)
{
  // test for inequality of base string and char
  usize_t size=c_?1:0;
  return static_cast<const S&>(str_).size()!=size || (size && static_cast<const S&>(str_).front()!=c_);
}
//----

template<class S0, class S1>
PFC_INLINE bool operator<(const str_base<S0> &str0_, const str_base<S1> &str1_)
{
  // test if base string is smaller than another base string
  usize_t size0=static_cast<const S0&>(str0_).size();
  usize_t size1=static_cast<const S1&>(str1_).size();
  int r=mem_diff(static_cast<const S0&>(str0_).data(), static_cast<const S1&>(str1_).data(), min(size0, size1));
  return r<0 || (r==0 && size0<size1);
}
//----

template<class S>
PFC_INLINE bool operator<(const str_base<S> &str_, const char *cstr_)
{
  // test if base string is smaller than c-string
  usize_t size0=static_cast<const S&>(str_).size();
  usize_t size1=str_size(cstr_);
  int r=mem_diff(static_cast<const S&>(str_).data(), cstr_, min(size0, size1));
  return r<0 || (r==0 && size0<size1);
}
//----

template<class S>
PFC_INLINE bool operator<(const char *cstr_, const str_base<S> &str_)
{
  // test if c-string is smaller than base string
  usize_t size0=str_size(cstr_);
  usize_t size1=static_cast<const S&>(str_).size();
  int r=mem_diff(cstr_, static_cast<const S&>(str_).data(), min(size0, size1));
  return r<0 || (r==0 && size0<size1);
}
//----

template<class S>
PFC_INLINE bool operator<(const str_base<S> &str_, char c_)
{
  // test if base string is smaller than char
  usize_t size0=static_cast<const S&>(str_).size();
  usize_t size1=c_?1:0;
  int r=(size0 && size1)?static_cast<const S&>(str_).front()-c_:0;
  return r<0 || (r==0 && size0<size1);
}
//----

template<class S>
PFC_INLINE bool operator<(char c_, const str_base<S> &str_)
{
  // test if char is smaller than base string
  usize_t size0=c_?1:0;
  usize_t size1=static_cast<const S&>(str_).size();
  int r=(size0 && size1)?c_-static_cast<const S&>(str_).front():0;
  return r<0 || (r==0 && size0<size1);
}
//----

template<class S0, class S1>
PFC_INLINE bool operator>(const str_base<S0> &str0_, const str_base<S1> &str1_)
{
  // test if base string is greater than another base string
  usize_t size0=static_cast<const S0&>(str0_).size();
  usize_t size1=static_cast<const S1&>(str1_).size();
  int r=mem_diff(static_cast<const S0&>(str0_).data(), static_cast<const S1&>(str1_).data(), min(size0, size1));
  return r>0 || (r==0 && size0>size1);
}
//----

template<class S>
PFC_INLINE bool operator>(const str_base<S> &str_, const char *cstr_)
{
  // test if base string is greater than c-string
  usize_t size0=static_cast<const S&>(str_).size();
  usize_t size1=str_size(cstr_);
  int r=mem_diff(static_cast<const S&>(str_).data(), cstr_, min(size0, size1));
  return r>0 || (r==0 && size0>size1);
}
//----

template<class S>
PFC_INLINE bool operator>(const char *cstr_, const str_base<S> &str_)
{
  // test if c-string is greater than base string
  usize_t size0=str_size(cstr_);
  usize_t size1=static_cast<const S&>(str_).size();
  int r=mem_diff(cstr_, static_cast<const S&>(str_).data(), min(size0, size1));
  return r>0 || (r==0 && size0>size1);
}
//----

template<class S>
PFC_INLINE bool operator>(const str_base<S> &str_, char c_)
{
  // test if base string is greater than char
  usize_t size0=static_cast<const S&>(str_).size();
  usize_t size1=c_?1:0;
  int r=(size0 && size1)?static_cast<const S&>(str_).front()-c_:0;
  return r>0 || (r==0 && size0>size1);
}
//----

template<class S>
PFC_INLINE bool operator>(char c_, const str_base<S> &str_)
{
  // test if char is greater than base string
  usize_t size0=c_?1:0;
  usize_t size1=static_cast<const S&>(str_).size();
  int r=(size0 && size1)?c_-static_cast<const S&>(str_).front():0;
  return r>0 || (r==0 && size0>size1);
}
//----

template<class S0, class S1>
PFC_INLINE bool operator<=(const str_base<S0> &str0_, const str_base<S1> &str1_)
{
  // test if base string is smaller than or equal to another base string
  usize_t size0=static_cast<const S0&>(str0_).size();
  usize_t size1=static_cast<const S1&>(str1_).size();
  int r=mem_diff(static_cast<const S0&>(str0_).data(), static_cast<const S1&>(str1_).data(), min(size0, size1));
  return r<0 || (r==0 && size0<=size1);
}
//----

template<class S>
PFC_INLINE bool operator<=(const str_base<S> &str_, const char *cstr_)
{
  // test if base string is smaller than or equal to c-string
  usize_t size0=static_cast<const S&>(str_).size();
  usize_t size1=str_size(cstr_);
  int r=mem_diff(static_cast<const S&>(str_).data(), cstr_, min(size0, size1));
  return r<0 || (r==0 && size0<=size1);
}
//----

template<class S>
PFC_INLINE bool operator<=(const char *cstr_, const str_base<S> &str_)
{
  // test if c-string is smaller than or equal to base string
  usize_t size0=str_size(cstr_);
  usize_t size1=static_cast<const S&>(str_).size();
  int r=mem_diff(cstr_, static_cast<const S&>(str_).data(), min(size0, size1));
  return r<0 || (r==0 && size0<=size1);
}
//----

template<class S>
PFC_INLINE bool operator<=(const str_base<S> &str_, char c_)
{
  // test if base string is smaller than or equal to char
  usize_t size0=static_cast<const S&>(str_).size();
  usize_t size1=c_?1:0;
  int r=(size0 && size1)?static_cast<const S&>(str_).front()-c_:0;
  return r<0 || (r==0 && size0<=size1);
}
//----

template<class S>
PFC_INLINE bool operator<=(char c_, const str_base<S> &str_)
{
  // test if char is smaller than or equal to base string
  usize_t size0=c_?1:0;
  usize_t size1=static_cast<const S&>(str_).size();
  int r=(size0 && size1)?c_-static_cast<const S&>(str_).front():0;
  return r<0 || (r==0 && size0<=size1);
}
//----

template<class S0, class S1>
PFC_INLINE bool operator>=(const str_base<S0> &str0_, const str_base<S1> &str1_)
{
  // test if base string is greater than or equal to another base string
  usize_t size0=static_cast<const S0&>(str0_).size();
  usize_t size1=static_cast<const S1&>(str1_).size();
  int r=mem_diff(static_cast<const S0&>(str0_).data(), static_cast<const S1&>(str1_).data(), min(size0, size1));
  return r>0 || (r==0 && size0>=size1);
}
//----

template<class S>
PFC_INLINE bool operator>=(const str_base<S> &str_, const char *cstr_)
{
  // test if base string is greater than or equal to c-string
  usize_t size0=static_cast<const S&>(str_).size();
  usize_t size1=str_size(cstr_);
  int r=mem_diff(static_cast<const S&>(str_).data(), cstr_, min(size0, size1));
  return r>0 || (r==0 && size0>=size1);
}
//----

template<class S>
PFC_INLINE bool operator>=(const char *cstr_, const str_base<S> &str_)
{
  // test if c-string is greater than or equal to base string
  usize_t size0=str_size(cstr_);
  usize_t size1=static_cast<const S&>(str_).size();
  int r=mem_diff(cstr_, static_cast<const S&>(str_).data(), min(size0, size1));
  return r>0 || (r==0 && size0>=size1);
}
//----

template<class S>
PFC_INLINE bool operator>=(const str_base<S> &str_, char c_)
{
  // test if base string is greater than or equal to char
  usize_t size0=static_cast<const S&>(str_).size();
  usize_t size1=c_?1:0;
  int r=(size0 && size1)?static_cast<const S&>(str_).front()-c_:0;
  return r>0 || (r==0 && size0>=size1);
}
//----

template<class S>
PFC_INLINE bool operator>=(char c_, const str_base<S> &str_)
{
  // test if char is greater than or equal to base string
  usize_t size0=c_?1:0;
  usize_t size1=static_cast<const S&>(str_).size();
  int r=(size0 && size1)?c_-static_cast<const S&>(str_).front():0;
  return r>0 || (r==0 && size0>=size1);
}
//----

template<class S>
bool replace_substr(str_base<S> &res_, const str_base<S> &src_, const char *replace_, const char *replacement_)
{
  // replace replace_ in string with replacemnet_
  PFC_ASSERT(&res_!=&src_);
  res_.clear();
  const char *start=src_.c_str();
  usize_t replace_size=str_size(replace_);
  while(const char *s=str_find_substr(start, replace_))
  {
    res_.push_back(start, usize_t(s-start));
    res_+=replacement_;
    start=s+replace_size;
  }
  if(start==src_.data())
    return false;
  res_+=start;
  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// const_pstr
//============================================================================
const_pstr::const_pstr()
  :m_size(0)
  ,m_data(0)
{
}
//----

const_pstr::const_pstr(const char *cstr_)
  :m_size(str_size(cstr_))
  ,m_data(cstr_)
{
}
//----

const_pstr::const_pstr(const char *str_, usize_t size_)
  :m_size(size_)
  ,m_data(str_)
{
}
//----

void const_pstr::init(const char *cstr_)
{
  m_size=str_size(cstr_);
  m_data=cstr_;
}
//----

void const_pstr::init(const char *str_, usize_t size_)
{
  m_size=size_;
  m_data=str_;
}
//----

void const_pstr::clear()
{
  m_size=0;
}
//----------------------------------------------------------------------------

usize_t const_pstr::size() const
{
  return m_size;
}
//----

usize_t const_pstr::capacity() const
{
  return m_size;
}
//----

const char &const_pstr::operator[](usize_t idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<m_size);
  return m_data[idx_];
}
//----

const char &const_pstr::front() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return *m_data;
}
//----

const char &const_pstr::back() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return m_data[m_size-1];
}
//----

const char *const_pstr::c_str() const
{
  PFC_ASSERT_PEDANTIC(m_data[m_size]==0);
  return m_data;
}
//----

const char *const_pstr::data() const
{
  return m_data;
}
//----------------------------------------------------------------------------


//============================================================================
// hash_func<const_pstr>
//============================================================================
template<>
struct hash_func<const_pstr>
{
  static PFC_INLINE unsigned index(const const_pstr &str_)
  {
    extern uint32_t crc32(const void*, usize_t num_bytes_, uint32_t seed_=0xffffffff);
    return crc32(str_.data(), str_.size());
  }
};
//----------------------------------------------------------------------------


//============================================================================
// pstr
//============================================================================
pstr::pstr()
  :m_size(0)
  ,m_capacity(0)
  ,m_data(0)
{
}
//----

pstr::pstr(const pstr &str_)
  :m_size(str_.m_size)
  ,m_capacity(str_.m_capacity)
  ,m_data(str_.m_data)
{
}
//----

pstr::pstr(char *cstr_)
  :m_size(str_size(cstr_))
  ,m_capacity(m_size)
  ,m_data(cstr_)
{
}
//----

pstr::pstr(char *str_, usize_t size_)
  :m_size(size_)
  ,m_capacity(size_)
  ,m_data(str_)
{
}
//----

pstr::pstr(char *str_, usize_t size_, usize_t capacity_)
  :m_size(size_)
  ,m_capacity(capacity_)
  ,m_data(str_)
{
}
//----

void pstr::init(char *cstr_)
{
  m_size=str_size(cstr_);
  m_capacity=m_size;
  m_data=cstr_;
}
//----

void pstr::init(char *str_, usize_t size_)
{
  m_size=size_;
  m_capacity=size_;
  m_data=str_;
}
//----

void pstr::init(char *str_, usize_t size_, usize_t capacity_)
{
  m_size=size_;
  m_capacity=capacity_;
  m_data=str_;
}
//----

void pstr::operator=(const pstr &str_)
{
  PFC_ASSERT(m_capacity<=str_.m_size);
  m_size=str_.m_size;
  mem_copy(m_data, str_.m_data, str_.m_size);
}
//----

template<class S>
void pstr::operator=(const str_base<S> &str_)
{
  usize_t new_size=str_.size();
  PFC_ASSERT(m_capacity<=new_size);
  m_size=new_size;
  mem_copy(m_data, str_.data(), new_size);
}
//----

void pstr::operator=(const char *cstr_)
{
  usize_t new_size=str_size(cstr_);
  PFC_ASSERT(m_capacity<=new_size);
  m_size=new_size;
  mem_copy(m_data, cstr_, new_size);
}
//----

void pstr::set(const char *str_, usize_t size_)
{
  PFC_ASSERT(size_<=m_capacity);
  m_size=size_;
  mem_copy(m_data, str_, size_);
}
//----

void pstr::clear()
{
  m_size=0;
}
//----

void pstr::resize(usize_t size_)
{
  PFC_ASSERT(size_<=m_capacity);
  m_size=size_;
}
//----------------------------------------------------------------------------

usize_t pstr::size() const
{
  return m_size;
}
//----

usize_t pstr::capacity() const
{
  return m_capacity;
}
//----

const char &pstr::operator[](usize_t idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<m_size);
  return m_data[idx_];
}
//----

char &pstr::operator[](usize_t idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<m_size);
  return m_data[idx_];
}
//----

const char &pstr::front() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return *m_data;
}
//----

char &pstr::front()
{
  PFC_ASSERT_PEDANTIC(m_size);
  return *m_data;
}
//----

const char &pstr::back() const
{
  PFC_ASSERT_PEDANTIC(m_size);
  return m_data[m_size-1];
}
//----

char &pstr::back()
{
  PFC_ASSERT_PEDANTIC(m_size);
  return m_data[m_size-1];
}
//----

const char *pstr::c_str() const
{
  PFC_ASSERT_PEDANTIC(m_size<m_capacity);
  m_data[m_size]=0;
  return m_data;
}
//----

char *pstr::c_str()
{
  PFC_ASSERT_PEDANTIC(m_size<m_capacity);
  m_data[m_size]=0;
  return m_data;
}
//----

const char *pstr::data() const
{
  return m_data;
}
//----

char *pstr::data()
{
  return m_data;
}
//----

template<class S>
void pstr::operator+=(const str_base<S> &str_)
{
  // append base string to the string
  usize_t size=static_cast<const S&>(str_).size();
  usize_t new_size=m_size+size;
  PFC_ASSERT(new_size<=m_capacity);
  mem_copy(m_data+m_size, str_.data(), size);
  m_size=new_size;
}
//----

void pstr::operator+=(const char *cstr_)
{
  // append c-string to the string
  usize_t size=str_size(cstr_);
  usize_t new_size=m_size+size;
  PFC_ASSERT(new_size<=m_capacity);
  mem_copy(m_data+m_size, cstr_, size);
  m_size=new_size;
}
//----

void pstr::operator+=(char c_)
{
  // append character to the string
  PFC_ASSERT_PEDANTIC(m_size<m_capacity);
  m_data[m_size++]=c_;
}
//----

void pstr::push_front(char c_)
{
  // prepend character to the string
  PFC_ASSERT(m_size<m_capacity);
  mem_move(m_data+1, m_data, m_size);
  *m_data=c_;
  ++m_size;
}
//----

void pstr::push_front(char c_, usize_t num_chars_)
{
  // prepend given number of characters to the string
  PFC_ASSERT(m_size+num_chars_<=m_capacity);
  mem_move(m_data+num_chars_, m_data, m_size);
  mem_set(m_data, c_, num_chars_);
  m_size+=num_chars_;
}
//----

void pstr::push_front(const char *cstr_)
{
  // prepend c-string to the string
  if(cstr_)
  {
    usize_t size=str_size(cstr_);
    push_front(cstr_, size);
  }
}
//----

void pstr::push_front(const char *str_, usize_t num_chars_)
{
  // prepend string of given size to the string
  PFC_ASSERT(str_ || !num_chars_);
  usize_t new_size=m_size+num_chars_;
  PFC_ASSERT(new_size<=m_capacity);
  mem_move(m_data+num_chars_, m_data, m_size);
  mem_copy(m_data, str_, num_chars_);
  m_size=new_size;
}
//----

void pstr::push_back(char c_)
{
  // append character to the string
  PFC_ASSERT_PEDANTIC(m_size<m_capacity);
  m_data[m_size++]=c_;
}
//----

void pstr::push_back(char c_, usize_t num_chars_)
{
  // append given number of characters to the string
  PFC_ASSERT(m_size+num_chars_<=m_capacity);
  mem_set(m_data+m_size, c_, num_chars_);
  m_size+=num_chars_;
}
//----

void pstr::push_back(const char *str_, usize_t num_chars_)
{
  // append string of given size to the string
  PFC_ASSERT(m_size+num_chars_<=m_capacity);
  mem_copy(m_data+m_size, str_, num_chars_);
  m_size+=num_chars_;
}
//----

void pstr::remove_front(usize_t num_chars_)
{
  // remove given number of characters from the beginning of the string
  PFC_ASSERT(m_size>=num_chars_);
  usize_t new_size=m_size-num_chars_;
  mem_move(m_data, m_data+num_chars_, new_size);
  m_size=new_size;
}
//----

void pstr::remove_back(usize_t num_chars_)
{
  // remove given number of characters from the end of the string
  PFC_ASSERT(m_size>=num_chars_);
  m_size-=num_chars_;
}
//----------------------------------------------------------------------------


//============================================================================
// hash_func<pstr>
//============================================================================
template<>
struct hash_func<pstr>
{
  static PFC_INLINE unsigned index(const pstr &str_)
  {
    extern uint32_t crc32(const void*, usize_t num_bytes_, uint32_t seed_=0xffffffff);
    return crc32(str_.data(), str_.size());
  }
};
//----------------------------------------------------------------------------
