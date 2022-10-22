#include <stdio.h>

int (*calc)(int, int);

int suma(int, int);

int resta(int, int);

int multip(int, int);

int div(int, int);


int main() {
    calc = suma;
    printf("La suma es %d\n", calc(1, 2));

}

int suma(int a, int b) {
    return a + b;
}

int resta(int a, int b) {
    return a - b;
}

int multip(int a, int b) {
    return a * b;
}

int div(int a, int b) {
    return a / b;
}