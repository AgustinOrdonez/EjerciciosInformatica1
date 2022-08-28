#include <stdio.h>
#include <string.h>

typedef struct {
    char nombre[32];
    int edad;
    char genero;
} Persona;

Persona initPersona(char *, int, char);

int comparePersona(Persona, Persona);

void cumplePersona(Persona *);

int main() {
    Persona a = initPersona("JUAN", 18, 'M');
    cumplePersona(&a);
    Persona b = initPersona("JUAN", 18, 'M');

    printf("%d\n", comparePersona(a, b));

    return 0;
}


Persona initPersona(char *nombre, int edad, char genero) {
    Persona persona;
    strcpy(persona.nombre, nombre);
    persona.edad = edad;
    persona.genero = genero;

    return persona;
}


int comparePersona(Persona a, Persona b) {
    int isPersona = 0;
    if (strcmp(a.nombre, b.nombre) || !(a.edad == b.edad) || !(a.genero == b.genero)) {
        isPersona = -1;
    }
    return isPersona;
}

void cumplePersona(Persona *persona) {
    persona->edad++;
}