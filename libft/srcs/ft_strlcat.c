/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <utenret@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:31:53 by ulysse            #+#    #+#             */
/*   Updated: 2022/11/11 15:51:55 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	res;	

	if (ft_strlen(dst) >= size)
		return (size + ft_strlen(src));
	i = size - ft_strlen(dst);
	res = ft_strlen(dst) + ft_strlen(src);
	ft_strlcpy(dst + ft_strlen(dst), src, i);
	return (res);
}
