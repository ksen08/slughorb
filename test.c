#include <stdio.h>
#include <math.h>

int main() {
    double x = 3.14;
    double n;
    double y = modf(x,&n);
    printf("%lf", y);
}