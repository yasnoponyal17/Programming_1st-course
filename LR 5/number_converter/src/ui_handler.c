#include "ui_handler.h"
#include <stdio.h>
#include <string.h>

void get_user_input(char* number_str, int max_len, int* from_base, int* to_base) {
    printf("Введите число: ");
    fgets(number_str, max_len, stdin);
    number_str[strcspn(number_str, "\n")] = '\0';

    printf("Введите исходную систему счисления (2, 8, 10, 16): ");
    scanf("%d", from_base);
    while (getchar() != '\n');

    printf("Введите целевую систему счисления (2, 8, 10, 16): ");
    scanf("%d", to_base);
    while (getchar() != '\n');
}

void display_result(const char* number_str, int from_base, int to_base, const char* result) {
    printf("Число %s (основание %d) = %s (основание %d)\n", number_str, from_base, result, to_base);
}