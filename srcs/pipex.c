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

void	do_cmd(int i, char **env, bool inpipe_open, bool outpipe_open, int *fd_in, int *fd_out, t_data *data, int argc)
{
	char *cmd;

	cmd = NULL;
	(void)argc;
	if (inpipe_open == true)
	{
		close(fd_in[1]);
		dup2(fd_in[0], 0);
	}
	if (outpipe_open == true)
	{
		dup2(fd_out[1], 1);
	}
	cmd = ft_strjoin_no_free("/bin/", data->split_args[i][0]);
	execve(cmd, data->split_args[i], env);
	perror("execve: ");
}

int	make_children(int i, char **env, bool inpipe_open, bool outpipe_open, int *fd_in, int *fd_out, t_data *data, int argc)
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
		do_cmd(i, env, inpipe_open, outpipe_open, fd_in, fd_out, data, argc);
		exit(1);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		fd_in[2];
	int		fd_out[2];	
	int		inpipe_count;
	int		outpipe_count;
	bool	outpipe_open;
	bool	inpipe_open;
	int		pipe_type;
	bool	do_swap;
	t_data	data;

	init_data(&data, argv, env, argc);
	inpipe_count = 0;
	outpipe_count = 0;
	pipe_type = 1;
	outpipe_open = false;
	inpipe_open = false;
	do_swap = true;
	i = 1;
	while (i < argc)
	{
		if (i != argc - 1)
		{
			if (pipe_type == 1)
			{
				if (pipe(fd_in) == - 1)
					perror("pipe in in main");
				pipe_type = 0;
				inpipe_open = true;
			}
			else if (pipe_type == 0)
			{
				if (pipe(fd_out) == - 1)
					perror("pipe out in main");
				pipe_type = 1;
				outpipe_open = true;
			}
		}
		if (inpipe_open == true)
			inpipe_count++;
		if (outpipe_open == true)
			outpipe_count++;
		if (do_swap == true)
		{
			do_swap = false;
			make_children(i, env, outpipe_open, inpipe_open, fd_out, fd_in, &data, argc);
		}
		else
		{
			do_swap = true;
			make_children(i, env, inpipe_open, outpipe_open, fd_in, fd_out, &data, argc);
		}
		if (inpipe_count == 2)
		{
			close(fd_in[0]);
			close(fd_in[1]);
			inpipe_open = false;
			inpipe_count = 0;
		}
		if (outpipe_count == 2)
		{
			close(fd_out[0]);
			close(fd_out[1]);
			outpipe_open = false;
			outpipe_count = 0;
		}
		++i;
	}
	if (outpipe_open == true)
	{
		close (fd_out[0]);
		close (fd_out[1]);
	}
	if (inpipe_open == true)
	{
		close (fd_in[0]);
		close (fd_in[1]);
	}
	while (wait(0) != -1)
		continue ;
	exit(0);
}
