#include <stdio.h>
#include <pthread.h>
#include <dirent.h>
#include <malloc.h>
#include <sys/stat.h>


#define MAXTHREADS 100

void writeFileContentIntoBuffer(FILE *, char **);

void writeBufferIntoFile(char *, FILE *);

int removeDoubleWhiteSpaces(char *);

void copyFileToDirectory(FILE *, char *, char *);

void *copyFile(void *);

int main(int argc, char *args[]) {
    DIR *dir;
    struct dirent *dirEntry;
    int movedFiles = 0;
    char *fileNameWithPath;
    pthread_t threadIds[MAXTHREADS];
    int i;
    int *returnValue;
    int *removedSpaces;

    if (argc == 2) {
        dir = opendir(args[1]);
        if (dir) {
            while ((dirEntry = readdir(dir)) != NULL) {

                if (strcmp(".", dirEntry->d_name) && strcmp("..", dirEntry->d_name)) {
                    fileNameWithPath = malloc(strlen(args[1]) + strlen(dirEntry->d_name) + 2);
                    if (!fileNameWithPath) {
                        exit(-1);
                    }
                    strcpy(fileNameWithPath, args[1]);
                    strcat(fileNameWithPath, "/");
                    strcat(fileNameWithPath, dirEntry->d_name);

                    pthread_create(&threadIds[movedFiles], NULL, copyFile, fileNameWithPath);

                    movedFiles++;
                }
            }

            closedir(dir);

            returnValue = malloc(4);
            removedSpaces = malloc(sizeof(int) * movedFiles);
            for (i = 0; i < movedFiles; ++i) {
                pthread_join(threadIds[i], (void **) &returnValue);
                *(removedSpaces + i) = *returnValue;
            }

            printf("Arhchivos movidos:%d\n", movedFiles);//Meterle esto por thread
            for (i = 0; i < movedFiles; i++) {
                printf("En el archivo %d: se eliminaron: %d espacios en blanco\n",i,removedSpaces[i]);
            }


        }

    }
    else {
        printf("Cantidad de argumentos errónea\n");
    }

}

/**NEEDS an already opened file, if buffer is empty assign it NULL*/
void writeFileContentIntoBuffer(FILE *fp, char **buffer) {
    int i = 0;
    int buffSize = 0;
    __int8 bytesRead = 10;
    int realSize = 0;

    fseek(fp, 0, SEEK_SET);
    while (bytesRead == 10) {//malloc al buff
        *buffer = realloc(*buffer, buffSize += 10);
        if (!buffer) {
            exit(-1);
        }

        bytesRead = fread((*buffer) + i, 1, 10, fp);
        realSize += bytesRead;
        i += 10;
    }
    (*buffer)[realSize] = 0;


}

/**NEEDS an already opened file*/


void writeBufferIntoFile(char *buffer, FILE *fp) {
    int i;
    int a;

//    fseek(fp, 0, SEEK_SET);
    for (i = 0; i < strlen(buffer); i++) {
        a = fwrite(buffer + i, 1, 1, fp);
    }
}


/**Returns ammout of blank spaces removed*/
int removeDoubleWhiteSpaces(char *str) {
    int j;
    int ammountRemoved = 0;

    while (*str) {
        while (*str == 32 && *(str + 1) == 32) {
            j = 0;
            while (*(str + j)) {
                *(str + j) = *(str + j + 1);
                j++;
            }
            ammountRemoved++;
        }
        str++;
    }
    return ammountRemoved;
}

void copyFileToDirectory(FILE *fp, char *filename, char *outDir) {
    char *filenameWithPath = malloc(strlen(outDir) + 1 + strlen(filename) + 1);

    int i;
    char *buffer = NULL;
    FILE *destFp;

    writeFileContentIntoBuffer(fp, &buffer);

    strcpy(filenameWithPath, outDir);
    strcat(filenameWithPath, "/");
    strcat(filenameWithPath, filename);

    struct stat st = {0};

    if (stat(outDir, &st) == -1) {
        mkdir(outDir);
    }
    destFp = fopen(filenameWithPath, "w");
    if (!destFp) {
        printf("NO SE PUDO ABRIR EL ARCHIVO\n");
    }
    else {
        writeBufferIntoFile(buffer, destFp);
        fclose(destFp);
    }
    free(buffer);

}

void *copyFile(void *fullFilename) {
    FILE *fp;
    char *buff;
    int *blankSpacesRemoved = malloc(sizeof(int));


    fp = fopen(fullFilename, "r");

    if (!fp) {
        printf("EL ARCHIVO NO SE ABRIÓ AL PRINCIPIO\n");
    }

    buff = NULL;
    writeFileContentIntoBuffer(fp, &buff);
    *blankSpacesRemoved = removeDoubleWhiteSpaces(buff);

    fclose(fp);

    fp = fopen(fullFilename, "w+");

    writeBufferIntoFile(buff, fp);

    copyFileToDirectory(fp, strrchr(fullFilename, '/') + 1, "./output");
    fclose(fp);

    free(buff);

    remove(fullFilename);
    return blankSpacesRemoved;
}
