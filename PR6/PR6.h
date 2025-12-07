#ifndef PR6
#define PR6

#define MAX_RAND_MAT_SIZE 20
#define MAX_MAN_MAT_SIZE 10
#define MIN_MAT_SIZE 2

#define MAX_RAND_COEF 1e10
#define MAX_MAN_COEF 1e15
#define MIN_RAND_COEF -1e10
#define MIN_MAN_COEF -1e15

#define MAX_PRECISION 14
#define MIN_PRECISION 1

#define MAX_ITERS 100000


#define EOT 4
/* 
 * Although EOF is -1, and most input funcs return it on ^D on POSIX systems, 4 (EOT) is the actual control char index of it (^D)
 * Windows, however, always returns EOT (4) on ^D if using getch()/getchar(), instead of EOF (-1)
 * The return value of scanf() in this case is always -1 on both platforms
 */

enum EXIT_STATUS {
    OK,
    ERR_MALLOC,
    EXIT_EOT
};

void SoLAE_input(double **ptr, unsigned short mat_size, enum EXIT_STATUS *exit_code, bool random);
double *solve_SoLAE(double **SoLAE, double epsilon, unsigned size);
bool valid_SoLAE(double **SoLAE, unsigned size);

static double max_delta(double *ptr1, double *ptr2, unsigned short size);
static void replace_arr_vals(double *src, double *dest, unsigned size);
static double sum_arr_muls(double *ptr1, double *ptr2, unsigned size);
static double abs_sum(double *row, unsigned short size);

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
static inline double lfrandom(double floor, double ceil);

static const char *ERR_MALLOC_MSG = "Memory allocation failed. Try another matrix size or end program\n";
static const char *EXIT_EOT_MSG = "End of input detected. Exiting program gracefully.\n";
static const char *TMPLT_INVALID_VAL_MSG = "Please try inputting the %s as specified: ";

#endif