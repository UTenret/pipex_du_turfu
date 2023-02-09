/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:02:20 by utenret           #+#    #+#             */
/*   Updated: 2022/11/14 19:51:25 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*sl;

	while (*lst != NULL)
	{
		sl = *lst;
		*lst = (*lst)->next;
		del(sl->content);
		free(sl);
	}
	*lst = NULL;
}
