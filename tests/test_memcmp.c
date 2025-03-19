#include "../test.h"

void s21_memcmp_test(const void *str1, const void *str2, s21_size_t n);

// Core
START_TEST(core_test_1) {
  char *str1 = "hello";
  char *str2 = "hello";
  s21_memcmp_test(str1, str2, 5);
}
END_TEST

START_TEST(core_test_2) {
  char *str1 = "apple";
  char *str2 = "appla";
  s21_memcmp_test(str1, str2, 5);
}
END_TEST

// Edge
START_TEST(edge_test_1) {
  char *str1 = "";
  char *str2 = "";
  s21_memcmp_test(str1, str2, 0);
}
END_TEST

START_TEST(edge_test_2) {
  char *str1 = "abc\0def";
  char *str2 = "abc\0xyz";
  s21_memcmp_test(str1, str2, 7);
}
END_TEST

START_TEST(edge_test_3) {
  char *str1 = "hello";
  char *str2 = "hellooo";
  s21_memcmp_test(str1, str2, 4);
}
END_TEST

// Unexpected
START_TEST(unexp_test_1) {
  char str1[5] = "1234";
  int str2[5] = {49, 50, 51, 52, 0};
  s21_memcmp_test(str1, str2, 5);
}
END_TEST

START_TEST(unexp_test_2) {
  char str1[1000] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
  char str2[1000] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567880";
  s21_memcmp_test(str1, str2,
                  1000);  // Строки идентичны, за исключением последнего символа
}
END_TEST

Suite *create_memcmp_test(void) {
  Suite *suite = suite_create("s21_memcmp_test");

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

void s21_memcmp_test(const void *str1, const void *str2, s21_size_t n) {
  int exp = memcmp(str1, str2, n);
  int res = s21_memcmp(str1, str2, n);

  int expression =
      (exp > 0 && res > 0) || (exp < 0 && res < 0) || (exp == 0 && res == 0);
  ck_assert_int_eq(expression, 1);
}
