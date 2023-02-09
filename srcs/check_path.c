/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:56:27 by utenret           #+#    #+#             */
/*   Updated: 2023/01/30 13:57:14 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	cmd_name_contains_path(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->cmd_name[i][j] != '\0')
	{
		if (data->cmd_name[i][j] == '/')
			return (true);
		j++;
	}
	return (false);
}

void	print_path_error(t_data *data, int i, char *join)
{
	int	fd;

	fd = open(data->cmd_name[i], O_RDONLY);
	join = ft_strjoin_free_s2("bash: ", join);
	if (fd == -1)
	{
		join = ft_strjoin(join, ": No such file or directory\n");
		write(2, join, ft_strlen(join));
		free(join);
		close_all_pipes(data, -1);
		free_everything(data);
	}
	else
	{
		perror(join);
		free(join);
		close_all_pipes(data, -1);
		free_everything(data);
	}
	exit (1);
}

char	*check_correct_path(t_data *data, int i)
{
	char	*join;
	int		j;

	join = NULL;
	if (cmd_name_contains_path(data, i) == true)
	{
		join = ft_strjoin(join, data->cmd_name[i]);
		if (access(join, F_OK | X_OK) == 0)
			return (join);
		print_path_error(data, i, join);
	}
	j = 1;
	while (data->split_path[j] != NULL)
	{
		data->split_path[j] = ft_strjoin(data->split_path[j], "/");
		join = ft_strjoin_no_free(data->split_path[j], data->cmd_name[i]);
		if (access(join, F_OK | X_OK) == 0)
			return (join);
		free(join);
		j++;
	}
	cmd_not_found_err(data, i);
	return (0);
}
