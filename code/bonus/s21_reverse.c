#include "../../s21_string.h"

char *s21_reverse(char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t len = s21_strlen(str);
  for (s21_size_t i = 0; i < (len / 2); i++) {
    char temp = str[len - 1 - i];
    str[len - 1 - i] = str[i];
    str[i] = temp;
  }

  return str;
}
