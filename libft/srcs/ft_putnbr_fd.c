/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:21:21 by utenret           #+#    #+#             */
/*   Updated: 2022/11/11 18:29:19 by utenret          ###   ########.fr       */
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

static char	*ft_convert(char *str, int n, int i)
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
	return (str);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	str[12];

	i = get_nbr_size(n);
	ft_convert(str, n, i);
	ft_putstr_fd(str, fd);
}
