/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:18:32 by eamchart          #+#    #+#             */
/*   Updated: 2025/05/15 16:18:55 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
// 2147483648
// ifd fd
int num_length(char *str)
{
	int len;

	len = ft_strlen(str);
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
	if (strncmp(str, "2147483648", 10) >= 0)
		return (1);
	return (0);

}

int is_space(char *str)
{
	return ((*str == 32) || (*str >= 9 && *str <= 13));
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (is_space(str)) // not important
		str++;
	if (str[i] == '+')
		i++;
	if (num_length(&str[i]))
		return (1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

long	ft_atoi(const char *str)
{
	int	op;
	long	final;

	op = 1;
	final = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			op *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		final = (final * 10) + (*str - '0');
		str++;
	}
	return (final * op);
}