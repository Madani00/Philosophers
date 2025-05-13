/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdadda <mdadda@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:09:55 by mdadda            #+#    #+#             */
/*   Updated: 2024/11/06 18:50:53 by mdadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*source;

	i = 0;
	source = (unsigned char *)s;
	while (i < n)
	{
		if (source[i] == (unsigned char)c)
		{
			return ((void *)&source[i]);
		}
		i++;
	}
	return (NULL);
}
