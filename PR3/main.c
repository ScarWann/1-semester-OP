#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
#endif
#include "main.h"



int main() {
    printf("Program for calculating square roots up to a certain precision.\n"
           "You can exit at any time by pressing Ctrl+D\n");
    do {
        interaction_cycle();
    } while (!end_input());
    return EXIT_SUCCESS;
}

void interaction_cycle() {
    bool success; 

    double e = 0;
    printf("Enter epsilon (must be a positive number in range [%.0le, 0.1], prefferably in exponential form (i.e. 1e-6)): ", MIN_E);
    do {
        e = extra_scanf();
        success = valid_e(e);
        if (!success) printf("Please enter a number in the specified range: ");
    } while (!success);
    unsigned short precision = -log10(e);
    
    double temp = 0;
    int k = 0;
    printf("Enter k (must be an integer less than or equal to %.0e): ", MAX_K);
    do {
        temp = extra_scanf();
        success = valid_k(temp);
        if (!success) printf("Please enter an integer in the specified range: ");
    } while (!success);
    k = (int)temp;

    double x = 0;
    printf("Enter x (must have a square root of power %d and be in range [%.0e, %.0e]): ", k, e, MAX_X);
    do {
        x = extra_scanf();
        success = valid_x(x, e, k);
        if (!success) printf("Please enter a number that has the specified root in the valid range: ");
    } while (!success);

    if (x && x != 1) {
        printf("The final root value is %.*lf\n", precision, root(x, k, e, precision));
    } else {
        printf("The final root value is %.*lf\n", precision, x);
    }
}

extern inline bool valid_e(double e) {
    return (0.1 >= e && e >= MIN_E);
}

extern inline bool valid_x(double x, double e, short k) {
    if (isnan(x) || fabs(x) > MAX_X || fabs(x) < e) return false;
    if (k % 2 == 0 && x <= 0) return false;
    if (k < 0 && x == 0) return false;
    return true;
}

extern inline bool valid_k(double k) {
    return ((int)k == k && fabs(k) <= MAX_K && (int)k != 0);
}


static double extra_scanf() {
    short success = 0;
    double result = 0;
    success = scanf("%lf", &result);
    if (success == EOF) {
        printf("End of input detected. Closing program.\n");
        exit(EXIT_SUCCESS);
    } else if (!success){
        result = NAN;
    }
    flush_stdin();
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
    flush_stdin();
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

double root(double x, int k, double e, unsigned short precision) {
    double out;
    unsigned int iters;
    if (k > 0) {
        iters = root_(x, k, e, precision, &out);
    } else {
        iters = root_(1./x, -k, e, precision, &out);
    }
    printf("Calculation finished in %d iterations\n", iters);
    return out;
}

static inline double root_(double x, int k, double e, unsigned short precision, double *out) {
    double y = 1, d = 1;
    unsigned int i = 0;
    while (fabs(d) > e) {
        d = (x / pow(y, k - 1) - y) / k;
        y += d;
        i++;
    }
    *out = y;
    return i;
}
