/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:44:03 by utenret           #+#    #+#             */
/*   Updated: 2023/01/17 18:08:38 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_does_str_contains_n(char	*str)
{
	ssize_t	i;

	i = 0;
	if (str[i] == '\n')
		return (i + 1);
	while (str[i])
	{
		i++;
		if (str[i] == '\n')
			return (i + 1);
	}
	return (-1);
}

char	*ft_rest(char *res, char *gnl, size_t i)
{
	size_t	c;

	c = ft_strlen(gnl);
	if (i < ft_strlen(gnl))
	{
		res = ft_strnjoin(res, gnl, i);
		ft_strlcpy(gnl, gnl + i, BUFFER_SIZE + 1);
		ft_memset(gnl + c, 0, BUFFER_SIZE + 1 - c);
		return (res);
	}
	else
	{
		res = ft_strjoin(res, gnl);
		ft_memset(gnl, 0, BUFFER_SIZE);
		return (res);
	}
}

char	*ft_weout(char **res, char *buf, char *gnl, int c)
{
	int	i;

	i = ft_does_str_contains_n(buf);
	if (i == -1)
	{
		*res = ft_strjoin(*res, buf);
		ft_memset(buf, 0, BUFFER_SIZE);
		return (buf);
	}
	else if (i == 0)
		return (buf);
	else
	{
		ft_strlcpy(gnl, buf + i, c + 1 - i);
		ft_memset(buf + i, 0, c - i);
		*res = ft_strjoin(*res, buf);
		ft_memset(buf, 0, BUFFER_SIZE);
	}
	return (buf);
}

int	ft_letsread(char **res, char *buf, char *gnl, int fd)
{
	int	c;
	int	i;

	i = ft_does_str_contains_n(buf);
	*res = ft_strjoin(*res, gnl);
	ft_memset(gnl, 0, BUFFER_SIZE);
	while (i == -1)
	{
		c = read(fd, buf, BUFFER_SIZE);
		i = ft_does_str_contains_n(buf);
		if (c == 0 || c == -1)
		{
			if (*(res[0]) != '\0' && c != -1)
				return (0);
			free(*res);
			return (1);
		}
		if (i == -1)
			buf = ft_weout(res, buf, gnl, c);
	}
	ft_weout(res, buf, gnl, c);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	gnl[OPEN_MAX][BUFFER_SIZE + 1] = {0};
	char		buf[BUFFER_SIZE + 1];
	char		*res;
	ssize_t		i;

	if (fd > -1 && fd < FOPEN_MAX)
	{
		ft_memset(buf, 0, BUFFER_SIZE + 1);
		i = ft_does_str_contains_n(gnl[fd]);
		res = NULL;
		if (i >= 0)
			return (ft_rest(res, gnl[fd], i));
		else if (ft_letsread(&res, buf, gnl[fd], fd) == 0)
			return (res);
	}
	return (NULL);
}
