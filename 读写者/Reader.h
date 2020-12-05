#include<iostream>
#include<stdlib.h>
#include<time.h>

#include "RunableThread.h"
#include "RwLock.h"

#ifndef Reader_h
#define Reader_h

// ʹ���������������ȥ��д Execue ����
class Reader :public RunableThread
{
private:
	RwLock* lock;
	int* buffer;

protected:
	unsigned Execue()
	{
		if (NULL == this->lock)
			return 0;
		srand(time(0));

		int readerCon = lock->ReadLock(-1);
		Sleep(rand() % 100);

		*buffer += 1;
		std::cout << "Reader" << readerCon << ":" << *buffer << ".\n";

		Sleep(rand() % 100);
		lock->ReadUnlock();
		return 0;
	}
public:
	Reader(RwLock* lock)
	{
		this->lock = lock;
		buffer = NULL;
	}

	Reader()
	{
		this->lock = NULL;
	}

	HANDLE Init(RwLock* lock, int* buffer)
	{
		HANDLE hold = this->lock;
		this->lock = lock;
		this->buffer = buffer;
		return hold;
	}
};

#endif