# Philosophers
A multithreading solution to the classic Dining Philosophers problem, avoiding deadlocks and data races.

---

## 📌 Key Notes & Advice
	⚠️ Critical Testing Guidelines

	kjdfsdkfkjs
- Avoid -fsanitize=thread + Valgrind (--tool=helgrind)
	- These tools slow thread creation and may falsely report philosopher deaths.
	- Use them separately for data race/deadlock detection, but never together.

- Thread Count Limits
	- CPU-bound tasks: Aim for threads ≈ CPU cores.
	- I/O-bound tasks: Up to 200 philosophers (per project constraints).
	- Do not exceed 200 philosophers (subject requirement).

- Death Monitor Optimization

	- Add a small delay  in the death-checking loop to prevent CPU waste from tight loops.
    - Avoid false positives (checking last_meal right before it updates).

- Debugging Hangs
    - Mutex locks/unlocks (ensure all paths release locks).


## 🛠️ Testing
1. Data Races & Deadlocks
bash

# Compile with thread sanitizer (avoid during normal runs)  
gcc -fsanitize=thread -g *.c -o philo  

# Run with Valgrind (separately!)  
valgrind --tool=helgrind ./philo 5 800 200 200 7  

Expected: No reported data races or deadlocks.
2. Philosopher Death Timing
bash

# Philosopher should die after ~400ms  
./philo 1 400 200 200  

# No deaths (enough time to eat)  
./philo 2 800 200 200 2  

3. Thread Limits
bash

# Test upper limit (200 threads)  
./philo 200 800 200 200  

# Edge case: 1 philosopher (will die)  
./philo 1 800 200 200  

4. Performance Stress Test
bash

time ./philo 150 800 200 200  # Monitor CPU usage  