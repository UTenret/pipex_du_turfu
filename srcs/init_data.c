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
