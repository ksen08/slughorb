#include "string.h"

#include <stdio.h>
#include <string.h>

#define s21_NULL NULL
typedef size_t s21_size_t;

//если не находит - возвращает NULL
//если находит - возвращает индекс первого вхождения

//Если подстрока substring пуста (длина её равна 0), то согласно стандарту strstr, 
//результатом будет указатель на начало строки string. В этом случае функция сразу возвращает string, 
//устанавливая флаг в 1.

char *s21_strstr(const char *string, const char *substring) {
    char *result = s21_NULL;
    int f = 0;
    if (string == s21_NULL || substring == s21_NULL) return result;
    if (*substring == '\0') result = (char *)string;
    s21_size_t substring_len = strlen(substring);
    s21_size_t string_len = strlen(string);
    if (string_len >= substring_len) {
        for (s21_size_t i = 0; string[i] != '\0' && !f; i++) {
            s21_size_t j = 0;
            while (string[i + j] == substring[j] && substring[j] != '\0') j++;
            if (substring[j] == '\0') {
                result = (char *)&string[i];
                f = 1;
            }
        }
    }
    return result;
}
int main() {
    char *string = "Hello world";
    char *substring = "world";
    char *result = s21_strstr(string, substring);
    //char *result = strstr(string, substring);
   if (result != NULL) {
        printf("Found at position: %ld\n", result - string);
    } else {
        printf("Not found\n");
    }
    return 0;
}



























/*#define s21_size_t unsigned long long 
#define s21_NULL (void*)0

char *s21_strstr(const char *string, const char *substring) { //поиск подстроки в строке
    char *result;
    if(string == s21_NULL || substring == s21_NULL) return s21_NULL;
    if(*substring == '\0') result = (char *)string;
    s21_size_t substring_len = strlen(substring);
    for(s21_size_t i = 0; string[i] != '\0'; i++) {
        s21_size_t string_len = strlen(string);
        if(string_len < substring_len) result = s21_NULL;
        s21_size_t j = 0;
        while(string[i+j] == substring[j] && substring[j] != '\0') j++;
        if(substring[j] == '\0') result = (char *)&string[i];
    }
    return result;
}

int main() {
    char *string = "Hello, world";
    char *substring = "";
    //char *result = s21_strstr(string, substring);
    char *result = strstr(string, substring);
    if (result != NULL) {
        printf("Founds at position: %ld\n", result - string);
    } else {
        printf("Not found\n");
    }

    return 0;
}
*/