#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int SharedVariable = 0;
#ifdef PTHREAD_SYNC
pthread_mutex_t sharedMutex;
#endif

void * SimpleThreads(void * which);

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		fprintf(stderr,"usage: ./weave.out <integer value>\n");
		return -1;
	}
	char *ptr = NULL;
	int threadCount = strtol(argv[1], &ptr, 10); 
	if(threadCount < 0 | ptr[0] != '\0')
	{
		fprintf(stderr,"%d must be an integer >= 0\n", atoi(argv[1]));
        return -1;
	}
	printf("Initiating %d threads.\n",threadCount);
	pthread_t threads[threadCount];
	int thread_args[threadCount];
	int num;
	for(num = 0; num < threadCount; num++)
	{
		thread_args[num] = num;
		pthread_create(&threads[num], NULL, SimpleThreads, &thread_args[num]);
	}
	
	for(num = 0; num < threadCount; num++)
	{
		pthread_join(threads[num], NULL);
	}
	
	return 0;
}

void * SimpleThreads(void * which)
{
	int num, val;
	for(num = 0; num < 20; num++)
	{
		if(random() > RAND_MAX / 2)
			usleep(10);
		#ifdef PTHREAD_SYNC              //If enabled
		pthread_mutex_lock(&sharedMutex);//Lock access to resource
		#endif
		val = SharedVariable;
		printf("*** thread %d sees value %d\n", *((int *) which), val);
		SharedVariable = val + 1;
		#ifdef PTHREAD_SYNC
		pthread_mutex_unlock(&sharedMutex);//When done, unlock access
		#endif
	}
	val = SharedVariable;
	printf("Thread %d sees final value %d\n", *((int *) which), val);
}