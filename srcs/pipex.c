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

void	do_cmd(int i, char **env, bool inpipe_open, bool outpipe_open, int *fd_in, int *fd_out, t_data *data, int ac)
{
	char *cmd;

	cmd = NULL;
	(void)ac;
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

int	make_children(int i, char **env, bool inpipe_open, bool outpipe_open, int *fd_in, int *fd_out, t_data *data, int ac)
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
		do_cmd(i, env, inpipe_open, outpipe_open, fd_in, fd_out, data, ac);
		exit (1);
	}
}

int	main(int ac, char **av, char **env)
{
	int		i;
	int		fd_in[2];
	int		fd_out[2];	
	int		inpipe_count;
	int		outpipe_count;
	bool	outpipe_open;
	bool	inpipe_open;
	int		pipe_type;
	int		pipe_count;
	bool	do_swap;
	t_data	data;

	init_data(&data, av, env, ac);
	inpipe_count = 0;
	outpipe_count = 0;
	i = 1;
	pipe_type = 1;
	outpipe_open = false;
	inpipe_open = false;
	pipe_count = 0;
	do_swap = true;
	while (i < ac)
	{
		if (ft_strncmp(av[i], "pipe", 5) == 0)
		{
			pipe_count++;
			i++;
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
		else
		{
			if (inpipe_open == true)
				inpipe_count++;
			if (outpipe_open == true)
				outpipe_count++;
			if (do_swap == true)
			{
				do_swap = false;
				make_children(i, env, outpipe_open, inpipe_open, fd_out, fd_in, &data, ac);
			}
			else
			{
				do_swap = true;
				make_children(i, env, inpipe_open, outpipe_open, fd_in, fd_out, &data, ac);
			}
			i++;
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
		}
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
