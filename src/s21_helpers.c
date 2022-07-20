#include "./s21_decimal.h"

int get_bit(s21_decimal dec, int bit_num) {
    int out = - 1;
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
            if ((bit >= 112 && bit <= 119) || bit == 127) {
                printf("\x1B[31m""%d", out);
            } else {
                printf( "\x1B[0m""%d", out);
            }
        }
        putchar('\n');
    }
    putchar('\n');
}

void put_exp(s21_decimal* dec, int exp) {
    exp = (exp > 28) ? 28 : exp; // хз, может и не нужно
    for (int bit_num = 0; bit_num < 5; bit_num++) {
        put_bit(dec, bit_num + 112, exp & 0b1);
        exp >>= 1;
    }
}

char* dec_to_str(s21_decimal dec) {
    char* out = (char*) calloc(32, sizeof(char));
    memset(out, '0', 29), out[29] = '\0', out[30] = '\0', out[31] = '\0';
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
    int point = (dec.bits[3] << 1) >> 17;
    if (point) {
        memmove(out + 30 - point, out + 29 - point, point);
        out[29 - point] = '.';
    }
    // Вставка знака
    if (get_bit(dec, 127)) {
        memmove(out + 1, out, 30);
        out[0] = '-';
    }
    return out;
}

// Вспомогательные функции для математических операций

int shift_left(s21_decimal* dec) {
    int flag = (dec->bits[2] & LEFT_BIT) ? 1 : 0; // 1 - будет переполнение сдвиг невозможен
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
    int flag = (dec->bits[0] & 1) ? 1 : 0; // 1 - будет переполнение сдвиг невозможен
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
    int flag = 1;
    for (int byte = 2; byte >= 0 && flag == 1; byte--) {
        if ((unsigned)value_1.bits[byte] != (unsigned)value_2.bits[byte]) {
            flag = 0;
        }
    }
    return flag;
}

int s21_is_greater_simple(s21_decimal value_1, s21_decimal value_2) {
    int flag = 0;
    for (int byte = 2; byte >= 0 && flag == 0; byte--) {
        if ((unsigned)value_1.bits[byte] > (unsigned)value_2.bits[byte]) {
            flag = 1;
        }
        if ((unsigned)value_1.bits[byte] < (unsigned)value_2.bits[byte]) {
            flag = - 1;
        }
    }
    flag = (flag == 1) ? 1 : 0;
    return flag;
}

int s21_is_greater_or_equal_simple(s21_decimal value_1, s21_decimal value_2) {
    int flag = s21_is_equal_simple(value_1, value_2);
    flag += s21_is_greater_simple(value_1, value_2);
    flag = (flag == 0) ? 0 : 1;
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
    return flag; // 0 - OK; 1 - inf
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
    for (int i = 0; i < count; i++) {
        if (get_bit(value_2, i) == 1) {
            s21_add_simple(*result, value_1, result);
        }
        if (shift_left(&value_1)) flag = 1;
    }
    if (flag) *result = tmp;
    return flag; // Добавить выводы ошибок при переполнении
}

s21_decimal s21_div_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    // for (int i = 0; i < 3; i++) result->bits[i] = 0;  // Обнуление нужно только в сложной версии
    int num_bits_1 = signific_bits(value_1);
    int num_bits_2 = signific_bits(value_2);
    // Выравниваем биты второго числа по левому краю первого числа
    int diff = num_bits_1 - num_bits_2;
    for (int i = 0; i < diff; i++) {
        shift_left(&value_2);
    }
    // Деление
    for (int i = 0; i <= diff && !shift_left(result); i++) {
        // shift_left(result);
        if (s21_is_greater_or_equal_simple(value_1, value_2)) {
            s21_sub_simple(value_1, value_2, &value_1);
            result->bits[0] += 1;
        }
        shift_right(&value_2);
    }
    return value_1;
}

s21_decimal s21_div_full_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_decimal ten = {{10, 0, 0, 0}};  // Тупо число 10 для умножения на него
    s21_decimal two = {{2, 0, 0, 0}};  // Тупо число 2 для деления на него
    s21_decimal mod = {{1, 0, 0, 0}};   // Остаток от деления
    for (int i = 0; i < 3; i++) result->bits[i] = 0;
    int num_bits_2 = signific_bits(*result);
    int exp = -1;
    // Выход если нет остатка от деления или заполнены все биты в result
    while ((num_bits_2 < 95 || ) && (mod.bits[0] != 0  || mod.bits[1] != 0  || mod.bits[2] != 0)) {
        exp++;
        s21_mul_simple(*result, ten, result);
        mod = s21_div_simple(value_1, value_2, result);
        s21_div_simple(*result, mod, result);
            char* f2 = dec_to_str(mod);
            printf("dec2 || %s\n", f2);
            free(f2);
        while (s21_mul_simple(mod, ten, &mod)) {
            // Случай большого остатка, не умножающегося на 10
            s21_div_simple(mod, two, &mod);
            s21_div_simple(value_2, two, &value_2);
        }
        num_bits_2 = signific_bits(*result);
    }
    // Изменение экспоненты
    put_exp(result, exp);
    return *result; // ? удалить? заменить на инт?
}