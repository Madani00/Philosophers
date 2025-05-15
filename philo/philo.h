#ifndef PHILO_H
#define PHILO_H

#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>

// contains information ./philo 5 800 200 200 [5]
typedef struct s_info
{
	int nmb_philo;
	long time_die;
	long time_sleep;
	long time_eat;
	long limit_meals; // [5] } flag if -1 then it is not provided
	long start_simulation; // all philos will have a timestamps starting from this value
	bool end_simulation; // turn on, when a philo dies or all philos are full MOnitor

	bool all_threads_ready; // new u just added it (It can be used to ensure all philosopher threads are initialized before the simulation begins, potentially preventing race conditions during setup.)
	pthread_mutex_t mutex; // avoid races while reading from infos
	pthread_mutex_t *forks; // array to all forks [f, f ,f ,f ,f]
} t_info;

// idea : add the state of a philo, you may want to track the state , thinking , sleeping, for debugging .
typedef struct s_philo
{
	int id;
	long meals_counter;
	bool philo_full; // if the philo eats all the the meals required]
	long last_meal_time; // time passed from last meal (long ; bc we are using microsecond) , usefull to checking if a philosopher has starved
	pthread_mutex_t *left_fork; // A pointer to the mutex representing the philosopher's left fork.
	pthread_mutex_t *right_fork;
	pthread_t thread_id; // Stores the thread ID of the philosopher
	t_info *infos; // so that a philo can access all the data
} t_philo;

int	ft_strlen(char *str);
long	ft_atoi(const char *str);
int	ft_isnum(char *str);
int is_space(char *str);
int num_length(char *str);
int check_args(int ac, char **av);
void check_inputs(t_info *info, char **av);
int check_numeric(int ac, char **av);



#endif
