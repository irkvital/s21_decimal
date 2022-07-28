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
    s21_decimal dec1 = {{0, MAX_INT, 429496722, 0}};
    put_exp(&dec1, 25);
    put_bit(&dec1, 127, 0);

    s21_decimal dec2 = {{7856454637, 0, MAX_INT, 0}};
    put_exp(&dec2, 20);
    put_bit(&dec2, 127, 0);
    
    // s21_decimal dec3 = {{0, 0, 0, 0}};
    s21_decimal dec4 = {{0, 0, 0, 0}};



// Формирование 10^10. Потом заменить дефайном или ручками прописать
    s21_decimal dec10 = DEC_TEN;
    for (int i = 1; i < 10; i++) {
        s21_mul_simple(dec10, DEC_TEN, &dec10);
    }

    int exp1 = get_exp(dec1);
    int exp2 = get_exp(dec2);
    s21_decimal tmp = DEC_NUL;
    s21_decimal res = DEC_NUL;
// Формирование 3х слагаемых каждого множителя
    s21_decimal deca[3];
    s21_decimal decb[3];
    deca[2] = dec1;
    decb[2] = dec2;
    for (int i = 2; i >= 0; i--) {
        if (i > 0) {
            deca[i] = s21_div_simple(deca[i], dec10, &deca[i - 1]);
            decb[i] = s21_div_simple(decb[i], dec10, &decb[i - 1]);
        }
        put_exp(&deca[i], exp1);
        put_exp(&decb[i], exp2);
        exp1 -= 10;
        exp2 -= 10;
        char* f2 = dec_to_str(deca[i]);
        printf("DECA %d || %s\n", i, f2);
        free(f2);
        char* f3 = dec_to_str(decb[i]);
        printf("DECb %d || %s\n", i, f3);
        free(f3);
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int expa = get_exp(deca[i]);
            int expb = get_exp(decb[j]);
            s21_mul_simple(deca[i], decb[j], &tmp);
            put_exp(&tmp, expa + expb);

        char* ff = dec_to_str(deca[i]);
        printf("DECA|| %s\n", ff);
        free(ff);
        char* fd = dec_to_str(decb[j]);
        printf("DECB|| %s\n", fd);
        free(fd);

        char* f1 = dec_to_str(res);
        printf("RES || %s\n", f1);
        free(f1);

            s21_add(res, tmp, &res);

        char* f2 = dec_to_str(tmp);
        printf("TMP || %s\n", f2);
        free(f2);
        printf("EXP %d\n", get_exp(tmp));
        char* f3 = dec_to_str(res);
        printf("RES || %s\n\n", f3);
        free(f3);
        }
    }


    // char* a1 = dec_to_str(deca[1]);
    // printf("DEC 2 || %s\n", a1);
    // free(a1);

    // char* a2 = dec_to_str(deca[2]);
    // printf("DEC 3 || %s\n", a2);
    // free(a2);


    // printf("MID %d\n", s21_mul(dec1, dec2, &dec4));
    // deca2 = s21_div_simple(dec1, dec14, &deca1);
    // decb2 = s21_div_simple(dec2, dec14, &decb1);
    // int exp1 = get_exp(dec1);
    // int exp2 = get_exp(dec2);
    // put_exp(&deca1, exp1 - 14);
    // put_exp(&decb1, exp2 - 14);
    // put_exp(&deca2, exp1);
    // put_exp(&decb2, exp2);

    // s21_mul(deca2, decb2, &res);
    // s21_mul(deca1, decb2, &tmp);
    // s21_add(res, tmp, &res);
    // s21_mul(deca2, decb1, &tmp);
    // s21_add(res, tmp, &res);
    // s21_mul(deca1, decb1, &tmp);
    // s21_add(res, tmp, &res);


    print_bits(dec1);
    print_bits(dec2);
    // print_bits(dec3);
    // print_bits(dec4);

    char* f1 = dec_to_str(dec1);
    printf("dec1 || %s\n", f1);
    free(f1);

    char* f2 = dec_to_str(dec2);
    printf("dec2 || %s\n", f2);
    free(f2);

    // char* f3 = dec_to_str(dec10);
    // printf("MUL  || %s\n", f3);
    // free(f3);

    // char* f4 = dec_to_str(decb2);
    // printf("res1 || %s\n", f4);
    // free(f4);

    char* f5 = dec_to_str(res);
    printf("%s\n", f5);
    free(f5);
    return 0;
}


// 6277101733925.1791261777244234
//          0000.0000003271620816583974375