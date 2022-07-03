#include <stdio.h>
#include "string.h"

#define STRING_LENGTH 30

void emptyString(char *, int);

int countChar(char *, int, char);

int myStrLen(char *);

void myStrCpy(char *, char *);

void invertString(char *);

void strToUpperCase(char *);

void strToLowerCase(char *);

void capitalizeFirstLetter(char *);

void removeBlankSpaces(char *);

int countWords(char *);

char isAlphaNumeric(char *);

char isANumber(char *);

char isAlpha(char *);

void generateEmailAddress(char *);

char startsWith(char *, char *);

int main() {
    char string[STRING_LENGTH] = "sdsd";
    char stringB[STRING_LENGTH] = "sda";

    //emptyString(string, 10);
    //invertString(string);
    //strToUpperCase(string);
    //strToLowerCase(string);
    //capitalizeFirstLetter(string);
    //removeBlankSpaces(string);
    //generateEmailAddress(string);
    for (int i = 0; i < STRING_LENGTH; ++i) {
        printf("|%c|  ", string[i]);
    }
    //printf("\n%d words", countWords(string));
    //printf("\nStarts with: %d", startsWith(string, stringB));



    /*char *str[] = {
            "Hello",
            "World"
    };

    printf("Posición de memoria: %d\n", str + 1);
    puts(str[1]);
    *(str + 1) = "fdf";
    //*(*(str + 1) + 1) = 0;
    printf("Char: %c\n", *(*(str + 1) + 1));
    printf("Posición de memoria: %d\n", str + 1);
    puts(str[1]);*/
    //Apparently you can change strings on char pointer array, but you can't change the individual chars of the string



    return 0;
}


void emptyString(char *string, int maxSize) {
    for (int i = 0; i < maxSize; ++i) {
        string[i] = 0;
    }
}

int countChar(char *string, int maxSize, char character) {
    int i;
    int count = 0;
    for (i = 0; i < maxSize; ++i) {
        if (*(string + i) == character) {
            count++;
        }
    }
    return count;
}

/**Expecting to get a string ending with 0*/
int myStrLen(char *string) {
    int count = 0;
    while (*string) {
        count++;
        string++;
    }
    return count;
}

/**Expecting to get a string ending with 0 and destination at least the same size as source*/
void myStrCpy(char *dest, char *source) {
    while (*source) {
        *dest = *source;
        source++;
        dest++;
    }
    *dest = 0;
}

/**Expecting to get a string ending with 0*/
void invertString(char *str) {
    int stringLength = myStrLen(str);
    int i;
    char temp;

    for (i = 0; i < stringLength / 2; ++i) {
        temp = *(str + i);
        *(str + i) = *(str + stringLength - 1 - i);
        *(str + stringLength - 1 - i) = temp;
    }
}

/**Expecting to get a string ending with 0*/
void strToUpperCase(char *str) {
    while (*str) {
        if (*str > 96 && *str < 123) {
            *str = *str - 32;
        }
        str++;
    }
}

/**Expecting to get a string ending with 0*/
void strToLowerCase(char *str) {
    while (*str) {
        if (*str > 64 && *str < 91) {
            *str = *str + 32;
        }
        str++;
    }
}

/**Expecting to get a string ending with 0*/
void capitalizeFirstLetter(char *str) {
    if (*str > 96 && *str < 123) {
        *str = *str - 32;
    }
    str++;
    while (*str) {
        if (*str > 64 && *str < 91) {
            *str = *str + 32;
        }
        str++;
    }
}

/**Expecting to get a string ending with 0*/
void removeBlankSpaces(char *str) {
    int i = 0;
    int j;

    while (*(str + i)) {
        while (*(str + i) == 32) {
            j = i;
            while (*(str + j)) {
                *(str + j) = *(str + j + 1);
                j++;
            }
        }
        i++;
    }
}

/**Expecting to get a string ending with 0*/
int countWords(char *str) {
    int count = 0;
    while (*str) {
        str++;
        if (*(str - 1) != 32 && (*str == 32 || *str == 0)) {
            count++;
        }
    }
    return count;
}

char isAlphaNumeric(char *str) {
    char isAlphanumeric = 1;
    while (*str || isAlphanumeric) {
        if (!(*str >= 48 && *str <= 57 || *str >= 65 && *str <= 90 || *str >= 97 && *str <= 122)) {
            isAlphanumeric = 0;
        }
        str++;
    }
    return isAlphanumeric;
}

char isANumber(char *str) {
    char isANumber = 1;
    while (*str || isANumber) {
        if (!(*str >= 48 && *str <= 57)) {
            isANumber = 0;
        }
        str++;
    }
    return isANumber;
}

char isAlpha(char *str) {
    char isAlpha = 1;
    while (*str || isAlpha) {
        if (!(*str >= 65 && *str <= 90 || *str >= 97 && *str <= 122)) {
            isAlpha = 0;
        }
        str++;
    }
    return isAlpha;
}

/**Expects a string at least 27 bytes long*/
void generateEmailAddress(char *str) {
    char name[20];
    char surname[20];
    char *domain = "@frba.utn.edu.ar";
    int i;

    printf("Ingrese nombre\n");
    fgets(name, 20, stdin);//It doesn't work well with more than 20 long strings, don't know how to fix
    printf("Ingrese apellido\n");
    fgets(surname, 20, stdin);

    *(str) = *name;
    for (i = 1; i <= 8 && *(surname + i - 1) != 10; i++) {
        *(str + i) = *(surname + i - 1);
    }
    while (*domain) {
        *(str + i) = *(domain);
        domain++;
        i++;
    }
    *(str + i) = 0;
}

/**Expecting to get string B to end with 0, also expects string A longer than B
 * It  checks if string A starts with string B*/
char startsWith(char *strA, char *strB) {
    char startsWith = 1;
    while (*strB && startsWith) {
        if (*strB != *strA) {
            startsWith = 0;
        }
        strA++;
        strB++;
    }
    return startsWith;
}