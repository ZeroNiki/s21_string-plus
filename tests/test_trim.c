#include "../test.h"

START_TEST(test_trim_normal_strings) {
  const char mas[] = "     &#@\n\n\t Hello, Ricasso! *&#@ \n\t   ";
  const char trim_chars[] = " &#@\n\t";
  char *psrc = s21_trim(mas, trim_chars);
  ck_assert_pstr_eq(psrc, "Hello, Ricasso! *");
  free(psrc);

  const char mas_2[] = "    \n\tHello, Ricasso! *&#@ \n\t   ";
  const char trim_chars_2[] = "";
  char *psrc_2 = s21_trim(mas_2, trim_chars_2);
  ck_assert_pstr_eq(psrc_2, "Hello, Ricasso! *&#@");
  free(psrc_2);

  const char mas_3[] = "*1234";
  const char trim_chars_3[] = "*1234";
  char *psrc_3 = s21_trim(mas_3, trim_chars_3);
  ck_assert_pstr_eq(psrc_3, "\0");
  free(psrc_3);
}
END_TEST

START_TEST(void_src) {
  const char *src = NULL;
  const char *trim_chars = "/";
  char *res = s21_trim(src, trim_chars);

  ck_assert_ptr_eq(res, NULL);
}
END_TEST

START_TEST(test_trim_null) {
  char *res = s21_trim(" hello ", NULL);
  ck_assert_pstr_eq(res, "hello");
  free(res);
}
END_TEST

START_TEST(test_trim_empty) {
  char *res = s21_trim(" hello ", "");
  ck_assert_pstr_eq(res, "hello");
  free(res);
}
END_TEST

Suite *create_trim_test(void) {
  Suite *s = suite_create("s21_trim_test");
  TCase *ts_core = tcase_create("Core");

  tcase_add_test(ts_core, test_trim_normal_strings);
  tcase_add_test(ts_core, void_src);
  tcase_add_test(ts_core, test_trim_null);
  tcase_add_test(ts_core, test_trim_empty);

  suite_add_tcase(s, ts_core);

  return s;
}
