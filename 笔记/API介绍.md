# 句柄

​	句柄，是整个Windows编程的基础。一个句柄是指使用的一个唯一的整数值，即一个4字节(64位程序中为8字节)长的数值，来标识应用程序中的不同对象和同类对象中的不同的实例，诸如，一个窗口，按钮，图标，滚动条，输出设备，控件或者文件等。应用程序能够通过句柄访问相应的对象的信息，但是句柄不是一个指针，程序不能利用句柄来直接阅读文件中的信息。如果句柄不用在I/O文件中，它是毫无用处的。 句柄是Windows用来标志应用程序中建立的或是使用的唯一整数，Windows使用了大量的句柄来标志很多对象。



# HANDLE

​	Handle本身是一个32位的无符号整数，它用来代表一个内核对象。并不指向实际的内核对象，用户模式下的程序永远不可能获得一个内核对象的实际地址（一般情况下）；是作为一个索引在一个表中查找对应的内核对象的实际地址。每个进程都有一个表，叫句柄表，该表的第一项就是进程自己的句柄

​	`Handle就是一种用来"间接"代表一个内核对象的整数值。你可以在程序中使用handle来代表你想要操作的内核对象。这里的内核对象包括：事件（Event）、线程、进程、Mutex等等。我们最常见的就是文件句柄（file handle）。`



# DWORD

​	C++中使用DWORD不用声明，但是要加头文件Windows.h

​	1.DWORD 就是 Double Word，每个 word 为 2 个字节即为 4 个字节，每个字节是 8 位，共 32 位。

​	2.DWORD 的宏定义如下：  #define DWORD unsigned long

​	3.DWORD 在 Windows 下经常用来保存地址（或者存放指针） 



# WINAPI

​	#define WINAPI _stdcall

​	WINAPI是一个宏，所代表的符号是__stdcall, 函数名前加上这个符号表示这个函数的调用约定是标准调用约定，windows API函数采用这种调用约定。

```
stdcall的调用约定意味着： 
	1）参数从右向左压入堆栈；
	2）函数自身修改堆栈；
	3)函数名自动加前导的下划线，后面紧跟一个@符号，其后紧跟着参数的尺寸。
```



# LPVOID

