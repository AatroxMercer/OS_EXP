DIR_ROOT = $(shell pwd)
DIR_CLIENT = $(DIR_ROOT)/client
DIR_SERVER = $(DIR_ROOT)/server

.PHONY: $(DIR_SERVER) $(DIR_CLIENT) load unload

all: $(DIR_SERVER) $(DIR_CLIENT)
	cp ./client/main ./main

$(DIR_SERVER):
	$(MAKE) -C $@

$(DIR_CLIENT):
	$(MAKE) -C $@

load:
	sudo dmesg --clear
	sudo insmod $(PWD)/server/sb_chat_server.ko
	sudo mknod /dev/sb_chat_server c 290 0

unload:
	sudo rm /dev/sb_chat_server
	sudo rmmod sb_chat_server