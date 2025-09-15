#include <stdio.h>
#include <conio.h> //#include <curses.h> для Unix-like ОС

int loop();
int roman(size_t number, short int value, char *numeral);


int main() {
    printf("Program for quick arabic decimal to roman numerical system translation\n");
    while (!loop()) {}
    return 0;
}

int loop() {
    unsigned int numberBuffer = 0; 
    int success = 0;

    printf("Enter a positive integer less than 4000 to translate or press Ctrl+D to quit program\n");
    success = scanf("%u", &numberBuffer);

    if (success == EOF) {
        printf("\nEnd of input detected, exiting program\n");
        return 1;
    } else if(!success || numberBuffer < 1 || numberBuffer > 3999) {
        printf("Please enter only positive integers less than 4000 (bad input)\n");
    } else {
        numberBuffer = roman(numberBuffer, 1000, "M");
        numberBuffer = roman(numberBuffer, 900, "CM");
        numberBuffer = roman(numberBuffer, 500, "D");
        numberBuffer = roman(numberBuffer, 400, "CD");
        numberBuffer = roman(numberBuffer, 100, "C");
        numberBuffer = roman(numberBuffer, 90, "XC");
        numberBuffer = roman(numberBuffer, 50, "L");
        numberBuffer = roman(numberBuffer, 40, "XL");
        numberBuffer = roman(numberBuffer, 10, "X");
        numberBuffer = roman(numberBuffer, 9, "IX");
        numberBuffer = roman(numberBuffer, 5, "V");
        numberBuffer = roman(numberBuffer, 4, "IV");
        numberBuffer = roman(numberBuffer, 1, "I");
        printf("\n");
    }
    fflush(stdin); //Для Windows, на Unix-like інші імплементації
    char ch;
    while((ch = getchar()) != '\n' && ch != EOF){}
    return 0;
}

int roman(size_t number, short int value, char *numeral) {
    while (number>=value) {
        printf("%s", numeral);
        number -= value;
    }
    return number;
}