#include "./s21_decimal.h"

int get_bit(s21_decimal dec, int bit_num) {
    int out = (dec.bits[bit_num / 32] & (1 << bit_num % 32)) ? 1 : 0;
    return out;
}

void put_bit(s21_decimal* dec, int bit_num, int bit) {
    if (bit == 1) {
        dec->bits[bit_num / 32] |= (1 << bit_num % 32);
    } else if (bit == 0) {
        dec->bits[bit_num / 32] &= ~(1 << bit_num % 32);
    }
}

// void print_bits(s21_decimal dec) {
//     for (int byte = 0; byte < 4; byte++) {
//         for (int bit = 32 * (byte + 1) - 1; bit >= byte * 32; bit--) {
//             int out = get_bit(dec, bit);
//             if ((bit >= 112 && bit <= 119) || bit == 127) {
//                 printf("\x1B[31m""%d", out);
//             } else {
//                 printf("\x1B[0m""%d", out);
//             }
//         }
//         putchar('\n');
//     }
//     putchar('\n');
// }

void put_exp(s21_decimal* dec, int exp) {
    for (int bit_num = 0; bit_num < 8; bit_num++) {
        put_bit(dec, bit_num + 112, exp & 0b1);
        exp >>= 1;
    }
}

int get_exp(s21_decimal dec) {
    int out = dec.bits[3];
    out <<= 1;
    out >>= 17;
    out = (out > 100) ? out - 256 : out;
    return out;
}

char* dec_to_str(s21_decimal dec) {
    char* out = (char*) calloc(32, sizeof(char));
    memset(out, '0', 29);
    char exptwo[30];
    memset(exptwo, '0', 28), exptwo[28] = '1', exptwo[29] = '\0';

    if (get_bit(dec, 0)) out[28] = '1';
    for (int bit_num = 1; bit_num < 96; bit_num++) {
        // Получение степеней двойки
        int flag = 0;
        for (int i = 28; i >= 0; i--) {
            int symbol = exptwo[i] - '0';
            symbol = (flag) ? (symbol * 2 + flag) : (symbol * 2);
            exptwo[i] = symbol % 10 + '0';
            flag = symbol / 10;
        }
        // Сложение строк
        if (get_bit(dec, bit_num)) {
            flag = 0;
            for (int i = 28; i >= 0; i--) {
                int symbol = exptwo[i] - '0' + out[i] - '0';
                symbol = (flag) ? (symbol + flag) : symbol;
                out[i] = symbol % 10 + '0';
                flag = symbol / 10;
            }
        }
    }
    // Вставка точки
    int point = get_exp(dec);
    if (point > 28 || point < 0) point = 0;
    if (point) {
        memmove(out + 30 - point, out + 29 - point, point);
        out[29 - point] = '.';
    }
    // Удаление первых нулей
    int count = 0;
    while (count < 29 - point - 1 && out[count] == '0') count++;
    if (count != 0) memmove(out, out + count, 32 - count);
    // Вставка знака
    if (get_bit(dec, 127)) {
        memmove(out + 1, out, 30);
        out[0] = '-';
    }
    return out;
}

// Вспомогательные функции для математических операций

int shift_left(s21_decimal* dec) {
    int flag = (dec->bits[2] & LEFT_BIT) ? 1 : 0;  // 1 - будет переполнение сдвиг невозможен
    if (!flag) {
        for (int byte = 0; byte < 3; byte++) {
            int flagn = (dec->bits[byte] & LEFT_BIT) ? 1 : 0;
            dec->bits[byte] <<= 1;
            dec->bits[byte] += flag;
            flag = flagn;
        }
    }
    return flag;
}

int shift_right(s21_decimal* dec) {
    int flag = (dec->bits[0] & 1) ? 1 : 0;  // 1 - будет переполнение сдвиг невозможен
    if (!flag) {
        for (int byte = 2; byte >= 0; byte--) {
            int flagn = (dec->bits[byte] & 1) ? 1 : 0;
            dec->bits[byte] >>= 1;
            put_bit(dec, 32 * byte + 31, flag);
            flag = flagn;
        }
    }
    return flag;
}

