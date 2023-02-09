/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:35:28 by utenret           #+#    #+#             */
/*   Updated: 2023/01/30 14:10:07 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data {
	char	**split_path;
	char	*path;
	char	*correct_path;
	char	***split_args;
	char	**cmd_name;
	int		**pipe_fd;
	int		fd[2];
	pid_t	pid;
	int		child_nbr;
	bool	here_doc;
}					t_data;

///////////////////free_func///////////////////////

void	free_cmd_name(t_data *data);
void	free_split_path(t_data *data);
void	free_split_args(t_data *data);
void	free_everything(t_data *data);

///////////////////free_func_cont///////////////////////

void	cmd_not_found_err(t_data *data, int i);
void	close_all_pipes(t_data *data, int read);
void	unlink_here_doc(void);

///////////////////init_data///////////////////////

void	init_data(t_data *data, char **av, char **env, int ac);
void	init_data_fd(t_data *data, char **av, int ac);
void	init_data_pipe(t_data *data, int ac);
void	init_data_cmd_names(t_data *data, int ac);
void	init_data_path(t_data *data, char **env);

///////////////////init_data_cont//////////////////

void	init_data_split(t_data *data, char **av, int ac);
void	init_data_split_args(t_data *data, char **av, int ac);
char	*find_path(char **env);
void	init_here_doc(t_data *data);

//////////////////check_path///////////////////////

bool	cmd_name_contains_path(t_data *data, int i);
void	print_path_error(t_data *data, int i, char *join);
char	*check_correct_path(t_data *data, int i);

#endif
