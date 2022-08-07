#include "test.h"

START_TEST(s21_compare_less) {
    
    ck_assert_int_eq(0, s21_is_less(test_cases[5], test_cases[2]));
    ck_assert_int_eq(1,  s21_is_less(test_cases[2], test_cases[6]));
    ck_assert_int_eq(0,  s21_is_less(test_cases[0], test_cases[0]));

} END_TEST


Suite *s21_Suite_compare_less() {
    Suite *s;

    s = suite_create("Compare less unit test");
    
    TCase *tc1_s21_compare_less = tcase_create("less_s21_compare");

    tcase_add_test(tc1_s21_compare_less, s21_compare_less);

    suite_add_tcase(s, tc1_s21_compare_less);
    
    return s;
}
