#include <stdio.h>
#include "sock-lib.h"

#define MAX_PART_NAME 100
#define MAX_COMMAND_SIZE 7

typedef struct st_part {
    unsigned int partNumber;
    char partName[MAX_PART_NAME];
    unsigned int partQuantity;
    unsigned int price;
} Part;

int main(int argc, char *args[]) {

    int socketFd;
    char command[MAX_COMMAND_SIZE];
    char response;
    Part *foundElement = malloc(sizeof(Part));
    unsigned int partNumber;

    if (argc == 4) {
        socketFd = conectar(2, args);

        strcpy(command, args[2]);

        write(socketFd, command, sizeof(command));

        partNumber = atoi(args[3]);
        partNumber = htonl(partNumber);
        if (!strcmp(command, "order")) {

            write(socketFd, &partNumber, sizeof(partNumber));
            read(socketFd, &response, sizeof(char));

            if (response == 'w') {
                printf("Operación realizada con éxito\n");
            }
            else {
                printf("Operación fallida\n");
            }

        }
        else if (!strcmp(command, "search")) {
            write(socketFd, &partNumber, sizeof(partNumber));
            read(socketFd, &response, sizeof(char));

            if (response == 'w') {
                read(socketFd, foundElement, sizeof(Part));
                printf("El elemento que pidió es el siguiente\n"
                       "Número de parte: %u\n"
                       "Nombre de parte: %s\n"
                       "Cantidad en stock: %u\n"
                       "Precio: %u\n", foundElement->partNumber, foundElement->partName, foundElement->partQuantity,
                       foundElement->price);
                free(foundElement);
            }
            else {
                printf("El elemento que pidió no se encuentra en stock\n");
            }
        }
        else {
            printf("Comando equivocado\n"
                   "Opciones disponibles:\n"
                   "    -search     (Dada un número de parte lista todos los datos del artículo)\n"
                   "    -order      (Dado un número de parte baja en 1 la cantidad de stock)\n");

        }
        close(socketFd);

    }
    else {
        printf("Usage: ./clientAutopartes <hostname> <command> <argument>\n");
    }


    return 0;
}