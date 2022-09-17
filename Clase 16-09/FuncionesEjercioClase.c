#include "Funciones.h"
#include <stdio.h>

void pedirNombre(Alumno *alumno) {
    printf("Ingrese el nombre del alumno\n");
    //fgets(alumno->nombre, MAX_NAME_LENGTH, stdin);
    scanf("%s", alumno->nombre);
}

void pedirApellido(Alumno *alumno) {
    printf("Ingrese el apellido del alumno\n");
    //fgets(alumno->apellido, MAX_NAME_LENGTH, stdin);
    scanf("%s", alumno->apellido);
}

void pedirLegajo(Alumno *alumno) {
    printf("Ingrese el numero de legajo del alumno\n");
    scanf("%d", &alumno->legajo);
}

void pedirNota(Alumno *alumno) {
    printf("Ingrese la nota del alumno\n");
    scanf("%d", &alumno->nota);
}

void printAlumno(Alumno *alumno) {
    printf("El alumno se llama: %s %s\n", alumno->nombre, alumno->apellido);
    printf("El legajo es: %d\n", alumno->legajo);
    printf("Tiene una nota de: %d\n", alumno->nota);
}