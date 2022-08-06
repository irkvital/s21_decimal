#include "test.h"

START_TEST(s21_compare_greater_or_equal) {
    
    int len = sizeof(test_cases) / 16;

    for (int i = 0, j = len - 1, res = 1; i < len - 1; i++) {
        res = s21_is_greater_or_equal(test_cases[i], test_cases[j]);
//    for (int k = 0; k < 4; k++) {
//        printf("dec1.int%d = %15d    dec2.int%d = %d\n",k, test_cases[i].bits[k],
//            k, test_cases[j].bits[k]);    
//    }
//    printf("\n"); 
       ck_assert_int_eq(0, res);
    }

    for (int i = 0, j = len-1, res = 0; i < len - 1; i++) {
        res = s21_is_greater_or_equal(test_cases[j], test_cases[i]);
//    for (int k = 0; k < 4; k++) {
//        printf("dec1.int%d = %15d    dec2.int%d = %d\n",k, test_cases[i].bits[k],
//            k, test_cases[j].bits[k]);    
//    }
//    printf("\n"); 
       ck_assert_int_eq(1, res);
    } 

    for (int i = 0, j = 0, res = 0; i < len; i++, j++) {
//    for (int k = 0; k < 4; k++) {
//        printf("dec1.int%d = %15d    dec2.int%d = %d\n",k, test_cases[i].bits[k],
//            k, test_cases[j].bits[k]);    
//    }
//    printf("\n"); 
       res = s21_is_greater_or_equal(test_cases[j], test_cases[i]);
        ck_assert_int_eq(1, res);
    } 


} END_TEST


Suite *s21_Suite_compare_greater_or_equal() {
    Suite *s;

    s = suite_create("Compare greater_or_equal unit test");
    
    TCase *tc1_s21_compare_greater_or_equal = tcase_create("greater_or_equal_s21_compare");

    tcase_add_test(tc1_s21_compare_greater_or_equal, s21_compare_greater_or_equal);

    suite_add_tcase(s, tc1_s21_compare_greater_or_equal);
    
    return s;
}
