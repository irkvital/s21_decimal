#include "./s21_decimal.h"
#include <time.h>

int rand_dec(s21_decimal* dec);

int main() {
    srand(time(NULL));
    s21_decimal dec1 = DEC_NUL;
    s21_decimal dec2 = DEC_NUL;
    s21_decimal dec_res = DEC_NUL;

    int out = 0;
    int count = 0;
    do {
        // rand_dec(&dec1);
        // rand_dec(&dec2);
        str_to_dec("-915073219.9895412674", &dec1);
        str_to_dec("-3672.9655592003221437500522486", &dec2);

        s21_div(dec1, dec2, &dec_res);
        int exp = get_exp(dec_res);

        char* strdec1 = dec_to_str(dec1);
        char* strdec2 = dec_to_str(dec2);

        char str[120];
        sprintf(str, "python3 1.py %s %s %d > 1.txt", strdec1, strdec2, exp);
        system(str);

        char res_py[32];
        FILE *fp;
        if ((fp = fopen("1.txt", "r"))) {
            fgets(res_py, 32, fp);
            fclose(fp);
        }

    // PRINT
        char* f3 = dec_to_str(dec_res);
        out = strncmp(f3, res_py, strlen(res_py) - 1);
        count++;
        if (out) {
            printf("dec1   || %s\n", strdec1);
            printf("dec2   || %s\n", strdec2);
            printf("21_res || %s\n", f3);
            printf("py_res || %s\n\n", res_py);
        }
        free(strdec1);
        free(strdec2);
        free(f3);
    } while (out == 0 && count < 1);
    printf("COUNT %d\n", count);

    return 0;
}

// int main() {
//     srand(time(NULL));
//     s21_decimal dec1 = DEC_NUL;
//     s21_decimal dec2 = DEC_NUL;
//     s21_decimal dec_res = DEC_NUL;

//         str_to_dec("-906908.0538779339260", &dec1);
//         str_to_dec("24152593779688908674270663.781", &dec2);

//         printf("%d\n", s21_mul(dec1, dec2, &dec_res));
//         int exp = get_exp(dec_res);
//         printf("exp %d\n", exp);


//     // PRINT
//         char* f1 = dec_to_str(dec1);
//         printf("dec1   || %s\n", f1);
//         free(f1);
//         char* f2 = dec_to_str(dec2);
//         printf("dec2   || %s\n", f2);
//         free(f2);
//         char* f3 = dec_to_str(dec_res);
//         printf("21_res || %s\n", f3);
//         free(f3);

//     return 0;
// }


int rand_dec(s21_decimal* dec) {
    int exp = rand() % 29;
    int sign = rand() % 2;
    int max = rand() % 3;
    *dec = DEC_NUL;
    for (int i = 0; i <= max; i++) {
        dec->bits[i] = rand() % MAX_INT;
    }
    put_bit(dec, 127, sign);
    put_exp(dec, exp);
    return exp;
}