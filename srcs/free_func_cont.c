/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:59:23 by utenret           #+#    #+#             */
/*   Updated: 2023/01/30 18:03:50 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_not_found_err(t_data *data, int i)
{
	char	*error;

	error = NULL;
	error = ft_strjoin(error, data->cmd_name[i]);
	error = ft_strjoin(error, ": command not found\n");
	ft_dprintf(2, "%s", error);
	free(error);
	close_all_pipes(data, -1);
	free_everything(data);
	exit (1);
}

void	close_all_pipes(t_data *data, int read)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->pipe_fd[j] != NULL)
	{
		while (i < 2)
		{
			if (j == read && i == 0)
				i++;
			else
			{
				close(data->pipe_fd[j][i]);
				i++;
			}
		}
		i = 0;
		j++;
	}
}

void	unlink_here_doc(void)
{
	int	fd;

	fd = open("here_doc_tmp", O_RDONLY);
	if (fd > 0)
	{
		if (unlink("here_doc_tmp") == -1)
			perror("unlink");
	}
}
