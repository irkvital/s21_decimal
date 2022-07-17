#include <stdio.h>
#include <math.h>
#include "./s21_decimal.h"

int main() {
    // s21_decimal dec = {{2, (1 << 30), 2, 3}};
    s21_decimal dec = {{0, 1, 2, 3}};
    print_bits(dec);
    // putchar('\n');

    put_bit(&dec, 1, 1);
    print_bits(dec);
    return 0;
}
