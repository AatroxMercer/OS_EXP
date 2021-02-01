#include "client.hpp"

Client::Client() {
    // check if server is online
    device_handle = open("/dev/sb_chat_server", O_RDWR, S_IRUSR | S_IWUSR);
    if (device_handle == FAILURE ){
        cerr << "Error : server offline" << endl;
        exit(0);
    }

    userReception(REGISTER);

    pid_t pid = fork();
    // error occured
    if (pid < 0) {
        cerr << "Error : fork failed." << endl;
        exit(0);
    }
    // running in child process
    else if (pid == 0) {
        while (1) { reader(); }
    }
    // running in parent process
    else {
        writer();
        kill(pid, SIGINT);
    }
}


Client::~Client() {
    cout << "Thanks for using!" << endl;
    userReception(UNREGISTER);
    close(device_handle);
}

// op : 1 to register , -1 to unregister
// return 0 : fail
void Client::userReception(int op) {
    // refresh user table
    int total;
    FILE* fd = fopen("/home/sb/desktop/workspace/os/exp_3/sb_chat/user.table", "rt+");
    fscanf(fd, "%d", &total);
    rewind(fd);
    fprintf(fd, "%5d", total+op);
    fclose(fd);

    sem_handle = semget(ftok("/dev/sb_chat_server", 0), 1, IPC_CREAT);
    // create semaphore
    if (total == 0 && op == 1) {
        union semun sem_union;
        sem_union.val = 1;
        if(semctl(sem_handle, 0, SETVAL, sem_union) == FAILURE) {
            cerr << "Error : failed to create semaphore" << endl;
            exit(0);
        }
        cout << "Create semaphore success." << endl;
        return;
    }
    // delete semaphore
    if (total == 1 && op == -1) {
        if(semctl(sem_handle, 0, IPC_RMID) == FAILURE) {
            cerr << "Error : failed to delete semaphore" << endl;
            exit(0);

        }
        cout << "Delete semaphore success." << endl;
        return;
    }
}

// order : -1 to wait(P), 1 to signal(V)
void Client::semaphore(int order) {
    struct sembuf sem_opa;
    sem_opa.sem_num = 0;
    sem_opa.sem_op = order;
    sem_opa.sem_flg = SEM_UNDO;

    if (semop(sem_handle, &sem_opa, 1) == FAILURE) {
        printf("Error : Fail to %c semaphore\n", order == SIGNAL_V ? 'V' : 'P');
        exit(0);
    }
}

// receiving message
void Client::pop3() {
    read(device_handle, &buffer, sizeof(int));
}

// sending message
void Client::smtp() {
    write(device_handle, &current, sizeof(int));
}

void Client::reader() {
    pop3();
    if (strcmp(current, buffer) == 0) { return; }

    strcpy(current, buffer);
    cout << "\t\t\tReceving : " << current << endl;
}

void Client::writer() {
    char order;
    while (1) {
        cout << "type in s to start send msg." << endl;
        cout << "type in q to quit." << endl;
        while ((order = getchar()) != 's' && order != 'q');
        if (order == 'q') { break; }

        cout << "queueing..." << endl;
        semaphore(WAIT_P);

        cout << "Message content:" << endl;
        cin >> current;
        smtp();
        semaphore(SIGNAL_V);
    }
}