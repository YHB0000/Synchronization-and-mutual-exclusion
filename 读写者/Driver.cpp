#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<process.h>

#include "Rwlock.h"
#include "RunableThread.h"
#include "Reader.h"
#include "Writer.h"

#include "stdlib.h"

// 本程序将演示互斥读写的重要性以及不加控制地向输出流中进行输出导致的输出序列混乱
void main()
{
	RwLock lock;

	Reader re[600];
	Writer wr[25];
	HANDLE rehs[600] = { NULL };
	HANDLE wrhs[25] = { NULL };

	int i = 0, j = 0, k = 0, r = 0;
	int buffer = 0;
	srand(time(0));

	for (i = 0; i < 600+25; i++)
	{
		r = rand() % 2;

		if (0 == r)
		{
			if (j < 25)
			{
				wr[j].Init(&lock, &buffer);
				wrhs[j] = wr[j].Start();
				j += 1;
			} else {
				re[k].Init(&lock, &buffer);
				rehs[k] = re[k].Start();
				k += 1;
			}
		} else {
			if (k < 600)
			{
				re[k].Init(&lock, &buffer);
				rehs[k] = re[k].Start();
				k += 1;
			} else
			{
				wr[j].Init(&lock, &buffer);
				wrhs[j] = wr[j].Start();
				j += 1;
			}
		}
	}
	WaitForMultipleObjects(25, wrhs, TRUE, INFINITE);
	WaitForMultipleObjects(600, rehs, TRUE, INFINITE);

	_getch();
}