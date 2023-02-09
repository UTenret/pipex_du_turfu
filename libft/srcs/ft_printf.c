/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:33:33 by utenret           #+#    #+#             */
/*   Updated: 2022/12/05 17:43:09 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_check_next_pc(const char *str, size_t j)
{
	ssize_t	i;

	i = 0;
	while (str[i] && i < (ssize_t)j)
	{
		if (str[i] == '%')
			return (i);
		i++;
	}
	i = -1;
	return (i);
}

int	ft_check_conv(int fd, const char *str, void *arg)
{
	if (*str == 'c')
		return (ft_putchar(fd, (unsigned long)arg));
	if (*str == 's')
		return (ft_putstr_stack(fd, (char *)arg));
	if (*str == 'p' && ft_sizell((unsigned long long)arg) > 0)
	{
		if ((unsigned long long)arg == 0)
			return (ft_nil(fd));
		write(fd, "0x", 2);
		ft_p(fd, (unsigned long long)arg, ft_sizell((unsigned long long)arg));
		return (ft_sizell((unsigned long long)arg) + 2);
	}
	if (*str == 'd' || *str == 'i')
		return (ft_putstr(fd, ft_itoa((intptr_t)arg)));
	if (*str == 'u')
		return (ft_putstr(fd, ft_uitoa((uintptr_t)arg)));
	if (*str == 'x')
		ft_convert_hexa_min(fd, (uintptr_t)arg, ft_sizel((uintptr_t)arg));
	if (*str == 'X')
		ft_convert_hexa_maj(fd, (uintptr_t)arg, ft_sizel((uintptr_t)arg));
	if (*str == 'X' || *str == 'x')
		return (ft_sizel((uintptr_t)arg));
	return (0);
}

int	ft_move_ahead(int fd, const char *str, ssize_t i)
{
	if (i > 0)
	{
		return (i);
	}
	if (i == 0)
	{
		write(fd, &(*str), 1);
		str++;
		write(fd, &(*str), 1);
		return (2);
	}
	return (0);
}

int	ft_vdprintf(int fd, const char *str, va_list ap, size_t len)
{
	ssize_t			i;
	int				wc;

	wc = 0;
	while (ft_check_next_pc(str, len) >= 0)
	{
		i = ft_check_next_pc(str, len);
		wc += ft_putnstr(fd, str, i);
		str += i;
		if (i == -1)
			break ;
		if (*(str + 1) == '\0')
			return (-1);
		if (*str == '%' && *(str + 1) == '%')
			wc += write(fd, "%", 1);
		else
		{
			i = ft_check_conv(fd, str + 1, va_arg(ap, void *));
			wc += ft_move_ahead(fd, str, i);
		}
		str += 2;
	}
	if (*str != '\0')
		wc += ft_putstr_stack(fd, str);
	return (wc);
}

int	ft_printf(const char *str, ...)
{
	int				wc;
	va_list			ap;
	size_t			len;

	len = ft_strlen(str);
	va_start(ap, str);
	wc = ft_vdprintf(STDOUT_FILENO, str, ap, len);
	va_end(ap);
	return (wc);
}
