#include "test.h"

START_TEST(s21_conversion_dec_to_float_1) {
    s21_decimal dec;
    float expect_fl = 0.123456789;
    float result_fl;
    str_to_dec("0.1234567910432815551757812500", &dec);
    int out = s21_from_decimal_to_float(dec, &result_fl);
    ck_assert_int_eq(1, (result_fl == expect_fl));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_dec_to_float_2) {
    s21_decimal dec;
    float expect_fl = -0.123456789;
    float result_fl;
    str_to_dec("-0.1234567910432815551757812500", &dec);
    int out = s21_from_decimal_to_float(dec, &result_fl);
    ck_assert_int_eq(1, (result_fl == expect_fl));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_dec_to_float_3) {
    s21_decimal dec;
    float expect_fl = -79228102514064307593543900330.;
    float result_fl;
    str_to_dec("-79228101123500060288156172287", &dec);
    int out = s21_from_decimal_to_float(dec, &result_fl);
    ck_assert_int_eq(1, (result_fl == expect_fl));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_dec_to_float_4) {
    s21_decimal dec;
    float expect_fl = 258763864865.78657838;
    float result_fl;
    str_to_dec("258763866112.0", &dec);
    int out = s21_from_decimal_to_float(dec, &result_fl);
    ck_assert_int_eq(1, (result_fl == expect_fl));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_dec_to_float_5) {
    s21_decimal dec;
    float expect_fl = 0;
    float result_fl;
    str_to_dec("0", &dec);
    int out = s21_from_decimal_to_float(dec, &result_fl);
    ck_assert_int_eq(1, (result_fl == expect_fl));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_dec_to_float_6) {
    s21_decimal dec;
    float expect_fl = 79228162514264337593543950336.;
    float result_fl;
    str_to_dec("79228162514264337593543950335", &dec);
    int out = s21_from_decimal_to_float(dec, &result_fl);
    ck_assert_int_eq(1, (result_fl == expect_fl));
    ck_assert_int_eq(0, out);
} END_TEST


Suite *s21_Suite_conversion_dec_to_float() {
    Suite *s;

    s = suite_create("Other dec_to_float unit test");
    
    TCase *tc1_s21_conversion_dec_to_float = tcase_create("dec_to_float_s21_conversion");

    tcase_add_test(tc1_s21_conversion_dec_to_float, s21_conversion_dec_to_float_1);
    tcase_add_test(tc1_s21_conversion_dec_to_float, s21_conversion_dec_to_float_2);
    tcase_add_test(tc1_s21_conversion_dec_to_float, s21_conversion_dec_to_float_3);
    tcase_add_test(tc1_s21_conversion_dec_to_float, s21_conversion_dec_to_float_4);
    tcase_add_test(tc1_s21_conversion_dec_to_float, s21_conversion_dec_to_float_5);
    tcase_add_test(tc1_s21_conversion_dec_to_float, s21_conversion_dec_to_float_6);

    suite_add_tcase(s, tc1_s21_conversion_dec_to_float);
    return s;
}


    // char* f1 = dec_to_str(s21_res);
    // printf("res   || %s\n", f1);
    // free(f1);
    // char* f2 = dec_to_str(expect_dec);
    // printf("exp   || %s\n", f2);
    // free(f2);