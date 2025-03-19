#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  if (dest == s21_NULL) {
    return s21_NULL;
  }

  if (src == s21_NULL) {
    return dest;
  }

  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t i = 0;

  while (i < n && src[i] != '\0') {
    dest[dest_len + i] = src[i];
    i++;
  }

  dest[dest_len + i] = '\0';

  return dest;
}
