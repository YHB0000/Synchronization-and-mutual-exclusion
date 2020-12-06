#ifndef Buffer_h
#define Buffer_h
#ifndef _WINDOWS_
#include<Windows.h>
#endif
#include<conio.h>
#include<process.h>
#include<WinBase.h>

class Buffer
{
protected:
	HANDLE *mutexUse;			// ÿһ�� Buffer ��дʱʹ��
	HANDLE *mutexUnUse;			// ÿһ�� Buffer ��дʱʹ��
	int bufferNumber;			// �洢���ݲ���
	char** buffer;				// ���ݴ洢��
	int bufferSize;				// �۵Ĵ�С
public:
	Buffer()
	{
		mutexUse = new HANDLE[1];
		mutexUnUse = new HANDLE[1];
		bufferNumber = 1;
		buffer = new char* [bufferNumber];
		bufferSize = 1;
		for (int i = 0; i < bufferNumber; i++)
		{
			buffer[i] = new char[bufferSize];
			mutexUse[i] = CreateSemaphore(NULL, 0, 1, NULL);		// ��ֵ 0
			mutexUnUse[i] = CreateSemaphore(NULL, 1, 1, NULL);		// ��ֵ 1
		}
	}
	~Buffer()
	{
		int i = 0, j = 0;
		if (NULL != mutexUse)
		{
			for (i = 0; i < bufferNumber; i++)
			{
				if (NULL != mutexUse[i])
				{
					CloseHandle(mutexUse[i]);
				}
			}
			delete[] mutexUse;
		}
		if (NULL != mutexUnUse)
		{
			for (i = 0; i < bufferNumber; i++)
			{
				if (NULL != mutexUnUse[i])
				{
					CloseHandle(mutexUnUse[i]);
				}
			}
			delete[] mutexUnUse;
		}
		if (NULL != buffer)
		{
			for (i = 0; i < bufferNumber; i++)
			{
				if (NULL != buffer[i])
				{
					delete[] buffer[i];
				}
			}
			delete[] buffer;
		}
	}
	// ��ʼ�� buffernumber ����������ÿ����������СΪ buffersize
	int Init(int bufferNumber, int bufferSize)
	{
		int i = 0, j = 0;
		if (NULL != mutexUse)
		{
			for (i = 0; i < this->bufferNumber; i++)
			{
				if (NULL != mutexUse[i])
				{
					CloseHandle(mutexUse[i]);
				}
			}
			delete[] mutexUse;
		}
		if (NULL != mutexUnUse)
		{
			for (i = 0; i < this->bufferNumber; i++)
			{
				if (NULL != mutexUnUse[i])
				{
					CloseHandle(mutexUnUse[i]);
				}
			}
			delete[] mutexUnUse;
		}
		if (NULL != buffer)
		{
			for (i = 0; i < this->bufferNumber; i++)
			{
				if (NULL != buffer[i])
				{
					delete[] buffer[i];
				}
			}
			delete[] buffer;
		}
		mutexUse = new HANDLE[bufferNumber];
		mutexUnUse = new HANDLE[bufferNumber];
		this->bufferNumber = bufferNumber;
		buffer = new char* [bufferNumber];
		this->bufferSize = bufferSize;
		for (i = 0; i < bufferNumber; i++)
		{
			buffer[i] = new char[bufferSize];
			mutexUse[i] = CreateSemaphore(NULL, 0, 1, NULL);		// ��ֵ 0
			mutexUnUse[i] = CreateSemaphore(NULL, 1, 1, NULL);		// ��ֵ 1
		}
		std::cout << "Init "<< bufferNumber <<" buffers each with " << bufferSize << " size" << std::endl;
		return 0;
	}
	// ������
	int Read(char* recBuffer, int recBufferLen)
	{
		// �ȴ�һ���Ѿ����Ĳۣ���ʼ���� 3 ���ۣ�
		// �ȴ� ���ź���������� ������Ϊ P �������̣�
		DWORD slot = WaitForMultipleObjects(bufferNumber, mutexUse, FALSE, INFINITE);

		// ����ֵ��ȥ WAIT_OBJECT_0 ��ʾ����ȴ������Ķ���� mutexUse ��������
		slot -= WAIT_OBJECT_0;
		int i = 0;
		for (i = 0; i < bufferSize - 1 && i < recBufferLen; i++ )
		{
			if (buffer[slot][i] != '\0')
			{
				recBuffer[i] = buffer[slot][i];
			} else {
				recBuffer[i] = '\0';
				break;
			}
		}
		recBuffer[i] = '\0';
		ReleaseSemaphore(mutexUnUse[slot], 1, NULL);	// ���۵�״̬����Ϊ���� ���գ�
		return i;
	}
	// д����
	int Write(char* inBuffer, int inBufferLen)
	{
		// �ȴ�һ���Ѿ����Ĳ�
		DWORD slot = WaitForMultipleObjects(bufferNumber, mutexUnUse, FALSE, INFINITE);
		slot -= WAIT_OBJECT_0;
		int i = 0;
		for (i = 0; i < bufferSize - 1 && i < inBufferLen; i++)
		{
			if (inBuffer[i] != '\0')
			{
				buffer[slot][i] = inBuffer[i];
			} else {
				buffer[slot][i] = '\0';
				break;
			}
		}
		buffer[slot][i] = '\0';
		ReleaseSemaphore(mutexUse[slot], 1, NULL);	// ���۵�״̬����Ϊ��
		return i;
	}
};
#endif