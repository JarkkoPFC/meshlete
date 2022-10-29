//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "core/str.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// default_logging_func
//============================================================================
#ifdef PFC_COMPILER_MSVC
#include <iostream>
void pfc::default_logging_func(const char *str_, usize_t num_chars_)
{
  static bool is_debugger=IsDebuggerPresent()==TRUE;
  if(num_chars_!=usize_t(-1))
  {
    char buf[1024];
    while(num_chars_)
    {
      // copy characters to the buffer
      usize_t size=str_copy(buf, str_, min<usize_t>(num_chars_+1, sizeof(buf)));
      str_+=size;
      num_chars_-=size;

      // print buffer
      if(is_debugger)
        OutputDebugString(buf);
      else
        std::cout<<buf;
    }
  }
  else
  {
    if(is_debugger)
      OutputDebugString(str_);
    else
      std::cout<<str_;
  }
}
#elif defined(PFC_COMPILER_GCC)
void pfc::default_logging_func(const char *str_, usize_t num_chars_)
{
  if(num_chars_!=usize_t(-1))
  {
    char buf[1024];
    while(num_chars_)
    {
      // copy characters to the buffer
      usize_t size=str_copy(buf, str_, min<usize_t>(num_chars_+1, sizeof(buf)));
      str_+=size;
      num_chars_-=size;

      // print buffer
      std::cout<<buf;
    }
  }
  else
    std::cout<<str_;
}
#endif
//----------------------------------------------------------------------------


//============================================================================
// log/warn/error
//============================================================================
namespace
{
  enum {log_indention_size=2};
  void(*s_logf_func)(const char*, usize_t)=&default_logging_func;
  void(*s_warnf_func)(const char*, usize_t)=&default_logging_func;
  void(*s_errorf_func)(const char*, usize_t)=&default_logging_func;
//  mp_critical_section s_log_cs;
  volatile bool s_aborted=false;
  volatile unsigned s_log_indention=0;
  //----

  void va_log(void(*log_func_)(const char*, usize_t), const char *fmt_, va_list args_)
  {
    while(fmt_)
    {
      // find next formatting position and output preceding string
      const char *s=str_find(fmt_, '%');
      usize_t num_chars=s?usize_t(s-fmt_):usize_t(-1);
      if(num_chars)
        (*log_func_)(fmt_, num_chars);
      if(!s)
        break;

      // build formatting string
      bool terminate_format_str=false;
      char fmt_string[64];
      char *fmt_pos=fmt_string;
      *fmt_pos++='%';
      do
      {
        // check for format string overflow
        *fmt_pos++=*++s;
        if(fmt_pos==fmt_string+sizeof(fmt_string)-2)
        {
          *fmt_pos++=0;
          (*log_func_)(fmt_string, usize_t(-1));
          break;
        }

        switch(*s)
        {
          // unfinished string formatting
          case 0:
          {
            (*log_func_)(fmt_string, usize_t(-1));
            terminate_format_str=true;
            --s;
          } break;

          // integer value formatting
          case 'c': case 'd': case 'i': case 'u': case 'o': case 'x': case 'X':
          {
            char buf[64];
            int v=va_arg(args_, int);
            *fmt_pos++=0;
            PFC_SNPRINTF(buf, sizeof(buf), fmt_string, v);
            (*log_func_)(buf, usize_t(-1));
            terminate_format_str=true;
          } break;

          // floating point value formatting
          case 'f': case 'F': case 'e': case 'E': case 'g': case 'G':  case 'a': case 'A':
          {
            char buf[64];
            double v=va_arg(args_, double);
            *fmt_pos++=0;
            PFC_SNPRINTF(buf, sizeof(buf), fmt_string, v);
            (*log_func_)(buf, usize_t(-1));
            terminate_format_str=true;
          } break;

          // pointer formatting
          case 'p':
          {
            char buf[64];
            void *v=va_arg(args_, void*);
            *fmt_pos++=0;
            PFC_SNPRINTF(buf, sizeof(buf), fmt_string, v);
            (*log_func_)(buf, usize_t(-1));
            terminate_format_str=true;
          } break;

          // none or % formatting
          case 'n': case '%':
          {
            char buf[64];
            *fmt_pos++=0;
            PFC_SNPRINTF(buf, sizeof(buf), fmt_string, 0);
            (*log_func_)(buf, usize_t(-1));
            terminate_format_str=true;
          } break;

          // string formatting
          case 's':
          {
            char *v=va_arg(args_, char*);
            (*log_func_)(v, usize_t(-1));
            terminate_format_str=true;
          } break;
        }
      } while(!terminate_format_str);
      fmt_=s+1;
    }
  }
} // namespace <anonymous>
//----

void pfc::log(const char *str_)
{
  if(!s_aborted)
  {
//    s_log_cs.enter();
    (*s_logf_func)(str_, usize_t(-1));
//    s_log_cs.leave();
  }
}
//----

