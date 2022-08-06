#include "test.h"

START_TEST(s21_other_floor_1) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-6.03859187520912032422302842", &s21_res);
    str_to_dec("-7", &expect_dec);
    int out = s21_floor(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_floor_2) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-3908291258215925.4090869715711", &s21_res);
    str_to_dec("-3908291258215926", &expect_dec);
    int out = s21_floor(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_floor_3) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-0.05311686657495426669", &s21_res);
    str_to_dec("-1", &expect_dec);
    int out = s21_floor(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_floor_4) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("2295073270.356096218094683170", &s21_res);
    str_to_dec("2295073270", &expect_dec);
    int out = s21_floor(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_floor_5) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("9.99999999999999999999", &s21_res);
    str_to_dec("9", &expect_dec);
    int out = s21_floor(s21_res, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
    ck_assert_int_eq(0, out);
} END_TEST

START_TEST(s21_other_floor_6) {
    s21_decimal s21_res;
    str_to_dec("744367.68425", &s21_res);
    put_exp(&s21_res, 30);
    int out = s21_floor(s21_res, &s21_res);
    ck_assert_int_eq(1, out);
} END_TEST

Suite *s21_Suite_other_floor() {
    Suite *s;

    s = suite_create("Other floor unit test");
    
    TCase *tc1_s21_other_floor = tcase_create("floor_s21_other");

    tcase_add_test(tc1_s21_other_floor, s21_other_floor_1);
    tcase_add_test(tc1_s21_other_floor, s21_other_floor_2);
    tcase_add_test(tc1_s21_other_floor, s21_other_floor_3);
    tcase_add_test(tc1_s21_other_floor, s21_other_floor_4);
    tcase_add_test(tc1_s21_other_floor, s21_other_floor_5);
    tcase_add_test(tc1_s21_other_floor, s21_other_floor_6);

    suite_add_tcase(s, tc1_s21_other_floor);
    return s;
}


    // char* f1 = dec_to_str(s21_res);
    // printf("res   || %s\n", f1);
    // free(f1);
    // char* f2 = dec_to_str(expect_dec);
    // printf("exp   || %s\n", f2);
    // free(f2);