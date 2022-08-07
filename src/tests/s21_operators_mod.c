#include "test.h"

START_TEST(s21_operators_mod_1) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-2.077183750418240648446056858", &expect_dec);
    s21_mod(test_cases[0], test_cases[1], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_mod_2) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-0.0307599982442639407169715711", &expect_dec);
    s21_mod(test_cases[1], test_cases[2], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_mod_3) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("0", &expect_dec);
    s21_mod(test_cases[2], test_cases[3], &s21_res);
        ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_mod_4) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("0", &expect_dec);
    s21_mod(test_cases[3], test_cases[4], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_mod_5) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("0.229507327035609621809468317", &expect_dec);
    s21_mod(test_cases[4], test_cases[5], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_mod_6) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("0", &expect_dec);
    s21_mod(test_cases[6], test_cases[5], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_mod_7) {
    s21_decimal expect_dec, s21_res, a_dec, b_dec;
    str_to_dec("-385964.28330307537203556736209", &a_dec);
    str_to_dec("-78964982.38092437071", &b_dec);
    str_to_dec("-385964.283303075372035567362", &expect_dec);
    s21_mod(a_dec, b_dec, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST


Suite *s21_Suite_operators_mod() {
    Suite *s;

    s = suite_create("Operators mod unit test");
    
    TCase *tc1_s21_operators_mod = tcase_create("mod_s21_operators");

    tcase_add_test(tc1_s21_operators_mod, s21_operators_mod_1);
    tcase_add_test(tc1_s21_operators_mod, s21_operators_mod_2);
    tcase_add_test(tc1_s21_operators_mod, s21_operators_mod_3);
    tcase_add_test(tc1_s21_operators_mod, s21_operators_mod_4);
    tcase_add_test(tc1_s21_operators_mod, s21_operators_mod_5);
    tcase_add_test(tc1_s21_operators_mod, s21_operators_mod_6);
    tcase_add_test(tc1_s21_operators_mod, s21_operators_mod_7);

    suite_add_tcase(s, tc1_s21_operators_mod);
    
    return s;
}


    // char* f1 = dec_to_str(s21_res);
    // printf("res   || %s\n", f1);
    // free(f1);
    // char* f2 = dec_to_str(expect_dec);
    // printf("exp   || %s\n", f2);
    // free(f2);