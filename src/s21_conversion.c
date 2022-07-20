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


int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int flag = 0;
    char* tmp;
   for (int i = 32; i < 96; i++) {
        if (get_bit(src, i)) {
            printf("huge val\n");
            return 1;
            flag = 1;
            break;
            }
        }
    
    if (flag == 0)
        tmp = dec_to_str(src);
        *dst = strtof(tmp, NULL);
/*        if (get_bit(src, 127)) {
            (*dst) *= 1;
            printf("catch sign\n");
            }*/
    return 0;
}
