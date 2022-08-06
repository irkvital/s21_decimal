#include "test.h"

START_TEST(s21_compare_greater) {
    
    int len =  sizeof(test_cases) / 16 - 1;

    for (int i = 0; i < len; i++) {
        ck_assert_int_eq(0, s21_is_greater(test_cases[i], test_cases[dec_num - 1]));
    }

    for (int i = 0, j = len; i < len; i++) {
      ck_assert_int_eq(1, s21_is_greater(test_cases[j], test_cases[i]));
  } 

    s21_decimal negative_zero = {{0, 0, 0, 0x80000000}};

    ck_assert_int_eq(0, s21_is_greater(test_cases[3], negative_zero));  

} END_TEST


Suite *s21_Suite_compare_greater() {
    Suite *s;

    s = suite_create("Compare greater unit test");
    
    TCase *tc1_s21_compare_greater = tcase_create("greater_s21_compare");

    tcase_add_test(tc1_s21_compare_greater, s21_compare_greater);

    suite_add_tcase(s, tc1_s21_compare_greater);
    
    return s;
}