​	LPVOID是一个没有类型的指针，也就是说你可以将LPVOID类型的[变量赋值](https://baike.baidu.com/item/变量赋值/23729660)给任意类型的指针，比如在参数传递时就可以把任意类型传递给一个LPVOID类型为参数的方法，然后在方法内再将这个“任意类型”从传递时的“LPVOID类型”转换回来。



# _beginthread _beginthreadex

​	process.h

​	创建一个线程,指定以C运行库的形式运行,而CreateThreadO 以 Win32调用方式创建线程。

## 语法

```c++
uintptr_t _beginthreadex(
	void *security,
	//指向一个SECURITY_ ATTRIBUTES 结构，用来标识其返回的句柄能否被其子线程继承
	unsigned stack_size,					//新线程的栈的大小
	unsigned (*start_address)(void *),	    //新线程的起始地址
	vo1d *arglist,						    //向新线程传递的参数列表
	unsigned initflag,						//新线程的初始状态
	unsigned *thrdaddr						//指向一个32位的变量，改变量用来保存线程标识符
);
uintptr_t _beginthread( // NATIVE CODE
   void( __cdecl *start_address )( void * ),
   unsigned stack_size,
   void *arglist
);
uintptr_t _beginthread( // MANAGED CODE
   void( __clrcall *start_address )( void * ),
   unsigned stack_size,
   void *arglist
);
uintptr_t _beginthreadex( // NATIVE CODE
   void *security,
   unsigned stack_size,
   unsigned ( __stdcall *start_address )( void * ),
   void *arglist,
   unsigned initflag,
   unsigned *thrdaddr
);
uintptr_t _beginthreadex( // MANAGED CODE
   void *security,
   unsigned stack_size,
   unsigned ( __clrcall *start_address )( void * ),
   void *arglist,
   unsigned initflag,
   unsigned *thrdaddr
);
```



## 参数

### *start_address*

​	开始执行新线程的例程的起始地址。对于**_beginthread**，调用约定是[__cdecl](https://docs.microsoft.com/zh-cn/cpp/cpp/cdecl?view=msvc-160)（对于本机代码）或[__clrcall](https://docs.microsoft.com/zh-cn/cpp/cpp/clrcall?view=msvc-160)（对于托管代码）；对于**_beginthreadex**，它可以是[__stdcall](https://docs.microsoft.com/zh-cn/cpp/cpp/stdcall?view=msvc-160)（对于本机代码）或[__clrcall](https://docs.microsoft.com/zh-cn/cpp/cpp/clrcall?view=msvc-160)（对于托管代码）。

### *stack_size*

​	新线程的堆栈大小或 0。

### *arglist*

​	要传递到新线程的参数列表，或为 **NULL**。

### *Security*

​	指向[SECURITY_ATTRIBUTES](https://docs.microsoft.com/zh-cn/previous-versions/windows/desktop/legacy/aa379560(v=vs.85))结构的*安全*指针，该结构确定返回的句柄是否可以由子进程继承。如果*Security*为**NULL**，则不能继承该句柄。对于Windows 95应用程序，必须为**NULL**。

### *initflag*

​	用于控制新线程的初始状态的标志。将*initflag*设置为0可立即运行，或将**CREATE_SUSPENDED设置**为处于挂起状态的线程；使用[ResumeThread](https://docs.microsoft.com/zh-cn/windows/win32/api/processthreadsapi/nf-processthreadsapi-resumethread)执行线程。将*initflag*设置为**STACK_SIZE_PARAM_IS_A_RESERVATION**标志，以使用*stack_size*作为堆栈的初始保留大小（以字节为单位）；如果未指定此标志，则*stack_size*指定提交大小。

### *thrdaddr*

​	指向接收线程标识符的 32 位变量。 如果 **为 NULL**，则不使用。



## 返回值

​	如果成功，则这些函数中的每个函数都会为新创建的线程返回一个句柄。但是，如果新创建的线程退出太快，则**_beginthread**可能不会返回有效的句柄。（见备注部分的讨论）在错误中，**_beginthread**返回-1L，并且**将errno**设置为**EAGAIN**如果有太多的线程，以**EINVAL**如果参数无效或堆栈大小是不正确，或**EACCES**如果没有足够的资源（例如内存）。

​	发生错误时，**_beginthreadex**返回0，并且**设置了errno**和**_doserrno**。

​	如果*start_address*为**NULL**，则将调用无效的参数处理程序，如[Parameter Validation中所述](https://docs.microsoft.com/zh-cn/cpp/c-runtime-library/parameter-validation?view=msvc-160)。 如果允许执行继续，这些函数**会将errno设置**为**EINVAL**并返回-1。



# WaitForSingleObject

​	windows.h(synchapi.h)

​	等待直到指定的对象处于发信号状态或超时间隔过去。

​	指定句柄消耗其信号量（hHandle）的值，类似于PV操作中的P

## 语法

```c++
DWORD WaitForSingleObject(
  HANDLE hHandle,				// 指向句柄数组的指针
  DWORD  dwMilliseconds			// 超时间隔（以毫秒为单位）
);
```



## 参数

### hHandle

​	对象的句柄。有关可以指定其句柄的对象类型的列表，请参见以下“备注”部分。

​	如果在等待仍未完成的情况下关闭了此句柄，则该函数的行为是不确定的。

​	句柄必须具有**SYNCHRONIZE**访问权限。有关更多信息，请参见 [标准访问权限](https://docs.microsoft.com/en-us/windows/desktop/SecAuthZ/standard-access-rights)。

### dwMilliseconds

​	超时间隔（以毫秒为单位）。

​	如果指定了非零值，则函数将等待，直到发出信号通知对象或间隔过去为止。

​	如果*dwMilliseconds*为零，则如果未用信号通知对象，则函数不会进入等待状态；否则，函数将进入等待状态。它总是立即返回。

​	**如果*dwMilliseconds*为INFINITE，则该函数仅在信号通知对象时返回。**



## 返回值

​	如果函数成功，则返回值指示导致函数返回的事件。它可以是以下值之一。

| 返回码/值                          | 描述                                                         |
| :--------------------------------- | :----------------------------------------------------------- |
| **WAIT_ABANDONED**0x00000080L      | 指定的对象是互斥对象，在拥有线程终止之前，拥有互斥对象的线程未释放该互斥对象。互斥对象的所有权授予调用线程，并且互斥状态设置为无信号。如果互斥锁正在保护持久状态信息，则应检查其一致性。 |
| **WAIT_OBJECT_0**0x00000000L       | 发出指定对象的状态信号。                                     |
| **WAIT_TIMEOUT**0x00000102L        | 超时时间间隔过去了，并且对象的状态没有信号。                 |
| **WAIT_FAILED**（DWORD）0xFFFFFFFF | 该功能失败。要获取扩展的错误信息，请调用 [GetLastError](https://docs.microsoft.com/en-us/windows/desktop/api/errhandlingapi/nf-errhandlingapi-getlasterror)。 |



# WaitForMutipleObjects

​	windows.h(synchapi.h)	

​	等待指定的一个或全部的对象（*lpHandles）完成作业，或等待超过指定的时间

## 语法

```c++
DWORD WaitForMu1tipleObjects( 
    DWORD nCount,				 // 句柄的数量
	ONST HANDLE *1pHandles,      // 指向句柄数组的指针 
    B0OL fWaitAll,			     // 等待标志位
	DWORD dwM1111seconds 	     // 超时间隔（以毫秒为单位）
);
```

## 参数

### nCount

​	*lpHandles*指向的数组中对象句柄的数量。对象句柄的最大数量为**MAXIMUM_WAIT_OBJECTS**。此参数不能为零。

### lpHandles

​	对象句柄数组。有关可以指定其句柄的对象类型的列表，请参见以下“备注”部分。该数组可以包含不同类型对象的句柄。它可能不包含同一句柄的多个副本。

​	如果在等待仍悬而未决的情况下关闭了这些句柄之一，则该函数的行为未定义。

​	句柄必须具有**SYNCHRONIZE**访问权限。有关更多信息，请参见 [标准访问权限](https://docs.microsoft.com/en-us/windows/desktop/SecAuthZ/standard-access-rights)。

### bWaitAll

​	如果此参数为**TRUE**，则当信号*lpHandles*数组中所有对象的状态时，该函数将返回。

​	如果为**FALSE**，则当任何一个对象的状态设置为已信号通知时，该函数将返回。

​	在后一种情况下，返回值指示其状态导致函数返回的对象。

### dwMilliseconds

​	超时间隔（以毫秒为单位）。如果指定了非零值，则函数将等待，直到发出指定对象的信号或间隔过去为止。如果*dwMilliseconds*为零，则如果未发出指定对象的信号，则函数不会进入等待状态；否则，函数将进入等待状态。它总是立即返回。

​	**如果*dwMilliseconds*为INFINITE，则该函数仅在发出指定对象的信号时返回。**



## 返回值

​	如果函数成功，则返回值指示导致函数返回的事件。它可以是以下值之一。（请注意，**WAIT_OBJECT_0**定义为0，**WAIT_ABANDONED_0**定义为0x00000080L。）

| 返回码/值                                                    | 描述                                                         |
| :----------------------------------------------------------- | :----------------------------------------------------------- |
| **WAIT_OBJECT_0**至（**WAIT_OBJECT_0** + *nCount* – 1）      | 如果*bWaitAll*为**TRUE**，则返回值指示所有指定对象的状态都已发出信号。如果*bWaitAll*为**FALSE**，则返回值减去**WAIT_OBJECT_0**表示满足等待条件的对象的*lpHandles*数组索引。如果在调用过程中用信号通知了多个对象，则这是信号对象的数组索引，其索引值在所有信号对象中均最小。 |
| **WAIT_ABANDONED_0**至（**WAIT_ABANDONED_0** + *nCount* – 1） | 如果*bWaitAll*为**TRUE**，则返回值指示所有指定对象的状态都已发出信号，并且至少一个对象是废弃的互斥对象。如果*bWaitAll*为**FALSE**，则返回值减去[WAIT_ABANDONED_0](https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject)表示满足等待的废弃互斥对象的*lpHandles*数组索引。互斥对象的所有权授予调用线程，并且互斥设置为无信号。如果互斥锁正在保护持久状态信息，则应检查其一致性。 |
| **WAIT_TIMEOUT**0x00000102L                                  | 超过了超时时间间隔，并且不满足*bWaitAll*参数指定的条件。     |
| **WAIT_FAILED**（**DWORD**）0xFFFFFFFF                       | 该功能失败。要获取扩展的错误信息，请调用 [GetLastError](https://docs.microsoft.com/en-us/windows/desktop/api/errhandlingapi/nf-errhandlingapi-getlasterror)。 |



# CreateSemaphore

​	winbase.h(windows.h)

​	创建一个信号量

​	创建或打开一个已命名或未命名的信号量对象



## 语法

```c++
HANDLE CreateSemaphore(
	LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
							// 指定一个LPSECURITY_ATTRIBUTES 结构，该结构通常指定安全属性
	LONG lInitia1Count,		// 设置信号量的初始计数 
    LONG lMaximumCount,		// 信号量的最大计数 
    LPCTSTR lpName			// 指定信号量对象的名称
);
```



## 参数

### lpSemaphoreAttributes

​	指向[SECURITY_ATTRIBUTES](https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/aa379560(v=vs.85)) 结构的指针。

​	如果此参数为**NULL**，则子进程不能继承该句柄。

​	结构的**lpSecurityDescriptor**成员为新信号量指定一个安全描述符。如果此参数为**NULL**，则信号量将获取默认的安全描述符。信号量的默认安全描述符中的ACL来自创建者的主令牌或模拟令牌。

### lInitialCount

​	信号量对象的初始计数。此值必须大于或等于零且小于或等于*lMaximumCount*。

​	当信号量的计数大于零时，会发出信号状态；在信号量为零时，则不会发出信号状态。

​	**每当等待函数释放一个正在等待信号量的线程时，计数就会减少一**。

​	通过调用[ReleaseSemaphore](https://docs.microsoft.com/en-us/windows/desktop/api/synchapi/nf-synchapi-releasesemaphore)函数将计数增加指定的数量 。

### lMaximumCount

​	信号量对象的最大计数。该值必须大于零。

### lpName

​	信号量对象的名称。名称限制为**MAX_PATH个**字符。名称比较区分大小写。

​	如果*lpName*与现有的命名信号对象的名称匹配，则此函数请求**SEMAPHORE_ALL_ACCESS**访问权限。在这种情况下，*lInitialCount*和*lMaximumCount*参数将被忽略，因为它们已由创建过程设置。如果*lpSemaphoreAttributes*参数不是**NULL**，则它确定是否可以继承该句柄，但是将忽略其安全描述符成员。

​	如果*lpName*为**NULL**，则创建不带名称的信号量对象。

​	如果*lpName*与现有事件，互斥体，等待计时器，作业或文件映射对象的名称匹配，则该函数将失败，并且 [GetLastError](https://docs.microsoft.com/en-us/windows/desktop/api/errhandlingapi/nf-errhandlingapi-getlasterror)函数将返回**ERROR_INVALID_HANDLE**。发生这种情况是因为这些对象共享相同的名称空间。

​	该名称可以具有“全局”或“本地”前缀，以在全局或会话名称空间中显式创建对象。名称的其余部分可以包含除反斜杠字符（\）之外的任何字符。有关更多信息，请参见 [内核对象命名空间](https://docs.microsoft.com/en-us/windows/desktop/TermServ/kernel-object-namespaces)。使用终端服务会话可实现快速的用户切换。内核对象名称必须遵循为“终端服务”概述的准则，以便应用程序可以支持多个用户。



## 返回值

​	如果函数成功，则返回值是信号量对象的句柄。

​	如果在函数调用之前存在命名的信号量对象，则该函数将返回现有对象的句柄，而 [GetLastError](https://docs.microsoft.com/en-us/windows/desktop/api/errhandlingapi/nf-errhandlingapi-getlasterror)将返回**ERROR_ALREADY_EXISTS**。

​	如果函数失败，则返回值为**NULL**。要获取扩展的错误信息，请调用[GetLastError](https://docs.microsoft.com/en-us/windows/desktop/api/errhandlingapi/nf-errhandlingapi-getlasterror)。



# ReleaseSemaphore

​	windows.h（synchapi.h）

​	增加信号量（hSemaphore）的值，类似于PV操作中的V

​	将指定的信号量对象的计数增加指定的数量。



## 语法

```c++
BOOL ReleaseSemaphore(
	HANDLE hSemaphore,			// 要操作的信号量对象的句柄
	LONG lReleaseCount,			// 以当前为基础，信号量对象要增加的值
	LPLONG lpPreviousCount		// 信号量变化前值的指针
)
```

​	

## 参数

### hSemaphore

​	信号量对象的句柄。该 [CreateSemaphore](https://docs.microsoft.com/en-us/windows/desktop/api/winbase/nf-winbase-createsemaphorea)或 [OpenSemaphore](https://docs.microsoft.com/en-us/windows/desktop/api/winbase/nf-winbase-opensemaphorea)函数返回该句柄。

​	该句柄必须具有**SEMAPHORE_MODIFY_STATE**访问权限。有关更多信息，请参见 [同步对象安全性和访问权限](https://docs.microsoft.com/en-us/windows/desktop/Sync/synchronization-object-security-and-access-rights)。

### lReleaseCount

​	信号量对象的当前计数要增加的数量。该值必须大于零。

​	如果指定的数量将导致信号量的计数超过创建信号量时指定的最大计数，则该计数不会更改，函数将返回**FALSE**。

### lpPreviousCount

​	指向变量的指针，以接收信号量的先前计数。如果不需要上一个计数，则此参数可以为**NULL**。



## 返回值

​	如果函数成功，则返回值为非零。

​	如果函数失败，则返回值为零。要获取扩展的错误信息，请调用[GetLastError](https://docs.microsoft.com/en-us/windows/desktop/api/errhandlingapi/nf-errhandlingapi-getlasterror)。



# CloseHandle

​	process.h

​	关闭指定句柄的对象

```
BOOL WINAPI CloseHandle(
	HANDLE hObject			// 要关闭的对象的句柄
);
```



