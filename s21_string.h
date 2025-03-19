#ifndef S21_STRING_H
#define S21_STRING_H

#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

/* Тут мне стоит пояснить за библеотеки: (в основном для sprintf)
 * limits.h INT_MIN - мин. значение
 * locale.h - для работы с языками (localeconv() - структура с тек. локалью)
 * math.h: ->
 * powl - вычисляет число в степени
 * fmodl - вычисляет остаток от деления с плавающей запятой
 * fabsl - вычисляет модуль числа
 * ceill - округляет число вверх до ближайшего целого
 * truncl - отбрасывает дробную часть числа
 * roundl - округляет число до ближайшего целого
 * * * * * * * *
 * Я старался :) */

#define s21_NULL ((void *)0)
typedef long unsigned s21_size_t;

// breaadvi
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);

// monteala
s21_size_t s21_strcspn(const char *str1, const char *str2);
s21_size_t s21_strlen(const char *str);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strerror(int errnum);

// nellaror
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

// For sprintf (nellaror)
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcat(char *dest, const char *src);
void *s21_memmove(void *dest, const void *src, s21_size_t n);

#include "s21_bonus.h"
#include "s21_stdio.h"

#endif
