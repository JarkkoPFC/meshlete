//============================================================================
// Software Rasterizer Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_RASTERIZER_TEX_H
#define PFC_RASTERIZER_TEX_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core/core.h"
#include <math.h>
namespace pfc
{

// new
enum {ptx_file_ver=0x1000};
//----------------------------------------------------------------------------


//============================================================================
// e_ptx_type
//============================================================================
enum e_ptx_type
{
  ptxtype_none    =0x00,
  ptxtype_2d      =0x01,
  ptxtype_3d      =0x02,
  ptxtype_cube    =0x03,
  ptxtype_array2d =0x04
};
//----------------------------------------------------------------------------


//============================================================================
// e_ptx_format
//============================================================================
enum e_ptx_format
{
  ptxfmt_none          =0x00,
  // <8bpc formats
  ptxfmt_r3g3b2,
  ptxfmt_r5g6b5,
  ptxfmt_b5g6r5,
  ptxfmt_r5g5b5a1,
  ptxfmt_r4g4b4a4,
  // 8bpc formats
  ptxfmt_r8,
  ptxfmt_r8g8,
  ptxfmt_r8g8b8,
  ptxfmt_r8g8b8a8,
  // 10-11bpc formats
  ptxfmt_r11g11b10,
  ptxfmt_r11g11b10f,
  ptxfmt_r10g10b10a2,
  ptxfmt_r10g10b10a2f,
  // 16bpc formats
  ptxfmt_r16,
  ptxfmt_r16f,
  ptxfmt_r16g16,
  ptxfmt_r16g16f,
  ptxfmt_r16g16b16,
  ptxfmt_r16g16b16f,
  ptxfmt_r16g16b16a16,
  ptxfmt_r16g16b16a16f,
  // 32bpc formats
  ptxfmt_r32,
  ptxfmt_r32f,
  ptxfmt_r32g32,
  ptxfmt_r32g32f,
  ptxfmt_r32g32b32,
  ptxfmt_r32g32b32f,
  ptxfmt_r32g32b32a32,
  ptxfmt_r32g32b32a32f,
  // BC formats
  ptxfmt_bc1,
  ptxfmt_bc2,
  ptxfmt_bc3,
  ptxfmt_bc4,
  ptxfmt_bc5,
  ptxfmt_bc6h,
  ptxfmt_bc7,
};
//----

template<e_ptx_format> struct ptx_format;
//----------------------------------------------------------------------------


//============================================================================
// e_ptx_layout
//============================================================================
enum e_ptx_layout
{
  ptxlayout_linear =0x00,
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_texture
//============================================================================
class rasterizer_texture
{
public:
  // construction
  rasterizer_texture();
  rasterizer_texture(const void *ptx_file_);
  void init(const void *ptx_file_);
  PFC_INLINE bool is_valid() const;
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE e_ptx_type type() const;
  PFC_INLINE e_ptx_format format() const;
  PFC_INLINE e_ptx_layout layout() const;
  PFC_INLINE uint8_t num_lods() const;
  PFC_INLINE uint16_t width() const;
  PFC_INLINE uint16_t height() const;
  PFC_INLINE uint16_t depth() const;
  PFC_INLINE const void *data() const;
  //--------------------------------------------------------------------------

private:
  rasterizer_texture(const rasterizer_texture&); // not implemented
  void operator=(const rasterizer_texture&); // not implemented
  //--------------------------------------------------------------------------

  //==========================================================================
  // ptx_header
  //==========================================================================
  struct ptx_header
  {
    char file_sig[4];
    uint16_t file_ver;
    uint16_t flags;
    uint32_t fsize;
    uint8_t type;
    uint8_t format;
    uint8_t layout;
    uint8_t num_lods;
    uint16_t width;
    uint16_t height;
    uint16_t depth;
    uint16_t reserved[5];
    uint8_t data[1];
  };
  //--------------------------------------------------------------------------

