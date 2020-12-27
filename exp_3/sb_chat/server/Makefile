ifneq ($(KERNELRELEASE),)
obj-m := sb_chat_server.o
else
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

modules:
	echo $(PWD)
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	sudo rm .*.cmd *.symvers *.order *.mod*
	sudo rm *.o
endif