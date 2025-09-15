#include <stdio.h>
//#include <conio.h> // 
#include <curses.h> //для Unix-like ОС
#include <math.h>

void loop();
size_t roman(size_t number, short int value, char *numeral);


int main() {
    printf("Program for quick arabic decimal to roman numerical system translation\n");
    while (true) {
        loop();
    }
    return 0;
}

void loop() {
    size_t numberBuffer = 0; 
    char *lineBuffer;
    size_t lineBufferSize = sizeof(lineBuffer);
    unsigned short characters;


    printf("Enter a positive integer less than 4000 to translate or press Ctrl+C (^C) to quit program\n");
    characters = getline(&lineBuffer, &lineBufferSize, stdin);

    //Перевірка на валідність вхідних даних
    for (size_t i = 0; i < characters; i++) {
        if (lineBuffer[i] == '\n') {
            characters--;
            lineBuffer[i] = '\0';
            break;
        } else if (lineBuffer[i] < '0' || lineBuffer[i] > '9') {
            printf("Please enter only positive integers less than 4000 (bad input)\n");
            return;
        }
    }

    //Конвертація string в int
    for (int i = 0; i < characters; i++) {
        numberBuffer += (lineBuffer[characters - i - 1] - 48) * pow(10, i);
    }

    //Крайній випадок, коли задане число не в правильному діапазоні
    if (numberBuffer == 0 || numberBuffer > 3999) {
        printf("Please enter only positive integers less than 4000 (bad input)\n");
        return;
    }

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
    return;
}

size_t roman(size_t number, short int value, char *numeral) {
    while (number>=value) {
        printf("%s", numeral);
        number -= value;
    }
    return number;
}