  const ptx_header *m_header;
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_sampler2d
//============================================================================
template<e_ptx_format src_fmt>
class rasterizer_sampler2d
{
public:
  // construction
  rasterizer_sampler2d();
  rasterizer_sampler2d(const rasterizer_texture&);
  void init(const rasterizer_texture&);
  //--------------------------------------------------------------------------

  // sampling
  template<e_ptx_format dst_fmt> void load(ptx_format<dst_fmt>&, uint16_t u_, uint16_t v_);
  template<e_ptx_format dst_fmt> void sample_point(ptx_format<dst_fmt>&, float u_, float v_);
  //--------------------------------------------------------------------------

private:
  const rasterizer_texture *m_tex;
};
//----------------------------------------------------------------------------




//============================================================================
//============================================================================
// inline & template implementations
//============================================================================
//============================================================================
//----------------------------------------------------------------------------


//============================================================================
// ptx_format
//============================================================================
template<>
struct ptx_format<ptxfmt_r3g3b2>
{
  enum {rsize=3, gsize=3, bsize=2, asize=0};
  PFC_INLINE uint8_t get_r() const {return uint8_t(r<<5);}
  PFC_INLINE uint8_t get_g() const {return uint8_t(g<<5);}
  PFC_INLINE uint8_t get_b() const {return uint8_t(b<<6);}
  PFC_INLINE uint8_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t)              {r=r_>>5; g=g_>>5; b=b_>>6;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t)          {r=r_>>13; g=g_>>13; b=b_>>14;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t)          {r=r_>>29; g=g_>>29; b=b_>>30;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t)      {r=uint8_t(r_*7.99f); g=uint8_t(g_*7.99f); b=uint8_t(b_*3.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), 0);}
  //--------------------------------------------------------------------------

  uint8_t r:3, g:3, b:2;
};
//----

template<>
struct ptx_format<ptxfmt_r5g6b5>
{
  enum {rsize=5, gsize=6, bsize=5, asize=0};
  PFC_INLINE uint8_t get_r() const {return uint8_t(r<<3);}
  PFC_INLINE uint8_t get_g() const {return uint8_t(g<<2);}
  PFC_INLINE uint8_t get_b() const {return uint8_t(b<<3);}
  PFC_INLINE uint8_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t)              {r=r_>>3; g=g_>>2; b=b_>>3;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t)          {r=r_>>11; g=g_>>10; b=b_>>11;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t)          {r=r_>>27; g=g_>>26; b=b_>>27;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t)      {r=uint8_t(r_*31.99f); g=uint8_t(g_*63.99f); b=uint8_t(b_*31.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), 0);}
  //--------------------------------------------------------------------------

  uint16_t r:5, g:6, b:5;
};
//----

template<>
struct ptx_format<ptxfmt_b5g6r5>
{
  enum {rsize=5, gsize=6, bsize=5, asize=0};
  PFC_INLINE uint8_t get_r() const {return uint8_t(r<<3);}
  PFC_INLINE uint8_t get_g() const {return uint8_t(g<<2);}
  PFC_INLINE uint8_t get_b() const {return uint8_t(b<<3);}
  PFC_INLINE uint8_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t)              {r=r_>>3; g=g_>>2; b=b_>>3;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t)          {r=r_>>11; g=g_>>10; b=b_>>11;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t)          {r=r_>>27; g=g_>>26; b=b_>>27;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t)      {r=uint8_t(r_*31.99f); g=uint8_t(g_*63.99f); b=uint8_t(b_*31.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), 0);}
  //--------------------------------------------------------------------------

  uint16_t b:5, g:6, r:5;
};
//----

