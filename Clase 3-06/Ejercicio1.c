#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define VALUES_SIZE 100

int main(void) {
    int values[VALUES_SIZE];
    int i;
    int rep;
    int repCount = 0;

    srand(getpid());

    printf("Ingrese un número entero entre 0 y 100 para contar su repetición\n");
    scanf("%d", &rep);

    for (i = 0; i < VALUES_SIZE; i++) {
        values[i] = rand() % 101;
        if (values[i] == rep) {
            repCount++;
        }
    }
    if (repCount == 1) {
        printf("El número %d se repitió %d vez\n", rep, repCount);
    }
    else {
        printf("El número %d se repitió %d veces\n", rep, repCount);
    }
    return 0;
}
