/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:29:46 by marsoare          #+#    #+#             */
/*   Updated: 2024/07/25 21:51:12 by marsoare         ###   ########.fr       */
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
char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		//walk over the env and return everyting after the PATH=
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	//allpaths = ft_split(my_getenv("PATH", env), ':');
	//char *path = allpath[0];
	/*
	while(allpath++)
		write(2, *allpath, ft_strlen(*allpath));
	s_cmd = ft_split(cmd, ' ');
	*/
	while (allpath[i])
	{
		//check somehow each path to find if the command are in it
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_tab(s_cmd);
			return (exec); //if find the cmd
		}
		free(exec);
	}
	// free everything if dont and handle the error
	free_tab(allpath);
	free_tab(s_cmd);
	return (cmd);
}