#ifndef PR3
#define PR3

#define MAX_X 1e100
#define MIN_E 1e-16
#define MAX_K 1e6


extern void interaction_cycle(void);
extern inline bool valid_e(double e);
extern inline bool valid_k(double k);
extern inline bool valid_x(double x, double e, short k);
extern double root(double x, int k, double e);

static double extra_scanf(void);
static bool end_input(void);
static inline void flush_stdin(void);
static inline double root_(double x, int k, double e, int *iters);

#endif