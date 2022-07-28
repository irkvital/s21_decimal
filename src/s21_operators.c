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
    s21_decimal dec10 = {{1410065408, 2, 0, 0}};
    int exp1 = get_exp(value_1);
    int exp2 = get_exp(value_2);
    s21_decimal tmp = DEC_NUL;
    *result = DEC_NUL;
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
            int expa = get_exp(deca[i]);
            int expb = get_exp(decb[j]);
            s21_mul_simple(deca[i], decb[j], &tmp);
            put_exp(&tmp, expa + expb);
            s21_add(*result, tmp, result);
        }
    }
}

// int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//     int out = 0;
//     for (int i = 0; i < 4; i++) result->bits[i] = 0;
//     int sign_res = get_bit(value_1, 127) ^ get_bit(value_2, 127);  // Исключающее или
//     put_bit(result, 127, sign_res);
//     put_bit(&value_1, 127, sign_res);
//     put_bit(&value_2, 127, sign_res);
//     s21_decimal dec_tmp = {{0, 0, 0, 0}};
//     // if (s21_mul_simple(value_1, DEC_TEN, &dec_tmp)) {
//     //     int exp = get_exp(value_1);
//     //     exp--;
//     //     s21_div_simple(value_1, DEC_TEN, &value_1);
//     //     put_exp(&value_1, exp);
//     // }
//     int exp_1 = get_exp(value_1);
//     int exp_2 = get_exp(value_2);
//     int exp_res = exp_1 + exp_2;

//     do {
//         dec_tmp = s21_div_simple(value_2, DEC_TEN, &value_2);   // Получение цифры
//         s21_mul_simple(value_1, dec_tmp, &dec_tmp);  // Умножение первого числа на цифру разряда второго
//         put_exp(&dec_tmp, exp_res);
//         s21_add(*result, dec_tmp, result);
//         exp_res--;
//     } while ((value_2.bits[0] != 0 || value_2.bits[1] != 0 || value_2.bits[2] != 0) && exp_res >= 0);
//     return out;
// }

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int out = 0;
    for (int i = 0; i < 3; i++) result->bits[i] = 0;
    if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
        out = 3;  //    n / 0 = error
    } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0) {
        for (int i = 0; i < 4; i++) result->bits[i] = 0; //   0 / n = 0
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
    int out = 0;
    centering(&value_1, &value_2);
    *result = s21_div_simple(value_1, value_2, &value_2);
    put_bit(result, 127, get_bit(value_1, 127));
    return out;  // Что-то доделать надо
}