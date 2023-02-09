/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testouillepipexouille.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:19:32 by utenret           #+#    #+#             */
/*   Updated: 2023/02/08 21:19:45 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_first_gato(t_data *data, char **env, int i, int *pipe_fd)
{
	char *cmd;

	cmd = NULL;
	cmd = ft_strjoin_no_free("/bin/", data->split_args[i][0]);
	dup2(pipe_fd[1], 1);
//	close(pipe_fd[1]);
	execve(cmd, data->split_args[i], env);
	perror("execveds=dsffs");
}

void	make_second_gato(t_data *data, char **env, int i, int *pipe_fd)
{
	char *cmd;

	cmd = NULL;
	cmd = ft_strjoin_no_free("/bin/", data->split_args[i][0]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	execve(cmd, data->split_args[i], env);
	perror("execveds=dsffs");
}

int	make_gato(t_data *data, char **env, int i, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid != 0)
		return (0);
	else
	{
		if (i == 1)
			make_first_gato(data, env, i, pipe_fd);	
		else
			make_second_gato(data, env, i, pipe_fd);
	}
	exit (1);
}

void	ft_test(t_data *data, char **env)
{
	int		pipe_fd[2];
	int		i;
	
	i = 0;
	if (pipe(pipe_fd) == - 1)
		perror("pipe in in main");
	while (i < 2)
	{
		i++;
		make_gato(data, env, i, pipe_fd);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	while (wait(0) != -1)
		continue ;
	exit (1);
}
