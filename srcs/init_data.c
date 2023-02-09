/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <utenret@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 00:42:18 by ulysse            #+#    #+#             */
/*   Updated: 2023/02/08 16:26:49 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data *data, char **av, char **env, int ac)
{
	init_data_path(data, env);
	init_data_split(data, av, ac);
	init_data_cmd_names(data, ac);
//	init_data_fd(data, av, ac);
//	init_data_pipe(data, ac);
//	if (data->here_doc == true)
//		data->child_nbr = 2;
//	else
//		data->child_nbr = 1;
}

void	init_data_fd(t_data *data, char **av, int ac)
{
	const char		*here_doc = "here_doc";
	unsigned long	i;

	i = 0;
	data->here_doc = false;
	while (av[1][i] != '\0')
	{
		if (av[1][i] != here_doc[i])
			break ;
		i++;
	}
	if (i == ft_strlen(here_doc))
		data->here_doc = true;
	if (data->here_doc == true && ac < 6)
		exit (1);
	data->fd[1] = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (data->here_doc == false)
		data->fd[0] = open(av[1], O_RDONLY);
	else
		init_here_doc(data);
	if (data->fd[0] == -1)
		ft_dprintf(2, "%s : No such file or directory\n", av[1]);
}

void	init_data_pipe(t_data *data, int ac)
{
	int	i;

	i = 0;
	data->pipe_fd = malloc((ac - 3 + 1) * sizeof(int *));
	if (data->pipe_fd == NULL)
		free_everything(data);
	while (i < ac - 3)
	{
		data->pipe_fd[i] = ft_calloc(3, sizeof(int));
		if (data->pipe_fd[i] == NULL)
			free_everything(data);
		i++;
	}
	i = 0;
	while (i < ac - 3)
	{
		if (pipe(data->pipe_fd[i]) == -1)
		{
			perror("pipe in init_data_pipe");
			exit (1);
		}
		i++;
	}
	data->pipe_fd[i] = NULL;
}

void	init_data_cmd_names(t_data *data, int ac)
{
	int	i;

	data->cmd_name = ft_calloc(ac, sizeof(char *));
	if (data->cmd_name == NULL)
		free_everything(data);
	i = 0;
	while (i < ac - 1)
	{
		if (data->split_args[i][0] != NULL)
			data->cmd_name[i] = ft_strdup(data->split_args[i][0]);
		else
			data->cmd_name[i] = ft_strjoin(data->cmd_name[i], "");
		i++;
	}
	data->cmd_name[i] = NULL;
}

void	init_data_path(t_data *data, char **env)
{
	data->path = find_path(env);
	if (data->path == NULL)
	{
		ft_dprintf(2, "Error.\nPath not found.\n");
		exit (1);
	}
}
