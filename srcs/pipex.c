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

//	dup2(data->pipe_fd[nb - 1][0], 0);
//	dup2(data->fd[1], 1);
void	do_cmd(int i, char **env, bool inpipe_open, bool outpipe_open, int *fd_in, int *fd_out, t_data *data, int ac)
{
	char *cmd;

	cmd = NULL;
	(void)ac;
	if (inpipe_open == true)
	{
//		dprintf(2, "\ninpipe_open for cmd[%s]\n", data->split_args[i][0]);
		close(fd_in[1]);
		dup2(fd_in[0], 0);
	}
//	else
//		dprintf(2, "\ninpipe_closed for cmd[%s]\n", data->split_args[i][0]);
	if (outpipe_open == true)
	{
//		dprintf(2, "\noutpipe_open for cmd[%s]\n", data->split_args[i][0]);
//		close(fd_out[1]);
		dup2(fd_out[1], 1);
//		dup2(fd_in[1], 1);
	}
//	else
//		dprintf(2, "\noutpipe_closed for cmd[%s]\n", data->split_args[i][0]);
	cmd = ft_strjoin_no_free("/bin/", data->split_args[i][0]);
//	dprintf(2, "cnd=====[%s]\n", cmd);
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
//				dprintf(2, "\nopening a ||||||||||||||||||||||||||||||||||||||||||||||||||||fd_in\n");
				if (pipe(fd_in) == - 1)
					perror("pipe in in main");
				pipe_type = 0;
				inpipe_open = true;
			}
			else if (pipe_type == 0)
			{
//				dprintf(2, "opening a |||||||||||||||||||||||||||||||||||||||||||||||||||||fd_out\n");
				if (pipe(fd_out) == - 1)
					perror("pipe out in main");
				pipe_type = 1;
				outpipe_open = true;
			}
		}
		else
		{
			if (inpipe_open == true)
//				printf("inpipe_open =|||||||||||||||||||= true for that cmd [%s]\n", data.split_args[i][0]);
				inpipe_count++;
			if (outpipe_open == true)
				outpipe_count++;
			if (do_swap == true)
			{
//				printf("this cmd [%s]\n", data.split_args[i][0]);
				do_swap = false;
//				make_children(i, env, false, true, fd_out, fd_in, &data, ac);
				make_children(i, env, outpipe_open, inpipe_open, fd_out, fd_in, &data, ac);
			}
			else
			{
//				printf("that cmd [%s]\n", data.split_args[i][0]);
				do_swap = true;
//				if (inpipe_open == true)
//					printf("inpipe_open == true for that cmd [%s]\n", data.split_args[i][0]);
//				make_children(i, env, true, false, fd_in, fd_out, &data, ac);
				make_children(i, env, inpipe_open, outpipe_open, fd_in, fd_out, &data, ac);
			}
			// int tmp_pipe[2] = fd_in;
			// fd_in = ft_out;
			// ft_out = tmp_pipe;
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
//	if (outpipe_open == true)
//		dprintf(2, "\n======================================================outpipe open for last cmd IN PARENT\n");	
//	else 
//		dprintf(2, "=========================================================outpipe closed for last cmd IN PARENT\n");
//	if (inpipe_open == true)	
//		dprintf(2, "\n=======================================================inpipe open for last cmd IN PARENT\n");
//	else 
//		dprintf(2, "=========================================================inpipe closed for last cmd IN PARENT\n");
	while (wait(0) != -1)
		continue ;
	exit(0);
}

/*
void	first_cmd(t_data *data, char **env)
{
	const int	nb = data->child_nbr - 1;

	if (data->fd[0] == -1)
	{
		free_everything(data);
		exit (1);
	}
	data->correct_path = check_correct_path(data, nb);
	dup2(data->fd[0], 0);
	dup2(data->pipe_fd[nb][1], 1);
	close_all_pipes(data, data->child_nbr);
	if (execve(data->correct_path, data->split_args[nb], env) == -1)
	{
		free(data->correct_path);
		cmd_not_found_err(data, nb);
	}
}

void	last_cmd(t_data *data, char **env)
{
	const int	nb = data->child_nbr - 1;

	data->correct_path = check_correct_path(data, nb);
	dup2(data->pipe_fd[nb - 1][0], 0);
	dup2(data->fd[1], 1);
	close_all_pipes(data, -1);
	if (execve(data->correct_path, data->split_args[nb], env) == -1)
	{
		free(data->correct_path);
		cmd_not_found_err(data, nb);
	}
}

void	middle_cmd(t_data *data, char **env)
{
	const int	nb = data->child_nbr - 1;

	data->correct_path = check_correct_path(data, nb);
	dup2(data->pipe_fd[nb - 1][0], 0);
	dup2(data->pipe_fd[nb][1], 1);
	close_all_pipes(data, data->child_nbr);
	if (execve(data->correct_path, data->split_args[nb], env) == -1)
	{
		free(data->correct_path);
		cmd_not_found_err(data, nb);
	}
}

int	make_children(t_data *data, char **env, int ac)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid != 0)
	{
		data->child_nbr++;
		data->here_doc = false;
		return (0);
	}
	else if (data->here_doc == true)
		first_cmd(data, env);
	else if (data->child_nbr == 1)
		first_cmd(data, env);
	else if (data->child_nbr == ac - 3)
		last_cmd(data, env);
	else
		middle_cmd(data, env);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		fd_in[2];
	int		inpipe_count;
//	int		fd_out[2];	


	if (ac < 5)
		exit (1);
	init_data(&data, av, env, ac);
	inpipe_count = 0;
	while (data.child_nbr < ac - 2)
	{
		printf("[%s]\n", data.split_args[data.child_nbr - 1][0]);
		if (ft_strncmp(data.split_args[data.child_nbr - 1][0], "pipe", 5) == 0)
		{
			if (pipe(fd_in) == - 1)
				perror("pipe in main");
			data.child_nbr++;
		}
		else if (inpipe_count == 2)
		{
			close (fd_in[0]);
			close (fd_in[1]);
		}
		else
		{
			inpipe_count++;
			make_children(&data, env, ac);
		}
	}
	close_all_pipes(&data, -1);
	close(data.fd[0]);
	close(data.fd[1]);
	while (wait(0) != -1)
		continue ;
	free_everything(&data);
	exit(0);
}*/
