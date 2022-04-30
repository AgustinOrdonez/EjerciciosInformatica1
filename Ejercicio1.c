#include<stdio.h>

int main(void) {

    float x;
    float result;
    
    printf("Ingrese x para f(x)=3x+2\n");
    scanf("%f", &x);
    result = 3 * x + 2;
    printf("f(x)=%.2f\n", result);
    return 0;
}

