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
    int exp = get_exp(value), out = 0;
    s21_decimal fract = DEC_NUL;
    s21_decimal one = {{1, 0, 0, 0}};
    put_bit(&one, 127, 1);
    if (get_bit(value, 127)) 
        put_bit(result, 127, 1);

    if (exp > 0 && exp <= 28) {
        while(exp-- > 0) {
            fract = s21_div_simple(value, DEC_TEN, result);
            value = *result;
        }
    } else if (exp == 0) { 
        *result = value; 
    } else { out = 1; }

    if (get_bit(value, 127) && !s21_is_equal(fract, DEC_NUL))
        s21_add(*result, one, result);
    return out;
}


int s21_round(s21_decimal value, s21_decimal *result) {
    int out = 0, exp = get_exp(value), sign = get_bit(value, 127);
    
    s21_decimal fract = DEC_NUL;
    s21_decimal one = {{1, 0, 0, 0}};
    s21_decimal half_one = {{5, 0, 0, 0}};
//    put_exp(&half_one, 1);
//    print_bits(half_one);

    if (get_bit(value, 127)) 
        put_bit(result, 127, 1);

    
    if (exp > 0 && exp <= 28) {
        while(exp-- > 0) {
            fract = s21_div_simple(value, DEC_TEN, result);
            value = *result;
        }
        put_bit(&fract, 127, 0);
        if (s21_is_greater_or_equal(fract, half_one) && !sign)
            s21_add(*result, one, result);
        else if (s21_is_greater_or_equal(fract, half_one) && sign)
            s21_sub(*result, one, result);

    } else if (exp == 0) { 
        *result = value; 
    } else { out = 1; }

    return out; 
}


int s21_truncate(s21_decimal value, s21_decimal *result) {
    int out = 0, exp = get_exp(value), sign = get_bit(value, 127); 
    if (exp > 0 && exp <= 28) {
        while (exp-- > 0) {
        s21_div_simple(value, DEC_TEN, result);
        value = *result;
        }
    } else if (exp == 0) {
        *result = value;
    } else { out = 1; }
    if(sign)
        put_bit(result, 127, 1);
    return out;
}
    
