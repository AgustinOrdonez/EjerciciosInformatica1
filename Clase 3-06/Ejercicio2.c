#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define VALUES_SIZE 100
#define MIN_RAND 10
#define MAX_RAND 20

int main(void) {
    int values[VALUES_SIZE];
    int i;
    int summ = 0;
    float avg;
    int max = MIN_RAND - 1;
    int min = MAX_RAND + 1;
    int j;
    int ammount;
    int maxAmmountValue;
    int maxAmmount = 0;

    srand(getpid());

    for (i = 0; i < VALUES_SIZE; i++) {
        values[i] = rand() % (MAX_RAND - MIN_RAND + 1) + MIN_RAND;
        summ += values[i];
        if (values[i] > max) {
            max = values[i];
        }
        else if (values[i] < min) {
            min = values[i];
        }
    }
    for (i = MIN_RAND; i <= MAX_RAND; i++) {
        ammount = 0;
        for (j = 0; j < VALUES_SIZE; j++) {
            if (values[j] == i) {
                ammount++;
            }
        }
        if (ammount > maxAmmount) {
            maxAmmount = ammount;
            maxAmmountValue = i;
        }
    }

    avg = (float) summ / VALUES_SIZE;
    printf("El promedio de los valores fue: %.2f\n"
           "El valor máximo fue el %d\n"
           "El valor mínimo fue el %d\n"
           "El valor más pequeño más repetido fue el %d y se repitió %d veces \n",//No se me ocurre forma(buena) de poner todos los valores que se repitieron igual cantidad de veces sin arrays redimensionables
           avg, max, min, maxAmmountValue, maxAmmount);

    return 0;
}
