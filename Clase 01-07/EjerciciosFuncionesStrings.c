#include <stdio.h>


#define STRING_LENGTH 40

void emptyString(char *, int);

int countChar(char *, int, char);

int myStrLen(char *);

void myStrCpy(char *, char *);

void myStrNCpy(char *, char *, int);

void myStrCat(char *, char *);

void myStrNCat(char *, char *, int);

char myStrCmp(char *, char *);

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

int countWordsRepetition(char *, char *);

void removeConsecutiveSpaces(char *);

char isAnEmail(char *);

int main() {
    char string[STRING_LENGTH] = "yo Hola soyo     yo yo yoyo yo";
    char stringB[STRING_LENGTH] = "yo";
    //emptyString(string, 10);
    //invertString(string);
    //strToUpperCase(string);
    //strToLowerCase(string);
    //capitalizeFirstLetter(string);
    //removeBlankSpaces(string);
    removeConsecutiveSpaces(string);
    //generateEmailAddress(string);
    //myStrCat(string, stringB);
    for (int i = 0; i < STRING_LENGTH; ++i) {
        printf("|%c|  ", string[i]);
    }
    //printf("\n%d words", countWords(string));
    //printf("\nStarts with: %d", startsWith(string, stringB));
    printf("\nString B repeition on string A: %d", countWordsRepetition(string, stringB));
    printf("\nString is an email: %d", isAnEmail(string));



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

void myStrNCpy(char *dest, char *source, int limit) {
    int check = 0;
    while (*source && check < limit) {
        *dest = *source;
        check++;
        source++;
        dest++;
    }
    *dest = 0;
}

void myStrCat(char *strA, char *strB) {
    while (*strA) {
        strA++;
    }
    while (*strB) {
        *strA = *strB;
        strA++;
        strB++;
    }
}

void myStrNCat(char *strA, char *strB, int limit) {
    int check = 0;
    while (*strA) {
        check++;
        strA++;
    }
    while (*strB && check < limit) {
        *strA = *strB;
        check++;
        strA++;
        strB++;
    }
}

/**Returns 0 if equal, 1 if different*/
char myStrCmp(char *strA, char *strB) {
    char isEqual = 0;
    if (myStrLen(strA) == myStrLen(strB)) {
        while (*strA) {
            if (*strA != *strB && isEqual) {
                isEqual = 1;
            }
            strA++;
            strB++;
        }
    }
    else {
        isEqual = 1;
    }
    return isEqual;
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
    int j;

    while (*str) {
        while (*str == 32) {
            j = 0;
            while (*(str + j)) {
                *(str + j) = *(str + j + 1);
                j++;
            }
        }
        str++;
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
    //Don't check if name it's all letters because there are very weird names
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

/**Expecting to get string B to end with 0. Returns -1 if B is longer than A
 * It  checks if string A starts with string B*/
char startsWith(char *strA, char *strB) {
    char startsWith = 1;

    if (myStrLen(strA) > myStrLen(strB)) {
        while (*strB && startsWith) {
            if (*strB != *strA) {
                startsWith = 0;
            }
            strA++;
            strB++;
        }
    }
    else {
        startsWith = -1;
    }

    return startsWith;
}

/**Expects a string ending with 0. It returns -1 if string B is longer than A*/
int countWordsRepetition(char *strA, char *strB) {
    int rep = 0;
    int i = 0;
    char isSameWord = 1;
    char flag = 1;

    if (myStrLen(strA) > myStrLen(strB)) {
        while (*strA) {
            if ((flag || *(strA - 1) == 32) && *strA == *strB) {
                flag = 0;
                while (*(strB + i) && isSameWord) {
                    if (*(strB + i) != *(strA + i)) {
                        isSameWord = 0;
                    }
                    i++;
                }

                if (isSameWord) {
                    if (*(strA + i) == 32 || *(strA + i) == 0) {
                        rep++;
                    }
                }
                i = 0;
                isSameWord = 1;
            }

            strA++;
        }

    }
    else {
        rep = -1;
    }
    return rep;
}

void removeConsecutiveSpaces(char *str) {
    int j;

    while (*str) {
        while (*str == 32 && *(str + 1) == 32) {
            j = 0;
            while (*(str + j)) {
                *(str + j) = *(str + j + 1);
                j++;
            }
        }
        str++;
    }
}

/**Returns 1 if the string has only one @ and at least one . afterwards*/
char isAnEmail(char *str) {
    char isAnEmail = 0;
    int atCount = 0;

    while (*str) {
        if (*str == 64) {
            atCount++;
        }
        if (atCount == 1 && *str == '.') {
            isAnEmail = 1;
        }
        str++;
    }
    if (atCount != 1) {
        isAnEmail = 0;
    }
    return isAnEmail;
}