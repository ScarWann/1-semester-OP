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
#define MIN_E 1e-16
#define MAX_K 1e6


void interaction_cycle(void);
inline bool valid_e(double e);
inline bool valid_k(double k);
inline bool valid_x(double x, double e, short k);
double root(double x, int k, double e, unsigned short precision);

static double extra_scanf(void);
static bool end_input(void);
static inline void flush_stdin(void);
static double root_(double x, int k, double e, unsigned short precision);

int main() {
    printf("Program for calculating square roots up to a certain precision.\n"
           "You can exit at any time by pressing Ctrl+D\n");
    do {
        loop();
    } while (!end_input());
    return 0;
}

void loop() {
    bool success = true; 
    double e = 0;
    printf("Enter epsilon (must be a positive number in range [%.0le, 0.1], prefferably in exponential form (i.e. 1e-6)): ", MIN_E);
    do {
        e = extraScanf();
        success = valid_e(e);
        if (!success) printf("Please enter a number in the specified range: ");
    } while (!success);
    unsigned short precision = -log10(e);
    
    double temp = 0;
    int k = 0;
    printf("Enter k (must be an integer less than or equal to %.0e): ", MAX_K);
    do {
        temp = extraScanf();
    } while (!validK(temp));
    k = (int)temp;

    double x = 0;
    printf("Enter x (must have a square root of power %d and be in range [%.0e, %.0e]): ", k, e, MAX_X);
    do {
        x = extraScanf();
        printf("Please enter a number that has the specified root in the valid range: ");
    } while (!validX(x, e, k));

    if (x && x != 1) {
        printf("The final root value is %.*lf\n", precision, root(x, k, e, precision));
    } else {
        printf("The final root value is %.*lf\n", precision, x);
    }
}

inline bool valid_e(double e) {
    return (0.1 >= e && e >= MIN_E);
}


inline bool valid_x(double x, double e, short k) {
    if (isnan(x) || fabs(x) > MAX_X || fabs(x) < e) return false;
    if (k % 2 == 0 && x <= 0) return false;
    if (k < 0 && x == 0) return false;
    return true;
}

bool valid_x(double x, double e, short k) {
    if (!(fabs(x) <= MAX_X && fabs(x) >= e)) {
        return false;
    } else if (k > 0 && (k % 2 == 0) && (x < 0)) {
        return false;
    } else if (k > 0) {
        return true;
    } else if ((k % 2 == 0) && (x <= 0)) {
        return false;
    } else if (x == 0) {
        return false;
    }
    return true;
}


double extra_scanf() {
    short success = 0;
    double result = 0;
    success = scanf("%lf", &result);
    if (success == EOF) {
        printf("End of input detected. Closing program.\n");
        exit(EXIT_SUCCESS);
    } else if (!success){
        result = NAN;
    }
    flushStdin();
    return result;
}

static bool end_input() {
    char ch;
    printf("Press Ctrl+D to end program. Enter any key to continue: ");
    ch = getchar();
    if (ch == EOF) {
        printf("End of input detected. Closing program.\n");
        return 1;
    }
    flushStdin();
    return 0;
}

static void inline flush_stdin(void) {
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

static double root_(double x, int k, double e, unsigned short precision) {
    double y = 1, d = 1;
    unsigned int i = 0;
    while (fabs(d) > e) {
        d = (x / pow(y, k - 1) - y) / k;
        y += d;
        i++;
        if (i < 1e3) {
            printf("Iteration %d: y = %.*le, delta = %.*le\n", i, precision, y, precision, d);
        } else if (i == 1e3) {
            printf("Exceeded 1000 iterations, detailed output turned off.\n");
        }
    }
    printf("Calculated root in %u iterations\n", i);
    return y;
}
