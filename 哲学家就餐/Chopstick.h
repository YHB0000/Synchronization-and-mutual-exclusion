#ifndef Chopstick_h
#define Chopstick_h
#ifndef _WINDOWS_
#include <Windows.h>
#endif
#include<conio.h>
#include<process.h>

class Chopstick
{
private:
	HANDLE mut, num;
	int phnum;
public:
	Chopstick() {
		phnum = 0;
		mut = CreateSemaphore(NULL, 1, 1, NULL);
		num = CreateSemaphore(NULL, 4, 1, NULL);
	}
	~Chopstick()
	{
		CloseHandle(num);
	}
	int takeright()
	{
		WaitForSingleObject(num, INFINITE);
		phnum++;
		return phnum;
	}
	int takeleft()
	{
		if (phnum == 1)
		{
			WaitForSingleObject(mut, INFINITE);
			return phnum;
		}
		WaitForSingleObject(num, INFINITE);
		return phnum;
	}
	void finish()
	{
		if (phnum == 1)
		{
			ReleaseSemaphore(mut, 1, NULL);
		}
		ReleaseSemaphore(num, 2, NULL);
	}
	int show()
	{
		phnum++;
		return phnum;
	}
};

#endif // !Chopstick_h
