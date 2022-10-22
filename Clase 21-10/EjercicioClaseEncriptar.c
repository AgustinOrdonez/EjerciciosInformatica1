#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd;
    char *buf;
    int a = 1;
    int i = 0;
    int size = 0;
    char *encriptedFile;
    if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
        buf = (char *) malloc(50);
        while (a) {
            a = read(fd, buf + i, 1);
            *(buf + i) = ~*(buf + i);
            i++;
            size++;
        }
        close(fd);
        encriptedFile = (char *) malloc(strlen(argv[1]) + 8);
        strcpy(encriptedFile, "crypto_");
        strcat(encriptedFile, argv[1]);
        fd = open(encriptedFile, O_RDWR | O_CREAT, 0666);

        write(fd, buf, size - 1);
        close(fd);
    }
}