template<>
struct ptx_format<ptxfmt_r5g5b5a1>
{
  enum {rsize=5, gsize=5, bsize=5, asize=1};
  PFC_INLINE uint8_t get_r() const {return uint8_t(r<<3);}
  PFC_INLINE uint8_t get_g() const {return uint8_t(g<<3);}
  PFC_INLINE uint8_t get_b() const {return uint8_t(b<<3);}
  PFC_INLINE uint8_t get_a() const {return uint8_t(a<<7);}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_)           {r=r_>>3; g=g_>>2; b=b_>>3; a=a_>>7;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t a_)       {r=r_>>11; g=g_>>10; b=b_>>11; a=a_>>15;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t a_)       {r=r_>>27; g=g_>>27; b=b_>>27; a=a_>>31;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t a_)   {r=uint8_t(r_*31.99f); g=uint8_t(g_*31.99f); b=uint8_t(b_*31.99f); a=a_>=0.5f;}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), px_.get_a());}
  //--------------------------------------------------------------------------

  uint16_t r:5, g:5, b:5, a:1;
};
//----

template<>
struct ptx_format<ptxfmt_r4g4b4a4>
{
  enum {rsize=4, gsize=4, bsize=4, asize=4};
  PFC_INLINE uint8_t get_r() const {return uint8_t(r<<4);}
  PFC_INLINE uint8_t get_g() const {return uint8_t(g<<4);}
  PFC_INLINE uint8_t get_b() const {return uint8_t(b<<4);}
  PFC_INLINE uint8_t get_a() const {return uint8_t(a<<4);}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_)           {r=r_>>4; g=g_>>4; b=b_>>4; a=a_>>4;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t a_)       {r=r_>>12; g=g_>>12; b=b_>>12; a=a_>>12;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t a_)       {r=r_>>28; g=g_>>28; b=b_>>28; a=a_>>28;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t a_)   {r=uint8_t(r_*15.99f); g=uint8_t(g_*15.99f); b=uint8_t(b_*15.99f); a=uint8_t(a_*15.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), px_.get_a());}
  //--------------------------------------------------------------------------

  uint16_t r:4, g:4, b:4, a:4;
};
//----

template<>
struct ptx_format<ptxfmt_r8>
{
  enum {rsize=8, gsize=0, bsize=0, asize=0};
  PFC_INLINE uint8_t get_g() const {return 0;}
  PFC_INLINE uint8_t get_r() const {return r;}
  PFC_INLINE uint8_t get_b() const {return 0;}
  PFC_INLINE uint8_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t, uint8_t, uint8_t)                    {r=r_;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t, uint16_t, uint16_t)                {r=r_>>8;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t, uint32_t, uint32_t)                {r=r_>>24;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t, float32_t, float32_t)            {r=uint8_t(r_*255.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), 0, 0, 0);}
  //--------------------------------------------------------------------------

  uint8_t r;
};
//----

template<>
struct ptx_format<ptxfmt_r8g8>
{
  enum {rsize=8, gsize=8, bsize=0, asize=0};
  PFC_INLINE uint8_t get_r() const {return r;}
  PFC_INLINE uint8_t get_g() const {return g;}
  PFC_INLINE uint8_t get_b() const {return 0;}
  PFC_INLINE uint8_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t, uint8_t)                 {r=r_; g=g_;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t, uint16_t)             {r=r_>>8; g=g_>>8;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t, uint32_t)             {r=r_>>24; g=g_>>24;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t, float32_t)         {r=uint8_t(r_*255.99f); g=uint8_t(g_*255.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), 0, 0);}
  //--------------------------------------------------------------------------

  uint8_t r, g;
};
//----

template<>
struct ptx_format<ptxfmt_r8g8b8>
{
  enum {rsize=8, gsize=8, bsize=8, asize=0};
  PFC_INLINE uint8_t get_r() const {return r;}
  PFC_INLINE uint8_t get_g() const {return g;}
  PFC_INLINE uint8_t get_b() const {return b;}
  PFC_INLINE uint8_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t)              {r=r_; g=g_; b=b_;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t)          {r=r_>>8; g=g_>>8; b=b_>>8;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t)          {r=r_>>24; g=g_>>24; b=b_>>24;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t)      {r=uint8_t(r_*255.99f); g=uint8_t(g_*255.99f); b=uint8_t(b_*255.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), 0);}
  //--------------------------------------------------------------------------

  uint8_t r, g, b;
};
//----

