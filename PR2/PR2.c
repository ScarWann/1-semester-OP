#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
#endif

#define MAX_LENGTH 1e6
#define MIN_LENGTH 1e-5
#define MAX_DIGITS 8

void loop();
double lineInput(char *);
short precisionInput();
bool endInput();
double input();
void flush_stdin();
bool validTriangle(double, double, double);
double perimeter(double, double, double);
long double area(double, double, double);
double height(double, double, double);
double median(double, double, double);
double bisector(double, double, double);

int main() {
    printf("This is a program for calculating several triangle parameters (perimeter, area, heights, medians and bisectors) based on its sides.\nYou can exit the program by pressing Ctrl+D anytime.\n");
    do {loop();} while (!endInput());
    return 0;
}

void loop() {
    double a = 0;
    double b = 0;
    double c = 0;
    short precision = 0;

    while(!(a = lineInput("BC"))){;}
    while(!(b = lineInput("AC"))){;}
    while(!(c = lineInput("AB"))){;}
    if(!validTriangle(a, b, c)) {
        printf("The sides do not form a valid triangle. Please reenter the numbers correctly\n");
        return;
    }

    printf("Please enter the amount of digits after the comma in the output (max %d): ", MAX_DIGITS);
    while(!(precision = precisionInput())){printf("Invalid input. Try again: ");}

    printf("Perimeter of ABC: %.*lf\n", precision, perimeter(a, b, c));
    printf("Area of ABC: %.*Lf\n", precision, area(a, b, c));
    
    printf("Height AH_1 of ABC: %.*lf\n", precision, height(a, b, c));
    printf("Height BH_2 of ABC: %.*lf\n", precision, height(b, a, c));
    printf("Height CH_3 of ABC: %.*lf\n", precision, height(c, a, b));

    printf("Median AM_1 of ABC: %.*lf\n", precision, median(a, b, c));
    printf("Median BM_2 of ABC: %.*lf\n", precision, median(b, a, c));
    printf("Median CM_3 of ABC: %.*lf\n", precision, median(c, a, b));

    printf("Bisector AL_1 of ABC: %.*lf\n", precision, bisector(a, b, c));
    printf("Bisector BL_2 of ABC: %.*lf\n", precision, bisector(b, a, c));
    printf("Bisector CL_3 of ABC: %.*lf\n", precision, bisector(c, a, b));
}

double lineInput(char *lineName){
    double length;
    printf("Please enter the value of line %s (%.0e to %.0e): ", lineName, MIN_LENGTH, MAX_LENGTH);
    length = input();
    if (!(MIN_LENGTH <= length && length <= MAX_LENGTH)) {
        printf("Invalid input. Try again. ");
        return 0;
    }
    return length;
}

short precisionInput() {
    short precision = 0;
    if (precision > MAX_DIGITS) {
        return 0;
    }
    precision = (short)input();
    return precision;
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
        result = 0;
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

bool validTriangle(double a, double b, double c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}

double perimeter(double a, double b, double c) {
    return a + b + c;
}

long double area(double a, double b, double c) {
    long double p = (a + b + c) / 2;
    return sqrtl(p * (p - a) * (p - b) * (p - c));
}

double height(double oppositeLength, double secondaryLength1, double secondaryLength2) {
    return area(oppositeLength, secondaryLength1, secondaryLength2) * 2 / oppositeLength;
}

double median(double oppositeLength, double secondaryLength1, double secondaryLength2) {
    return 0.5 * sqrt(2 * pow(secondaryLength1, 2) + 2 * pow(secondaryLength2, 2) - pow(oppositeLength, 2));
}

double bisector(double oppositeLength, double secondaryLength1, double secondaryLength2) {
    double p = (oppositeLength + secondaryLength1 + secondaryLength2) / 2;
    return sqrt(secondaryLength1 * secondaryLength2 * p * (p - oppositeLength)) * 2 / (secondaryLength1 + secondaryLength2);
}

