#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>

// Это фигня хранит параментры форматирования
typedef struct {
  char flag[10];
  int width;
  int accuracy;
  char type;
} FormatSpec;

int s21_sprintf(char *dest, const char *format, ...);

// Извлекает модификаторы (флаги, ширину, точность и длину)
int parseFormatModifier(int pos, const char *format, FormatSpec *fmt,
                        va_list *args);

// Вставляет в строку
int insertFormatedValue(char *dest, char symbol, FormatSpec fmt, va_list *args);

// Для устоновления точности по умолчанию
int setDefaultPrecision(int accuracy, int symbol);

// Для c (char)
int s21_ctos(char *dest, va_list *args, char *flag, int accuracy, char type);

// Добавляет отформатированное значение в строку
char *s21_conf(char *dest, FormatSpec fmt, char symbol);

// Для string
char *s21_stos(char *dest, va_list *args, int accuracy, char type);

// Для работы с указателями
char *s21_ptoa(char *dest, int *variable);

// Для int (и других)
char *s21_itoa(char *dest, int number, int accuracy, char *flag);
char *s21_itoa_long(char *dest, long int number, int accuracy, char *flag);
char *s21_itoa_short(char *dest, short int number, int accuracy, char *flag);

// 'g'/'G' - числа с точкой (Высокая точность)
char *s21_gtoa_long(char *dest, long double number, int accuracy, char *flag,
                    int symbol);
char *s21_gtoa(char *dest, double number, int accuracy, char *flag, int symbol);

// Для float
char *s21_ftoa_long(char *dest, long double number, int afterpoint, char *flag,
                    int ttz);
char *s21_ftoa(char *dest, double number, int afterpoint, char *flag, int ttz);

// Для безнаковых типов данных (А также для x, X, o)
char *s21_utoa(char *dest, unsigned int number, int format, int accuracy,
               char *flag);
char *s21_utoa_long(char *dest, unsigned long int number, int format,
                    int accuracy, char *flag);
char *s21_utoa_short(char *dest, unsigned short int number, int format,
                     int accuracy, char *flag);

// Обрабатывает длинные числа в научном формате
char *s21_ntoa_long(char *dest, long double number, int accuracy, char *flag,
                    int symbol, int ttz);
char *s21_ntoa(char *dest, double number, int accuracy, char *flag, int symbol,
               int ttz);

#endif  //! S21_SPRINTF_H
