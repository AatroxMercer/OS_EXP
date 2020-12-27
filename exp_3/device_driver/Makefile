ifneq ($(KERNELRELEASE),)
obj-m := ch_device.o
else
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	sudo rm *.o *.mod *.mod.c .ch* .m* Module* module* .M*
endif

load:
	sudo dmesg --clear
	sudo insmod ch_device.ko
	sudo mknod /dev/ch_device c 290 0

test: ch_test.c
	gcc $< -o ch_test
	./ch_test

clean:
	sudo rm /dev/ch_device
	sudo rmmod ch_device
	sudo rm *.o *.mod *.mod.c .ch* .m* Module* module* .M*
	sudo rm *.ko ch_test