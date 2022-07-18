#include "./s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {  // ДОБАВИТЬ ОБРАБОТКУ ОШИБОК
    char* tmp = dec_to_str(src);
    *dst = strtof(tmp, NULL); // (float)atof(tmp)
    printf("st %s\n", tmp);
    free(tmp);
    return 0;
}