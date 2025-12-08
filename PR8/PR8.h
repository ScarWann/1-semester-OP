#ifndef PR8
#define PR8

#ifndef _WIN32
#define EOT 4
#else
#define EOT 26
#endif
/* 
 * Although EOF is -1, and most input funcs return it on ^D on POSIX systems, 4 (EOT) is the actual control char index of it (^D)
 * Windows, however, always returns 27 on ^Z if using getch()/getchar(), instead of EOF (-1). ^D does nothing most of the time
 * The return value of scanf() in this case is always -1 on both platforms
 */

typedef struct complex {
    double re;
    double im;
};

typedef enum circuit {
    RL_C,
    RC_L,
    R2C_R1L,
    R2_R1CL
};

#define DOUBLE_RES 2


#define omega ps[0]
#define L     ps[1]
#define C     ps[2]
#define R     ps[3]
#define R1    ps[3]
#define R2    ps[4]

static const void* circuit_funcs[4] = {
    circuit1,
    circuit2,
    circuit3,
    circuit4
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