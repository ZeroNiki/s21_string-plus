#include "../test.h"

START_TEST(test_strlen_basic) {
  char str[] = "Hello, world!";
  ck_assert_int_eq(s21_strlen(str), 13);
}
END_TEST

START_TEST(test_strlen_empty_string) {
  char str[] = "";
  ck_assert_int_eq(s21_strlen(str), 0);
}
END_TEST

START_TEST(test_strlen_single_char) {
  char str[] = "A";
  ck_assert_int_eq(s21_strlen(str), 1);
}
END_TEST

START_TEST(test_strlen_spaces) {
  char str[] = "    ";
  ck_assert_int_eq(s21_strlen(str), 4);
}
END_TEST

START_TEST(test_strlen_special_chars) {
  char str[] = "\n\t\r";
  ck_assert_int_eq(s21_strlen(str), 3);
}
END_TEST

START_TEST(test_strlen_long_string) {
  char str[1001];
  for (int i = 0; i < 1000; i++) {
    str[i] = 'a';
  }
  str[1000] = '\0';
  ck_assert_int_eq(s21_strlen(str), 1000);
}
END_TEST

START_TEST(test_strlen_null_pointer) {
  const char *str = NULL;
  ck_assert_int_eq(s21_strlen(str), 0);
}
END_TEST

Suite *create_strlen_test(void) {
  Suite *s = suite_create("s21_strlen_test");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strlen_basic);
  tcase_add_test(tc_core, test_strlen_empty_string);
  tcase_add_test(tc_core, test_strlen_single_char);
  tcase_add_test(tc_core, test_strlen_spaces);
  tcase_add_test(tc_core, test_strlen_special_chars);
  tcase_add_test(tc_core, test_strlen_long_string);
  tcase_add_test(tc_core, test_strlen_null_pointer);

  suite_add_tcase(s, tc_core);
  return s;
}
