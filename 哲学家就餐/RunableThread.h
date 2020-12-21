#ifndef RunableThread_h
#define RunableThread_h
#ifndef _WINDOWS_
#include<Windows.h>	// Ϊ MFC �ṩ������
#endif // !_WINDOWS_
#include<conio.h>
#include<process.h>
#include<WinBase.h>
/*�������������ʵ�����̵߳Ļ����ṹ�Ѿ����������д�ã�Ҫдһ���ܹ���������ʵ���̵߳��ֻ࣬��Ҫ
��public�ķ�ʽ�̳д��࣬Ȼ����дExecue�������˷����ĺ���˼���ǽ�thisָ�봫�ݸ���̬������Ȼ��
��̬����ͨ��ָ���������ʵ���ķ������� */
class RunableThread
{
private:
protected:
	HANDLE hThread;
	unsigned thrdaddr;
	/*����_beginthreadex��_beginthread����ֻ����ȫ�ֺ��������о�̬������Ϊ���������������ԲŽ�
	�����������Ϊ��̬������ֻ�о�̬������û�а취�������зǾ�̬��Ա�ģ�Ҫ�����ʵ�����߳���ִ�У���
	��Ҫ���ʷǾ�̬���������Բ������ְ취*/
	static unsigned WINAPI ThreadProc(LPVOID lpParam)
	{
		RunableThread* pto = (RunableThread*)lpParam;
		return pto->Execue();
	}
	virtual unsigned Execue() = 0;
public:
	RunableThread()
	{
		hThread = NULL;
	}
	HANDLE Start()
	{
		//���� this ָ�룬Ȼ��ʹ�����ָ��ȥ���ʷǾ�̬��Ա��
		return hThread = (HANDLE)_beginthreadex(NULL, 0, RunableThread::ThreadProc, (LPVOID)this, 0, &thrdaddr);
	}
	int Close()
	{
		if (NULL != hThread)
		{
			CloseHandle(hThread);
			hThread = NULL;
		}
		return 0;
	}
	~RunableThread()
	{
		Close();
	}
};
#endif