/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:18:08 by eamchart          #+#    #+#             */
/*   Updated: 2025/05/20 10:59:47 by eamchart         ###   ########.fr       */
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
// 2 - // [philo_pos = 1, philo->id = 2]  // [ l=(f) , r=(f) , f ,f ,f]
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
	if (pthread_mutex_init(&info->mutex, NULL))
		return (NULL);
	while (i < info->nmb_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (NULL);
		i++;
	}
	init_philo(info, philos);
	return (philos);
}
bool get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool res;

	pthread_mutex_lock(mutex);
	res = *value;
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
	printf("(%ld)  %d %s\n", time, philo->id, state);
	pthread_mutex_unlock(&philo->infos->mutex);
}
// info->limit_meals 5
// philo->meals_counter 5
bool monitor_state(t_philo *philo)
{
	int i;

	if (get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
		return (true);	
	i = 0;
	while (i < philo->infos->nmb_philo)
	{
		if (philo[i].meals_counter != philo->infos->limit_meals)
			return (false);
		i++;
	}
	return (true);
}
void safe_increment(pthread_mutex_t *mutex, long *dest)
{
	pthread_mutex_lock(mutex);
	*dest += 1;
	pthread_mutex_unlock(mutex);
}
// int check_death(t_philo *philo)
// {
// 	// long last_time;
// 	// long cur_time;

// 	// cur_time = current_time();
// 	// last_time = cur_time - philo->last_meal_time;
// 	if (philo->infos->time_eat >= philo->infos->time_die)
// 	{
// 		pthread_mutex_lock(&philo->infos->mutex);
// 		printf("%d\n", philo->infos->end_simulation);
// 		philo->infos->end_simulation = true;
// 		pthread_mutex_unlock(&philo->infos->mutex);
// 		print_state(philo, "is died");
// 		return (1);
// 	}
// 	return (0);
// }

// void *check_death(void *arg)
// {
// 	t_philo *philo;

// 	philo =  (t_philo *)arg;
// 	if (philo->infos->time_eat >= philo->infos->time_die)
// 	{
// 		pthread_mutex_lock(&philo->infos->mutex);
// 		philo->infos->end_simulation = true;
// 		pthread_mutex_unlock(&philo->infos->mutex);
// 		print_state(philo, "is died");
// 	}
// 	return (NULL);
// }
// // 4 390 200 200  (if 390 < 200 + 200)
// // if a philos doesn’t start eating ’time_to_die’ milliseconds 
// // after starting his last meal or the beginning of the simulation, it dies
void *dinner_simu(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;
	// wait_all_threads(philo->infos);
	while (!philo->infos->end_simulation) // !monitor_state(philo)
	{

		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		print_state(philo, "is eating");
		philo->last_meal_time = current_time(); 
		usleep(philo->infos->time_eat);
		safe_increment(&philo->infos->mutex, &philo->meals_counter);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (!philo->infos->end_simulation)
			return (NULL);
		// if (philo->infos->end_simulation)
		// 	return (NULL);
		// if (philo->meals_counter >= philo->infos->limit_meals)
		// 	return (NULL);
		// if (check_death(philo))
		// 	return (NULL);
		print_state(philo, "is sleeping");
		usleep(philo->infos->time_sleep);
		print_state(philo, "is thinking");	
	}
	return (NULL);
}

bool check_death(t_philo *philo)
{
    long current;
    long time_since_last_meal;

    current = current_time();
    pthread_mutex_lock(&philo->infos->mutex);
    time_since_last_meal = current - philo->last_meal_time;
    if (time_since_last_meal >= philo->infos->time_die && !philo->philo_full)
    {
        philo->infos->end_simulation = true;
        printf("(%ld) %d died\n", current - philo->infos->start_simulation, philo->id);
        pthread_mutex_unlock(&philo->infos->mutex);
        return (true);
    }
    pthread_mutex_unlock(&philo->infos->mutex);
    return (false);
}

// void *dinner_simu(void *data)
// {
//     t_philo *philo = (t_philo *)data;
    
//     philo->last_meal_time = philo->infos->start_simulation;
    
//     while (1)
//     {
//         if (get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
//             break;
            
//         pthread_mutex_lock(philo->left_fork);
//         print_state(philo, "has taken a fork");
//         pthread_mutex_lock(philo->right_fork);
//         print_state(philo, "has taken a fork");
        
//         print_state(philo, "is eating");
//         pthread_mutex_lock(&philo->infos->mutex);
//         philo->last_meal_time = current_time();
//         pthread_mutex_unlock(&philo->infos->mutex);
        
//         usleep(philo->infos->time_eat * 1000); 
        
//         safe_increment(&philo->infos->mutex, &philo->meals_counter);
    
//         pthread_mutex_unlock(philo->left_fork);
//         pthread_mutex_unlock(philo->right_fork);
        
//         if (philo->infos->limit_meals > 0 && 
//             philo->meals_counter >= philo->infos->limit_meals)
//         {
//             philo->philo_full = true;
//             break;
//         }
//         print_state(philo, "is sleeping");
//         usleep(philo->infos->time_sleep * 1000);
        
//         print_state(philo, "is thinking");
//         usleep(1000); 
//         if (check_death(philo))
//             break;
//     }
//     return (NULL);
// }

// void *monitor(void *data)
// {
//     t_philo *philo = (t_philo *)data;
//     int i;
//     bool all_full;
    
//     while (1)
//     {
//         i = 0;
//         all_full = true;
//         while (i < philo->infos->nmb_philo)
//         {
//             if (check_death(&philo[i]))
//                 return (NULL);
//             if (philo->infos->limit_meals > 0 && !philo[i].philo_full)
//                 all_full = false;
//             i++;
//         }
//         if (all_full)
//         {
//             pthread_mutex_lock(&philo->infos->mutex);
//             philo->infos->end_simulation = true;
//             pthread_mutex_unlock(&philo->infos->mutex);
//             return (NULL);
//         }
//         usleep(1000); // Check every 1ms
//     }
// }

void *monitor(void *data)
{
    t_philo *philo = (t_philo *)data;
    int i;
    bool all_full;
    
    while (1)
    {
        i = 0;
        all_full = false;
		while (i < philo->infos->nmb_philo)
		{
			if (philo[i].meals_counter == philo->infos->limit_meals)
			{
				all_full = true;
				break;
			}
			i++;
		}
        if (all_full)
        {
            pthread_mutex_lock(&philo->infos->mutex);
            philo->infos->end_simulation = true;
            pthread_mutex_unlock(&philo->infos->mutex);
            return (NULL);
        }
        //usleep(1000); // Check every 1ms
    }
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


int start_eating(t_philo *philos, t_info *info)
{
	int i;
	pthread_t mr;
	i = 0;

	info->start_simulation = current_time();
	while (i < info->nmb_philo)
	{
		if (pthread_create(&philos[i].thread_id, NULL, dinner_simu, &philos[i]))
			return (1);
		i++;
	}
	// start of simulation (need a function that is gonna give us the actual time)
	// now all threads are ready 
	// set_bool(&info->mutex, &info->all_threads_ready, true);
	pthread_create(&mr, NULL, monitor, philos);
	pthread_join(mr, NULL);
	return (0);
}


int main(int ac, char **av)
{
	t_info infos;
	t_philo *philos;

	memset(&infos, 0, sizeof(t_info));
	if (check_args(ac, av))
		return (1);
	if (check_inputs(&infos, av))
		return (printf("Error in the number\n"));
	philos = initialize(&infos);
	if (!philos)
		return (1);
	if (start_eating(philos, &infos))
		return (1);
	clean_up(philos, &infos);
}

				
