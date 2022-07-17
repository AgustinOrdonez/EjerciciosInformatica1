#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define TAMAÑO_MAXIMO 50

int desplazarLetras(char *, char *);

void desencriptarTexto(char *, char *, int);

int isANumber(char);

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
        /*desencriptarNumero(str2, str1);
        printf("String numeros desencriptados: %s\n", str1);*/
    }
    else {
        printf("No es posible encriptar el string\n");
    }

    return 0;
}


int desplazarLetras(char *source, char *dest) {
    int desplazamiento = getpid() % 25 + 1;
    int encriptedChar;
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

/**Returns 1 if true, 0 if false*/
int isANumber(char character) {
    return character >= '0' && character <= '9';
}

void encriptarNumeros(char *source, char *dest) {
    char encriptedChar;
    char firstNumber = 1;
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
        if (isANumber(*source) && (firstNumber || (!isANumber(*(source - 1)))) ||
            !isANumber(*source) && isANumber(*(source - 1))) {
            firstNumber = 0;
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
            source++;
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
    while (*str && !isEncriptable) {
        if (!(*str >= 'A' && *str <= 'Z' || *str >= 'a' && *str <= 'z' || isANumber(*str) || *str == ' ' ||
              *str == '\n')) {
            isEncriptable = -1;
        }
        str++;
    }
    return isEncriptable;
}

