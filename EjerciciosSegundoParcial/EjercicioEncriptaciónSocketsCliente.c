#include <stdio.h>
#include "sock-lib.h"

int main(int argc, char *args[]) {
    int socketFd;
    char *buff;
    unsigned int totalBytes;
    unsigned int buffLength;

    if (argc == 3) {
        socketFd = conectar(2, args);

        buffLength = htonl(strlen(args[2]) + 1);


        /*Escribiendo mensaje*/
        write(socketFd, &buffLength, sizeof(int));
        write(socketFd, args[2], strlen(args[2]) + 1);


        /*Leyendo el mensaje codificado*/
        read(socketFd, &totalBytes, sizeof(int));
        totalBytes = ntohl(totalBytes);

        buff = malloc(totalBytes);
        read(socketFd, buff, totalBytes);
        printf("El mensaje encriptado es: %s\n", buff);

    }
    else {
        printf("Usage:\n ./client hostname \" Message Here\"");
    }

    return 0;
}