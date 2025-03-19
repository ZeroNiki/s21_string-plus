#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *next_token = s21_NULL;
  char *current_token = s21_NULL;

  if (str) {
    next_token = str;
  }
  if (next_token) {
    while (*next_token && s21_strchr(delim, *next_token)) {
      next_token++;
    }

    if (*next_token) {
      current_token = next_token;

      while (*next_token && !s21_strchr(delim, *next_token)) {
        next_token++;
      }

      if (*next_token) {
        *next_token = '\0';
        next_token++;
      }
    }
  }

  return current_token;
}
