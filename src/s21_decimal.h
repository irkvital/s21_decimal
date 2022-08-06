#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MINUS   1
#define PLUS    0

#define TRUE    1
#define FALSE   0
#define MAX_EXP 28
#define LEFT_BIT (1 << 31)
#define  MAX_INT (unsigned)4294967295

// bits[0] - младшие биты 0-31
// bits[1] - средние биты 32-63
// bits[2] - старшие биты 64-95
// bits[3] - 96-111 нули, 112-119 показатели степени, 120-126 нули, 127 знак ('0' - '+')
typedef struct {
    int bits[4];
} s21_decimal;

#define DEC_TEN (s21_decimal) {{10, 0, 0, 0}}
#define DEC_TWO (s21_decimal) {{2, 0, 0, 0}}
#define DEC_NUL (s21_decimal) {{0, 0, 0, 0}}


// Арифметические операторы. Возвращают: 0 - ок, 1 - велико или +INF, 2 - мало или -INF, 3 - деление на 0

    int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
    int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
    int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
    int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
    int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);


// Операторы сравнения. Возвращают: 0 - FALSE, 1 - TRUE

    int s21_is_less(s21_decimal value_1, s21_decimal value_2);
    int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
    int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
    int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
    int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
    int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

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

// Вспомогательные функции

    int shift_left(s21_decimal* dec);
    int shift_right(s21_decimal* dec);
    int signific_bits(s21_decimal dec);  // Количество значащих битов
    int s21_is_equal_simple(s21_decimal value_1, s21_decimal value_2);
    int s21_is_greater_simple(s21_decimal value_1, s21_decimal value_2);
    int s21_is_greater_or_equal_simple(s21_decimal value_1, s21_decimal value_2);
    int get_bit(s21_decimal dec, int bit_num);
    void put_bit(s21_decimal* dec, int bit_num, int bit);
    void print_bits(s21_decimal dec);
    void put_exp(s21_decimal* dec, int exp);
    int get_exp(s21_decimal dec);
    char* dec_to_str(s21_decimal dec);

    int s21_add_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
    int s21_sub_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
    int s21_mul_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
    // Возвращает остаток от деления (без учета знака и степеней)
    s21_decimal s21_div_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
    int s21_div_full_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
    void centering(s21_decimal* value_1, s21_decimal* value_2);
    void centering_simple(s21_decimal* value_1, s21_decimal* value_2, int exp_1, int exp_2);
    int str_to_dec(char str[], s21_decimal* dec);
    int scale(float);
    void div_bank_round(s21_decimal* value, int flag);

#endif  // SRC_S21_DECIMAL_H_
