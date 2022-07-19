#include <stdio.h>
#include <math.h>
#include "./s21_decimal.h"

#define  MAX_INT 4294967295

int main() {
    /*
    s21_decimal dec = {{4294967295, 0, 0, 0}};
    // put_sign(&dec, MINUS);
    put_exp(&dec, 0);
    put_bit(&dec, 127, MINUS);
    // put_bit(&dec, 3, 0);
    // print_bits(dec);
    // char* f = dec_to_str(dec);
    // printf("%s\n", f);
    // free(f);
    float fl = 0;
    s21_from_decimal_to_float(dec, &fl);
    printf("fl %.28f\n", fl);
    */

    s21_decimal dec1 = {{1, 1, 0, 0}};
    s21_decimal dec2 = {{8, 0, 0, 0}};
    s21_decimal dec3 = {{0, 0, 0, 0}};

    s21_sub_simple(dec1, dec2, &dec3);
    print_bits(dec1);
    print_bits(dec2);
    print_bits(dec3);

    char* f1 = dec_to_str(dec1);
    printf("%s\n", f1);
    free(f1);

    char* f2 = dec_to_str(dec2);
    printf("%s\n", f2);
    free(f2);

    char* f3 = dec_to_str(dec3);
    printf("%s\n", f3);
    free(f3);

    return 0;
}
