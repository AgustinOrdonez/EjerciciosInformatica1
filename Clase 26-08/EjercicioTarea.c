#include <stdio.h>
#include <string.h>

#define MAX_MATS 100
#define MAX_MAT_NAME 32

typedef struct {
    char name[MAX_MAT_NAME];
    int stock;
    int id;
} Material;

int arrayContainsMaterial(Material [MAX_MATS], char *);

Material initMaterial(char *, int, int);

Material getMaterialFromName(char *, Material[MAX_MATS]);

int main() {
    Material material;
    Material materials[MAX_MATS];
    int currentStock;
    char currentName[MAX_MAT_NAME];
    int i = 0;
    int index = 0;


    while (i < MAX_MATS) {
        printf("Introduzca un material\n");
        scanf("%s", &currentName);//fgets(currentName, MAX_MAT_NAME, stdin);
        printf("Introduzca la cantidad a cargar\n");
        scanf("%d", &currentStock);
        if (arrayContainsMaterial(materials, currentName)) {
            material = getMaterialFromName(material.name, materials);
            materials[material.id].stock += currentStock;
        }
        else {
            material = initMaterial(currentName, currentStock, index);
            materials[index] = material;
            index++;
        }

        if (currentStock == 0) {
            i = MAX_MATS;
        }
        i++;
    }
    printf("Ingreso terminado");
    return 0;
}

/**Returns 1 if material is inside the array, 0 if it is not)*/
int arrayContainsMaterial(Material materials[MAX_MATS], char *materialsName) {
    int constainsMaterial = 0;
    int i;

    for (i = 0; i < MAX_MATS && !constainsMaterial; i++) {
        if (!strcmp(materials[i].name, materialsName)) {
            constainsMaterial = 1;
        }
    }
    return constainsMaterial;
}

Material initMaterial(char *name, int stock, int id) {
    Material material;
    strcpy(material.name, name);
    material.stock = stock;
    material.id = id;
    return material;
}


Material getMaterialFromName(char *materialsName, Material materials[MAX_MATS]) {
    Material material;
    int i;
    char found = 0;

    for (i = 0; i < MAX_MATS && !found; i++) {
        if (!strcmp(materials[i].name, materialsName)) {
            material = materials[i];
            found = 1;
        }
    }

    return material;
}
