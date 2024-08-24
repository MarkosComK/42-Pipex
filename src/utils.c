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

void	cmd_msg(char *msg, char *cmd)
{
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(cmd, STDERR);
}

int	open_file(char *file, int in_or_out)
{
	if (in_or_out == INFILE)
	{
		if (access(file, F_OK))
		{
			write(STDERR, "pipex: ", 7);
			write(STDERR, file, ft_strlen(file));
			write(STDERR, ": No such file or directory\n", 28);
			return (STDIN);
		}
		else if (access(file, R_OK))
		{
			write(STDERR, "pipex: ", 7);
			write(STDERR, file, ft_strlen(file));
			write(STDERR, ": Permission denied\n", 20);
			return (STDIN);
		}
		return (open(file, O_RDONLY));
	}
	else
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
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
