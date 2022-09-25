#include <stdio.h>

void escribir();

void leer();

void buscarPorIndice(int);

typedef struct {
    int id;
    char nombre[30];
    char sexo;
} Registro;

int main() {
    escribir();
//    leer();
    buscarPorIndice(2);
    return 0;
}


void escribir() {

    Registro a = {1, "Juan", 'M'};
    Registro b = {2, "Maria", 'F'};
    Registro c = {3, "Pedro", 'M'};
    Registro registroArray[3] = {a, b, c};
    FILE *fp;

    fp = fopen("./listado.bin", "w");
    if (fp != 0) {
        fwrite(registroArray, sizeof(registroArray), 1, fp);
        fclose(fp);
    }
    else {
        printf("NO");
    }
}

void leer() {
    FILE *fp;
    Registro registroArray[3];
    int i;
    fp = fopen("./listado.bin", "r");

    if (fp != 0) {
        fread(registroArray, sizeof(registroArray), 1, fp);
        for (i = 0; i < 3; i++) {
            printf("id: %d\nnombre: %s\nsexo: %c\n", registroArray[i].id, registroArray[i].nombre,
                   registroArray[i].sexo);
        }
    }
}

void buscarPorIndice(int indice) {
    FILE *fp;
    Registro a;
    fp = fopen("./listado.bin", "r");

    fseek(fp, sizeof(Registro) * indice, SEEK_SET);
    fread(&a, sizeof(Registro), 1, fp);
    printf("id: %d\nnombre: %s\nsexo: %c\n", a.id, a.nombre, a.sexo);
    fclose(fp);
}