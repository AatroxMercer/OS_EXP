#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>

int main() {
    struct timeval tv;
    syscall(78, &tv, NULL);
    printf("tv_sec:%d\n", tv.tv_sec);
    printf("tv_usec:%d\n", tv.tv_usec);
    return 0;
}
