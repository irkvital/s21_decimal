//
// Created by Nana Daughterless on 6/3/22.
//

#ifndef SRC_COMPARISON_DECIMAL_COMPARISON_H_
#define SRC_COMPARISON_DECIMAL_COMPARISON_H_

#include "../another/decimal_another.h"
#include "../core/decimal_core.h"

typedef enum { false, true } bool;

int s21_is_less(s21_decimal a, s21_decimal b);
int stupid_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int stupid_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

#endif  // SRC_COMPARISON_DECIMAL_COMPARISON_H_
