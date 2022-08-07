#include "test.h"

START_TEST(s21_compare_equal) {
    
//    int len = sizeof(test_cases) / 16;
//    for (int i = 0; i < len; i++)
        ck_assert_int_eq(1, s21_is_equal(test_cases[3], test_cases[3]));

    
    ck_assert_int_eq(0, s21_is_equal(test_cases[5], test_cases[4]));

    
//    s21_decimal negative_zero = {{0, 0, 0, 0x80000000}};

//    ck_assert_int_eq(1, s21_is_equal(test_cases[3], test_cases[3]));
} END_TEST


Suite *s21_Suite_compare_equal() {
    Suite *s;

    s = suite_create("Compare equal unit test");
    
    TCase *tc1_s21_compare_equal = tcase_create("equal_s21_compare");

    tcase_add_test(tc1_s21_compare_equal, s21_compare_equal);

    suite_add_tcase(s, tc1_s21_compare_equal);
    
    return s;
}

//    for (int k = 0; k < 4; k++) {
//        printf("dec1.int%d = %15d    dec2.int%d = %d\n",k, test_cases[i].bits[k],
//            k, test_cases[i].bits[k]);    
//    }
//    printf("\n"); 

