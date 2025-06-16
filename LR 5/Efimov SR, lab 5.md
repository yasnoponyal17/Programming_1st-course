# Лабораторная работа 5
## Тема работы: Сборка C-проектов (Make, Meson, CMake)
### Конвертер систем счисления
#### Описание задачи
Создать программу, которая позволяет конвертировать числа из одной системы счисления в другую. Поддерживаемые системы: двоичная, восьмеричная, десятичная, шестнадцатеричная. Пользователь должен вводить исходное число, его систему счисления и целевую систему счисления.
#### Цели проекта
- Понимание алгоритмов перевода чисел между различными системами счисления
- Работа со строковым представлением чисел
- Реализация функций для валидации ввода (например, проверка, что в двоичном числе
нет цифр, кроме 0 и 1)
- Разделение логики конвертации на модули
#### Модули
- converter.c / converter.h
- validator.c / validator.h
- ui_handler.c / ui_handler.h
- main.c
#### converter.c
```c
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
```
#### validator.c
```c
#include "validator.h"
#include <ctype.h>
#include <string.h>

int is_valid_number(const char* number_str, int base) {
    if (base < 2 || base > 16) {
        return 0;
    }

    int start = (number_str[0] == '-') ? 1 : 0;
    if (number_str[start] == '\0') {
        return 0;
    }

    for (int i = start; number_str[i]; i++) {
        char c = toupper(number_str[i]);
        int digit_value;

        if (isdigit(c)) {
            digit_value = c - '0';
        } else if (isalpha(c) && c >= 'A' && c <= 'F') {
            digit_value = c - 'A' + 10;
        } else {
            return 0;
        }

        if (digit_value >= base) {
            return 0;
        }
    }

    return 1;
}
```
#### ui_handler.c
```c
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
```

#### main.c
```c
#include "converter.h"
#include "validator.h"
#include "ui_handler.h"
#include <stdio.h>
#include <string.h>


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
```
#### Makefile
```make
CC = gcc
CFLAGS = -Wall -g
ifdef DEBUG
CFLAGS += -DDEBUG
endif
TARGET = number_converter
SRCDIR = src
INCDIR = include
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/converter.c $(SRCDIR)/validator.c $(SRCDIR)/ui_handler.c
OBJECTS = $(SOURCES:.c=.o)
DEPS = $(INCDIR)/converter.h $(INCDIR)/validator.h $(INCDIR)/ui_handler.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	del /Q $(OBJECTS) $(TARGET).exe 2>nul || rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
```

#### CMake
```cmake
cmake_minimum_required(VERSION 3.10)
project(NumberConverter C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g -DDEBUG")

include_directories(include)
add_executable(number_converter 
    src/main.c 
    src/converter.c 
    src/validator.c 
    src/ui_handler.c
)
```

#### Meson
```meson
project('number_converter', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=c11'])

executable('number_converter',
           'src/main.c', 'src/converter.c', 'src/validator.c', 'src/ui_handler.c',
           c_args : ['-DDEBUG'],
           include_directories : include_directories('include'),
           install : false)
```

#### Результат работы
![Result](images/lr%205.png)

### Ефимов Сергей Робертович, 1 курс, ИВТ-2, подгруппа 3
