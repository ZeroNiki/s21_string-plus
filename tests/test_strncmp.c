#include "../test.h"

void s21_strncmp_test(const char *str1, const char *str2, s21_size_t n);

// Core
START_TEST(core_test_1) {
  const char str1[] = "Hello";
  const char str2[] = "Hello";
  s21_strncmp_test(str1, str2, 5);
}
END_TEST

START_TEST(core_test_2) {
  const char str1[] = "Hello";
  const char str2[] = "Hello, World!";
  s21_strncmp_test(str1, str2, 5);
}
END_TEST

START_TEST(core_test_3) {
  const char str1[] = "Hello";
  const char str2[] = "Hellz";
  s21_strncmp_test(str1, str2, 5);
}
END_TEST

// Edge
START_TEST(edge_test_1) {
  const char str1[] = "abc";
  const char str2[] = "abcd";
  s21_strncmp_test(str1, str2, 3);
}
END_TEST

START_TEST(edge_test_2) {
  const char str1[] = "abcd";
  const char str2[] = "abc";
  s21_strncmp_test(str1, str2, 4);
}
END_TEST

START_TEST(edge_test_3) { ck_assert_int_eq(s21_strncmp("abc", "abc", 5), 0); }
END_TEST

START_TEST(edge_test_4) {
  ck_assert_int_lt(s21_strncmp("", "abc", 3), 0);
  ck_assert_int_gt(s21_strncmp("abc", "", 3), 0);
}
END_TEST

START_TEST(edge_test_5) { ck_assert_int_gt(s21_strncmp("hello", "hel", 5), 0); }
END_TEST

// Unexpected
START_TEST(unexp_test_1) {
  const char str1[] = "abc";
  const char str2[] = "abc";
  s21_strncmp_test(str1, str2, 0);
}
END_TEST

Suite *create_strncmp_test(void) {
  Suite *suite = suite_create("s21_strncmp_test");

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
  tcase_add_test(tc_edge, edge_test_3);
  tcase_add_test(tc_edge, edge_test_4);
  tcase_add_test(tc_edge, edge_test_5);
  suite_add_tcase(suite, tc_edge);

  // Unexpected tests
  TCase *tc_unexp = tcase_create("Unexpected");
  tcase_add_test(tc_unexp, unexp_test_1);
  suite_add_tcase(suite, tc_unexp);

  return suite;
}

void s21_strncmp_test(const char *str1, const char *str2, s21_size_t n) {
  int expected_result = strncmp(str1, str2, n);
  int result = s21_strncmp(str1, str2, n);

  ck_assert_int_eq(expected_result, result);
}
