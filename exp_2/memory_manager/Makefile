CFLAGS = -Wall -Werror -Wextra -Wpedantic

main.out : main.o memory_manager.o
	g++ $(CFLAGS) $^ -o $@

main.o : main.cpp
	g++ $(CFLAGS) -c $<

memory_manager.o : memory_manager.cpp
	g++ $(CFLAGS) -c $<

.PHONY:sample
sample : sample.cpp
	g++ $(CFLAGS) $< -o sample.out
	./sample.out

.PHONY:clean
clean:
	rm *.o $(target)