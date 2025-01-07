#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char *start = str;
  while (*format) {
    if (*format != '%') {
      *str++ = *format;
    } else {
      format++;
      spec specific = {0};
      format = parser_flags(format, &specific);
      format = parser_width(format, args, &specific.width);
      format = parser_accuracy(format, args, &specific);
      if (*format == 'h' || *format == 'l') {
        switch (*format) {
          case 'h':
            specific.length_h = 1;
            format++;
            break;
          case 'l':
            specific.length_l = 1;
            format++;
            break;
        }
      }
      format++;
      // спецификаторы
      switch (*format) {  //
        case 'c':         // diana
          break;
        case 'd':  // ksenia
          break;
        case 'f':  // diana
          break;
        case 's':  // ksenia
          break;
        case 'u':
          break;
      }
      format++;
      /*if (*format == 'd') {
        int value = va_arg(args, int);  // Извлекаем число
        char temp[50];
        sprintf(temp, "%d", value);  // Преобразуем число в строку

        int len = strlen(temp);
        if (value < 0) len--;  // Учитываем знак для отрицательных чисел
        int zero_padding =
            (specific.accuracy > len) ? specific.accuracy - len : 0;

        // Если число отрицательное, добавляем место для знака
        if (value < 0 && specific.accuracy > len) zero_padding++;

        // Выводим пробелы слева, если ширина больше
        if (specific.width > len + zero_padding && !specific.minus) {
          int padding = specific.width - len - zero_padding;
          while (padding-- > 0) {
            *str++ = ' ';
          }
        }

        // Копируем знак для отрицательных чисел
        if (value < 0) {
          *str++ = '-';
          strcpy(temp, temp + 1);  // Убираем знак из строки
        }

        // Выводим ведущие нули для точности
        while (zero_padding-- > 0) {
          *str++ = '0';
        }

        // Копируем само число
        strcpy(str, temp);
        str += strlen(temp);

        // Выводим пробелы справа, если выравнивание по левому краю
        if (specific.width > len + zero_padding && specific.minus) {
          int padding = specific.width - len - zero_padding;
          while (padding-- > 0) {
            *str++ = ' ';
          }
        }

        format++;
      }
    }*/
      *str = '\0';
      va_end(args);
      return (str - start);
    }
  }
}

const char *parser_flags(const char *format, spec *specific) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '#' ||
         *format == '0') {
    switch (*format) {
      case '+':
        specific->plus = 1;
        break;
      case '-':
        specific->minus = 1;
        break;
      case ' ':
        specific->space = 1;
        break;
      case '0':
        specific->zero = 1;
    }
    format++;
  }
  specific->space =
      (specific->space &&
       !specific->plus);  // не может быть плюс и пробел одновременно
  return format;
}

const char *parser_width(const char *format, va_list args, int *width) {
  /*if (*format ==
      '*') {  // есть два варианта ширины, если не звездочка, то другое
    *width = va_arg(args, int);
    format++;
  } else {  // перевод символа в число
  */
  *width = 0;
  while (*format >= '0' && *format <= '9') {
    *width *= 10;
    *width += *format - '0';
    format++;
  }
  return format;
}
const char *parser_accuracy(const char *format, va_list args, spec *specific) {
  if (*format == '.') {
    specific->point = 1;  // точность используется
    specific->zero = 0;   // тогда не надо ведущие нули
    format++;
    format = parser_width(format, args, &specific->accuracy);
  } else {
    specific->accuracy = -1;  // не указана точность
  }
  return format;
}
void spec_d(char *str, spec *specific, va_list args) {
  long int n = 0;
  if (specific->length_h == 1)
    n = (short)va_arg(args, int);  // извлекаем число
  else if (specific->length_l == 1)
    n = (long)va_arg(args, long int);
  else
    n = va_arg(args, int);
  itoa_s21(n, str, 10);
  int len = strlen(str);
  int len_accuracy_length = 0;
  if (specific->accuracy != -1 && specific->accuracy > len)
    len_accuracy_length = specific->accuracy - len;
  // добавление знака
  /*if (specific->minus == 1)
    *str++ = '-';
  else if (specific->plus == 1)
    *str++ = '+';
  else if (specific->space == 1)
    *str++ = ' ';*/
  // добавить обработку числа 0 с точностью 0
  if (n != 0 ||
      (specific->accuracy != -1 && len_accuracy_length != 0 && n == 0)) {
    if (specific->minus == 1 && n < 0) *str++ = '-';
    if (specific->plus == 1 && n >= 0) *str++ = '+';
    if (specific->space == 1 && n >= 0) *str++ = ' ';
    if (specific->zero == 1) {
      for (int i = 0; i < len_accuracy_length; i++) *str++ = '0';
    }
  }
}
char *itoa_s21(long int n, char *buff,
               int base) {  // преобразуемое число, строка, которой число
                            // должно стать, основание системы
  int i = 0;
  int minus = 0;
  if (n < 0) {
    minus = 1;
    n = -n;
  }
  if (n == 0) {
    buff[i++] = '0';
  }
  while (n > 0) {
    long int next = n % 10;
    if (next < 10)
      buff[i++] = next + '0';
    else
      buff[i++] = next - 10 + 'A';
    n /= 10;
  }
  buff[i] = '\0';
  return reverse(buff, 0, i - 1);
}

char *reverse(char *str, int start, int end) {
  char temp;
  while (start < end) {
    temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
  return str;
}
int main() {
  char buffer[100];
  s21_sprintf(buffer, "%4d", 4, 42);
  printf("Result: '%s'\n", buffer);
  int n = 28;
  printf("%d", n / 10);
}