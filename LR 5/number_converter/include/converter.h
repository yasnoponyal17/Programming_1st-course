#ifndef CONVERTER_H
#define CONVERTER_H

char* decimal_to_base(long decimal_value, int base, char* result_buffer, int buffer_size);

long base_to_decimal(const char* number_str, int base);

#endif 