#ifndef Buffer_h
#define Buffer_h
#ifndef _WINDOWS_
#include<Windows.h>
#endif
#include<conio.h>
#include<process.h>
#include<WinBase.h>

class Buffer
{
protected:
	HANDLE *mutexUse;			// 每一个 Buffer 读写时使用
	HANDLE *mutexUnUse;			// 每一个 Buffer 读写时使用
	int bufferNumber;			// 存储数据槽数
	char** buffer;				// 数据存储地
	int bufferSize;				// 槽的大小
public:
	Buffer()
	{
		mutexUse = new HANDLE[1];
		mutexUnUse = new HANDLE[1];
		bufferNumber = 1;
		buffer = new char* [bufferNumber];
		bufferSize = 1;
		for (int i = 0; i < bufferNumber; i++)
		{
			buffer[i] = new char[bufferSize];
			mutexUse[i] = CreateSemaphore(NULL, 0, 1, NULL);		// 初值 0
			mutexUnUse[i] = CreateSemaphore(NULL, 1, 1, NULL);		// 初值 1
		}
	}
	~Buffer()
	{
		int i = 0, j = 0;
		if (NULL != mutexUse)
		{
			for (i = 0; i < bufferNumber; i++)
			{
				if (NULL != mutexUse[i])
				{
					CloseHandle(mutexUse[i]);
				}
			}
			delete[] mutexUse;
		}
		if (NULL != mutexUnUse)
		{
			for (i = 0; i < bufferNumber; i++)
			{
				if (NULL != mutexUnUse[i])
				{
					CloseHandle(mutexUnUse[i]);
				}
			}
			delete[] mutexUnUse;
		}
		if (NULL != buffer)
		{
			for (i = 0; i < bufferNumber; i++)
			{
				if (NULL != buffer[i])
				{
					delete[] buffer[i];
				}
			}
			delete[] buffer;
		}
	}
	// 初始化 buffernumber 个缓冲区，每个缓冲区大小为 buffersize
	int Init(int bufferNumber, int bufferSize)
	{
		int i = 0, j = 0;
		if (NULL != mutexUse)
		{
			for (i = 0; i < this->bufferNumber; i++)
			{
				if (NULL != mutexUse[i])
				{
					CloseHandle(mutexUse[i]);
				}
			}
			delete[] mutexUse;
		}
		if (NULL != mutexUnUse)
		{
			for (i = 0; i < this->bufferNumber; i++)
			{
				if (NULL != mutexUnUse[i])
				{
					CloseHandle(mutexUnUse[i]);
				}
			}
			delete[] mutexUnUse;
		}
		if (NULL != buffer)
		{
			for (i = 0; i < this->bufferNumber; i++)
			{
				if (NULL != buffer[i])
				{
					delete[] buffer[i];
				}
			}
			delete[] buffer;
		}
		mutexUse = new HANDLE[bufferNumber];
		mutexUnUse = new HANDLE[bufferNumber];
		this->bufferNumber = bufferNumber;
		buffer = new char* [bufferNumber];
		this->bufferSize = bufferSize;
		for (i = 0; i < bufferNumber; i++)
		{
			buffer[i] = new char[bufferSize];
			mutexUse[i] = CreateSemaphore(NULL, 0, 1, NULL);		// 初值 0
			mutexUnUse[i] = CreateSemaphore(NULL, 1, 1, NULL);		// 初值 1
		}
		std::cout << "Init "<< bufferNumber <<" buffers each with " << bufferSize << " size" << std::endl;
		return 0;
	}
	// 读操作
	int Read(char* recBuffer, int recBufferLen)
	{
		// 等待一个已经填充的槽（初始化后共 3 个槽）
		// 等待 读信号量创建完成 （可视为 P 操作过程）
		DWORD slot = WaitForMultipleObjects(bufferNumber, mutexUse, FALSE, INFINITE);

		// 返回值减去 WAIT_OBJECT_0 表示满足等待条件的对象的 mutexUse 数组索引
		slot -= WAIT_OBJECT_0;
		int i = 0;
		for (i = 0; i < bufferSize - 1 && i < recBufferLen; i++ )
		{
			if (buffer[slot][i] != '\0')
			{
				recBuffer[i] = buffer[slot][i];
			} else {
				recBuffer[i] = '\0';
				break;
			}
		}
		recBuffer[i] = '\0';
		ReleaseSemaphore(mutexUnUse[slot], 1, NULL);	// 将槽的状态设置为可用 （空）
		return i;
	}
	// 写操作
	int Write(char* inBuffer, int inBufferLen)
	{
		// 等待一个已经填充的槽
		DWORD slot = WaitForMultipleObjects(bufferNumber, mutexUnUse, FALSE, INFINITE);
		slot -= WAIT_OBJECT_0;
		int i = 0;
		for (i = 0; i < bufferSize - 1 && i < inBufferLen; i++)
		{
			if (inBuffer[i] != '\0')
			{
				buffer[slot][i] = inBuffer[i];
			} else {
				buffer[slot][i] = '\0';
				break;
			}
		}
		buffer[slot][i] = '\0';
		ReleaseSemaphore(mutexUse[slot], 1, NULL);	// 将槽的状态设置为满
		return i;
	}
};
#endif