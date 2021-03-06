# HIT_OS_Lab
## 哈尔滨工业大学计算机学院操作系统实验
**操作系统实验共有四个：**
### √ 操作系统的引导
```
1.阅读《Linux内核完全注释》的第6章，对计算机和Linux 0.11的引导过程进行初步的了解
2.按照要求改写Linux 0.11的引导程序bootsect.s以及setup.s（必要时会修改build.c文件）
√ bootsect.s能在屏幕上打印一段自定义信息
√ bootsect.s能完成setup.s的载入，并跳转到setup.s开始地址执行，而setup.s向屏幕输出一行"Now we are in SETUP"的提示信息
√ setup.s能获取至少一个基本的硬件参数（如内存参数、显卡参数、硬盘参数等），将其存放在内存的特定地址，并输出到屏幕上，然后setup.s不再加载Linux内核，保持上述信息显示在屏幕上
```
### √ 系统调用
```
1. 在Linux 0.11上添加两个系统调用（在kernel/who.c中实现），并编写两个简单的应用程序测试它们：
√ 第一个系统调用是iam()，其原型为：int iam(const char * name)，完成的功能是将字符串参数name的内容拷贝到内核中保存下来
√ 第二个系统调用是whoami()，其原型为：int whoami(char* name, unsigned int size)，它将内核中由iam()保存的名字拷贝到name指向的用户地址空间中，同时确保不会对name越界访存（name的大小由size说明）
2. 运行添加过新系统调用的Linux 0.11，在其环境下编写两个测试程序 iam.c 和 whoami.c
```
### √ 进程运行轨迹的跟踪与统计
```
1. 基于模板“process.c”编写多进程的样本程序，实现如下功能：
(1)所有子进程都并行运行，每个子进程的实际运行时间一般不超过30秒
(2)父进程向标准输出打印所有子进程的id，并在所有子进程都退出后才退出
2. 在Linux 0.11上实现进程运行轨迹的跟踪。基本任务是在内核中维护一个日志文件/var/process.log，把从操作系统启动到系统关机过程中所有进程的运行轨迹都记录在这一log文件中。
3. 在修改过的0.11上运行样本程序，通过分析log文件，统计该程序建立的所有进程的等待时间、完成时间（周转时间）和运行时间，然后计算平均等待时间，平均完成时间和吞吐量。可以自己编写统计程序，也可以使用python脚本程序stat_log.py进行统计。
4. 修改0.11进程调度的时间片，然后再运行同样的样本程序，统计同样的时间数据，和原有的情况对比，体会不同时间片带来的差异。
```
### √ 信号量的实现和应用
```
1. 在Ubuntu下编写程序，用信号量解决生产者——消费者问题
2. 在linux-0.11中实现信号量，用生产者—消费者程序检验之
在Ubuntu上编写应用程序 “pc.c”，解决经典的生产者—消费者问题，完成下面的功能：
√ 建立一个生产者进程，N个消费者进程（N>1）
√ 用文件建立一个共享缓冲区
√ 生产者进程依次向缓冲区写入整数0,1,2,...,M，M>=500
√ 消费者进程从缓冲区读数，每次读一个，并将读出的数字从缓冲区删除，然后将本进程ID和数字输出到标准输出
√ 缓冲区同时最多只能保存10个数
```
### 注意(Attention)
```
以上资料仅供参考，切勿照搬！！！
```