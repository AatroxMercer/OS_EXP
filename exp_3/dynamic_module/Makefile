CFLAGS = -Wall -Werror -Wextra -Wpedantic

ifneq ($(KERNELRELEASE),)
obj-m := mymodules.o
obj-m := modify_syscall.o

else
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

call_gettimeofday : call_gettimeofday.c
	gcc $(CFLAGS) $< -o $@


call_mysyscall : call_mysyscall.c
	gcc $(CFLAGS) $< -o $@

clean:
	sudo rm *.o *.mod *.mod.c .M* .m* Module* module*
