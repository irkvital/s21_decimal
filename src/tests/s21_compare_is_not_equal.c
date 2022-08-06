#include "test.h"

START_TEST(s21_compare_is_not_equal) {
    
    int len = sizeof(test_cases) / 16;

    for (int i = 0, j = len - 1, res = 0; i < len - 1; i++, j--) {
        if (i == j) continue;
        res = s21_is_not_equal(test_cases[j], test_cases[i]);
//        for (int k = 0; k < 4; k++) {
//            printf("dec1.int%d = %15d    dec2.int%d = %d\n",k, test_cases[i].bits[k],
//                k, test_cases[j].bits[k]);    
//        }
//        printf("\n");
        ck_assert_int_eq(1, res);
    }

    for (int i = 0, j = 0, res = 1; i < len; i++, j++) {
        if (i == j) continue;
        res = s21_is_not_equal(test_cases[j], test_cases[i]);
//        for (int k = 0; k < 4; k++) {
//            printf("dec1.int%d = %15d    dec2.int%d = %d\n",k, test_cases[i].bits[k],
//                k, test_cases[j].bits[k]);    
//        }
//        printf("\n"); 
        ck_assert_int_eq(0, res);
    } 



} END_TEST


Suite *s21_Suite_compare_is_not_equal() {
    Suite *s;

    s = suite_create("Compare is_not_equal unit test");
    
    TCase *tc1_s21_compare_is_not_equal = tcase_create("is_not_equal_s21_compare");

    tcase_add_test(tc1_s21_compare_is_not_equal, s21_compare_is_not_equal);

    suite_add_tcase(s, tc1_s21_compare_is_not_equal);
    
    return s;
}
