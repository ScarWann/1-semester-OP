#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
#endif

#define MAX_K 1000
#define MAX_DIGITS 10


void loop();
unsigned short kInput();
double xInput(bool);
double eInput();
bool endInput();
double input();
void flush_stdin();
double root(double x, unsigned short k, double e);

int main() {
    printf("Program for calculating square roots up to a certain precision. You can exit at any time by pressing Ctrl+D\n");
    do {loop();} while (!endInput());
    return 0;
}

void loop() {
    unsigned short k = 0;
    printf("Enter k (must be a positive integer less than or equal to %d): ", MAX_K);
    while(!((k = kInput()))) {printf("Please enter a positive integer in the specified range [1, %d]: ", MAX_K);}

    double x = 0;
    printf("Enter x (must be a number that has a square root of power %d): ", k);
    while(!((x = xInput(!(k % 2))) == x)) {printf("Please enter a number that has a square root of power %d: ", k);}

    double e = 0;
    printf("Enter epsilon (must be a positive number in range [1, 1e-%d], prefferably a negative power of 10 (i.e. 1e-6)): ", MAX_DIGITS);
    while(!((e = eInput()) == e)) {printf("Please enter a positive number in range [1, 1e-%d]: ", MAX_DIGITS);}

    short precision = -log10(e) + 1;
    printf("The final root value is %.*lf\n", precision, root(x, k, e));
}

unsigned short kInput() {
    double k = 0;
    k = input();
    if ((unsigned short)k != k || k > MAX_K || k <= 0) {
        return 0;
    }
    return k;
}

double xInput(bool kIsEven) {
    double x = 0;
    x = input();
    if (kIsEven && x <= 0) {
        return NAN;
    }
    return x;
}

double eInput() {
    double e = 0;
    e = input();
    if (e > 1 || e <= 0) {
        return NAN;
    }
    return e;
}

bool endInput() {
    short success = 0;
    char ch;
    printf("Press Ctrl+D to end program. Enter any key to continue: ");
    ch = getchar();
    if (ch == EOF) {
        printf("End of input detected. Closing program.\n");
        return 1;
    }
    flush_stdin();
    return 0;
}

double input() {
    short success = 0;
    double result = 0;
    success = scanf("%lf", &result);
    if (success == EOF) {
        printf("End of input detected. Closing program.\n");
        exit(0);
    } else if (!success){
        result = NAN;
    }
    flush_stdin();
    return result;
}

void flush_stdin() {
#ifdef _WIN32
    fflush(stdin);
#elif defined(__linux__)
    #ifdef __GLIBC__
        __fpurge(stdin);
    #else
        fpurge(stdin);
    #endif
#endif 
}

double root(double x, unsigned short k, double e) {
    double y = 1, d = 1;
    short precision = -log10(e) + 1;
    short i = 0;
    while (fabs(d) > e) {
        d = (x / pow(y, k - 1) - y) / k;
        y += d;
        i++;
        printf("Iteration %d: y = %.*lf, delta = %.*lf\n", i, precision, y, precision, d);
    }
    return y;
}