int signific_bits(s21_decimal dec) {
    int count = 96;
    s21_decimal tmp = dec;
    while (!shift_left(&tmp) && count > 0) {
        count--;
    }
    return count;
}

int s21_is_equal_simple(s21_decimal value_1, s21_decimal value_2) {
    int flag = TRUE;
    for (int byte = 2; byte >= 0 && flag == TRUE; byte--) {
        if ((unsigned)value_1.bits[byte] != (unsigned)value_2.bits[byte]) {
            flag = FALSE;
        }
    }
    return flag;
}

int s21_is_greater_simple(s21_decimal value_1, s21_decimal value_2) {
    int flag = FALSE;
    for (int byte = 2; byte >= 0 && flag == FALSE; byte--) {
        if ((unsigned)value_1.bits[byte] > (unsigned)value_2.bits[byte]) {
            flag = TRUE;
        }
        if ((unsigned)value_1.bits[byte] < (unsigned)value_2.bits[byte]) {
            flag = - 1;
        }
    }
    flag = (flag == TRUE) ? TRUE : FALSE;
    return flag;
}

int s21_is_greater_or_equal_simple(s21_decimal value_1, s21_decimal value_2) {
    int flag = s21_is_equal_simple(value_1, value_2);
    flag += s21_is_greater_simple(value_1, value_2);
    flag = (flag == FALSE) ? FALSE : TRUE;
    return flag;
}

int s21_add_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int flag = 0;
    for (int bit_num = 0; bit_num < 96; bit_num++) {
        int bit1 = get_bit(value_1, bit_num);
        int bit2 = get_bit(value_2, bit_num);
        int bit3 = bit1 + bit2 + flag;
        flag = bit3 / 2;
        put_bit(result, bit_num, bit3 % 2);
    }
    return flag;  // 0 - OK; 1 - inf
}

int s21_sub_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int flag = 0;
    for (int bit_num = 0; bit_num < 96; bit_num++) {
        int bit1 = get_bit(value_1, bit_num);
        int bit2 = get_bit(value_2, bit_num);
        int bit3 = bit1 - bit2 - flag;
        put_bit(result, bit_num, (bit3 + 2) % 2);
        flag = (bit3 < 0) ? 1 : 0;
    }
    return flag;
}

int s21_mul_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_decimal tmp = *result;
    int flag = 0;
    for (int i = 0; i < 3; i++) result->bits[i] = 0;
    // Количество значащих цифр во втором множителе
    int count = signific_bits(value_2);
    //  Умножение
    for (int i = 0; i < count && flag == 0; i++) {
        if (get_bit(value_2, i) == 1) {
            flag = s21_add_simple(*result, value_1, result);
        }
        if (shift_left(&value_1) && i != count - 1) flag = 1;
    }
    if (flag) *result = tmp;
    return flag;  // 1 - ошибка переполнения
}

s21_decimal s21_div_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    for (int i = 0; i < 3; i++) result->bits[i] = 0;
    int num_bits_1 = signific_bits(value_1);
    int num_bits_2 = signific_bits(value_2);
    // Выравниваем биты второго числа по левому краю первого числа
    int diff = num_bits_1 - num_bits_2;
    for (int i = 0; i < diff; i++) {
        shift_left(&value_2);
    }
    // Деление
    for (int i = 0; i <= diff && !shift_left(result); i++) {
        if (s21_is_greater_or_equal_simple(value_1, value_2)) {
            s21_sub_simple(value_1, value_2, &value_1);
            result->bits[0] += 1;
        }
        shift_right(&value_2);
    }
    return value_1;
}

