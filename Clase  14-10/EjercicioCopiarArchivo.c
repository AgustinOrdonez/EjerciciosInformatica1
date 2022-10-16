#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>

int main() {
    int fd;
    char *buf;
    int a = 2133;//inicializo para testear
    fd = open("./original", O_RDONLY);
    a = lseek(fd, 0, SEEK_END);//Subóptimo, habría que ir leyendo de a pedazos
    lseek(fd, 0, SEEK_SET);
    buf = (char *) malloc(a);
    a = read(fd, buf, a);
    close(fd);
    fd = open("./copia", O_RDWR | O_CREAT, 0666);
    write(fd, buf, a);
    close(fd);
}