#include "test.h"

START_TEST(s21_operators_sub_1) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-6.038591875209120324223028429", &expect_dec);
    s21_sub(test_cases[0], test_cases[1], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_sub_2) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-3.9082912582159254090869715711", &expect_dec);
    s21_sub(test_cases[1], test_cases[2], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_sub_3) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-0.05311686657495426669", &expect_dec);
    s21_sub(test_cases[2], test_cases[3], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_sub_4) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-0.2295073270356096218094683170", &expect_dec);
    s21_sub(test_cases[3], test_cases[4], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_sub_5) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-9.770492672964390378190531683", &expect_dec);
    s21_sub(test_cases[4], test_cases[5], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_sub_6) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("90", &expect_dec);
    s21_sub(test_cases[6], test_cases[5], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_sub_7) {
    s21_decimal expect_dec, s21_res, a_dec, b_dec;
    str_to_dec("-99229.09468317", &a_dec);
    str_to_dec("992295073270.09468317", &b_dec);
    str_to_dec("-992295172499.18936634", &expect_dec);
    s21_sub(a_dec, b_dec, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_sub_8) {
    s21_decimal expect_dec, s21_res, a_dec, b_dec;
    str_to_dec("-385964.28330307537203556736209", &a_dec);
    str_to_dec("-78964982.38092437071", &b_dec);
    str_to_dec("78579018.097621295337964432638", &expect_dec);
    s21_sub(a_dec, b_dec, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));

} END_TEST

Suite *s21_Suite_operators_sub() {
    Suite *s;

    s = suite_create("Operators sub unit test");
    
    TCase *tc1_s21_operators_sub = tcase_create("sub_s21_operators");

    tcase_add_test(tc1_s21_operators_sub, s21_operators_sub_1);
    tcase_add_test(tc1_s21_operators_sub, s21_operators_sub_2);
    tcase_add_test(tc1_s21_operators_sub, s21_operators_sub_3);
    tcase_add_test(tc1_s21_operators_sub, s21_operators_sub_4);
    tcase_add_test(tc1_s21_operators_sub, s21_operators_sub_5);
    tcase_add_test(tc1_s21_operators_sub, s21_operators_sub_6);
    tcase_add_test(tc1_s21_operators_sub, s21_operators_sub_7);
    tcase_add_test(tc1_s21_operators_sub, s21_operators_sub_8);

    suite_add_tcase(s, tc1_s21_operators_sub);
    
    return s;
}


    // char* f1 = dec_to_str(s21_res);
    // printf("res   || %s\n", f1);
    // free(f1);
    // char* f2 = dec_to_str(expect_dec);
    // printf("exp   || %s\n", f2);
    // free(f2);