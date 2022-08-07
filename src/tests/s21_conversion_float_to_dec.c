#include "test.h"

START_TEST(s21_conversion_float_to_dec_1) {
    s21_decimal expect_dec, s21_res;
    float fl = 0.123456789;
    int out = s21_from_float_to_decimal(fl, &s21_res);
    str_to_dec("0.1234567910432815551757812500", &expect_dec);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_float_to_dec_2) {
    s21_decimal expect_dec, s21_res;
    float fl = -0.123456789;
    int out = s21_from_float_to_decimal(fl, &s21_res);
    str_to_dec("-0.1234567910432815551757812500", &expect_dec);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_float_to_dec_3) {
    s21_decimal s21_res;
    float fl = 79228162514264337593543950335.;
    int out = s21_from_float_to_decimal(fl, &s21_res);
    ck_assert_int_eq(1, out);
} END_TEST

START_TEST(s21_conversion_float_to_dec_4) {
    s21_decimal expect_dec, s21_res;
    float fl = -79228102514064307593543900330.;
    int out = s21_from_float_to_decimal(fl, &s21_res);
    str_to_dec("-79228101123500060288156172288", &expect_dec);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_float_to_dec_5) {
    s21_decimal expect_dec, s21_res;
    float fl = 0.00000000000000000000000000000001;
    int out = s21_from_float_to_decimal(fl, &s21_res);
    str_to_dec("0", &expect_dec);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(1, out);
} END_TEST

START_TEST(s21_conversion_float_to_dec_6) {
    s21_decimal expect_dec, s21_res;
    float fl = 258763864865.78657838;
    int out = s21_from_float_to_decimal(fl, &s21_res);
    str_to_dec("258763866112.0", &expect_dec);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST


Suite *s21_Suite_conversion_float_to_dec() {
    Suite *s;

    s = suite_create("Other float_to_dec unit test");
    
    TCase *tc1_s21_conversion_float_to_dec = tcase_create("float_to_dec_s21_conversion");

    tcase_add_test(tc1_s21_conversion_float_to_dec, s21_conversion_float_to_dec_1);
    tcase_add_test(tc1_s21_conversion_float_to_dec, s21_conversion_float_to_dec_2);
    tcase_add_test(tc1_s21_conversion_float_to_dec, s21_conversion_float_to_dec_3);
    tcase_add_test(tc1_s21_conversion_float_to_dec, s21_conversion_float_to_dec_4);
    tcase_add_test(tc1_s21_conversion_float_to_dec, s21_conversion_float_to_dec_5);
    tcase_add_test(tc1_s21_conversion_float_to_dec, s21_conversion_float_to_dec_6);

    suite_add_tcase(s, tc1_s21_conversion_float_to_dec);
    return s;
}


    // char* f1 = dec_to_str(s21_res);
    // printf("res   || %s\n", f1);
    // free(f1);
    // char* f2 = dec_to_str(expect_dec);
    // printf("exp   || %s\n", f2);
    // free(f2);