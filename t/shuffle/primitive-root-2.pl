#! /usr/bin/perl

#
# Todd Xue at Fri Dec 21 14:39:40 PST 2012
#
# Reference:
#   1. GNU coreutils factor command: The Pollard Rho algorithm
#   2. Primes p Such That 2 is a Primitive Root Modulo p: http://homepages.math.uic.edu/~rfuller/primroot2.pdf
#
# Ideally with 64 bit Perl, we can get all primes close to 2^1, ..., 2^63, 2^64
# 

use strict;
use warnings;

#
# pick out a faster one to decide if an integer is an prime
#
sub is_prime_v1 ($) {
    my $n = shift;
    my $m = sqrt $n;
    for my $i (2..$n) {
        last if $i > $m;
        return 0 if $n % $i == 0;
    }
    return 1;
}
sub is_prime_v2 ($) {
    my $n = shift;
    my $factors = qx(factor $n);
    return scalar($factors =~ /^(\d+): (\1)/);
}
sub is_prime ($) { return is_prime_v2 $_[0]; }


#
# this version becomes very slow when $p become large, eg. > 134217541
# 
sub is_2_primitive_root($) {
    my $p = shift;

    #printf "%20s is_2_primitive_root $p\n", " ";

    # only 2^($p-1) => 1 
    my $num = 1;
    my $c = 1;
    for (; $c < $p-1; ++$c) {
        $num *= 2;
        $num %= $p;
        last if $num == 1;
    }

    #printf "%20s is_2_primitive_root $p done\n", " ";
    return $c == $p-1;
}


#
# find primes which closest to n (<n), and have 2 as primite root 
#
sub find_prime_with_root_2 ($) {
    my $n = shift;
    $n -= 1;
    
    for (; $n > 0; $n -= 2) {
        next unless is_prime $n;

        #
        # when < 2^^20, performance is not a problem, choose the closest one
        #
        if ($n < 1048576) {
            next unless is_2_primitive_root $n;
            last;
        }

        # 
        # this one used to speed up:
        #
        # If p is a prime of the form p = 4q + 1 for some odd prime q,
        # then 2 is a primitive root modulo p.
        # 
        next unless $n % 4 == 1;
        my $q = ($n-1)/4;
        next unless is_prime $q;

        # 
        # math proofs shows $n already has primitive root 2
        # uncomment this to do a verification
        #
        #print "$n = 4*$q+1 -- not 2 primitive root\n" and next unless is_2_primitive_root $n;

        last;
    }
    return $n;
}

#
# step1: generate 4, 8, ..., all 2 powers > 2
# 
our @powers;
{
    my $power = 2;
    for (2..50) {
        $power *= 2;
        push @powers, $power;
    }
}


#
# print 2 power nearby primes which has 2 as primitve root
#
printf "%-5s %20s: %-20s%20s\n", "K", "POWER(2,K)", "Close Prime with Root 2", "Difference";
my $power = 2;
for my $n (@powers) {
    my $p = find_prime_with_root_2 $n;
    printf "%-5d %20d: %-20d%20d\n", $power, $n, $p, ($n-$p);
    ++$power;
}


__END__

the result of this script
>./prime.pl
K               POWER(2,K): Close Prime with Root 2          Difference
2                        4: 3                                      1
3                        8: 5                                      3
4                       16: 13                                     3
5                       32: 29                                     3
6                       64: 61                                     3
7                      128: 107                                   21
8                      256: 227                                   29
9                      512: 509                                    3
10                    1024: 1019                                   5
11                    2048: 2029                                  19
12                    4096: 4093                                   3
13                    8192: 8179                                  13
14                   16384: 16381                                  3
15                   32768: 32749                                 19
16                   65536: 65371                                165
17                  131072: 131059                                13
18                  262144: 262139                                 5
19                  524288: 524269                                19
20                 1048576: 1048573                                3
21                 2097152: 2096789                              363
22                 4194304: 4193789                              515
23                 8388608: 8386949                             1659
24                16777216: 16776989                             227
25                33554432: 33552749                            1683
26                67108864: 67108109                             755
27               134217728: 134215349                           2379
28               268435456: 268435109                            347
29               536870912: 536869637                           1275
30              1073741824: 1073740517                          1307
31              2147483648: 2147483477                           171
32              4294967296: 4294966877                           419
33              8589934592: 8589932237                          2355
34             17179869184: 17179867709                         1475
35             34359738368: 34359735629                         2739
36             68719476736: 68719475549                         1187
37            137438953472: 137438953349                         123
38            274877906944: 274877906477                         467
39            549755813888: 549755809469                        4419
40           1099511627776: 1099511625677                       2099
41           2199023255552: 2199023255477                         75
42           4398046511104: 4398046493837                      17267
43           8796093022208: 8796093021917                        291
44          17592186044416: 17592186041117                      3299
45          35184372088832: 35184372084077                      4755
46          70368744177664: 70368744175949                      1715
47         140737488355328: 140737488354557                      771
48         281474976710656: 281474976706349                     4307
49         562949953421312: 562949953418837                     2475
50        1125899906842624: 1125899906841653                     971
