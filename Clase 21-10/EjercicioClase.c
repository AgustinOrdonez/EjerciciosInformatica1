#include <stdio.h>

unsigned char paridad(unsigned char *, int);

void printBits(unsigned int, unsigned char);

int main() {
    unsigned char byteArray[3] = {0x90, 0xF0, 0x87};
    printf("Valor en hexa:%X\n", paridad(byteArray, 3));

}


unsigned char paridad(unsigned char *byteArray, int size) {
    int i;
    int j;
    unsigned char mask;
    unsigned int ammount;
    unsigned char paridad = 0;

    for (i = 0; i < 8; i++) {
        mask = 1 << i;
        ammount = 0;
        for (j = 0; j < size; j++) {
            if ((mask & byteArray[j])) {
                ammount++;
            }
        }
        if ((ammount % 2)) {
            paridad = paridad | mask;
        }

    }
    return paridad;
}



