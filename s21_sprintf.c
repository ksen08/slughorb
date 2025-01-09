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
      format = parser_width(format, args, &specific);
      format = parser_accuracy(format, args, &specific);
      //printf("%d\n",specific.width);
      //printf("%d",specific.accuracy);
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
      // спецификаторы
      switch (*format) {  //
        case 'c':         // diana
          break;
        case 'd':  // ksenia
          spec_d(str,&specific, args);
          break;
        case 'f':  // diana
          break;
        case 's':  // ksenia
          break;
        case 'u':
          break;
        case '%':
          break;
      }
    }
    format++;
  }
 // *str = '\0';
  va_end(args);
  return (str - start);
}

const char *parser_flags(const char *format, spec *specific) {
  while (*format == '-' || *format == '+' || *format == ' ') {
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
    }
    format++;
  }
  specific->space =
      (specific->space &&
       !specific->plus);  // не может быть плюс и пробел одновременно
  return format;
}
const char *parser_wa(const char *format, va_list args, int *value) {
  *value = 0;
  while (*format >= '0' && *format <= '9') {
    *value *= 10;
    *value += *format - '0';
    format++;
  }
  return format;
}

const char *parser_width(const char *format, va_list args, spec *specific) {
  return parser_wa(format, args, &specific->width);
}

const char *parser_accuracy(const char *format, va_list args, spec *specific) {
  if (*format == '.') {
    format++;
    format = parser_wa(format, args, &specific->accuracy);
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
  char buff[1024];
  itoa_s21(n, buff, 10); //преобразовали в строку
  int len = strlen(buff);
  //int len_accuracy_length = 0;
  char *start = str;
  if (specific->width > len) {
    for(int i = 0; i < specific->width - len; i++)
      *str++ = ' ';
  }
  strcpy(str, buff);
  str += len;
  *str = '\0';
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
  s21_sprintf(buffer, "%2d", 320);
  //sprintf(buffer, "%2d", 320);
  printf("%s\n", buffer);
}