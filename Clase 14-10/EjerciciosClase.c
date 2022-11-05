#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

void strToUpperCase(char *str);

int getNumberFromChar(char);

int isNumber(char);

int binaryToDecimal(char *);

int octalToDecimal(char *);

int hexToDecimal(char *);

int printNumberOnAllBases(int);

char getCharFromInt(int);

void decToBinary(int, char *);

void decToBinary2(int, char *);

void decToBaseX(int, char *, int);


int main() {
    char binaryNumber[123];

//    decToBinary2(38, binaryNumber);
    decToBaseX(6831, binaryNumber, 16);
    printf("bin: %d\n", binaryToDecimal("01"));
    printf("oct: %d\n", octalToDecimal("10"));
    printf("decToBin: %s\n", binaryNumber);
//    printNumberOnAllBases(15);
    return 0;
}


void strToUpperCase(char *str) {
    while (*str) {
        if (*str > 96 && *str < 123) {
            *str = *str - 32;
        }
        str++;
    }
}

int isNumber(char chr) {
    int isNumber = 1;
    if (!(chr >= '0' && chr <= '9')) {
        isNumber = 0;
    }
    return isNumber;
}

int getNumberFromChar(char chr) {
    int number = -1;
    //printf("NUMERO: %d\n",chr);
    if (isNumber(chr)) {
        number = chr - '0';
    }
    //printf("NUM:%d \n",number);

    return number;
}

int getHexNumberFromChar(char chr) {
    int decimal;
    bool isHex = true;
    strToUpperCase(chr);
    if (isNumber(chr)) {
        decimal = getNumberFromChar(chr);
    }
    else if (chr >= 'A' && chr <= 'F') {
        decimal = chr - 'A' + 10;
    }
    else {
        decimal = -1;
    }
    return decimal;
}

int binaryToDecimal(char *number) {
    int sum = 0;
    int i = strlen(number) - 1;
    bool isBinary = true;

    while (*number && isBinary) {
        if (getNumberFromChar(*number) >= 0 && getNumberFromChar(*number) <= 1) {
            sum += getNumberFromChar(*number) * pow(2, i);
            number++;
            i--;
        }
        else {
            isBinary = false;
        }
    }
    return isBinary ? sum : -1;
}

int octalToDecimal(char *number) {
    int sum = 0;
    int i = strlen(number) - 1;
    bool isOctal = true;

    while (*number && isOctal) {
        if (getNumberFromChar(*number) >= 0 && getNumberFromChar(*number) <= 7) {
            sum += getNumberFromChar(*number) * pow(8, i);
            number++;
            i--;
        }
        else {
            isOctal = false;
        }
    }
    return isOctal ? sum : -1;
}

int hexToDecimal(char *number) {
    int sum = 0;
    int i = strlen(number) - 1;
    bool isOctal = true;

    while (*number && isOctal) {
        if (getNumberFromChar(*number) >= 0 && getNumberFromChar(*number) <= 7) {
            sum += getNumberFromChar(*number) * pow(16, i);
            number++;
            i--;
        }
        else {
            isOctal = false;
        }
    }
    return isOctal ? sum : -1;
}

int printNumberOnAllBases(int num) {
    printf("decimal: %d\noctal: %o\nhexadecimal: %x", num, num, num);
}


char getCharFromInt(int integer) {
    int chr = -1;
    if (integer >= 0 && integer <= 9) {
        chr = integer + '0';
    }
    return chr;
}

void decToBinary(int decimal, char *bin) {
    int num = decimal;
    int i = 0;
    while (num >= 2) {
        num = num / 2;
        i++;
    }
    while (decimal >= 2) {
        bin[i] = getCharFromInt(decimal % 2);
        i--;
        decimal = decimal / 2;
    }
    *bin = getCharFromInt(decimal % 2);
}

void decToBinary2(int decimal, char *bin) {
    int i;
    int j;
    int ant = 1;
    bool first = true;

    while (ant >= 0) {
        i = 0;
        while (pow(2, i) <= decimal) {
            i++;
        }
        for (j = 0; j < (ant - i) && !first; j++) {
            *bin = '0';
            bin++;
        }
        first = false;
        decimal -= pow(2, i - 1);
        ant = i - 1;
        if (i != 0) {
            *bin = '1';
            bin++;
        }
    }
    *bin = 0;
}

void decToBaseX(int decimal, char *dest, int base) {
    int num = decimal;
    int i = 0;
    while (num >= base) {
        num = num / base;
        i++;
    }
    while (decimal >= base) {
        if ((decimal % base) < 10) {
            dest[i] = getCharFromInt(decimal % base);
        }
        else {
            dest[i] = (decimal % base) + 'A' - 10;

        }
        i--;
        decimal = decimal / base;
    }
    if ((decimal % base) < 10) {//Habría que hacer esto funcion.....
        *dest = getCharFromInt(decimal % base);
    }
    else {
        *dest = (decimal % base) + 'A' - 10;
    }

}