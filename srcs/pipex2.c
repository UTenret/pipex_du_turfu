/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utenret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:27:39 by utenret           #+#    #+#             */
/*   Updated: 2023/02/08 15:30:54 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <bsd/string.h>
# include <assert.h>
# include <stdint.h>
# include <limits.h>
# include <stdbool.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	int		fd_in[2];
	int		fd_out[2];	
	int		inpipe_count;
	int		outpipe_count;

	inpipe_count = 0;
	outpipe_count = 0;
	while (ac > 1)
	{
		printf("")
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
}
