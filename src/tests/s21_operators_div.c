#include "test.h"

START_TEST(s21_operators_div_1) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("2.5243548972949849530023662694", &expect_dec);
    s21_div(test_cases[0], test_cases[1], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_div_2) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("74.579100391790955807048384204", &expect_dec);
    s21_div(test_cases[1], test_cases[2], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_div_3) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-0", &expect_dec);
    s21_div(test_cases[2], test_cases[3], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_div_4) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("0", &expect_dec);
    s21_div(test_cases[3], test_cases[4], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_div_5) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("0.0229507327035609621809468317", &expect_dec);
    s21_div(test_cases[4], test_cases[5], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_div_6) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("10", &expect_dec);
    s21_div(test_cases[6], test_cases[5], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_div_7) {
    s21_decimal expect_dec, s21_res, a_dec, b_dec;
    str_to_dec("-0.000000000000000000000001", &a_dec);
    str_to_dec("-0.000000000000000000000001", &b_dec);
    str_to_dec("1", &expect_dec);
    s21_div(a_dec, b_dec, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_div_8) {
    s21_decimal expect_dec, s21_res, a_dec, b_dec;
    str_to_dec("197973011418281765692961951.58", &a_dec);
    str_to_dec("1269854.873", &b_dec);
    str_to_dec("155902076392852308007.76865750", &expect_dec);
    s21_div(a_dec, b_dec, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));

} END_TEST

Suite *s21_Suite_operators_div() {
    Suite *s;

    s = suite_create("Operators div unit test");
    
    TCase *tc1_s21_operators_div = tcase_create("div_s21_operators");

    tcase_add_test(tc1_s21_operators_div, s21_operators_div_1);
    tcase_add_test(tc1_s21_operators_div, s21_operators_div_2);
    tcase_add_test(tc1_s21_operators_div, s21_operators_div_3);
    tcase_add_test(tc1_s21_operators_div, s21_operators_div_4);
    tcase_add_test(tc1_s21_operators_div, s21_operators_div_5);
    tcase_add_test(tc1_s21_operators_div, s21_operators_div_6);
    tcase_add_test(tc1_s21_operators_div, s21_operators_div_7);
    tcase_add_test(tc1_s21_operators_div, s21_operators_div_8);

    suite_add_tcase(s, tc1_s21_operators_div);
    
    return s;
}


    // char* f1 = dec_to_str(s21_res);
    // printf("res   || %s\n", f1);
    // free(f1);
    // char* f2 = dec_to_str(expect_dec);
    // printf("exp   || %s\n", f2);
    // free(f2);