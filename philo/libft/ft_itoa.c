/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdadda <mdadda@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:36:06 by mdadda            #+#    #+#             */
/*   Updated: 2025/04/10 09:43:57 by mdadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	if (n == 0)
	{
		return (1);
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		lent;
	char	*str;

	nbr = n;
	lent = ft_len(nbr);
	str = gc_malloc((lent + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[lent] = '\0';
	lent--;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		str[lent] = (nbr % 10) + '0';
		nbr /= 10;
		lent--;
	}
	return (str);
}
