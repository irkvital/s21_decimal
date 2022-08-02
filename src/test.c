#include <stdio.h>
#include <math.h>
#include "./s21_decimal.h"


int main() {
    s21_decimal dec1 = DEC_NUL;
    // char strinp1[32] = "-1801765452";
    // str_to_dec(strinp1, &dec1);
    float f = 533834287383478009856.0;
    s21_from_float_to_decimal(f, &dec1);

    // s21_decimal dec2 = DEC_NUL;
    // char strinp2[32] = "71780112248297297370296977550";
    // str_to_dec(strinp2, &dec2);

    // s21_decimal dec3 = {{0, 0, 0, 0}};
    // s21_decimal dec4 = {{0, 0, 0, 0}};

    // printf("MID %d\n", s21_mul(dec1, dec2, &dec4));
    // printf("MID %d\n", s21_mul(dec1, dec2, &dec4));

    print_bits(dec1);
    // print_bits(dec2);
    // print_bits(dec3);
    // print_bits(dec4);
    printf("FLOAT   %f\n", f);
    char* f1 = dec_to_str(dec1);
    printf("dec1 || %s\n", f1);
    free(f1);

    // char* f2 = dec_to_str(dec2);
    // printf("dec2 || %s\n", f2);
    // free(f2);

    // char* f3 = dec_to_str(dec3);
    // printf("DEC3  || %s\n", f3);
    // free(f3);
    // print_bits(dec3);

    // char* f4 = dec_to_str(dec4);
    // printf("%s    || RES\n", f4);
    // free(f4);

    return 0;
}
