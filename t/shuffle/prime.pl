#! /usr/bin/perl

use strict;
use warnings;

sub is_prime ($) {
    my $n = shift;
    my $factors = qx(factor $n);
    return scalar($factors =~ /^(\d+): (\1)/);
}

sub is_2_primitive_root($) {
    my $p = shift;

    # only 2^($p-1) => 1 
    my $num = 1;
    my $c = 1;
    for (; $c < $p-1; ++$c) {
        $num *= 2;
        $num %= $p;
        last if $num == 1;
    }

    return $c == $p-1;
}


#
# find primes which closest to n (<n), and have 2 as primite root 
#
sub find_prime_with_root_2 ($) {
    my $n = shift;
    $n -= 1;
    
    while ($n > 0) {
        $n -= 2 and next unless is_prime $n;
        $n -= 2 and next unless is_2_primitive_root $n;
        last;
    }
    
    return $n;
}

#
# step1: generate 4, 8, ..., all 2 powers > 2
# 
my @powers; 
{
    my $power = 2;
    for (2..31) {
        $power *= 2;
        push @powers, $power;
    }
}


#
# print 2 power nearby primes which has 2 as primitve root
#
for my $n (@powers) {
    my $p = find_prime_with_root_2 $n;
    print "$n:\t$p\n";
}


__END__

The result of this script
>./prime.pl
4:		3
8:		5
16:		13
32:		29
64:		61
128:		107
256:		227
512:		509
1024:		1019
2048:		2029
4096:		4093
8192:		8179
16384:		16381
32768:		32749
65536:		65371
131072:		131059
262144:		262139
524288:		524269
1048576:	1048573
2097152:	2097133
4194304:	4194187
8388608:	8388587
16777216:	16776989
33554432:	33554371
67108864:	67108859

<-- From here, it becomes very very slow, wront for Artin Conjecture(" 40% prime numbers have 2 as primitive roots")???

