CFLAGS = -Wall -Werror -Wextra -Wpedantic

all : pipe_communication.out software_interrupt.out my_memset.out

pipe_communication.out : pipe_communication.c
	gcc $(CFLAGS) $< -o $@

software_interrupt.out : software_interrupt.c
	gcc $(CFLAGS) $< -o $@

my_memset.out : my_memset.c
	gcc $(CFLAGS) $< -o $@
