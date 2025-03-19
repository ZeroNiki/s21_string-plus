#include "../s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *s = (unsigned char *)str;

  while (n--) {
    *s++ = (unsigned char)c;
  }

  return str;
}
