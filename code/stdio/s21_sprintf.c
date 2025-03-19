#include "../../s21_string.h"

int s21_sprintf(char *dest, const char *format, ...) {
  dest[0] = '\0';

  // работа с ... (Произвольное кол-во аргументов)
  va_list args;
  va_start(args, format);

  int counter = 0;
  for (int x = 0; format[x] != '\0'; x++) {
    if (format[x] == '%') {  // <- обработка спец.
      FormatSpec fmt = {"xxxxx", INT_MIN, INT_MIN, 'x'};
      x = parseFormatModifier(x, format, &fmt, &args);

      if (format[x] == 'n') {  // <-  обработка спец. %n (Аналог count)
        *(va_arg(args, int *)) = counter;
      } else {
        counter += insertFormatedValue(dest + counter, format[x], fmt, &args);
      }

    } else {  // <- обычные символов
      dest[counter] = format[x];
      dest[counter += 1] = '\0';
    }
  }

  // Конец?
  va_end(args);
  return counter;
}

int parseFormatModifier(int pos, const char *format, FormatSpec *fmt,
                        va_list *args) {
  // Флаги
  for (pos++; s21_strchr("-+ #0", format[pos]); pos++) {
    // логика 5 - s21_strlen(...) предпологает что каждый флаг имеет уникальную
    // позицию
    (fmt->flag)[5 - s21_strlen(s21_strchr("-+ #0", format[pos]))] = 'o';
  }

  // Ширина
  for (; s21_strchr("0123456789", format[pos]); pos++) {
    // Если формат содержит "20d", то fmt->width будет постепенно увеличиваться:
    // 0 > 2 > 20.
    fmt->width = (fmt->width * 10) + (format[pos] - 48);
  }

  // Если т. символ * то ширина будет браться из args
  for (; format[pos] == '*'; pos++) {
    // "*d" и arg = 10, то fmt-width = 10
    fmt->width = va_arg(*args, int);
  }

  // Точность
  if (format[pos] == '.') {
    for (pos++; format[pos] == '-'; pos++) {
      continue;
    }

    // format[pos] = 0123456789, то добавляем в accuracy
    for (; s21_strchr("0123456789", format[pos]); pos++) {
      fmt->accuracy = (fmt->accuracy * 10) + (format[pos] - 48);
    }

    // Если * то точность парситься из args
    for (; format[pos] == '*'; pos++) {
      fmt->accuracy = va_arg(*args, int);
    }
    // Если точность (-) то default (0)
    fmt->accuracy < 0 ? fmt->accuracy = 0 : 0;
  }

  // Длина
  for (; s21_strchr("hlL", format[pos]); pos++) {
    fmt->type = format[pos];
  }

  // Обновлёная позиция
  return pos;
}

int setDefaultPrecision(int accuracy, int symbol) {
  // Тут ничего особеного
  // Просто ставил accuracy для определённых значений
  // в default
  if (accuracy < 0) {
    // Целое число (точность = 0)
    if (s21_strchr("diouxX", symbol)) {
      accuracy = 1;
    }

    // Числа с точкой (точность = 6 (после точки))
    if (s21_strchr("eEfgG", symbol)) {
      accuracy = 6;
    }

    // Указатель
    if (s21_strchr("p", symbol)) {
      accuracy = 16;
    }
  }
  return accuracy;
}

