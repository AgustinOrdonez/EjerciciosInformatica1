#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define TAMAÑO_MAXIMO 50

int desplazarLetras(char *, char *);

void desencriptarTexto(char *, char *, int);

void encriptarNumeros(char *, char *);

void desencriptarNumero(char *, char *);

int esEncriptable(char *);

int main(int argc, char *argv[]) {
    char str1[TAMAÑO_MAXIMO];
    char str2[TAMAÑO_MAXIMO];
    //char str3[TAMAÑO_MAXIMO];
    //int desplazamiento;

    printf("Ingrese un string a encriptar\n");
    fgets(str1, TAMAÑO_MAXIMO, stdin);
    if (!esEncriptable(str1)) {
        desplazarLetras(str1, str1);
        encriptarNumeros(str1, str2);
        printf("String encriptado: %s\n", str2);
    }
    else {
        printf("No es posible encriptar el string\n");
    }

/*  printf("Es encriptable : %d\n", esEncriptable(str1));
    encriptarNumeros(str2, str2);
    puts(str2);
    printf("Número de desplazamientos:%d\n", desplazamiento);
    desencriptarTexto(str2, str3, desplazamiento);
    desencriptarNumero(str3, str3);
    printf("String desencriptado : %s\n", str3);*/
    return 0;
}


int desplazarLetras(char *source, char *dest) {
    int desplazamiento = getpid() % 25 + 1;
    char encriptedChar;
    while (*source) {
        encriptedChar = *source;
        if (*source >= 'A' && *source <= 'Z') {
            encriptedChar = *source + desplazamiento;
            if (encriptedChar > 'Z') {
                encriptedChar = 'A' + encriptedChar - 'Z' - 1;
            }
        }
        if (*source >= 'a' && *source <= 'z') {
            encriptedChar = *source + desplazamiento;
            if (encriptedChar > 'z') {
                encriptedChar = 'a' + encriptedChar - 'z' - 1;
            }
        }
        *dest = encriptedChar;
        source++;
        dest++;
    }
    *dest = 0;

    return desplazamiento;
}

void desencriptarTexto(char *source, char *dest, int desplazamiento) {
    char unEncriptedChar;
    while (*source) {
        unEncriptedChar = *source;
        if (*source >= 'A' && *source <= 'Z') {
            unEncriptedChar = *source - desplazamiento;
            if (unEncriptedChar < 'A') {
                unEncriptedChar = 'Z' + unEncriptedChar - 'A' + 1;
            }
        }
        *dest = unEncriptedChar;
        source++;
        dest++;
    }
    *dest = 0;
}

void encriptarNumeros(char *source, char *dest) {
    char encriptedChar;
    int i = 1;
    while (*source) {
        encriptedChar = *source;
        switch (*source) {
            case '0':
            case '1':
            case '2':
                encriptedChar = '$' + *source - '0';
                break;
            case '3':
                encriptedChar = '*';
                break;
            case '4':
                encriptedChar = '@';
                break;
            case '5':
                encriptedChar = '!';
                break;
            case '6':
                encriptedChar = '+';
                break;
            case '7':
                encriptedChar = '=';
                break;
            case '8':
                encriptedChar = '(';
                break;
            case '9':
                encriptedChar = ')';
                break;
        }
        if (*(source) >= '0' && *(source) <= '9' && (!(*(source - 1) >= '0' && *(source - 1) <= '9') || i == 1) ||
            !(*(source) >= '0' && *(source) <= '9') && (*(source - 1) >= '0' && *(source - 1) <= '9')) {
            for (i = 0; i < strlen(source); ++i) {
                *(dest + i + 1) = *(source + i);
            }
            *dest = '#';
            dest++;
        }
        *dest = encriptedChar;
        source++;
        dest++;
    }
    *dest = 0;
}

void desencriptarNumero(char *source, char *dest) {
    char encriptedChar;
    int i;
    while (*source) {
        if (*source == '#') {
            for (i = 0; i < strlen(source); ++i) {
                *(dest + i) = *(source + i + 1);
            }
            *source++;
        }
        encriptedChar = *source;
        switch (*source) {
            case '$':
            case '%':
            case '&':
                encriptedChar = '0' + *source - '$';
                break;
            case '*':
                encriptedChar = '3';
                break;
            case '@':
                encriptedChar = '4';
                break;
            case '!':
                encriptedChar = '5';
                break;
            case '+':
                encriptedChar = '6';
                break;
            case '=':
                encriptedChar = '7';
                break;
            case '(':
                encriptedChar = '8';
                break;
            case ')':
                encriptedChar = '9';
                break;
        }
        *dest = encriptedChar;

        source++;
        dest++;
    }
    *dest = 0;
}

/**Returns 0 if true, -1 if not*/
int esEncriptable(char *str) {
    int isEncriptable = 0;
    while (!*str && isEncriptable) {
        if (!(*str >= 'A' && *str <= 'Z' || *str >= 'a' && *str <= 'z' || *str >= '0' && *str <= '9' || *str == ' ')) {
            isEncriptable = -1;
        }
        str++;
    }
    return isEncriptable;
}

