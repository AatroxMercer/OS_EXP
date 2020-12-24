#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>

int main() {
	int ret = syscall(78,10,20);
	printf("%d\n", ret);
	return 0;
}
