# philosofers

## notes
- CFLAGS = -Wall -Werror -Wextra -pthread -g -fsanitize=thread
- valgrind --tool=helgrind ./philo
- A common guideline is to have a number of threads roughly equal to the number of CPU cores for CPU-bound tasks. For I/O-bound tasks, you might have more threads, but 150 is still quite high.
- NORE SURE: everytime philosopher eats you need to update his last meal time , in his campus people say as soon as the philo takes both forks

##  Resource Hierarchy (Ordering of Resource Acquisition):
- THIS IS MY SOLUTION TO PREVENT DEADLOCKS (odd and even)

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

## Concurrent Execution

Threads don't necessarily run "at the same time" in the strictest sense (unless you have multiple CPU cores). Instead, the OS scheduler rapidly switches between them, giving the illusion of parallel execution.



## Similarity between Threads and Processes –
- Only one thread or process is active at a time
- Within process both execute sequentiall
- Both can create children

## Types of Threads:
- 1- User Level thread :
- 2- Kernel Level Thread :

## concurrency & Parallelism:

- **concurrency** (Threading): CPU switches between different threads really fast, giving a falsehood of concurrency. Keypoint: only one thread is running at any given time. When one thread is running, others are blocked. You might think, how is this any useful than just running procedurally? Well, think of it as a priority queue. Threads can be scheduled. CPU scheduler can give each thread a certain amount of time to run, pause them, pass data to other threads, then give them different priorities to run at a later time. It's a must for not instant running processes that interact with each other. It's used in servers extensively: thousands of clients can request something at the same time, then getting what they requested at a later time (If done procedurally, only one client can be served at a time). Philosophy: do different things together. It doesn't reduce the total time (moot point for server, because one client doesn't care other clients' total requests).
- **Parallelism**: threads are running parallel, usually in different CPU core, true concurrency. Keypoint: multiple threads are running at any given time. It's useful for heavy computations, super long running processes. Same thing with a fleet of single core machines, split data into sections for each machine to compute, pool them together at the end. Different machines/cores are hard to interact with each other. Philosophy: do one thing in less time.

## Hyper-threading definition
Hyper-threading is a process by which a CPU divides up its physical cores into virtual cores that are treated as if they are actually physical cores by the operating system. These virtual cores are also called threads.

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
- - POSIX C Rules for making OSes behave like Unix (standards consisting of libraries, macros, system call, threading functions).
- - SUS (Single UNIX Specification) → A strict certification for "real Unix" systems.
- GNU (linux kernel + gnu tools) → is an operating system that is free software, it consists of GNU packages (programs specifically released by the GNU Project) , is a project aiming to create a completly free operationg system
## Bonus Fact:

- Threads are lighter than processes (faster to create/destroy).
- Threads share code, data, and files but have independent registers and stacks.
- the scheduler may decided to run Thread 2 first even though Thread 1 was created earlier
- printf uses buffered output by default. Without synchronization, output can appear corrupted or missing
-  pthread_create(&thr1, NULL, &hi, NULL);       // every thread we call have its own 'hi' function
-  Normal thread Termination is  function 'hi' completes execution and returns (NULL).
- Each thread has its own stack: if you have a
locally-allocated variable inside of some function a thread is exe-
cuting, it is essentially private to that thread; no other thread can
(easily) access it. To share data between threads, the values must be
in the heap or otherwise some locale that is globally accessible.


## Synchronisation tricks
```c
	if (ph->id % 2 == 0)
		ft_usleep(ph->pa->eat / 10);
```
```c
if (p->id & 1)
   ft_usleep(p->par->t2e * 0.9 + 1);

# Possible delayed times are `time2eat * 0.5` or `time2eat * 0.9 + 1`,
# respectively waiting until the first batch is halfway through their meal,
# or until they're 99% done with their meal

```

## why monitor sleeps a certain time
- monitor constantly checking if any philosopher has died. this can cause a problem :
1 - CPU Overhead – The loop runs too fast, wasting CPU cycles.
2- Race Conditions – If the monitor checks philo->last_meal right before a philosopher updates it, it might falsely detect death even though the philosopher just ate.

- . Potential Downsides
- If time_die is very small, the monitor might still miss deaths.
- If philosophers take too long to eat, the monitor could delay detecting death.

# even & odd philos why die?
## for even numbers system is fair
./philo 4 800 200 350
if (nmb_philo == even && (time_eat <= time_sleep))
	time_think == 0;

./philo 4 800 200 100
if (nmb_philo == even && (time_eat > time_sleep))
	time_think == time_eat - time_sleep;

## for odd numbers system is NOT

./philo 3 800 200 200
if (nmb_philo == odd && (time_eat == time_sleep))
	time_think == time_eat;

./philo 3 800 200 300
if (nmb_philo == odd && (time_eat < time_sleep))
	time_think == time_eat * 2 - time_sleep;

./philo 3 800 200 100
if (nmb_philo == odd && (time_eat > time_sleep))
	time_think == time_eat * 2 - time_sleep;

# tests
- ./philo 4 -500 200 200	   Invalid argument
- ./philo 30 2.25 6.51 81 2        Invalid argument
- ./philo 30 2lsdf 60 81          Invalid argument
- ./philo 4 0 200 200	Invalid argument (zero time).
- ./philo 4 214748364732 200 200	Invalid argument

- ./philo 3 600 200 100         No one dies.
- ./philo 200 120 60 60        No one dies (hard test)
- ./philo 199 180 60 60        No one dies.
- ./philo 3 190 60 60          No one dies.
- ./philo 5 800 200 200        No one dies.
- ./philo 4 410 200 200       No one dies (try 405)
- ./philo 200 410 200 200       No one die
- ./philo 4 2147483647 200 200         No one dies.

- ./philo 1 200 200 200	   Philosopher 1 picks one fork and dies after 200ms.
- ./philo 5 800 200 200 7	  Simulation stops after each philosopher eats 7 times.
- ./philo 4 310 200 200	        One philosopher dies.
- ./philo 4 500 200 2147483647	One philosopher dies after 500 ms.
- ./philo 4 200 210 200	        One philosopher dies; death must be printed before 210 ms.
- ./philo 5 800 600 100         should die
- ./philo 200 122 60 60        should die (mine works great)
- ./philo 2 600 500 200         should die mmm
- ./philo 2 310 200 100          mmm why is dies
- WARNING : -g -fsanitize=thread may hangs your program.


