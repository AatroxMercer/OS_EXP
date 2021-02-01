CFLAGS = -Wall -Werror -Wextra -Wpedantic

main : main.o client.o
	g++ $(CFLAGS) $^ -o $@
	rm *.o

main.o : main.cpp
	g++ $(CFLAGS) -c $<

client.o : client.cpp
	g++ $(CFLAGS) -c $<