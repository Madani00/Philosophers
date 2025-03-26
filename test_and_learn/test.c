#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void* increment() {
	int *res;
	res = malloc(4);
	*res = 5;
    return (void *)res;
}

int main() {
    pthread_t t1;
	int *value;
	pthread_create(&t1, NULL, increment, NULL);

	pthread_join(t1, (void *)&value);

    printf("the returned value: %d\n", *value);
    return 0;
}
