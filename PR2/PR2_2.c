#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
#endif

#define MAX_LENGTH 1e9
#define MIN_LENGTH 1e-4
#define MAX_DIGITS_OUT 7
#define COMPARISON_EPSILON 1e-9

void loop();
bool validPrecision(float);
bool validLength(float);
bool endInput();
float extraScanf();
void flush_stdin();
bool validTriangle(float, float, float);
float perimeter(float, float, float);
double area(float, float, float);
float height(float, float, float);
float median(float, float, float);
float bisector(float, float, float);

int main() {
    printf("This is a program for calculating several triangle parameters (perimeter, area, heights, medians and bisectors) based on its sides.\n"
           "You can exit the program by pressing Ctrl+D anytime.\n");
    do {
        loop();
    } while (!endInput());
    return 0;
}

void loop() {
    float a = 0;
    float b = 0;
    float c = 0;
    unsigned short precision = 0;
    float temp = 0;

    printf("Please enter the value of line AB (%.0e to %.0e): ", MIN_LENGTH, MAX_LENGTH);
    do {a = extraScanf();} while (!validLength(a));

    printf("Please enter the value of line AC (%.0e to %.0e): ", MIN_LENGTH, MAX_LENGTH);
    do {b = extraScanf();} while (!validLength(b));

    printf("Please enter the value of line BC (%.0e to %.0e): ", MIN_LENGTH, MAX_LENGTH);
    do {c = extraScanf();} while (!validLength(c));

    if(!validTriangle(a, b, c)) {
        printf("The sides do not form a valid triangle. Please reenter the numbers correctly\n");
        return;
    }

    printf("Please enter the amount of digits after the comma in the output (max %d): ", MAX_DIGITS_OUT);
    do {temp = extraScanf();} while(!validPrecision(temp));
    precision = (unsigned short)temp;

    printf("\nPerimeter of ABC: %.*e\n", precision, perimeter(a, b, c));
    printf("Area of ABC: %.*le\n\n", precision, area(a, b, c));
    
    printf("Height AH_1 of ABC: %.*e\n", precision, height(a, b, c));
    printf("Height BH_2 of ABC: %.*e\n", precision, height(b, a, c));
    printf("Height CH_3 of ABC: %.*e\n\n", precision, height(c, a, b));

    printf("Median AM_1 of ABC: %.*e\n", precision, median(a, b, c));
    printf("Median BM_2 of ABC: %.*e\n", precision, median(b, a, c));
    printf("Median CM_3 of ABC: %.*e\n\n", precision, median(c, a, b));

    printf("Bisector AL_1 of ABC: %.*e\n", precision, bisector(a, b, c));
    printf("Bisector BL_2 of ABC: %.*e\n", precision, bisector(b, a, c));
    printf("Bisector CL_3 of ABC: %.*e\n\n", precision, bisector(c, a, b));
}

bool validLength(float length) {
    if (!((length - MAX_LENGTH) < COMPARISON_EPSILON && (MIN_LENGTH - length) < COMPARISON_EPSILON)) {
        printf("Invalid input. Try again: ");
        return false;
    }
    return true;
}

bool validPrecision(float precision) {
    if (!(precision <= MAX_DIGITS_OUT && 0 < precision)) {
        printf("Invalid input. Try again: ");
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

float extraScanf() {
    short success = 0;
    float result = 0;
    success = scanf("%f", &result);
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

bool validTriangle(float a, float b, float c) {
    return (a + b - c > COMPARISON_EPSILON) && (a + c - b > COMPARISON_EPSILON) && (b + c - a > COMPARISON_EPSILON);
}

float perimeter(float a, float b, float c) {
    return a + b + c;
}

double area(float a, float b, float c) {
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

float height(float oppositeLength, float secondaryLength1, float secondaryLength2) {
    return area(oppositeLength, secondaryLength1, secondaryLength2) * 2.0 / oppositeLength;
}

float median(float oppositeLength, float secondaryLength1, float secondaryLength2) {
    return 0.5 * sqrt(2 * pow(secondaryLength1, 2.0) + 2 * pow(secondaryLength2, 2.0) - pow(oppositeLength, 2.0));
}

float bisector(float oppositeLength, float secondaryLength1, float secondaryLength2) {
    float p = (oppositeLength + secondaryLength1 + secondaryLength2) / 2.0;
    return sqrt(secondaryLength1 * secondaryLength2 * p * (p - oppositeLength)) / (secondaryLength1 + secondaryLength2) * 2.0;
}

