#ifndef UI_HANDLER_H
#define UI_HANDLER_H

void get_user_input(char* number_str, int max_len, int* from_base, int* to_base);

void display_result(const char* number_str, int from_base, int to_base, const char* result);

#endif