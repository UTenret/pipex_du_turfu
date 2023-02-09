/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <utenret@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:05:17 by ulysse            #+#    #+#             */
/*   Updated: 2022/11/14 17:54:22 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if ((char *)dest < (char *)src)
		ft_memcpy(dest, src, n);
	else
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)(dest))[n - i - 1]
				= ((const unsigned char *)src)[n - i - 1];
			i++;
		}	
	}
	return (dest);
}
