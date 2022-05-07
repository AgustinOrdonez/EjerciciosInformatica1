#include <stdio.h>

int main(void) {

    int num1;
    int suma = 0;
    int mayor = -1;
    int menor = -1;
    char validation = 1;

    while (validation) {
        printf("Ingrese un valor entero\n");
        scanf("%d", &num1);
        if (num1 >= 0) {
            suma += num1;
            printf("El valor acumulado es: %d\n", suma);

            if (num1 > mayor) {
                mayor = num1;
            }
            if (num1 < menor || menor == -1) {
                menor = num1;
            }
            printf("Para dejar de intoducir números ingrese un negativo\n");
        }
        else {
            printf("Ingreso de números finalizado\n");
            validation = 0;
        }
    }
    if (menor != -1) {
        printf("El menor número ingresado fue el %d\nEl mayor número ingresado fue el %d\n", menor, mayor);
    }
    else {
        printf("No hay números ingresados");
    }

}