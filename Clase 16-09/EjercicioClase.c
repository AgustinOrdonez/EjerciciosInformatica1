#include "Funciones.h"
#include <stdio.h>
#include <malloc.h>

int main() {
    int i;
    int j;
    Alumno *alumnos;
    int cantidadDeAlumnos;
    int nuevaCantidadDeAlumnos;
    char añadir;

    printf("Ingrese la cantidad de alumnos a ingresar\n");
    scanf("%d", &cantidadDeAlumnos);

    //printf("%d", cantidadDeAlumnos * sizeof(Alumno));
    alumnos = (Alumno *) malloc(cantidadDeAlumnos * sizeof(Alumno));

    if (alumnos) {
        for (i = 0; i < cantidadDeAlumnos; i++) {
            pedirNombre(&alumnos[i]);
            pedirApellido(&alumnos[i]);
            pedirLegajo(&alumnos[i]);
            pedirNota(&alumnos[i]);
        }
        printf("Ingreso finalizado. Desea ingresar más alumnos?(Y para añadir más)\n");
        getc(stdin);
        scanf("%c", &añadir);
        if (añadir == 'Y') {
            printf("Ingrese la cantidad de alumnos agregar\n");
            getc(stdin);
            scanf("%d", &nuevaCantidadDeAlumnos);
            alumnos = (Alumno *) realloc(alumnos, (cantidadDeAlumnos + nuevaCantidadDeAlumnos) * (sizeof(Alumno)));
            if (alumnos) {
                for (i = cantidadDeAlumnos; i < (cantidadDeAlumnos + nuevaCantidadDeAlumnos); i++) {
                    pedirNombre(&alumnos[i]);
                    pedirApellido(&alumnos[i]);
                    pedirLegajo(&alumnos[i]);
                    pedirNota(&alumnos[i]);
                }
            }
            else {
                printf("FAIL2\n");
            }
        }
        for (j = 0; j < i; j++) {
            printf("Alumno número: %d:\n", j + 1);
            printAlumno(&alumnos[j]);
        }
        free(alumnos);
    }
    else {
        printf("FAIL\n");
    }

}

