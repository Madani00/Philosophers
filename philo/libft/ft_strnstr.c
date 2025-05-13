/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdadda <mdadda@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:47:35 by mdadda            #+#    #+#             */
/*   Updated: 2024/11/05 18:53:09 by mdadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	if (!haystack || !needle)
		return (NULL);
	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		n = 0;
		if (haystack[i] == needle[n])
		{
			while (haystack[i + n] == needle[n] && (i + n) < len)
			{
				if (needle[n + 1] == '\0')
					return ((char *)&haystack[i]);
				n++;
			}
		}
		i++;
	}
	return (NULL);
}
