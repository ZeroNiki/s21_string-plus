#include "../test.h"

void s21_strcat_test(char *dest, const char *src);

// Core
START_TEST(core_test_1) {
  char dest[20] = "Hello, ";
  char src[10] = "world!";
  s21_strcat_test(dest, src);
}
END_TEST

START_TEST(core_test_2) {
  char dest[20] = "Test";
  char src[10] = "ing";
  s21_strcat_test(dest, src);
}
END_TEST

START_TEST(core_test_3) {
  char dest[30] = "";
  char src[15] = "Empty dest";
  s21_strcat_test(dest, src);
}
END_TEST

// Edge
START_TEST(edge_test_1) {
  char dest[10] = "123";
  char src[10] = "";
  s21_strcat_test(dest, src);
}
END_TEST

START_TEST(edge_test_2) {
  char dest[50] = "";
  char src[50] = "";
  s21_strcat_test(dest, src);
}
END_TEST

// Unexpected
START_TEST(unexp_test_1) {
  char dest[15] = "Overlap";
  s21_strcat_test(dest, dest + 3);
}
END_TEST

Suite *create_strcat_test(void) {
  Suite *suite = suite_create("s21_strcat_test");

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

void s21_strcat_test(char *dest, const char *src) {
  char expected_dest[100];
  char actual_dest[100];

  strcpy(expected_dest, dest);
  strcpy(actual_dest, dest);

  strcat(expected_dest, src);

  s21_strcat(actual_dest, src);

  ck_assert_str_eq(expected_dest, actual_dest);
}
