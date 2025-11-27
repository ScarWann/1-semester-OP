#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
    #include <unistd.h>
    #include <termios.h>
#endif



#define MAX_MAT_SIZE 10
#define MIN_MAT_SIZE 2

#define MAX_PRECISION 14
#define MIN_PRECISION 1

#define MAX_ITERS 100000

#

#define EOT 4
/* 
 * Although EOF is -1, and most input funcs return it on ^D on POSIX systems, 4 (EOT) is the actual control char index of it (^D)
 * Windows, however, always returns EOT (4) on ^D, instead of EOF (-1)
 * The return value of scanf() is always -1 on both platforms
 */

enum EXIT_STATUS {
    OK,
    MALLOC_ERR,
    EOF_EXIT
};

void SoLAE_input(double **ptr, unsigned short mat_size, enum EXIT_STATUS *exit_code);
double *solve_SoLAE(double **SoLAE, double epsilon, unsigned size);
bool valid_SoLAE(double **SoLAE, unsigned size);

static double max_delta(double *ptr1, double *ptr2, unsigned short size);
static void replace_arr_vals(double *src, double *dest, unsigned size);
static double sum_arr_muls(double *ptr1, double *ptr2, unsigned size);
static double abs_sum(double *row, unsigned short size);

static bool bool_input();
static void huconditional_input(unsigned short *out, bool (condition(unsigned short val)), char *errmsg);
static void lfconditional_input(double *out, bool (condition(double val)), char *errmsg);
static void coef_input_msg(unsigned int i, unsigned int j);
static void print_subscript(unsigned int n);
static void output_solutions(double* solution, unsigned short precision, unsigned short size);

static bool valid_size(unsigned short size);
static bool valid_coef(double coef);
static bool valid_precision(unsigned short precision);


#ifndef _WIN32
static int getch(void);
#endif

static bool user_exit(void);
static void inline flush_stdin(void);
static void inline delete_ptr(void *ptr);



int main(void) {
    printf("\nProgram for computing the solution of SoLAEs (systems of linear algebraic eqations)\n"
           "You can exit by pressing Ctrl+D at any time\n\n"
           "               Input form:\n"
           "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
           "┃ A₁₀ + A₁₁x₁ + A₁₂x₂ + ... + A₁ₙxₙ = 0 ┃\n"
           "┃ A₂₀ + A₂₁x₁ + A₂₂x₂ + ... + A₂ₙxₙ = 0 ┃\n"
           "┃            .                  .     . ┃\n"
           "┃            .                  .     . ┃\n"
           "┃            .                  .     . ┃\n"
           "┃ Aₙ₀ + Aₙ₁x₁ + Aₙ₂x₂ + ... + Aₙₙxₙ = 0 ┃\n"
           "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n"
        
        );

    do {
        unsigned short mat_size;
        printf("Enter matrix size in range %u to %u: ", MIN_MAT_SIZE, MAX_MAT_SIZE);
        huconditional_input(&mat_size, &valid_size,
                            "Please enter the size as an integer in the specified range: ");
        if (mat_size == 0) return EXIT_SUCCESS;
        

        double** SoLAE = (double**)malloc(mat_size * sizeof(double*));
        if (SoLAE == NULL) {
            printf("Memory allocation error. Try another matrix size\n");
            continue;
        }
        enum EXIT_STATUS exit_code = OK;
        SoLAE_input(SoLAE, mat_size, &exit_code);
        if (exit_code != OK) delete_ptr(SoLAE);
        switch (exit_code)
        {
        case MALLOC_ERR:
            printf("Memory allocation error. Try again");
            continue;
        case EOF_EXIT:
            printf("End of input detected. Exiting program gracefully.\n");
            return EXIT_SUCCESS;
        }

        if (!valid_SoLAE(SoLAE, mat_size)) {
            printf("Gauss-Seidel method not applicable for this SoLAE\n");
            delete_ptr(SoLAE);
            continue;
        }

        short unsigned precision;
        printf("Enter the precision (amount of digits, as an integer) in range %d to %d: ", MIN_PRECISION, MAX_PRECISION);
        huconditional_input(&precision, &valid_precision, 
                            "Please enter the precision as an integer in the specified range: ");
        if (precision == 0) return EXIT_SUCCESS;

        double* solutions = solve_SoLAE(SoLAE, pow(0.1, precision), mat_size);
        if (solutions != NULL) output_solutions(solutions, precision, mat_size);
        delete_ptr(SoLAE);

    } while (!user_exit());
    return EXIT_SUCCESS;
}

// EXTERNS

void SoLAE_input(double **ptr, unsigned short mat_size, enum EXIT_STATUS *exit_code) {
    printf("Enter the value of the SoLAE coeficients\n");
    for (unsigned short i = 0; i < mat_size; i++) {
        short success;
        ptr[i] = (double*)malloc((mat_size + 1)  * sizeof(double));
        if (ptr[i] == NULL) {
            *exit_code = MALLOC_ERR;
            return;
        }
        for (unsigned short j = 0; j < mat_size + 1; j++) {
            coef_input_msg(i + 1, j);
            lfconditional_input(&ptr[i][j], &valid_coef,
                                "Please enter the coeficient in the valid range: ");
        }
    }
    return;
}

