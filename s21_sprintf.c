#include "string.h"
#include <string.h>

int s21_sprintf(char *str, const char *format, ...){ 
    va_list args; 
    va_start(args, format);
    char *start = str;
    while(*format){
        if(*format != '%'){ 
             *str++ = *format;
        } else { 
            format++;
            spec specific = {0};
            format = parser_flags(format, &specific);
            format = parser_width(format, args, &specific);
 
          /*  //точность  
            if(*format == '.'){ 
 
            } 
            format++; 
 
            //длина 
            if(*format == 'h' || *format == 'l'){ 
                switch(*format){ 
                    case 'h': 
                        break; 
                    case 'l': 
                        break; 
                } 
 
            } 
            format++; 
 
            //спецификаторы 
            switch(*format){ 
                case 'c': 
                    break; 
                case 'd': 
                    break; 
                case 'f': 
                    break; 
                case 's': 
                    break; 
                case 'u': 
                    break; 
            } 
            format++; */
             if (*format == 'd') {
                int value = va_arg(args, int);  // Извлекаем число из args
                char temp[20];
                sprintf(temp, "%d", value);  // Преобразуем число в строку

                // Применяем ширину
                int len = strlen(temp);
                if (specific.width > len) {
                    // Выводим пробелы для выравнивания
                    int padding = specific.width - len;
                    while (padding-- > 0) {
                        *str++ = ' ';  // Пробелы слева
                    }
                }

                // Копируем число
                strcpy(str, temp);
                str += len;
            }
            format++;
        }
    }
    *str = '\0';
    va_end(args);
    return (str-start);
}

const char *parser_flags(const char *format, spec *specific) {
    while (*format == '-' || *format == '+' || *format == ' ' ||
           *format == '#' || *format == '0') {
        switch(*format){ 
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
    specific->space = (specific->space  && !specific->plus); //не может быть плюс и пробел одновременно
    return format;
}

const char *parser_width(const char *format, va_list args, spec *specific) {
    if(*format == '*'){ //есть два варианта ширины, если не звездочка, то другое 
        specific->width = va_arg(args, int); 
        format++; 
    } else { //перевод символа в число
        specific->width = 0;
        while(*format >= '0' && *format <= '9') {
            specific->width *= 10;
            specific->width += *format - '0';
            format++;
        }
    }
    return format;
}
int main() {
    char buffer[100];
    s21_sprintf(buffer, "%*d", 10, 42);
    printf("Result: '%s'\n", buffer);
}


