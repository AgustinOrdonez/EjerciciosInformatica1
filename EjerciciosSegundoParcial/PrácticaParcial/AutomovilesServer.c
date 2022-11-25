#include <stdio.h>
#include <malloc.h>
#include <pthread.h>
#include "sock-lib.h"

#define MAX_PART_NAME 100
#define MAX_THREADS 20
#define MAX_COMMAND_SIZE 7

typedef struct st_part {
    unsigned int partNumber;
    char partName[MAX_PART_NAME];
    unsigned int partQuantity;
    unsigned int price;
} Part;


typedef struct st_node {
    struct st_node *next;
    Part *parteDeAutomovil;
} PartNode;

void insertElement(Part *, PartNode **);

int isPartEqual(Part *, Part *);

int isPartOnList(Part *, PartNode *);

void insertElementSafe(Part *, PartNode **);

int order(Part *, PartNode *);

Part *search(unsigned int partNumber);

int retrievePartsFromCsv(PartNode **listHead, char *filename);

int savePartsOnCsv(PartNode *listHead, char *filename);

void handleClose(int);

void removeEndOfLine(char *str);

void *manageClient(void *);

//Recursos compartido
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
unsigned int threadCount = 0;
PartNode *head = NULL;
char *saveFilename;


int main(int argc, char *args[]) {
    struct sockaddr_in myAddr;
    int socketFd;
    int *socketId;
    FILE *fp;
    pthread_t threadIds[MAX_THREADS];

    saveFilename = args[1];

    if (argc == 2) {
        //Llenado de la lista, se crea el csv si no lo encuentra
        if ((retrievePartsFromCsv(&head, saveFilename) == -1)) {
            fp = fopen(saveFilename, "w");
            fprintf(fp, "partNumber,partName,partQuantity,price\n");
            fclose(fp);
            printf("Archivo generado");
        }

        //Para guardar uso control+c
        signal(SIGINT, handleClose);

        if ((socketFd = abrirConeccion(&myAddr)) == -1) {
            perror("No se pudo abrir el servidor");
            exit(-1);
        }
        else {
            printf("Server iniciado\n");
        }


        while (1) {
            //Para no tener un segmentation fault
            if (threadCount < MAX_THREADS) {
                //Malloc para que no sea suceptible a cambios por multithreading
                socketId = malloc(sizeof(int));
                *socketId = aceptarPedidos(socketFd);

                pthread_mutex_lock(&mutex);
                pthread_create(&threadIds[threadCount++], NULL, manageClient, socketId);
                pthread_mutex_unlock(&mutex);
            }
            else {
                sleep(1);
            }
        }


    }
    else {
        printf("Usage: ./serverAutopartes <archivoCsv>\n");
    }


    return 0;
}


void insertElement(Part *element, PartNode **head) {
    PartNode *node = malloc(sizeof(PartNode));

    node->next = *head;
    node->parteDeAutomovil = element;
    *head = node;
}


/**Compares if two parts are the same based on partNumber. Returns 0 if false*/
int isPartEqual(Part *a, Part *b) {
    return (a->partNumber) == (b->partNumber);
}

/**Returns 0 if false based on partNumber*/
int isPartOnList(Part *element, PartNode *listHead) {
    int isPartOnList = 0;
    int found = 0;

    while (((listHead) != NULL) && !found) {
        if (isPartEqual(element, listHead->parteDeAutomovil)) {
            isPartOnList = 1;
            found = 1;
        }
        listHead = listHead->next;
    }
    return isPartOnList;
}

void insertElementSafe(Part *element, PartNode **head) {
    if (!isPartOnList(element, *head)) {
        insertElement(element, head);
    }
}

/**Decreaces stock by 1 when possible, returns -1 if stock is already zero*/
int order(Part *element, PartNode *listHead) {
    int errCode;

    while ((listHead) != NULL) {
        if (isPartEqual(element, listHead->parteDeAutomovil)) {
            if (listHead->parteDeAutomovil->partQuantity != 0) {
                pthread_mutex_lock(&mutex);
                listHead->parteDeAutomovil->partQuantity--;
                pthread_mutex_unlock(&mutex);
            }
            else {
                errCode = -1;
            }
        }
        listHead = listHead->next;
    }

    return errCode;
}

