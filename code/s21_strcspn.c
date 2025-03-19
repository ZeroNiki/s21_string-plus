#include "../s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t k = 0;

  while (str1[k] != '\0') {
    for (s21_size_t i = 0; str2[i] != '\0'; i++) {
      if (str1[k] == str2[i]) {
        return k;
      }
    }
    k++;
  }
  return k;
}
