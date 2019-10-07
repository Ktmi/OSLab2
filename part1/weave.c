#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int SharedVariable = 0;
#ifdef PTHREAD_SYNC
pthread_mutex_t sharedMutex;
#endif
void * SimpleThreads(void * which){
	int num, val;
	for(num = 0; num < 20; num++){
		#ifdef PTHREAD_SYNC
		pthread_mutex_lock(&sharedMutex);
		#endif
		if(random() > RAND_MAX / 2)
			usleep(10);
		val = SharedVariable;
		printf("*** thread %d sees value %d\n", *((int *) which), val);
		SharedVariable = val + 1;
		#ifdef PTHREAD_SYNC
		pthread_mutex_unlock(&sharedMutex);
		#endif
	}
	val = SharedVariable;
	printf("Thread %d sees final value %d\n", *((int *) which), val);
}

int main(int ac, char ** argv)
{
	if (ac != 2)
	{
		printf("Input too long.\n");
		return 1;
	}
	char *ptr = NULL;
	int threadCount = strtol(argv[1], &ptr, 10); 
	if(ptr[0] != '\0')
	{
		printf("Input invalid.\n");
		return 1;
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
