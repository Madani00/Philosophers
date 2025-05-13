# philosofers

## notes
- CFLAGS = -Wall -Werror -Wextra -pthread -g -fsanitize=thread
- valgrind --tool=helgrind ./philo
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
**Processes** are isolated and safer but slow to create. (process includes the resources the program needs to run, they are managed by the operation system {exp: processor registers, program counters, stack pointers , memory pages})
**Threads** are faster and share data easily but risk crashing the whole process.
- thread : (is a unit of execution within a process), they share memory address space , they have same properties as of the process so they are called as light weight processes.  {exp: processor registers.. }

## how OS run a thread or process on CPU?
- handled by `context switching`, one process is switched out of CPU so another process can run.
- OS stored the state of the currect runnig process so it can execute a later point
- context switching is expensive 

## Similarity between Threads and Processes –
- Only one thread or process is active at a time
- Within process both execute sequentiall
- Both can create children

## Types of Threads:
- 1- User Level thread : 
- 2- Kernel Level Thread : 
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
A mutex  is a synchronization primitive used to protect shared resources from simultaneous access by multiple threads. It ensures that only one thread can access a critical section at a time, preventing race conditions.


## idk if i have to check them or NO
./philo 4 390 200 200  (if 390 < 200 + 200 propably someone is gonna die)
arguable depends on campus : everytime philo eats you need to update his last meal time, as soon as he takes both forks

## what is POSIX
- Unix → The original OS (old operating system).
- Linux → A free, Unix-like OS, Ubuntu, Fedora .. (not Unix, just was inspired by it).
- - POSIX → Rules for making OSes behave like Unix (standards consisting of libraries, macros, system call, threading functions).
- - SUS (Single UNIX Specification) → A strict certification for "real Unix" systems.

## Bonus Fact:

- Threads are lighter than processes (faster to create/destroy).
- Threads share code, data, and files but have independent registers and stacks.
- the scheduler may decided to run Thread 2 first even though Thread 1 was created earlier
