#include "../../s21_string.h"

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t len = 0;

  while (str[len]) len++;

  char *result = (char *)malloc(len + 1);

  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      result[i] = str[i] - ('a' - 'A');
    } else {
      result[i] = str[i];
    }
  }

  result[len] = '\0';
  return result;
}
