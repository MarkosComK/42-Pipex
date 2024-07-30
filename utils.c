/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:29:46 by marsoare          #+#    #+#             */
/*   Updated: 2024/07/30 11:35:14by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	size_t	i;
	
	i = 0;
	while(tab[i])
	{
		free(tab[i++]);
	}
	free(tab);
}

void	error_msg(char *str)
{
	ft_putstr_fd("\33[31m", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("\33[0m", 2);
}
char	*filterenv(char *name, char **env)
{
	int		i;

	i = 0;
	while (ft_strncmp(name, env[i], 4))
		i++;
	return (&env[i][5]);
}

char	*get_path(char *cmd, char **env)
{
	char	**split_cmd;
	char	**paths;
	int		i;

	paths = ft_split(filterenv("PATH", env), ':');
	i = 0;
	split_cmd = ft_split(cmd, ' ');
	/*
	while (paths[i])
	{
		//check somehow each path to find if the command are in it
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_tab(split_cmd);
			return (exec); //if find the cmd
		}
		free(exec);
	}
	*/
/*
	free_tab(paths);
	free_tab(split_cmd);
*/
	return (cmd);
}