template<>
struct ptx_format<ptxfmt_r8g8b8a8>
{
  enum {rsize=8, gsize=8, bsize=8, asize=8};
  PFC_INLINE uint8_t get_r() const {return r;}
  PFC_INLINE uint8_t get_g() const {return g;}
  PFC_INLINE uint8_t get_b() const {return b;}
  PFC_INLINE uint8_t get_a() const {return a;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_)           {r=r_; g=g_; b=b_; a=a_;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t a_)       {r=r_>>8; g=g_>>8; b=b_>>8; a=a_>>8;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t a_)       {r=r_>>24; g=g_>>24; b=b_>>24; a=a_>>24;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t a_)   {r=uint8_t(r_*255.99f); g=uint8_t(g_*255.99f); b=uint8_t(b_*255.99f); a=uint8_t(a_*255.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), px_.get_a());}
  //--------------------------------------------------------------------------

  uint8_t r, g, b, a;
};
//----

template<>
struct ptx_format<ptxfmt_r11g11b10>
{
  enum {rsize=11, gsize=11, bsize=10, asize=0};
  PFC_INLINE uint16_t get_r() const {return uint16_t(r<<5);}
  PFC_INLINE uint16_t get_g() const {return uint16_t(g<<5);}
  PFC_INLINE uint16_t get_b() const {return uint16_t(b<<6);}
  PFC_INLINE uint16_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t)              {r=r_<<3; g=g_<<3; b=b_<<2;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t)          {r=r_>>5; g=g_>>5; b=b_>>6;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t)          {r=r_>>21; g=g_>>21; b=b_>>22;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t)      {r=uint16_t(r_*2047.99f); g=uint16_t(g_*2047.99f); b=uint16_t(b_*1023.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), 0);}
  //--------------------------------------------------------------------------

  uint32_t r:11, g:11, b:10;
};
//----

template<>
struct ptx_format<ptxfmt_r11g11b10f>
{
  enum {rsize=11, gsize=11, bsize=10, asize=0};
  PFC_INLINE uint16_t get_r() const {return uint16_t(r);}
  PFC_INLINE uint16_t get_g() const {return uint16_t(g);}
  PFC_INLINE uint16_t get_b() const {return uint16_t(b);}
  PFC_INLINE uint16_t get_a() const {return 0;}
  //--------------------------------------------------------------------------

  uint32_t r:11, g:11, b:10;
};
//----

template<>
struct ptx_format<ptxfmt_r10g10b10a2>
{
  enum {rsize=10, gsize=10, bsize=10, asize=2};
  PFC_INLINE uint16_t get_r() const {return uint16_t(r<<6);}
  PFC_INLINE uint16_t get_g() const {return uint16_t(g<<6);}
  PFC_INLINE uint16_t get_b() const {return uint16_t(b<<6);}
  PFC_INLINE uint16_t get_a() const {return uint16_t(a<<14);}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_)           {r=r_<<2; g=g_<<2; b=b_<<2; a=a_>>6;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t a_)       {r=r_>>6; g=g_>>6; b=b_>>6; a=a_>>14;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t a_)       {r=r_>>22; g=g_>>22; b=b_>>22; a=a_>>30;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t a_)   {r=uint16_t(r_*1023.99f); g=uint16_t(g_*1023.99f); b=uint16_t(b_*1023.99f); a=uint8_t(a_*3.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), px_.get_a());}
  //--------------------------------------------------------------------------

  uint32_t r:10, g:10, b:10, a:2;
};
//----

template<>
struct ptx_format<ptxfmt_r10g10b10a2f>
{
  enum {rsize=10, gsize=10, bsize=10, asize=2};
  PFC_INLINE uint16_t get_r() const {return uint16_t(r);}
  PFC_INLINE uint16_t get_g() const {return uint16_t(g);}
  PFC_INLINE uint16_t get_b() const {return uint16_t(b);}
  PFC_INLINE uint16_t get_a() const {return uint16_t(a);}
  //--------------------------------------------------------------------------

