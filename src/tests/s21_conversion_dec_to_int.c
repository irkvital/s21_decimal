#include "test.h"

START_TEST(s21_conversion_dec_to_int_1) {
    s21_decimal dec;
    int expect_int = 0;
    int result_int;
    str_to_dec("0", &dec);
    int out = s21_from_decimal_to_int(dec, &result_int);
    ck_assert_int_eq(1, (result_int == expect_int));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_dec_to_int_2) {
    s21_decimal dec;
    int expect_int = -12345;
    int result_int;
    str_to_dec("-12345.99999", &dec);
    int out = s21_from_decimal_to_int(dec, &result_int);
    ck_assert_int_eq(1, (result_int == expect_int));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_dec_to_int_3) {
    s21_decimal dec;
    int expect_int = 2147483647;
    int result_int;
    str_to_dec("2147483647", &dec);
    int out = s21_from_decimal_to_int(dec, &result_int);
    ck_assert_int_eq(1, (result_int == expect_int));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_dec_to_int_4) {
    s21_decimal dec;
    int expect_int = -2147483647;
    int result_int;
    str_to_dec("-2147483647", &dec);
    int out = s21_from_decimal_to_int(dec, &result_int);
    ck_assert_int_eq(1, (result_int == expect_int));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_dec_to_int_5) {
    s21_decimal dec;
    int expect_int = 987532;
    int result_int;
    str_to_dec("987532.45", &dec);
    int out = s21_from_decimal_to_int(dec, &result_int);
    ck_assert_int_eq(1, (result_int == expect_int));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_conversion_dec_to_int_6) {
    s21_decimal dec;
    int result_int;
    str_to_dec("79228162514264337593543950335", &dec);
    int out = s21_from_decimal_to_int(dec, &result_int);
    ck_assert_int_eq(1, out);
} END_TEST


Suite *s21_Suite_conversion_dec_to_int() {
    Suite *s;

    s = suite_create("Other dec_to_int unit test");
    
    TCase *tc1_s21_conversion_dec_to_int = tcase_create("dec_to_int_s21_conversion");

    tcase_add_test(tc1_s21_conversion_dec_to_int, s21_conversion_dec_to_int_1);
    tcase_add_test(tc1_s21_conversion_dec_to_int, s21_conversion_dec_to_int_2);
    tcase_add_test(tc1_s21_conversion_dec_to_int, s21_conversion_dec_to_int_3);
    tcase_add_test(tc1_s21_conversion_dec_to_int, s21_conversion_dec_to_int_4);
    tcase_add_test(tc1_s21_conversion_dec_to_int, s21_conversion_dec_to_int_5);
    tcase_add_test(tc1_s21_conversion_dec_to_int, s21_conversion_dec_to_int_6);

    suite_add_tcase(s, tc1_s21_conversion_dec_to_int);
    return s;
}


    // char* f1 = dec_to_str(s21_res);
    // printf("res   || %s\n", f1);
    // free(f1);
    // char* f2 = dec_to_str(expect_dec);
    // printf("exp   || %s\n", f2);
    // free(f2);