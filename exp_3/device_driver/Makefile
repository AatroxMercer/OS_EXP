CFLAGS = #-Wall -Werror -Wextra -Wpedantic

ifneq ($(KERNELRELEASE),)
obj-m := char_device_driver.o
else
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	make clean
endif

testbench : testbench.c
	gcc $(CFLAGS) $< -o $@

clean:
	sudo rm *.o *.mod *.mod.c .M* .m* Module* module* .*