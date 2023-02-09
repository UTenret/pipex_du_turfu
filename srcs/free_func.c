/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:05:25 by utenret           #+#    #+#             */
/*   Updated: 2023/01/30 14:06:19 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd_name(t_data *data)
{
	int	j;

	j = 0;
	while (data->cmd_name[j] != NULL)
	{
		free(data->cmd_name[j]);
		j++;
	}
	free(data->cmd_name);
}

void	free_split_path(t_data *data)
{
	int	j;

	j = 0;
	while (data->split_path[j] != NULL)
	{
		free(data->split_path[j]);
		j++;
	}
	free(data->split_path);
}

void	free_split_args(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->split_args[j] != NULL)
	{
		while (data->split_args[j][i] != NULL)
		{
			free(data->split_args[j][i]);
			i++;
		}
		free(data->split_args[j]);
		i = 0;
		j++;
	}
	free(data->split_args);
}

void	free_pipes(t_data *data)
{
	int	j;

	j = 0;
	while (data->pipe_fd[j] != NULL)
	{
		free(data->pipe_fd[j]);
		j++;
	}
	free(data->pipe_fd);
}

void	free_everything(t_data *data)
{
	free_cmd_name(data);
	free_split_path(data);
	free_split_args(data);
	free_pipes(data);
	unlink_here_doc();
}
