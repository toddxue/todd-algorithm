#include "timed.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>

struct Elem {
    int hn;
    int hval;
    Elem* hnext;
};

void test_hash_linear_probing(int n, Elem* buckets[], int m, Elem* e_arr) {
    using namespace hash_linear_probing;
    for (int i = 0; i < m; ++i) {
        Elem& e = e_arr[i];
        if (search_n(n, buckets, e.hval, e.hn))
            insert(n, buckets, &e);
    }
}

void test_hash_chaining(int n, Elem* buckets[], int m, Elem* e_arr) {
    using namespace hash_chaining;
    for (int i = 0; i < m; ++i) {
        Elem& e = e_arr[i];
        if (search_n(n, buckets, e.hval, e.hn))
            insert(n, buckets, &e);
    }
}

int test(int buckets_c, int slots_c) {

    Elem** buckets = new Elem*[buckets_c];
    Elem* e_arr = new Elem[slots_c];

    for (int i = 0; i < slots_c; ++i) {
        e_arr[i].hn = random();
        e_arr[i].hval = hash_hval(e_arr[i].hn);
    }

    {
        memset(buckets, 0, sizeof(Elem*) * buckets_c);
        TIMED_BLOCK_STDERR(linear_probing, true);
        test_hash_linear_probing(buckets_c, buckets, slots_c, e_arr);
    }

    {
        memset(buckets, 0, sizeof(Elem*) * buckets_c);
        TIMED_BLOCK_STDERR(linear_chaining, true);
        test_hash_chaining(buckets_c, buckets, slots_c, e_arr);
    }
    
    delete e_arr;
    delete[] buckets;
}

int main(int argc, char* argv[]) {
    int buckets_c = strtol(argv[1], 0, 10);
    int slots_c = strtol(argv[2], 0, 10);
    test(buckets_c, slots_c);
    test(buckets_c, slots_c);
    test(buckets_c, slots_c);
    return 0;
}
