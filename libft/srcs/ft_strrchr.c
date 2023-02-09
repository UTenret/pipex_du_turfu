/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <utenret@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:01:56 by ulysse            #+#    #+#             */
/*   Updated: 2022/11/11 15:50:26 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*j;

	j = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			j = (char *)s;
		s++;
	}
	if ((unsigned char)c == '\0')
			j = (char *)s;
	return (j);
}
