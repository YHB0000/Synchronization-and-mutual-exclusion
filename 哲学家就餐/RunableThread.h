#ifndef RunableThread_h
#define RunableThread_h
#ifndef _WINDOWS_
#include<Windows.h>	// 为 MFC 提供兼容性
#endif // !_WINDOWS_
#include<conio.h>
#include<process.h>
#include<WinBase.h>
/*在类中启动类的实例的线程的基本结构已经在这个类中写好，要写一个能够启动自身实例线程的类，只需要
用public的方式继承此类，然后重写Execue方法，此方法的核心思想是将this指针传递给静态函数，然后
静态函数通过指针启动类的实例的方法函数 */
class RunableThread
{
private:
protected:
	HANDLE hThread;
	unsigned thrdaddr;
	/*由于_beginthreadex和_beginthread函数只接受全局函数和类中静态函数作为第三个参数，所以才将
	这个函数声明为静态，但是只有静态函数是没有办法访问类中非静态成员的，要让类的实例在线程中执行，必
	须要访问非静态函数，所以才有这种办法*/
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
		//传递 this 指针，然后使用这个指针去访问非静态成员，
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