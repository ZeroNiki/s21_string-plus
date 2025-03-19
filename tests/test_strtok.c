#include "../test.h"

START_TEST(test_strtok_simple_strings) {
  char mas[] = "/testing/with/original/string.h/";
  char mas_1[] = "/testing/with/original/string.h/";
  char del_2[3] = "/";
  char *nstr_1, *nstr_2;
  nstr_1 = strtok(mas, del_2);
  nstr_2 = s21_strtok(mas_1, del_2);
  while (nstr_1 != s21_NULL) {
    ck_assert_pstr_eq(nstr_1, nstr_2);
    nstr_1 = strtok(s21_NULL, del_2);
    nstr_2 = s21_strtok(s21_NULL, del_2);
  }

  char mas_4[] = ". . testing with original string.h";
  char mas_5[] = ". . testing with original string.h";
  char del_6[3] = ". ";
  nstr_1 = strtok(mas_4, del_6);
  nstr_2 = s21_strtok(mas_5, del_6);
  while (nstr_1 != s21_NULL) {
    ck_assert_pstr_eq(nstr_1, nstr_2);
    nstr_1 = strtok(s21_NULL, del_6);
    nstr_2 = s21_strtok(s21_NULL, del_6);
  }

  char mas_7[] = "testing with original string.h";
  char mas_8[] = "testing with original string.h";
  char del_9[3] = ". ";
  nstr_1 = strtok(mas_7, del_9);
  nstr_2 = s21_strtok(mas_8, del_9);
  while (nstr_1 != s21_NULL) {
    ck_assert_pstr_eq(nstr_1, nstr_2);
    nstr_1 = strtok(s21_NULL, del_9);
    nstr_2 = s21_strtok(s21_NULL, del_9);
  }
}
END_TEST

Suite *create_strtok_test(void) {
  Suite *s = suite_create("s21_strtok_test");
  TCase *ts_core = tcase_create("Core");

  tcase_add_test(ts_core, test_strtok_simple_strings);

  suite_add_tcase(s, ts_core);

  return s;
}
