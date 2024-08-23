/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:29:01 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/23 10:14:26 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

void	here_doc(char *limiter)
{
	char	*line;
	int		fd[2];
	pid_t	reader;

	if (pipe(fd) == -1)
		exit(0);
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (42)
		{
			line = get_next_line(0);
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	wait(NULL);
}

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], STDERR);
		free_tab(s_cmd);
		exit(0);
	}
}

void	redir(char *cmd, char **env, int fdin)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		if (fdin == STDIN)
			exit(1);
		else
			exec(cmd, env);
	}
}

int	main(int ac, char **av, char **env)
{
	int	fdin;
	int	fdout;
	int	i;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			i = 3;
			fdout = open_file(av[ac - 1], OUTFILE);
			here_doc(av[2]);
		}
		else
		{
			i = 2;
			fdout = open_file(av[ac - 1], OUTFILE);
			fdin = open_file(av[1], INFILE);
			dup2(fdin, STDIN);
		}
		while (i < ac - 2)
			redir(av[i++], env, 1);
		dup2(fdout, STDOUT);
		exec(av[i], env);
	}
	write(STDERR, "Invalid number of arguments.\n", 29);
}
