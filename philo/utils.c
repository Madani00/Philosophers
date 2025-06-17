/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:55:33 by eamchart          #+#    #+#             */
/*   Updated: 2025/06/17 19:57:55 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

bool	check_death(t_philo *philo)
{
	long	current;
	long	time_pass;

	pthread_mutex_lock(&philo->infos->mutex);
	current = current_time();
	time_pass = current - philo->last_meal_time;
	if (time_pass >= philo->infos->time_die)
	{
		philo->infos->end_simulation = true;
		printf("%ld %d died\n", current - philo->infos->start_simulation,
			philo->id);
		pthread_mutex_unlock(&philo->infos->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->infos->mutex);
	return (false);
}

void	*monitor_routine(void *data)
{
	t_philo	*philo;
	int		i;
	bool	all_full;

	philo = (t_philo *)data;
	
	//usleep(500); // added this
	while (1)
	{
		i = 0;
		all_full = true;
		while (i < philo->infos->nmb_philo)
		{
			if (get_long(&philo->infos->mutex, &philo[i].meals_counter)
				< philo->infos->limit_meals && philo->infos->limit_meals > 0)
				all_full = false;
			if (check_death(&philo[i]))
				return (NULL);
			i++;
		}
		if (all_full && philo->infos->limit_meals > 0)
		{
			set_bool(&philo->infos->mutex, &philo->infos->end_simulation, true);
			return (NULL);
		}
		usleep(500);
	}
}
