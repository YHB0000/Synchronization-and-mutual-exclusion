#ifndef Rwlock_h
#define Rwlock_h
#ifndef _WINDOWS_
#include <Windows.h>
#endif
#include<conio.h>
#include<process.h>

// 使用子类自身的属性去重写 Execue 函数
// 该程序对于 time != INFINITE 的等待会造成死锁，需要将计数器增加的操作改变位置
class RwLock
{
private:
	// 读者、写者进程计数
	int rCounter, wCounter;
	// Handle to an object	句柄实际上是一个数据，是一个Long（整长型）的数据，占用系统资源
	HANDLE mut, sem, write;
public:
	// 读写锁初始化
	RwLock() {
		// 读者、写者进程计数置零
		rCounter = wCounter = 0;
		// 创建临界资源
		mut = CreateSemaphore(NULL, 1, 1, NULL);
		sem = CreateSemaphore(NULL, 1, 1, NULL);
		write = CreateSemaphore(NULL, 1, 1, NULL);
	}
	// 读写锁析构
	~RwLock()
	{
		rCounter = wCounter = 0;
		// 所有的内核对象（包括线程 Handle）都是系统资源，用了要还，也就是说用完后一定要 closehandle 关闭
		CloseHandle(mut);
		CloseHandle(sem);
		CloseHandle(write);
	}
	// 读锁函数
	int ReadLock(int time = INFINITE) // -1 表示 INFINITE
	{
		int timer = INFINITE;
		if (time >= 0)
		{
			timer = time;

			// WaitForSingleObject 函数用来检测 hHandle 事件的信号状态
			// 当函数的执行时间超过 dwMilliseconds 就返回
			// 但如果参数 dwMilliseconds 为 INFINITE 时函数将直到相应时间时间变成信号状态才返回，
			// 否则就一直等待下去，直到 WaitForSingleObject 有返回值才执行后面的代码

			WaitForSingleObject(mut, INFINITE);
			WaitForSingleObject(sem, INFINITE);

			WaitForSingleObject(write, 0);	// 位置返回

			// 读者进程 +1
			rCounter += 1;

			// 释放临界资源
			ReleaseSemaphore(sem, 1, NULL);
			ReleaseSemaphore(mut, 1, NULL);

			return rCounter;
		}
	}
	// 写锁函数
	int WriteLock(int time = INFINITE) // -1 表示 INFINITE
	{
		int timer = INFINITE;
		if (time >= 0)
		{
			timer = time;

			WaitForSingleObject(mut, INFINITE);
			WaitForSingleObject(write, INFINITE);

			rCounter += 1;

			return rCounter;
		}
	}
	// 读者释放锁
	int ReadUnlock()
	{
		return 0;
	}
	// 只允许一个 writer，所以 writer 退出时，释放临界资源，可读可写
	int WriteUnlock()
	{
		return 0;
	}
};

#endif // !Rwlock_h
