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
    *result = DEC_NUL;
    int out = 0, exp = get_exp(value), sign = get_bit(value, 127);
    s21_decimal fract = DEC_NUL;
    s21_decimal one = {{1, 0, 0, 0}};
    s21_decimal half_one = {{5, 0, 0, 0}};
    put_exp(&half_one, 1);
    if (exp > 0 && exp <= 28) {
            s21_mod(value, one, &fract);
            s21_sub(value, fract, result);
            if (sign) s21_negate(half_one, &half_one);
            if (s21_is_greater_or_equal(fract, half_one) && !sign) {
                s21_add(*result, one, result);
            } else if (s21_is_less_or_equal(fract, half_one) && sign) {
                s21_sub(*result, one, result);
            }
    } else if (exp == 0) {
        *result = value;
    } else { out = 1; }

    return out;
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
