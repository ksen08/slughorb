#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
int main() {
    /*double x = 3.14;
    double n;
    double y = modf(x,&n);
    printf("%lf", y);*/
    char str[] = "-20";
    int n = strlen(str);
    printf("%d", n);
}
/*if (n != 0 ||
      (specific->accuracy != -1 && len_accuracy_length != 0 && n == 0)) {
    if (specific->minus == 1 && n < 0) *str++ = '-';
    if (specific->plus == 1 && n >= 0) *str++ = '+';
    if (specific->space == 1 && n >= 0) *str++ = ' ';
  }



 if (specific->accuracy != -1 && specific->accuracy > len)
    len_accuracy_length = specific->accuracy - len;


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