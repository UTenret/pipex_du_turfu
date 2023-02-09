/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:21:58 by utenret           #+#    #+#             */
/*   Updated: 2022/11/25 14:22:11 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char *s1, char *s2, int size)
{
	char	*s;
	size_t	len1;

	len1 = 0;
	if (s1 != NULL)
		len1 = ft_strlen(s1);
	s = malloc(len1 + size + 1);
	if (s != NULL)
	{
		if (s1 != NULL)
			ft_strlcpy(s, s1, len1 + 1);
		if (s2 != NULL)
			ft_strlcpy(s + len1, s2, size + 1);
	}
	if (s1 != NULL)
		free(s1);
	return (s);
}
