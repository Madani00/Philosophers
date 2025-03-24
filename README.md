# philosofers

## notes
- CFLAGS = -Wall -Werror -Wextra -pthread -g -fsanitize=thread
- 150 threads is a lot.
A common guideline is to have a number of threads roughly equal to the number of CPU cores for CPU-bound tasks. For I/O-bound tasks, you might have more threads, but 150 is still quite high.
## tester
https://github.com/AbdallahZerfaoui/42PhilosophersHelper

## Difference between processes and threads
**Processes** are isolated and safer but slow to create.
**Threads** are faster and share data easily but risk crashing the whole process.

## Race Conditions
- in threads happens when multiple threads access and manipulate shared data at the same time, and the final result depends on the timing of thread execution. This leads to unpredictable and incorrect results.
- when the number is small the first thread finishes then the second one starts so nothing happend comparing a grand number

## How to Prevent Race Conditions:
Mutexes (Mutual Exclusions): Lock the shared resource so only one thread can access it at a time.

Semaphores: Control access to shared resources with counters.

Atomic Operations: Ensure that the entire operation is done without interruption.

Thread Synchronization: Use synchronization primitives (like condition variables) to control the execution order.

## What is a mutex in C? (pthread_mutex)

