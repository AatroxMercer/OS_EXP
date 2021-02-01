#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#define REGISTER 1
#define UNREGISTER -1
#define WAIT_P -1
#define SIGNAL_V +1
#define MSG_MAX_LENGTH 140+1

int sem_handle;
int device_handle;
char buffer[MSG_MAX_LENGTH];
char current[MSG_MAX_LENGTH];

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
};

// op : 1 to register , -1 to unregister
// return 0 : fail
static int userReception(int op) {
    // refresh user table
    int total;
    FILE* fd = fopen("/home/sb/desktop/workspace/os/exp_3/device_driver/user.table", "rt+");
    fscanf(fd, "%d", &total);
    rewind(fd);
    fprintf(fd, "%5d", total+op);
    fclose(fd);

    sem_handle = semget(ftok("/dev/ch_device", 0), 1, IPC_CREAT);
    // create semaphore
    if (total == 0 && op == 1) {
        union semun sem_union;
        sem_union.val = 1;
        if(semctl(sem_handle, 0, SETVAL, sem_union) == -1)
            { printf("Error : Failed to create semaphore\n"); }
        printf("Create semaphore success.\n");
        return op;
    }
    // delete semaphore
    if (total == 1 && op == -1) {
        if(semctl(sem_handle, 0, IPC_RMID) == -1)
            { printf("Error : Failed to delete semaphore\n"); }
        printf("Delete semaphore success.\n");
        return op;
    }
    return 0;
}
// order : -1 to wait(P), 1 to signal(V)
static int semaphore(int order) {
    struct sembuf sem_opa;
    sem_opa.sem_num = 0;
    sem_opa.sem_op = order;
    sem_opa.sem_flg = SEM_UNDO;

    if (semop(sem_handle, &sem_opa, 1) == -1) {
        printf("Error : Fail to %c semaphore\n", order==SIGNAL_V?'V':'P');
        return 0;
    }
    return 1;
}

static void pop3() {
    read(device_handle, &buffer, sizeof(int));
    if (strcmp(current, buffer) == 0) { return; }

    strcpy(current, buffer);
    printf("\t\t\tReceving : %s\n", current);
}

static void smtp() {
    printf("queueing...\n");
    semaphore(WAIT_P);

    printf("Message content: \n");
    scanf("%s", current);
    write(device_handle, &current, sizeof(int));

    semaphore(SIGNAL_V);
}

int main(int argc, char *argv[]) {
    device_handle = open("/dev/ch_device", O_RDWR, S_IRUSR | S_IWUSR);
    if (device_handle == -1 ){
        printf("Error : device open failure\n");
        return -1;
    }

    userReception(REGISTER);

    pid_t pid = fork();
    // error occured
    if (pid < 0) { printf("Error : fork failed.\n"); }
    // running in child process
    else if (pid == 0) {
        while (1) { pop3(); }
    }
    // running in parent process
    else {
        char order;
        while (1) {
            printf("type in s to start send msg.\n");
            printf("type in q to quit.\n");
            while ((order = getchar()) != 's' && order != 'q');
            if (order == 'q') { break; }
            smtp();
        }
        kill(pid, SIGINT);
    }

    close(device_handle);
    userReception(UNREGISTER);
    return 0;
}
