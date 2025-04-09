#include <stdio.h> // printf
#include <stdlib.h> //malloc
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

typedef struct s_info t_info;

typedef struct s_philo
{
	int id;
	long meals_counter;
	bool full; // if the philo eats all the the meals required]
	long last_meal_time; // time passed from last meal (long ; bc we are using microsecond)
	t_fork *left_fork; // pointer to left fork
	t_fork *right_fork; // change it to if you want : pthread_mutex_t righ_fork;
	pthread_t thread_id; // philo is a thread
	struct t_info *infos; // so that a philo can access all the data
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
	bool all_threads_ready; // new u just added it
	pthread_mutex_t mutex; // avoid races while reading from infos
	t_fork *forks; // array to all forks [f, f ,f ,f ,f]
	t_philo *philos;

	int is_dead; // you may need it madani
};



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
