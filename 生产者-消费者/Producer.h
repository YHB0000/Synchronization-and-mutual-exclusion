#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "RunableThread.h"
#include "Buffer.h"
#ifndef Producer_h
#define Producer_h
class Producer :public RunableThread
{
private:
	Buffer* bf;
	FILE* fp;
protected:
	virtual unsigned Execue()
	{
		//std::cout << "Producer Execue()" << std::endl;
		char buffer[20];
		// ���ļ��ڲ��� λ��ָ�� ����ָ��һ������ ������/�ļ����Ŀ�ͷ
		rewind(this->fp);
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
	Buffer* Init(Buffer* bf, FILE* fp)
	{
		Buffer* hold = this->bf = bf;
		this->bf = bf;
		this->fp = fp;
		return hold;
	}
};
#endif