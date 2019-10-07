#include <pthread.h>
#include <stdio.h>

long long sum;
long long outArr[1024];
void *runner(void *param);

int main(int argc, char *argv[])
{
	pthread_t tid;
	pthread_attr_t attr;
	if (argc != 2)
	{
		fprintf(stderr,"usage: fib.out <integer value>\n");
		return -1;
	}
    char *ptr = NULL;
	int upper = strtol(argv[1], &ptr, 10); 
	if (upper < 0 | ptr[0] != '\0')
    {
        fprintf(stderr,"%d must be an integer >= 0\n", atoi(argv[1]));
        return -1;
    }
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, argv[1]);
    pthread_join(tid, NULL);
    printf("Final fib = %lld\n",sum);
    int index = 0;
    for (index = 0; index <= upper; index++)
    {
        printf("Fib[%d] = %lld\n",index, outArr[index]);
    }
}

void *runner(void *param)
{
    int i, upper = atoi(param);
    outArr[0] = 0;
    outArr[1] = 1;
    for (i = 2; i <= upper; i++)
        sum = outArr[i] = outArr[i - 1] + outArr[i - 2];
    pthread_exit(0);
}