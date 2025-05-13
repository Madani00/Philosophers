/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdadda <mdadda@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:10:01 by mdadda            #+#    #+#             */
/*   Updated: 2024/11/06 19:00:16 by mdadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*destination;
	unsigned char	*source;

	if (n == 0 || dest == src)
		return (dest);
	i = 0;
	source = (unsigned char *)src;
	destination = (unsigned char *)dest;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (dest);
}
