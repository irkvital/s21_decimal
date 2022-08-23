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

// int s21_from_float_to_decimal(float src, s21_decimal *dst) {
//     *dst = DEC_NUL;
//     int res = 0;
//     int scale_f = scale(src);
//     if (abs(scale_f) <= 95) {
//         int decimal_exp = 0;
//         int bit_count = 31;
//         unsigned int fbits = *((unsigned int*)&src);
//         if (!!(0x80000000 & fbits))
//             put_bit(dst, 127, 1);
//         fbits <<= 8;

//         for (unsigned int mask = 0x80000000, i = 23; mask; mask >>= 1, i--) {
//             if (i == 23) {
//                 put_bit(dst, i, 1);
//             } else if (!!(fbits&mask)) {
//                 put_bit(dst, i, 1);
//             } else {
//                 put_bit(dst, i, 0); }
//         }

//         if (scale_f > 23) {
//             for (int i = scale_f - 23; i > 0; i--)
//                 shift_left(dst);
//         } else {
//             for (int mask = 0b1, i = 23; !(mask & dst->bits[0]) && i > scale_f ; dst->bits[0] >>= 1)
//                 i--;
//         }

//         while (!get_bit(*dst, bit_count) && bit_count >= 0)
//             bit_count--;

//         for (int i = 0; i < bit_count - scale_f; i++) {
//             s21_mul(*dst, DEC_TEN, dst);
//             if (!get_bit(*dst, 0))
//                 shift_right(dst);
//             decimal_exp++;
//             }

//         put_exp(dst, decimal_exp);
//     } else { res = 1; }

// return res;
// }


int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int error = 0;
    int binaryScale = 0;
    bool minus = false;
    if (src < 0) {
        minus = true;
        src = -src;
    }
    unsigned int fbits = *((unsigned int *)&src);
    double number_double = (double)src;
    *dst = DEC_NUL;
    binaryScale = getBinaryExp(fbits);
    if (isinf(src) || isnan(src)) {
        error = 1;
    } else {
        if (number_double != 0.0) {
            int scale = 0;
            for (; !(int)(number_double / 1E7); number_double *= 10) scale += 1;
            number_double = (float)number_double;
            while (fmod(number_double, 10.0) == 0 && scale > 0) {
                number_double = number_double / 10;
                scale -= 1;
            }
            if (scale <= 28 && (binaryScale + 1 > -95 && binaryScale + 1 <= 95)) {
                src = number_double;
                unsigned int fbits = *((unsigned int *)&src);
                binaryScale = getBinaryExp(fbits);
                setMantissa(dst, binaryScale);
                if (src != 1) {
                    setFloat(dst, binaryScale, fbits);
                }
                for (int i = 1; i <= scale; i++) {
                    ChangeDegree(1, &dst->bits[3]);
                }
                if (minus == true) {
                    dst->bits[3] |= LEFT_BIT;
                }
            } else {
                error = 1;
            }
        }
    }
    return error;
}

int getBinaryExp(unsigned int fbits) {
    int scale = 7;
    unsigned int mask = 0b01000000000000000000000000000000;
    int sum = 0;
    for (int i = 0; i <= 7; i++) {
        if (fbits & mask) {
            sum = sum + pow(2, scale);
        }
        mask >>= 1;
        scale = scale - 1;
    }
    return sum - 127 - 1;
}

void setMantissa(s21_decimal *dst, int binaryScale) {
    binaryScale = binaryScale + 1;
    unsigned int mask = 1;
    for (int i = 0; i < binaryScale % 32; i++) {
        mask <<= 1;
    }
    if (binaryScale >= 0 && binaryScale <= 31) {
        dst->bits[0] = dst->bits[0] | mask;
    }
    if (binaryScale >= 32 && binaryScale <= 63) {
        dst->bits[1] = dst->bits[1] | mask;
    }
    if (binaryScale >= 64 && binaryScale <= 95) {
        dst->bits[2] = dst->bits[2] | mask;
    }
}

void setFloat(s21_decimal *dst, int binaryScale, unsigned int fbits) {
    unsigned int maskFloat = 0b00000000010000000000000000000000;
    while (binaryScale > -2) {
        unsigned int mask = 1;
        for (int i = 0; i < binaryScale % 32; i++) {
            mask <<= 1;
        }
        if (binaryScale <= 31) {
            if (fbits & maskFloat) {
                dst->bits[0] = dst->bits[0] | mask;
            }
        }
        if (binaryScale >= 32 && binaryScale <= 63) {
            if (fbits & maskFloat) {
                dst->bits[1] = dst->bits[1] | mask;
            }
        }
        if (binaryScale >= 64 && binaryScale <= 95) {
            if (fbits & maskFloat) {
                dst->bits[2] = dst->bits[2] | mask;
            }
        }
        mask >>= 1;
        maskFloat >>= 1;
        binaryScale = binaryScale - 1;
    }
}

void ChangeDegree(int sign, int *num) {
    if (num) {
        int sign_num = 0;
        if (CheckRigtBit(*num)) {
            sign_num = 1;
        }
        *num = *num >> 16;
        if (sign) {
            *num += 1;
        } else {
            *num -= 1;
        }
        *num = *num << 16;
        if (sign_num) {
            *num = *num | 1;
        }
    }
}

int CheckRigtBit(int num) {
    int res = 0;
    if (num & 0b00000000000000000000000000000001) {
        res = 1;
    }
    return res;
}
