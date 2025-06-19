#include "ui_handler.h"
#include <stdio.h>
#include <string.h>

// Функция получения числа и систем счисления
// number_str - число
// max_len - максимальная длина ввода
// from_base - исходная система счисления
// to_base - целевая система счисления
void get_user_input(char* number_str, int max_len, int* from_base, int* to_base) {
    printf("Enter a number: ");
    fgets(number_str, max_len, stdin);
    number_str[strcspn(number_str, "\n")] = '\0';

    printf("Enter the original number system (2, 8, 10, 16): ");
    scanf("%d", from_base);
    while (getchar() != '\n');

    printf("Enter the target number system (2, 8, 10, 16): ");
    scanf("%d", to_base);
    while (getchar() != '\n');
}

// Функция вывода результата 
// number_str - число
// from_base - исходная система счисления
// to_base - целевая система счисления
// result - результат конвертации
void display_result(const char* number_str, int from_base, int to_base, const char* result) {
    printf("Number %s (system %d) = %s (system %d)\n", number_str, from_base, result, to_base);
}