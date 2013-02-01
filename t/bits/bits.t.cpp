#include "TAP.h"
#include "bits.h"

typedef bits::uint uint;
static bool swap_test(uint a, uint b) { 
    uint a2 = a; 
    uint b2 = b;
    bits::swap(a2, b2);
    return a2 == b && b2 == a;
}


int main(int argc, char* argv[]) {
    OK_SUM();

    OK(bits::add(0, 0) == 0);
    OK(bits::add(1, 0) == 1);
    OK(bits::add(0, 1) == 1);
    OK(bits::add(1, 1) == 2);
    OK(bits::add(1, 2) == 3);
    OK(bits::add(1, 3) == 4);
    OK(bits::add(123, 456) == 579);

    OK(bits::gt(123, 456) == false);
    OK(bits::lt(123, 456) == true);

    OK(bits::gt(456, 123) == true);
    OK(bits::lt(456, 123) == false);

    OK(bits::max(123, 456) == 456);
    OK(bits::min(123, 456) == 123);
    OK(bits::max(456, 123) == 456);
    OK(bits::min(456, 123) == 123);

    OK(swap_test(0, 0));
    OK(swap_test(1, 0));
    OK(swap_test(0, 0));
    OK(swap_test(1, 1));

    OK(swap_test(1, 2));

    OK(swap_test(123, 456));
    OK(swap_test(456, 123));

    OK(bits::is_2_power(0));
    OK(bits::is_2_power(1));
    OK(bits::is_2_power(2));
    OK(bits::is_2_power(4));
    OK(bits::is_2_power(1024));
    OK(bits::is_2_power(2147483648));

    OK(!bits::is_2_power(2+1));
    OK(!bits::is_2_power(4+1));
    OK(!bits::is_2_power(1024+1));
    OK(!bits::is_2_power(2147483648+1));

    OK(!bits::is_2_power(4+2));
    OK(!bits::is_2_power(1024+512));
    OK(!bits::is_2_power(2147483648+1024));

    OK(bits::log2(1) == 0);
    OK(bits::log2(2) == 1);
    OK(bits::log2(3) == 1);
    OK(bits::log2(4) == 2);
    OK(bits::log2(5) == 2);
    OK(bits::log2(6) == 2);
    OK(bits::log2(7) == 2);
    OK(bits::log2(8) == 3);
    OK(bits::log2(1024) == 10);
    OK(bits::log2(1025) == 10);

    OK(bits::number_of_bit1(0) == 0);
    OK(bits::number_of_bit1(1) == 1);
    OK(bits::number_of_bit1(2) == 1);
    OK(bits::number_of_bit1(3) == 2);
    OK(bits::number_of_bit1(7) == 3);
    OK(bits::number_of_bit1(15) == 4);

    
    OK(bits::right_most_1_pos(0) == 32);
    OK(bits::right_most_1_pos(1) == 0);
    OK(bits::right_most_1_pos(2) == 1);
    OK(bits::right_most_1_pos(3) == 0);
    OK(bits::right_most_1_pos(4) == 2);
    OK(bits::right_most_1_pos(6) == 1);

    OK(bits::next_smallest(1) == 2);
    OK(bits::next_smallest(2) == 4);
    OK(bits::next_smallest(3) == 5);
    OK(bits::next_smallest(5) == 6);

    OK(bits::prev_largest(2) == 1);
    OK(bits::prev_largest(4) == 2);
    OK(bits::prev_largest(5) == 3);
    OK(bits::prev_largest(6) == 5);

    return 0;
}
