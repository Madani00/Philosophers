/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdadda <mdadda@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:28:37 by mdadda            #+#    #+#             */
/*   Updated: 2024/11/03 11:05:28 by mdadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastnode;

	if (!new || !lst)
		return ;
	lastnode = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		lastnode = ft_lstlast(*lst);
		lastnode->next = new;
	}
}
