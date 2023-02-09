/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:11:43 by utenret           #+#    #+#             */
/*   Updated: 2022/11/09 17:48:35 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_nbr_size(int n)
{
	int				s;
	unsigned int	j;

	s = 0;
	if (n == 0)
		s++;
	if (n < 0)
	{
		j = (-1 * n);
		s++;
	}
	else
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

static void	ft_convert(char *str, int n, int i)
{
	unsigned int	j;
	int				s;

	s = i - 1;
	if (n < 0)
	{
		str[0] = '-';
		j = (-1 * n);
	}
	else
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

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = get_nbr_size(n);
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	ft_convert(str, n, i);
	return (str);
}