int insertFormatedValue(char *dest, char symbol, FormatSpec fmt,
                        va_list *args) {
  // Основная логи заключается в том чтобы в соответсвии с
  // format вызвать соответствующую ф-ю форматирования
  char *flag = fmt.flag;
  int indent = 0, accuracy = setDefaultPrecision(fmt.accuracy, symbol);

  // %
  if (symbol == '%') {
    s21_strcat(dest, "%");

  } else if (symbol == 'c') {  // <- char
    return s21_ctos(dest + indent, args, flag, fmt.width, fmt.type);

  } else if (s21_strchr("di", symbol)) {  // <- int

    if (fmt.type == 'h') {  // <- длина h (переводит в short int)
      s21_itoa_short(dest + indent, va_arg(*args, int), accuracy, flag);
    } else if (fmt.type == 'l') {  // <- длина l (переводит в long int)
      s21_itoa_long(dest + indent, va_arg(*args, long int), accuracy, flag);
    } else {  // <- просто int
      s21_itoa(dest + indent, va_arg(*args, int), accuracy, flag);
    }

  } else if (symbol == 'p') {  // <- pointer
    s21_ptoa(dest + indent, va_arg(*args, void *));

  } else if (symbol == 's') {  // <- string
    s21_stos(dest + indent, args, accuracy, fmt.type);

  } else if (symbol == 'f') {  // <- float
    if (fmt.type == 'L') {     // <- long double
      s21_ftoa_long(dest + indent, va_arg(*args, long double), accuracy, flag,
                    0);
    } else {  // <- double
      s21_ftoa(dest + indent, va_arg(*args, double), accuracy, flag, 0);
    }

  } else if (s21_strchr(
                 "gG",
                 symbol)) {  // <- числа с плавающей точкой в компактной форме
    if (fmt.type == 'L') {   // <- long double
      s21_gtoa_long(dest + indent, va_arg(*args, long double), accuracy, flag,
                    symbol);
    } else {  // <- double
      s21_gtoa(dest + indent, va_arg(*args, double), accuracy, flag, symbol);
    }

  } else if (s21_strchr("eE", symbol)) {  // <- Экспоненциальная форма
    if (fmt.type == 'L') {
      s21_ntoa_long(dest + indent, va_arg(*args, long double), accuracy, flag,
                    symbol, 0);
    } else {
      s21_ntoa(dest + indent, va_arg(*args, double), accuracy, flag, symbol, 0);
    }

  } else if (s21_strchr("xX", symbol)) {  // <- Шестнадцатеричные числа
    // Условие symbol == 'x' ? 32 : 16 задает формат вывода: 'x' — строчные
    // буквы, 'X' — заглавные.
    if (fmt.type == 'h') {
      s21_utoa_short(dest + indent, va_arg(*args, int), symbol == 'x' ? 32 : 16,
                     accuracy, flag);
    } else if (fmt.type == 'l') {
      s21_utoa_long(dest + indent, va_arg(*args, long int),
                    symbol == 'x' ? 32 : 16, accuracy, flag);
    } else {
      s21_utoa(dest + indent, va_arg(*args, int), symbol == 'x' ? 32 : 16,
               accuracy, flag);
    }

  } else if (symbol == 'o') {  // Восьмеричные числа
    if (fmt.type == 'h') {
      s21_utoa_short(dest + indent, va_arg(*args, unsigned int), 8, accuracy,
                     flag);
    } else if (fmt.type == 'l') {
      s21_utoa_long(dest + indent, va_arg(*args, long unsigned int), 8,
                    accuracy, flag);
    } else {
      s21_utoa(dest + indent, va_arg(*args, unsigned int), 8, accuracy, flag);
    }

  } else if (symbol == 'u') {  // Беззнаковые числа
    // обрабатывается с основанием 10
    if (fmt.type == 'h') {
      s21_utoa_short(dest + indent, va_arg(*args, unsigned int), 10, accuracy,
                     flag);
    } else if (fmt.type == 'l') {
      s21_utoa_long(dest + indent, va_arg(*args, long unsigned int), 10,
                    accuracy, flag);
    } else {
      s21_utoa(dest + indent, va_arg(*args, unsigned int), 10, accuracy, flag);
    }
  }

  // Если символ не принадлежит "n%c", вызывается s21_conf
  s21_strchr("n%c", symbol) ? 0 : s21_conf(dest + indent, fmt, symbol);

  // Длина итоговой строки
  return s21_strlen(dest);
}

char *s21_conf(char *dest, FormatSpec fmt, char symbol) {
  // Здесь происходит проверка, есть ли флаги или ширина
  if (s21_strcmp(fmt.flag, "xxxxx") || fmt.width >= 0 || fmt.type != 'x') {
    // если символ является 'g' или 'G', то убираются завершающие нули в числе
    if (s21_strchr("gG", symbol) && fmt.flag[3] != 'o') {
      if (!(s21_strlen(dest) == 1 && dest[0] == '0')) {
        for (int x = (s21_strlen(dest) - 1); dest[x] == '0';
             dest[x] = '\0', x--) {
          continue;
        }
      }
    }
  }

  char *aux = dest;
  char filler = ' ';
  // Кол-во символов, которые нужно добавить в строку
  int countFill = fmt.width > 0 ? fmt.width - s21_strlen(dest) : 0;

  // Проверка флагов и корректировка положения строки
  if (fmt.flag[4] == 'o') {  // по правому краю
    if (aux[0] == '-') {
      aux++;
    }
    s21_strchr("cs", symbol) ? 0 : (filler = '0');

  } else if (fmt.flag[0] == 'o') {  // по левому
    aux += s21_strlen(aux);
  }

  // Заполнение строки пробелами или нулями
  if (countFill > 0) {
    for (s21_memmove(aux + countFill, aux, s21_strlen(aux) + 1);
         countFill != 0;) {
      aux[countFill - 1] = filler;
      countFill -= 1;
    }
  }

  return dest;
}

