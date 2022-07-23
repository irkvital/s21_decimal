#include "./s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int out = 0;
    for (int i = 0; i < 3; i++) result->bits[i] = 0;
    centering(&value_1, &value_2);
    int sign_1 = get_bit(value_1, 127);
    int sign_2 = get_bit(value_2, 127);
    int sign   = PLUS;
    if (sign_1 == sign_2) {
        out = s21_add_simple(value_1, value_2, result);
        if (sign_1 == MINUS) sign = MINUS;
    } else {
        if (s21_is_greater_or_equal_simple(value_1, value_2)) {
            s21_sub_simple(value_1, value_2, result);
            if (sign_1 == MINUS) sign = MINUS;
        } else {
            s21_sub_simple(value_2, value_1, result);
            if (sign_1 == PLUS) sign = MINUS;
        }
    }
    put_bit(result, 127, sign);
    put_exp(result, get_exp(value_1));
    if (out != 0 && sign == MINUS) out = 2;
    return out;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_negate(value_2, &value_2);
    int out = s21_add(value_1, value_2, result);
    return out;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int out = 0;
    centering(&value_1, &value_2);
    out = s21_mul_simple(value_1, value_2, result);

    int tmp_1 = get_bit(value_1, 127);
    int tmp_2 = get_bit(value_2, 127);
    int tmp_res = tmp_1 ^ tmp_2;  // Исключающее или
    put_bit(result, 127, tmp_res);

    tmp_1 = get_exp(value_1);
    tmp_2 = get_exp(value_2);
    tmp_res = tmp_1 + tmp_2;
    put_exp(result, tmp_res);
    out = (tmp_res > 28) ? 2 : out;
    return out;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int out = 0;
    if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
        out = 3;  //    n / 0 = error
    } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0) {
        for (int i = 0; i < 4; i++) result->bits[i] = 0; //   0 / n = 0
    } else {
        centering(&value_1, &value_2);
        if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
        out = 1;  //    Число слишком велико
        }
        if (!out) out = s21_div_full_bits(value_1, value_2, result);
    }
    int sign_1 = get_bit(value_1, 127);
    int sign_2 = get_bit(value_2, 127);
    int sign = sign_1 ^ sign_2;  // Исключающее или
    put_bit(result, 127, sign);
    return out;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int out = 0;
    centering(&value_1, &value_2);
    *result = s21_div_simple(value_1, value_2, &value_2);
    put_bit(result, 127, get_bit(value_1, 127));
    return out;  // Что-то доделать надо
}