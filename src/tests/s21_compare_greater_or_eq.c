#include "test.h"

START_TEST(s21_compare_greater_or_equal) {
    
        ck_assert_int_eq(0,s21_is_greater_or_equal(test_cases[2], test_cases[5]));
        ck_assert_int_eq(1, s21_is_greater_or_equal(test_cases[5], test_cases[5]));
        ck_assert_int_eq(1, s21_is_greater_or_equal(test_cases[7], test_cases[5]));


} END_TEST


Suite *s21_Suite_compare_greater_or_equal() {
    Suite *s;

    s = suite_create("Compare greater_or_equal unit test");
    
    TCase *tc1_s21_compare_greater_or_equal = tcase_create("greater_or_equal_s21_compare");

    tcase_add_test(tc1_s21_compare_greater_or_equal, s21_compare_greater_or_equal);

    suite_add_tcase(s, tc1_s21_compare_greater_or_equal);
    
    return s;
}
