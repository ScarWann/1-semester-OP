#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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
bool validStr(char* str);
void cleanStr(char* str);
void exitWithMsg();
void printIndexedStrs(char** arr, unsigned short arrLen);
bool strsAscendAlph(char* str1, char* str2);
void sortStrsArr(char** arr, unsigned short arrLen);
bool endInput();
void flushStdin();

int main() {
    printf("Program for sorting strings of standard ASCII characters in alphabetical order. Non-ASCII characters get treated as 2-4 characters by the program\n"
           "Entering extra chars will automatically cut them.\n"
           "Entering less chars than specified will treat the empty spaces as char 0 ('\\0')\n"
           "You can press Ctrl+D or enter an empty string to end the program.\n");
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

    char** arr = (char**)malloc(arrLen * strLen * sizeof(char*));
    for (int i = 0; i < arrLen; i++) {
        arr[i] = (char*)malloc(strLen  * sizeof(char));
        printf("Enter string number %d: ", i + 1);

        do {
            if(!fgets(arr[i], strLen + 1, stdin)) exitWithMsg();

            cleanStr(arr[i]);
            flushStdin();
        } while (!validStr(arr[i]));
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

void cleanStr(char* str) {
    for (int i = strlen(str);; i--) {
        if (str[i] == '\0') continue;
        if (str[i] == '\n') {
            str[i] = '\0';
        } else return;
    }
}

bool validArrLen(unsigned short var, short success) {
    if (success == EOF) {
        exitWithMsg();
    } else if (!(var && success && var < MAX_ARR_LEN && var > 1)) {
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

bool validStr(char* str) {
    if (str[0] == 0) {
        exitWithMsg();
    }
    return true;
}

void exitWithMsg() {
    printf("End of input detected. Closing program.\n");
    exit(0);
}

bool strsAscendAlph(char* str1, char* str2) {
    if (strcasecmp(str1, str2) > 0) {
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

void printIndexedStrs(char** arr, unsigned short arrLen) {
    printf("i  | string\n");
    printf("==============================\n");
    for (int i = 0; i < arrLen; i++) {
        printf("%-3d| %s\n", i + 1, arr[i]);
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