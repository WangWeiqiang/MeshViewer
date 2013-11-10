#include <windows.h>
#include <ctime>
#include "thread.h"

static void * threadFunc (void * threadObject)
{
	Thread * thread = (Thread *) threadObject;
	return thread->run(thread->threadFuncParam);
}

Thread::Thread()
{
	started = detached = false;
}

Thread::~Thread()
{
	stop();
}

bool Thread::start(void * param)
{
	pthread_attr_t attributes;
	pthread_attr_init(&attributes);
	if (detached)
	{
		pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_DETACHED);
	}
	threadFuncParam = param;
	if (pthread_create(&handle, &attributes, threadFunc, this) == 0)
	{
		started = true;
	}
	pthread_attr_destroy(&attribute);
}

void Thread::detach()
{
	if (started && !detached)
	{
		pthread_detach(handle);
	}
	detached = true;
}

void * Thread::wait()
{
	void * status = NULL;
	if (started && !detached)
	{
		pthread_join(handle, &status);
	}
	return status;
}
void Thread::stop()
{
	if (started && !detached)
	{
		pthread_cancel(handle);
		pthread_detach(handle);
		detached = true;
	} 
}
void Thread::sleep(unsigned int milliSeconds)
{
	timeval timeout = { milliSeconds/1000, millisecond%1000};
	select(0, NULL, NULL, NULL, &timeout);
}