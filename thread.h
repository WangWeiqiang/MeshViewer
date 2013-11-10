#include <stdio.h>
#include <windows.h>
#ifndef __THREAD__H_
#define __THREAD__H_
class Thread
{
	public:
	Thread();
	virtual ~Thread();
	int start (void * = NULL);
	void stop();
	void sleep (int);
	void detach();
	void * wait();
	protected:
	virtual void * run(void *) = 0;
	private:
	HANDLE  handle;
	bool started;
	bool detached;
	void * threadFuncParam;
	friend void * threadFunc(void *);
	};
	static void * threadFunc(void *); 
#endif