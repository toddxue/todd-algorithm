/*
 * hash.cpp --
 *
 * hash data structures 
 *     differenct collision handling:
 *       #1 linear probing/open addressing
 *       #2 chaining
 *       #3 dynamic/extendible hashing
 *     
 *     hash func itself may not be related, 
 *     we choose this one as the default:
 *         h = h*33 + c -- recusivly when iterate 'c'
 *
 *     if special context have better data structure
 *     always there will be more natural one
 *
 * 2010/1/3: initial release by Todd Xue
 */
#include "hash.h"

