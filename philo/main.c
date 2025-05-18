/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:18:08 by eamchart          #+#    #+#             */
/*   Updated: 2025/05/18 11:39:55 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void clean_up(t_philo *philo, t_info *info)
{
	int i;

	i = 0;
	while (i < philo->infos->nmb_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	free(philo);
	free(info->forks);
}
// right fork = philo_id - 1 (philo position in the array) = 4
// left fork = [philo_position + 1] % philo_nmb = [4 + 1] % 5 = 0



// 1 - // [philo_pos = 0, philo->id = 1]  // [ l=(f) , r=(f) ,f ,f ,f]
// 2 - // [philo_pos = 1, philo->id = 2]  // [ f , r=(f) , l=(f) ,f ,f]
// 3 - // [philo_pos = 2, philo->id = 3]  // [ f, f , l=(f) , r=(f) ,f]
// 4 - // [philo_pos = 3, philo->id = 4]  // [ f , f , f , r=(f) , l=(f)]
// 5 - // [philo_pos = 4, philo->id = 5]  // [ r=(f) , f ,f ,f ,l=(f)]
void init_forks(t_philo *philo, pthread_mutex_t *forks, int philo_pos)
{
	int philo_nb;

	philo_nb = philo->infos->nmb_philo;   
	// deadlock problem here
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &forks[philo_pos];
		philo->left_fork = &forks[(philo_pos + 1) % philo_nb];
	}
	else
	{					                                       
		philo->right_fork = &forks[(philo_pos + 1) % philo_nb];
		philo->left_fork = &forks[philo_pos];
	}
}


void init_philo(t_info *info, t_philo *philo)
{
	int i;

	i = 0;
	while (i < info->nmb_philo)
	{
		philo[i].infos = info;
		philo[i].id = i + 1;
		philo[i].philo_full = false;
		philo[i].meals_counter = 0;
		init_forks(&philo[i], info->forks, i); // i position in the table , [f, f ,f ,f ,f]
		i++;
	}
}

t_philo * initialize(t_info *info)
{
	int i;
	t_philo *philos;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nmb_philo);
	philos = malloc(sizeof(t_philo) * info->nmb_philo);
	if (!info->forks || !philos)
		return (NULL);
	pthread_mutex_init(&info->mutex, NULL);
	while (i < info->nmb_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	init_philo(info, philos);
	return (philos);
}
bool get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool res;

	pthread_mutex_lock(mutex);
	res = *value; // reading safe
	pthread_mutex_unlock(mutex);
	return (res);
}


long	current_time(void)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	return (s_time.tv_sec * 1000 + s_time.tv_usec / 1000);
}

void wait_all_threads(t_info *info)
{
	// if the thread are not ready keep waiting
	while (!get_bool(&info->mutex, &info->all_threads_ready))
		;
	printf("there are ready now now now now\n");
	
}

void print_state(t_philo *philo, char *state)
{
	long time;

	time = current_time() - philo->infos->start_simulation;
	
	pthread_mutex_lock(&philo->infos->mutex);
	printf("(%ld) %d %s\n", time, philo->id, state);
	pthread_mutex_unlock(&philo->infos->mutex);
}
// 0 - wait all the philos, synchro start
// 1 - endless loop philo
void *dinner_simu(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;

	//wait_all_threads(philo->infos);
	pthread_mutex_lock(&philo->left_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork);
	print_state(philo, "has taken a fork");

	
	print_state(philo, "is eating");
	usleep(philo->infos->time_eat);
	philo->last_meal_time = ;
	philo->meals_counter++;
	
	print_state(philo, "is sleeping");
	usleep(philo->infos->time_sleep);
	
	print_state(philo, "is thinking");

	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	
	// printf("Current time: %ld\n", current_time());
	// printf("Start simulation time: %ld\n", philo->infos->start_simulation);
	
	return (NULL);
}

void set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long get_long(pthread_mutex_t *mutex, long *value)
{
	long res;

	pthread_mutex_lock(mutex);
	res = *value; // reading safe
	pthread_mutex_unlock(mutex);
	return (res);
}
// info->limit_meals 5
// philo->meals_counter 5
bool monitor_state(t_info *info, t_philo *philos)
{
	int i;

	if (get_bool(&info->mutex, &info->end_simulation))
		return (true);	
	i = 0;
	while (i < info->nmb_philo)
	{
		if (philos[i].meals_counter != info->limit_meals)
			return (false);
		i++;
	}
	return (true);
}

// 0 - if no meals return 0
// 0.1 - if only one philo do hoc funtion
// 1 - create all the threads (philos)
// 2 - create a monitor thread (searching if a philo is dead)
// 3 - synchronize , make all philos start at the same time
// 4 - join everything
void start_eating(t_philo *philos, t_info *info)
{
	int i;
	
	i = 0;

	while (i < info->nmb_philo)
	{
		pthread_create(&philos[i].thread_id, NULL, dinner_simu, &philos[i]);
		i++;
	}
	sleep(1);
	// start of simulation (need a function that is gonna give us the actual time)
	// now all threads are ready 
	//set_bool(&info->mutex, &info->all_threads_ready, true);
	// while (!monitor_state(info, philos) && )
	// {
		
	// }
	
}


int main(int ac, char **av)
{
	t_info infos;
	t_philo *philos;

	memset(&infos, 0, sizeof(t_info));
	if (check_args(ac, av))
		return (1);
	check_inputs(&infos, av);
	philos = initialize(&infos);
	infos.start_simulation = current_time();
	printf("%ld\n", infos.start_simulation);
	start_eating(philos, &infos);
	//clean_up(&philos, &infos);
}


