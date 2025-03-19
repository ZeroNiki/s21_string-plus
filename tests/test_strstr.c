#include "../test.h"

START_TEST(test_strstr_simple_strings) {
  char mas[] = "";
  ck_assert_pstr_eq(strstr(mas, ""), s21_strstr(mas, ""));

  char mas_2[] = "Ricasso progr\0ing in SaMaRkAnD1";
  ck_assert_pstr_eq(strstr(mas_2, "progr"), s21_strstr(mas_2, "progr"));

  char mas_3[] = "qrstwsas\0";
  ck_assert_pstr_eq(strstr(mas_3, "sas"), s21_strstr(mas_3, "sas"));
}
END_TEST

START_TEST(handle_null) {
  const char *haystack = NULL;
  const char *needle = NULL;
  char *res = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(res, NULL);
}
END_TEST

START_TEST(handle_null_2) {
  const char *haystack = "hello";
  const char *needle = NULL;
  char *res = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(res, NULL);
}

Suite *create_strstr_test(void) {
  Suite *s = suite_create("s21_strstr_test");
  TCase *ts_core = tcase_create("Core");

  tcase_add_test(ts_core, test_strstr_simple_strings);
  tcase_add_test(ts_core, handle_null);
  tcase_add_test(ts_core, handle_null_2);

  suite_add_tcase(s, ts_core);

  return s;
}
