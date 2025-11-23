#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
#endif
#include "io.h"



int main() {
    return 0;
}

enum IO_MODE {
    TITLE,
    SIZE_INPUT,
    PARAMETER_INPUT,
    EPSILON_INPUT,
    OUTPUT
};

struct windowsize {
    int ws_row;
    int ws_col;
} windowSize;

enum IO_MODE Mode = TITLE;


void outputCurrentState() {
    switch (Mode) {
        case (TITLE):
            signal(SIGWINCH, outputTitle);
            outputTitle();
        case (SIZE_INPUT):
            
    }
}

void outputTitle() {
    signal(SIGWINCH, SIG_IGN);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize);
	clear();
    printf(

        "\nProgram for computing the solution of SoLAEs (systems of linear algebraic eqations)\n"
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
    signal(SIGWINCH, outputTitle);
    getchar();
}

void printCentered(const char* content, int offset) {
    const unsigned short lines = countCharsInStr(content, '\n');
    const char** substrs = (const char**)splitStr(content, '\n');
    const unsigned short upPadding = (windowSize.ws_row - lines) / 2;
    const unsigned short leftPadding = windowSize.ws_col / 2;
    for (unsigned i = 0; i < lines; i++) { 
		mvaddstr(upPadding + i, leftPadding - reallen(substrs[i]) / 2, substrs[i]);

    }
}

unsigned reallen(char* str) {
    unsigned len = 0;
    while (*str) len += (*str++ & 0xc0) != 0x80;
    return len;
}

char** splitStr(char* str, char ch) {
    char** strs = (char**)malloc(sizeof(char*) * countCharsInStr(str, ch));
    for (unsigned i = 0; strs[i] = strtok(str, &ch); i++);
    return strs;
}

unsigned countCharsInStr(char* str, char ch) {
    unsigned i = 0;
    for (;str[i]; str[i]== ch ? i++ : *str++);
    return i;
}

double** SoLAEInput() {
    short success = 0;
    short unsigned matrixSize = 0;
    printf("Enter the size of the SoLAE (must be an integer less than or equal to %d): ", MAX_MAN_MAT_SIZE);
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
            printf("Enter coeficient a_%hu_%hu (vertical, horizontal coords): ", 
                    i + 1, j);
            do {
                success = scanf("%lf", &matrix[i][j]);
                flushStdin();
                if(success == EOF) return EOFexit();
                if(!success) {
                    printf("Please enter a valid number: ");
                }
            } while (!success);
        }
    }

    return matrix;
}

void outputSolutions(double* solutions) {
    for (short unsigned i = 0;;) {
        printf("X");
        printSubscript(i);
        printf(" = %lf", solutions[i]);
        if (isnan(solutions[++i])) {
            printf("\n");
            return;
        } else {
            printf(", ");
        }
    }
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

void printSubscript(unsigned int n) {
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