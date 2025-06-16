/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:49:36 by eamchart          #+#    #+#             */
/*   Updated: 2025/05/24 18:54:16 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *state)
{
	long	time;

	if (!get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
	{
		pthread_mutex_lock(&philo->infos->mutex);
		time = current_time() - philo->infos->start_simulation;
		printf("%ld %d %s\n", time, philo->id, state);
		pthread_mutex_unlock(&philo->infos->mutex);
	}
}

void	thinking(t_philo *philo)
{
	if (!get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
	{
		print_state(philo, "is thinking");
		if (philo->id % 2 != 0)
			usleep(philo->infos->time_eat * 0.5);
	}
}

void	sleeping(t_philo *philo)
{
	if (!get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
	{
		print_state(philo, "is sleeping");
		exact_sleep(philo->infos, philo->infos->time_sleep);
	}
}

void	eating(t_philo *philo)
{
	if (philo->id % 2 != 0)
		usleep(1000);
	if (!get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
	{
		// if (philo->id % 2 != 0)
		// 	usleep(1000);
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		if (philo->infos->nmb_philo == 1)
		{
			set_bool(&philo->infos->mutex, &philo->infos->end_simulation, true);
			pthread_mutex_unlock(philo->left_fork);
			return ;
		}
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		print_state(philo, "is eating");
		philo->last_meal_time = current_time();
		philo->meals_counter++;
		if (!get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
			exact_sleep(philo->infos, philo->infos->time_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	*thread_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
