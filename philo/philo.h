#include <stdio.h> // printf
#include <stdlib.h> //malloc
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>


typedef struct s_philo
{
	int id;
	long meals_counter;
	bool philo_full; // if the philo eats all the the meals required]
	long last_meal_time; // time passed from last meal (long ; bc we are using microsecond) , usefull to checking if a philosopher has starved
	pthread_mutex_t *left_fork; // A pointer to the mutex representing the philosopher's left fork.
	pthread_mutex_t *right_fork;
	pthread_t thread_id; // Stores the thread ID of the philosopher
	struct t_info *infos; // so that a philo can access all the data
} t_philo;


// contains information ./philo 5 800 200 200 [5]
typedef struct s_info
{
	int nmb_philo;
	long time_die;
	long time_sleep;
	long time_eat;
	long limit_meals; // [5] } flag if -1 then it is not provided
	long start_simulation; // all philos will have a timestamps starting from this value
	bool end_simulation; // turn on, when a philo dies or all philos are full

	bool all_threads_ready; // new u just added it (It can be used to ensure all philosopher threads are initialized before the simulation begins, potentially preventing race conditions during setup.)
	pthread_mutex_t mutex; // avoid races while reading from infos
	pthread_mutex_t *forks; // array to all forks [f, f ,f ,f ,f]
	t_philo *philos;

} t_info;




















// i think about this way to do it
typedef struct s_philos
{
	int				id;
	pthread_t		thread;
	size_t			num_philos;
	pthread_mutex_t	*mealtex;
	pthread_mutex_t	*eatentex;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			last_meal;
	int				sleep;
	int				eaten;
	int				*dead;
	struct s_table	*table;
}				t_philos;

typedef struct s_table
{
	pthread_t		table;
	t_philos		*philos;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*deadtex;
	pthread_mutex_t	*eatentex;
	pthread_mutex_t	*forks;
	int				num_of_meals;
	unsigned long	time;
	int				dead_flag;
}				t_table;
