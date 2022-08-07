#include "./s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int out = 0;
    char* tmp = dec_to_str(src);
    *dst = strtof(tmp, NULL);
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
    if (src.bits[1] || src.bits[2]) {
        res = 1;
    } else {
        *dst = tmp_res;
    }
    return res;
}


int s21_from_int_to_decimal(int src, s21_decimal* dst) {
    *dst = DEC_NUL;
    unsigned int out;
    if (src < 0) {
        out = - src;
        put_bit(dst, 127, MINUS);
    } else {
        out = src;
        put_bit(dst, 127, PLUS);
    }
    dst->bits[0] = out;
return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    *dst = DEC_NUL;
    int res = 0;
    int scale_f = scale(src);
    if (abs(scale_f) <= 95) {
        int decimal_exp = 0;
        int bit_count = 31;
        unsigned int fbits = *((unsigned int*)&src);
        if (!!(0x80000000 & fbits))
            put_bit(dst, 127, 1);
        fbits <<= 8;

        for (unsigned int mask = 0x80000000, i = 23; mask; mask >>= 1, i--) {
            if (i == 23) {
                put_bit(dst, i, 1);
            } else if (!!(fbits&mask)) {
                put_bit(dst, i, 1);
            } else {
                put_bit(dst, i, 0); }
        }

        if (scale_f > 23) {
            for (int i = scale_f - 23; i > 0; i--)
                shift_left(dst);
        } else {
            for (int mask = 0b1, i = 23; !(mask & dst->bits[0]) && i > scale_f ; dst->bits[0] >>= 1)
                i--;
        }

        while (!get_bit(*dst, bit_count) && bit_count >= 0)
            bit_count--;

        for (int i = 0; i < bit_count - scale_f; i++) {
            s21_mul(*dst, DEC_TEN, dst);
            if (!get_bit(*dst, 0))
                shift_right(dst);
            decimal_exp++;
            }

        put_exp(dst, decimal_exp);
    } else { res = 1; }

return res;
}