int s21_ctos(char *dest, va_list *args, char *flag, int accuracy, char type) {
  int counter = 0;

  if (accuracy < 1) {
    accuracy = 1;
  }

  // Широкие char
  if (type == 'l') {
    wchar_t w_c = va_arg(*args, wchar_t);

    // Широкий char в строку
    wchar_t w_c_array[2] = {w_c, L'\0'};  // Создаем строку из одного символа
    counter += wcstombs(dest + counter, w_c_array, 512);
  } else {
    dest[counter++] = va_arg(*args, int);
    dest[counter] = '\0';
  }

  // Точность
  if (flag[0] != 'o' && accuracy - counter > 0) {
    // Сдвигаем строку вправо, чтобы освободить место
    s21_memmove(dest + (accuracy - counter), dest, counter + 1);

    // Дополнение пробелами
    for (int x = 0; x < accuracy - counter; x += 1) {
      dest[x] = ' ';
    }

    counter = accuracy;
  }

  // Флаги выравнивания по правому флагу
  for (int x = counter; flag[0] == 'o' && x < (accuracy); x += 1) {
    dest[counter++] = ' ';
  }

  return counter;
}

char *s21_stos(char *dest, va_list *args, int accuracy, char type) {
  // Строка с широкими символами
  if (type == 'l') {
    // Wide string в обычнкую строку
    wcstombs(dest, va_arg(*args, wchar_t *), 512);
  } else {
    // Если обычный то просто копируем в dest
    s21_strcat(dest, va_arg(*args, char *));
  }

  if (accuracy < 0) {
    accuracy = s21_strlen(dest);
  }
  dest[accuracy] = '\0';

  return dest;
}

char *s21_ptoa(char *dest, int *variable) {
  int *aux = variable;

  if (aux == s21_NULL) {
    s21_strcat(dest, "0x0");

  } else {
    /* aux = ((void *)(((s21_size_t)aux) >> 4
     * aux в целое (size_t)
     * здвигает на 4 байта вправо
     * Преобразует обратно к указателю типа "void *" */
    for (int x = s21_strlen(dest); aux != 0;
         aux = ((void *)(((s21_size_t)aux) >> 4)), x++) {
      unsigned int last_symbol = ((s21_size_t)aux) % 0x10;

      // Заполняем строку символами, представляющими цифры и буквы в 16x
      if (last_symbol < 10) {
        dest[x] = ('0' + last_symbol);
      } else {
        dest[x] = ('a' + (last_symbol - 10));
      }

      dest[x + 1] = '\0';
    }
    s21_strcat(dest, "x0");
    s21_reverse(dest);  // Для корректного отображения
  }

  return dest;
}

char *s21_utoa(char *dest, unsigned int number, int format, int accuracy,
               char *flag) {
  int lenStr = 0, type = 97, numb = number;

  if (format == 32) {
    format /= 2;
  } else {
    type = 65;
  }

  // Этот цикл преобразует число в строку
  for (; (lenStr < accuracy - 1) || (number / format) != 0;
       number /= format, lenStr++) {
    if ((number % format) < 10) {
      dest[lenStr] = (number % format) + 48;
    } else {
      dest[lenStr] = ((number % format) - 10) + type;
    }
  }

  if (number < 10) {
    dest[lenStr++] = number + 48;
  } else {
    dest[lenStr++] = (number - 10) + type;
  }

  // Обработка флага "o" для 8x
  if (flag[3] == 'o' && format == 8 && number != 0) {
    dest[lenStr++] = '0';
  }
  dest[lenStr] = '\0';

  // Добавление префикса для 16x
  if (flag[3] == 'o' && format == 16 && type == 65 && numb != 0) {
    s21_strcat(dest, "X0");
  }

  if (flag[3] == 'o' && format == 16 && type == 97 && numb != 0) {
    s21_strcat(dest, "x0");
  }

  s21_reverse(dest);
  return dest;
}

