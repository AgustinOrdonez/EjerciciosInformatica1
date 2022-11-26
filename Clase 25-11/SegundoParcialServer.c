#include <stdio.h>
#include <stdbool.h>
#include "sock-lib.h"
#include <pthread.h>
#include <string.h>


#define HOSTNAME_LEN 64
#define STATUS_SIZE 10
#define MAX_THREAD_COUNT 10

typedef struct {
    char hostname[HOSTNAME_LEN];
    int cpu;
    int mem;
} Status;

void *handleClient(void *);

void *checkArraySize(void *);

int appendToLogFile(Status param);

void emptyStatus(Status status);

Status clientStatus[STATUS_SIZE];

int clientAmmount = 0;

unsigned int threads = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;

int arrFull = 0;

int main() {
    struct sockaddr_in myAddr;
    int socketFd;
    int *sockId;
    pthread_t threadIds[MAX_THREAD_COUNT];
    pthread_t checkingThreadId;

    pthread_create(&checkingThreadId, NULL, checkArraySize, NULL);
    pthread_detach(checkingThreadId);


    if ((socketFd = abrirConeccion(&myAddr)) == -1) {
        printf("No se pudo abrir el servidor\n");
        exit(-2);
    }
    else {
        printf("Servidor abierto correctamente\n");
    }


    while (true) {
        sockId = malloc(sizeof(int));


        pthread_mutex_lock(&mutex);
        if (threads < MAX_THREAD_COUNT) {

//            pthread_mutex_lock(&mutexB);
            if (!arrFull) {
                *sockId = aceptarPedidos(socketFd);
            }
//            pthread_mutex_unlock(&mutexB);


//            pthread_mutex_lock(&mutex);
            pthread_create(&threadIds[threads], NULL, handleClient, sockId);
            pthread_detach(threadIds[threads++]);
//            pthread_mutex_unlock(&mutex);
        }
        else {
//            pthread_mutex_unlock(&mutex);
//            sleep(1);
        }
        pthread_mutex_unlock(&mutex);

    }

}


void *handleClient(void *arg) {
    int *sockid = (int *) arg;
    unsigned int bytesToRead;
    char *buffer;
    char *token;
    Status status;

    read(*sockid, &bytesToRead, sizeof(int));
//    printf("bytes: %d\n", bytesToRead);
//    bytesToRead = ntohs(bytesToRead);

    buffer = (char *) malloc(bytesToRead + 1);
    read(*sockid, buffer, bytesToRead + 1);
    buffer[bytesToRead] = 0;
    printf("TR:%s\n", buffer);

    if ((token = strtok(buffer, ";")) != NULL) {
        strcpy(status.hostname, token);
    }
    else {
        printf("No se pudo leer el token\n");
    }
    if ((token = strtok(NULL, ";")) != NULL) {
        status.cpu = atoi(token);
    }
    else {
        printf("No se pudo leer el token\n");

    }
    if ((token = strtok(NULL, ";")) != NULL) {
        status.mem = atoi(token);
    }
    else {
        printf("No se pudo leer el token\n");
    }


    pthread_mutex_lock(&mutex);
    printf("Threads:%d\n", threads);
    threads--;
//    pthread_mutex_unlock(&mutex);

//    pthread_mutex_lock(&mutexA);

    if (clientAmmount < STATUS_SIZE) {
        clientStatus[clientAmmount++] = status;
    }//MEJOR PASARLO POR REFERENCIA(puntero) por tema de eficiencia
//    pthread_mutex_unlock(&mutexA);

    pthread_mutex_unlock(&mutex);


    close(*sockid);
    free(sockid);
    return NULL;
}

void *checkArraySize(void *arg) {
    int i;
    while (true) {
        pthread_mutex_lock(&mutex);

        if (clientAmmount >= STATUS_SIZE) {
//            pthread_mutex_lock(&mutexB);
            arrFull = 1;
            for (i = 0; i < STATUS_SIZE; ++i) {
                if ((clientStatus[i].cpu > 50) || (clientStatus[i].mem > 50)) {
                    if (appendToLogFile(clientStatus[i]) == -1) {
                        printf("No se pudo guardar en el archivo\n");
                        exit(-1);
                    }
                }
                emptyStatus(clientStatus[i]);
            }
//            pthread_mutex_lock(&mutexA);
            clientAmmount = 0;
//            pthread_mutex_unlock(&mutexA);
            arrFull = 0;
//            pthread_mutex_unlock(&mutexB);
        }
        pthread_mutex_unlock(&mutex);

//        usleep(500);
    }

    return NULL;
}

void emptyStatus(Status status) {
    strcpy(status.hostname, "\0");
    status.cpu = 0;
    status.mem = 0;
}

int appendToLogFile(Status status) {
    int errCode;
    FILE *fp;


    if ((fp = fopen("status.log", "a")) != NULL) {
        fprintf(fp, "25-11-2022;23:00;%s; cpu=% %d;memory=% %d\n", status.hostname, status.cpu, status.mem);
        fclose(fp);


    }
    else {
        printf("Error opening the file");
        errCode = -1;
    }

    return errCode;
}

