#include <stdio.h>
#include <math.h>
#include "./s21_decimal.h"

int main() {
    // s21_decimal dec = {{2, (1 << 30), 2, 3}};
    s21_decimal dec = {{0, 0, 0, 0}};
    print_bits(dec);

    put_sign(&dec, MINUS);
    put_exp(&dec, 1);
    // put_bit(&dec, 0, 1);
    // put_bit(&dec, 3, 0);
    print_bits(dec);
    return 0;
}
