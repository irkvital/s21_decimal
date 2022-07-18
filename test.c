#include <stdio.h>
#include <math.h>
#include "./s21_decimal.h"

#define  MAX_INT 4294967295

int main() {
    s21_decimal dec = {{MAX_INT, MAX_INT, MAX_INT, 0}};
    // put_sign(&dec, MINUS);
    put_exp(&dec, 28);
    put_bit(&dec, 127, MINUS);
    // put_bit(&dec, 3, 0);
    print_bits(dec);
    print_dec(dec);
    return 0;
}
