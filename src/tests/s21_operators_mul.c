#include "test.h"

START_TEST(s21_operators_mul_1) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("39.614081247908796757769715711", &expect_dec);
    s21_mul(test_cases[0], test_cases[1], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_mul_2) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("0.2104175868134569372093170784", &expect_dec);
    s21_mul(test_cases[1], test_cases[2], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_mul_3) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-0.00000000000000000000", &expect_dec);
    s21_mul(test_cases[2], test_cases[3], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_mul_4) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("0.0000000000000000000000000000", &expect_dec);
    s21_mul(test_cases[3], test_cases[4], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_mul_5) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("2.2950732703560962180946831700", &expect_dec);
    s21_mul(test_cases[4], test_cases[5], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_mul_6) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("1000", &expect_dec);
    s21_mul(test_cases[6], test_cases[5], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_mul_7) {
    s21_decimal expect_dec, s21_res, a_dec, b_dec;
    str_to_dec("-0.000000000000000000000001", &a_dec);
    str_to_dec("-0.000000000000000000000001", &b_dec);
    str_to_dec("0.0000000000000000000000000000", &expect_dec);
    s21_mul(a_dec, b_dec, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_mul_8) {
    s21_decimal expect_dec, s21_res, a_dec, b_dec;
    str_to_dec("-2878351094.545946573", &a_dec);
    str_to_dec("0.000000000000000308214658", &b_dec);
    str_to_dec("-0.0000008871499982094045882835", &expect_dec);
    s21_mul(a_dec, b_dec, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));

} END_TEST

Suite *s21_Suite_operators_mul() {
    Suite *s;

    s = suite_create("Operators mul unit test");
    
    TCase *tc1_s21_operators_mul = tcase_create("mul_s21_operators");

    tcase_add_test(tc1_s21_operators_mul, s21_operators_mul_1);
    tcase_add_test(tc1_s21_operators_mul, s21_operators_mul_2);
    tcase_add_test(tc1_s21_operators_mul, s21_operators_mul_3);
    tcase_add_test(tc1_s21_operators_mul, s21_operators_mul_4);
    tcase_add_test(tc1_s21_operators_mul, s21_operators_mul_5);
    tcase_add_test(tc1_s21_operators_mul, s21_operators_mul_6);
    tcase_add_test(tc1_s21_operators_mul, s21_operators_mul_7);
    tcase_add_test(tc1_s21_operators_mul, s21_operators_mul_8);

    suite_add_tcase(s, tc1_s21_operators_mul);
    
    return s;
}


    // char* f1 = dec_to_str(s21_res);
    // printf("res   || %s\n", f1);
    // free(f1);
    // char* f2 = dec_to_str(expect_dec);
    // printf("exp   || %s\n", f2);
    // free(f2);