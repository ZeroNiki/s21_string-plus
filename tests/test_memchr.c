#include "../test.h"

void s21_memchr_test(char *str, int c, s21_size_t n);

// Core
START_TEST(core_test_1) {
  char *str = "HELLO++";
  s21_memchr_test(str, '+', 7);
}
END_TEST

START_TEST(core_test_2) {
  char *str = "JAVA";
  s21_memchr_test(str, 'x', 4);
}
END_TEST

// Edge
START_TEST(edge_test_1) {
  char *str = "";
  s21_memchr_test(str, 'B', 50);
}
END_TEST

START_TEST(edge_test_2) {
  char *str = "abc\0def";
  s21_memchr_test(str, 0, 7);
}
END_TEST

START_TEST(edge_test_3) {
  char *str = "check";
  s21_memchr_test(str, 'e', 0);
}
END_TEST

// Unexpected
START_TEST(unexp_test_1) {
  char str[2] = "B";
  s21_memchr_test(str, 'B', 2);
}
END_TEST

START_TEST(unexp_test_2) {
  char str[10] = "ABCD";
  s21_memchr_test(str, 'A', 20);
}
END_TEST

Suite *create_memchr_test(void) {
  Suite *suite = suite_create("s21_memchr_test");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, core_test_1);
  tcase_add_test(tc_core, core_test_2);
  suite_add_tcase(suite, tc_core);

  TCase *tc_edge = tcase_create("Edge");
  tcase_add_test(tc_edge, edge_test_1);
  tcase_add_test(tc_edge, edge_test_2);
  tcase_add_test(tc_edge, edge_test_3);
  suite_add_tcase(suite, tc_edge);

  TCase *tc_unexp = tcase_create("Unexpected");
  tcase_add_test(tc_unexp, unexp_test_1);
  tcase_add_test(tc_unexp, unexp_test_2);
  suite_add_tcase(suite, tc_unexp);

  return suite;
}

void s21_memchr_test(char *str, int c, s21_size_t n) {
  char *expected_match = memchr(str, c, n);
  char *match = s21_memchr(str, c, n);

  ck_assert_ptr_eq(expected_match, match);
}
