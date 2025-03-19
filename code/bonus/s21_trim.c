#include "../../s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *_return = s21_NULL;

  if (src) {
    if (!trim_chars || trim_chars[0] == '\0') {
      trim_chars = "\t\n ";
    }

    int start = 0;
    while (src[start] && s21_strchr(trim_chars, src[start])) {
      start++;
    }

    int end = s21_strlen(src) - 1;
    while (end >= start && s21_strchr(trim_chars, src[end])) {
      end--;
    }

    int trimmed_length = (end >= start) ? (end - start + 1) : 0;

    char *result = (char *)malloc(trimmed_length + 1);
    if (result) {
      s21_strncpy(result, src + start, trimmed_length);
      result[trimmed_length] = '\0';
      _return = result;
    }
  }

  return _return;
}
