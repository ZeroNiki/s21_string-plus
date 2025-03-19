#ifndef S21_BONUS_H
#define S21_BONUS_H

#include "s21_string.h"

// breaadvi
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);

// nellaror
char *s21_reverse(char *str);

#endif
