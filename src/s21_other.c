#include "./s21_decimal.h"


int s21_negate(s21_decimal value, s21_decimal *result) {
    *result = value;
    int sign = get_bit(value, 127);
    sign = (sign == MINUS) ? (PLUS) : (MINUS);
    put_bit(result, 127, sign);
    int out = (result) ? 0 : 1;
    return out;
}


int s21_floor(s21_decimal value, s21_decimal *result) {
    *result = DEC_NUL;
    int exp = get_exp(value), out = 0, flag = 0;
    s21_decimal fract = DEC_NUL;
    s21_decimal one = {{1, 0, 0, 0}};
    put_bit(&one, 127, 1);
    if (get_bit(value, 127))
        put_bit(result, 127, 1);

    if (exp > 0 && exp <= 28) {
        while (exp-- > 0) {
            fract = s21_div_simple(value, DEC_TEN, result);
            if (s21_is_not_equal(fract, DEC_NUL)) flag = 1;
            value = *result;
            put_exp(result, exp);
        }
    } else if (exp == 0) {
        *result = value;
    } else { out = 1; }

    if (get_bit(value, 127) && flag)
        s21_add(*result, one, result);
    return out;
}

int s21_round(s21_decimal value, s21_decimal *result) {
    int sign = get_bit(value, 127);
    s21_decimal base = {0}, mul = {0}, one = {0};
    s21_decimal copy = value;
    s21_truncate(value, result);
    s21_from_int_to_decimal(10, &base);
    s21_from_int_to_decimal(1, &one);
    int degree = get_exp(value);

    if (degree != 0)
        degree--;
    while (degree != 0) {
        s21_div_simple(value, base, &value);
        degree--;
    }
    mul = s21_div_simple(value, base, &value);
    if (mul.bits[0] >= 5 && !s21_is_equal(copy, *result)) {
        s21_add_simple(*result, one, result);
    }
    put_bit(result, 127, sign);
    return 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
    *result = DEC_NUL;
    int exp = get_exp(value), out = 0;
    if (get_bit(value, 127))
        put_bit(result, 127, 1);

    if (exp > 0 && exp <= 28) {
        while (exp-- > 0) {
            s21_div_simple(value, DEC_TEN, &value);
        }
        *result = value;
        put_exp(result, 0);
    } else if (exp == 0) {
        *result = value;
    } else { out = 1; }
    return out;
}
