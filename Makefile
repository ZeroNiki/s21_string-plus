# Компиляция
CC = gcc
GCOV_FLAGS = --coverage -fprofile-arcs -ftest-coverage -lgcov
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
COVRFLAGS = --html --html-details --exclude-lines-by-pattern '.*assert.*' --exclude '.*test_.*' --exclude '.*run.c*'

# Библеотеки
CHECKFLAGS = -lcheck -lsubunit -lrt -lm

# Папки
CODE_DIR = ./code
TEST_DIR = ./tests
BONUS_DIR = $(CODE_DIR)/bonus
IO_DIR = $(CODE_DIR)/stdio

# Debug
MEM_REP = ./mem_rep.txt

# Исходники
TARGET_SRC = $(wildcard $(CODE_DIR)/*.c) $(wildcard $(BONUS_DIR)/*.c) $(wildcard $(IO_DIR)/*.c)
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)

TARGET_OBJ = $(TARGET_SRC:.c=.o)
GCOV_OBJ = $(TARGET_SRC:.c=.gcov.o)

LIBRARY = s21_string.a
GCOV_LIB = s21_string_gcov.a

TEST_EXEC = run_tests
COV_EXEC = run_gcov_tests

all: $(LIBRARY)

review: $(GCOV_LIB) gcov_report

# Статика для тестов
$(LIBRARY): clean $(TARGET_OBJ)
			ar rcs $(LIBRARY) $(TARGET_OBJ)
			ranlib $(LIBRARY)

# Статика для рапорта
$(GCOV_LIB): clean $(GCOV_OBJ)
			ar rcs $(GCOV_LIB) $(GCOV_OBJ)
			ranlib $(GCOV_LIB)

# Сборка и запуск проекта
test: clean $(TEST_EXEC)
			@./$(TEST_EXEC)

# Тоже самое но для gcovr
gcov_exec: clean $(COV_EXEC)
			@./$(COV_EXEC)

# Сам рапорт
gcov_report: gcov_exec
			mkdir gcov-rep
			mkdir lcov-rep
			lcov --capture --directory . --output-file lcov-rep/cov.info
			genhtml lcov-rep/cov.info --output-directory lcov-rep
			python3 -m venv venv
			. venv/bin/activate && pip install gcovr
			. venv/bin/activate && gcovr --root . $(COVRFLAGS) --output gcov-rep/report.html && deactivate

			rm -rf ./venv/

# Clang-format в стиле Google
format:
			find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format --style=Google -i {} +
			find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format --style=Google -n {} +

format-check:
			find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format --style=Google -n {} +

# I hate this
memcheck: clean test
			valgrind --tool=memcheck --leak-check=yes ./$(TEST_EXEC) 3>&1 2>&3 | tee $(MEM_REP)
			clear
			grep "ERROR SUMMARY:" -E $(MEM_REP)

check:
			cppcheck $(TARGET_SRC)
			cppcheck $(BONUS_DIR)/*.c
			cppcheck $(IO_DIR)/*.c
			cppcheck $(TEST_SRC)
			cppcheck *.h


# Мусор 1
$(CODE_DIR)/%.o: $(CODE_DIR)/%.c
			$(CC) $(CFLAGS) -c $< -o $@

# Мусор 2
$(CODE_DIR)/%.gcov.o: $(CODE_DIR)/%.c
			$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@

# Компиляция
$(TEST_EXEC): $(TEST_SRC) $(LIBRARY)
			$(CC) $(CFLAGS) -I. -o $@ $^ $(CHECKFLAGS)

# Компиляция для рапорта
$(COV_EXEC): $(TEST_SRC) $(GCOV_LIB)
			$(CC) $(CFLAGS) $(GCOV_FLAGS) -I. -o $@ $^ $(CHECKFLAGS)

# Очистка мусора
clean:
			rm -f $(LIBRARY) $(TEST_EXEC) $(TARGET_OBJ) *.gcda *.gcno *.gcov
			rm -f $(CODE_DIR)/*.gcda $(CODE_DIR)/*.gcno $(CODE_DIR)/*.gcov $(CODE_DIR)/*.gcov.o
			rm -f $(IO_DIR)/*.gcda $(IO_DIR)/*.gcno $(IO_DIR)/*.gcov $(IO_DIR)/*.gcov.o
			rm -f $(BONUS_DIR)/*.gcda $(BONUS_DIR)/*.gcno $(BONUS_DIR)/*.gcov $(BONUS_DIR)/*.gcov.o
			rm -f $(BONUS_DIR)/*.o $(IO_DIR)/*.o
			rm -f $(COV_EXEC) $(GCOV_LIB)
			rm -rf ./venv/
			rm -rf gcov-rep
			rm -rf lcov-report
			rm -rf lcov-rep
			rm -f *.txt

# Для избежания ошибок при компиляции
.PHONY: all test review clean format memcheck gcov_report
