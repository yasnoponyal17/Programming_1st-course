#include "converter.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Функция, конвертирующая из десятичного числа в указанную систему счисления
// decimal_value - число для конвертации
// base - целевая система счисления
// result - результат
// size - размер буфера
char* decimal_to_base(long decimal_value, int base, char* result, int size) {
    // Проверка системы счисления
    if (base < 2 || base > 16) {
        snprintf(result, size, "Error: Invalid target number system (%d)", base);
        return result;
    }

    // Возвращать ноль, если число в десятичной системе равно нулю
    if (decimal_value == 0) {
        snprintf(result, size, "0");
        return result;
    }

    char digits[] = "0123456789ABCDEF"; // Все символы 16-ричной системы счисления
    char temp_buffer[65]; // Буфер для хранения чисел в обратном порядке
    int i = 0;
    int is_negative = decimal_value < 0; // Отрицательное число


    if (is_negative) {
        decimal_value = -decimal_value;
    }

    // Разделяем число на цифры в исходной системе
    while (decimal_value > 0 && i < size - 1) {
        temp_buffer[i++] = digits[decimal_value % base];
        decimal_value /= base;
    }

    // Проверка переполнения буфера
    if (i >= size - 1) {
        snprintf(result, size, "Error: buffer too small");
        return result;
    }

    int offset = is_negative ? 1 : 0;
    if (is_negative) {
        result[0] = '-';
    }

    // Переворачиваем цифры в правильный порядок
    for (int j = 0; j < i; j++) {
        result[j + offset] = temp_buffer[i - 1 - j];
    }
    result[i + offset] = '\0';

    return result;
}

// Функция, конвертирующая из указанной системы счисления в десятичную
// number_str - строка с числом
// base - исходная система счисления
long base_to_decimal(const char* number_str, int base) {
    // Проверка системы счисления
    if (base < 2 || base > 16) {
        fprintf(stderr, "Error: invalid original number system (%d)\n", base);
        return 0;
    }

    long decimal_value = 0;
    long power = 1;
    int len = strlen(number_str);
    int is_negative = (number_str[0] == '-');

    // Обрабатываем все цифры, начиная с самого правого
    for (int i = len - 1; i >= is_negative; i--) {
        int digit_value;
        char c = toupper(number_str[i]);

        // Преобразование символа в числовое значения
        if (isdigit(c)) {
            digit_value = c - '0'; // Для цифр от 0 до 9
        } else if (isalpha(c) && c >= 'A' && c <= 'F') {
            digit_value = c - 'A' + 10; // Для букв от A до F
        } else {
            fprintf(stderr, "Error: invalid character '%c' for number system %d\n", c, base);
            return 0;
        }

        // Проверка, что цифра допустима в указанной системе счисления
        if (digit_value >= base) {
            fprintf(stderr, "Error: digit '%c' is not valid for number system %d\n", c, base);
            return 0;
        }

        decimal_value += digit_value * power;
        power *= base;
    }

    return is_negative ? -decimal_value : decimal_value;
}