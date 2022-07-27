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
    s21_decimal dec1 = {{0, 0, 50549865, 0}};
    put_exp(&dec1, 25);
    put_bit(&dec1, 127, 0);

    s21_decimal dec2 = {{0, 0, MAX_INT, 0}};
    put_exp(&dec2, 25);
    put_bit(&dec2, 127, 0);
    
    // s21_decimal dec3 = {{0, 0, 0, 0}};
    s21_decimal dec4 = {{0, 0, 0, 0}};

    s21_decimal dec14 = DEC_TEN;
    for (int i = 1; i < 14; i++) {
        s21_mul_simple(dec14, DEC_TEN, &dec14);
    }

    s21_decimal deca1 = {{0, 0, 0, 0}};
    s21_decimal deca2 = {{0, 0, 0, 0}};
    s21_decimal decb1 = {{0, 0, 0, 0}};
    s21_decimal decb2 = {{0, 0, 0, 0}};
    s21_decimal tmp = {{0, 0, 0, 0}};
    s21_decimal res = {{0, 0, 0, 0}};

    printf("MID %d\n", s21_mul(dec1, dec2, &dec4));
    deca2 = s21_div_simple(dec1, dec14, &deca1);
    decb2 = s21_div_simple(dec2, dec14, &decb1);
    int exp1 = get_exp(dec1);
    int exp2 = get_exp(dec2);
    put_exp(&deca1, exp1 - 14);
    put_exp(&decb1, exp2 - 14);
    put_exp(&deca2, exp1);
    put_exp(&decb2, exp2);

    s21_mul(deca2, decb2, &res);
    s21_mul(deca1, decb2, &tmp);
    s21_add(res, tmp, &res);
    s21_mul(deca2, decb1, &tmp);
    s21_add(res, tmp, &res);
    s21_mul(deca1, decb1, &tmp);
    s21_add(res, tmp, &res);


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

    char* f3 = dec_to_str(dec4);
    printf("MUL  || %s\n", f3);
    free(f3);

    // char* f4 = dec_to_str(decb2);
    // printf("res1 || %s\n", f4);
    // free(f4);

    char* f5 = dec_to_str(res);
    printf("%s\n", f5);
    free(f5);
    return 0;
}