char *s21_ntoa_long(char *dest, long double number, int accuracy, char *flag,
                    int symbol, int ttz) {
  int lenStr = 0, lenNum = 0, result = 0, ac = accuracy;
  char flagX[10] = "xxxxx";
  char flag1[10] = "xoxxx";

  //  порядок числа
  if (number != 0) {
    for (int aux = lenNum = fabsl(number) < 1    ? 1
                            : fabsl(number) < 10 ? 0
                                                 : (-1);
         aux != 0; lenNum += aux) {
      // Powl нужен для масштабирования числа
      aux = ((fabsl(number) * powl(10, lenNum)) < 1 ||
             10 < fabsl(number) * powl(10, lenNum))
                ? aux
                : 0;
    }
  }

  // Число в строку
  s21_itoa(dest,
           (ac == 0 ? (roundl(number * powl(10, lenNum)))
                    : (number * powl(10, lenNum))),
           1, flag);

  /*  возвращает символ десятичной точки, определяемый локалью */
  // localeconv()->decimal_point - дес. точка добовляется в строку
  if (ac != 0 || flag[3] == 'o') {
    s21_strcat(dest, (localeconv()->decimal_point));
  }

  for (lenStr = s21_strlen(dest); number < 0; number *= (-1)) {
    continue;
  }

  // Дробная часть
  for (result = lenNum; (accuracy != 0 && (lenNum + 1) <= 0); accuracy--) {
    if (accuracy == 1) {
      s21_itoa(dest + (lenStr++),
               roundl(fmodl((roundl(number) * powl(10, lenNum += 1)), 10)), 1,
               flagX);
    } else {
      s21_itoa(dest + (lenStr++), fmodl((number * powl(10, lenNum += 1)), 10),
               1, flagX);
    }
  }

  // Тоже дробная часть
  for (int aux = lenNum + 1; accuracy != 0; accuracy--) {
    if (accuracy == 1) {
      s21_itoa(dest + (lenStr++),
               roundl(fmodl((number * powl(10, (aux++))), 10)), 1, flagX);
    } else {
      s21_itoa(dest + (lenStr++), fmodl((number * powl(10, (aux++))), 10), 1,
               flagX);
    }
  }

  // Удаление незначащих нулей
  if (ttz == 1 && flag[3] != 'o') {
    for (int x = s21_strlen(dest) - 1; s21_strchr("0.", dest[x]);
         dest[x--] = '\0') {
      continue;
    }

    for (int x = s21_strlen(dest) - 1;
         s21_strchr((localeconv()->decimal_point), dest[x]);) {
      dest[x--] = '\0';
    }
  }

  // Добавление символа и порядка
  lenStr = s21_strlen(dest);
  dest[lenStr++] = symbol;
  dest[lenStr] = '\0';
  s21_itoa(dest + (lenStr), -result, 2, flag1);

  return dest;
}

