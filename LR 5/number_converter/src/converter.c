#include "converter.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

char* decimal_to_base(long decimal_value, int base, char* result_buffer, int buffer_size) {
    if (base < 2 || base > 16) {
        snprintf(result_buffer, buffer_size, "Ошибка: Неверная целевая система счисления (%d)", base);
        return result_buffer;
    }

    if (decimal_value == 0) {
        snprintf(result_buffer, buffer_size, "0");
        return result_buffer;
    }

    char digits[] = "0123456789ABCDEF";
    char temp_buffer[65];
    int i = 0;
    int is_negative = decimal_value < 0;

    if (is_negative) {
        decimal_value = -decimal_value;
    }

    while (decimal_value > 0 && i < buffer_size - 1) {
        temp_buffer[i++] = digits[decimal_value % base];
        decimal_value /= base;
    }

    if (i >= buffer_size - 1) {
        snprintf(result_buffer, buffer_size, "Ошибка: Буфер слишком мал");
        return result_buffer;
    }

    int offset = is_negative ? 1 : 0;
    if (is_negative) {
        result_buffer[0] = '-';
    }

    for (int j = 0; j < i; j++) {
        result_buffer[j + offset] = temp_buffer[i - 1 - j];
    }
    result_buffer[i + offset] = '\0';

    return result_buffer;
}

long base_to_decimal(const char* number_str, int base) {
    if (base < 2 || base > 16) {
        fprintf(stderr, "Ошибка: Неверная исходная система счисления (%d)\n", base);
        return 0;
    }

    long decimal_value = 0;
    long power = 1;
    int len = strlen(number_str);
    int is_negative = (number_str[0] == '-');

    for (int i = len - 1; i >= is_negative; i--) {
        int digit_value;
        char c = toupper(number_str[i]);

        if (isdigit(c)) {
            digit_value = c - '0';
        } else if (isalpha(c) && c >= 'A' && c <= 'F') {
            digit_value = c - 'A' + 10;
        } else {
            fprintf(stderr, "Ошибка: Некорректный символ '%c' для системы счисления %d\n", c, base);
            return 0;
        }

        if (digit_value >= base) {
            fprintf(stderr, "Ошибка: Цифра '%c' недопустима для системы счисления %d\n", c, base);
            return 0;
        }

        decimal_value += digit_value * power;
        power *= base;
    }

    return is_negative ? -decimal_value : decimal_value;
}