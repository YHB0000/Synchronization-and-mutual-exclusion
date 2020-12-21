#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<process.h>

#include "Chopstick.h"
#include "Philosopher.h"
#include "RunableThread.h"

using namespace std;

int main()
{

	Chopstick ch;
	Philosopher ph[5];
	HANDLE phhs[25] = { NULL };

	srand(time(0));
	for (int j = 0; j < 5; j++)
	{
		Sleep(rand() % 200);
		cout << endl;
		cout << "---------- The " << j+1 << " day -----------" << endl;
		for (int i = 0; i < 5; i++)
		{
			ph[i].Init(&ch, i + 1);
			phhs[i] = ph[i].Start();
		}
		cout << endl;
		Sleep(rand() % 1000);
	}

	WaitForMultipleObjects(25, phhs, TRUE, INFINITY);

	return 0;

}