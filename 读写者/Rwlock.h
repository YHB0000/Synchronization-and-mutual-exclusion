#ifndef Rwlock_h
#define Rwlock_h
#ifndef _WINDOWS_
#include <Windows.h>
#endif
#include<conio.h>
#include<process.h>

// ʹ���������������ȥ��д Execue ����
// �ó������ time != INFINITE �ĵȴ��������������Ҫ�����������ӵĲ����ı�λ��
class RwLock
{
private:
	// ���ߡ�д�߽��̼���
	int rCounter, wCounter;
	// Handle to an object	���ʵ������һ�����ݣ���һ��Long�������ͣ������ݣ�ռ��ϵͳ��Դ
	HANDLE mut, sem, write;
public:
	// ��д����ʼ��
	RwLock() {
		// ���ߡ�д�߽��̼�������
		rCounter = wCounter = 0;
		// �����ٽ���Դ
		mut = CreateSemaphore(NULL, 1, 1, NULL);
		sem = CreateSemaphore(NULL, 1, 1, NULL);
		write = CreateSemaphore(NULL, 1, 1, NULL);
	}
	// ��д������
	~RwLock()
	{
		rCounter = wCounter = 0;
		// ���е��ں˶��󣨰����߳� Handle������ϵͳ��Դ������Ҫ����Ҳ����˵�����һ��Ҫ closehandle �ر�
		CloseHandle(mut);
		CloseHandle(sem);
		CloseHandle(write);
	}
	// ��������
	int ReadLock(int time = INFINITE) // -1 ��ʾ INFINITE
	{
		int timer = INFINITE;
		if (time >= 0)
		{
			timer = time;

			// WaitForSingleObject ����������� hHandle �¼����ź�״̬
			// ��������ִ��ʱ�䳬�� dwMilliseconds �ͷ���
			// ��������� dwMilliseconds Ϊ INFINITE ʱ������ֱ����Ӧʱ��ʱ�����ź�״̬�ŷ��أ�
			// �����һֱ�ȴ���ȥ��ֱ�� WaitForSingleObject �з���ֵ��ִ�к���Ĵ���

			WaitForSingleObject(mut, INFINITE);
			WaitForSingleObject(sem, INFINITE);

			WaitForSingleObject(write, 0);	// λ�÷���

			// ���߽��� +1
			rCounter += 1;

			// �ͷ��ٽ���Դ
			ReleaseSemaphore(sem, 1, NULL);
			ReleaseSemaphore(mut, 1, NULL);

			return rCounter;
		}
	}
	// д������
	int WriteLock(int time = INFINITE) // -1 ��ʾ INFINITE
	{
		int timer = INFINITE;
		if (time >= 0)
		{
			timer = time;

			WaitForSingleObject(mut, INFINITE);
			WaitForSingleObject(write, INFINITE);

			rCounter += 1;

			return rCounter;
		}
	}
	// �����ͷ���
	int ReadUnlock()
	{
		return 0;
	}
	// ֻ����һ�� writer������ writer �˳�ʱ���ͷ��ٽ���Դ���ɶ���д
	int WriteUnlock()
	{
		return 0;
	}
};

#endif // !Rwlock_h
