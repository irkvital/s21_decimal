#include "./s21_decimal.h"

int s21_is_equal(s21_decimal v1, s21_decimal v2) {
    int out = FALSE;
    centering(&v1, &v2);
    out = s21_is_equal_simple(v1, v2);
    if (out == TRUE && v1.bits[3] == v2.bits[3]) {
        out = TRUE;
    } else {
        out = FALSE;
    }
    // Если два нуля
    if (v1.bits[0] == 0 && v1.bits[1] == 0 && v1.bits[2] == 0 && v2.bits[0] == 0
                                           && v2.bits[1] == 0 && v2.bits[2] == 0) out = TRUE;
    return out;
}