char *s21_ftoa_long(char *dest, long double number, int afterpoint, char *flag,
                    int ttz) {
  char flagX[10] = "xxxxx";
  int lenStr = 0, minus = 0, ac = afterpoint, k3 = 0;

  // Обработка (-) чисел
  for (; number < 0; number *= (-1), minus = 1) {
    continue;
  }

  // Вычисления др. части
  // ceill - округляет результат вверх
  // truncl - извлекает целую часть
  long double aux =
      ceill((number - truncl(number)) * powl(10, afterpoint) - 0.5);

  // Форматирование др. части
  for (; ((afterpoint != 0) || ((aux / 10) > 1) || (fmodl(aux, 10) > 1));
       afterpoint--, aux /= 10) {
    /* fmodl(aux, 10) - остаток от деления aux на 10 */
    dest[lenStr++] = ((int)fmodl(aux, 10)) + 48;
    dest[lenStr] = '\0';
  }

  // Доп округление
  if (aux == 1) {
    k3 = 1;
  }

  // Добавление дес. точки
  if (ac != 0 || flag[3] == 'o') {
    dest[lenStr++] = (localeconv()->decimal_point)[0];
  }

  if (ac == 0) {
    number = roundl(number);
  }

  // Форм. цел. части
  for (aux = k3 == 1 ? round(number) : number; ((aux / 10) >= 1);
       aux /= 10, dest[lenStr] = '\0') {
    dest[lenStr++] = ((int)fmodl(aux, 10)) + 48;
  }

  s21_itoa(dest + lenStr, fmodl(aux, 10), 1, flagX);

  // Добавление знака минус
  if (minus == 1) {
    s21_strcat(dest, "-");
  }

  lenStr = s21_strlen(dest);

  // Если указаны флаги ('-', и тд)
  if (dest[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o')) {
    dest[lenStr++] = flag[1] == 'o' ? '+' : ' ';
    dest[lenStr] = '\0';
  }

  // Правильный порядок
  s21_reverse(dest);

  // Удаление безполезных нулей
  if (ttz == 1 && flag[3] != 'o') {
    int x = s21_strlen(dest) - 1;

    for (; s21_strchr("0", dest[x]); dest[x--] = '\0') {
      continue;
    }

    if (dest[x] == (localeconv()->decimal_point)[0]) {
      dest[x] = '\0';
    }
  }

  return dest;
}

char *s21_gtoa_long(char *dest, long double number, int accuracy, char *flag,
                    int symbol) {
  int lenNum = 0;

  if (accuracy == 0) {
    accuracy = 1;
  }

  // Обработка нулевого значения
  if (number == 0) {
    s21_ftoa_long(dest, number, accuracy - 1, flag, 1);
  } else {
    // Вычисление порядка числа
    for (int aux = lenNum = fabsl(number) < 1    ? 1
                            : fabsl(number) < 10 ? 0
                                                 : (-1);
         aux != 0; lenNum += aux) {
      aux = ((fabsl(number) * powl(10, lenNum)) < 1 ||
             10 < fabsl(number) * powl(10, lenNum))
                ? aux
                : 0;
    }

    // Эксп. и обычное представление
    if (lenNum <= 0) {  // <- маленькие числа
      if ((accuracy + lenNum) <= 0) {
        s21_ntoa_long(dest, number, accuracy - 1, flag, symbol - 2, 1);
      } else {
        s21_ftoa_long(dest, number, (accuracy - 1) + lenNum, flag, 1);
      }

    } else {  // <- большие числа
      if ((accuracy - 1) <= lenNum) {
        s21_ntoa_long(dest, number, accuracy - 1, flag, symbol - 2, 1);
      } else {
        s21_ftoa_long(dest, number, lenNum + (accuracy - 1), flag, 1);
      }
    }
  }

  return dest;
}

char *s21_itoa(char *dest, int number, int accuracy, char *flag) {
  int lenStr = 0, minus = number < 0 ? (number *= (-1)) : 0;

  if (number < 0) {
    // Форматирования числа (в строковом пред.)
    for (; ((lenStr < accuracy) || (-(number / 10) != 0) ||
            (-(number % 10) != 0));
         number /= 10) {
      dest[lenStr++] = (-(number % 10)) + 48;
    }

  } else {
    for (;
         ((lenStr < accuracy) || ((number / 10) != 0) || ((number % 10) != 0));
         number /= 10) {
      dest[lenStr++] = (number % 10) + 48;
    }
  }

  // Для отрицательных чисел
  if (minus != 0) {
    dest[lenStr++] = '-';
  }

  // Флаги
  if (dest[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o')) {
    if (flag[1] == 'o') {
      dest[lenStr++] = '+';
    } else {
      dest[lenStr++] = ' ';
    }
  }

  dest[lenStr] = '\0';
  s21_reverse(dest);

  return dest;
}

char *s21_utoa_long(char *dest, long unsigned int number, int format,
                    int accuracy, char *flag) {
  // Регистр для 16x чисел
  int lenStr = 0, type = 97, numb = number;

  if (format == 32) {
    format /= 2;
  } else {
    type = 65;
  }

  for (; (lenStr < accuracy - 1) || (number / format) != 0;
       number /= format, lenStr += 1) {
    if ((number % format) < 10) {
      dest[lenStr] = (number % format) + 48;
    } else {
      dest[lenStr] = ((number % format) - 10) + type;
    }
  }

  // Последняя цифра
  if (number < 10) {
    dest[lenStr++] = number + 48;
  } else {
    dest[lenStr++] = (number - 10) + type;
  }

  // префикс для 8x
  if (flag[3] == 'o' && format == 8 && number != 0) {
    dest[lenStr++] = '0';
  }
  dest[lenStr] = '\0';

  // префикс для 16x
  if (flag[3] == 'o' && format == 16 && type == 65 && numb != 0) {
    s21_strcat(dest, "X0");
  }

  if (flag[3] == 'o' && format == 16 && type == 97 && numb != 0) {
    s21_strcat(dest, "x0");
  }

  s21_reverse(dest);

  return dest;
}

char *s21_itoa_long(char *dest, long int number, int accuracy, char *flag) {
  // определение знака числа
  int lenStr = 0;

  long int minus = 0;
  if (number < 0) {
    minus = (number *= (-1));
  }

  // Число в строку в обратном порядке
  if (number < 0) {
    for (; ((lenStr < accuracy) || (-(number / 10) != 0) ||
            (-(number % 10) != 0));
         number /= 10) {
      dest[lenStr++] = (-(number % 10)) + 48;
    }

  } else {
    for (;
         ((lenStr < accuracy) || ((number / 10) != 0) || ((number % 10) != 0));
         number /= 10) {
      dest[lenStr++] = (number % 10) + 48;
    }
  }

  // Знак
  if (minus != 0) {
    dest[lenStr++] = '-';
  }

  // Флаги
  if (dest[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o')) {
    if (flag[1] == 'o') {
      dest[lenStr++] = '+';
    } else {
      dest[lenStr++] = ' ';
    }
  }

  dest[lenStr] = '\0';
  s21_reverse(dest);

  return dest;
}

char *s21_utoa_short(char *dest, short unsigned int number, int format,
                     int accuracy, char *flag) {
  int lenStr = 0, type = 97, numb = number;

  // Регистр
  if (format == 32) {
    format /= 2;
  } else {
    type = 65;
  }

  for (; (lenStr < accuracy - 1) || (number / format) != 0;
       number /= format, lenStr += 1) {
    if ((number % format) < 10) {
      dest[lenStr] = (number % format) + 48;
    } else {
      dest[lenStr] = ((number % format) - 10) + type;
    }
  }

  // Последний разряд
  if (number < 10) {
    dest[lenStr++] = number + 48;
  } else {
    dest[lenStr++] = (number - 10) + type;
  }

  if (flag[3] == 'o' && format == 8 && number != 0) {
    dest[lenStr++] = '0';
  }
  dest[lenStr] = '\0';

  if (flag[3] == 'o' && format == 16 && type == 65 && numb != 0) {
    s21_strcat(dest, "X0");
  }

  if (flag[3] == 'o' && format == 16 && type == 97 && numb != 0) {
    s21_strcat(dest, "x0");
  }

  s21_reverse(dest);

  return dest;
}

char *s21_itoa_short(char *dest, short int number, int accuracy, char *flag) {
  int lenStr = 0, minus = number < 0 ? (number *= (-1)) : 0;

  if (number < 0) {
    for (; ((lenStr < accuracy) || (-(number / 10) != 0) ||
            (-(number % 10) != 0));
         number /= 10) {
      dest[lenStr++] = (-(number % 10)) + 48;
    }
  } else {
    for (;
         ((lenStr < accuracy) || ((number / 10) != 0) || ((number % 10) != 0));
         number /= 10) {
      dest[lenStr++] = (number % 10) + 48;
    }
  }

  if (minus != 0) {
    dest[lenStr++] = '-';
  }

  if (dest[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o')) {
    dest[lenStr++] = flag[1] == 'o' ? '+' : ' ';
  }
  dest[lenStr] = '\0';

  s21_reverse(dest);

  return dest;
}

char *s21_ntoa(char *dest, double number, int accuracy, char *flag, int symbol,
               int ttz) {
  char flagX[10] = "xxxxx";
  char flag1[10] = "xoxxx";
  int lenStr = 0, lenNum = 0, result = 0, ac = accuracy;

  if (number != 0) {
    for (int aux = lenNum = fabs(number) < 1    ? 1
                            : fabs(number) < 10 ? 0
                                                : (-1);
         aux != 0; lenNum += aux) {
      aux = ((fabs(number) * pow(10, lenNum)) < 1 ||
             10 < fabs(number) * pow(10, lenNum))
                ? aux
                : 0;
    }
  }

  s21_itoa(dest,
           (ac == 0 ? (round(number * pow(10, lenNum)))
                    : (number * pow(10, lenNum))),
           1, flag);

  if (ac != 0 || flag[3] == 'o') {
    s21_strcat(dest, (localeconv()->decimal_point));
  }

  for (lenStr = s21_strlen(dest); number < 0; number *= (-1)) {
    continue;
  }

  for (result = lenNum; (accuracy != 0 && (lenNum + 1) <= 0); accuracy -= 1) {
    if (accuracy == 1) {
      s21_itoa(dest + (lenStr++),
               fmod((round(number) * pow(10, lenNum += 1)), 10), 1, flagX);
    } else {
      s21_itoa(dest + (lenStr++), fmod((number * pow(10, lenNum += 1)), 10), 1,
               flagX);
    }
  }

  for (int aux = lenNum + 1; accuracy != 0; accuracy--) {
    accuracy == 1
        ? s21_itoa(dest + (lenStr++),
                   round(fmod((number * pow(10, (aux++))), 10)), 1, flagX)
        : s21_itoa(dest + (lenStr++), fmod((number * pow(10, (aux++))), 10), 1,
                   flagX);
  }

  if (ttz == 1 && flag[3] != 'o') {
    for (int x = s21_strlen(dest) - 1; s21_strchr("0", dest[x]);
         dest[x--] = '\0') {
      continue;
    }
    for (int x = s21_strlen(dest) - 1;
         s21_strchr((localeconv()->decimal_point), dest[x]);) {
      dest[x--] = '\0';
    }
  }

  lenStr = s21_strlen(dest);
  dest[lenStr++] = symbol;
  dest[lenStr] = '\0';

  s21_itoa(dest + (lenStr), -result, 2, flag1);

  return dest;
}

char *s21_ftoa(char *dest, double number, int afterpoint, char *flag, int ttz) {
  char flagX[10] = "xxxxx";
  int lenStr = 0, minus = 0, ac = afterpoint, k3 = 0;

  for (; number < 0; number *= (-1), minus = 1) {
    continue;
  }
  double aux = ceil((number - trunc(number)) * pow(10, afterpoint) - 0.5);

  for (; ((afterpoint != 0) || ((aux / 10) > 1) || (fmod(aux, 10) > 1));
       afterpoint -= 1, aux /= 10) {
    dest[lenStr++] = ((int)fmod(aux, 10)) + 48;
    dest[lenStr] = '\0';
  }

  if (aux == 1) {
    k3 = 1;
  }

  if (ac != 0 || flag[3] == 'o') {
    dest[lenStr++] = (localeconv()->decimal_point)[0];
  }

  if (ac == 0) {
    number = round(number);
  }

  for (aux = k3 == 1 ? round(number) : number; (aux / 10 >= 1);
       aux /= 10, dest[lenStr] = '\0') {
    dest[lenStr++] = ((int)fmod(aux, 10)) + 48;
  }

  s21_itoa(dest + lenStr, fmod(aux, 10), 1, flagX);

  if (minus == 1) {
    s21_strcat(dest, "-");
  }

  lenStr = s21_strlen(dest);

  if (dest[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o')) {
    if (flag[1] == 'o') {
      dest[lenStr++] = '+';
    } else {
      dest[lenStr++] = ' ';
    }

    dest[lenStr] = '\0';
  }

  s21_reverse(dest);

  if (ttz == 1 && flag[3] != 'o') {
    int x = s21_strlen(dest) - 1;
    for (; s21_strchr("0", dest[x]); dest[x--] = '\0') {
      continue;
    }

    if (dest[x] == (localeconv()->decimal_point)[0]) {
      dest[x] = '\0';
    }
  }

  return dest;
}

char *s21_gtoa(char *dest, double number, int accuracy, char *flag,
               int symbol) {
  int lenNum = 0;

  if (accuracy == 0) {
    accuracy = 1;
  }

  if (number == 0) {
    s21_ftoa(dest, number, accuracy - 1, flag, 1);

  } else {
    for (int aux = lenNum = fabs(number) < 1    ? 1
                            : fabs(number) < 10 ? 0
                                                : (-1);
         aux != 0; lenNum += aux) {
      aux = ((fabs(number) * pow(10, lenNum)) < 1 ||
             10 < fabs(number) * pow(10, lenNum))
                ? aux
                : 0;
    }

    if (lenNum <= 0) {
      if (accuracy + lenNum <= 0) {
        s21_ntoa(dest, number, accuracy - 1, flag, symbol - 2, 1);
      } else {
        s21_ftoa(dest, number, (accuracy - 1) + lenNum, flag, 1);
      }

    } else {
      if (lenNum > 4) {
        s21_ntoa(dest, number, accuracy - 1, flag, symbol - 2, 1);
      } else {
        s21_ftoa(dest, number, lenNum + (accuracy - 1), flag, 1);
      }
    }
  }

  return dest;
}
