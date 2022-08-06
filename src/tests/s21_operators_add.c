#include "test.h"

START_TEST(s21_operators_add_1) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-13.961408124790879675776971571", &expect_dec);
    s21_add(test_cases[0], test_cases[1], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_add_2) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-4.0145249913658339424669715711", &expect_dec);
    s21_add(test_cases[1], test_cases[2], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_add_3) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("-0.05311686657495426669", &expect_dec);
    s21_add(test_cases[2], test_cases[3], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_add_4) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("0.2295073270356096218094683170", &expect_dec);
    s21_add(test_cases[3], test_cases[4], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_add_5) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("10.229507327035609621809468317", &expect_dec);
    s21_add(test_cases[4], test_cases[5], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_add_6) {
    s21_decimal expect_dec, s21_res;
    str_to_dec("110", &expect_dec);
    s21_add(test_cases[6], test_cases[5], &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_add_7) {
    s21_decimal expect_dec, s21_res, a_dec, b_dec;
    str_to_dec("-99229.09468317", &a_dec);
    str_to_dec("992295073270.09468317", &b_dec);
    str_to_dec("992294974041.00000000", &expect_dec);
    s21_add(a_dec, b_dec, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

START_TEST(s21_operators_add_8) {
    s21_decimal expect_dec, s21_res, a_dec, b_dec;
    str_to_dec("-385964.28330307537203556736209", &a_dec);
    str_to_dec("-78964982.38092437071", &b_dec);
    str_to_dec("-79350946.66422744608203556736", &expect_dec);
    s21_add(a_dec, b_dec, &s21_res);
    ck_assert_int_eq(1, s21_is_equal(s21_res, expect_dec));
} END_TEST

Suite *s21_Suite_operators_add() {
    Suite *s;

    s = suite_create("Operators add unit test");
    
    TCase *tc1_s21_operators_add = tcase_create("add_s21_operators");

    tcase_add_test(tc1_s21_operators_add, s21_operators_add_1);
    tcase_add_test(tc1_s21_operators_add, s21_operators_add_2);
    tcase_add_test(tc1_s21_operators_add, s21_operators_add_3);
    tcase_add_test(tc1_s21_operators_add, s21_operators_add_4);
    tcase_add_test(tc1_s21_operators_add, s21_operators_add_5);
    tcase_add_test(tc1_s21_operators_add, s21_operators_add_6);
    tcase_add_test(tc1_s21_operators_add, s21_operators_add_7);
    tcase_add_test(tc1_s21_operators_add, s21_operators_add_8);

    suite_add_tcase(s, tc1_s21_operators_add);
    
    return s;
}


    // char* f1 = dec_to_str(s21_res);
    // printf("res   || %s\n", f1);
    // free(f1);
    // char* f2 = dec_to_str(expect_dec);
    // printf("exp   || %s\n", f2);
    // free(f2);