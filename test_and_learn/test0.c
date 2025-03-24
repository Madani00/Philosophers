#include <stdio.h> // printf
#include <stdlib.h> //malloc
#include <pthread.h>
#include <unistd.h>


void *test()
{
	printf("just testing how this work\n");
}

int main()
{
	pthread_t dd;
	pthread_create(&dd, NULL, &test, NULL);
	pthread_join(dd, NULL); // basically like wait
}
