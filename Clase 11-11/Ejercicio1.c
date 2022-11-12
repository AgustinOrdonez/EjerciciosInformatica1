#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAXTHREADS 100

void *calculateFactorial(void *);

int main(int argc, char *args[]) {

    int i;
    pthread_t threadIds[MAXTHREADS];//NOT HANDLED SEGMENTATION FAULT

    for (i = 1; i < argc; ++i) {

        pthread_create(&threadIds[i], NULL, calculateFactorial, (void *) args[i]);

    }
    pthread_exit(NULL);

}


void *calculateFactorial(void *arg) {
    int i;
    int factorial = 1;
    for (i = 1; i <= atoi((char *) arg); i++) {
        factorial = factorial * i;
    }
    printf("Factorial de %s arg es: %d\n", (char *) arg, factorial);
    return NULL;
}

