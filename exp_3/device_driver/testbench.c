#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    int fd, num;
    // 打开"/dev/ch_device"
    fd = open("/dev/ch_device", O_RDWR, S_IRUSR | S_IWUSR);
    if (fd != -1 )
    {
        //初次读ch_device
        read(fd, &num, sizeof(int));
        printf("The ch_device is %d\n", num);
        //写ch_device
        printf("Please input the num written to ch_device\n");
        scanf("%d", &num);
        write(fd, &num, sizeof(int));
        //再次读ch_device
        read(fd, &num, sizeof(int));
        printf("The ch_device is %d\n", num);
        //关闭"/dev/ch_device"
        close(fd);
    }
    else { printf("Device open failure\n"); }
    return 0;
}
