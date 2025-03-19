#include "../test.h"

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = create_memchr_test();
  sr = srunner_create(s);

  // breaadvi
  srunner_add_suite(sr, create_memcmp_test());
  srunner_add_suite(sr, create_memcpy_test());
  srunner_add_suite(sr, create_memset_test());
  srunner_add_suite(sr, create_strchr_test());
  srunner_add_suite(sr, create_to_lower_test());
  srunner_add_suite(sr, create_to_upper_test());
  srunner_add_suite(sr, create_strlen_test());
  srunner_add_suite(sr, create_trim_test());
  srunner_add_suite(sr, create_insert_test());

  // monteala
  srunner_add_suite(sr, create_strncpy_test());
  srunner_add_suite(sr, create_strncat_test());
  srunner_add_suite(sr, create_strncmp_test());
  srunner_add_suite(sr, create_strcspn_test());
  srunner_add_suite(sr, create_strerror_test());

  // nellaror
  srunner_add_suite(sr, create_strpbrk_test());
  srunner_add_suite(sr, create_strrchr_test());
  srunner_add_suite(sr, create_strstr_test());
  srunner_add_suite(sr, create_strtok_test());
  srunner_add_suite(sr, create_sprintf_test());

  // For sprintf (nellaror)
  srunner_add_suite(sr, create_strcmp_test());
  srunner_add_suite(sr, create_memmove_test());
  srunner_add_suite(sr, create_strcat_test());
  srunner_add_suite(sr, create_reverse_test());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
