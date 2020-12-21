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

protected:
	unsigned Execue()
	{
		int phnum;
		while (1)
		{
			srand(time(0));
			/*if (rand() % 2 == 0)
			{*/
				Sleep(rand() % 100);
				std::cout << "The philosopher is thinking" << std::endl;
			//}
			//else {
				Sleep(rand() % 100);
				phnum = Chop->takeright();
				std::cout << "The " << phnum << " philosopher take one Chopstick." << std::endl;
				//Sleep(rand() % 100);
				Chop->takeleft();
				std::cout << "The " << phnum << " philosopher is eating." << std::endl;
				//Sleep(rand() % 100);
				Chop->finish();
				return 0;
			//}
		}
		//return 0;
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

	HANDLE Init(Chopstick* Chop)
	{
		HANDLE hold = this->Chop;
		this->Chop = Chop;
		return hold;
	}
};
#endif