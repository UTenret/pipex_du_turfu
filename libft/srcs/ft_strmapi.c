/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:56:47 by utenret           #+#    #+#             */
/*   Updated: 2022/11/11 15:55:21 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*map;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	map = malloc(ft_strlen(s) + 1);
	if (!map)
		return (NULL);
	ft_strlcpy(map, s, ft_strlen(s) + 1);
	while (map[i])
	{
		map[i] = f(i, map[i]);
		i++;
	}		
	return (map);
}
