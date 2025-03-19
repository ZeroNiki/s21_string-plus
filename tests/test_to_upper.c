#include "../test.h"

START_TEST(test_empty_string) {
  char *string = s21_to_upper("");
  ck_assert_str_eq(string, "");
  free(string);
}
END_TEST

START_TEST(test_simple_words_string) {
  char *string = s21_to_upper("HEY! What are u doing out here?!");
  ck_assert_str_eq(string, "HEY! WHAT ARE U DOING OUT HERE?!");
  free(string);
}
END_TEST

START_TEST(test_numbers_string) {
  char *string = s21_to_upper("1234567890");
  ck_assert_str_eq(string, "1234567890");
  free(string);
}
END_TEST

START_TEST(test_with_special_symbol_n) {
  char *string = s21_to_upper("Hello\nWorld");
  ck_assert_str_eq(string, "HELLO\nWORLD");
  free(string);
}
END_TEST

START_TEST(test_with_special_symbol_t) {
  char *string = s21_to_upper("HeLLo\tWORLD");
  ck_assert_str_eq(string, "HELLO\tWORLD");
  free(string);
}
END_TEST

START_TEST(test_with_special_symbol_r) {
  char *string = s21_to_upper("Hello\rWorld");
  ck_assert_str_eq(string, "HELLO\rWORLD");
  free(string);
}
END_TEST

START_TEST(test_zero_terminated_string) {
  char *string = s21_to_upper("Hello\0 Hey");
  ck_assert_str_eq(string, "HELLO");
  free(string);
}
END_TEST

START_TEST(test_upper_null_strin) {
  char *res = s21_to_upper(NULL);
  ck_assert_ptr_eq(res, NULL);
}
END_TEST

START_TEST(test_russian_letters) {
  char *res = s21_to_upper("Привет");
  ck_assert_pstr_eq(res, "Привет");
}
END_TEST

Suite *create_to_upper_test(void) {
  Suite *s = suite_create("s21_to_upper_test");
  TCase *ts_core = tcase_create("Core");

  tcase_add_test(ts_core, test_empty_string);
  tcase_add_test(ts_core, test_simple_words_string);
  tcase_add_test(ts_core, test_numbers_string);
  tcase_add_test(ts_core, test_with_special_symbol_n);
  tcase_add_test(ts_core, test_with_special_symbol_t);
  tcase_add_test(ts_core, test_with_special_symbol_r);
  tcase_add_test(ts_core, test_zero_terminated_string);
  tcase_add_test(ts_core, test_upper_null_strin);
  tcase_add_test(ts_core, test_russian_letters);

  suite_add_tcase(s, ts_core);

  return s;
}
