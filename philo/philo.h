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


typedef struct s_info
{
	int nmb_philo;
	long time_die;
	long time_sleep;
	long time_eat;
	long limit_meals;
	long start_simulation;
	bool end_simulation;

	bool all_threads_ready;
	pthread_mutex_t mutex; 
	pthread_mutex_t *forks; 
} t_info;

// idea : add the state of a philo, you may want to track the state , thinking , sleeping, for debugging.
typedef struct s_philo
{
	int id;
	long meals_counter;
	bool philo_full;
	long last_meal_time;
	pthread_mutex_t *left_fork; 
	pthread_mutex_t *right_fork;
	pthread_t thread_id; 
	t_info *infos;
} t_philo;

int	ft_strlen(char *str);
long	ft_atoi(const char *str);
int	ft_isnum(char *str);
int is_space(char *str);
int num_length(char *str);
int check_args(int ac, char **av);
int check_inputs(t_info *info, char **av);
int check_numeric(int ac, char **av);


#endif
