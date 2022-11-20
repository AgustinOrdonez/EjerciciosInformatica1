#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#define MAX_NAME_LENGTH 20
#define MAX_CSV_ELEMENT_LENGTH MAX_NAME_LENGTH+10*3
typedef struct {
    int codigoProducto;
    char nombre[MAX_NAME_LENGTH];
    int cantidadStock;
    int codigoPostal;
} Producto;

int cargarProductos(Producto **, unsigned int);

int filtrarProductos(const Producto *, int, int *, int, const char *);

int añadirProductoACsv(const Producto *producto, const char *nombreDeArchivo);

char *transformarProductoEnElementoCsv(const Producto *producto);

void goneBad(int);
void goneWell(int);

int main(int argc, char *args[]) {

    bool continuar = true;
    char option;
    Producto *productos = NULL;
    unsigned int cantidadDeProductos = 0;
    pid_t id;
    int i;
    int *codigosPostales;
    int err;

    while (continuar) {
        printf("Ingrese valores según corresponda\n");
        printf("0- Si desea salir del menu\n");
        printf("1- Si desea añadir productos\n");
        scanf("%d", &option);
        if (option == 1) {
            productos = realloc(productos, ++cantidadDeProductos);
            cargarProductos(&productos, cantidadDeProductos);
        }
        else if (!option) {
            continuar = false;
        }
        else {
            printf("Opción errónea\n");
        }
    }
    if (argc > 1) {
        codigosPostales = malloc(sizeof(int) * (argc - 1));

        for (i = 0; i < argc; ++i) {
            codigosPostales[i] = atoi(args[i]);
        }
        id = fork();
        signal(40,goneBad);
        signal(41,goneWell);
        if (!id) {
            err=filtrarProductos(productos, cantidadDeProductos, codigosPostales, argc - 1,
                             "datos_filtrados.csv");
            if (err == -1) {
                kill(getppid(), 40);
            }
            else {
                kill(getppid(), 41);
            }

        }
        else {
            wait(id);
        }
    }
    else {
        printf("Ingrese códigos postales para filtrar\n");
    }


}

/**Returns -1 in case of error*/
int cargarProductos(Producto **arrayProducto, unsigned int cantidadNueva) {
    int err = 0;
    int temp;

    printf("Ingrese el código del producto\n");
    temp = scanf("%d", &((*arrayProducto) + cantidadNueva - 1)->codigoProducto);
    if (temp != 1) {
        err = -1;
    }
    printf("Ingrese el nombre del producto\n");
    temp = scanf("%s", &((*arrayProducto) + cantidadNueva - 1)->nombre);
    if (temp != 1) {
        err = -1;
    }
    printf("Ingrese la cantida de stock del producto\n");
    temp = scanf("%d", &((*arrayProducto) + cantidadNueva - 1)->cantidadStock);
    if (temp != 1) {
        err = -1;
    }
    printf("Ingrese el código postal del producto\n");
    temp = scanf("%d", &((*arrayProducto) + cantidadNueva - 1)->codigoPostal);
    if (temp != 1) {
        err = -1;
    }

    return err;
}


/**Returns -1 in case of error*/
int filtrarProductos(const Producto *arrProductos, int cantidadProductos, int *codigosPostales,
                     int cantidadDeCodigosPostales,
                     const char *archivoDeDestino) {
    int i;
    int j;
    int err;

    for (i = 0; i < cantidadProductos; i++) {
        for (j = 0; j < cantidadDeCodigosPostales; ++j) {
            if (arrProductos[i].codigoPostal == codigosPostales[j]) {
                err = añadirProductoACsv(&arrProductos[i], archivoDeDestino);
            }
        }

    }

    return err;
}

int añadirProductoACsv(const Producto *producto, const char *nombreDeArchivo) {
    int fd;
    char buff[MAX_CSV_ELEMENT_LENGTH];
    unsigned char i;
    int err;

    fd = open(nombreDeArchivo, O_CREAT | O_WRONLY);
    lseek(fd, 0, SEEK_END);
    strcpy(buff, transformarProductoEnElementoCsv(producto));
    for (i = 0; i < strlen(buff); i++) {
        write(fd, buff[i], 1);
    }
    err = close(fd);
    return err;
}

char *transformarProductoEnElementoCsv(const Producto *producto) {
    char productoParseado[MAX_CSV_ELEMENT_LENGTH];

    sprintf(productoParseado, "CP%dAR,%d,%s,%d\n", producto->codigoPostal, producto->codigoProducto,
            producto->cantidadStock);

    return productoParseado;
}

void goneBad(int sig) {
    printf("Went BAD\n");
}
void goneWell(int sig) {
    printf("Went WELL\n");
}