void pfc::logf(const char *fs_, ...)
{
  // write string to log window
  if(!s_aborted)
  {
//    s_log_cs.enter();
    va_list args;
    va_start(args, fs_);
    va_log(s_logf_func, fs_, args);
    va_end(args);
//    s_log_cs.leave();
  }
}
//----

void pfc::log_indention()
{
  if(!s_aborted)
  {
    // write indention with log function
    char str[64];
    unsigned indention=s_log_indention;
    indention=min(indention, unsigned((sizeof(str)-1)/log_indention_size));
    mem_set(str, ' ', indention*log_indention_size);
    str[indention*log_indention_size]=0;
//    s_log_cs.enter();
    (*s_logf_func)(str, indention*log_indention_size);
//    s_log_cs.leave();
  }
}
//----

void pfc::warn(const char *str_)
{
  if(!s_aborted)
  {
//    s_log_cs.enter();
    (*s_warnf_func)(str_, usize_t(-1));
//    s_log_cs.leave();
  }
}
//----

void pfc::warnf(const char *fs_, ...)
{
  // write string to warning window
  if(!s_aborted)
  {
//    s_log_cs.enter();
    va_list args;
    va_start(args, fs_);
    va_log(s_warnf_func, fs_, args);
    va_end(args);
//    s_log_cs.leave();
  }
}
//----

void pfc::warn_indention()
{
  if(!s_aborted)
  {
    // write indention with log function
    char str[64];
    unsigned indention=s_log_indention;
    indention=min(indention, unsigned((sizeof(str)-1)/log_indention_size));
    mem_set(str, ' ', indention*log_indention_size);
    str[indention*log_indention_size]=0;
//    s_log_cs.enter();
    (*s_warnf_func)(str, indention*log_indention_size);
//    s_log_cs.leave();
  }
}
//----

void pfc::error(const char *str_)
{
  if(!s_aborted)
  {
//    s_log_cs.enter();
    (*s_errorf_func)(str_, usize_t(-1));
//    s_log_cs.leave();
  }
}
//----

void pfc::errorf(const char *fs_, ...)
{
  // write string to error window
  if(!s_aborted)
  {
//    s_log_cs.enter();
    va_list args;
    va_start(args, fs_);
    va_log(s_errorf_func, fs_, args);
    va_end(args);
//    s_log_cs.leave();
  }
}
//----

void pfc::error_indention()
{
  if(!s_aborted)
  {
    // write indention with log function
    char str[64];
    unsigned indention=s_log_indention;
    indention=min(indention, unsigned((sizeof(str)-1)/log_indention_size));
    mem_set(str, ' ', indention*log_indention_size);
    str[indention*log_indention_size]=0;
//    s_log_cs.enter();
    (*s_errorf_func)(str, indention*log_indention_size);
//    s_log_cs.leave();
  }
}
//----

void pfc::set_logging_funcs(void(*logf_)(const char*, usize_t), void(*warnf_)(const char*, usize_t), void(*errorf_)(const char*, usize_t))
{
  // setup logging functions
  s_logf_func=logf_?logf_:&default_logging_func;
  s_warnf_func=warnf_?warnf_:&default_logging_func;
  s_errorf_func=errorf_?errorf_:&default_logging_func;
}
//----

void pfc::indent_log()
{
  ++s_log_indention;
//  atom_inc(s_log_indention);
}
//----

void pfc::unindent_log()
{
//  unsigned old_indention=atom_dec(s_log_indention);
  unsigned old_indention=s_log_indention--;
  PFC_ASSERT(int(old_indention)>=0);
}
//----------------------------------------------------------------------------

namespace
{
  bool default_preabort_func()
  {
    return true;
  }
  //----

  bool(*s_preabort_func)()=&default_preabort_func;
} // namespace anonymous
//----

bool pfc::preabort()
{
  if(!s_aborted)
  {
//    s_log_cs.enter();
    s_aborted=(*s_preabort_func)();
//    s_log_cs.leave();
  }
  return s_aborted;
}
//----

void pfc::set_preabort_func(bool(*preabort_)())
{
  s_preabort_func=preabort_?preabort_:&default_preabort_func;
}
//----------------------------------------------------------------------------


//============================================================================
// memory tracking
//============================================================================
namespace pfc
{
#ifdef PFC_BUILDOP_MEMORY_TRACKING
//  static mp_critical_section s_memory_info_list_csect;
  memory_info memory_info::s_head={0, 0, &s_head, &s_head};
  PFC_THREAD_VAR const char *memory_stack_entry::s_stack[max_memory_stack_depth]={0};
  PFC_THREAD_VAR unsigned memory_stack_entry::s_stack_depth=PFC_MEM_TRACK_STACK_DEPTH;
  //----

  void add_memory_info(memory_info &info_)
  {
    // add memory info block to the block list
//    s_memory_info_list_csect.enter();
    info_.next=&memory_info::s_head;
    info_.prev=memory_info::s_head.prev;
    memory_info::s_head.prev->next=&info_;
    memory_info::s_head.prev=&info_;
//    s_memory_info_list_csect.leave();
    ++memory_info::s_head.num_items;
//    atom_inc(memory_info::s_head.num_items);

#if PFC_MEM_TRACK_STACK_DEPTH>0
    // save memory allocation stack
    mem_copy(info_.stack, memory_stack_entry::s_stack+memory_stack_entry::s_stack_depth-PFC_MEM_TRACK_STACK_DEPTH, sizeof(info_.stack));
#endif
  }
  //----

