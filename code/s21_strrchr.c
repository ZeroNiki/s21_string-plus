#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *ptr = s21_NULL;

  if (str == s21_NULL) return ptr;

  do {
    if (*str == c) {
      ptr = (char *)str;
    }
    str++;
  } while (*(str - 1));

  return ptr;
}
