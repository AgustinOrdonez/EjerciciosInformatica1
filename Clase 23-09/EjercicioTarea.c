#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

#define MAX_NAME_LENGTH 30

typedef struct {
    int id;
    char nombre[MAX_NAME_LENGTH];
    int edad;
    float altura;
    float peso;
} Persona;

void imprimirPersona(Persona *);

int escribirPersonaEnArchivo(Persona *, FILE *);

int leerPersonaPorId(FILE *, int, Persona *);

int escribirArrayPersonasEnArchivo(Persona[], int, FILE *);

int leerArrayDePersonasDeArchivo(FILE *, Persona **);

void inicializarPersonaPorTeclado(Persona *, int);

int buscarPersonaPorNombre(Persona [], int, char *, Persona *);

int editarEntradaConId(int, FILE *, Persona *);

int main() {
    FILE *file;
    Persona *personas;
    bool mostrarMenu = true;
    int opcionMenu;
    int cantidadDePersonas;
    char personaABuscar[MAX_NAME_LENGTH];
    int idABuscar;
    Persona personaEncontrada;
    int errCode;

    personas = (Persona *) malloc(sizeof(Persona));
    if (!personas) {
        return -1;
    }
    file = fopen("personas", "r");
    if (file) {
        cantidadDePersonas = leerArrayDePersonasDeArchivo(file, &personas);
        fclose(file);
    }
    else {
        personas = (Persona *) realloc(personas, 0);
    }
    while (mostrarMenu) {
        printf("=======================\n"
               "Elija alguna de las siguientes opciones:\n"
               "1) Cargar persona\n"
               "2) Buscar persona por nombre\n"
               "3) Buscar persona por id\n"
               "4) Editar una persona\n"
               "5) Salir del menu\n"
               "=======================\n");
        scanf("%d", &opcionMenu);
        switch (opcionMenu) {
            case 1:
                if (!personas) {
                    personas = (Persona *) malloc(sizeof(Persona));
                    cantidadDePersonas = 1;
                }
                else {
                    personas = (Persona *) realloc(personas, sizeof(Persona) * ++cantidadDePersonas);
                }
                file = fopen("personas", "a");
                if (personas) {
                    inicializarPersonaPorTeclado(&personas[cantidadDePersonas - 1], cantidadDePersonas);
                    if (!file) { return -2; }
                    escribirPersonaEnArchivo(&personas[cantidadDePersonas - 1], file);
                    fclose(file);
                }
                else {
                    printf("Mallok es mallo\n");
                }
                break;
            case 2:
                printf("Ingrese el nombre de la persona a buscar\n");
                scanf("%s", personaABuscar);
                if (personas) {
                    file = fopen("personas", "r");
                    errCode = buscarPersonaPorNombre(personas, cantidadDePersonas, personaABuscar, &personaEncontrada);
                    fclose(file);
                    if (errCode != -1) {
                        printf("Persona encontrada, sus datos son:\n");
                        imprimirPersona(&personaEncontrada);
                    }
                    else {
                        printf("La persona no está registrada\n");
                    }
                }
                else {
                    printf("El array está vacío maestro\n");
                }
                break;
            case 3:
                printf("Ingrese el id de la persona a buscar\n");
                scanf("%d", &idABuscar);
                if (personas) {
                    file = fopen("personas", "r");
                    errCode = leerPersonaPorId(file, idABuscar, &personaEncontrada);
                    fclose(file);
                    if (errCode != -1) {
                        printf("Persona encontrada, sus datos son:\n");
                        imprimirPersona(&personaEncontrada);
                    }
                    else {
                        printf("La persona no está registrada\n");
                    }
                }
                else {
                    printf("El array está vacío maestro\n");
                }
                break;
            case 4:
                printf("Ingrese el id de la persona a editar\n");
                scanf("%d", &idABuscar);
                file = fopen("personas", "r+");
                if (!file) { return -3; }
                editarEntradaConId(idABuscar, file, personas);
                fclose(file);
                break;
            case 5:
                mostrarMenu = false;
                break;
            default:
                printf("Opción no válida\n");
                break;
        }

    }
    free(personas);
}

void imprimirPersona(Persona *persona) {
    printf("Id: %d\n", persona->id);
    printf("Nombre: %s\n", persona->nombre);
    printf("Edad: %d\n", persona->edad);
    printf("Altura: %.2f\n", persona->altura);
    printf("Peso: %.2f\n", persona->peso);
}

/**Returns -1 if error*/
int escribirPersonaEnArchivo(Persona *persona, FILE *file) {
    int bytesWritten = fwrite(persona, sizeof(Persona), 1, file);
    return (!bytesWritten) ? -1 : 0;
}

/**Returns -1 if error*/
int leerPersonaPorId(FILE *file, int id, Persona *persona) {
    int bytesRead;
    fseek(file, (id - 1) * sizeof(Persona), SEEK_SET);
    bytesRead = fread(persona, sizeof(Persona), 1, file);
    return (!bytesRead) ? -1 : 0;
}

/**Returns -1 if error*/
int escribirArrayPersonasEnArchivo(Persona personas[], int arraySize, FILE *file) {
    int bytesWritten = fwrite(personas, sizeof(Persona), arraySize, file);
    return (bytesWritten != arraySize) ? -1 : 0;

}

/**Expects pointer has memory allocated for at least one element, returns the ammount of elements found but -1 if you don't have enough memory*/
int leerArrayDePersonasDeArchivo(FILE *file, Persona **personasSalida) {
    int readenBytes = 1;
    int i = 0;;

    while (readenBytes == 1) {
        readenBytes = fread((*personasSalida) + i++, sizeof(Persona), 1, file);
        *personasSalida = (Persona *) realloc(*personasSalida, sizeof(Persona) * (i + 1));
        if (*personasSalida == 0) {
            i = 0;
            readenBytes = -1;
        }
    }
    *personasSalida = (Persona *) realloc(*personasSalida,
                                          sizeof(Persona) * (i - 1));//Dejo el espacio justo para la gente que hay
    return i - 1;
}

void inicializarPersonaPorTeclado(Persona *persona, int id) {
    persona->id = id;
    printf("Ingrese el nombre de la persona\n");
    scanf("%s", (persona->nombre));
    printf("Ingrese la edad de la persona\n");
    scanf("%d", &(persona->edad));
    printf("Ingrese la altura de la persona(en metros)\n");
    scanf("%f", &(persona->altura));
    printf("Ingrese el peso de la persona(en Kgf)\n");
    scanf("%f", &(persona->peso));
}

/**Returns -1 if person wasn't found*/
int buscarPersonaPorNombre(Persona personas[], int arraySize, char *nombre, Persona *personaEncontrada) {
    int i;
    bool found = false;

    for (i = 0; i < arraySize && !found; i++) {
        if (!strcmp(personas[i].nombre, nombre)) {
            *personaEncontrada = personas[i];
            found = true;
        }
    }
    return (found) ? 0 : -1;
}

int editarEntradaConId(int id, FILE *file, Persona *personas) {
    fseek(file, (id - 1) * sizeof(Persona), SEEK_SET);
    inicializarPersonaPorTeclado((personas + (id - 1)), id);
    escribirPersonaEnArchivo((personas + (id - 1)), file);
}
