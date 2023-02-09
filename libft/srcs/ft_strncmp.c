/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <utenret@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:41:53 by ulysse            #+#    #+#             */
/*   Updated: 2022/11/14 17:49:03 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	duc;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		uc = s1[i];
		duc = s2[i];
		if (uc != duc)
			return (uc - duc);
		i++;
	}
	return (0);
}