  uint32_t r:10, g:10, b:10, a:2;
};
//----

template<>
struct ptx_format<ptxfmt_r16>
{
  enum {rsize=16, gsize=0, bsize=0, asize=0};
  PFC_INLINE uint16_t get_r() const {return r;}
  PFC_INLINE uint16_t get_g() const {return 0;}
  PFC_INLINE uint16_t get_b() const {return 0;}
  PFC_INLINE uint16_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t, uint8_t, uint8_t)                    {r=r_<<8;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t, uint16_t, uint16_t)                {r=r_;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t, uint32_t, uint32_t)                {r=r_>>16;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t, float32_t, float32_t)            {r=uint16_t(r_*65535.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), 0, 0, 0);}
  //--------------------------------------------------------------------------

  uint16_t r;
};
//----

template<>
struct ptx_format<ptxfmt_r16f>
{
  enum {rsize=16, gsize=0, bsize=0, asize=0};
  PFC_INLINE float16_t get_r() const {return r;}
  PFC_INLINE float16_t get_g() const {return 0;}
  PFC_INLINE float16_t get_b() const {return 0;}
  PFC_INLINE float16_t get_a() const {return 0;}
  //--------------------------------------------------------------------------

  float16_t r;
};
//----

template<>
struct ptx_format<ptxfmt_r16g16>
{
  enum {rsize=16, gsize=16, bsize=0, asize=0};
  PFC_INLINE uint16_t get_r() const {return r;}
  PFC_INLINE uint16_t get_g() const {return g;}
  PFC_INLINE uint16_t get_b() const {return 0;}
  PFC_INLINE uint16_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t, uint8_t)                 {r=r_<<8; g=g_<<8;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t, uint16_t)             {r=r_; g=g_;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t, uint32_t)             {r=r_>>16; g=g_>>16;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t, float32_t)         {r=uint16_t(r_*65535.99f); g=uint16_t(g_*65535.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), 0, 0);}
  //--------------------------------------------------------------------------

  uint16_t r, g;
};
//----

template<>
struct ptx_format<ptxfmt_r16g16f>
{
  enum {rsize=16, gsize=16, bsize=0, asize=0};
  PFC_INLINE float16_t get_r() const {return r;}
  PFC_INLINE float16_t get_g() const {return g;}
  PFC_INLINE float16_t get_b() const {return 0;}
  PFC_INLINE float16_t get_a() const {return 0;}
  //--------------------------------------------------------------------------

  float16_t r, g;
};
//----

template<>
struct ptx_format<ptxfmt_r16g16b16>
{
  enum {rsize=16, gsize=16, bsize=16, asize=0};
  PFC_INLINE uint16_t get_r() const {return r;}
  PFC_INLINE uint16_t get_g() const {return g;}
  PFC_INLINE uint16_t get_b() const {return b;}
  PFC_INLINE uint16_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t)              {r=r_<<8; g=g_<<8; b=b_<<8;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t)          {r=r_; g=g_; b=b_;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t)          {r=r_>>16; g=g_>>16; b=b_>>16;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t)      {r=uint16_t(r_*65535.99f); g=uint16_t(g_*65535.99f); b=uint16_t(b_*65535.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), 0);}
  //--------------------------------------------------------------------------

  uint16_t r, g, b;
};
//----

template<>
struct ptx_format<ptxfmt_r16g16b16f>
{
  enum {rsize=16, gsize=16, bsize=16, asize=0};
  PFC_INLINE float16_t get_r() const {return r;}
  PFC_INLINE float16_t get_g() const {return g;}
  PFC_INLINE float16_t get_b() const {return b;}
  PFC_INLINE float16_t get_a() const {return 0;}
  //--------------------------------------------------------------------------

  float16_t r, g, b;
};
//----

