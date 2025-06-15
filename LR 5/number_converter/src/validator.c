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