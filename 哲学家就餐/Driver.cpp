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
	HANDLE phhs[5] = { NULL };

	srand(time(0));
	for (int i = 0; i < 5; i++)
	{
		ph[i].Init(&ch);
		phhs[i] = ph[i].Start();
		Sleep(rand() % 100);
	}

	WaitForMultipleObjects(5, phhs, TRUE, INFINITY);

	return 0;

}