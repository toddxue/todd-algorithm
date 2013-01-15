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

