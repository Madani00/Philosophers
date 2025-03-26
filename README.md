# philosofers

## notes
- CFLAGS = -Wall -Werror -Wextra -pthread -g -fsanitize=thread
- 150 threads is a lot.
- A common guideline is to have a number of threads roughly equal to the number of CPU cores for CPU-bound tasks. For I/O-bound tasks, you might have more threads, but 150 is still quite high.
- NORE SURE: everytime philosopher eats you need to update his last meal time , in his campus people say as soon as the philo takes both forks

## some ways to implement you program
1 - odd sleep (time_to_eat / 2) (you need to make the philos sleep at the start of yr program) (when you have even number of philos 4 , it is easy cause the 1 and 3 eats, 2 and 4 sleeps vice versa)
2 - odd start taking from right fork, even start taking from left fork (to prevent deadlock )
3 - all philosophers take from right fork, except for the last one.
## tester
https://github.com/AbdallahZerfaoui/42PhilosophersHelper

## Difference between processes and threads
**Processes** are isolated and safer but slow to create.
**Threads** are faster and share data easily but risk crashing the whole process.

## Race Conditions
- in threads happens when multiple threads access and manipulate shared data at the same time, and the final result depends on the timing of thread execution. This leads to unpredictable and incorrect results.
- can only happen on multi-core processor , very unlikely to encounter it on a single-core processor
- when the number is small the first thread finishes then the second one starts so nothing happend comparing a grand number

## How to Prevent Race Conditions:
Mutexes (Mutual Exclusions): Lock the shared resource so only one thread can access it at a time.

Semaphores: Control access to shared resources with counters.

Atomic Operations: Ensure that the entire operation is done without interruption.

Thread Synchronization: Use synchronization primitives (like condition variables) to control the execution order.

## What is a mutex in C? (pthread_mutex)

## Get return value from a thread (pthread_join)
```bash
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
```
