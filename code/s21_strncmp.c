#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t i = 0;

  while (i < n) {
    if (str1[i] != str2[i] || str1[i] == '\0') {
      return (unsigned char)str1[i] - (unsigned char)str2[i];
    }
    i++;
  }
  return 0;
}
