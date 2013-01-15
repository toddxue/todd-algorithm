#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

std::vector<int> array;

void make_factor(int n, int max)
{
    if (n == 1) {
        if (array.size() > 0) {
            printf("%d", array[0]);
            for (int k = 1; k < array.size(); ++k)
                printf(" * %d", array[k]);
            printf("\n");
        }
    }
    else {
        for (int i = max; i >= 2; --i) {
            if (n % i == 0) {
                array.push_back(i);
                make_factor(n/i, i);
                array.pop_back();
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc == 0)
        return 0;

    int number = strtol(argv[1], 0, 10);
    if (number > 0)
        make_factor(number, number);
    return 0;
}

/**

Some plays:

    >play/number/make-multiplication.play 96
    96
    48 * 2
    32 * 3
    24 * 4
    24 * 2 * 2
    16 * 6
    16 * 3 * 2
    12 * 8
    12 * 4 * 2
    12 * 2 * 2 * 2
    8 * 6 * 2
    8 * 4 * 3
    8 * 3 * 2 * 2
    6 * 4 * 4
    6 * 4 * 2 * 2
    6 * 2 * 2 * 2 * 2
    4 * 4 * 3 * 2
    4 * 3 * 2 * 2 * 2
    3 * 2 * 2 * 2 * 2 * 2
    
    
    >play/number/make-multiplication.play 96 | wc -l
    19
    
    >play/number/make-multiplication.play 100 | wc -l
    9
    
    >play/number/make-multiplication.play 22 | wc -l
    2
    
    >play/number/make-multiplication.play 256 | wc -l
    22
    
    >play/number/make-multiplication.play 10000 | wc -l
    109
    
    >play/number/make-multiplication.play 100000 | wc -l
    339
    
    >play/number/make-multiplication.play 1000000 | wc -l
    1043
    
    >time play/number/make-multiplication.play 1000000 | wc -l
    1043
    
    real0m0.018s
    user0m0.016s
    sys0m0.005s
    
This beats the source question java one running time (10x more):

    $ time java -cp . PrintFactors 1000000 | wc -l
        1043
    real    0m0.285s
    user    0m0.448s
    sys     0m0.068s

Not necessary better algorithm, only C is just far faster than JAVA. Also several notes:

  1. Factorization is NP problem, so no very efficient algorithms so far found yet
  2. If N = P^n, than we've O(n^2) algorithms using dynamic programming
  3. In the case #2, it's equalivalent to traditional partition problem we've formula from Euler/Hardy/ramanujan
  4. Factoring N first may speed up, will try to see how faster 
  5. This is not a very good question to ask since good solution/understanding is too hard/complicated.

*/
