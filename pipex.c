/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:21 by marsoare          #+#    #+#             */
/*   Updated: 2024/07/24 15:53:01 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd1_execute(char **av, int *pipe_fds)
{
	int	fd;
	fd = open(av[1], O_RDONLY);
	dup2(fd, STDIN_FILENO);
	dup2(pipe_fds[0], STDOUT_FILENO);
	execute();

}

void	cmd2_execute(char **av, int *pipe_fds)
{

}

int main(int ac, char **av)
{
	int		pipe_files[2];
	pid_t	pid;

	if (pipe(pipe_files) == -1)
		perror("error in pipe");
	if ((pid = fork()) == -1);
		perror("error in fork");
	if (!pid)
		cmd1_execute(av, pipe_files);
	if (pid)
		cmd2_execute(av, pipe_files);
}
