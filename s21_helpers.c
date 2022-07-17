#include "./s21_decimal.h"

int get_bit(s21_decimal dec, int bit_num) {
    int out = -1;
    if (bit_num >= 0 && bit_num < 128) {
        out = (dec.bits[bit_num / 32] & (1 << bit_num % 32)) ? 1 : 0;
    }
    return out;
}

int put_bit(s21_decimal* dec, int bit_num, int bit) {
    int out = 0;
    if (bit_num >= 0 && bit_num < 128) {
        if (bit == 1) {
            dec->bits[bit_num / 32] |= (1 << bit_num % 32);
            out = 1;
        } else if (bit == 0) {
            dec->bits[bit_num / 32] &= ~(1 << bit_num % 32);
            out = 1;
        }
    }
    return out;
}

void print_bits(s21_decimal dec) {
    for (int byte = 0; byte < 4; byte++) {
        for (int bit = 32 * (byte + 1) - 1; bit >= byte * 32; bit--) {
            int out = get_bit(dec, bit);
            if (bit >= 112 && bit <= 119) {
                printf("\x1B[31m""%d", out);
            } else {
                printf( "\x1B[0m""%d", out);
            }
            
        }
        putchar('\n');
    }
    putchar('\n');
}

void put_sign(s21_decimal* dec, int sign) {
    put_bit(dec, 127, sign);
}

void put_exp(s21_decimal* dec, int exp) {
    exp = (exp > 28) ? 28 : exp; // хз, может и не нужно
    for (int bit_num = 0; bit_num < 5; bit_num++) {
        put_bit(dec, bit_num + 112, exp & 0b1);
        exp >>= 1;
    }
}

// int str_to_dec(char* src) {

// }