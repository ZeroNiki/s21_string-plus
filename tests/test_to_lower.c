#include "../test.h"

START_TEST(test_empty_string) {
  char *string = s21_to_lower("");
  ck_assert_str_eq(string, "");
  free(string);
}
END_TEST

START_TEST(test_simple_words_string) {
  char *string = s21_to_lower("HEY! What are u doing out here?!");
  ck_assert_str_eq(string, "hey! what are u doing out here?!");
  free(string);
}
END_TEST

START_TEST(test_numbers_string) {
  char *string = s21_to_lower("1234567890");
  ck_assert_str_eq(string, "1234567890");
  free(string);
}
END_TEST

START_TEST(test_with_special_symbol_n) {
  char *string = s21_to_lower("Hello\nWorld");
  ck_assert_str_eq(string, "hello\nworld");
  free(string);
}
END_TEST

START_TEST(test_with_special_symbol_t) {
  char *string = s21_to_lower("HeLLo\tWORLD");
  ck_assert_str_eq(string, "hello\tworld");
  free(string);
}
END_TEST

START_TEST(test_with_special_symbol_r) {
  char *string = s21_to_lower("Hello\rWorld");
  ck_assert_str_eq(string, "hello\rworld");
  free(string);
}
END_TEST

START_TEST(test_zero_terminated_string) {
  char *string = s21_to_lower("Hello\0 Hey");
  ck_assert_str_eq(string, "hello");
  free(string);
}
END_TEST

Suite *create_to_lower_test(void) {
  Suite *s = suite_create("s21_to_lower_test");
  TCase *ts_core = tcase_create("Core");

  tcase_add_test(ts_core, test_empty_string);
  tcase_add_test(ts_core, test_simple_words_string);
  tcase_add_test(ts_core, test_numbers_string);
  tcase_add_test(ts_core, test_with_special_symbol_n);
  tcase_add_test(ts_core, test_with_special_symbol_t);
  tcase_add_test(ts_core, test_with_special_symbol_r);
  tcase_add_test(ts_core, test_zero_terminated_string);

  suite_add_tcase(s, ts_core);

  return s;
}
