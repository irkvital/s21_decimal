#include "./s21_decimal.h"


int s21_negate(s21_decimal value, s21_decimal *result) {
    *result = value;
    int sign = get_bit(value, 127);
    sign = (sign == MINUS) ? (PLUS) : (MINUS);
    put_bit(result, 127, sign);
    int out = (result) ? 0 : 1;
    return out;
}


int s21_floor(s21_decimal value, s21_decimal *result) {
    int exp = get_exp(value);
    int flag = 0; 
    s21_decimal integer = {{10, 0, 0, 0}};
    s21_decimal fract;
    s21_decimal one = {{1, 0, 0, 0}};
    put_bit(&one, 127, 1);
   
    if (get_bit(value, 127)) {
        flag = 1;  
        put_bit(result, 127, 1);
    }         
    fract = s21_div_simple(value, integer, result);
        
    if (exp > 0) {
        while(exp-- > 0) {
            s21_div_simple(value, integer, result);
            value = *result;
        }
    } else { *result = value; }

    if (get_bit(value, 127) && !s21_is_equal(fract, DEC_NUL))
        s21_add(*result, one, result);
return 0;
}
