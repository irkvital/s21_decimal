#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_


#include <check.h>
#include "../s21_decimal.h"
#define dec_num 17




static const s21_decimal test_cases[dec_num] = {
{{100, 0, 0, 0x80010000}}, 
{{2147483647, 2147483647, 2147483647, 0x801C0000}},         //min decimal, exp = 28, sign = 1
{{1513252461, 1236723423, 0, 0x80140000}},                  //exp = 20, sign = 1                       //exp = 1, sign = 1
{{0, 0, 0, 0}},
{{125617186, 1231257813, 124416171, 0x1C0000}},
{{10, 0, 0, 0}},                               
{{100, 0, 0, 0}},
{{2147483647, 0, 0, 0}},
{{1000, 10, 0, 0}},
{{10000, 100, 0, 0}},
{{2012561778, 21474, 0, 0}},
{{2147483647, 21474123, 0, 0}},
{{200000, 30000, 4000, 0x50000}},                           //exp = 5 
{{2147483647, 2147483647, 0, 0}},
{{444000, 555500, 6660, 0}},
{{2147483647, 2147483647, 2147483647, 0}},
};


static const float result_conversion_to_float[dec_num] = {
-10.000000,
-3.961408,
-0.053117,
0.000000,
0.229507,
10.000000,
100.000000,
2147483648.000000,
42949672960.000000,
429496729600.000000,
92232140980224.000000,
92230660290248704.000000,
737869746455707648.000000,
9223372036854775808.000000,
122855315530905613762560.000000,
39614081257132168796771975168.000000,
};

Suite *s21_Suite_compare_equal();
Suite *s21_Suite_compare_greater();
Suite *s21_Suite_compare_greater_or_equal();
Suite *s21_Suite_compare_less();
Suite *s21_Suite_compare_less_or_equal();
Suite *s21_Suite_compare_is_not_equal();

Suite *s21_Suite_operators_add();
Suite *s21_Suite_operators_sub();
Suite *s21_Suite_operators_mul();
Suite *s21_Suite_operators_div();
Suite *s21_Suite_operators_mod();

Suite *s21_Suite_other_floor();
Suite *s21_Suite_other_round();
Suite *s21_Suite_other_negate();
Suite *s21_Suite_other_truncate();

Suite *s21_Suite_conversion_int_to_dec();
Suite *s21_Suite_conversion_float_to_dec();
Suite *s21_Suite_conversion_dec_to_float();
Suite *s21_Suite_conversion_dec_to_int();



#endif  // SRC_TESTS_TEST_H_
