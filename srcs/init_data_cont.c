/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:15:08 by utenret           #+#    #+#             */
/*   Updated: 2023/02/08 16:29:02 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_here_doc(t_data *data)
{
	char	*nl;
	char	*nl_cmp;

	nl = NULL;
	nl_cmp = NULL;
	nl_cmp = ft_strjoin_no_free(data->split_args[0][0], "\n");
	data->fd[0] = open("here_doc_tmp", O_RDWR | O_APPEND | O_CREAT, 0666);
	write(2, "heredoc> ", 9);
	while (1)
	{
		nl = get_next_line(0);
		if (ft_strncmp(nl, nl_cmp, ft_strlen(nl)) == 0)
			break ;
		write(2, "heredoc> ", 9);
		if (nl != NULL)
		{
			write(data->fd[0], nl, ft_strlen(nl));
			free(nl);
			nl = NULL;
		}
	}
	close(data->fd[0]);
	data->fd[0] = open("here_doc_tmp", O_RDONLY, 0666);
	free(nl);
	free(nl_cmp);
}

void	init_data_split(t_data *data, char **av, int ac)
{
	data->split_path = ft_split(data->path, ':');
	init_data_split_args(data, av, ac);
}

bool	is_arg_only_spaces(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

void	init_data_split_args(t_data *data, char **av, int ac)
{
	int	i;

	i = 0;
	data->split_args = ft_calloc(ac, sizeof(char **));
	if (data->split_args == NULL)
	{
		perror("malloc:");
		exit (1);
	}
	while (i < ac)
	{
//		if (is_arg_only_spaces(av[i + 2]) == true)
//			data->split_args[i] = ft_split(av[i + 2], '\n');
//		else
		data->split_args[i] = ft_split(av[i], ' ');
		i++;
	}
	data->split_args[i] = NULL;
}

char	*find_path(char **env)
{
	int	j;

	j = 0;
	while (env[j] != NULL)
	{
		if (ft_strnstr(env[j], "PATH=/mnt", ft_strlen(env[j])) != NULL)
			return (ft_strnstr(env[j], "PATH=/mnt", ft_strlen(env[j])));
		j++;
	}
	return (NULL);
}
