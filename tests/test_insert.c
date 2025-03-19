#include "../test.h"

START_TEST(test_insert_simple_string) {
  const char mas[] = "dom";
  char *mas_2 = (char *)s21_insert(mas, "ran", 0);
  ck_assert_pstr_eq(mas_2, "random");
  free(mas_2);

  const char mas2[] = {'d', 'o', 'm'};
  mas_2 = (char *)s21_insert(mas2, "ran", 0);
  ck_assert_pstr_eq(mas_2, "randomdom");
  free(mas_2);

  const char *mas_4 = s21_NULL;
  mas_2 = (char *)s21_insert(mas_4, "maz", 0);
  ck_assert_pstr_eq(mas_2, s21_NULL);
  free(mas_2);

  mas_2 = (char *)s21_insert(mas, mas_4, 0);
  ck_assert_pstr_eq(mas_2, "dom");
  free(mas_2);
}
END_TEST

START_TEST(test_insert_null_src) {
  char *res = (char *)s21_insert(NULL, "test", 0);
  ck_assert_pstr_eq(res, s21_NULL);
}
END_TEST

START_TEST(test_insert_null_str) {
  const char *src = "hello";
  char *result = (char *)s21_insert(src, NULL, 3);
  ck_assert_pstr_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_insert_empty_string) {
  const char *src = "world";
  char *result = (char *)s21_insert(src, "", 3);
  ck_assert_pstr_eq(result, "world");
  free(result);
}
END_TEST

START_TEST(test_insert_start_index_out_of_bounds) {
  const char *src = "abc";
  char *result = (char *)s21_insert(src, "XYZ", 5);
  ck_assert_pstr_eq(result, s21_NULL);
}
END_TEST

START_TEST(test_insert_at_start) {
  const char *src = "world";
  char *result = (char *)s21_insert(src, "hello ", 0);
  ck_assert_pstr_eq(result, "hello world");
  free(result);
}
END_TEST

START_TEST(test_insert_at_end) {
  const char *src = "hello";
  char *result = (char *)s21_insert(src, " world", 5);
  ck_assert_pstr_eq(result, "hello world");
  free(result);
}
END_TEST

START_TEST(test_insert_at_middle) {
  const char *src = "he world";
  char *result = (char *)s21_insert(src, "llo", 2);
  ck_assert_pstr_eq(result, "hello world");
  free(result);
}
END_TEST

START_TEST(allocation_failure) {
  const char *src = "test";
  const char *str = "ing";

  char *result = (char *)s21_insert(src, str, 2);
  if (!result) {
    ck_assert_ptr_eq(result, s21_NULL);
  } else {
    free(result);
  }
}
END_TEST

Suite *create_insert_test(void) {
  Suite *s = suite_create("s21_insert_test");
  TCase *ts_core = tcase_create("Core");

  tcase_add_test(ts_core, test_insert_simple_string);
  tcase_add_test(ts_core, test_insert_null_src);
  tcase_add_test(ts_core, test_insert_null_str);
  tcase_add_test(ts_core, test_insert_empty_string);
  tcase_add_test(ts_core, test_insert_start_index_out_of_bounds);
  tcase_add_test(ts_core, test_insert_at_start);
  tcase_add_test(ts_core, test_insert_at_end);
  tcase_add_test(ts_core, test_insert_at_middle);
  tcase_add_test(ts_core, allocation_failure);

  suite_add_tcase(s, ts_core);

  return s;
}
