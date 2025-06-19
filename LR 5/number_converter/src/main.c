#include "converter.h"
#include "validator.h"
#include "ui_handler.h"
#include <stdio.h>
#include <string.h>

// Макрос для отладочной печати
#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif


// Главная функция
int main() {
    char number_str[65]; // Входное число
    int from_base, to_base; // Системы счисления
    char result_buffer[65]; // Результат

    // Основной цикл программы
    while (1) {
        // Получаем пользовательский ввод
        get_user_input(number_str, sizeof(number_str), &from_base, &to_base);

        // Проверка команды выхода
        if (strcmp(number_str, "exit") == 0) {
            printf("Program completed.\n");
            break;
        }

        // Отладочная печать
        DEBUG_PRINT("Input: number = %s, original system = %d, target system = %d\n",
                    number_str, from_base, to_base);

        // Проверка валидации числа
        if (!is_valid_number(number_str, from_base)) {
            fprintf(stderr, "Error: invalid number for number system %d\n", from_base);
            continue;
        }

        // Конвертация в десятичную систему счисления
        long decimal_value = base_to_decimal(number_str, from_base);
        if (decimal_value == 0 && number_str[0] != '0') {
            continue;
        }

        // Конвертация в целевую систему счисления
        char* result = decimal_to_base(decimal_value, to_base, result_buffer, sizeof(result_buffer));
        display_result(number_str, from_base, to_base, result);
    }

    return 0;
}