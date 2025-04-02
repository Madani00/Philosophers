#include <stdio.h> // printf
#include <stdlib.h> //malloc
#include <pthread.h>
#include <unistd.h>

typedef struct s_info t_info;

typedef struct s_philo
{
	int id;
	long meals_counter;
	bool full; // if the philo eats all the the meals required]
	long last_meal_time; // time passed from last meal (long ; bc we are using microsecond)
	t_fork *left; // pointer to left fork
	t_fork *right;
	pthread_t thread_id; // philo is a thread
	t_info *infos; // so that a philo can access all the data
} t_philo;

typedef struct s_fork
{
	pthread_mutex_t fork;
	int fork_id; // useful for debugging
} t_fork;


// contains information ./philo 5 800 200 200 [5]
struct s_info
{
	long nmb_philo;
	long time_die;
	long time_sleep;
	long time_eat;
	long limit_meals; // [5] } flag if -1 then it is not provided
	long start_simulation; // all philos will have a timestamps starting from this value
	bool end_simulation; // turn on, when a philo dies or all philos are full
	t_fork *forks; // array to all forks [f, f ,f ,f ,f]
	t_philo *philos;
};
