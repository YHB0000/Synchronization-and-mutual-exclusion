#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "RunableThread.h"
#include "Chopstick.h"

#ifndef Philosopher
#define Philosopher_h
class Philosopher : public RunableThread
{
private:
	Chopstick* Chop;
	int number;

protected:
	unsigned Execue()
	{
		int phnum;
		srand(time(0));
		while (1)
		{
			if (rand() % 2 == 0)
			{
				Sleep(rand() % 100);
				std::cout << "The " << this->number << " philosopher is thinking" << std::endl;
			}
			else {
				phnum = Chop->takeright();
				std::cout << "The " << this->number << " philosopher take one Chopstick." << std::endl;
				Chop->takeleft();
				std::cout << "The " << this->number << " philosopher is eating." << std::endl;
				Chop->finish();
				return 0;
			}
		}
	}
public:
	Philosopher(Chopstick* Chop)
	{
		this->Chop = Chop;
	}

	Philosopher()
	{
		this->Chop = NULL;
	}

	HANDLE Init(Chopstick* Chop, int number)
	{
		HANDLE hold = this->Chop;
		this->Chop = Chop;
		this->number = number;
		return hold;
	}
};
#endif