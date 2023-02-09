/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <utenret@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:25:31 by ulysse            #+#    #+#             */
/*   Updated: 2022/11/15 11:39:35 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_word_size(char const *str, char c);

static	int	ft_add_words(char **split, char const *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (*str)
	{
		j = 0;
		if (!(ft_word_size(str, c)))
			return (1);
		split[i] = malloc(ft_word_size(str, c) + 1);
		if (!split[i])
			return (0);
		while (*str == c && *str != '\0')
			str++;
		while (*str != c && *str != '\0')
		{
			split[i][j] = *str;
			str++;
			j++;
		}
		split[i][j] = '\0';
		i++;
	}
	return (1);
}

static size_t	ft_word_size(char const *str, char c)
{
	size_t	len_word;

	while (*str == c && *str != '\0')
		str++;
	len_word = 0;
	while (*str != c && *str != '\0')
	{
		str++;
		len_word += 1;
	}
	return (len_word);
}

static	size_t	ft_nbr_words(char const *str, char c)
{
	size_t	len_words;
	size_t	nbr_words;
	size_t	i;

	i = 0;
	len_words = 0;
	nbr_words = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i] != '\0')
			len_words++;
		if (len_words > 0 && (str[i] == c || str[i] == '\0'))
		{
			nbr_words++;
			len_words = 0;
		}
		i++;
	}
	if (len_words > 0)
		nbr_words += 1;
	return (nbr_words);
}

static	void	ft_cleanup(char **split)
{
	size_t	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_split(char const *str, char c)
{
	char		**split;
	const int	num_words = ft_nbr_words(str, c);	

	split = malloc(sizeof (char *) * (num_words + 1));
	if (!split)
		return (NULL);
	if (!ft_add_words(split, str, c))
	{
		ft_cleanup(split);
		return (split);
	}
	split[num_words] = NULL;
	return (split);
}
