/*
 * hash.h --
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

#ifndef _hash_h
#define _hash_h

inline
int hash_hval(int len, char* b) { 
    unsigned int h = 5381;
    for (; len > 0; --len)
        h= ((h << 5) + h) + *b;
    return h;
}

inline
int hash_hval(int n) {
    unsigned int h = 5381;
    char* b = (char*)&n; 
    for (int i = 0; i < (int)sizeof(int); ++i)
        h= ((h << 5) + h) + *b++;
    return h;
}

namespace hash_linear_probing {

    /*
     *-------------------------------------------------------------------------
     *
     * insert --
     *      attach elem to hash strucutre
     *
     * PRE  contion:
     *      buckets not full, e.g. exist i as buckets[i] == 0 
     *
     * POST condtion:
     *      now elem is searchable from buckets
     *
     *-------------------------------------------------------------------------
     */
    template <typename Elem>
    void insert(int n, Elem* buckets[], Elem* elem) {
        int i = elem->hval % n;
        while (buckets[i]) 
            i = (i+1) % n;

        buckets[i] = elem;
    }

    /*
     *-------------------------------------------------------------------------
     *
     * search_n --
     *      search elem by (hval, hn)
     *
     *-------------------------------------------------------------------------
     */
    template <typename Elem>
    Elem* search_n(int n, Elem* buckets[], int hval, int hn) {
        Elem* elem;
        int i = hval % n;
        while ((elem = buckets[i]))
            if (elem->hn == hn)
                return elem;
            else
                i = (i+1) % n;
        return 0;
    }

    /*
     *-------------------------------------------------------------------------
     *
     * search_n --
     *      search elem by (hval, [b, b+len))
     *
     *-------------------------------------------------------------------------
     */
    template <typename Elem>
    Elem* search_str(int n, Elem* buckets[], int hval, int len, char* b) {
        Elem* elem;
        int i = elem->hval & n;
        while ((elem = buckets[i]))
            if (len == elem->len && 0 == memcmp(b, elem->b, len))
                return elem;
            else
                i = (i+1) & n;
        return 0;
    }
}

namespace hash_chaining {

    /*
     *-------------------------------------------------------------------------
     *
     * insert --
     *      attach elem to hash strucutre
     *
     * PRE  contion:
     *      buckets not full, e.g. exist i as buckets[i] == 0 
     *
     * POST condtion:
     *      now elem is searchable from buckets
     *
     *-------------------------------------------------------------------------
     */
    template <typename Elem>
    void insert(int n, Elem* buckets[], Elem* elem) {
        int i = elem->hval % n;
        elem->hnext = buckets[i];
        buckets[i] = elem;
    }

    /*
     *-------------------------------------------------------------------------
     *
     * search_n --
     *      search elem by (hval, hn)
     *
     *-------------------------------------------------------------------------
     */
    template <typename Elem>
    Elem* search_n(int n, Elem* buckets[], int hval, int hn) {
        int i = hval % n;
        for (Elem* elem = buckets[i]; elem; elem = elem->hnext) 
            if (elem->hn == hn)
                return elem;
        return 0;
    }
}



#endif