template<>
struct ptx_format<ptxfmt_r16g16b16a16>
{
  enum {rsize=16, gsize=16, bsize=16, asize=16};
  PFC_INLINE uint16_t get_r() const {return r;}
  PFC_INLINE uint16_t get_g() const {return g;}
  PFC_INLINE uint16_t get_b() const {return b;}
  PFC_INLINE uint16_t get_a() const {return a;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_)           {r=r_<<8; g=g_<<8; b=b_<<8; a=a_<<8;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t a_)       {r=r_; g=g_; b=b_; a=a_;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t a_)       {r=r_>>16; g=g_>>16; b=b_>>16; a=a_>>16;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t a_)   {r=uint16_t(r_*65535.99f); g=uint16_t(g_*65535.99f); b=uint16_t(b_*65535.99f); a=uint16_t(a_*65535.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), px_.get_a());}
  //--------------------------------------------------------------------------

  uint16_t r, g, b, a;
};
//----

template<>
struct ptx_format<ptxfmt_r16g16b16a16f>
{
  enum {rsize=16, gsize=16, bsize=16, asize=16};
  PFC_INLINE float16_t get_r() const {return r;}
  PFC_INLINE float16_t get_g() const {return g;}
  PFC_INLINE float16_t get_b() const {return b;}
  PFC_INLINE float16_t get_a() const {return a;}
  //--------------------------------------------------------------------------

  float16_t r, g, b, a;
};
//----

template<>
struct ptx_format<ptxfmt_r32>
{
  enum {rsize=32, gsize=0, bsize=0, asize=0};
  PFC_INLINE uint32_t get_r() const {return r;}
  PFC_INLINE uint32_t get_g() const {return 0;}
  PFC_INLINE uint32_t get_b() const {return 0;}
  PFC_INLINE uint32_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t, uint8_t, uint8_t)                    {r=r_<<24;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t, uint16_t, uint16_t)                {r=r_<<16;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t, uint32_t, uint32_t)                {r=r_;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t, float32_t, float32_t)            {r=uint32_t(r_*42949672965.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), 0, 0, 0);}
  //--------------------------------------------------------------------------

  uint32_t r;
};
//----

template<>
struct ptx_format<ptxfmt_r32f>
{
  enum {rsize=32, gsize=0, bsize=0, asize=0};
  PFC_INLINE float32_t get_r() const {return r;}
  PFC_INLINE float32_t get_g() const {return 0;}
  PFC_INLINE float32_t get_b() const {return 0;}
  PFC_INLINE float32_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t, uint8_t, uint8_t)                    {r=r_/255.0f;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t, uint16_t, uint16_t)                {r=r_/65535.0f;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t, uint32_t, uint32_t)                {r=r_/42949672965.0f;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t, float32_t, float32_t)            {r=r_;}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), 0, 0, 0);}
  //--------------------------------------------------------------------------

  float32_t r;
};
//----

template<>
struct ptx_format<ptxfmt_r32g32>
{
  enum {rsize=32, gsize=32, bsize=0, asize=0};
  PFC_INLINE uint32_t get_r() const {return r;}
  PFC_INLINE uint32_t get_g() const {return g;}
  PFC_INLINE uint32_t get_b() const {return 0;}
  PFC_INLINE uint32_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t, uint8_t)                 {r=r_<<24; g=g_<<24;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t, uint16_t)             {r=r_<<16; g=g_<<16;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t, uint32_t)             {r=r_; g=g_;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t, float32_t)         {r=uint32_t(r_*42949672965.99f); g=uint32_t(g_*42949672965.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), 0, 0);}
  //--------------------------------------------------------------------------

  uint32_t r, g;
};
//----

template<>
struct ptx_format<ptxfmt_r32g32f>
{
  enum {rsize=32, gsize=32, bsize=0, asize=0};
  PFC_INLINE float32_t get_r() const {return r;}
  PFC_INLINE float32_t get_g() const {return g;}
  PFC_INLINE float32_t get_b() const {return 0;}
  PFC_INLINE float32_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t, uint8_t)                 {r=r_/255.0f; g=g_/255.0f;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t, uint16_t)             {r=r_/65535.0f; g=g_/65535.0f;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t, uint32_t)             {r=r_/42949672965.0f; g=g_/42949672965.0f;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t, float32_t)         {r=r_; g=g_;}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), 0, 0);}
  //--------------------------------------------------------------------------

  float32_t r, g;
};
//----

