#include <stdio.h>

int myStrLen(char *);

void strToUpperCase(char *);

int main() {
    char arr[10] = "GASDaa";
    strToUpperCase(arr);
    printf("%s", arr);
}

int myStrLen(char *array) {
    int count = 0;
    char letter = *(array);
    while (letter != 0) {
        count++;
        letter = *(array + count);
    }
    return count;
}

void strToUpperCase(char *str) {
    int i = 0;
    char letter = *(str);
    while (letter != 0) {
        if (letter > 96 && letter < 123) {
            *(str + i) = letter - 32;
        }
        i++;
        letter = *(str + i);
    }
}