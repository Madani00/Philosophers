#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


int counter = 0;
pthread_mutex_t lock;

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    return NULL;
}
// how to create threads in a loop
int main() {
    pthread_t t1[4];

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    for (int i = 0; i < 4; i++)
	{
		pthread_create(&t1[i], NULL, increment, NULL);
		printf("thread %d had started\n", i);
	}

	for (int i = 0; i < 4; i++)
	{
		pthread_join(t1[i], NULL);
		printf("%d has ended\n", i);
	}

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    printf("Final counter value: %d\n", counter);  // Expected: 200000
    return 0;
}
