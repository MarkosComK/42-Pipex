/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:21 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/23 10:31:23 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_exec_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], STDERR);
		free_tab(s_cmd);
		exit(127);
	}
}


void	child(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[1], INFILE);
	dup2(fd, STDIN);
	dup2(p_fd[1], STDOUT);
	close(p_fd[0]);
	exec(av[2], env);
}

void	parent(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[4], OUTFILE);
	dup2(fd, STDOUT);
	dup2(p_fd[0], STDIN);
	close(p_fd[1]);
	exec(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (ac != 5 || pipe(p_fd) == -1)
		error_msg("Invalid arguments number!\n", NULL, -1, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		error_msg("Error calling fork!\n", p_fd, -1, EXIT_FAILURE);
	if (!pid)
		child(av, p_fd, env);
	parent(av, p_fd, env);
}
