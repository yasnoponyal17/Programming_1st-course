#include "converter.h"
#include "validator.h"
#include "ui_handler.h"
#include <stdio.h>
#include <string.h>

#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

int main() {
    char number_str[65];
    int from_base, to_base;
    char result_buffer[65];

    while (1) {
        get_user_input(number_str, sizeof(number_str), &from_base, &to_base);

        if (strcmp(number_str, "exit") == 0) {
            printf("Программа завершена.\n");
            break;
        }

        DEBUG_PRINT("Введено: число = %s, исходная система = %d, целевая система = %d\n",
                    number_str, from_base, to_base);

        if (!is_valid_number(number_str, from_base)) {
            fprintf(stderr, "Ошибка: Некорректное число для системы счисления %d\n", from_base);
            continue;
        }

        long decimal_value = base_to_decimal(number_str, from_base);
        if (decimal_value == 0 && number_str[0] != '0') {
            continue;
        }

        char* result = decimal_to_base(decimal_value, to_base, result_buffer, sizeof(result_buffer));
        display_result(number_str, from_base, to_base, result);
    }

    return 0;
}