#include <stdio.h>
#include <math.h>
#include "./s21_decimal.h"


int main() {
    /*
    s21_decimal dec1 = {{6048146, 0, 0, 0}};
    put_exp(&dec1, 4);
    put_bit(&dec1, 127, 1);

    s21_decimal dec2 = {{0, 99759684, 43, 0}};
    put_exp(&dec2, 5);
    put_bit(&dec2, 127, 1);
*/
    s21_decimal dec1 = {{0, 0, 23546767, 0}};
    put_exp(&dec1, 5);
    put_bit(&dec1, 127, 1);

    s21_decimal dec2 = {{0, 0, 0, 0}};
    put_exp(&dec2, 6);
    put_bit(&dec2, 127, 1);
    
    s21_decimal dec3 = {{0, 0, 0, 0}};
    s21_decimal dec4 = {{0, 0, 0, 0}};

    printf("MID %d\n", s21_div(dec1, dec2, &dec4));

    print_bits(dec1);
    print_bits(dec2);
    print_bits(dec3);
    print_bits(dec4);

    char* f1 = dec_to_str(dec1);
    printf("dec1 || %s\n", f1);
    free(f1);

    char* f2 = dec_to_str(dec2);
    printf("dec2 || %s\n", f2);
    free(f2);

    char* f3 = dec_to_str(dec3);
    printf("res1 || %s\n", f3);
    free(f3);

    char* f4 = dec_to_str(dec4);
    printf("%s\n", f4);
    free(f4);

    return 0;
}
