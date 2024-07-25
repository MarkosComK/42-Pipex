/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:21 by marsoare          #+#    #+#             */
/*   Updated: 2024/07/25 13:43:16 by marsoare         ###   ########.fr       */
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

void	execute(char *cmd)
{
	char	**split_cmd;
	char	*path;
	
	split_cmd = ft_split(cmd, ' ');
	path = ft_strjoin("/bin/", split_cmd[0]);
	if (execve(path, split_cmd, NULL) == -1)
	{
		error_msg("Command not found");
		error_msg(cmd);
		free_tab(split_cmd);
		free(path);
	}
}

void	cmd1_execute(char **av, int *pipe_fds)
{
	int	fd;
	fd = open(av[1], O_RDONLY, 0777);
	dup2(fd, STDIN_FILENO);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[0]);
	execute(av[2]);

}

void	cmd2_execute(char **av, int *pipe_fds)
{
	int	fd;
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(pipe_fds[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(pipe_fds[1]);
	execute(av[3]);
}

int main(int ac, char **av)
{
	(void) ac;
	int		pipe_files[2];
	pid_t	pid;

	if (ac != 5)
		perror("Incorrect number of args");
	if (pipe(pipe_files) == -1)
		perror("error in pipe");
	if ((pid = fork()) == -1)
		perror("error in fork");
	if (!pid)
		cmd1_execute(av, pipe_files);
	if (pid)
		cmd2_execute(av, pipe_files);
}
