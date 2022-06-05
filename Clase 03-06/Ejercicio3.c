#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define VALUES_SIZE 1000
#define MIN_RAND 0
#define MAX_RAND 100
#define INTERESING_VALUES_SIZE 4

int main(void) {
    int values[VALUES_SIZE];
    int i;
    int j;
    int interestingValues[INTERESING_VALUES_SIZE] = {0, 1, 10, 100};
    int interestingValuesIndex[INTERESING_VALUES_SIZE];

    for (i = 0; i < INTERESING_VALUES_SIZE; ++i) {
        interestingValuesIndex[i] = VALUES_SIZE;
    }

    srand(getpid());

    for (i = 0; i < VALUES_SIZE; i++) {
        values[i] = rand() % (MAX_RAND - MIN_RAND + 1) + MIN_RAND;
        for (j = 0; j < INTERESING_VALUES_SIZE; j++) {
            if (values[i] == interestingValues[j]) {
                if (i < interestingValuesIndex[j]) {
                    interestingValuesIndex[j] = i;
                }
            }
        }
    }

    for (i = 0; i < INTERESING_VALUES_SIZE; ++i) {
        if (interestingValuesIndex[i] != VALUES_SIZE) {
            printf("Indice del primer %d es : %d\n", interestingValues[i], interestingValuesIndex[i]);
        }
        else {
            printf("El valor %d no ha aparecido\n", interestingValues[i]);
        }
    }

    return 0;
}
