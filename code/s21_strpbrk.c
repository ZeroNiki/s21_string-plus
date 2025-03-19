#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  int len_s1 = (int)s21_strlen(str1);
  int len_s2 = (int)s21_strlen(str2);

  for (int i = 0; i < len_s1; i++) {
    for (int j = 0; j < len_s2; j++) {
      if (str2[j] == str1[i]) {
        return (char *)(str1 + i);
      }
    }
  }

  return s21_NULL;
}
