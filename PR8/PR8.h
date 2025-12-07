#ifndef PR8
#define PR8



#ifndef _WIN32
#define EOT 4
#else
#define EOT 27
#endif
/* 
 * Although EOF is -1, and most input funcs return it on ^D on POSIX systems, 4 (EOT) is the actual control char index of it (^D)
 * Windows, however, always returns EOT (4) on ^Z if using getch()/getchar(), instead of EOF (-1). ^D does nothing most of the time
 * The return value of scanf() in this case is always -1 on both platforms
 */

typedef struct complex {
    double re;
    double im;
};

static double func1(double x, double y);
static double func2(double x, double y);
double solve_div(double func(double x, double y), double y, double a, double b, double e);
double solve_newt(double func(double x, double y), double y, double a, double b, double e);
static double derivative(double func(double x, double y), double x, double y);

static void* bool_choice(void *choice1, void *choice2, char* str_choice1, char* str_choice2);
static double lfconditional_input(bool (condition(double val)), char *val_name);
static bool user_exit(void);

static bool valid_boundary(double boundary);
static bool valid_y(double y);
static bool valid_epsilon(double epsilon);

#ifndef _WIN32
static int getch(void);
#endif

static inline void order_ascending(double *a, double *b);
static void inline flush_stdin(void);

static const char *EXIT_EOT_MSG = "End of input detected. Exiting program gracefully.\n";
static const char *INVALID_VAL_MSG = "Please try inputting the %s as specified: ";
static const char *CALC_SUCC = "The calculated root is: %lf\n";
static const char *CALC_FAIL_RANG = "The root \"escaped\" out of the specified range\n";
static const char *CALC_FAIL_NAN = "The method converged on a value that is not in the definition of the function\n";
static const char *CALC_FAIL_ITER = "The method exceeded the allowed iteration amount\n";
static const char *CALC_FAIL_EPS = "The method attempted to calculate an extremely imprecise derivative\n";

#endif