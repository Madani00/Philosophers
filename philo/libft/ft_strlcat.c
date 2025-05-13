/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdadda <mdadda@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:20:31 by mdadda            #+#    #+#             */
/*   Updated: 2024/11/06 19:01:24 by mdadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!dest && dstsize == 0)
		return (src_len);
	dest_len = ft_strlen(dest);
	if (dstsize <= dest_len)
		return (src_len + dstsize);
	i = dest_len;
	j = 0;
	while (src[j] && i < dstsize - 1)
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (src_len + dest_len);
}
