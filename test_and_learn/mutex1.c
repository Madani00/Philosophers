#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


int counter = 0;             // Shared resource
pthread_mutex_t lock;        // Mutex variable

void* increment(void* arg)
{
    for (int i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&lock);    // Lock before accessing the shared resource, If another thread already holds it, the calling thread waits until it’s released.
        counter++;                    // Critical section
        pthread_mutex_unlock(&lock);  // Unlock after access, allowing other threads to acquire it.
    }
    return (NULL);
}

int main() {
    pthread_t t1, t2;

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    // Create two threads
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    printf("Final counter value: %d\n", counter);  // Expected: 200000
    return 0;
}