template<>
struct ptx_format<ptxfmt_r32g32b32>
{
  enum {rsize=32, gsize=32, bsize=32, asize=0};
  PFC_INLINE uint32_t get_r() const {return r;}
  PFC_INLINE uint32_t get_g() const {return g;}
  PFC_INLINE uint32_t get_b() const {return b;}
  PFC_INLINE uint32_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t)              {r=r_<<24; g=g_<<24; b=b_<<24;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t)          {r=r_<<16; g=g_<<16; b=b_<<16;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t)          {r=r_; g=g_; b=b_;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t)      {r=uint32_t(r_*42949672965.99f); g=uint32_t(g_*42949672965.99f); b=uint32_t(b_*42949672965.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), 0);}
  //--------------------------------------------------------------------------

  uint32_t r, g, b;
};
//----

template<>
struct ptx_format<ptxfmt_r32g32b32f>
{
  enum {rsize=32, gsize=32, bsize=32, asize=0};
  PFC_INLINE float32_t get_r() const {return r;}
  PFC_INLINE float32_t get_g() const {return g;}
  PFC_INLINE float32_t get_b() const {return b;}
  PFC_INLINE float32_t get_a() const {return 0;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t)              {r=r_/255.0f; g=g_/255.0f; b=b_/255.0f;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t)          {r=r_/65535.0f; g=g_/65535.0f; b=b_/65535.0f;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t)          {r=r_/42949672965.0f; g=g_/42949672965.0f; b=b_/42949672965.0f;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t)      {r=r_; g=g_; b=b_;}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), 0);}
  //--------------------------------------------------------------------------

  float32_t r, g, b;
};
//----

template<>
struct ptx_format<ptxfmt_r32g32b32a32>
{
  enum {rsize=32, gsize=32, bsize=32, asize=32};
  PFC_INLINE uint32_t get_r() const {return r;}
  PFC_INLINE uint32_t get_g() const {return g;}
  PFC_INLINE uint32_t get_b() const {return b;}
  PFC_INLINE uint32_t get_a() const {return a;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_)           {r=r_<<24; g=g_<<24; b=b_<<24; a=a_<<24;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t a_)       {r=r_<<16; g=g_<<16; b=b_<<16; a=a_<<16;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t a_)       {r=r_; g=g_; b=b_; a=a_;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t a_)   {r=uint32_t(r_*42949672965.99f); g=uint32_t(g_*42949672965.99f); b=uint32_t(b_*42949672965.99f); a=uint32_t(a_*42949672965.99f);}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), px_.get_a());}
  //--------------------------------------------------------------------------

  uint32_t r, g, b, a;
};
//----

template<>
struct ptx_format<ptxfmt_r32g32b32a32f>
{
  enum {rsize=32, gsize=32, bsize=32, asize=32};
  PFC_INLINE float32_t get_r() const {return r;}
  PFC_INLINE float32_t get_g() const {return g;}
  PFC_INLINE float32_t get_b() const {return b;}
  PFC_INLINE float32_t get_a() const {return a;}
  PFC_INLINE void set_rgba(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_)           {r=r_/255.0f; g=g_/255.0f; b=b_/255.0f; a=a_/255.0f;}
  PFC_INLINE void set_rgba(uint16_t r_, uint16_t g_, uint16_t b_, uint16_t a_)       {r=r_/65535.0f; g=g_/65535.0f; b=b_/65535.0f; a=a_/65535.0f;}
  PFC_INLINE void set_rgba(uint32_t r_, uint32_t g_, uint32_t b_, uint32_t a_)       {r=r_/42949672965.0f; g=g_/42949672965.0f; b=b_/42949672965.0f; a=a_/42949672965.0f;}
  PFC_INLINE void set_rgba(float32_t r_, float32_t g_, float32_t b_, float32_t a_)   {r=r_; g=g_; b=b_; a=a_;}
  template<e_ptx_format src_fmt> PFC_INLINE void set(const ptx_format<src_fmt> &px_) {set_rgba(px_.get_r(), px_.get_g(), px_.get_b(), px_.get_a());}
  //--------------------------------------------------------------------------

