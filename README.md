# philosofers

## notes
- CFLAGS = -Wall -Werror -Wextra -pthread -g -fsanitize=thread
- 150 threads is a lot.
A common guideline is to have a number of threads roughly equal to the number of CPU cores for CPU-bound tasks. For I/O-bound tasks, you might have more threads, but 150 is still quite high.
## tester
https://github.com/AbdallahZerfaoui/42PhilosophersHelper

# data races
when two treaths changes the value of something in memory , the first one reach 10 , and the second was slow so he overwrite the to 3
