#include <stdio.h>
#include <math.h>
#include "./s21_decimal.h"

int main() {
    s21_decimal dec = {{(1 << 31), (1 << 30), 2, 3}};
    print_bits(dec);
    putchar('\n');

    put_bit(&dec, 127, 0);
    print_bits(dec);
    return 0;
}
