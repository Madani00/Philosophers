<div align="center">
	
# Philosophers

</div>

A multithreading solution to the classic Dining Philosophers problem, avoiding deadlocks and data races.

<div align="center">
  <img src="https://www.digikey.fi/maker-media/e8113528-f967-4389-82f2-221519a6509a.jpg" alt="42">
</div>

---

<div align="center">

## 📌 Key Notes & Advice

</div>


### 1. Avoid -fsanitize=thread + Valgrind (--tool=helgrind)
	- These tools slow thread creation and may falsely report philosopher deaths.
	- Use them separately for data race/deadlock detection, but never together.

### 2. Thread Count Limits
	- CPU-bound tasks: Aim for threads ≈ CPU cores.
	- I/O-bound tasks: Up to 200 philosophers (per project constraints).
	- Do not exceed 200 philosophers (subject requirement).

### 3. Death Monitor Optimization

	- Add a small delay  in the death-checking loop to prevent CPU waste from tight loops.
    - Avoid false positives (checking last_meal right before it updates).

### 4. Debugging Hangs
    - Mutex locks/unlocks (ensure all paths release locks).

<div align="center">

## 🛠️ Testing

</div>

### Invalid argument tests
```bash
./philo 4 -500 200 200	  
./philo 30 2.25 6.51 81 2   
./philo 30 2lsdf 60 81 
./philo 4 "" 200 200
./philo 4 214748364732 200 200
```

### No deaths (enough time to eat)
```bash
./philo 200 130 60 60   
./philo 199 190 60 60     
./philo 3 190 60 60             
./philo 4 405 200 200       
./philo 4 410 200 200      
./philo 200 410 200 200      
./philo 5 610 200 400			
./philo 3 310 100 200		
./philo 4 2147483647 200 200   
./philo 155 190 60 120
./philo 3 610 200 100
```

### Philosopher should die
```bash
./philo 2 310 200 100        
./philo 1 200 200 200	  # edge case
./philo 4 310 200 200	     
./philo 4 500 200 2147483647
./philo 4 200 210 200	     
./philo 5 800 600 100        
./philo 2 600 500 200        
./philo 2 310 200 100        
./philo 4 310 200 100      
```
