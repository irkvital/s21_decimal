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


int s21_is_less(s21_decimal v1, s21_decimal v2) {
    int out = FALSE, flag = 0;
    int sign_1 = get_bit(v1, 127), sign_2 = get_bit(v2, 127);
    if (sign_1 == sign_2) {
        centering(&v1, &v2);
        for (int byte = 2; byte >= 0 && flag == 0; byte--) {
            if ((unsigned)v1.bits[byte] > (unsigned)v2.bits[byte]) {
                if (!sign_1)
                    out = FALSE, flag = 1;
                else
                    out = TRUE, flag = 1;
            } else if ((unsigned)v1.bits[byte] < (unsigned)v2.bits[byte]) {
                if (!sign_1)
                    out = TRUE, flag = 1;
                else
                    out = FALSE, flag = 1;
            } else if (byte == 0 && flag == 0) {
                    out = FALSE;
                    }
        }
    } else if (!sign_1) {
            out = FALSE;
    } else if (sign_1) {
            out = TRUE;
    }
return out;
}


int s21_is_less_or_equal(s21_decimal v1, s21_decimal v2) {
    int out = s21_is_equal(v1, v2);
    out += s21_is_less(v1, v2);
    out = out > 0 ? 1 : 0;
return out;
}


int s21_is_not_equal(s21_decimal v1, s21_decimal v2) {
return !s21_is_equal(v1, v2);
}

