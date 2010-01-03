#include "TAP.h"
#include "hash.h"

using namespace hash_chaining;

struct Elem {
    int hn;
    int hval;
    Elem* hnext;
};

bool rcheck(int n, int c) {
    for (; c; --c) {
        Elem** buckets = (Elem**)calloc(n, sizeof(Elem*));
        int ec = random() % n;
        Elem* e = (Elem*)malloc(ec * sizeof(Elem));

        int hn_base = random();
        if (random() % 2) 
            hn_base = -hn_base;

        int hval;
        
        for (int i = 0; i < ec; ++i) {
            e[i].hn = hn_base + i;
            hval = random();
            if (hval < 0) 
                hval = -hval;
            e[i].hval = hval; // suppose hval >= 0 always
            insert(n, buckets, &e[i]);
        }

        for (int i = 0; i < ec; ++i) {
            if (search_n(n, buckets, e[i].hval, e[i].hn) != &e[i])
                return false;
        }

        free(e);
        free(buckets);
    }
}


int main(int argc, char* argv[]) {
    OK_SUM();

    // n == 1 : 
    {
        Elem* buckets[] = {0};
        Elem e1 = {1, 1};
        insert(1, buckets, &e1);
        Elem* e2 = search_n(1, buckets, e1.hval, e1.hn);
        OK(e2 == &e1);
    }
    
    // n == 2 : 
    {
        Elem* buckets[] = {0, 0};
        Elem e1 = {1, 1};
        Elem e2 = {2, 2};
        insert(2, buckets, &e1);
        insert(2, buckets, &e2);
        
        OK(search_n(2, buckets, e1.hval, e1.hn) == &e1);
        OK(search_n(2, buckets, e2.hval, e2.hn) == &e2);
    }
    
    // same hash 
    {
        Elem* buckets[] = {0, 0};
        Elem e1 = {1, 1};
        Elem e2 = {2, 1};
        insert(2, buckets, &e1);
        insert(2, buckets, &e2);
        
        OK(search_n(2, buckets, e1.hval, e1.hn) == &e1);
        OK(search_n(2, buckets, e2.hval, e2.hn) == &e2);
    }

    // now comes the random test cases
    OK(rcheck(1, 10));
    OK(rcheck(2, 10));
    OK(rcheck(3, 30));
    OK(rcheck(4, 40));
    OK(rcheck(5, 50));
    OK(rcheck(6, 60));
    OK(rcheck(7, 70));
    OK(rcheck(8, 80));
    OK(rcheck(9, 90));
    OK(rcheck(10, 100));
    OK(rcheck(50, 500));
    OK(rcheck(100, 1000));
    return 0;
}
