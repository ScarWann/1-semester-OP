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
#include "PR8.h"

int main(void) {
    printf("Program for computing the roots of multivariable functions\n"
            "You can exit by pressing "
        #ifndef _WIN32
            "Ctrl+D"
        #else 
            "Ctrl+Z"
        #endif
            " at any time\n"
        );


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

// CIRCUITS
// Params are as follows: omega, L, C, R(1), (R2)

static struct complex* circuit1(double *ps) {
    struct complex* n;
    struct complex* d;
    n->re = L / C;
    n->im = -R / omega / C;
    d->re = R;
    d->im = omega*L - 1 / omega / C;
    return cdiv(n, d);
}

static struct complex* circuit2(double *ps) {
    struct complex* n;
    struct complex* d;
    n->re = L / C;
    n->im = R / omega / C;
    d->re = R;
    d->im = omega * L - 1 / omega / C;
    return cdiv(n, d);
}

static struct complex* circuit3(double *ps) {
    struct complex* n;
    struct complex* d;
    n->re = R1 * R2;
    n->im = R1 * (omega * L - 1 / omega / L);
    d->re = R1 + R2;
    d->im = omega * L - 1 / omega / C;
    return cdiv(n, d);
}

static struct complex* circuit4(double *ps) {
    struct complex* n;
    struct complex* d;
    n->re = R1 * R2 + L / C;
    n->im = R1 * (omega * L * R1 - R2 / omega / L);
    d->re = R1 + R2;
    d->im = omega * L - 1 / omega / C;
    return cdiv(n, d);
}

// MATH

static struct complex* cdiv(struct complex *n, struct complex *d) {
    struct complex* res;
    res->re = (n->re * d->re + n->im * d->im) / (n->im * n->im + d->im * d->im);
    res->im = (d->re * n->im + n->re * d->im) / (n->im * n->im + d->im * d->im);
    return res;
}

// I/O

static void* mul_choice(void* *choices, char *keys, char* *str_choices) {
    print_choices(keys, str_choices);
    do {
        int res = find(keys, getch());
        if (res == -1) {
            printf("%s", ERR_POLL);
        } else if (keys[res] == EOT) {
            printf("%s", EXIT_EOT_MSG);
            return NULL;
        } else {
            printf("'%c' pressed. Option number %d chosen", keys[res], res + 1);
            return choices[res];
        }
    } while (true); 
}

static void print_choices(char *keys, char* *str_choices) {
    printf("Press the specified key to select option");
    for (int i = 0; keys[i] != EOT; i++) {
        printf("%4c\n", keys[i]);
        printf("%s", str_choices[i]);
    }
}

static void mul_poll(double *dest, char* *var_names, unsigned len) {
    for (int i = 0; i < len; i++) {
        printf("Please enter the %s: ", var_names[i]);
        dest[i] = lfconditional_input(valid_param, var_names[i]);
    }
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

static bool valid_param(double val) {
    return isfinite(val) && val <= MAX_PARAM && val >= MIN_PARAM;
}

// MISC

static int find(char *ptr, char val) {
    int i = 0;
    do {
        if (ptr[i] == val) return i;
    } while (ptr[++i] != EOT);
    return (i == EOT) ? i : -1;
}

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