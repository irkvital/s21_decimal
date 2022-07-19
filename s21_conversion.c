#include "./s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int out = 0;
    char* tmp = dec_to_str(src);
    *dst = strtof(tmp, NULL); // (float)atof(tmp)
    if (tmp) {
        free(tmp);
    } else {
        out = 1;
    }
    return out;
}