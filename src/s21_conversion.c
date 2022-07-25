#include "./s21_decimal.h"
#define hint 2147483648
#define lint -2147483649

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
    int res = 0;
    char* tmp = dec_to_str(src);     
    long int tmp_res = (int)strtod(tmp, NULL);
    free(tmp);
    if (tmp_res > hint && tmp_res < lint) {
        res = 1;
    } else {
        *dst = tmp_res; }
    return res;
}


int s21_from_int_to_decimal(int src, s21_decimal* dst){
    unsigned int out = hint - src + 1;
    dst->bits[0] = out;
    


//    int mod, full = src, flag = 0;
//    if (src < hint && src > lint) {
//        if (src < 0)
//            put_bit(dst, 127, 1);
//        src = abs(src);
//        for(int i = 0; full; i++) {
//            full = src / 2;
//            mod = src % 2;
//            src = full;
//            put_bit(dst, i, mod);
//        }
//    } else { flag = 1; } 
return out;
}
