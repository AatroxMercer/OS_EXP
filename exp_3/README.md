# 准备阶段

1. 空间不是很够，，不打算装虚拟机。需要别的解决方案。
   1. 使用ubuntu-base系统+chroot指令得到一个sandbox
   2. sandbox中没有dev sys run proc 等运行时重要资源
   3. 自行将自己的ubuntu系统下的dev 等挂载到 要chroot的/路径下

2. V2.4失败，原因可能如下
   1. 内核版本冲突
   2. gcc版本冲突

3. v2.6直接编译失败
   1. linux/init.h库需要到指定路径下的编译器编译

4. sudo insmod modify_syscall.ko 失败
   1. 高版本内核的syscall table是只读的
   2. 使用内核版本比较低的ubuntu虚拟机
   3. virtualbox+ubuntu10.04

5. 依旧被杀
   1. 加入解除系统调用表的写保护
   2. dmesg 可以看到输出了

6. 尝试使用调用计算加减得到错误答案-1
   1. 将函数返回值改为固定数字，依然得到-1,说明可能对表的修改失败了，或者指向了错误的位置
   2. 真的没辙了，google前一整页都试过了，没用。

