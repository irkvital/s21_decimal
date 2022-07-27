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

// int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//     int out = 0;
//     int tmp_1 = get_bit(value_1, 127);
//     int tmp_2 = get_bit(value_2, 127);
//     int sign_res = tmp_1 ^ tmp_2;  // Исключающее или
//     put_bit(result, 127, sign_res);

//     centering(&value_1, &value_2);

//     tmp_1 = get_exp(value_1);
//     tmp_2 = get_exp(value_2);
//     int exp_res = tmp_1 + tmp_2;
//     put_exp(result, exp_res);

//     out = s21_mul_simple(value_1, value_2, result);
//     if (out == 0) {
//         out = (exp_res > 28) ? 2 : out;
//     } else {
//         // Формирования децимала при +inf и -inf
//         for (int i = 0; i < 3; i++) result->bits[i] = MAX_INT;
//         put_exp(result, 0);
//         if (sign_res == PLUS) {
//             put_bit(result, 127, PLUS);
//         } else {
//             put_bit(result, 127, MINUS);
//             out = 2;
//         }
//     }
//     return out;
// }

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int out = 0;
    int tmp_1 = get_bit(value_1, 127);
    int tmp_2 = get_bit(value_2, 127);
    int sign_res = tmp_1 ^ tmp_2;  // Исключающее или
    put_bit(result, 127, sign_res);

    s21_decimal dt_1 = {{0 ,0 ,0 ,0}};
    s21_decimal dt_2 = {{0 ,0 ,0 ,0}};

    // Деление на 10 для избежания переполнения при больших дробных частях
    tmp_1 = signific_bits(value_1);
    tmp_2 = signific_bits(value_2);
    int exp_1 = get_exp(value_1);
    int exp_2 = get_exp(value_2);
    while (tmp_1 + tmp_2 > 96 && (exp_1 > 0 || exp_2 > 0)) {
        if (tmp_1 > 1 && exp_1 >= exp_2) {
            dt_1 = div_ten(&value_1);
            exp_1 = get_exp(value_1);
        } else if (exp_2 > 0) {
            dt_2 = div_ten(&value_2);
            exp_2 = get_exp(value_2);
        }
        tmp_1 = signific_bits(value_1);
        tmp_2 = signific_bits(value_2);
    }
    if (dt_1.bits[0] >= 5) s21_add(value_1, dt_1, &value_1);
    if (dt_2.bits[0] >= 5) s21_add(value_2, dt_2, &value_2);

    int exp_res = exp_1 + exp_2;
    put_exp(result, exp_res);

    out = s21_mul_simple(value_1, value_2, result);
    if (out == 0) {
        out = (exp_res > 28) ? 2 : 0;
    } else {
        // Формирования децимала при +inf и -inf
        for (int i = 0; i < 3; i++) result->bits[i] = MAX_INT;
        put_exp(result, 0);
        if (sign_res == PLUS) {
            put_bit(result, 127, PLUS);
            out = 1;
        } else {
            put_bit(result, 127, MINUS);
            out = 2;
        }
    }
    return out;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int out = 0;
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