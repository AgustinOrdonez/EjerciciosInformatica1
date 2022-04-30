#include<stdio.h>

int main(void) {

    float nota;

    printf("Ingrese la nota a evaluar\n");
    scanf("%f", &nota);
    if (nota > 0 && nota <= 10) {
        if (nota >= 6) {
            printf("APROBADO\n");
        }
        else {
            printf("DESAPROBADO\n");
        }
    }
    else {
        printf("Nota inválida\n");
    }
    return 0;
}