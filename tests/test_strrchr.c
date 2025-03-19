#include "../test.h"

void s21_strrchr_test(const char *str, int c);

START_TEST(core_test_1) {
  const char *str1 = "UVAYS";
  char str2 = 'G';
  s21_strrchr_test(str1, str2);
}
END_TEST

START_TEST(core_test_2) {
  const char *str1 = "AY";
  char str2 = 'y';
  s21_strrchr_test(str1, str2);
}
END_TEST

START_TEST(core_test_3) {
  const char *str1 = "ABC";
  char str2 = 'C';
  s21_strrchr_test(str1, str2);
}
END_TEST

START_TEST(edge_test_1) {
  const char str1[] = {'\0', 'A', '\0', 'N', '\0'};
  char str2 = 'N';
  s21_strrchr_test(str1, str2);
}
END_TEST

START_TEST(edge_test_2) {
  const char *str1 = "INGI";
  char str2 = 0;
  s21_strrchr_test(str1, str2);
}
END_TEST

START_TEST(unexp_test_1) {
  const char *str1 = "UVAYSA";
  char str2 = 123;
  s21_strrchr_test(str1, str2);
}
END_TEST

START_TEST(null_ptr) {
  const char *str = NULL;
  char ch = 'e';
  char *res = s21_strrchr(str, ch);
  ck_assert_ptr_eq(res, NULL);
}
END_TEST

Suite *create_strrchr_test(void) {
  Suite *s = suite_create("s21_strrchr_test");
  TCase *ts_core = tcase_create("Core");

  tcase_add_test(ts_core, core_test_1);
  tcase_add_test(ts_core, core_test_2);
  tcase_add_test(ts_core, core_test_3);
  tcase_add_test(ts_core, edge_test_1);
  tcase_add_test(ts_core, edge_test_2);
  tcase_add_test(ts_core, unexp_test_1);
  tcase_add_test(ts_core, null_ptr);

  suite_add_tcase(s, ts_core);

  return s;
}

void s21_strrchr_test(const char *str, int c) {
  char *exp = strrchr(str, c);
  char *res = s21_strrchr(str, c);

  ck_assert_ptr_eq(exp, res);
}
