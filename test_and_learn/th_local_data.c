#include <stdio.h> // printf
#include <stdlib.h> //malloc
#include <pthread.h>
#include <unistd.h>



int *value;

void *thread_func(void *arg) {
    int x = 42;
    value = &x;
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    pthread_join(thread, NULL);
    printf("%d\n", *value); // UNDEFINED - x no longer exists
    return 0;
}