#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int a = 0;

int main() {
        int child_status;
        pid_t pid, pid_self;
        /*
                fork:
                        return 0 for child process
                        return child pid for parent process
        */
        pid = fork();
        a++;
        printf("%d", a);

        if (pid < 0) {
                // error occured
                fprintf(stderr, "Fork Failed\n");
                return 1;
        } else if (pid == 0) {
                execlp("./hello_openEuler.out",  NULL);
                // running in child process
                a += 2;
                printf("%d", a);
                pid_self = getpid();
                printf("child: pid_self = %d\n", pid_self);
                printf("child: pid = %d\n", pid);
        } else {
                // running in parent process
                a += 4;
                printf("%d", a);
                pid_self = getpid();
                printf("parent: pid_slef = %d\n", pid_self);
                printf("parent: pid = %d\n", pid);
                if (wait(&child_status) == pid)
                        return 0;
                else
                        return 1;
        }

        a += 100;

        return 0;
}