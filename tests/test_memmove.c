#include "../test.h"

void s21_memmove_test(void *dest, const void *src, s21_size_t n);

// Core
START_TEST(core_test_1) {
  char dest[10] = "abcdef";
  char src[10] = "12345";
  s21_memmove_test(dest, src, 5);
}
END_TEST

START_TEST(core_test_2) {
  char dest[15] = "abcdefgh";
  s21_memmove_test(dest + 2, dest, 5);
}
END_TEST

START_TEST(core_test_3) {
  char dest[15] = "abcdefgh";
  s21_memmove_test(dest, dest + 2, 5);
}
END_TEST

// Edge
START_TEST(edge_test_1) {
  char dest[10] = "";
  char src[10] = "";
  s21_memmove_test(dest, src, 0);
}
END_TEST

START_TEST(edge_test_2) {
  char dest[10] = "abcdef";
  char src[10] = "";
  s21_memmove_test(dest, src, 5);
}
END_TEST

// Unexpected
START_TEST(unexp_test_1) {
  char dest[15] = "overlap";
  s21_memmove_test(dest, dest + 3, 4);
}
END_TEST

Suite *create_memmove_test(void) {
  Suite *suite = suite_create("s21_memmove_test");

  // Core
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, core_test_1);
  tcase_add_test(tc_core, core_test_2);
  tcase_add_test(tc_core, core_test_3);
  suite_add_tcase(suite, tc_core);

  // Edge
  TCase *tc_edge = tcase_create("Edge");
  tcase_add_test(tc_edge, edge_test_1);
  tcase_add_test(tc_edge, edge_test_2);
  suite_add_tcase(suite, tc_edge);

  // Unexpected
  TCase *tc_unexp = tcase_create("Unexpected");
  tcase_add_test(tc_unexp, unexp_test_1);
  suite_add_tcase(suite, tc_unexp);

  return suite;
}

void s21_memmove_test(void *dest, const void *src, s21_size_t n) {
  void *expected = memmove(dest, src, n);
  void *result = s21_memmove(dest, src, n);

  ck_assert_ptr_eq(result, dest);
  ck_assert_str_eq(expected, result);
}
