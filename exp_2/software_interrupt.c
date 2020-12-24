#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int p_flag, wait_flag;
void stop();

int main() {
    int pid1, pid2;

    // create child_1
    while((pid1 = fork()) == -1);
    // parent
    if(pid1 > 0) {
        // create child_2
        while((pid2 = fork()) == -1);
        // parent
        if(pid2 > 0) {
            // wait start
            // pause();
            wait_flag = 1;
            p_flag = 3;

            printf("kill child 1\n");
            kill(pid1, 16);
            printf("kill child 2\n");
            kill(pid2, 17);

            wait(0);
            wait(0);
            // pause();
            printf("Parent process ends !!\n");
            exit(0);
        }
        // child_2
        else {
            wait_flag = 1;
            p_flag = 2;
            signal(17, stop);
            pause();
            printf("Child process 2 is killed by parent !!\n");
            exit(0);
        }
    }
    // child_1
    else {
        wait_flag = 1;
        p_flag = 1;
        signal(16, stop);
        pause();
        printf("Child process 1 is killed by parent !!\n");
        exit(0);
    }
    return 0;
}

void stop() {
    printf("software_interrupt %d\n", p_flag);
}