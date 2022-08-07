#include "test.h"

START_TEST(s21_other_truncate_1) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-6.03859187520912032422302842", &s21_res);
    str_to_dec("-6", &expect_dec);
    int out = s21_truncate(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_truncate_2) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-3908291258215925.4090869715711", &s21_res);
    str_to_dec("-3908291258215925", &expect_dec);
    int out = s21_truncate(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_truncate_3) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-0.05311686657495426669", &s21_res);
    str_to_dec("-0", &expect_dec);
    int out = s21_truncate(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_truncate_4) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("2295073270.356096218094683170", &s21_res);
    str_to_dec("2295073270", &expect_dec);
    int out = s21_truncate(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_truncate_5) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("9.99999999999999999999", &s21_res);
    str_to_dec("9", &expect_dec);
    int out = s21_truncate(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_truncate_6) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("87637685379687", &s21_res);
    str_to_dec("87637685379687", &expect_dec);
    int out = s21_truncate(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_truncate_7) {
    s21_decimal s21_res;
    str_to_dec("744367.68425", &s21_res);
    put_exp(&s21_res, 30);
    int out = s21_truncate(s21_res, &s21_res);
    ck_assert_int_eq(1, out);
} END_TEST

Suite *s21_Suite_other_truncate() {
    Suite *s;

    s = suite_create("Other truncate unit test");
    
    TCase *tc1_s21_other_truncate = tcase_create("truncate_s21_other");

    tcase_add_test(tc1_s21_other_truncate, s21_other_truncate_1);
    tcase_add_test(tc1_s21_other_truncate, s21_other_truncate_2);
    tcase_add_test(tc1_s21_other_truncate, s21_other_truncate_3);
    tcase_add_test(tc1_s21_other_truncate, s21_other_truncate_4);
    tcase_add_test(tc1_s21_other_truncate, s21_other_truncate_5);
    tcase_add_test(tc1_s21_other_truncate, s21_other_truncate_6);
    tcase_add_test(tc1_s21_other_truncate, s21_other_truncate_7);

    suite_add_tcase(s, tc1_s21_other_truncate);
    return s;
}


    // char* f1 = dec_to_str(s21_res);
    // printf("res   || %s\n", f1);
    // free(f1);
    // char* f2 = dec_to_str(expect_dec);
    // printf("exp   || %s\n", f2);
    // free(f2);