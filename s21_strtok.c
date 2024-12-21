#include "string.h"

//вызываем первый раз-идет с начала строки
//вызываем второй раз и передаём NULL-идет по оставшейся части строки

//когда строка закончена - возвращает NULL

char *s21_strtok(char *string, const char *delim) {
    static char *prev = s21_NULL;
    char *result = s21_NULL;
    int f = 0;
    if(string) {
        prev = string;
        f = 1;
    }
    if(prev != s21_NULL || *prev != '\0') {
        while(*prev && strchr(delim, *prev)) //пропускаем расзделители в начале строки
            prev++;
        if(*prev == '\0') result = s21_NULL;
        else {
            char *token = prev;
            while(*prev && !strchr(delim, *prev)) //пропускаем расзделители в начале строки
                prev++;
            if(*prev != '\0') {
                *prev = '\0';
                prev++; 
            } else prev = s21_NULL;
            result = token;
        }
        
    }
    return result;
}
int main() {
    char string[] = ", ,!";
    const char *delim = " ,.!";
    char *token = s21_strtok(string, delim);
    if(token == s21_NULL) printf("e");
    printf("%s\n", token);
    char *token2 = s21_strtok(s21_NULL, delim);
    printf("%s\n", token2);
    char *token3 = s21_strtok(s21_NULL, delim);
    printf("%s\n", token3);
   /* while (token != s21_NULL) {
        printf("%s\n", token);
        token = s21_strtok(s21_NULL, delim);  // Продолжаем токенизацию
    }*/
    return 0;
}