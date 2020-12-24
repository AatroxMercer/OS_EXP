#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
//original syscall 78 function: gettimeofday
#define SYSCALL_INDEX 78

// point to the original system call function
unsigned long original_sys_call_func;
//  start address of system call table
unsigned long p_sys_call_table = 0xffffffff8155e018;
unsigned long *sys_call_addr;

asmlinkage int hello(int a, int b) {
	return a + b;
}

void disable_write_protection(void) {
  unsigned long cr0 = read_cr0();
  clear_bit(16, &cr0);
  write_cr0(cr0);
}

void enable_write_protection(void) {
    unsigned long cr0 = read_cr0();
    set_bit(16, &cr0);
    write_cr0(cr0);
}

// make syscall[SYSCALL_INDEX] point to function hello
void modify_syscall(void) {
    original_sys_call_func = *(sys_call_addr);
    *(sys_call_addr) = (unsigned long)&hello;
	printk("No 87 syscall has changed to hello");
}

// restore syscall[SYSCALL_INDEX] to original function
void restore_syscall(void) {
    *(sys_call_addr) = original_sys_call_func;
	printk("No 87 syscall has changed to origin");
}

// contruct module
static int mymodule_init(void) {
    // base + offset -> target pointer
    sys_call_addr = (unsigned long *)(p_sys_call_table  + 4*SYSCALL_INDEX);
    disable_write_protection();
    modify_syscall();
    return 0;
}

// distruct module
static void mymodule_exit(void) {
    restore_syscall();
    enable_write_protection();
}

module_init(mymodule_init);
module_exit(mymodule_exit);