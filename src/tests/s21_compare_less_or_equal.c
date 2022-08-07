#include "test.h"

START_TEST(s21_compare_less_or_equal) {
    
    ck_assert_int_eq(0, s21_is_less_or_equal(test_cases[5], test_cases[2]));
    ck_assert_int_eq(1, s21_is_less_or_equal(test_cases[2], test_cases[6]));
    ck_assert_int_eq(1, s21_is_less_or_equal(test_cases[0], test_cases[0]));

} END_TEST


Suite *s21_Suite_compare_less_or_equal() {
    Suite *s;

    s = suite_create("Compare less_or_equal unit test");
    
    TCase *tc1_s21_compare_less_or_equal = tcase_create("less_or_equal_s21_compare");

    tcase_add_test(tc1_s21_compare_less_or_equal, s21_compare_less_or_equal);

    suite_add_tcase(s, tc1_s21_compare_less_or_equal);
    
    return s;
}
