/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:22:35 by eamchart          #+#    #+#             */
/*   Updated: 2025/05/24 17:53:01 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Number of arguments not valid\n"));
	if (check_numeric(ac, av))
		return (printf("Error in the number\n"));
	return (0);
}

int	check_inputs(t_info *info, char **av)
{
	info->nmb_philo = ft_atoi(av[1]);
	info->time_die = ft_atoi(av[2]);
	info->time_eat = ft_atoi(av[3]);
	info->time_sleep = ft_atoi(av[4]);
	info->limit_meals = -1;
	if (av[5])
		info->limit_meals = ft_atoi(av[5]);
	if (!info->time_die || !info->nmb_philo || !info->time_sleep
		|| !info->time_eat || !info->limit_meals)
		return (1);
	return (0);
}

void	init_forks(t_philo *philo, pthread_mutex_t *forks, int philo_pos)
{
	int	philo_nb;

	philo_nb = philo->infos->nmb_philo;
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

void	init_philo(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nmb_philo)
	{
		philo[i].infos = info;
		philo[i].id = i + 1;
		philo[i].meals_counter = 0;
		philo[i].last_meal_time = current_time();
		init_forks(&philo[i], info->forks, i);
		i++;
	}
}

long	current_time(void)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	return ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000));
}
