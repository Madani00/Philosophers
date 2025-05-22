/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:22:35 by eamchart          #+#    #+#             */
/*   Updated: 2025/05/22 11:08:44 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Number of arguments not valid\n"));
	if (check_numeric(ac, av))
		return (printf("Error in the number\n"));
	return (0);
}

int check_inputs(t_info *info, char **av)
{
	info->nmb_philo = ft_atoi(av[1]);
	info->time_die = ft_atoi(av[2]) * 1000;
	info->time_eat = ft_atoi(av[3]) * 1000;
	info->time_sleep = ft_atoi(av[4]) * 1000;
	info->limit_meals = -1;
	if (av[5])
		info->limit_meals = ft_atoi(av[5]);
	if (!info->time_die || !info->nmb_philo || !info->time_sleep
		|| !info->time_eat || !info->limit_meals || info->nmb_philo == 1)
		return (1);
	return (0);
}