#include<iostream>
#include<stdlib.h>
#include<time.h>

#include "RunableThread.h"
#include "RwLock.h"

#ifndef Writer_h
#define Writer_h

class Writer:public RunableThread
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

		int readerCon = lock->WriteLock(-1);
		Sleep(rand() % 100);

		*buffer += 1;
		std::cout << "Write: buffer=" << *buffer << ".\n";

		Sleep(rand() % 100);
		lock->WriteUnlock();
		return 0;
	}
public:
	Writer(RwLock* lock)
	{
		this->lock = lock;
	}

	Writer()
	{
		this->lock = NULL;
		buffer = NULL;
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