/**Returns NULL if it is not in the list*/
Part *search(unsigned int partNumber) {
    int search = 1;
    Part *foundElement = malloc(sizeof(Part));
    PartNode *initHead = malloc(sizeof(PartNode));
    foundElement->partNumber = partNumber;

    //Me guardo el inicio para no perder la referencia
    initHead = head;

    while ((head != NULL) && search) {

        if (isPartEqual(foundElement, head->parteDeAutomovil)) {
            strcpy(foundElement->partName, head->parteDeAutomovil->partName);
            foundElement->partQuantity = head->parteDeAutomovil->partQuantity;
            foundElement->price = head->parteDeAutomovil->price;

            //Variable de salida
            search = 0;
        }
        head = head->next;
    }
    head = initHead;
    if (search == 1) {
        foundElement = NULL;
    }

    return foundElement;
}

/**Returns -1 if falied*/
int retrievePartsFromCsv(PartNode **listHead, char *filename) {
    FILE *fp;
    char buff[500];
    char *token;
    Part *element = malloc(
            sizeof(Part));//Esta es la función en la que si este puntero declaro como Part(no puntero) me deja setear los valores pero por algún motivo se pierden los valores con el tiempo
    int errCode;

    if ((fp = fopen(filename, "r")) != NULL) {
        //Ignoro la línea de títulos
        fgets(buff, sizeof buff, fp);

        while ((fgets(buff, sizeof buff, fp)) != NULL) {//File has the same order as PartStructure

            removeEndOfLine(buff);

            token = strtok(buff, ",");

            if (token != NULL) {
                element->partNumber = atoi(token);
            }
            else {
                errCode = -1;
            }
            token = strtok(NULL, ",");

            if (token != NULL) {
                strcpy(element->partName, token);
            }
            else {
                errCode = -1;
            }

            token = strtok(NULL, ",");
            if (token != NULL) {
                element->partQuantity = atoi(token);
            }
            else {
                errCode = -1;
            }

            token = strtok(NULL, ",");
            if (token != NULL) {
                element->price = atoi(token);
            }
            else {
                errCode = -1;
            }

            insertElementSafe(element, listHead);

        }
        fclose(fp);


    }
    else {
        errCode = -1;
    }

    return errCode;
}

void removeEndOfLine(char *str) {//Esto solo saca el \n si está al final del string
    if (str[strlen(str)] == '\n') {
        str[strlen(str)] = 0;
    }
}

int savePartsOnCsv(PartNode *listHead, char *filename) {
    FILE *fp;

    fp = fopen(filename, "w");

    //Meto la cabecera
    fprintf(fp, "partNumber,partName,partQuantity,price\n");

    while (listHead != NULL) {
        fprintf(fp, "%d,%s,%u,%u\n", listHead->parteDeAutomovil->partNumber, listHead->parteDeAutomovil->partName,
                listHead->parteDeAutomovil->partQuantity, listHead->parteDeAutomovil->price);
        listHead = listHead->next;
    }
    fclose(fp);

    return 0;
}

void handleClose(int signal) {
    printf("Saving data to %s\n", saveFilename);
    savePartsOnCsv(head, saveFilename);
    printf("Saved!\n");
    exit(0);
}

void *manageClient(void *arg) {
    int *socketId = (int *) arg;
    char command[MAX_COMMAND_SIZE];
    unsigned int partNumber;
    Part *element = malloc(sizeof(Part));
    char state;

    read(*socketId, command, sizeof(command));

    if (!strcmp(command, "order")) {
        read(*socketId, &partNumber, sizeof(partNumber));
        partNumber = ntohl(partNumber);

        element->partNumber = partNumber;

        //b simboliza bad y w simboliza well
        if (order(element, head) == -1) {
            state = 'b';
        }
        else {
            state = 'w';
        }
        write(*socketId, &state, 1);

    }
    else if (!strcmp(command, "search")) {
        read(*socketId, &partNumber, sizeof(partNumber));
        partNumber = ntohl(partNumber);

        if ((element = search(partNumber))) {
            state = 'w';
            write(*socketId, &state, 1);
            //En search mando los datos después del estado, en el resto no requiero enviar datos
            write(*socketId, element, sizeof(Part));
        }
        else {
            state = 'b';
            write(*socketId, &state, 1);
        }
    }
    else {
        //En caso de que el comando no esté se envía x
        state = 'x';
        write(*socketId, &state, 1);
    }

    close(*socketId);
    free(arg);

    free(element);

    pthread_mutex_lock(&mutex);
    threadCount--;
    pthread_mutex_unlock(&mutex);

    return NULL;

}



