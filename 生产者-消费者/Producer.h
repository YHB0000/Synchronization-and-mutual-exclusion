#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include "RunableThread.h"
#include "Buffer.h"
#ifndef Producer_h
#define Producer_h
class Producer :public RunableThread
{
private:
	Buffer* bf;
	FILE* fp;
	int number;
protected:
	unsigned Execue()
	{
		std::cout << "Producer Execue()" << std::endl;
		char buffer[20];
		// 将文件内部的 位置指针 重新指向一个流（数据流/文件）的开头
		//rewind(fp);
		sprintf(buffer, "source%d.txt", number);
		fp = fopen(buffer, "r");
		while (NULL != fgets(buffer, 20, fp))
		{
			bf->Write(buffer, 20);
		}
		return 0;
	}
public:
	Producer()
	{
		this->bf = NULL;
	}
	Buffer* Init(Buffer* bf, FILE* fp, int i)
	{
		Buffer* hold = this->bf = bf;
		this->number = i;
		this->bf = bf;
		this->fp = fp;
		return hold;
	}
};
#endif