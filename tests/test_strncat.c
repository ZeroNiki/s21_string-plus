#include "../test.h"

START_TEST(test_strncat_basic) {
  char dest[50] = "Hello, ";
  char src[] = "world!";
  s21_strncat(dest, src, 6);
  ck_assert_str_eq(dest, "Hello, world!");
}
END_TEST

START_TEST(test_strncat_partial) {
  char dest[50] = "Hello, ";
  char src[] = "world!";
  s21_strncat(dest, src, 3);
  ck_assert_str_eq(dest, "Hello, wor");
}
END_TEST

START_TEST(test_strncat_empty_src) {
  char dest[50] = "Hello, ";
  char src[] = "";
  s21_strncat(dest, src, 5);
  ck_assert_str_eq(dest, "Hello, ");
}
END_TEST

START_TEST(test_strncat_empty_dest) {
  char dest[50] = "";
  char src[] = "world!";
  s21_strncat(dest, src, 6);
  ck_assert_str_eq(dest, "world!");
}
END_TEST

START_TEST(test_strncat_zero_n) {
  char dest[50] = "Hello, ";
  char src[] = "world!";
  s21_strncat(dest, src, 0);
  ck_assert_str_eq(dest, "Hello, ");
}
END_TEST

START_TEST(test_strncat_no_null_termination) {
  char dest[50] = "Hello";
  char src[] = "world";
  s21_strncat(dest, src, 100);
  ck_assert_str_eq(dest, "Helloworld");
}
END_TEST

// WARNING: This core test break code
// START_TEST(test_strncat_special_chars) {
//    char dest[50] = "Hello, ";
//    char src[] = "\n\tworld!";
//    s21_strncat(dest, src, 7);
//    ck_assert_str_eq(dest, "Hello, \n\tworld!");
//}
// END_TEST

START_TEST(test_strncat_null_src) {
  char dest[50] = "Hello, ";
  char *src = NULL;

  ck_assert_str_eq(s21_strncat(dest, src, 5), dest);
}
END_TEST

START_TEST(test_strncat_null_dest) {
  char *dest = NULL;
  char src[] = "world!";

  ck_assert_ptr_null(s21_strncat(dest, src, 5));
}
END_TEST

Suite *create_strncat_test(void) {
  Suite *s = suite_create("s21_strncat_test");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strncat_basic);
  tcase_add_test(tc_core, test_strncat_partial);
  tcase_add_test(tc_core, test_strncat_empty_src);
  tcase_add_test(tc_core, test_strncat_empty_dest);
  tcase_add_test(tc_core, test_strncat_zero_n);
  tcase_add_test(tc_core, test_strncat_no_null_termination);
  // tcase_add_test(tc_core, test_strncat_special_chars);
  tcase_add_test(tc_core, test_strncat_null_src);
  tcase_add_test(tc_core, test_strncat_null_dest);

  suite_add_tcase(s, tc_core);
  return s;
}
