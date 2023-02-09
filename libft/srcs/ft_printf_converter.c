/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_converter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:21:39 by utenret           #+#    #+#             */
/*   Updated: 2022/12/05 17:44:10 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_convert_hexa_maj(int fd, unsigned int nbr, size_t size)
{
	if (size > 0)
	{
		ft_convert_hexa_maj(fd, nbr / 16, size - 1);
		write(fd, &HEXAMAJ[nbr % 16], 1);
	}
}

void	ft_convert_hexa_min(int fd, unsigned int nbr, size_t size)
{
	if (size > 0)
	{
		ft_convert_hexa_min(fd, nbr / 16, size - 1);
		write(fd, &HEXAMIN[nbr % 16], 1);
	}
}

void	ft_p(int fd, unsigned long long nbr, size_t size)
{	
	if (size > 0)
	{
		ft_p(fd, nbr / 16, size - 1);
		write(fd, &HEXAMIN[nbr % 16], 1);
	}
}

int	ft_nil(int fd)
{
	return (write(fd, "(nil)", 5));
}

size_t	ft_sizel(unsigned int nbr)
{
	size_t	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr >= 16)
	{
		i++;
		nbr /= 16;
	}
	if (nbr != 0)
		i++;
	return (i);
}
