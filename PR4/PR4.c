#include <stdio.h>
#include <math.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
#endif
#include <stdbool.h>

double taylorSin(double, double);

int main() {
    printf("sin (x) with precision e: %lf", taylorSin(3, 0.000001));
}

double taylorSin(double x, double e) {
    double y = 0, d = x;
    for (int i = 1; fabs(d) > e; i+=2) {
        y += d;
        d *= -x * x / ((i + 1) * (i + 2));
    }
    return y;
}