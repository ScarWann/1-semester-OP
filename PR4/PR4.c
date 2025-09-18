#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
#endif

#define M_PI 3.14159265358979323846

#define MIN_X 1e-4
#define MAX_X 1e3
#define MIN_D 1e-4
#define MAX_D 1e3
#define MIN_E 1e-8
#define MAX_E 1e-3

void loop();
bool validX(float);
bool validDelta(float);
bool validEpsilon(float);
bool conditionalInput(float*, bool (*)(float));
bool endInput();
float input();
void flush_stdin();
float min(float, float);
float max(float, float);
double taylorSin(float, float);

int main() {
    printf("Program for calculating sin(x) with precision e using the Taylor series.\n");
    printf("You can press Ctrl+D to end the program at any time.\n");
    printf("x1 and x2 are interchangable, their order of input and relation doesn't matter\n");
    do {loop();} while (!endInput());
    return 0;
}

void loop() {
    float x1 = 0;
    printf("Enter x1 (in degrees) in range [%.0e, %.0e]: ", MIN_X, MAX_X);
    while (!conditionalInput(&x1, &validX)) {}

    float x2 = 0;
    printf("Enter x2 (in degrees) in range [%.0e, %.0e]: ", MIN_X, MAX_X);
    while (!conditionalInput(&x2, &validX)) {}

    float d = 0;
    printf("Enter step d (in degrees) in range [%.0e, %.0e]: ", MIN_D, MAX_D);
    while (!conditionalInput(&d, &validDelta)) {}

    float e = 0;
    printf("Enter precision e in range [%.0e, %.0e]: ", MIN_E, MAX_E);
    while (!conditionalInput(&e, &validEpsilon)) {}

    float minX = min(x1, x2);
    float maxX = max(x1, x2);
    float x = 0;
    if (d > 0) {
        x = minX;
    } else {
        x = maxX;
    }

    unsigned int digits = (unsigned int)-log10f(e) + 1;
    int spacing = digits + 10;
    double mathhResult = 0;
    double taylorResult = 0;
    double deltaError = 0;
    
    printf("%-*s %-*s %-*s %-*s\n", spacing, "--x--", spacing, "--sin(x)--", spacing, "--taylorSin(x)--", spacing, "--taylorSin(x) - sin(x)--");
    do {
        mathhResult = sin(M_PI * x / 180);
        taylorResult = taylorSin(x, e);
        deltaError = taylorResult - mathhResult;
        printf("%-*f %-*.*lf %-*.*lf %-*.*e\n", spacing, x, spacing, digits, mathhResult, spacing, digits, taylorResult, spacing, digits, deltaError);
        x += d;
    } while (x <= maxX && x >= minX);
}

bool validX(float x) {
    return fabs(x) <= MAX_X && fabs(x) >= MIN_X;
}

bool validDelta(float d) {
    return fabs(d) <= MAX_D && fabs(d) >= MIN_D;
}

bool validEpsilon(float e) {
    return e <= MAX_E && e >= MIN_E;
}

bool conditionalInput(float *var, bool (*condition)(float)) {
    float temp = 0;
    temp = input();
    if (!((temp == temp) && condition(temp))){
        printf("Invalid input. Try again: ");
        return false;
    }
    *var = temp;
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

float input() {
    short success = 0;
    float result = 0;
    success = scanf("%f", &result);
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

float min(float x1, float x2) {
    if (x1 > x2) {
        return x2;
    }
    return x1;
}

float max(float x1, float x2) {
    if (x1 > x2) {
        return x1;
    }
    return x2;
}

double taylorSin(float x, float e) {
    double radX = M_PI * x / 180;
    double y = 0, d = radX;
    for (int i = 1; fabs(d) > e; i+=2) {
        y += d;
        d *= -radX * radX / ((i + 1) * (i + 2));
    }
    return y;
}