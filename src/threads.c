#include <pthread.h>

static pthread_attr_t cweb_thread_attr;

void *thread_function (void *arg)
{
}

pthread_t
cweb_create_thread ((void *)thread_routine)
{
	int retval = 0;
	pthread_t thread;
	retval = pthread_create(&thread, NULL, thread_routine, NULL);
	if (retval != 0)
		return NULL;
	else
		return &thread;
}
