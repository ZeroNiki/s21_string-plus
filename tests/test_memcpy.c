#include "../test.h"
void s21_memcpy_test(int dest_size, const void *src, s21_size_t n);

// Core tests
START_TEST(core_test_1) {
  char src[21] = "TESTTES";
  s21_memcpy_test(10, src, 4);
}
END_TEST

// Edge tests
START_TEST(edge_test_1) {
  char src[21] = "SSSSSSS";
  s21_memcpy_test(21, src, 0);
}
END_TEST

START_TEST(edge_test_2) {
  char src[21] = "SSSSSSS";
  s21_memcpy_test(21, src, 7);
}
END_TEST

// Unexpected tests
START_TEST(unexp_test_1) {
  char src[21] = "TESTTES";
  s21_memcpy_test(21, src, 0);
}
END_TEST

START_TEST(unexp_test_2) {
  char src[21] = "TESTTES";
  s21_memcpy_test(0, src, 0);
}
END_TEST

Suite *create_memcpy_test(void) {
  Suite *suite = suite_create("s21_memcpy_test");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, core_test_1);
  suite_add_tcase(suite, tc_core);

  TCase *tc_edge = tcase_create("Edge");
  tcase_add_test(tc_edge, edge_test_1);
  tcase_add_test(tc_edge, edge_test_2);
  suite_add_tcase(suite, tc_edge);

  TCase *tc_unexp = tcase_create("Unexpected");
  tcase_add_test(tc_unexp, unexp_test_1);
  tcase_add_test(tc_unexp, unexp_test_2);
  suite_add_tcase(suite, tc_unexp);

  return suite;
}

void s21_memcpy_test(int dest_size, const void *src, s21_size_t n) {
  if (dest_size > 0) {
    char *dest_result = calloc(dest_size, sizeof(char));
    char *dest_expected = calloc(dest_size, sizeof(char));

    if (dest_result != s21_NULL && dest_expected != s21_NULL) {
      memcpy(dest_expected, src, n);
      s21_memcpy(dest_result, src, n);

      free(dest_expected);
      free(dest_result);
    }
  }
}
