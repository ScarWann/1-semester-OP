#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
#endif
#include "solae.h"
#include "io.h"


int main(int argc, char** argv) {

    do {
        double** SoLAE = SoLAEInput();
        if (SoLAE == NULL) return EXIT_SUCCESS;
        double solutions[5] = {2, 5, 10, 0.5, NAN};//solveSoLAE(SoLAE);
        outputSolutions(solutions);

    } while (!userExit());
    return EXIT_SUCCESS;
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