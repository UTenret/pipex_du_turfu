/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:52:37 by utenret           #+#    #+#             */
/*   Updated: 2023/01/28 16:26:35 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr_stack(int fd, const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (write(fd, "(null)", 6));
	if (*s == '\0')
		return (-1);
	i = ft_strlen(s);
	write(fd, s, i);
	return (i);
}

int	ft_putstr(int fd, char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		write(fd, &(s[i]), 1);
		i++;
	}
	if (s != NULL)
		free(s);
	return (i);
}

int	ft_putnstr(int fd, const char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (s[i] && i < n)
	{
		write(fd, &(s[i]), 1);
		i++;
	}
	return (i);
}

size_t	ft_sizell(unsigned long long nbr)
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
