#include "./s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    *result = value;
    int sign = get_bit(value, 127);
    sign = (sign == MINUS) ? (PLUS) : (MINUS);
    put_bit(result, 127, sign);
    int out = (result) ? 0 : 1;
    return out;
}