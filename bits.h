/*
 * bits.h --
 *
 * algorithms related to the calculation of the bits
 *
 * Fri Feb  1 10:25:43 PST 2013: initial release by Todd Xue
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
     * so stupid for this one
     */
    inline uint add(uint a, uint b) { if (b == 0) return a; uint sum = a ^ b; uint carry = ((a & b) << 1); return add(sum, carry); }
    
    /**
     * compare without using > < operator, but can C operators: -, bits
     */
    inline bool lt(uint a, uint b) { return (a - b) & (1 << 31); }
    inline bool gt(uint a, uint b) { return !lt(a, b); }
    inline uint max(uint a, uint b) { return lt(a,b) ? b : a; }
    inline uint min(uint a, uint b) { return a + b - max(a, b); }

    /**
     * swap using ^, in Z/2, it's same as -, + WITHOUT extra storage
     * (a, b) -> (a-b, b) -> (a-b, a) -> (b, a)
     * 
     * If inline really succeeded, then it really does it without extra storage
     * 
     * i'm confused at the beginning, now clarify as this:
     *  
     * in Z/2
     *   ^  + or -
     *   | max
     *   & min
     *   ~ no mapping, seems
     *
     * the codes written below is weird, without looking the above logic, how we know it works :(???
     */
    inline void swap(uint& a, uint& b) { 
        a = a ^ b; 
        b = a ^ b; 
        a = a ^ b; 
    }

    /**
     * using bit to decide if a uinteger is power of 2
     */
    inline bool is_2_power(uint a) { return (a & (a-1)) == 0; } 

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
     * right most 1 pos
     */
    inline uint right_most_1_pos(uint a) { if (!a) return 32; uint pos = 0; while ((a & 1) == 0) a >>= 1, ++pos; return pos; }

    /**
     * Number of bit 1
     *   3 --> 2
     *   4 --> 1
     */
    inline uint number_of_bit1(uint a) { uint c = 0; while (a > 0) { c += (a & 0x1); a >>= 1; } return c; }
    inline uint number_of_bit0(uint a) { return (uint)(sizeof(uint)/sizeof(char)*8 - number_of_bit1(a)); }


    /**
     * next smallest number with same number of 1 bits
     * return 0 if there is no next number
     */
    inline uint next_smallest(uint a) { 
        
        if (a == 0)
            return 0;

        /**
         *  0  1 1 1 0 0 0 0 
         *         ^
         *         p1
         */
        uint p1 = right_most_1_pos(a);

        /**
         *  0 1 1 1 0 0 0 0 
         *        ^
         *  ^     p1
         *  p2
         */
        uint p2 = p1+1;
        while (p2 < 32 && (a & (1 << p2)) > 0) ++p2;
        if (p2 == 32)
            return 0;

        uint b = a;
        /**
         * turn on p2 bit
         * 
         *  1  1 1 1 0 0 0 0 
         *  ^     
         *  p2
         */
        b |= (1 << p2);

        /**
         * turn off [0, p2)
         * 
         *  1  0 0 0 0 0 0 0 
         *  ^     
         *  p2
         */
        b &= ~((1 << p2) - 1);

        /**
         * turn on all removed bits to lowest bits
         *
         *  1  0 0 0 0 0 1 1 
         *  ^     
         */
        if (p2 - p1 > 1)
            b |= ((1 << (p2 - p1 - 1)) - 1);
        
        return b;
    }

    /**
     * previous largest number with same number of 1 bits
     * return 0 if there is no next number
     * 
     * the reverse of next_smallest, turns out a simpler :)
     */
    inline uint prev_largest(uint a) { return ~next_smallest(~a); }
}

#endif
