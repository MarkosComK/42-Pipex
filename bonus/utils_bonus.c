/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:56:40 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/12 11:56:54 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_filterenv(char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	return (&env[i][5]);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**paths;
	char	*tmp_exec;
	char	**split_cmd;

	i = 0;
	paths = ft_split(ft_filterenv(env), ':');
	split_cmd = ft_split(cmd, ' ');
	while (paths[i])
	{
		tmp_exec = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(tmp_exec, split_cmd[0]);
		free(tmp_exec);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_tab(split_cmd);
			return (exec);
		}
		free(exec);
		i++;
	}
	free_tab(paths);
	free_tab(split_cmd);
	return (cmd);
}

void	close_pipes(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	free_pipes(int	**fd)
{
	int	i;

	i = -1;
	while (fd[++i])
		free(fd[i]);
	free(fd);
}

void	error_msg(char *msg, int **fd, char *str, int exit_status)
{
	int	len;

	if (fd)
	{
		close_pipes(fd);
		free_pipes(fd);
	}
	if (str)
		free(str);
	if (msg)
	{
		len = ft_strlen(msg);
		write(2, msg, len);
	}
	exit(exit_status);
}

