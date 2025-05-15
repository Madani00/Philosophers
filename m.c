

#include <stdio.h> // printf
#include <stdlib.h> //malloc
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

typedef struct s_info t_info;

typedef struct s_philo
{
	int id;
	long meals_counter;
	bool philo_full; // if the philo eats all the the meals required]
	long last_meal_time; // time passed from last meal (long ; bc we are using microsecond) , usefull to checking if a philosopher has starved
	pthread_mutex_t *left_fork; // A pointer to the mutex representing the philosopher's left fork.
	pthread_mutex_t *right_fork;
	pthread_t thread_id; // Stores the thread ID of the philosopher
	//t_info *infos; // so that a philo can access all the data
} t_philo;





int main()
{
    t_philo philo;
	philo.philo_full = true;
    memset(&philo, 0, sizeof(t_philo));

    printf("%d %ld %d %ld %p %p %lu \n", philo.id , philo.meals_counter, philo.philo_full, philo.last_meal_time, philo.left_fork, philo.right_fork, philo.thread_id);
}