#include <stdio.h>
#include <math.h>
#include "./s21_decimal.h"


int main() {
    s21_decimal dec1 = {{0, MAX_INT, 1474967220, 0}};
    put_exp(&dec1, 25);
    put_bit(&dec1, 127, 0);

    s21_decimal dec2 = {{785645463, 0, MAX_INT, 0}};
    put_exp(&dec2, 20);
    put_bit(&dec2, 127, 0);
    
    // s21_decimal dec3 = {{0, 0, 0, 0}};
    s21_decimal dec4 = {{0, 0, 0, 0}};

    printf("MID %d\n", s21_mul(dec1, dec2, &dec4));

    print_bits(dec1);
    print_bits(dec2);
    // print_bits(dec3);
    print_bits(dec4);

    char* f1 = dec_to_str(dec1);
    printf("dec1 || %s\n", f1);
    free(f1);

    char* f2 = dec_to_str(dec2);
    printf("dec2 || %s\n", f2);
    free(f2);

    // char* f3 = dec_to_str(dec3);
    // printf("DEC3  || %s\n", f3);
    // free(f3);
    // print_bits(dec3);

    char* f4 = dec_to_str(dec4);
    printf("res1 || %s\n", f4);
    free(f4);

    return 0;
}
