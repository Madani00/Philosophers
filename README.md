# philosofers

## notes
- CFLAGS = -Wall -Werror -Wextra -pthread -g -fsanitize=thread
- valgrind --tool=helgrind ./philo
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

## tests to handle
3 600 200 100
200 120 60 60
199 180 60 60
3 190 60 60 . where no philo should die
3 200 60 60 
5 800 200 200. No philosopher should die

## start simulation



#### **b. Synchronize Threads**
Ensure all threads are ready before starting the simulation. You can use a barrier or a shared flag (`all_threads_ready`) to synchronize.

#### **c. Monitor Philosopher States**
Create a monitoring thread to check if any philosopher has died or if all have eaten the required number of meals. This thread will set `end_simulation` to `true` when the simulation should stop.

#### **d. Join Threads**
After the simulation ends, join all philosopher threads to ensure proper cleanup.


```

---

### **5. Next Steps**
1. Implement the philosopher routine (`philosopher_routine`) to handle the "thinking," "eating," and "sleeping" states.
2. Add a monitoring thread to check for starvation or completion.
3. Test your program with different numbers of philosophers and meal limits to ensure correctness and avoid deadlocks.

Let me know if you need help with any specific part!






### **Explanation**
- In the original code, `philos` in `main` is a local variable, and passing it to `initialize` does not allow the function to modify the pointer itself (only the memory it points to).
- By passing `t_philo **philos` to `initialize`, you allow the function to modify the pointer in `main` by dereferencing it (`*philos`).
- This ensures that the memory allocated for `philos` is correctly accessible in `main` and other functions.

## understand
- pthread_create(&thr1, NULL, &hi, NULL);       // every thread we call have its own 'hi' function 