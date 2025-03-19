#include "../test.h"

START_TEST(simple_test) {
  char str[] = "hello";
  ck_assert_pstr_eq(s21_reverse(str), "olleh");
}
END_TEST

START_TEST(null_ptr) {
  char *str = NULL;
  ck_assert_pstr_eq(s21_reverse(str), NULL);
}
END_TEST

Suite *create_reverse_test(void) {
  Suite *s = suite_create("s21_reverse_test");
  TCase *ts_core = tcase_create("Core");

  tcase_add_test(ts_core, simple_test);
  tcase_add_test(ts_core, null_ptr);

  suite_add_tcase(s, ts_core);

  return s;
}
