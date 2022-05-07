#include<stdio.h>

int main(void) {

    float base;
    float altura;
    float area;

    printf("Con este programa podrá calcular el área de un triángulo\n");
    printf("Ingrese el valor de la base\n");
    scanf("%f", &base);
    printf("Ingrese el valor de la altura\n");
    scanf("%f", &altura);
    if (base > 0 && altura > 0) {
        area = base * altura / 2;
        printf("El área del triángulo es: %.2f\n", area);
    }
    else {
        printf("El triángulo indicado tiene lados iguales o menores a 0\n");
    }
    return 0;
}
