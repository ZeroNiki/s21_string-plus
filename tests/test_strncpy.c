#include "../test.h"

START_TEST(test_copy_less_than_n) {
  char dest[20];
  const char *src = "hello";
  size_t n = 10;
  char *result = s21_strncpy(dest, src, n);
  ck_assert_str_eq(dest, "hello");
  ck_assert_ptr_eq(result, dest);
  for (size_t i = 5; i < n; i++) {
    ck_assert_int_eq(dest[i], '\0');
  }
}
END_TEST

START_TEST(test_copy_equal_n) {
  char dest[10] = {0};
  const char *src = "hello";
  s21_strncpy(dest, src, 5);
  ck_assert_str_eq(dest, "hello");
}
END_TEST

START_TEST(test_copy_empty_src) {
  char dest[20];
  const char *src = "";
  size_t n = 5;
  char *result = s21_strncpy(dest, src, n);
  ck_assert_str_eq(dest, "");
  for (size_t i = 0; i < n; i++) {
    ck_assert_int_eq(dest[i], '\0');
  }
  ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_n_is_zero) {
  char dest[20] = "existing";
  const char *src = "hello";
  size_t n = 0;
  char *result = s21_strncpy(dest, src, n);
  ck_assert_str_eq(dest, "existing");
  ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_dest_equals_src) {
  char str[20] = "overlap_test";
  char *result = s21_strncpy(str, str, 20);
  ck_assert_str_eq(result, "overlap_test");
  ck_assert_ptr_eq(result, str);
}
END_TEST

Suite *create_strncpy_test(void) {
  Suite *s = suite_create("s21_strncpy_test");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_copy_less_than_n);
  tcase_add_test(tc_core, test_copy_equal_n);
  tcase_add_test(tc_core, test_copy_empty_src);
  tcase_add_test(tc_core, test_n_is_zero);
  tcase_add_test(tc_core, test_dest_equals_src);

  suite_add_tcase(s, tc_core);

  return s;
}
