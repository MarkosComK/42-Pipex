/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:21 by marsoare          #+#    #+#             */
/*   Updated: 2024/07/30 13:03:04 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	path = get_path(split_cmd[0], env);
	if (execve(path, split_cmd, env) == -1)
	{
		error_msg("Command not found");
		error_msg(cmd);
		free_tab(split_cmd);
		exit(0);
	}
}

void	cmd1_execute(char **av, int *pipe_fds, char **env)
{
	int	fd;

	fd = open(av[1], O_RDONLY, 0444);
	dup2(fd, STDIN_FILENO);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[0]);
	execute(av[2], env);
}

void	cmd2_execute(char **av, int *pipe_fds, char **env)
{
	int	fd;

	wait(NULL);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(pipe_fds[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(pipe_fds[1]);
	execute(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		pipe_files[2];
	pid_t	pid;

	pid = fork();
	if (ac != 5)
	{
		error_msg("Incorrect number of args");
		exit(0);
	}
	if (pipe(pipe_files) == -1)
		error_msg("error in pipe");
	if (pid == -1)
		error_msg("error in fork");
	if (pid == 0)
		cmd1_execute(av, pipe_files, env);
	waitpid(pid, NULL, 0);
	cmd2_execute(av, pipe_files, env);
}
