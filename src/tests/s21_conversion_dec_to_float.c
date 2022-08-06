#include "test.h"

START_TEST(s21_conversion_dec_to_float) {
    
    int len = sizeof(test_cases) / 16;
    float res = 0;
    for (int i = 0; i < len; i++, res = 0) {
        s21_from_decimal_to_float(test_cases[i], &res);

//    for (int k = 0; k < 4; k++) {
//        printf("dec1.int%d = %15d    dec2.int%d = %d\n",k, test_cases[i].bits[k],
//            k, test_cases[i].bits[k]);    
//    }
//    printf("\n"); 
       ck_assert_float_eq_tol(result_conversion_to_float[i], res, 1e-6);
    }
} END_TEST


Suite *s21_Suite_conversion_dec_to_float() {
    Suite *s;

    s = suite_create("Compare dec_to_float unit test");
    
    TCase *tc1_s21_conversion_dec_to_float = tcase_create("dec_to_float_s21_compare");

    tcase_add_test(tc1_s21_conversion_dec_to_float, s21_conversion_dec_to_float);

    suite_add_tcase(s, tc1_s21_conversion_dec_to_float);
    
    return s;
}
