#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char *ptr = str;
  while (*format != '\0') {
    if (*format != '%') {
      *ptr++ = *format;
    } else {
      format++;
      spec specific = {0};
      format = parser_flags(format, &specific);
      format = parser_width(format, args, &specific);
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
      // спецификаторы
      char specifier = *format;
      switch (specifier) {  //
        case 'c':           // diana
          break;
        case 'd':  // ksenia
          spec_d_or_u(ptr, &specific, args, 'd');
          ptr += strlen(ptr);
          break;
        case 'f':  // diana
          break;
        case 's':  // ksenia
          break;
        case 'u':  // ksenia
          spec_d_or_u(ptr, &specific, args, 'u');
          ptr += strlen(ptr);
          break;
        case '%':
          *ptr++ = '%';
          break;
        default:
          break;
      }
    }
    format++;
  }
  *ptr = '\0';
  va_end(args);
  return (str - ptr);
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
void signed_legth(long int *n, spec *specific, va_list args) {
  if (specific->length_h == 1)
    *n = (short)va_arg(args, int);  // извлекаем число
  else if (specific->length_l == 1)
    *n = va_arg(args, long);
  else
    *n = va_arg(args, int);
}
void unsigned_legth(long int *n, spec *specific, va_list args) {
  if (specific->length_h == 1)
    *n = (short unsigned)va_arg(args, unsigned);  // извлекаем число
  else if (specific->length_l == 1)
    *n = (unsigned long)va_arg(args, long long);
  else
    *n = (unsigned)va_arg(args, unsigned);
}
char *spec_d_or_u(char *str, spec *specific, va_list args, char specifier) {
  long n = 0;
  if (specifier == 'd') {
    signed_legth(&n, specific, args);
  } else if (specifier == 'u') {
    unsigned_legth((unsigned long *)&n, specific, args);
  }
  char buff[1024];
  int negative = 0;
  if (n < 0) negative = 1;
  itoa_s21(n, buff);  // преобразовали в строку
  int len = strlen(buff);
  int len2 = len;
  int count = 0;
  if (specific->accuracy && specific->accuracy > len) {
    len2 += specific->accuracy - len - negative;
  }
  if ((negative == 1 || specific->plus == 1 || specific->space == 1) &&
      specifier != 'u') {
    count += 1;
  }
  if (specific->width && specific->width > (len2 + count) && !specific->minus) {
    for (int i = 0; (i - negative) < specific->width - (len2 + count); i++)
      *str++ = ' ';
  }
  if (specifier != 'u') {
    if (negative == 1) {
      *str++ = '-';
    } else if (specific->plus)
      *str++ = '+';
    else if (specific->space)
      *str++ = ' ';
  }
  if (specific->accuracy > len - negative) {
    for (int i = 0; i < specific->accuracy - len; i++) *str++ = '0';
  }
  if (specific->accuracy == 0 && *buff == '0') {
    *buff = ' ';  // потом скорее всего неправильно будет работать
  }
  strncpy(str, buff, len);
  str += len;
  if (specific->width > len2 + count && specific->minus) {  // для минуса
    for (int i = 0; i < specific->width - (len2 + count); i++) *str++ = ' ';
  }
  *str = '\0';
  return str;
}
char *itoa_s21(long int n,
               char *buff) {  // преобразуемое число, строка, которой число
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
// u не надо пробел флаг
int main() {
  char buffer[100];
  // s21_sprintf(buffer, "%15.10lu", 1234567890L);
  sprintf(buffer, "%%", 123);
  // sprintf(buffer, " %5u %5u %.5u", 123, -456, 789); //работает
  /*const char *format = "%hd %ld";
  short sh = 123;
  long lg = 456789L;*/
  // int res1 = s21_sprintf(buffer, format, sh, lg); работает
  //  sprintf(buffer, "% -10.7u", 2147483648);
  //  sprintf(buffer, "+d % d % -d", 123, -456, 789); //работает
  //   sprintf(buffer, "% -10.7u", 3);
  //      sprintf(buffer, "%15.10lu", 1234567890L);//работает
  // sprintf(buffer, "%ld", 2147483648L);  //работает
  //      sprintf(buffer, "% 10.7u", 3);
  //      sprintf(buffer, "%%Uy", 0);
  //      sprintf(buffer, "HH% -10.12dYYY", -146);
  //      sprintf(buffer, "%13.10d", 678); //работал и с отрицательным
  //      числом sprintf(buffer, "%9.1dUy", 0); sprintf(buffer, "HH%2.0dOO",
  //      0); //работает sprintf(buffer, "%.0d", 0); //ничего не должно
  //      выводится sprintf(buffer, "%0.1d", 8581385185); //раб
  //      sprintf(buffer, "%15.10d", 99999); //работает
  // sprintf(buffer, "%15.5ld", 300000000000000);  // работает
  // s21_sprintf(buffer, "%15.5ld", 300000000);
  // sprintf(buffer, "%15.5hd", 300000000);  // не раб
  //           sprintf(buffer, "%+-6.0d\n", 5); //работает
  //           sprintf(buffer, "% +6.0d", 5);  // работает
  //          sprintf(buffer, "%10.8u", -5);  // работал норм
  //          sprintf(buffer, "%-10.8d", 5);  // работал
  //          sprintf(buffer, "%+ 10.8d", 5);//работал
  printf("%s\n", buffer);
}