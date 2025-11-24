#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <wchar.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
#endif


#define MAX_MAT_SIZE 100
#define MAX_DIGITS 14

void loop();
double** SoLAE_input();
double* solve_SoLAE(double** SoLAE);
void output_solutions(double* solutions);
void flush_stdin();
bool user_exit();
void* EOF_exit();

int main() {
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
        double** SoLAE = SoLAEInput();
        if (SoLAE == NULL) return EXIT_SUCCESS;
        double* solutions = solveSoLAE(SoLAE);
        outputSolutions(solutions);

    } while (!userExit());
    return EXIT_SUCCESS;
}

double** SoLAE_input() {
    short success = 0;
    short unsigned matrixSize = 0;
    printf("Enter the size of the SoLAE (must be an integer less than or equal to %d): ", MAX_MAT_SIZE);
    do {
        success = scanf("%hu", &matrixSize);
        flushStdin();
        if (success == EOF) return EOFexit();
    } while (!success);


    double** matrix = (double**)malloc(matrixSize * sizeof(double*));
    if (matrix == NULL) {
        printf("Memory allocation error. Aborting program.\n");
        return NULL;
    }

    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = (double*)malloc((matrixSize + 1)  * sizeof(double));
        for (int j = 0; j < matrixSize + 1; j++) {
            printf("Enter coeficient a_%hu_%hu (vertical, horizontal coords): ", i + 1, j);
            do {
                success = scanf("%lf", &matrix[i][j]);
                if(success == EOF) return EOFexit();
                if(!success) {
                    printf("Please enter a valid number: ");
                }
            } while (!success);
        }
    }

    return matrix;
}

double* solve_SoLAE(double** SoLAE, unsigned size) {
    double *bs = (double*)malloc(sizeof(double) * size);
    for (int i = 0; i < size; i++) {
        bs[i] = -SoLAE[i][0];
    }

    double *xps = (double*)malloc(sizeof(double) * size);
    for (int i = 0; i < size; i++) {
        xps[i] = bs[i] / SoLAE[i][i+1];
    }
    double *xs = (double*)malloc(sizeof(double) * size);
    return xs;
}

bool valid_SoLAE(double **SoLAE, unsigned size) {
    for (int i = 0; i < size; i++) {
        if (SoLAE[i][i+1] == 0) return false;
        if (sum(SoLAE[i], size) > SoLAE[i][i+1] * 2) return false;
    }

    return true;
}

static double arrmulsum(double *row, double ) {

}

static double sum(double *row, unsigned short size){
    double result = 0;
    for (int i = 0; i < size; i++) {
        result += row[i];
    }
    return result;
}

void output_solutions(double* solution) {
    for (short i = 0; i < sizeof(*solution) / sizeof(double); i++) wprintf("X_%ls: %lf", subscriptNumber(i), solution[i]);
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

static void print_subscript(unsigned int n) {
    const char *subscripts[] = {
        "₀", "₁", "₂", "₃", "₄", 
        "₅", "₆", "₇", "₈", "₉"
    };
    
    if (n == 0) {
        printf("%s", subscripts[0]);
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

void* EOFexit() {
    printf("End of input detected. Closing program gracefully.\n");
    return NULL;
}

static bool user_exit() {
    char ch;
    printf("Press Ctrl+D to end program. Enter any key to continue: ");
    ch = getchar();
    if (ch == EOF) {
        printf("End of input detected. Closing program.\n");
        return true;
    }
    flushStdin();
    return false;
}