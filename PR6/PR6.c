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
double** SoLAEInput();
double* solveSoLAE(double** SoLAE);
void outputSolutions(double* solutions);
void flushStdin();
bool userExit();
void* EOFexit();
wchar_t subscriptNumber(int ch);

int main() {
    printf("\nProgram for computing the solution of SoLAEs (systems of linear algebraic eqations)\n"
           "You can exit by pressing Ctrl+D at any time\n\n"
           "               Input form:\n"
           "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
           "┃ A₁₀ + A₁₁x₁ + A₁₂x₂ + ... + A₁ᵢxᵢ = 0 ┃\n"
           "┃ A₂₀ + A₂₁x₁ + A₂₂x₂ + ... + A₂ᵢxᵢ = 0 ┃\n"
           "┃            .                  .     . ┃\n"
           "┃            .                  .     . ┃\n"
           "┃            .                  .     . ┃\n"
           "┃ Aⱼ₀ + Aⱼ₁x₁ + Aⱼ₂x₂ + ... + Aⱼᵢxᵢ = 0 ┃\n"
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

double** SoLAEInput() {
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

double* solveSoLAE(double** SoLAE) {
    double* temp = (double)malloc(sizeof(SoLAE) / );
    return temp;
}

void outputSolutions(double* solution) {
    for (short i = 0; i < sizeof(*solution) / sizeof(double); i++) wprintf("X_%ls: %lf", subscriptNumber(i), solution[i]);
}

void flushStdin() {
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

wchar_t subscriptNumber(int ch) {
    return ch + 0x2080;
}

void* EOFexit() {
    printf("End of input detected. Closing program gracefully.\n");
    return NULL;
}

bool userExit() {
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