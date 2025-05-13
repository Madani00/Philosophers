/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdadda <mdadda@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:17:58 by mdadda            #+#    #+#             */
/*   Updated: 2024/11/01 09:48:23 by mdadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(const char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_get_start(const char *str, const char *set)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_check(set, str[i]))
		i++;
	return (i);
}

static size_t	ft_get_end(const char *str, const char *set)
{
	size_t	i;

	i = ft_strlen(str);
	if (i == 0)
	{
		return (0);
	}
	i--;
	while (i > 0 && ft_check(set, str[i]))
		i--;
	return (i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int	start;
	int	end;

	if (!s1 || !set)
		return (NULL);
	end = ft_get_end(s1, set);
	start = ft_get_start(s1, set);
	if (start > end)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start + 1));
}
