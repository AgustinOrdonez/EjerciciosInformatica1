#include <stdbool.h>
#include "sock-lib.h"
#include <pthread.h>
#include <string.h>

#define MAX_THREADS 100


void *routine(void *);

void encriptarMensaje(char *buff);

int openedThreads = 0;

int main() {

    int socketFd;
    struct sockaddr_in myAddr;
    int *socketId;
    pthread_t threadIds[MAX_THREADS];

    if ((socketFd = abrirConeccion(&myAddr)) == -1) {
        perror("No se pudo abrir el servidor");
        exit(-1);
    }
    else {
        printf("Servidor iniciado\n");
    }
    while (true) {
        socketId = malloc(sizeof(int));
        *socketId = aceptarPedidos(socketFd);

        if (pthread_create(&threadIds[openedThreads], NULL, routine, (void *) socketId) != 0) {
            pthread_detach(threadIds[openedThreads]);
            exit(-2);
        }
    }

    return 0;
}


void *routine(void *arg) {
    int *fd = (int *) arg;
    char *buff;
    unsigned int messageLength;

    if (read(*fd, &messageLength, sizeof(messageLength)) == -1) {
        perror("NO SE PUDO LEER EL TAMAÑO");
        exit(-3);
    }
    messageLength = ntohl(messageLength);


    buff = malloc(messageLength);
    if (read(*fd, buff, messageLength) == -1) {
        perror("NO SE PUDO LEER");
        exit(-3);
    }

    encriptarMensaje(buff);
    printf("Mensaje encriptado como: %s\n", buff);

    messageLength = htonl(messageLength);
    write(*fd, &messageLength, sizeof(messageLength));

    write(*fd, buff, messageLength);

    printf("Mensaje Enviado");
    close(*fd);

    free(arg);
    free(buff);
    return NULL;
}

void encriptarMensaje(char *buff) {
    for (int i = 0; i < strlen(buff); ++i) {
        buff[i] = (buff[i] & (~0b00000001));
    }
}
