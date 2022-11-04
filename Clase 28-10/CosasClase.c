#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


void signalHandler(int);


int main() {
    signal(31, signalHandler);
//    while (1) {
//        sleep(1);
//    }
    pause();
    return 0;
}


void signalHandler(int sig) {
    printf("COSO");
//    exit(0);
}
