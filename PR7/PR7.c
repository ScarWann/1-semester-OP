#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
    #include <unistd.h>
    #include <termios.h>
#endif
#include "PR7.h"

int main(void) {
    printf("Program for computing the roots of multivariable functions\n"
           "You can exit by pressing Ctrl+D at any time\n");


    do {
        printf("Please enter the two boundaries between which the roots will be found (a and b, in no particular order)\n"
               "Boundary 1: ");
        double a = lfconditional_input(&valid_boundary, "boundary");
        if (isnan(a)) break;

        printf("Boundary 2: ");
        double b = lfconditional_input(&valid_boundary, "boundary");
        if (isnan(b)) break;

        if (a == b) {
            printf("Please reenter two different values or exit the program.\n");
            continue;
        }

        order_ascending(&a, &b);

        printf("Please enter the value of y: ");
        double y = lfconditional_input(&valid_y, "y");
        if (isnan(y)) break;

        double (*math_func) (double x, double y);
        math_func = bool_choice(&func1, &func2,
                                "cos(y/x) - 2sin(1/x) + 1/x",
                                "sin(ln(x)) - cos(ln(x)) + y * ln(x)");
        
        if (math_func == NULL) break;

        void (*calc_func) (double func(double x, double y), double y, double a, double b, double e);
        calc_func = bool_choice(&solve_div, &solve_newt,
                                "Half division method",
                                "Newton's method");

        printf("Enter the epsilon as an integer in range %.0e to %.0e: ", 
               MIN_EPSILON, MAX_EPSILON);
        double e = lfconditional_input(&valid_epsilon, "epsilon");
        if (isnan(e)) break;

        calc_func(math_func, y, a, b, e);

    } while (!user_exit());

    return EXIT_SUCCESS;
}

// MATH

static double func1(double x, double y) {
    return cos(y/x) - 2. * sin(1./x) + 1./x;
}

static double func2(double x, double y) {
    return sin(log(x)) - cos(log(x)) + y * log(x);
}

void solve_div(double func(double x, double y), double y, double a, double b, double e) {
    double sol;
    double ta = a, tb = b;
    do {
        sol = (ta + tb) / 2.;
        if (func(ta, y) * func(sol, y) > 0) {
            ta = sol;
        } else {
            tb = sol;
        }
    } while ((fabs(ta - tb) > e) && !isnan(sol));

    if (isnan(sol)) {
        printf("%s", CALC_FAIL_NAN);
    }else if (sol - e > a || sol + e < b) {
        printf("%s", CALC_FAIL_RANG);
    } else {
        printf(CALC_SUCC, sol);
    }
}

void solve_newt(double func(double x, double y), double y, double a, double b, double e) {
    double sol = b;
    double delta;
    unsigned i = 0;
    double dfval = derivative(func, sol, y);

    do {
        if (fabs(dfval) < M_EPS) break;
        
        delta = func(sol, y) / dfval;
        sol -= delta;
        
        //if (sol < a || sol > b) return NAN;
        i++; 
    } while (fabs(delta) > e && i < MAX_ITERS && !isnan(sol));
    
    if (fabs(dfval) < M_EPS) {
        printf("%s", CALC_FAIL_EPS);
    } else if (isnan(sol)) {
        printf("%s", CALC_FAIL_NAN);
    } else if (sol - e > a && sol + e < b) {
        printf("%s", CALC_FAIL_RANG);
    } else if (i > MAX_ITERS) {
        printf("%s", CALC_FAIL_ITER);
    } else {
        printf(CALC_SUCC, sol);
    }
}

static double derivative(double func(double x, double y), double x, double y) {
    return (func(x + M_EPS, y) - func(x - M_EPS, y)) / (2 * M_EPS);
}

// I/O

static void* bool_choice(void *choice1, void *choice2, char* str_choice1, char* str_choice2) {
    printf("Press the specified number to choose either option:\n"
           "    1: %s\n"
           "    2: %s\n",
           str_choice1, str_choice2);
    bool finished = false;
    do {
        finished = true;
        switch (getch()) {
            case '1':
                printf("Option 1, '%s', chosen\n", str_choice1);
                return choice1;
            case '2':
                printf("Option 2, '%s', chosen\n", str_choice2);
                return choice2;
            case EOT:
                printf("%s\n", EXIT_EOT_MSG);
                return NULL;
            default:
                printf("Unknown button pressed. Try again\n");
                finished = false;
        }
    } while (!finished);
}

static double lfconditional_input(bool (condition(double val)), char *val_name) {
    short success;
    double val;
    do {
        success = scanf("%lf", &val);
        flush_stdin();
        if (success == EOF) {
            printf("%s", EXIT_EOT_MSG);
            return NAN;
        }  else if (!(success && condition(val))) {
            printf(INVALID_VAL_MSG, val_name);
        }
    } while (!(success && condition(val)));
    return val;
}

static bool user_exit(void) {
    char ch;
    printf("Press Ctrl+D to end program. Enter any key to continue\n");
    ch = getch();
    flush_stdin();
    if (ch == EOT) { 
        printf("%s", EXIT_EOT_MSG);
        return true;
    }
    return false;
}

// VALIDATIONS

static bool valid_boundary(double boundary) {
    return fabs(boundary) <= SAMPLE_RANGE && isfinite(boundary);
}

static bool valid_y(double y) {
    return fabs(y) <= MAX_Y && fabs(y) >= MIN_Y && isfinite(y);
}

static bool valid_epsilon(double epsilon) {
    return epsilon <= MAX_EPSILON && epsilon >= MIN_EPSILON && isfinite(epsilon);
}

// MISC

static inline void order_ascending(double *a, double *b) {
    if (*a > *b) {
        double tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

#ifndef _WIN32
static int getch(void) {
    struct termios old, new;
    int ch;
    
    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return ch;
}
#endif

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