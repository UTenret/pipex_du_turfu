/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <utenret@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:37:46 by ulysse            #+#    #+#             */
/*   Updated: 2022/11/25 14:20:14 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1 != NULL)
		len1 = ft_strlen(s1);
	if (s2 != NULL)
		len2 = ft_strlen(s2);
	s = malloc(len1 + len2 + 1);
	if (s != NULL)
	{
		if (s1 != NULL)
			ft_strlcpy(s, s1, len1 + 1);
		if (s2 != NULL)
			ft_strlcpy(s + len1, s2, len2 + 1);
	}
	if (s1 != NULL)
		free(s1);
	return (s);
}
