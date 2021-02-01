#ifndef _MEMORY_MANAGER_H_
#define _MEMORY_MANAGER_H_
#define MAX_PROCESS_NAME_LEN 32
#define MIN_SLICE 10
#define MAX_PROCESS_ID 1024
#define DEFAULT_MEM_SIZE 1024
#define DEFAULT_MEM_START 0

#define MA_FF 1
#define MA_BF 2
#define MA_WF 3
#endif

#include <map>
#include <cstdlib>
#include <iostream>

using std::map;
using std::cin;
using std::cerr;
using std::cout;
using std::endl;

class FreeBlock {
public:
    int size;
    int start_addr;
    FreeBlock* next;

    static FreeBlock* init_freeBlock(int mem_size, int start_addr = DEFAULT_MEM_START) {
        FreeBlock* fb;
        fb = new FreeBlock;
        if (fb == nullptr) {
            cout << "alloction denied: no enough memory" << endl;
            return NULL;
        }
        fb->size = mem_size;
        fb->start_addr = start_addr;
        fb->next = nullptr;
        return fb;
    }

    static FreeBlock* init_freeBlock(int mem_size, FreeBlock* head) {
        // init linked-block of free blocks
        FreeBlock *curr, *next;
        curr = head;
        while (curr) {
            next = curr->next;
            delete curr;
            curr = next;
        }
        return FreeBlock::init_freeBlock(mem_size);
    }

    // compare free blocks according to order
    bool compare(const int order, FreeBlock *fb) {
        switch (order) {
        case 1: return this->start_addr < fb->start_addr;
        case 2: return this->size < fb->size;
        case 3: return this->size > fb->size;
        default: break;
        }
        return false;
    }

    void swap(FreeBlock *fb) {
        int temp;
        temp = this->size;
        this->size = fb->size;
        fb->size = temp;

        temp = this->start_addr;
        this->start_addr = fb->start_addr;
        fb->start_addr = temp;
    }
};

class AllocatedBlock {
public:
    // corresponding process id
    int pid;
    // process memory size
    int size;
    // extra size from MIN SLICE
    int extraSize;
    // momory start address
    int start_addr;
    // process name(shorter than 32)
    char process_name[MAX_PROCESS_NAME_LEN];
    AllocatedBlock* next;
};


class MemoryManager {
private:
    // couter of process
    int cp;
    // map of processes
    map<int, AllocatedBlock*> pMap;

    // total memory size
    int memSize;
    // free memory size
    int freeMem;
    // current memory allocation algorithm
    int ma_algorithm;
    // return true while memory is no more set-able
    bool isMemorySizeSet;

    // linked likst of free block
    FreeBlock* freeBlock_head;
    // linked list of allocated block
    AllocatedBlock* allocatedBlock_head;
public:
    MemoryManager();
    void displayMenu() const;

    void setMemorySize();

    void rearrange(const int);
    void selectMemoryAllocationAlgorithm();

    int newProcess();
    int allocateMemory(AllocatedBlock*);
    int retrenchMemory(AllocatedBlock *);

    int killProcess();
    AllocatedBlock* findProcess(const int);
    int freeMemoey(AllocatedBlock*);

    void displayMemoryUsage() const;

    int do_exit();
};