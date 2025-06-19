/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 08:24:39 by eamchart          #+#    #+#             */
/*   Updated: 2025/06/19 19:17:08 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if ((!s1 || !s2) || !n)
		return (0);
	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	set_think_time(t_philo	*philos)
{
	long	think_time;

	think_time = 1;
	if (philos->infos->nmb_philo % 2 != 0)
		think_time = (philos->infos->time_eat * 2) - philos->infos->time_sleep;
	philos->infos->time_think = think_time * 1000;
}
