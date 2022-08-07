#include "./s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int out = 0;
    *result = DEC_NUL;
    centering(&value_1, &value_2);
    int exp1 = get_exp(value_1);
    int exp2 = get_exp(value_2);
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
    if (out != 0 && exp1 && exp2) {
        s21_div_simple(value_1, DEC_TEN, &value_1);
        s21_div_simple(value_2, DEC_TEN, &value_2);
        put_exp(&value_1, exp1 - 1);
        put_exp(&value_2, exp2 - 1);
        out = s21_add(value_1, value_2, result);
    }
    return out;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    *result = DEC_NUL;
    s21_negate(value_2, &value_2);
    int out = s21_add(value_1, value_2, result);
    return out;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int out = 0;
    *result = DEC_NUL;
    int sign_res = get_bit(value_1, 127) ^ get_bit(value_2, 127);  // Исключающее или
    s21_decimal dec10 = {{1410065408, 2, 0, 0}};   // Число 10^10
    int exp1 = get_exp(value_1);
    int exp2 = get_exp(value_2);
    int exp, flag = 0;
    s21_decimal tmp = DEC_NUL;
    // Формирование 3х слагаемых каждого множителя
    s21_decimal deca[3];
    s21_decimal decb[3];
    deca[2] = value_1;
    decb[2] = value_2;
    for (int i = 2; i >= 0; i--) {
        if (i > 0) {
            deca[i] = s21_div_simple(deca[i], dec10, &deca[i - 1]);
            decb[i] = s21_div_simple(decb[i], dec10, &decb[i - 1]);
        }
        put_exp(&deca[i], exp1);
        put_exp(&decb[i], exp2);
        exp1 -= 10;
        exp2 -= 10;
    }
    // Попарное перемножение слагаемых и суммирование
    for (int i = 2; i >= 0; i--) {
        for (int j = 2; j >= 0; j--) {
            exp1 = get_exp(deca[i]);
            exp2 = get_exp(decb[j]);
            out += s21_mul_simple(deca[i], decb[j], &tmp);
            exp = exp1 + exp2;
            put_exp(&tmp, exp);
            out += s21_add(*result, tmp, result);
        }
    }
    // Домножение числа на 10, если экспонента больше 28
    exp = get_exp(*result);
    while (exp > 28) {
        exp--;
        flag = 1;
        s21_decimal tmp = s21_div_simple(*result, DEC_TEN, result);
        s21_decimal tmp_end = s21_div_simple(*result, DEC_TEN, &tmp_end);
        if (tmp.bits[0] > 5 || (tmp.bits[0] == 5 && tmp_end.bits[0] % 2 == 1)) {
        tmp.bits[0] = 1;
        s21_add_simple(*result, tmp, result);
    }
        put_exp(result, exp);
    }

    put_bit(result, 127, sign_res);
    if (out || get_exp(*result) < 0) {
        out = (sign_res == MINUS) ? 2 : 1;
    } else if (flag && result->bits[0] == 0 && result->bits[1] == 0 && result->bits[2] == 0) {
        out = 2;
    }
    return out;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int out = 0;
    *result = DEC_NUL;
    if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
        out = 3;  //    n / 0 = error
    } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0) {
        for (int i = 0; i < 4; i++) result->bits[i] = 0;  //   0 / n = 0
    } else {
        out = s21_div_full_bits(value_1, value_2, result);
    }
    int sign_1 = get_bit(value_1, 127);
    int sign_2 = get_bit(value_2, 127);
    int sign = sign_1 ^ sign_2;  // Исключающее или
    put_bit(result, 127, sign);
    if (out == 1 && sign == MINUS) out = 2;
    return out;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    *result = DEC_NUL;
    if (value_2.bits[0] != 0 || value_2.bits[1] != 0 || value_2.bits[2] != 0) {
        centering(&value_1, &value_2);
        *result = s21_div_simple(value_1, value_2, &value_2);
        put_bit(result, 127, get_bit(value_1, 127));
    }
    return 0;
}
