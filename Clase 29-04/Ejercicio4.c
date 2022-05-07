#include<stdio.h>

int main(void) {

    float nota1;
    float nota2;
    float nota3;
    float promedio;

    printf("Con este programa podrá calcular el promedio de 3 notas.\nLa aprobación se alcanza con notas mayores a 3.5\n");
    printf("Ingrese la primera nota\n");
    scanf("%f", &nota1);
    printf("Ingrese la segunda nota\n");
    scanf("%f", &nota2);
    printf("Ingrese la tercera nota\n");
    scanf("%f", &nota3);

    if (nota1 >= 1 && nota1 <= 7 && nota2 >= 1 && nota2 <= 7 && nota3 >= 1 && nota3 <= 7) {
        promedio = (nota1 + nota2 + nota3) / 3;
        printf("La nota 1 fue:   %.2f\n", nota1);
        printf("La nota 2 fue:   %.2f\n", nota2);
        printf("La nota 3 fue:   %.2f\n", nota3);
        printf("El promedio fue: %.2f\n", promedio);
        printf("Situación final: %s\n", (promedio > 3.5F ? "APROBADO" : "DESAPROBADO"));
    }
    else {
        printf("Las notas deben estar entre 1 y 7");
    }
    return 0;
}
