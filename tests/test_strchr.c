#include "../test.h"

void s21_strchr_test(const char *str, int c);

// Core
START_TEST(core_test_1) {
  char str[] = "Hello, World!";
  s21_strchr_test(str, 'o');
}
END_TEST

START_TEST(core_test_2) {
  char str[] = "abcdef";
  s21_strchr_test(str, 'z');
}
END_TEST

// Edge
START_TEST(edge_test_1) {
  char str[] = "Hello";
  s21_strchr_test(str, 'H');
}
END_TEST

START_TEST(edge_test_2) {
  char str[] = "Test";
  s21_strchr_test(str, '\0');
}
END_TEST

// Unexpected
START_TEST(unexp_test_1) {
  char *str = "A";
  s21_strchr_test(str, ' ');
}
END_TEST

Suite *create_strchr_test(void) {
  Suite *suite = suite_create("s21_strchr_test");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, core_test_1);
  tcase_add_test(tc_core, core_test_2);
  tcase_add_test(tc_core, edge_test_1);
  tcase_add_test(tc_core, edge_test_2);
  suite_add_tcase(suite, tc_core);

  TCase *tc_unexp = tcase_create("Unexpected");
  tcase_add_test(tc_unexp, unexp_test_1);
  suite_add_tcase(suite, tc_unexp);

  return suite;
}

void s21_strchr_test(const char *str, int c) {
  char *expected_match = strchr(str, c);
  char *res_match = s21_strchr(str, c);

  ck_assert_ptr_eq(expected_match, res_match);
}
