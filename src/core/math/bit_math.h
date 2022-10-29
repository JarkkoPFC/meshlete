//============================================================================
// Profoundic Core Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_BIT_MATH_H
#define PFC_CORE_MATH_BIT_MATH_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core/core.h"
namespace pfc
{

// new
PFC_INLINE uint64_t lsb(uint64_t);                     // the least significant set bit (e.g. lsb(176)=16. note: lsb(0)=0)
PFC_INLINE uint32_t lsb(uint32_t);
PFC_INLINE uint16_t lsb(uint16_t);
PFC_INLINE uint8_t lsb(uint8_t);
PFC_INLINE uint64_t msb(uint64_t);                     // the most significant set bit (e.g. msb(176)=128. note: msb(0)=undefined)
PFC_INLINE uint32_t msb(uint32_t);
PFC_INLINE uint16_t msb(uint16_t);
PFC_INLINE uint8_t msb(uint8_t);
PFC_INLINE uint64_t strip_lsb(uint64_t);               // strip lsb from the value (e.g. strip_lsb(176)=160)
PFC_INLINE uint32_t strip_lsb(uint32_t);
PFC_INLINE uint16_t strip_lsb(uint16_t);
PFC_INLINE uint8_t strip_lsb(uint8_t);
PFC_INLINE uint64_t strip_msb(uint64_t);               // strip msb from the value (e.g. strip_msb(176)=48)
PFC_INLINE uint32_t strip_msb(uint32_t);
PFC_INLINE uint16_t strip_msb(uint16_t);
PFC_INLINE uint8_t strip_msb(uint8_t);
PFC_INLINE uint8_t bitpos(uint64_t);                   // position of the bit of a power-of-2 value (e.g. bitpos(32)=5. note: bitpos(0)=undefined)
PFC_INLINE uint8_t bitpos(uint32_t);
PFC_INLINE uint8_t bitpos(uint16_t);
PFC_INLINE uint8_t bitpos(uint8_t);
PFC_INLINE uint8_t lsb_pos(uint64_t);                  // least-significant-bit position (e.g. lsb_pos(176)=4. note: lsb_pos(0)=undefined)
PFC_INLINE uint8_t lsb_pos(uint32_t);
PFC_INLINE uint8_t lsb_pos(uint16_t);
PFC_INLINE uint8_t lsb_pos(uint8_t);
PFC_INLINE uint8_t msb_pos(uint64_t);                  // most-significant-bit position (e.g. msb_pos(92)=6. note: msb_pos(0)=undefined)
PFC_INLINE uint8_t msb_pos(uint32_t);
PFC_INLINE uint8_t msb_pos(uint16_t);
PFC_INLINE uint8_t msb_pos(uint8_t);
PFC_INLINE bool is_pow2(uint64_t);                     // check if the value is power-of-2 (note: is_pow2(0)=true)
PFC_INLINE bool is_pow2(uint32_t);
PFC_INLINE bool is_pow2(uint16_t);
PFC_INLINE bool is_pow2(uint8_t);
PFC_INLINE uint64_t next_pow2(uint64_t);               // next power-of-2 (if the value is already power-of-2, returns the value)
PFC_INLINE uint32_t next_pow2(uint32_t);
PFC_INLINE uint16_t next_pow2(uint16_t);
PFC_INLINE uint8_t next_pow2(uint8_t);
PFC_INLINE uint64_t prev_pow2(uint64_t);               // previous power-of-2 (if the value is already power-of-2, returns the value)
PFC_INLINE uint32_t prev_pow2(uint32_t);
PFC_INLINE uint16_t prev_pow2(uint16_t);
PFC_INLINE uint8_t prev_pow2(uint8_t);
PFC_INLINE unsigned num_bits(uint64_t);                // number of set bits (e.g. num_bits(176)=3)
PFC_INLINE unsigned num_bits(uint32_t);
PFC_INLINE unsigned num_bits(uint16_t);
PFC_INLINE unsigned num_bits(uint8_t);
PFC_INLINE uint64_t clr_brun(uint64_t, uint8_t pos_);  // clear run of set bits starting at given position (e.g. clr_brun(10111101b, 3)=10000101b)
PFC_INLINE uint32_t clr_brun(uint32_t, uint8_t pos_);
PFC_INLINE uint16_t clr_brun(uint16_t, uint8_t pos_);
PFC_INLINE uint8_t clr_brun(uint8_t, uint8_t pos_);
PFC_INLINE uint64_t set_brun(uint64_t, uint8_t pos_);  // set run of unset bits starting at given position (e.g. set_brun(10001011b, 5)=11101011b)
PFC_INLINE uint32_t set_brun(uint32_t, uint8_t pos_);
PFC_INLINE uint16_t set_brun(uint16_t, uint8_t pos_);
PFC_INLINE uint8_t set_brun(uint8_t, uint8_t pos_);
PFC_INLINE uint64_t get_brun(uint64_t, uint8_t pos_);  // run of set bits starting at given position (e.g. get_brun(10111101b, 3)=00111000b)
PFC_INLINE uint32_t get_brun(uint32_t, uint8_t pos_);
PFC_INLINE uint16_t get_brun(uint16_t, uint8_t pos_);
PFC_INLINE uint8_t get_brun(uint8_t, uint8_t pos_);
PFC_INLINE uint64_t get_0brun(uint64_t, uint8_t pos_); // run of unset bits starting at given position (e.g. get_0brun(10001011b, 5)=10011111b)
PFC_INLINE uint32_t get_0brun(uint32_t, uint8_t pos_);
PFC_INLINE uint16_t get_0brun(uint16_t, uint8_t pos_);
PFC_INLINE uint8_t get_0brun(uint8_t, uint8_t pos_);
PFC_INLINE uint64_t reverse_bits(uint64_t);            // reverse the order of bits (e.g. reverse_bits(176)=0x0d000000)
PFC_INLINE uint32_t reverse_bits(uint32_t);
PFC_INLINE uint16_t reverse_bits(uint16_t);
PFC_INLINE uint8_t reverse_bits(uint8_t);
PFC_INLINE unsigned parity(uint64_t);                  // calculate parity of the value (even=0, odd=1)
PFC_INLINE unsigned parity(uint32_t);
PFC_INLINE unsigned parity(uint16_t);
PFC_INLINE unsigned parity(uint8_t);
PFC_INLINE uint64_t rol(uint64_t, uint8_t shift_);     // rotate bits to left
PFC_INLINE uint32_t rol(uint32_t, uint8_t shift_);
PFC_INLINE uint16_t rol(uint16_t, uint8_t shift_);
PFC_INLINE uint8_t rol(uint8_t, uint8_t shift_);
PFC_INLINE uint64_t ror(uint64_t, uint8_t shift_);     // rotate bits to right
PFC_INLINE uint32_t ror(uint32_t, uint8_t shift_);
PFC_INLINE uint16_t ror(uint16_t, uint8_t shift_);
PFC_INLINE uint8_t ror(uint8_t, uint8_t shift_);
PFC_INLINE uint64_t mask64(unsigned size_);            // generate bit mask of given size (i.e. set bits [0, size_-1])
PFC_INLINE uint32_t mask32(unsigned size_);
PFC_INLINE uint16_t mask16(unsigned size_);
PFC_INLINE uint8_t mask8(unsigned size_);
PFC_INLINE uint64_t imask64(unsigned size_);           // generate inverse bit mask of given size (i.e. set bits [size_, bits-1])
PFC_INLINE uint32_t imask32(unsigned size_);
PFC_INLINE uint16_t imask16(unsigned size_);
PFC_INLINE uint8_t imask8(unsigned size_);
template<int> PFC_INLINE uint64_t bit_shift(uint64_t); // shift bits with signed compile-time value: negative values shift to the right and positive to the left
template<int> PFC_INLINE uint32_t bit_shift(uint32_t);
template<int> PFC_INLINE uint16_t bit_shift(uint16_t);
template<int> PFC_INLINE uint8_t bit_shift(uint8_t);  
//----------------------------------------------------------------------------

//============================================================================
#include "bit_math.inl"
} // namespace pfc
#endif
