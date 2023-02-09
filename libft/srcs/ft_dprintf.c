/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:16:51 by utenret           #+#    #+#             */
/*   Updated: 2022/12/26 12:18:16 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprintf(int fd, const char *str, ...)
{
	int				wc;
	va_list			ap;
	size_t			len;

	len = ft_strlen(str);
	va_start(ap, str);
	wc = ft_vdprintf(fd, str, ap, len);
	va_end(ap);
	return (wc);
}
