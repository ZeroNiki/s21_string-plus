#include "../../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  void *_return = s21_NULL;

  if (src != s21_NULL && start_index <= s21_strlen(src)) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = (str != s21_NULL) ? s21_strlen(str) : 0;
    s21_size_t new_len = src_len + str_len + 1;

    char *result = calloc(new_len, sizeof(char));
    if (result != s21_NULL) {
      s21_memcpy(result, src, start_index);

      if (str != s21_NULL) {
        s21_memcpy(result + start_index, str, str_len);
      }

      s21_memcpy(result + start_index + str_len, src + start_index,
                 src_len - start_index);

      result[new_len - 1] = '\0';

      _return = (void *)result;
    }
  }

  return _return;
}
