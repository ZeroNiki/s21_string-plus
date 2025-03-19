#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  while (*str != '\0') {
    if (*str == c) {
      return (char *)str;
    }

    str++;
  }

  return c == '\0' ? (char *)str : s21_NULL;
}
