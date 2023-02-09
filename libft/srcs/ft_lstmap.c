/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:42:38 by utenret           #+#    #+#             */
/*   Updated: 2022/11/15 15:20:14 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nl;
	t_list	*nn;
	t_list	*temp;

	nl = NULL;
	temp = lst;
	while (temp)
	{
		nn = ft_lstnew(f(temp->content));
		if (nn)
			ft_lstadd_back(&nl, nn);
		else
		{
			ft_lstclear(&nl, del);
			return (NULL);
		}
		temp = temp->next;
	}
	return (nl);
}
