#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <stdio_ext.h>
#endif


#define MAX_STR_LEN 1000
#define MAX_ARR_LEN 1000

void loop();
bool validArrLen(unsigned short var, short success);
bool validStrLen(unsigned short var, short success);
bool validStr(char* str, unsigned short len, short success);
void cutStr(char** str, unsigned short len);
void exitWithMsg();
void printIndexedStrs(char** arr, unsigned short arrLen, unsigned short strLen);
bool strsAscendAlph(char* str1, char* str2);
void sortStrsArr(char** arr, unsigned short arrLen);
bool endInput();
void flushStdin();

int main() {
    printf("Program for sorting strings in alphabetical order.\n"
           "Entering extra chars will automatically cut them.\n"
           "Entering less chars than specified will treat the empty spaces as char 0 ('\\0')\n"
           "You can press Ctrl+D to end the program at any time.\n");
    do {
        loop();
    } while (!endInput());
    return 0;
}

void loop() {
    short success = 0;
    short unsigned arrLen = 0;
    printf("Enter the amount of compared strings (must be an integer less than or equal to %d): ", MAX_ARR_LEN);
    do {
        success = scanf("%hu", &arrLen);
        flushStdin();
    } while (!(validArrLen(arrLen, success)));

    short unsigned strLen = 0;
    printf("Enter the length of compared strings (must be an integer less than or equal to %d): ", MAX_STR_LEN);
    do {
        success = scanf("%hu", &strLen);
        flushStdin();
    } while (!(validStrLen(strLen, success)));

    char **arr = (char**)malloc(arrLen * (strLen + 1) * 4 * sizeof(char)); // Додаткове місце для \n й 4 байта для включення всіх символів UTF-8
    for (int i = 0; i < arrLen; i++) {
        arr[i] = (char*)malloc((strLen + 1) * 4 * sizeof(char));
        printf("Enter string number %d: ", i + 1);
        do {
            //success = scanf("%s", arr[i]);
            fgets(arr[i], strLen + 1, stdin);
            flushStdin();
            //cutStr(&arr[i], strLen);
        } while (0/*!validStr(arr[i], strLen, success*/);
    }
    
    sortStrsArr(arr, arrLen);

    printIndexedStrs(arr, arrLen, strLen);
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

void cutStr(char** str, unsigned short len) {
    for (int i = len;; i++) {
        if ((*str)[i] != '\0') {
            (*str)[i] = '\0';
        } else return;
    }
}

bool validArrLen(unsigned short var, short success) {
    if (success == EOF) {
        exitWithMsg();
    } else if (!(var && success && var < MAX_ARR_LEN)) {
        printf("Please enter a valid value: ");
        return false;
    }
    return true;
}

bool validStrLen(unsigned short var, short success) {
    if (success == EOF) {
        exitWithMsg();
    } else if (!(var && success && var < MAX_STR_LEN)) {
        printf("Please enter a valid value: ");
        return false;
    }
    return true;
}

bool validStr(char* str, unsigned short len, short success) {
    if (success == EOF) {
        exitWithMsg();
    } else if (!success) {
        printf("Please enter a valid string of length %d: ", len);
        return false;
    }
    return true;
}

void exitWithMsg() {
    printf("End of input detected. Closing program.\n");
    exit(0);
}

bool strsAscendAlph(char* str1, char* str2) {
    if (strcmp(str1, str2) > 0) {
        return false;
    } else {
        return true;
    }
}

void sortStrsArr(char** arr, unsigned short arrLen) {
    char *temp;
    for (int i = 0; i < arrLen - 1; i++) {
        for (int j = 0; j < arrLen - i - 1; j++) {
            if (!strsAscendAlph(arr[j], arr[j + 1]))
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printIndexedStrs(char** arr, unsigned short arrLen, unsigned short strLen) {
    printf("i  | string\n");
    printf("==============================\n");
    for (int i = 0; i < arrLen; i++) {
        printf("%-3d| %*s\n", i + 1, strLen, arr[i]);
    }
    printf("==============================\n");
    printf("i  | string\n");
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