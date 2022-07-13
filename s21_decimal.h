#ifndef SRC_S21_DECIMAL_H
#define SRC_S21_DECIMAL_H

#include <stdio.h>
#include <math.h>
// #include <stdlib.h>
// #include <limits.h>
// #include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_EXP 28

// bits[0] - младшие биты 0-31
// bits[1] - средние биты 32-63
// bits[2] - старшие биты 64-95
// bits[3] - 0-15 нули, 16-23 показатели степени, 24-30 нули, 31 знак ('0' - '+')
typedef struct 
{
    int bits[4];
} s21_decimal;

// Арифметические операторы. Возвращают: 0 - ок, 1 - велико или +INF, 2 - мало или -INF, 3 - деление на 0

    int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
    int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
    int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
    int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
    int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);


// Операторы сравнения. Возвращают: 0 - FALSE, 1 - TRUE

    int s21_is_less(s21_decimal, s21_decimal);
    int s21_is_less_or_equal(s21_decimal, s21_decimal);
    int s21_is_greater(s21_decimal, s21_decimal);
    int s21_is_greater_or_equal(s21_decimal, s21_decimal);
    int s21_is_equal(s21_decimal, s21_decimal);
    int s21_is_not_equal(s21_decimal, s21_decimal);

// Преобразователи. Возвращают: 0 - OK, 1 - ошибка конвертации

    int s21_from_int_to_decimal(int src, s21_decimal *dst);
    int s21_from_float_to_decimal(float src, s21_decimal *dst);
    int s21_from_decimal_to_int(s21_decimal src, int *dst);
    int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Другие функции. Возвращают: 0 - OK, 1 - ошибка вычисления

    int s21_floor(s21_decimal value, s21_decimal *result);
    int s21_round(s21_decimal value, s21_decimal *result);
    int s21_truncate(s21_decimal value, s21_decimal *result);
    int s21_negate(s21_decimal value, s21_decimal *result);






#endif //  SRC_S21_DECIMAL_H