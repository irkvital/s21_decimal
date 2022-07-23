#include "./s21_decimal.h"

int s21_is_equal(s21_decimal v1, s21_decimal v2) {
    int out = FALSE;
    centering(&v1, &v2);
    out = s21_is_equal_simple(v1, v2);
    if (out == TRUE && v1.bits[3] == v2.bits[3]) {  // Проверка на знаки
        out = TRUE;
    } else {
        out = FALSE;
    }
    // Если два нуля
    if (v1.bits[0] == 0 && v1.bits[1] == 0 && v1.bits[2] == 0 && v2.bits[0] == 0
                                           && v2.bits[1] == 0 && v2.bits[2] == 0) out = TRUE;
    return out;
}

int s21_is_greater(s21_decimal v1, s21_decimal v2) {
    int out = FALSE;
    int sign_1 = get_bit(v1, 127);
    int sign_2 = get_bit(v2, 127);
    if (sign_1 == sign_2) {
        centering(&v1, &v2);
        out = (sign_1 == PLUS) ? s21_is_greater_simple(v1, v2) : s21_is_greater_simple(v2, v1);
    } else if (sign_1 == PLUS && sign_2 == MINUS) {
        // Если два нуля
        if (v1.bits[0] == 0 && v1.bits[1] == 0 && v1.bits[2] == 0 && v2.bits[0] == 0
                                               && v2.bits[1] == 0 && v2.bits[2] == 0) {
            out = FALSE;
        } else {
            out = TRUE;
        }
    }
    return out;
}

int s21_is_greater_or_equal(s21_decimal v1, s21_decimal v2) {
    int out = FALSE;
    out = s21_is_equal(v1, v2);
    if (out == FALSE) out = s21_is_greater(v1, v2);
    return out;
}