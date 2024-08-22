/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:29:46 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/07 11:10:02 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_msg(char	*msg, int *fd, int file, int exit_code)
{
	int	len;

	if (msg)
	{
		len = ft_strlen(msg);
		write(2, msg, len);
	}
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (file >= 0)
		close(file);
	exit(exit_code);
}

int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ret == -1)
		exit(1);
	return (ret);
}

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
