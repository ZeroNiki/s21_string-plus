#include "../test.h"

void s21_strcspn_test(const char *str1, const char *str2);

// Core
START_TEST(core_test_1) {
  char str1[] = "abcdef";
  char str2[] = "x";
  s21_strcspn_test(str1, str2);
}
END_TEST

START_TEST(core_test_2) {
  char str1[] = "abcdef";
  char str2[] = "c";
  s21_strcspn_test(str1, str2);
}
END_TEST

START_TEST(core_test_3) {
  char str1[] = "abcdef";
  char str2[] = "cd";
  s21_strcspn_test(str1, str2);
}
END_TEST

// Edge
START_TEST(edge_test_1) {
  char str1[] = "";
  char str2[] = "abc";
  s21_strcspn_test(str1, str2);
}
END_TEST

START_TEST(edge_test_2) {
  char str1[] = "hello";
  char str2[] = "";
  s21_strcspn_test(str1, str2);
}
END_TEST

// Unexpected
START_TEST(unexp_test_1) {
  char str1[] = "abcxyz";
  char str2[] = "xyz";
  s21_strcspn_test(str1, str2);
}
END_TEST

Suite *create_strcspn_test(void) {
  Suite *suite = suite_create("s21_strcspn_test");

  // Core tests
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, core_test_1);
  tcase_add_test(tc_core, core_test_2);
  tcase_add_test(tc_core, core_test_3);
  suite_add_tcase(suite, tc_core);

  // Edge tests
  TCase *tc_edge = tcase_create("Edge");
  tcase_add_test(tc_edge, edge_test_1);
  tcase_add_test(tc_edge, edge_test_2);
  suite_add_tcase(suite, tc_edge);

  // Unexpected tests
  TCase *tc_unexp = tcase_create("Unexpected");
  tcase_add_test(tc_unexp, unexp_test_1);
  suite_add_tcase(suite, tc_unexp);

  return suite;
}

void s21_strcspn_test(const char *str1, const char *str2) {
  s21_size_t expected_result = strcspn(str1, str2);
  s21_size_t result = s21_strcspn(str1, str2);

  ck_assert_int_eq(expected_result, result);
}
