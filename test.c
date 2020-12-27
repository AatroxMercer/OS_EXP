#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>


int main(int argc, char *argv[]) {
    FILE* fd = fopen("/home/sb/desktop/workspace/os/exp_3/device_driver/test.buf", "rt+");
    char buf[10];
    int a;
    fscanf(fd, "%d", &a);
    printf("%d", ftell(fd));
    rewind(fd);
    fprintf(fd, "%5d", a+1);
    fclose(fd);
}