  float32_t r, g, b, a;
};
//----

template<>
struct ptx_format<ptxfmt_bc1>
{
};
//----

template<>
struct ptx_format<ptxfmt_bc2>
{
};
//----

template<>
struct ptx_format<ptxfmt_bc3>
{
};
//----

template<>
struct ptx_format<ptxfmt_bc4>
{
};
//----

template<>
struct ptx_format<ptxfmt_bc5>
{
};
//----

template<>
struct ptx_format<ptxfmt_bc6h>
{
};
//----

template<>
struct ptx_format<ptxfmt_bc7>
{
};
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_texture
//============================================================================
bool rasterizer_texture::is_valid() const
{
  return m_header!=0;
}
//----------------------------------------------------------------------------

e_ptx_type rasterizer_texture::type() const
{
  return e_ptx_type(m_header->type);
}
//----

e_ptx_format rasterizer_texture::format() const
{
  return e_ptx_format(m_header->format);
}
//----

e_ptx_layout rasterizer_texture::layout() const
{
  return e_ptx_layout(m_header->layout);
}
//----

uint8_t rasterizer_texture::num_lods() const
{
  return m_header->num_lods;
}
//----

uint16_t rasterizer_texture::width() const
{
  return m_header->width;
}
//----

uint16_t rasterizer_texture::height() const
{
  return m_header->height;
}
//----

uint16_t rasterizer_texture::depth() const
{
  return m_header->depth;
}
//----

const void *rasterizer_texture::data() const
{
  return m_header->data;
}
//----------------------------------------------------------------------------


//============================================================================
// rasterizer_sampler2d
//============================================================================
template<e_ptx_format src_fmt>
rasterizer_sampler2d<src_fmt>::rasterizer_sampler2d()
{
  m_tex=0;
}
//----

template<e_ptx_format src_fmt>
rasterizer_sampler2d<src_fmt>::rasterizer_sampler2d(const rasterizer_texture &tex_)
{
  init(tex_);
}
//----

template<e_ptx_format src_fmt>
void rasterizer_sampler2d<src_fmt>::init(const rasterizer_texture &tex_)
{
  PFC_ASSERT(tex_.format()==src_fmt);
  m_tex=&tex_;
}
//----------------------------------------------------------------------------

template<e_ptx_format src_fmt>
template<e_ptx_format dst_fmt>
void rasterizer_sampler2d<src_fmt>::load(ptx_format<dst_fmt> &px_, uint16_t u_, uint16_t v_)
{
  const ptx_format<src_fmt> &src_px=((const ptx_format<src_fmt>*)m_tex->data())[u_+v_*m_tex->width()];
  px_.set_rgba(src_px.get_r(), src_px.get_g(), src_px.get_b(), src_px.get_a());
}
//----

template<e_ptx_format src_fmt>
template<e_ptx_format dst_fmt>
void rasterizer_sampler2d<src_fmt>::sample_point(ptx_format<dst_fmt> &px_, float u_, float v_)
{
  u_=u_-::floor(u_);
  v_=v_-::floor(v_);
  uint16_t u=uint16_t(u_*m_tex->width());
  uint16_t v=uint16_t(v_*m_tex->height());
  const ptx_format<src_fmt> &src_px=((const ptx_format<src_fmt>*)m_tex->data())[u+v*m_tex->width()];
  px_.set_rgba(src_px.get_r(), src_px.get_g(), src_px.get_b(), src_px.get_a());
}
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
