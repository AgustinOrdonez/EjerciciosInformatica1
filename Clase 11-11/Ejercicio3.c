#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define MAXTHREADS 100

void *calculatePowerOf2(void *);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *args[]) {
    int i;
    int j;
    int *power;
    int temp=0;
    pthread_t threadIds[MAXTHREADS];//NOT HANDLED SEGMENTATION FAULT
    int *currPow;

    if (argc == 2) {


        for (i = 0; i < atoi(args[1]); ++i) {//NOT HANDLED EXCEPTION
            currPow= malloc(sizeof(int));
            *currPow=i;//O no malloc y poner sleep
            if (pthread_create(&threadIds[i], NULL, calculatePowerOf2, (void *) currPow) != 0) {
                exit(-1);
            }
//            usleep(5000);
        }


        for (j = 0; j < atoi(args[1]); ++j) {
            pthread_join(threadIds[j], (void **) &power);
            printf("[Thread %d]2 ^ %d = %d\n", threadIds[j], j, *(int *) power);
        }

    }
    else {
        printf("Cantidad de parámetros errónea\n");
    }

}


void *calculatePowerOf2(void *power) {
    int *result = malloc(sizeof(int));

    *result = pow(2, *(int *) power);
    free(power);
    return result;

}
