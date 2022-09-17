//#ifndef EJERCICIOSOBLIGATORIOS1_FUNCIONES_H
//#define EJERCICIOSOBLIGATORIOS1_FUNCIONES_H

//#endif //EJERCICIOSOBLIGATORIOS1_FUNCIONES_H
#define MAX_NAME_LENGTH 32

typedef struct {
    char nombre[MAX_NAME_LENGTH];
    char apellido[MAX_NAME_LENGTH];
    int legajo;
    int nota;
} Alumno;

void pedirNombre(Alumno *);

void pedirApellido(Alumno *);

void pedirLegajo(Alumno *);

void pedirNota(Alumno *);

void printAlumno(Alumno *);
