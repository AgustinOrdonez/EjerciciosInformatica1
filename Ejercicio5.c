#include<stdio.h>

int main(void) {

    int superficie;
    float costo;
    float total;

    printf("Ingrese la superficie en metros cuadrados(número entero)\n");
    scanf("%d", &superficie);
    printf("Ingrese el costo por metro cuadrado(En pesos)\n");
    scanf("%f", &costo);

    if (!(superficie > 1 && superficie < 100)) {
        printf("La superficie debe estar entre 1 y 100\n");
    }
    if (!(costo >= 100 && costo <= 5000)) {
        printf("El costo por metro cuadrado debe estar entre 100 y 5000 inclusive\n");
    }
    if (superficie > 1 && superficie < 100 && costo >= 100 && costo <= 5000) {//Querría tener bools o whiles :(
        total = superficie * costo * 0.95F;
        printf("El costo total es: %.2f\n", total);
    }
    return 0;
}