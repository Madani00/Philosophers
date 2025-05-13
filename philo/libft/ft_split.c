/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdadda <mdadda@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:13:13 by mdadda            #+#    #+#             */
/*   Updated: 2025/05/09 15:06:29 by mdadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	is_word;
	int	count;

	i = 0;
	is_word = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (is_word == 0)
			{
				count++;
				is_word = 1;
			}
		}
		else
		{
			is_word = 0;
		}
		i++;
	}
	return (count);
}

static char	**free_memory(char **ptr, int p)
{
	int	i;

	i = p - 1;
	while (i >= 0)
	{
		gc_free_one(ptr[i]);
		i--;
	}
	gc_free_one(ptr);
	return (NULL);
}

static char	**fill_words(char const *s, char c, char **ptr)

{
	int	i;
	int	start;
	int	array_position;

	array_position = 0;
	i = 0;
	start = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			ptr[array_position] = ft_substr(s, start, i - start);
			if (!ptr[array_position])
				return (free_memory(ptr, array_position));
			array_position++;
		}
		else
			i++;
	}
	ptr[array_position] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;

	if (!s)
		return (NULL);
	ptr = gc_malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	return (fill_words(s, c, ptr));
}
