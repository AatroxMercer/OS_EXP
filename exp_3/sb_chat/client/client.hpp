#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#define REGISTER 1
#define UNREGISTER -1
#define WAIT_P -1
#define SIGNAL_V +1
#define FAILURE -1
#define MSG_MAX_LENGTH 140+1

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
};

class Client {
private:
    int sem_handle;
    int device_handle;
    char buffer[MSG_MAX_LENGTH];
    char current[MSG_MAX_LENGTH];
public:
    Client();
    ~Client();
private:
    void userReception(int op);
    void semaphore(int op);

    void pop3();
    void smtp();

    void reader();
    void writer();
};

