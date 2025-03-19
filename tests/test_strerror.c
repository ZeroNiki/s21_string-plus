#include "../test.h"

// FOR s21_strerror.c
// WINDOWS LIST IS 43 strings long
#if defined(WIN32) || defined(_WIN32)
#define ERRORS_LIST_LENGTH 43
#endif

// LINUX LIST IS 134 strings long
#if defined(__linux__)
#define ERRORS_LIST_LENGTH 134
#endif

// MacOS LIST IS 107 strings long
#if defined(__APPLE__) || defined(__MACH__)
#define ERRORS_LIST_LENGTH 107
#endif

START_TEST(test_cases_in_boundaries) {
  for (int i = 0; i < ERRORS_LIST_LENGTH; i++) {
    if (i >= 0 && i < ERRORS_LIST_LENGTH) {
      ck_assert_str_eq(s21_strerror(i), strerror(i));
    }
  }
}
END_TEST

START_TEST(test_cases_out_of_boundaries) {
  for (int i = 200; i < 250; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(test_negative_integers) {
  for (int i = -10; i < -1; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

Suite *create_strerror_test(void) {
  Suite *s = suite_create("s21_strerror_test");
  TCase *ts_core = tcase_create("Core");

  tcase_add_test(ts_core, test_cases_in_boundaries);
  tcase_add_test(ts_core, test_cases_out_of_boundaries);
  tcase_add_test(ts_core, test_negative_integers);

  suite_add_tcase(s, ts_core);

  return s;
}
