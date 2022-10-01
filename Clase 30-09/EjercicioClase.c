#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LENGTH 30
#define GENDER_LENGTH 30
#define MAX_PERSONAS 20

typedef struct {
    int id;
    char name[NAME_LENGTH];
    char gender[GENDER_LENGTH];
} Persona;

void removeEndLine(char *);

void imprimirPersona(Persona *);

int main() {

    FILE *fp;
    char buff[1000];
    char *token;
    Persona personas[MAX_PERSONAS];
    int i = 0;

    fp = fopen("MOCK_DATA.csv", "r");
    if (fp == NULL) {
        printf("Error al abrir csv\n");
        return -1;
    }
    fgets(buff, sizeof(buff), fp);
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        removeEndLine(buff);
        // completar...
        token = strtok(buff, ",");
        if (token != NULL) {
            personas[i].id = atoi(token);
            token = strtok(NULL, ",");
        }
        if (token != NULL) {
            strcpy(personas[i].name, token);
            token = strtok(NULL, ",");
        }
        if (token != NULL) {
            strcpy(personas[i].gender, token);
        }
        imprimirPersona(&personas[i]);
//        while (token != NULL) {
//            token = strtok(NULL, ",");
//            if (token != NULL) {
//                printf("token=%s\n", token);
//            }
//        }

        i++;
    }

    fclose(fp);
    return 0;


}

void removeEndLine(char *str) {
    if (*(str + strlen(str) - 1) == '\n') {
        *(str + strlen(str) - 1) = 0;
    }
}

void imprimirPersona(Persona *persona) {
    printf("===============\n");
    printf("Id: %d\n", persona->id);
    printf("Nombre: %s\n", persona->name);
    printf("Género: %s\n", persona->gender);
    printf("===============\n");
}