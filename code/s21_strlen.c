#include "../s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;

  if (str == s21_NULL) {
    return len;
  }

  while (str[len] != '\0') {
    len++;
  }

  return len;
}
