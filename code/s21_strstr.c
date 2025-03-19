#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *_return = s21_NULL;

  if (haystack && needle) {
    if (*needle == '\0') {
      _return = (char *)haystack;
    } else {
      s21_size_t haystack_len = s21_strlen(haystack);
      s21_size_t needle_len = s21_strlen(needle);

      for (s21_size_t i = 0; i <= haystack_len - needle_len; i++) {
        s21_size_t j = 0;

        while (j < needle_len && haystack[i + j] == needle[j]) {
          j++;
        }

        if (j == needle_len) {
          _return = (char *)(haystack + i);
          break;
        }
      }
    }
  }

  return _return;
}
