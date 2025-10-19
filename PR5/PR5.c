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
bool endInput();
void flush_stdin();

int main() {
    printf("Program for sorting strings in alphabetical order.\n"
           "You can press Ctrl+D to end the program at any time.\n");
    do {
        loop();
    } while (!endInput());
    return 0;
}

void loop() {
    short success = 0;
    unsigned short arrLen = 0;
    printf("Enter the amount of compared strings (must be an integer less than %d): ", MAX_ARR_LEN);
    do {
        success = scanf("%u", arrLen);
    } while (!(validArrLen(arrLen, success)));

    unsigned short strLen = 0;
    printf("Enter the length of compared strings (must be an integer less than %d): ", MAX_ARR_LEN);
    do {
        success = scanf("%zi", strLen);
    } while (!(validStrLen(strLen, success)));

    char arr[arrLen][strLen];
    for (int i = 0; i < arrLen; i++) {
        printf("Enter string number %d: ", i);
        do {
            success = scanf("%s", &arr[i]);
        } while (!validStr(arr[i], strLen, success));
    }
    

}

bool validArrLen(unsigned short var, short success) {
    if (!(var && success && var < MAX_ARR_LEN)) {
        printf("Please enter a valid value: ");
        return false;
    } else if (success == EOF) {
        printf("End of input detected. Closing program.\n");
        exit(0);
    }
    return true;
}

bool validStrLen(unsigned short var, short success) {
    if (!(var && success && var < MAX_STR_LEN)) {
        printf("Please enter a valid value: ");
        return false;
    } else if (success == EOF) {
        printf("End of input detected. Closing program.\n");
        exit(0);
    }
    return true;
}

bool validStr(char* str, unsigned short len, short success) {
    if (success == EOF) {
        printf("End of input detected. Closing program.\n");
        exit(0);
    } else if (success) {
        for (int i = 0; i < len; i++) {
            if (str[i] == '\0') {
                printf("Please enter a valid string: ");
                return false;
            } else if (str[i] == '\n') {
                print("Fix yo shi vro");
            }
        }
    }
    return true;
}

bool endInput() {
    char ch;
    printf("Press Ctrl+D to end program. Enter any key to continue: ");
    ch = getchar();
    if (ch == EOF) {
        printf("End of input detected. Closing program.\n");
        return 1;
    }
    flush_stdin();
    return 0;
}

bool strsAscendAlph(char* str1, char* str2) {
    if (strcmp(str1, str2) > 0) {
        return false;
    } else {
        return true;
    }
}

void sortStrsByCondition(char** arr, void (*condition)(bool), unsigned short arrLen) {
    for(int i = 0; i < -1; i++) {
        for(int j = 0; j < num;j++) {
            if ( strcmp(mass[i],mass[j]) >0 )
            {
                char *tmp;
            tmp=mass[i];
            mass[i]=mass[j];
            mass[j]=tmp;
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