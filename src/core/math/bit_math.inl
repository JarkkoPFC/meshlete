//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// lsb/msb
//============================================================================
PFC_INLINE uint64_t lsb(uint64_t v_)
{
  // return the least significant set bit of the value
  return v_&-int64_t(v_);
}
//----

PFC_INLINE uint32_t lsb(uint32_t v_)
{
  // return the least significant set bit of the value
  return v_&-int32_t(v_);
}
//----

PFC_INLINE uint16_t lsb(uint16_t v_)
{
  // return the least significant set bit of the value
  return v_&-int16_t(v_);
}
//----

PFC_INLINE uint8_t lsb(uint8_t v_)
{
  // return the least significant set bit of the value
  return v_&-int8_t(v_);
}
//----------------------------------------------------------------------------

PFC_INLINE uint64_t msb(uint64_t v_)
{
  // return the most significant set bit of the value
#ifdef PFC_INTRINSIC_MSB64
  uint64_t res;
  PFC_INTRINSIC_MSB64(res, v_);
  return res;
#else
  v_|=v_>>1;
  v_|=v_>>2;
  v_|=v_>>4;
  v_|=v_>>8;
  v_|=v_>>16;
  v_|=v_>>32;
  return v_-(v_>>1);
#endif
}
//----

PFC_INLINE uint32_t msb(uint32_t v_)
{
  // return the most significant set bit of the value
#ifdef PFC_INTRINSIC_MSB32
  uint32_t res;
  PFC_INTRINSIC_MSB32(res, v_);
  return res;
#else
  v_|=v_>>1;
  v_|=v_>>2;
  v_|=v_>>4;
  v_|=v_>>8;
  v_|=v_>>16;
  return v_-(v_>>1);
#endif
}
//----

PFC_INLINE uint16_t msb(uint16_t v_)
{
  // return the most significant set bit of the value
#ifdef PFC_INTRINSIC_MSB32
  uint32_t res;
  PFC_INTRINSIC_MSB32(res, v_);
  return uint16_t(res);
#else
  v_|=v_>>1;
  v_|=v_>>2;
  v_|=v_>>4;
  v_|=v_>>8;
  return uint16_t(v_-(v_>>1));
#endif
}
//----

