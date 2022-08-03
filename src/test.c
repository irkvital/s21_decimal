#include "./s21_decimal.h"
#include <time.h>

int rand_dec(s21_decimal* dec);

int main() {
    srand(time(NULL));
    s21_decimal dec1 = DEC_NUL;
    s21_decimal dec2 = DEC_NUL;
    s21_decimal dec_res = DEC_NUL;

    // rand_dec(&dec1);
    // rand_dec(&dec2);
    str_to_dec("-236815656264883769144748.57204", &dec1);
    str_to_dec("00000.000005284694888333416396", &dec2);

    s21_div(dec1, dec2, &dec_res);
    int exp = get_exp(dec_res);

    char* strdec1 = dec_to_str(dec1);
    char* strdec2 = dec_to_str(dec2);

    char str[120];
    sprintf(str, "python3 1.py %s %s %d > 1.txt", strdec1, strdec2, exp);
    system(str);

    char res_py[32];
    FILE *fp;
    if (fp = fopen("1.txt", "r")) {
        fgets(res_py, 32, fp);
        fclose(fp);
    }

// PRINT
    char* f1 = dec_to_str(dec1);
    printf("dec1   || %s\n", f1);
    free(f1);
    char* f2 = dec_to_str(dec2);
    printf("dec2   || %s\n", f2);
    free(f2);
    char* f3 = dec_to_str(dec_res);
    printf("21_res || %s\n", f3);
    free(f3);
    printf("py_res || %s\n", res_py);




    free(strdec1);
    free(strdec2);

    return 0;
}



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