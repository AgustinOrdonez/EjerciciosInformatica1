#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8010    /* El puerto donde se conectará, servidor */
#define BACKLOG 10    /* Tamaño de la cola de conexiones recibidas */

int conectar(int, char **);

int abrirConeccion(struct sockaddr_in *my_addr); /* Función que crea la conexión*/

int aceptarPedidos(int);    /* Función que acepta una conexión entrante*/