PFC_INLINE uint8_t msb(uint8_t v_)
{
  // return the most significant set bit of the value
#ifdef PFC_INTRINSIC_MSB32
  uint32_t res;
  PFC_INTRINSIC_MSB32(res, v_);
  return uint8_t(res);
#else
  v_|=v_>>1;
  v_|=v_>>2;
  v_|=v_>>4;
  return uint8_t(v_-(v_>>1));
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// strip_lsb/msb
//============================================================================
PFC_INLINE uint64_t strip_lsb(uint64_t v_)
{
  // strip lsb from the value
  return v_&(v_-1);
}
//----

PFC_INLINE uint32_t strip_lsb(uint32_t v_)
{
  // strip lsb from the value
  return v_&(v_-1);
}
//----

PFC_INLINE uint16_t strip_lsb(uint16_t v_)
{
  // strip lsb from the value
  return v_&(v_-1);
}
//----

PFC_INLINE uint8_t strip_lsb(uint8_t v_)
{
  // strip lsb from the value
  return v_&(v_-1);
}
//----------------------------------------------------------------------------

PFC_INLINE uint64_t strip_msb(uint64_t v_)
{
  // strip msb from the value
  return v_&~msb(v_);
}
//----

PFC_INLINE uint32_t strip_msb(uint32_t v_)
{
  // strip msb from the value
  return v_&~msb(v_);
}
//----

PFC_INLINE uint16_t strip_msb(uint16_t v_)
{
  // strip msb from the value
  return v_&~msb(v_);
}
//----

PFC_INLINE uint8_t strip_msb(uint8_t v_)
{
  // strip msb from the value
  return v_&~msb(v_);
}
//----------------------------------------------------------------------------


//============================================================================
// bitpos/lsb_pos/msb_pos
//============================================================================
PFC_INLINE uint8_t bitpos(uint64_t v_)
{
  // get bit position
  PFC_ASSERT_PEDANTIC_MSG(v_==(v_&-int64_t(v_)), ("Value must be zero or power-of-2\r\n"));
#ifdef PFC_INTRINSIC_MSBPOS64
  uint8_t idx;
  PFC_INTRINSIC_MSBPOS64(idx, v_);
  return idx;
#else
  // calculate bit position by using 64-bit de Bruijn sequence
  static PFC_ALIGN(64) const uint8_t s_bitpos_lut[64]=
  { 0,  1, 48,  2, 57, 49, 28,  3, 61, 58, 50, 42, 38, 29, 17,  4,
   62, 55, 59, 36, 53, 51, 43, 22, 45, 39, 33, 30, 24, 18, 12,  5,
   63, 47, 56, 27, 60, 41, 37, 16, 54, 35, 52, 21, 44, 32, 23, 11,
   46, 26, 40, 15, 34, 20, 31, 10, 25, 14, 19,  9, 13,  8,  7,  6};
  return s_bitpos_lut[uint64_t(v_*PFC_CONST_UINT64(0x03f79d71b4cb0a89))>>58];
#endif
}
//----

PFC_INLINE uint8_t bitpos(uint32_t v_)
{
  // get bit position
  PFC_ASSERT_PEDANTIC_MSG(v_==(v_&-int32_t(v_)), ("Value must be zero or power-of-2\r\n"));
#ifdef PFC_INTRINSIC_MSBPOS32
  uint8_t idx;
  PFC_INTRINSIC_MSBPOS32(idx, v_);
  return idx;
#else
  // calculate bit position by using 32-bit de Bruijn sequence
  static PFC_ALIGN(32) const uint8_t s_bitpos_lut[32]=
  { 0,  1, 28,  2, 29, 14, 24,  3, 30, 22, 20, 15, 25, 17,  4,  8, 
   31, 27, 13, 23, 21, 19, 16,  7, 26, 12, 18,  6, 11,  5, 10,  9};
  return s_bitpos_lut[uint32_t(v_*0x077cb531)>>27];
#endif
}
//----

PFC_INLINE uint8_t bitpos(uint16_t v_)
{
  // get bit position
  PFC_ASSERT_PEDANTIC_MSG(v_==(v_&-int16_t(v_)), ("Value must be zero or power-of-2\r\n"));
#ifdef PFC_INTRINSIC_MSBPOS32
  uint8_t idx;
  PFC_INTRINSIC_MSBPOS32(idx, v_);
  return idx;
#else
  // calculate bit position by using 16-bit de Bruijn sequence
  static PFC_ALIGN(16) const uint8_t s_bitpos_lut[16]={0, 1, 2, 5, 3, 9, 6, 11, 15, 4, 8, 10, 14, 7, 13, 12};
  return s_bitpos_lut[uint16_t(v_*0x09af)>>12];
#endif
}
//----

PFC_INLINE uint8_t bitpos(uint8_t v_)
{
  // get bit position
  PFC_ASSERT_PEDANTIC_MSG(v_==(v_&-int8_t(v_)), ("Value must be zero or power-of-2\r\n"));
#ifdef PFC_INTRINSIC_MSBPOS32
  uint8_t idx;
  PFC_INTRINSIC_MSBPOS32(idx, v_);
  return idx;
#else
  // calculate bit position by using 8-bit de Bruijn sequence
  static PFC_ALIGN(8) const uint8_t s_bitpos_lut[8]={0, 1, 2, 4, 7, 3, 6, 5};
  return s_bitpos_lut[uint8_t(v_*0x17)>>5];
#endif
}
//----------------------------------------------------------------------------

PFC_INLINE uint8_t lsb_pos(uint64_t v_)
{
  // get LSB position
#ifdef PFC_INTRINSIC_LSBPOS64
  uint8_t lsb_pos;
  PFC_INTRINSIC_LSBPOS64(lsb_pos, v_);
  return lsb_pos;
#else
  return bitpos(uint64_t(v_&-int64_t(v_)));
#endif
}
//----

PFC_INLINE uint8_t lsb_pos(uint32_t v_)
{
  // get LSB position
#ifdef PFC_INTRINSIC_LSBPOS32
  uint8_t lsb_pos;
  PFC_INTRINSIC_LSBPOS32(lsb_pos, v_);
  return lsb_pos;
#else
  return bitpos(uint32_t(v_&-int32_t(v_)));
#endif
}
//----

PFC_INLINE uint8_t lsb_pos(uint16_t v_)
{
  // get LSB position
#ifdef PFC_INTRINSIC_LSBPOS32
  uint8_t lsb_pos;
  PFC_INTRINSIC_LSBPOS32(lsb_pos, v_);
  return lsb_pos;
#else
  return bitpos(uint16_t(v_&-int16_t(v_)));
#endif
}
//----

PFC_INLINE uint8_t lsb_pos(uint8_t v_)
{
  // get LSB position
#ifdef PFC_INTRINSIC_LSBPOS32
  uint8_t lsb_pos;
  PFC_INTRINSIC_LSBPOS32(lsb_pos, v_);
  return lsb_pos;
#else
  return bitpos(uint8_t(v_&-int8_t(v_)));
#endif
}
//----------------------------------------------------------------------------

PFC_INLINE uint8_t msb_pos(uint64_t v_)
{
  // get MSB position
#ifdef PFC_INTRINSIC_MSBPOS64
  uint8_t msb_pos;
  PFC_INTRINSIC_MSBPOS64(msb_pos, v_);
  return msb_pos;
#else
  return bitpos(msb(v_));
#endif
}
//----

PFC_INLINE uint8_t msb_pos(uint32_t v_)
{
  // get MSB position
#ifdef PFC_INTRINSIC_MSBPOS32
  uint8_t msb_pos;
  PFC_INTRINSIC_MSBPOS32(msb_pos, v_);
  return msb_pos;
#else
  return bitpos(msb(v_));
#endif
}
//----

PFC_INLINE uint8_t msb_pos(uint16_t v_)
{
  // get MSB position
#ifdef PFC_INTRINSIC_MSBPOS32
  uint8_t msb_pos;
  PFC_INTRINSIC_MSBPOS32(msb_pos, v_);
  return msb_pos;
#else
  return bitpos(msb(v_));
#endif
}
//----

PFC_INLINE uint8_t msb_pos(uint8_t v_)
{
  // get MSB position
#ifdef PFC_INTRINSIC_MSBPOS32
  uint8_t msb_pos;
  PFC_INTRINSIC_MSBPOS32(msb_pos, v_);
  return msb_pos;
#else
  return bitpos(msb(v_));
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// is_pow2
//============================================================================
PFC_INLINE bool is_pow2(uint64_t v_)
{
  // check for power-of-2 value
  return (v_&(v_-1))==0;
}
//----

PFC_INLINE bool is_pow2(uint32_t v_)
{
  // check for power-of-2 value
  return (v_&(v_-1))==0;
}
//----

PFC_INLINE bool is_pow2(uint16_t v_)
{
  // check for power-of-2 value
  return (v_&(v_-1))==0;
}
//----

PFC_INLINE bool is_pow2(uint8_t v_)
{
  // check for power-of-2 value
  return (v_&(v_-1))==0;
}
//----------------------------------------------------------------------------


//============================================================================
// next_pow2
//============================================================================
PFC_INLINE uint64_t next_pow2(uint64_t v_)
{
  // the next power-of-2 of the value (if v_ is pow-of-2 returns v_)
#ifdef PFC_INTRINSIC_MSBPOS64
  uint8_t msb_pos;
  PFC_INTRINSIC_MSBPOS64(msb_pos, v_+v_-1);
  return uint64_t(!!v_)<<msb_pos;
#else
  --v_;
  v_|=v_>>1;
  v_|=v_>>2;
  v_|=v_>>4;
  v_|=v_>>8;
  v_|=v_>>16;
  v_|=v_>>32;
  return v_+1;
#endif
}
//----

PFC_INLINE uint32_t next_pow2(uint32_t v_)
{
  // the next power-of-2 of the value (if v_ is pow-of-2 returns v_)
#ifdef PFC_INTRINSIC_MSBPOS32
  uint8_t msb_pos;
  PFC_INTRINSIC_MSBPOS32(msb_pos, v_+v_-1);
  return uint32_t(!!v_)<<msb_pos;
#else
  --v_;
  v_|=v_>>1;
  v_|=v_>>2;
  v_|=v_>>4;
  v_|=v_>>8;
  v_|=v_>>16;
  return v_+1;
#endif
}
//----

PFC_INLINE uint16_t next_pow2(uint16_t v_)
{
  // the next power-of-2 of the value (if v_ is pow-of-2 returns v_)
#ifdef PFC_INTRINSIC_MSBPOS32
  uint8_t msb_pos;
  PFC_INTRINSIC_MSBPOS32(msb_pos, v_+v_-1);
  return uint16_t(!!v_)<<msb_pos;
#else
  --v_;
  v_|=v_>>1;
  v_|=v_>>2;
  v_|=v_>>4;
  v_|=v_>>8;
  return v_+1;
#endif
}
//----

PFC_INLINE uint8_t next_pow2(uint8_t v_)
{
  // the next power-of-2 of the value (if v_ is pow-of-2 returns v_)
#ifdef PFC_INTRINSIC_MSBPOS32
  uint8_t msb_pos;
  PFC_INTRINSIC_MSBPOS32(msb_pos, v_+v_-1);
  return uint8_t(!!v_)<<msb_pos;
#else
  --v_;
  v_|=v_>>1;
  v_|=v_>>2;
  v_|=v_>>4;
  return v_+1;
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// prev_pow2
//============================================================================
PFC_INLINE uint64_t prev_pow2(uint64_t v_)
{
  // previous power-of-2 (if v_ is power-of-2, returns v_)
#ifdef PFC_INTRINSIC_MSBPOS64
  uint8_t msb_pos;
  PFC_INTRINSIC_MSBPOS64(msb_pos, v_);
  return uint64_t(!!v_)<<msb_pos;
#else
  v_|=v_>>1;
  v_|=v_>>2;
  v_|=v_>>4;
  v_|=v_>>8;
  v_|=v_>>16;
  v_|=v_>>32;
  return v_-(v_>>1);
#endif
}
//----

PFC_INLINE uint32_t prev_pow2(uint32_t v_)
{
  // previous power-of-2 (if v_ is power-of-2, returns v_)
#ifdef PFC_INTRINSIC_MSBPOS32
  uint8_t msb_pos;
  PFC_INTRINSIC_MSBPOS32(msb_pos, v_);
  return uint32_t(!!v_)<<msb_pos;
#else
  v_|=v_>>1;
  v_|=v_>>2;
  v_|=v_>>4;
  v_|=v_>>8;
  v_|=v_>>16;
  return v_-(v_>>1);
#endif
}
//----

PFC_INLINE uint16_t prev_pow2(uint16_t v_)
{
  // previous power-of-2 (if v_ is power-of-2, returns v_)
#ifdef PFC_INTRINSIC_MSBPOS32
  uint8_t msb_pos;
  PFC_INTRINSIC_MSBPOS32(msb_pos, v_);
  return uint16_t(!!v_)<<msb_pos;
#else
  v_|=v_>>1;
  v_|=v_>>2;
  v_|=v_>>4;
  v_|=v_>>8;
  return v_-(v_>>1);
#endif
}
//----

PFC_INLINE uint8_t prev_pow2(uint8_t v_)
{
  // previous power-of-2 (if v_ is power-of-2, returns v_)
#ifdef PFC_INTRINSIC_MSBPOS32
  uint8_t msb_pos;
  PFC_INTRINSIC_MSBPOS32(msb_pos, v_);
  return uint8_t(!!v_)<<msb_pos;
#else
  v_|=v_>>1;
  v_|=v_>>2;
  v_|=v_>>4;
  return v_-(v_>>1);
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// num_bits
//============================================================================
PFC_INLINE unsigned num_bits(uint64_t v_)
{
  // count the number of set bits with SWAR algorithm
  v_-=(v_>>1)&PFC_CONST_UINT64(0x5555555555555555);
  v_=((v_>>2)&PFC_CONST_UINT64(0x3333333333333333))+(v_&PFC_CONST_UINT64(0x3333333333333333));
  v_=((v_>>4)+v_)&PFC_CONST_UINT64(0x0f0f0f0f0f0f0f0f);
  v_+=v_>>8;
  v_+=v_>>16;
  return (v_+(v_>>32))&0x7f;
}
//----

PFC_INLINE unsigned num_bits(uint32_t v_)
{
  // count the number of set bits with SWAR algorithm
  v_-=(v_>>1)&0x55555555;
  v_=((v_>>2)&0x33333333)+(v_&0x33333333);
  v_=((v_>>4)+v_)&0x0f0f0f0f;
  v_+=v_>>8;
  return (v_+(v_>>16))&0x3f;
}
//----

PFC_INLINE unsigned num_bits(uint16_t v_)
{
  // count the number of set bits with SWAR algorithm
  v_-=(v_>>1)&0x5555;
  v_=((v_>>2)&0x3333)+(v_&0x3333);
  v_=((v_>>4)+v_)&0x0f0f;
  return (v_+(v_>>8))&0x1f;
}
//----

PFC_INLINE unsigned num_bits(uint8_t v_)
{
  // count the number of set bits with SWAR algorithm
  v_-=(v_>>1)&0x55;
  v_=((v_>>2)&0x33)+(v_&0x33);
  return (v_+(v_>>4))&0x0f;
}
//----------------------------------------------------------------------------


//============================================================================
// clr/set/get_brun
//============================================================================
PFC_INLINE uint64_t clr_brun(uint64_t v_, uint8_t pos_)
{
  // clear run of set bits starting at given position
  return v_&uint64_t(v_+(uint64_t(1)<<pos_));
}
//----

PFC_INLINE uint32_t clr_brun(uint32_t v_, uint8_t pos_)
{
  // clear run of set bits starting at given position
  return v_&uint32_t(v_+(uint32_t(1)<<pos_));
}
//----

PFC_INLINE uint16_t clr_brun(uint16_t v_, uint8_t pos_)
{
  // clear run of set bits starting at given position
  return v_&uint16_t(v_+(uint16_t(1)<<pos_));
}
//----

PFC_INLINE uint8_t clr_brun(uint8_t v_, uint8_t pos_)
{
  // clear run of set bits starting at given position
  return v_&uint8_t(v_+(uint8_t(1)<<pos_));
}
//----------------------------------------------------------------------------

PFC_INLINE uint64_t set_brun(uint64_t v_, uint8_t pos_)
{
  // set run of unset bits starting at given position
  return v_|uint64_t(v_-(uint64_t(1)<<pos_));
}
//----

PFC_INLINE uint32_t set_brun(uint32_t v_, uint8_t pos_)
{
  // set run of unset bits starting at given position
  return v_|uint32_t(v_-(uint32_t(1)<<pos_));
}
//----

PFC_INLINE uint16_t set_brun(uint16_t v_, uint8_t pos_)
{
  // set run of unset bits starting at given position
  return v_|uint16_t(v_-(uint16_t(1)<<pos_));
}
//----

PFC_INLINE uint8_t set_brun(uint8_t v_, uint8_t pos_)
{
  // set run of unset bits starting at given position
  return v_|uint8_t(v_-(uint8_t(1)<<pos_));
}
//----------------------------------------------------------------------------

PFC_INLINE uint64_t get_brun(uint64_t v_, uint8_t pos_)
{
  // get run of set bits starting at given position
  return v_&~uint64_t(v_+(uint64_t(1)<<pos_));
}
//----

PFC_INLINE uint32_t get_brun(uint32_t v_, uint8_t pos_)
{
  // get run of set bits starting at given position
  return v_&~uint32_t(v_+(uint32_t(1)<<pos_));
}
//----

PFC_INLINE uint16_t get_brun(uint16_t v_, uint8_t pos_)
{
  // get run of set bits starting at given position
  return v_&~uint16_t(v_+(uint16_t(1)<<pos_));
}
//----

PFC_INLINE uint8_t get_brun(uint8_t v_, uint8_t pos_)
{
  // get run of set bits starting at given position
  return v_&~uint8_t(v_+(uint8_t(1)<<pos_));
}
//----------------------------------------------------------------------------

PFC_INLINE uint64_t get_0brun(uint64_t v_, uint8_t pos_)
{
  // get run of unset bits starting at given position
  return v_|~uint64_t(v_-(uint64_t(1)<<pos_));
}
//----

PFC_INLINE uint32_t get_0brun(uint32_t v_, uint8_t pos_)
{
  // get run of unset bits starting at given position
  return v_|~uint32_t(v_-(uint32_t(1)<<pos_));
}
//----

PFC_INLINE uint16_t get_0brun(uint16_t v_, uint8_t pos_)
{
  // get run of unset bits starting at given position
  return v_|~uint16_t(v_-(uint16_t(1)<<pos_));
}
//----

PFC_INLINE uint8_t get_0brun(uint8_t v_, uint8_t pos_)
{
  // get run of unset bits starting at given position
  return v_|~uint8_t(v_-(uint8_t(1)<<pos_));
}
//----------------------------------------------------------------------------


//============================================================================
// reverse_bits
//============================================================================
PFC_INLINE uint64_t reverse_bits(uint64_t v_)
{
  // reverse the order of bits with SWAR algorithm
  v_=((v_&PFC_CONST_UINT64(0xaaaaaaaaaaaaaaaa))>>1)|((v_&PFC_CONST_UINT64(0x5555555555555555))<<1);
  v_=((v_&PFC_CONST_UINT64(0xcccccccccccccccc))>>2)|((v_&PFC_CONST_UINT64(0x3333333333333333))<<2);
  v_=((v_&PFC_CONST_UINT64(0xf0f0f0f0f0f0f0f0))>>4)|((v_&PFC_CONST_UINT64(0x0f0f0f0f0f0f0f0f))<<4);
  v_=((v_&PFC_CONST_UINT64(0xff00ff00ff00ff00))>>8)|((v_&PFC_CONST_UINT64(0x00ff00ff00ff00ff))<<8);
  v_=((v_&PFC_CONST_UINT64(0xffff0000ffff0000))>>16)|((v_&PFC_CONST_UINT64(0x0000ffff0000ffff))<<16);
  return (v_>>32)|(v_<<32);
}
//----

PFC_INLINE uint32_t reverse_bits(uint32_t v_)
{
  // reverse the order of bits with SWAR algorithm
  v_=((v_&0xaaaaaaaa)>>1)|((v_&0x55555555)<<1);
  v_=((v_&0xcccccccc)>>2)|((v_&0x33333333)<<2);
  v_=((v_&0xf0f0f0f0)>>4)|((v_&0x0f0f0f0f)<<4);
  v_=((v_&0xff00ff00)>>8)|((v_&0x00ff00ff)<<8);
  return (v_>>16)|(v_<<16);
}
//----

PFC_INLINE uint16_t reverse_bits(uint16_t v_)
{
  // reverse the order of bits with SWAR algorithm
  v_=((v_&0xaaaa)>>1)|((v_&0x5555)<<1);
  v_=((v_&0xcccc)>>2)|((v_&0x3333)<<2);
  v_=((v_&0xf0f0)>>4)|((v_&0x0f0f)<<4);
  return (v_>>8)|(v_<<8);
}
//----

PFC_INLINE uint8_t reverse_bits(uint8_t v_)
{
  // reverse the order of bits with SWAR algorithm
  v_=((v_&0xaa)>>1)|((v_&0x55)<<1);
  v_=((v_&0xcc)>>2)|((v_&0x33)<<2);
  return (v_>>4)|(v_<<4);
}
//----------------------------------------------------------------------------


//============================================================================
// parity
//============================================================================
PFC_INLINE unsigned parity(uint64_t v_)
{
  // calculate parity (0=even number of set bits, 1=odd number of set bits)
  v_^=v_>>32;
  v_^=v_>>16;
  v_^=v_>>8;
  v_^=v_>>4;
  return (0x6996>>(v_&0xf))&1;
}
//----

PFC_INLINE unsigned parity(uint32_t v_)
{
  // calculate parity (0=even number of set bits, 1=odd number of set bits)
  v_^=v_>>16;
  v_^=v_>>8;
  v_^=v_>>4;
  return (0x6996>>(v_&0xf))&1;
}
//----

PFC_INLINE unsigned parity(uint16_t v_)
{
  // calculate parity (0=even number of set bits, 1=odd number of set bits)
  v_^=v_>>8;
  v_^=v_>>4;
  return (0x6996>>(v_&0xf))&1;
}
//----

PFC_INLINE unsigned parity(uint8_t v_)
{
  // calculate parity (0=even number of set bits, 1=odd number of set bits)
  v_^=v_>>4;
  return (0x6996>>(v_&0xf))&1;
}
//----------------------------------------------------------------------------


//============================================================================
// rol/ror
//============================================================================
PFC_INLINE uint64_t rol(uint64_t v_, uint8_t shift_)
{
  // rotate bits to left
#ifdef PFC_INTRINSIC_ROL64
  uint64_t res;
  PFC_INTRINSIC_ROL64(res, v_, shift_);
  return res;
#else
  return v_<<shift_ | v_>>(64-shift_);
#endif
}
//----

PFC_INLINE uint32_t rol(uint32_t v_, uint8_t shift_)
{
  // rotate bits to left
#ifdef PFC_INTRINSIC_ROL32
  uint32_t res;
  PFC_INTRINSIC_ROL32(res, v_, shift_);
  return res;
#else
  return v_<<shift_ | v_>>(32-shift_);
#endif
}
//----

PFC_INLINE uint16_t rol(uint16_t v_, uint8_t shift_)
{
  // rotate bits to left
#ifdef PFC_INTRINSIC_ROL16
  uint16_t res;
  PFC_INTRINSIC_ROL16(res, v_, shift_);
  return res;
#else
  return v_<<shift_ | v_>>(16-shift_);
#endif
}
//----

PFC_INLINE uint8_t rol(uint8_t v_, uint8_t shift_)
{
  // rotate bits to left
#ifdef PFC_INTRINSIC_ROL8
  uint8_t res;
  PFC_INTRINSIC_ROL8(res, v_, shift_);
  return res;
#else
  return v_<<shift_ | v_>>(8-shift_);
#endif
}
//----------------------------------------------------------------------------

PFC_INLINE uint64_t ror(uint64_t v_, uint8_t shift_)
{
  // rotate bits to right
#ifdef PFC_INTRINSIC_ROR64
  uint64_t res;
  PFC_INTRINSIC_ROR64(res, v_, shift_);
  return res;
#else
  return v_>>shift_ | v_<<(64-shift_);
#endif
}
//----

PFC_INLINE uint32_t ror(uint32_t v_, uint8_t shift_)
{
  // rotate bits to right
#ifdef PFC_INTRINSIC_ROR32
  uint32_t res;
  PFC_INTRINSIC_ROR32(res, v_, shift_);
  return res;
#else
  return v_>>shift_ | v_<<(32-shift_);
#endif
}
//----

PFC_INLINE uint16_t ror(uint16_t v_, uint8_t shift_)
{
  // rotate bits to right
#ifdef PFC_INTRINSIC_ROR16
  uint16_t res;
  PFC_INTRINSIC_ROR16(res, v_, shift_);
  return res;
#else
  return v_>>shift_ | v_<<(16-shift_);
#endif
}
//----

PFC_INLINE uint8_t ror(uint8_t v_, uint8_t shift_)
{
  // rotate bits to right
#ifdef PFC_INTRINSIC_ROR8
  uint8_t res;
  PFC_INTRINSIC_ROR8(res, v_, shift_);
  return res;
#else
  return v_>>shift_ | v_<<(8-shift_);
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// mask/imask
//============================================================================
PFC_INLINE uint64_t mask64(unsigned size_)
{
  // return 64-bit bit-mask of given size
  PFC_ASSERT_PEDANTIC_MSG(size_<=64, ("Bit mask size must be smaller than or equal to 64\r\n"));
  static PFC_ALIGN_CACHE const uint64_t s_lut[65]=
  {PFC_CONST_UINT64(0x0000000000000000),
   PFC_CONST_UINT64(0x0000000000000001), PFC_CONST_UINT64(0x0000000000000003),
   PFC_CONST_UINT64(0x0000000000000007), PFC_CONST_UINT64(0x000000000000000f),
   PFC_CONST_UINT64(0x000000000000001f), PFC_CONST_UINT64(0x000000000000003f),
   PFC_CONST_UINT64(0x000000000000007f), PFC_CONST_UINT64(0x00000000000000ff),
   PFC_CONST_UINT64(0x00000000000001ff), PFC_CONST_UINT64(0x00000000000003ff),
   PFC_CONST_UINT64(0x00000000000007ff), PFC_CONST_UINT64(0x0000000000000fff),
   PFC_CONST_UINT64(0x0000000000001fff), PFC_CONST_UINT64(0x0000000000003fff),
   PFC_CONST_UINT64(0x0000000000007fff), PFC_CONST_UINT64(0x000000000000ffff),
   PFC_CONST_UINT64(0x000000000001ffff), PFC_CONST_UINT64(0x000000000003ffff),
   PFC_CONST_UINT64(0x000000000007ffff), PFC_CONST_UINT64(0x00000000000fffff),
   PFC_CONST_UINT64(0x00000000001fffff), PFC_CONST_UINT64(0x00000000003fffff),
   PFC_CONST_UINT64(0x00000000007fffff), PFC_CONST_UINT64(0x0000000000ffffff),
   PFC_CONST_UINT64(0x0000000001ffffff), PFC_CONST_UINT64(0x0000000003ffffff),
   PFC_CONST_UINT64(0x0000000007ffffff), PFC_CONST_UINT64(0x000000000fffffff),
   PFC_CONST_UINT64(0x000000001fffffff), PFC_CONST_UINT64(0x000000003fffffff),
   PFC_CONST_UINT64(0x000000007fffffff), PFC_CONST_UINT64(0x00000000ffffffff),
   PFC_CONST_UINT64(0x00000001ffffffff), PFC_CONST_UINT64(0x00000003ffffffff),
   PFC_CONST_UINT64(0x00000007ffffffff), PFC_CONST_UINT64(0x0000000fffffffff),
   PFC_CONST_UINT64(0x0000001fffffffff), PFC_CONST_UINT64(0x0000003fffffffff),
   PFC_CONST_UINT64(0x0000007fffffffff), PFC_CONST_UINT64(0x000000ffffffffff),
   PFC_CONST_UINT64(0x000001ffffffffff), PFC_CONST_UINT64(0x000003ffffffffff),
   PFC_CONST_UINT64(0x000007ffffffffff), PFC_CONST_UINT64(0x00000fffffffffff),
   PFC_CONST_UINT64(0x00001fffffffffff), PFC_CONST_UINT64(0x00003fffffffffff),
   PFC_CONST_UINT64(0x00007fffffffffff), PFC_CONST_UINT64(0x0000ffffffffffff),
   PFC_CONST_UINT64(0x0001ffffffffffff), PFC_CONST_UINT64(0x0003ffffffffffff),
   PFC_CONST_UINT64(0x0007ffffffffffff), PFC_CONST_UINT64(0x000fffffffffffff),
   PFC_CONST_UINT64(0x001fffffffffffff), PFC_CONST_UINT64(0x003fffffffffffff),
   PFC_CONST_UINT64(0x007fffffffffffff), PFC_CONST_UINT64(0x00ffffffffffffff),
   PFC_CONST_UINT64(0x01ffffffffffffff), PFC_CONST_UINT64(0x03ffffffffffffff),
   PFC_CONST_UINT64(0x07ffffffffffffff), PFC_CONST_UINT64(0x0fffffffffffffff),
   PFC_CONST_UINT64(0x1fffffffffffffff), PFC_CONST_UINT64(0x3fffffffffffffff),
   PFC_CONST_UINT64(0x7fffffffffffffff), PFC_CONST_UINT64(0xffffffffffffffff)};
  return s_lut[size_];
}
//----

PFC_INLINE uint32_t mask32(unsigned size_)
{
  // return 32-bit bit-mask of given size
  PFC_ASSERT_PEDANTIC_MSG(size_<=32, ("Bit mask size must be smaller than or equal to 32\r\n"));
  static PFC_ALIGN(128) const uint32_t s_lut[33]={0x00000000,
                                                0x00000001, 0x00000003, 0x00000007, 0x0000000f,
                                                0x0000001f, 0x0000003f, 0x0000007f, 0x000000ff,
                                                0x000001ff, 0x000003ff, 0x000007ff, 0x00000fff,
                                                0x00001fff, 0x00003fff, 0x00007fff, 0x0000ffff,
                                                0x0001ffff, 0x0003ffff, 0x0007ffff, 0x000fffff,
                                                0x001fffff, 0x003fffff, 0x007fffff, 0x00ffffff,
                                                0x01ffffff, 0x03ffffff, 0x07ffffff, 0x0fffffff,
                                                0x1fffffff, 0x3fffffff, 0x7fffffff, 0xffffffff};
  return s_lut[size_];
}
//----

PFC_INLINE uint16_t mask16(unsigned size_)
{
  // return 16-bit bit-mask of given size
  PFC_ASSERT_PEDANTIC_MSG(size_<=16, ("Bit mask size must be smaller than or equal to 16\r\n"));
  static PFC_ALIGN(64) const uint16_t s_lut[17]={0x0000,
                                               0x0001, 0x0003, 0x0007, 0x000f,
                                               0x001f, 0x003f, 0x007f, 0x00ff,
                                               0x01ff, 0x03ff, 0x07ff, 0x0fff,
                                               0x1fff, 0x3fff, 0x7fff, 0xffff};
  return s_lut[size_];
}
//----

PFC_INLINE uint8_t mask8(unsigned size_)
{
  // return 8-bit bit-mask of given size
  PFC_ASSERT_PEDANTIC_MSG(size_<=8, ("Bit mask size must be smaller than or equal to 8\r\n"));
  static PFC_ALIGN(16) const uint8_t s_lut[9]={0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};
  return s_lut[size_];
}
//----------------------------------------------------------------------------

PFC_INLINE uint64_t imask64(unsigned size_)
{
  // return 64-bit inverse bit-mask of given size
  PFC_ASSERT_PEDANTIC_MSG(size_<=64, ("Inverse bit mask size must be smaller than or equal to 64\r\n"));
  static PFC_ALIGN_CACHE const uint64_t s_lut[65]=
  {PFC_CONST_UINT64(0xffffffffffffffff),
   PFC_CONST_UINT64(0xfffffffffffffffe), PFC_CONST_UINT64(0xfffffffffffffffc),
   PFC_CONST_UINT64(0xfffffffffffffff8), PFC_CONST_UINT64(0xfffffffffffffff0),
   PFC_CONST_UINT64(0xffffffffffffffe0), PFC_CONST_UINT64(0xffffffffffffffc0),
   PFC_CONST_UINT64(0xffffffffffffff80), PFC_CONST_UINT64(0xffffffffffffff00),
   PFC_CONST_UINT64(0xfffffffffffffe00), PFC_CONST_UINT64(0xfffffffffffffc00),
   PFC_CONST_UINT64(0xfffffffffffff800), PFC_CONST_UINT64(0xfffffffffffff000),
   PFC_CONST_UINT64(0xffffffffffffe000), PFC_CONST_UINT64(0xffffffffffffc000),
   PFC_CONST_UINT64(0xffffffffffff8000), PFC_CONST_UINT64(0xffffffffffff0000),
   PFC_CONST_UINT64(0xfffffffffffe0000), PFC_CONST_UINT64(0xfffffffffffc0000),
   PFC_CONST_UINT64(0xfffffffffff80000), PFC_CONST_UINT64(0xfffffffffff00000),
   PFC_CONST_UINT64(0xffffffffffe00000), PFC_CONST_UINT64(0xffffffffffc00000),
   PFC_CONST_UINT64(0xffffffffff800000), PFC_CONST_UINT64(0xffffffffff000000),
   PFC_CONST_UINT64(0xfffffffffe000000), PFC_CONST_UINT64(0xfffffffffc000000),
   PFC_CONST_UINT64(0xfffffffff8000000), PFC_CONST_UINT64(0xfffffffff0000000),
   PFC_CONST_UINT64(0xffffffffe0000000), PFC_CONST_UINT64(0xffffffffc0000000),
   PFC_CONST_UINT64(0xffffffff80000000), PFC_CONST_UINT64(0xffffffff00000000),
   PFC_CONST_UINT64(0xfffffffe00000000), PFC_CONST_UINT64(0xfffffffc00000000),
   PFC_CONST_UINT64(0xfffffff800000000), PFC_CONST_UINT64(0xfffffff000000000),
   PFC_CONST_UINT64(0xffffffe000000000), PFC_CONST_UINT64(0xffffffc000000000),
   PFC_CONST_UINT64(0xffffff8000000000), PFC_CONST_UINT64(0xffffff0000000000),
   PFC_CONST_UINT64(0xfffffe0000000000), PFC_CONST_UINT64(0xfffffc0000000000),
   PFC_CONST_UINT64(0xfffff80000000000), PFC_CONST_UINT64(0xfffff00000000000),
   PFC_CONST_UINT64(0xffffe00000000000), PFC_CONST_UINT64(0xffffc00000000000),
   PFC_CONST_UINT64(0xffff800000000000), PFC_CONST_UINT64(0xffff000000000000),
   PFC_CONST_UINT64(0xfffe000000000000), PFC_CONST_UINT64(0xfffc000000000000),
   PFC_CONST_UINT64(0xfff8000000000000), PFC_CONST_UINT64(0xfff0000000000000),
   PFC_CONST_UINT64(0xffe0000000000000), PFC_CONST_UINT64(0xffc0000000000000),
   PFC_CONST_UINT64(0xff80000000000000), PFC_CONST_UINT64(0xff00000000000000),
   PFC_CONST_UINT64(0xfe00000000000000), PFC_CONST_UINT64(0xfc00000000000000),
   PFC_CONST_UINT64(0xf800000000000000), PFC_CONST_UINT64(0xf000000000000000),
   PFC_CONST_UINT64(0xe000000000000000), PFC_CONST_UINT64(0xc000000000000000),
   PFC_CONST_UINT64(0x8000000000000000), PFC_CONST_UINT64(0x0000000000000000)};
  return s_lut[size_];
}
//----

PFC_INLINE uint32_t imask32(unsigned size_)
{
  // return 32-bit inverse bit-mask of given size
  PFC_ASSERT_PEDANTIC_MSG(size_<=32, ("Inverse bit mask size must be smaller than or equal to 32\r\n"));
  static PFC_ALIGN(128) const uint32_t s_lut[33]={0xffffffff,
                                                0xfffffffe, 0xfffffffc, 0xfffffff8, 0xfffffff0,
                                                0xffffffe0, 0xffffffc0, 0xffffff80, 0xffffff00,
                                                0xfffffe00, 0xfffffc00, 0xfffff800, 0xfffff000,
                                                0xffffe000, 0xffffc000, 0xffff8000, 0xffff0000,
                                                0xfffe0000, 0xfffc0000, 0xfff80000, 0xfff00000,
                                                0xffe00000, 0xffc00000, 0xff800000, 0xff000000,
                                                0xfe000000, 0xfc000000, 0xf8000000, 0xf0000000,
                                                0xe0000000, 0xc0000000, 0x80000000, 0x00000000};
  return s_lut[size_];
}
//----

PFC_INLINE uint16_t imask16(unsigned size_)
{
  // return 16-bit inverse bit-mask of given size
  PFC_ASSERT_PEDANTIC_MSG(size_<=16, ("Inverse bit mask size must be smaller than or equal to 16\r\n"));
  static PFC_ALIGN(64) const uint16_t s_lut[17]={0xffff,
                                               0xfffe, 0xfffc, 0xfff8, 0xfff0,
                                               0xffe0, 0xffc0, 0xff80, 0xff00,
                                               0xfe00, 0xfc00, 0xf800, 0xf000,
                                               0xe000, 0xc000, 0x8000, 0x0000};
  return s_lut[size_];
}
//----

PFC_INLINE uint8_t imask8(unsigned size_)
{
  // return 8-bit inverse bit-mask of given size
  PFC_ASSERT_PEDANTIC_MSG(size_<=8, ("Inverse bit mask size must be smaller than or equal to 8\r\n"));
  static PFC_ALIGN(16) const uint8_t s_lut[9]={0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00};
  return s_lut[size_];
}
//----------------------------------------------------------------------------


//============================================================================
// bit_shift
//============================================================================
template<int shift>
uint64_t bit_shift(uint64_t v_)
{
  #define PFC_CLAMP_SHIFT(shift__) ((shift__)<0||(shift__)>=64?0:shift__)
  return shift>-64&&shift<64?shift<0?v_>>PFC_CLAMP_SHIFT(-shift):v_<<PFC_CLAMP_SHIFT(shift):0;
  #undef PFC_CLAMP_SHIFT
}
//----

template<int shift>
uint32_t bit_shift(uint32_t v_)
{
  #define PFC_CLAMP_SHIFT(shift__) ((shift__)<0||(shift__)>=32?0:shift__)
  return shift>-32&&shift<32?shift<0?v_>>PFC_CLAMP_SHIFT(-shift):v_<<PFC_CLAMP_SHIFT(shift):0;
  #undef PFC_CLAMP_SHIFT
}
//----

template<int shift>
uint16_t bit_shift(uint16_t v_)
{
  #define PFC_CLAMP_SHIFT(shift__) ((shift__)<0||(shift__)>=16?0:shift__)
  return shift>-16&&shift<16?shift<0?v_>>PFC_CLAMP_SHIFT(-shift):v_<<PFC_CLAMP_SHIFT(shift):0;
  #undef PFC_CLAMP_SHIFT
}
//----

template<int shift>
uint8_t bit_shift(uint8_t v_)
{
  #define PFC_CLAMP_SHIFT(shift__) ((shift__)<0||(shift__)>=8?0:shift__)
  return shift>-8&&shift<8?shift<0?v_>>PFC_CLAMP_SHIFT(-shift):v_<<PFC_CLAMP_SHIFT(shift):0;
  #undef PFC_CLAMP_SHIFT
}
//----------------------------------------------------------------------------
