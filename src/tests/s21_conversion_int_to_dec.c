#include "test.h"

START_TEST(s21_conversion_int_to_dec_1) {
    s21_decimal s21_res;
    int out = s21_from_int_to_decimal(2147483647, &s21_res);
    s21_decimal expect_dec = {{2147483647, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_int_to_dec_2) {
    s21_decimal s21_res;
    int out = s21_from_int_to_decimal(-2147483647, &s21_res);
    s21_decimal expect_dec = {{2147483647, 0, 0, LEFT_BIT}};
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_int_to_dec_3) {
    s21_decimal s21_res;
    int out = s21_from_int_to_decimal(0, &s21_res);
    s21_decimal expect_dec = {{0, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_int_to_dec_4) {
    s21_decimal s21_res;
    int out = s21_from_int_to_decimal(-0, &s21_res);
    s21_decimal expect_dec = {{0, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_int_to_dec_5) {
    s21_decimal s21_res;
    int out = s21_from_int_to_decimal(92354365, &s21_res);
    s21_decimal expect_dec = {{92354365, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_int_to_dec_6) {
    s21_decimal s21_res;
    int out = s21_from_int_to_decimal(-92354365, &s21_res);
    s21_decimal expect_dec = {{92354365, 0, 0, LEFT_BIT}};
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST


Suite *s21_Suite_conversion_int_to_dec() {
    Suite *s;

    s = suite_create("Other int_to_dec unit test");
    
    TCase *tc1_s21_conversion_int_to_dec = tcase_create("int_to_dec_s21_conversion");

    tcase_add_test(tc1_s21_conversion_int_to_dec, s21_conversion_int_to_dec_1);
    tcase_add_test(tc1_s21_conversion_int_to_dec, s21_conversion_int_to_dec_2);
    tcase_add_test(tc1_s21_conversion_int_to_dec, s21_conversion_int_to_dec_3);
    tcase_add_test(tc1_s21_conversion_int_to_dec, s21_conversion_int_to_dec_4);
    tcase_add_test(tc1_s21_conversion_int_to_dec, s21_conversion_int_to_dec_5);
    tcase_add_test(tc1_s21_conversion_int_to_dec, s21_conversion_int_to_dec_6);

    suite_add_tcase(s, tc1_s21_conversion_int_to_dec);
    return s;
}


    // char* f1 = dec_to_str(s21_res);
    // printf("res   || %s\n", f1);
    // free(f1);
    // char* f2 = dec_to_str(expect_dec);
    // printf("exp   || %s\n", f2);
    // free(f2);