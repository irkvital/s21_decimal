#include <stdio.h>
#include <math.h>
#include "./s21_decimal.h"

#define  MAX_INT 4294967295

int main() {
    // /*
    s21_decimal dec = {{178125, 0, 0, 0}};
    // put_sign(&dec, MINUS);
    put_exp(&dec, 3);
    put_bit(&dec, 127, MINUS);
    // put_bit(&dec, 3, 0);
    print_bits(dec);
    // char* f = dec_to_str(dec);
    // printf("%s\n", f);
    // free(f);
    float fl = 0;
    s21_from_decimal_to_float(dec, &fl);
    printf("fl %.28f\n", fl);
    // */

    // char s[50] = "-0000000000000000000000000000127.55";
    // float ss = strtof(s, NULL); // (float)atof(s)
    // float fl = -00127.55;
    // printf("%.40f\n", ss);
    // printf("%.40f\n", fl);

    return 0;
}
