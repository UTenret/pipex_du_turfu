/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <utenret@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:44:44 by ulysse            #+#    #+#             */
/*   Updated: 2022/11/11 15:58:04 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(char const *s, size_t len, unsigned int start)
{
	if (start > ft_strlen(s))
		return (0);
	if (ft_strlen(s + start) >= len)
		return (len);
	return (ft_strlen(s + start));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ns;
	size_t	i;

	i = 0;
	ns = malloc(get_size(s, len, start) + 1);
	if (!ns)
		return (NULL);
	while (len > 0 && *s && start < ft_strlen(s))
	{
		ns[i] = *(s + start);
		s++;
		i++;
		len--;
	}
	ns[i] = '\0';
	return (ns);
}
