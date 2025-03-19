#ifndef TEST_H
#define TEST_H

#include <check.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define BUFF_SIZE BUFSIZ

// breaadvi
Suite *create_memchr_test(void);
Suite *create_memcmp_test(void);
Suite *create_memcpy_test(void);
Suite *create_memset_test(void);
Suite *create_strchr_test(void);
Suite *create_to_lower_test(void);
Suite *create_to_upper_test(void);
Suite *create_trim_test(void);
Suite *create_insert_test(void);

// monteala
Suite *create_strncpy_test(void);
Suite *create_strlen_test(void);
Suite *create_strncmp_test(void);
Suite *create_strncat_test(void);
Suite *create_strcspn_test(void);
Suite *create_strerror_test(void);

// nellaror
Suite *create_strpbrk_test(void);
Suite *create_strrchr_test(void);
Suite *create_strstr_test(void);
Suite *create_strtok_test(void);
Suite *create_sprintf_test(void);

// For sprintf (nellaror)
Suite *create_strcmp_test(void);
Suite *create_memmove_test(void);
Suite *create_strcat_test(void);
Suite *create_reverse_test(void);

#endif  //! TEST_H
