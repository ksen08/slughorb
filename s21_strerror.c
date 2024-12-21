#include "string.h"
#include "string.h"
char *s21_strerror(int errnum);
int main() {
  printf("%s\n", s21_strerror(0));
  printf("ERROR2: %s\n", s21_strerror(1));
  printf("ERROR3: %s\n", s21_strerror(106));
  printf("ERROR4: %s\n", s21_strerror(600));
}

char *s21_strerror(int errnum) {
  char *error[] = ERROR;
  static char buff[2048];
  char *err = s21_NULL;
  if (errnum >= 0 && errnum <= N)
    err = error[errnum];
  else {
    sprintf(buff, "%s%d", "Uknown error: ", errnum);
    err = buff;
  }
  return err;
}