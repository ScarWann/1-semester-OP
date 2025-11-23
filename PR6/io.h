#ifndef IO_H
#define IO_H

#define MAX_RAND_MAT_SIZE 100
#define MAX_MAN_MAT_SIZE 10
#define MAX_DIGITS 14

void outputCurrentState();
void outputTitle();
void printCentered(char* content, int offset);
unsigned reallen(char* str);
char** splitStr(char* str, char ch);
unsigned countCharsInStr(char* str, char ch);
void outputSolutions(double* solutions);
void flushStdin();
bool userExit();
void* EOFexit();
void printSubscript(unsigned int n);

#endif