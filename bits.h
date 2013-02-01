/*
 * bits.h --
 *
 * algorithms related to the calculation of the bits
 *
 * 2009/12/26: initial release by Todd Xue
 */

#ifndef _bits_h
#define _bits_h

/**
 * some ugly bits operations
 */

namespace bits {

    typedef unsigned int uint;

    /**
     * using bit to implement add
     */
    inline uint add(uint a, uint b) { return ((a & b) << 1) | (a | b); } 

    /**
     * using bit to decide if a uinteger is power of 2
     */
    inline bool is_2_power(uint a) { return a & (a-1) == 0; } 

    /**
     * log2 
     * Note: 
     *   log2(0, 1) -> 0 --> 2^^?
     *   log2(2, 3) -> 1 --> 2^^0
     *   log2(4, 5, 6, 7) --> 2 --> 2^^2 = 4
     * No way to return a good value to log2(0) :(
     */
    inline uint log2(uint a) { uint c = 0; while (a >>= 1) ++c; return c; }

    /**
     * Number of bit 1
     *   3 --> 2
     *   4 --> 1
     */
    inline uint number_of_bit1(uint a) { uint c = 0; while (a > 0) { c += (a & 0x1); a >>= 1; } return c; }
    inline uint number_of_bit0(uint a) { return (uint)(sizeof(uint)/sizeof(char)*8 - number_of_bit1(a)); }
}

#endif
