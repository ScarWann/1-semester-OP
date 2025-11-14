#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
#endif


#define MAX_MAT_SIZE 100

void loop();
bool validArrLen(unsigned short var, short success);
bool validStrLen(unsigned short var, short success);
bool validStr(char* str);
void cleanStr(char** str);
void mallocError();
void exitWithMsg();
void printIndexedStrs(char** arr, unsigned short arrLen);
bool strsAscendAlph(char* str1, char* str2);
void sortStrsArr(char** arr, unsigned short arrLen);
bool endInput();
void flushStdin();

struct SoLAE {
    float** SoLAE;
    short inputStatus;
};

int main() {
    printf("Program for computing the solution of SoLAEs (systems of linear algebraic eqations)\n"
           "You can exit by pressing Ctrl+D at any time\n");

    bool userExit = false;

    do {
        float** SoLAE = SoLAEInput();
        float* solutions = SolveSoLAE(SoLAE);
        outputSolutions(solutions);

    } while (!userExit);
    return EXIT_SUCCESS;
}

void loop() {
    short success = 0;
    short unsigned matrixSize = 0;
    printf("Enter the size of the matrix (must be an integer less than or equal to %d): ", MAX_MAT_SIZE);
    do {
        success = scanf("%hu", &matrixSize);
        flushStdin();
    } while (!(validArrLen(matrixSize, success)));

    float** matrix = (float**)malloc(pow(matrixSize, 2) * sizeof(float*));
    if (matrix == NULL) mallocError();

    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = (float*)malloc(matrixSize  * sizeof(float));
        for (int j = 0; j < matrixSize; i++) {
            printf("Enter number with inexi %d, %d (vertical, horizontal coords): ", i + 1, j + 1);
            do {
                scanf("%d", &arr[i])
            } while (!validStr(arr[i]));
        }
    }
    
    sortStrsArr(arr, arrLen);

    printIndexedStrs(arr, arrLen);
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


bool validArrLen(unsigned short var, short success) {
    if (success == EOF) {
        exitWithMsg();
    } else if (!(var && success && var < MAX_MAT_SIZE)) {
        printf("Please enter a valid value: ");
        return false;
    }
    return true;
}

void mallocError() {
    print("Memory allocation error. Aborting program.\n");
    exit(EXIT_FAILURE);
}

void exitWithMsg() {
    printf("End of input detected. Closing program.\n");
    exit(EXIT_SUCCESS);
}

bool endInput() {
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