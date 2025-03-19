#include "../test.h"

START_TEST(test_empty_string1) {
  ck_assert_ptr_eq(s21_strpbrk("", "abc"), strpbrk("", "abc"));
}
END_TEST

START_TEST(test_empty_string2) {
  ck_assert_ptr_eq(s21_strpbrk("abc", ""), strpbrk("abc", ""));
}
END_TEST

START_TEST(test_both_empty_strings) {
  ck_assert_ptr_eq(s21_strpbrk("", ""), strpbrk("", ""));
}
END_TEST

START_TEST(test_no_matching_characters) {
  ck_assert_ptr_eq(s21_strpbrk("abcdef", "xyz"), strpbrk("abcdef", "xyz"));
}
END_TEST

START_TEST(test_matching_single_character) {
  ck_assert_ptr_eq(s21_strpbrk("abcdef", "d"), strpbrk("abcdef", "d"));
}
END_TEST

START_TEST(test_matching_multiple_characters) {
  ck_assert_ptr_eq(s21_strpbrk("abcdef", "cd"), strpbrk("abcdef", "cd"));
}
END_TEST

START_TEST(test_matching_at_start) {
  ck_assert_ptr_eq(s21_strpbrk("abcdef", "a"), strpbrk("abcdef", "a"));
}
END_TEST

START_TEST(test_matching_at_end) {
  ck_assert_ptr_eq(s21_strpbrk("abcdef", "f"), strpbrk("abcdef", "f"));
}
END_TEST

START_TEST(test_with_special_characters) {
  ck_assert_ptr_eq(s21_strpbrk("abc$%^&*()", "$^"),
                   strpbrk("abc$%^&*()", "$^"));
}
END_TEST

START_TEST(test_with_numeric_characters) {
  ck_assert_ptr_eq(s21_strpbrk("1234567890", "567"),
                   strpbrk("1234567890", "567"));
}
END_TEST

START_TEST(test_with_null_character_in_str2) {
  ck_assert_ptr_eq(s21_strpbrk("abcdef", "\0"), strpbrk("abcdef", "\0"));
}
END_TEST

START_TEST(test_partial_overlap) {
  ck_assert_ptr_eq(s21_strpbrk("abcdef", "efg"), strpbrk("abcdef", "efg"));
}
END_TEST

START_TEST(test_full_overlap) {
  ck_assert_ptr_eq(s21_strpbrk("abcdef", "abcdef"),
                   strpbrk("abcdef", "abcdef"));
}
END_TEST

START_TEST(test_zero_terminated_string) {
  ck_assert_ptr_eq(s21_strpbrk("abc\0def", "d"), strpbrk("abc\0def", "d"));
}
END_TEST

START_TEST(test_long_strings) {
  char *str1 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
  char *str2 = "xyz";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

Suite *create_strpbrk_test(void) {
  Suite *s = suite_create("s21_strpbrk_test");
  TCase *ts_core = tcase_create("Core");

  tcase_add_test(ts_core, test_empty_string1);
  tcase_add_test(ts_core, test_empty_string2);
  tcase_add_test(ts_core, test_both_empty_strings);
  tcase_add_test(ts_core, test_no_matching_characters);
  tcase_add_test(ts_core, test_matching_single_character);
  tcase_add_test(ts_core, test_matching_multiple_characters);
  tcase_add_test(ts_core, test_matching_at_start);
  tcase_add_test(ts_core, test_matching_at_end);
  tcase_add_test(ts_core, test_with_special_characters);
  tcase_add_test(ts_core, test_with_numeric_characters);
  tcase_add_test(ts_core, test_with_null_character_in_str2);
  tcase_add_test(ts_core, test_partial_overlap);
  tcase_add_test(ts_core, test_full_overlap);
  tcase_add_test(ts_core, test_zero_terminated_string);
  tcase_add_test(ts_core, test_long_strings);

  suite_add_tcase(s, ts_core);

  return s;
}
