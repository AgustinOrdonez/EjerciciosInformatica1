#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAXTHREADS 100

void *calculateFactorial(void *);

int main(int argc, char *args[]) {

    int i;
    int j;
    int *factorial;

    pthread_t threadIds[MAXTHREADS];//NOT HANDLED SEGMENTATION FAULT


    for (i = 1; i < argc; ++i) {

        pthread_create(&threadIds[i-1], NULL, calculateFactorial, (void *) args[i]);

    }


    for (j = 1; j < argc; ++j) {
        pthread_join(threadIds[j-1], (void **) &factorial);
        printf("[Thread %lud]Factorial de %s es: %d\n",threadIds[j-1], args[j],  *factorial);

    }

}


void *calculateFactorial(void *arg) {
    int i;
    int *factorial = malloc(sizeof(int));
    *factorial = 1;

    for (i = 1; i <= atoi((char *) arg); i++) {
        *factorial = *factorial * i;
    }
    return factorial;
}

