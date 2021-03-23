//============================================================================
// Software Rasterizer Library
//
// Copyright (c) 2021, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#include "rasterizer/rasterizer_tex.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_texture
//============================================================================
rasterizer_texture::rasterizer_texture()
{
  m_header=0;
}
//----

rasterizer_texture::rasterizer_texture(const void *ptx_file_)
{
  m_header=0;
  init(ptx_file_);
}
//----

void rasterizer_texture::init(const void *ptx_file_)
{
  // check for proper P3G file data
  PFC_ASSERT(ptx_file_);
  PFC_ASSERT_MSG((((usize_t)ptx_file_)&0x3)==0, ("PTX data is not properly aligned to 4-byte boundary\r\n"));
  PFC_ASSERT_MSG(*(uint32_t*)ptx_file_==0x78657470, ("Invalid PTX file signature\r\n"));
//  PFC_ASSERT_MSG(((const ptx_header*)ptx_file_)->file_ver==ptx_file_ver, ("PTX file %s mismatches PTX code %s\r\n", bcd16_version_str(((const ptx_header*)ptx_file_)->file_ver).str, bcd16_version_str(ptx_file_ver).str));

  // setup members
  m_header=(const ptx_header*)ptx_file_;
}
//----------------------------------------------------------------------------
