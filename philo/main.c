/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:18:08 by eamchart          #+#    #+#             */
/*   Updated: 2025/05/24 17:33:53 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exact_sleep(t_info *info, long temp)
{
	long	start;

	start = current_time();
	while (current_time() - start < temp)
	{
		if (info->end_simulation)
			break ;
		usleep(100);
	}
}

void	clean_up(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < philo->infos->nmb_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	free(philo);
	free(info->forks);
}

t_philo	*initialize(t_info *info)
{
	int		i;
	t_philo	*philos;

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

int	start_eating(t_philo *philos, t_info *info)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	info->end_simulation = false;
	info->start_simulation = current_time();
	while (i < info->nmb_philo)
	{
		if (pthread_create(&philos[i].thread_id, NULL,
				thread_routine, &philos[i]))
			return (1);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, philos);
	pthread_join(monitor, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	infos;
	t_philo	*philos;

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
