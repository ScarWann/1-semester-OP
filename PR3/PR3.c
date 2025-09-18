#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
#endif

#define MAX_X 1e304
#define MAX_K 1e6
#define MAX_DIGITS 14

void loop();
bool validK(double);
bool validX(double, short);
bool validE(double);
bool endInput();
double input();
void flush_stdin();
double root(double x, int k, double e);

int main() {
    printf("Program for calculating square roots up to a certain precision. You can exit at any time by pressing Ctrl+D\n");
    do {loop();} while (!endInput());
    return 0;
}

void loop() {
    double temp = 0;
    
    int k = 0;
    printf("Enter k (must be a positive integer less than or equal to %.0e): ", MAX_K);
    do {temp = input();} while (!validK(temp));
    k = (int)temp;

    double x = 0;
    printf("Enter x (must have a square root of power %d and be less than %.0e): ", k, MAX_X);
    do {temp = input();} while (!validX(temp, k));
    x = temp;

    double e = 0;
    printf("Enter epsilon (must be a positive number in range [1e-%d, 0.1], prefferably a negative power of 10 (i.e. 1e-6)): ", MAX_DIGITS);
    do {temp = input();} while (!validE(temp));
    e = temp;

    short precision = -log10(e) + 1;
    if (x) {
        printf("The final root value is %.*lf\n", precision, root(x, k, e));
    } else {
        printf("The final root value is 0\n");
    }
}

bool validK(double k) {
    if ((int)k != k || fabs(k) > MAX_K || k == 0) {
        printf("Please enter an integer in the specified range: ");
        return false;
    }
    return true;
}

bool validX(double x, short k) {
    if (x / INFINITY != x / INFINITY) {
        printf("Please enter a finite number: ");
        return false;
    } else if (x > MAX_X) {
        printf("Please enter a number in the specified range: ");
        return false;
    } else if (k > 0 && (k % 2 == 0) && (x < 0)) {
        printf("Please enter a number that has the specified root: ");
        return false;
    } else if (k > 0) {
        return true;
    } else if ((k % 2 == 0) && (x <= 0)) {
        printf("Please enter a number that has the specified root: ");
        return false;
    } else if (x == 0) {
        printf("Please enter a number that has the specified root: ");
        return false;
    }
    return true;
}

bool validE(double e) {
    if (e != e || e * 0 == NAN || e > 0.1 || e < pow(10, -MAX_DIGITS)) {
        printf("Please enter a number in the specified range: ");
        return false;
    }
    return true;
}

bool endInput() {
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

double root(double x, int k, double e) {
    double y = 1, d = 1;
    short precision = -log10(e) + 1;
    unsigned int i = 0;
    while (fabs(d) > e) {
        d = (x / pow(y, k - 1) - y) / k;
        y += d;
        i++;
        if (i < 1e3) {
            printf("Iteration %d: y = %.*lf, delta = %.*lf\n", i, precision, y, precision, d);
        } else if (i == 1e3) {
            printf("Exceeded 1000 iterations, detailed output turned off.\n");
        }
    }
    return y;
}