double *solve_SoLAE(double **SoLAE, double epsilon, unsigned size) {
    double *bs = (double*)malloc(sizeof(double) * size);
    if (bs == NULL) return NULL;
    for (int i = 0; i < size; i++) {
        bs[i] = -SoLAE[i][0];
    }
    
    double *xs = (double*)malloc(sizeof(double) * size);
    if (xs == NULL) {
        delete_ptr(bs);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        xs[i] = bs[i] / SoLAE[i][i+1];
    }

    double *xps = (double*)malloc(sizeof(double) * size);
    if (xps == NULL) {
        delete_ptr(bs);
        delete_ptr(xs);
        return NULL;
    }


    unsigned iters = 0; 
    do {
        replace_arr_vals(xs, xps, size);
        for (int i = 0; i < size; i++) {
            xs[i] = (bs[i] + SoLAE[i][i+1] * xs[i] 
                    - sum_arr_muls(SoLAE[i], xs, size))
                    / SoLAE[i][i+1];
        }
        iters++;
    } while (max_delta(xs, xps, size) > epsilon && iters < MAX_ITERS);
    return xs;
}

bool valid_SoLAE(double **SoLAE, unsigned size) {
    for (int i = 0; i < size; i++) {
        if (SoLAE[i][i+1] == 0) return false;
        if (abs_sum(SoLAE[i], size) > SoLAE[i][i+1] * 2) return false;
    }

    return true;
}

// MATH

static inline double max_delta(double *ptr1, double *ptr2, unsigned short size) {
    double res = 0;
    for (int i = 0; i < size; i++) {
        res = (res < abs(ptr1[i] - ptr2[i])) ? abs(ptr1[i] - ptr2[i]) : res;
    }
    return res;
}

static inline void replace_arr_vals(double *src, double *dest, unsigned size) {
    for (int i = 0; i < size; i++) dest[i] = src[i];
}

static inline double sum_arr_muls(double *ptr1, double *ptr2, unsigned size) {
    double sum = 0;
    for (int i = 0; i < size; i++) sum += ptr1[i+1] * ptr2[i];
    return sum;
}

static inline double abs_sum(double *row, unsigned short size) {
    double result = 0;
    for (int i = 0; i < size; i++) {
        result += abs(row[i]);
    }
    return result;
}

// I/O

static bool bool_input() {
    return getch() != '0';
}

static void huconditional_input(unsigned short *out, bool (condition(unsigned short val)), char *errmsg) {
    short success;
    do {
        success = scanf("%hu", out);
        flush_stdin();
        if (success == EOF) {
            printf("End of input detected. Exiting program gracefully.\n");
            *out = 0;
            return;
        }  else if (!(success && condition(*out))) {
            printf("%s", errmsg);
        }
    } while (!(success && condition(*out)));
}

static void lfconditional_input(double *out, bool (condition(double val)), char *errmsg) {
    short success;
    do {
        success = scanf("%lf", out);
        flush_stdin();
        if (success == EOF) {
            printf("End of input detected. Exiting program gracefully.\n");
            *out = NAN;
            return;
        }  else if (!(success && condition(*out))) {
            printf("%s", errmsg);
        }
    } while (!(success && condition(*out)));
}

static void coef_input_msg(unsigned int i, unsigned int j) {
    printf("Enter coeficient A");
    print_subscript(i);
    print_subscript(j);
    printf(": ");
}

static void print_subscript(unsigned int n) {
    const char *subscripts[] = {
        "₀", "₁", "₂", "₃", "₄", 
        "₅", "₆", "₇", "₈", "₉"
    };

    if (n == 0) {
        printf("₀");
        return;
    }
    
    char buffer[20];
    int i = 0;
    while (n > 0) {
        buffer[i++] = n % 10;
        n /= 10;
    }
    
    while (i > 0) {
        printf("%s", subscripts[buffer[--i]]);
    }
}

static void output_solutions(double* solution, unsigned short precision, unsigned short size) {
    for (short i = 0; i < size; i++) {
        printf("X");
        print_subscript(i);
        printf(": %.*lf\n", precision, solution[i]);
    }
}

static bool user_exit(void) {
    char ch;
    printf("Press Ctrl+D to end program. Enter any key to continue\n");
    ch = getch();
    flush_stdin();
    if (ch == EOT) { 
        printf("End of input detected. Closing program.\n");
        return true;
    }
    return false;
}

// VALIDATIONS

static bool valid_size(unsigned short size) {
    return size != 0 && size <= MAX_MAT_SIZE && size >= MIN_MAT_SIZE;
}

static bool valid_coef(double coef) {
    return isfinite(coef);
}

static bool valid_precision(unsigned short precision) {
    return precision <= MAX_PRECISION && precision >= MIN_PRECISION;
}

// MISC



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

static inline void delete_ptr(void *ptr) {
    free(ptr);
    ptr = NULL;
}

static inline double random(double floor, double ceil) {
    srand(time(NULL));
    return rand();
}