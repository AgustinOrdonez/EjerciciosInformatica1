#include <stdio.h>
#include <string.h>

#define WORKING_LIMIT 50

void printHelpMessage();

int main(int argc, char *args[]) {
    char areEqual = -1;
    char isValidOperation = 1;
    int i;
    char originalStr2[WORKING_LIMIT];

    if (argc == 4) {
        printf("Parámetros introducidos:\n");
        for (i = 1; i < argc; ++i) {
            printf("Parámetro %d: %s\n", i, args[i]);
        }

        //Saving str2
        strcpy(originalStr2, args[3]);

        if (!strcmp(args[1], "copy")) {
            strcpy(args[2], originalStr2);
        }
        else if (!strcmp(args[1], "compare")) {
            areEqual = !strcmp(args[2], originalStr2);
        }
        else if (!strcmp(args[1], "concatenate")) {
            strcat(args[2], originalStr2);
        }
        else {
            printHelpMessage();
            isValidOperation = 0;
        }
        if (isValidOperation) {
            if (areEqual == -1) {
                printf("Nuevo string: %s", args[2]);
            }
            else {
                printf(areEqual ? "Son iguales" : "Son distintos");
            }
        }

    }
    else {
        printHelpMessage();
    }

    return 0;
}

void printHelpMessage() {
    printf("Uso: <Nombre del archivo> <copy/compare/concatenate> <str1> <str2>\n");
}