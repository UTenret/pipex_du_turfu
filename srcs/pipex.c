/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:31:22 by utenret           #+#    #+#             */
/*   Updated: 2023/02/09 12:44:26 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_cmd(int i, char **env, t_pipe *fd_in, t_pipe *fd_out, t_data *data)
{
	char *cmd;

	cmd = NULL;
	if (fd_in->is_open)
	{
		close(fd_in->fds[1]);
		dup2(fd_in->fds[0], STDIN_FILENO);
	}
	if (fd_out->is_open)
		dup2(fd_out->fds[1], STDOUT_FILENO);
	cmd = ft_strjoin_no_free("/bin/", data->split_args[i][0]);
	execve(cmd, data->split_args[i], env);
	perror("execve");
}

int	make_children(int i, char **env, t_pipe *fd_in, t_pipe *fd_out, t_data *data)
{
	const pid_t	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid != 0)
		return (EXIT_SUCCESS);
	else
	{
		do_cmd(i, env, fd_in, fd_out, data);
		exit(EXIT_FAILURE);
	}
}

void    swap_pipes(int fd_in[2], int fd_out[2])
{
    fd_in[0] ^= fd_out[0];
    fd_out[0] ^= fd_in[0];
    fd_in[0] ^= fd_out[0];
    fd_in[1] ^= fd_out[1];
    fd_out[1] ^= fd_in[1];
    fd_in[1] ^= fd_out[1];
}

void	clean_pipe(t_pipe *pipe)
{
	if (pipe->fds[0] != -1)
		close(pipe->fds[0]);
	if (pipe->fds[1] != -1)
		close(pipe->fds[1]);
	pipe->count = 0;
	pipe->is_open = false;
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	t_pipe	fd_in;
	t_pipe	fd_out;
	t_data	data;

	clean_pipe(&fd_in);
	clean_pipe(&fd_out);
	init_data(&data, argv, env, argc);
	i = 1;
	while (i < argc)
	{
		if (i != argc - 1)
		{
			if (pipe(fd_in.fds) == - 1)
				perror("pipe in in main");
			fd_in.is_open = true;
		}
		// ft_printf("i=%d inopen=%d outopen=%d\n", i, fd_in.is_open, fd_out.is_open);
		fd_in.count += fd_in.is_open;
		fd_out.count += fd_out.is_open;
		make_children(i, env, &fd_out, &fd_in, &data);
		if (fd_in.count == 2)
			clean_pipe(&fd_in);
		if (fd_out.count == 2)
			clean_pipe(&fd_out);
		++i;
		t_pipe	tmp = fd_in;
		fd_in = fd_out;
		fd_out = tmp;
	}
	clean_pipe(&fd_in);
	clean_pipe(&fd_out);
	while (wait(NULL) != -1)
		;
	return (EXIT_SUCCESS);
}