int s21_div_full_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int out = 0;
    int err = 0;
    int num_bits_2 = signific_bits(*result);
    int exp = get_exp(value_1) - get_exp(value_2) - 1;
    s21_decimal tmp = {{0, 0, 0, 0}};
    // Выход если нет остатка от деления или заполнены все биты в result
    while ((num_bits_2 < 96) && exp < 28 && !err && (value_1.bits[0] != 0 || value_1.bits[1] != 0
                                                                                || value_1.bits[2] != 0)) {
        err = s21_mul_simple(*result, DEC_TEN, result);
        if (!err) {
            exp++;
            value_1 = s21_div_simple(value_1, value_2, &tmp);   // В value_1 записывается остаток от деления
            s21_add_simple(*result, tmp, result);
            while (s21_mul_simple(value_1, DEC_TEN, &value_1)) {
                // Случай большого остатка, не умножающегося на 10
                s21_div_simple(value_1, DEC_TWO, &value_1);
                s21_div_simple(value_2, DEC_TWO, &value_2);
            }
            num_bits_2 = signific_bits(*result);
        }
    }
    // Банковское округление к ближайшему четному
    s21_decimal tmp_end = {{0, 0, 0, 0}};
    s21_div_simple(value_1, value_2, &tmp_end);
    if (tmp_end.bits[0] > 5 || (tmp_end.bits[0] == 5 && tmp.bits[0] % 2 == 1)) {
        tmp_end.bits[0] = 1;
        s21_add_simple(*result, tmp_end, result);
    }
    // Изменение экспоненты
    err = 0;
    while (exp < 0 && !err) {
        exp++;
        err = s21_mul_simple(*result, DEC_TEN, result);
    }
    put_exp(result, exp);
    if (result->bits[0] == 0 && result->bits[1] == 0 && result->bits[2] == 0) {
        out = 2;
    } else if (err) {
        out = 1;
    }
    return out;
}

void centering(s21_decimal* value_1, s21_decimal* value_2) {
    int exp_1 = get_exp(*value_1);
    int exp_2 = get_exp(*value_2);
    if (exp_1 > exp_2) {
        centering_simple(value_1, value_2, exp_1, exp_2);
    } else if (exp_1 < exp_2) {
        centering_simple(value_2, value_1, exp_2, exp_1);
    }
}

// Степень value_1 > степени value_2
void centering_simple(s21_decimal* value_1, s21_decimal* value_2, int exp_1, int exp_2) {
    int diff = exp_1 - exp_2;
    while (diff > 0 && !s21_mul_simple(*value_2, DEC_TEN, value_2)) {
        diff--;
        exp_2++;
    }
    int flag = 0;
    while (diff > 0) {
        if (diff == 1) {
            div_bank_round(value_1, flag);
        } else {
            s21_decimal tmp = s21_div_simple(*value_1, DEC_TEN, value_1);
            if (tmp.bits[0]) flag = 1;
        }
        diff--;
        exp_1--;
    }
    put_exp(value_1, exp_1);
    put_exp(value_2, exp_2);
}

void div_bank_round(s21_decimal* value, int flag) {
    s21_decimal trash;
    s21_decimal tmp = s21_div_simple(*value, DEC_TEN, value);
    s21_decimal tmp_end = s21_div_simple(*value, DEC_TEN, &trash);
    // Округление
    if (tmp.bits[0] > 5 || (tmp.bits[0] == 5 && flag) || (tmp.bits[0] == 5 && tmp_end.bits[0] % 2 == 1)) {
        tmp.bits[0] = 1;
        s21_add_simple(*value, tmp, value);
    }
}

int str_to_dec(char str[], s21_decimal* dec) {
    *dec = DEC_NUL;
    int out = 0, sign = PLUS;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            int symbol = str[i] - '0';
            s21_decimal symb = {{symbol, 0, 0, 0}};
            out = s21_mul_simple(*dec, DEC_TEN, dec);
            s21_add_simple(*dec, symb, dec);
        } else if (str[i] == '.') {
            put_exp(dec, len - 1 - i);
        } else if (str[i] == '-') {
            sign = MINUS;
        }
    }
    put_bit(dec, 127, sign);
    return out;
}

int scale(float num) {
    int res = 127;
    unsigned int bits = *((unsigned int*)&num);
    bits <<= 1; bits >>= 24;
    return bits - res;
}
