#include <stdio.h>

#define ARR_SIZE 10

void init_arr(int *, int);

void load_arr(int *, int);

int size_arr(int *, int);

char has_value(int, int *);

char get_value(int, int *, int);

void print_arr(int *);

char union_arrs(int *, int *, int *, int);

int main() {

    int arr[ARR_SIZE];

    //init_arr(arr, 20);
    load_arr(arr, ARR_SIZE);
    print_arr(arr);
    printf("Size: %d\n", size_arr(arr, ARR_SIZE));
    printf("It has 5: %d\n", has_value(5, arr));
    return 0;
}

void init_arr(int *arr, int maxSize) {
    for (int i = 0; i < maxSize; ++i) {
        *(arr + i) = 0;
    }
}

void load_arr(int *arr, int maxSize) {

    for (int i = 0; i < maxSize; ++i) {
        printf("Ingrese valor\n");
        scanf("%d", arr + i);
        if (*(arr + i) == 0) {
            break;
        }
    }

}

/**Returns max size if array doesn't have  a 0*/
int size_arr(int *arr, int maxSize) {
    int i;
    int amount = maxSize;
    for (int i = 0; i < maxSize; ++i) {
        if (*arr == 0) {
            amount = i;
        }
        arr++;
    }
    return amount;
}

/**Returns 1 if it finds the value, 0 if it doesn't*/
char has_value(int value, int *arr) {

    char hasValue = 0;
    while (*arr) {
        if (*arr == value) {
            hasValue = 1;
        }
        arr++;
    }

    return hasValue;
}

/**Returns -1 if it could't fit the number*/
char get_value(int value, int *arr, int maxSize) {
    char error = -1;
    for (int i = 0; i < (maxSize - 1); ++i) {
        if (*(arr + i) == 0) {
            *(arr + i) = value;
            error = 0;
        }
    }
    return error;
}

void print_arr(int *arr) {
    while (*arr) {
        printf("%d\n", *arr);
    }
    arr++;
}


/**Returns -1 if any array could,t be fully copied*/
char union_arrs(int *destArray, int *sourceArray1, int *sourceArray2, int maxDestArraySize) {
    int i = 0;
    int error = 0;

    while (*sourceArray1 && i < maxDestArraySize) {
        *destArray = *sourceArray1;
        destArray++;
        sourceArray1++;
        i++;
    }

    while (*sourceArray2 && i < maxDestArraySize) {
        *destArray = *sourceArray2;
        destArray++;
        sourceArray2++;
        i++;
    }

    if (i == maxDestArraySize) {
        error = -1;
    }

    return error;
}

