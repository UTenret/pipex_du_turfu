/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:11:43 by utenret           #+#    #+#             */
/*   Updated: 2022/12/05 17:06:54 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned int	get_nbr_size(unsigned int n)
{
	int				s;
	unsigned int	j;

	s = 0;
	if (n == 0)
		s++;
	j = n;
	while (j >= 10)
	{
		j = j / 10;
		s++;
	}
	if (j > 0)
		s++;
	return (s);
}

static void	ft_convert(char *str, unsigned int n, unsigned int i)
{
	unsigned int	j;
	int				s;

	s = i - 1;
	j = n;
	while (j >= 10)
	{	
		str[s] = j % 10 + '0';
		j /= 10;
		s--;
	}
	if (j > 0)
		str[s] = j + '0';
	if (n == 0)
		str[0] = '0';
	str[i] = '\0';
}

char	*ft_uitoa(unsigned int n)
{
	char				*str;
	unsigned int		i;

	i = get_nbr_size(n);
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	ft_convert(str, n, i);
	return (str);
}
