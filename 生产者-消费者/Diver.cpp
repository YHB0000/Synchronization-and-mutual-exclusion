#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<process.h>
#include "RunableThread.h"
#include "Buffer.h"
#include "Producer.h"
#include "Consumer.h"
#include "stdlib.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	int i = 0, j = 0, k = 0;
	Buffer b3;
	Consumer cs[8];				// 8 个消费者
	HANDLE hcs[8];				// 保存消费线程句柄
	Producer ps[4];				// 4 个生产者
	HANDLE hps[4];				// 保存生产线程句柄
	FILE* fps[4] = { NULL };	// 4 个 producer 文件结构
	FILE* fpc[8] = { NULL };	// 8 个 consumer 文件结构
	char End[] = "exit";

	// 初始化
	char commonBuffer[100] = {'\0'};

	// 将 source.txt 的文本放进 buffer
	// 4 个 生产者 读取对应的 source.txt
	for (i = 0; i < 4; i++)
	{
		char data[100];
		sprintf(commonBuffer, "source%d.txt", i);
		fps[i] = fopen(commonBuffer, "r");			// 读 buffer
		cout << "source" << i << " is push in the fps[" << i << "]" << endl;
		fgets(data, 100, fps[i]);
		printf("%s\n", data);
	}

	// 创建 consumer.txt
	// 8 个 消费者 创建对应的 consumer.txt
	for (i = 0; i < 8; i++)
	{
		sprintf(commonBuffer, "consumer%d.txt", i);
		fpc[i] = fopen(commonBuffer, "w+");			// 写 buffer
		cout << "consumer" << i << " is created and push in the fpc[" << i << "]" << endl;
	}

	// 初始化 3 个缓冲区， 大小为 30
	b3.Init(3, 30);		

	// fpc 指向缓冲区，消费者 进程指向缓冲区
	for (i = 0; i < 8; i++)
	{
		cout << "cs[" << i << "] Init" << endl;
		cs[i].Init(&b3, fpc[i]);
	}

	// fps 指向缓冲区，生产者 进程指向缓冲区
	for (i = 0; i < 4; i++)
	{
		cout << "ps[" << i << "] Init" << endl;
		ps[i].Init(&b3, fps[i]);
	}

	// 创建 8 个 消费者 线程
	for (i = 0; i < 8; i++)
	{
		hcs[i] = cs[i].Start();
	}

	// 创建 4 个 生产者 线程
	for (i = 0; i < 4; i++)
	{
		hps[i] = ps[i].Start();
	}

	// 等待 生产者 结束
	WaitForMultipleObjects(4, hps, TRUE, INFINITY);	

	// 生产者 读完后关闭文件
	for (i = 0; i < 4; i++)
	{
		fclose(fps[i]);
	}

	// 建议在此设置断点进行调试
	for (i = 0; i < 8; i++)
	{
		b3.Write(End, strlen("exit"));
	}

	// 等待 消费者 结束
	WaitForMultipleObjects(8, hcs, TRUE, INFINITY);		

	// 消费者 读完后关闭文件
	for (i = 0; i < 8; i++)
	{
		fclose(fpc[i]);
	}
	return 0;
}