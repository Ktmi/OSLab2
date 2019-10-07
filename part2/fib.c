#include <pthread.h>
#include <stdio.h>

int sum;
int outArr[1024];
void *runner(void *param);

int main(int argc, char *argv[])
{
	pthread_t tid;
	pthread_attr_t attr;
	if (argc != 2)
	{
		fprintf(stderr,"usage: a.out <integer value>\n");
		return -1;
	}
	if (atoi(argv[1]) < 0)
    {
        fprintf(stderr,"%d must be >= 0\n", atoi(argv[1]));
        return -1;
    }
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, argv[1]);
    pthread_join(tid, NULL);
    printf("sum = %d\n",sum);
}

void *runner(void *param)
{
    int i, upper = atoi(param);
    outArr[0] = 0;
    outArr[1] = 1;
    for (i = 2; i <= upper; i++)
        outArr[i] = outArr[i - 1] + outArr[i - 2];
    pthread_exit(0);
}