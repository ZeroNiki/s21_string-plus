#include "../test.h"

// Core
START_TEST(core_test_1) {
  char str[10] = "abcdefghi";
  s21_memset(str, 'X', 5);
  ck_assert_str_eq(str, "XXXXXfghi");
}
END_TEST

START_TEST(core_test_2) {
  char str[10] = "abcdefghi";
  s21_memset(str, '0', 10);
  ck_assert_str_eq(str, "0000000000");
}
END_TEST

// Edge
START_TEST(edge_test_1) {
  char str[10] = "abcdefghi";
  s21_memset(str, 'X', 0);
  ck_assert_str_eq(str, "abcdefghi");
}
END_TEST

START_TEST(edge_test_2) {
  char str[10] = "abcdefghi";
  s21_memset(str, 'A', 1);
  ck_assert_str_eq(str, "Abcdefghi");
}
END_TEST

START_TEST(edge_test_3) {
  char str[10] = "";
  s21_memset(str, 'Z', 0);
  ck_assert_str_eq(str, "");
}
END_TEST

Suite *create_memset_test(void) {
  Suite *suite = suite_create("s21_memset_test");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, core_test_1);
  tcase_add_test(tc_core, core_test_2);
  suite_add_tcase(suite, tc_core);

  TCase *tc_edge = tcase_create("Edge");
  tcase_add_test(tc_edge, edge_test_1);
  tcase_add_test(tc_edge, edge_test_2);
  tcase_add_test(tc_edge, edge_test_3);
  suite_add_tcase(suite, tc_edge);

  return suite;
}