  void remove_memory_info(memory_info &info_)
  {
    // remove memory info block from the block list
//    s_memory_info_list_csect.enter();
    info_.prev->next=info_.next;
    info_.next->prev=info_.prev;
//    s_memory_info_list_csect.leave();
    --memory_info::s_head.num_items;
//    atom_dec(memory_info::s_head.num_items);
  }
#endif
} // namespace pfc
//----------------------------------------------------------------------------

class memory_log_allocator: public memory_allocator_base
{
public:
  virtual void check_allocator(usize_t num_bytes_, usize_t mem_align_) {}
  virtual void *alloc(usize_t num_bytes_, usize_t mem_align_=memory_align) {return PFC_ALIGNED_MALLOC(num_bytes_, mem_align_);}
  virtual void free(void *data_) {PFC_ALIGNED_FREE(data_);}
};
//----

void pfc::log_allocated_memory()
{
#ifdef PFC_BUILDOP_MEMORY_TRACKING
  // iterate through all allocated memory blocks
  // note: must ensure we don't perform any memory tracked allocations here, thus using custom allocator for memory logs
  memory_log_allocator alloc;
  heap_str mem_log(&alloc);
  memory_info *info=memory_info::s_head.next;
  bool is_first=true;
  if(info!=&memory_info::s_head)
  {
    mem_log+="============================================================================\r\n";
    mem_log.push_back_format("Allocated memory blocks (%i):\r\n", memory_info::s_head.num_items);
    mem_log+="----------------------------------------------------------------------------\r\n";
    do
    {
      // log the number of allocated bytes/objects and allocation site
      const uint8_t *data=((const uint8_t*)info)+memory_info_size;
      if(!is_first)
        mem_log+="\r\n";
      const alloc_site_info *sinfo=info->site_info;
      if(sinfo)
        mem_log.push_back_format("[0x%08x] %i %s: %s (%i) - %s\r\n", data, info->num_items&(~memory_flag_typeless), info->num_items&memory_flag_typeless?"bytes":"objects", sinfo->filename, sinfo->line, sinfo->funcname);
      else
        mem_log.push_back_format("[0x%08x] %i %s: <unknown allocation site>\r\n", data, info->num_items&(~memory_flag_typeless), info->num_items&memory_flag_typeless?"bytes":"objects");

      // log memory block data
      stack_str32 data_str;
      for(unsigned i=0; i<16; ++i)
        data_str+=data[i]>=32?data[i]:' ';
      mem_log.push_back_format("  Data: <%s> ", data_str.c_str());
      for(unsigned i=0; i<16; ++i)
        mem_log.push_back_format("%02x ", data[i]);
      mem_log+="\r\n";

#if defined(PFC_BUILDOP_MEMORY_TRACKING) && PFC_MEM_TRACK_STACK_DEPTH>0
      // log the call stack
      for(unsigned i=0; i<PFC_MEM_TRACK_STACK_DEPTH; ++i)
      {
        const char *stack_entry=info->stack[PFC_MEM_TRACK_STACK_DEPTH-1-i];
        if(stack_entry)
          mem_log.push_back_format("  %s\r\n", stack_entry);
      }
#endif

      // proceed to the next allocation
      info=info->next;
      is_first=false;
    } while(info!=&memory_info::s_head);
    log(mem_log.c_str());
    log("----------------------------------------------------------------------------\r\n");
  }
#else
  log("Memory tracking not enabled.\r\n");
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// default_memory_allocator
//============================================================================
void default_memory_allocator::check_allocator(usize_t num_bytes_, usize_t mem_align_)
{
  PFC_CHECK_MSG(mem_align_ && mem_align_<=memory_align && (mem_align_&(mem_align_-1))==0,
                ("default_memory_allocator memory alignment must be power-of-2 and in range [1, %u] (requesting %u byte alignment)\r\n", memory_align, mem_align_));
}
//----------------------------------------------------------------------------

void *default_memory_allocator::alloc(usize_t num_bytes_, usize_t mem_align_)
{
  PFC_ASSERT_PEDANTIC_MSG(mem_align_ && mem_align_<=memory_align && (mem_align_&(mem_align_-1))==0,
                          ("default_memory_allocator memory alignment must be power-of-2 and in range [1, %u] (requesting %u byte alignment)\r\n", memory_align, mem_align_));
  return PFC_MEM_ALLOC(num_bytes_);
}
//----

void default_memory_allocator::free(void *p_)
{
  PFC_MEM_FREE(p_);
}
//----------------------------------------------------------------------------

default_memory_allocator::default_memory_allocator()
{
}
//----

default_memory_allocator::~default_memory_allocator()
{
}
//----------------------------------------------------------------------------
