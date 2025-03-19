#include "../test.h"

void s21_strcmp_test(const char *str1, const char *str2);

// Core
START_TEST(core_test_1) {
  const char *str1 = "apple";
  const char *str2 = "apple";
  s21_strcmp_test(str1, str2);
}
END_TEST

START_TEST(core_test_2) {
  const char *str1 = "banana";
  const char *str2 = "apple";
  s21_strcmp_test(str1, str2);
}
END_TEST

START_TEST(core_test_3) {
  const char *str1 = "apple";
  const char *str2 = "banana";
  s21_strcmp_test(str1, str2);
}
END_TEST

// Edge
START_TEST(edge_test_1) {
  const char *str1 = "";
  const char *str2 = "non-empty";
  s21_strcmp_test(str1, str2);
}
END_TEST

START_TEST(edge_test_2) {
  const char *str1 = "non-empty";
  const char *str2 = "";
  s21_strcmp_test(str1, str2);
}
END_TEST

// Unexpected
START_TEST(unexp_test_1) {
  const char *str1 = "longer string with spaces";
  const char *str2 = "longer string with";
  s21_strcmp_test(str1, str2);
}
END_TEST

Suite *create_strcmp_test(void) {
  Suite *suite = suite_create("s21_strcmp_test");

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

void s21_strcmp_test(const char *str1, const char *str2) {
  int expected_result = strcmp(str1, str2);
  int actual_result = s21_strcmp(str1, str2);

  ck_assert_int_eq(expected_result, actual_result);
}
