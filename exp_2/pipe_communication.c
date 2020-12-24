#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <signal.h>
#include  <sys/wait.h>
#include  <sys/types.h>

int main(void) {
    int pipefd[2];
    int pid1, pid2;
    char OutPipe[100], InPipe[100];  	     // 定义两个字符数组

    // create pipe
    pipe(pipefd);

    // create child 1
    while((pid1 = fork( )) == -1);
    // child 1
    if(pid1 == 0) {
        // load data
        sprintf(OutPipe,"\n Child process 1 is sending message!\n");
        // lock out pipe
        lockf(pipefd[1], 1, 0);
        // write data
        printf("Child 1 wiriting !\n");
        write(pipefd[1], OutPipe, 50);
        // wait reading
        sleep(1);
        // free out pipe
        lockf(pipefd[1] ,0 ,0);
        exit(0);
    }
    else {
        // create child 2
        while((pid2 = fork()) == -1);          		// 若进程2创建不成功,则空循环
    // child 2
        if(pid2 == 0) {
            // load data
            sprintf(OutPipe,"\n Child process 2 is sending message!\n");
            // lock out pipe
            lockf(pipefd[1], 1, 0);
            // write data
            printf("Child 2 wiriting !\n");
            write(pipefd[1], OutPipe, 50);
            // wait reading
            sleep(1);
            // free out pipe
            lockf(pipefd[1], 0, 0);
            exit(0);
        }
    // parent
        else {
            wait(0);
            // lock in pipe
            lockf(pipefd[0], 1, 0);
            // read data
            read(pipefd[0], InPipe, 50);
            // free in pipe
            lockf(pipefd[0], 0, 0);
            // print data
            printf("%s\n",InPipe);
            wait(0);
            // lock in pipe
            lockf(pipefd[0], 1, 0);
            // read data
            read(pipefd[0], InPipe, 50);
            // free in pipe
            lockf(pipefd[0], 0, 0);
            // print data
            printf("%s\n",InPipe);
            exit(0);
        }
    }

    return 0;
}