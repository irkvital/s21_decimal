#include "test.h"

START_TEST(s21_other_negate_1) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-6.03859187520912032422302842", &s21_res);
    str_to_dec("6.03859187520912032422302842", &expect_dec);
    int out = s21_negate(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_negate_2) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-3908291258215925.5090869715711", &s21_res);
    str_to_dec("3908291258215925.5090869715711", &expect_dec);
    int out = s21_negate(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_negate_3) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-0.05311686657495426669", &s21_res);
    str_to_dec("0.05311686657495426669", &expect_dec);
    int out = s21_negate(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_negate_4) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("2295073270.356096218094683170", &s21_res);
    str_to_dec("-2295073270.356096218094683170", &expect_dec);
    int out = s21_negate(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_negate_5) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("9.99999999999999999999", &s21_res);
    str_to_dec("-9.99999999999999999999", &expect_dec);
    int out = s21_negate(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_negate_6) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-2147483648", &s21_res);
    str_to_dec("2147483648", &expect_dec);
    int out = s21_negate(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

Suite *s21_Suite_other_negate() {
    Suite *s;

    s = suite_create("Other negate unit test");
    
    TCase *tc1_s21_other_negate = tcase_create("negate_s21_other");

    tcase_add_test(tc1_s21_other_negate, s21_other_negate_1);
    tcase_add_test(tc1_s21_other_negate, s21_other_negate_2);
    tcase_add_test(tc1_s21_other_negate, s21_other_negate_3);
    tcase_add_test(tc1_s21_other_negate, s21_other_negate_4);
    tcase_add_test(tc1_s21_other_negate, s21_other_negate_5);
    tcase_add_test(tc1_s21_other_negate, s21_other_negate_6);

    suite_add_tcase(s, tc1_s21_other_negate);
    return s;
}


    // char* f1 = dec_to_str(s21_res);
    // printf("res   || %s\n", f1);
    // free(f1);
    // char* f2 = dec_to_str(expect_dec);
    // printf("exp   || %s\n", f2);
    // free(f2);