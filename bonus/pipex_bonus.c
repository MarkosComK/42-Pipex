/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:29:01 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/12 11:32:19 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

void	here_doc_input(char *limiter, int **fd)
{
	char	*line;

	while (42)
	{
		line = get_next_line(0);
		if (ft_memcmp(limiter, line, ft_strlen(line) - 1) == 0)
			break ;
		write(fd[0][1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	exit(0);
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

void	redir (char *cmd, char **env, int fdin)
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

int	main (int ac, char **av, char **env)
{
	int	fdin;
	int	fdout;
	int	i;

	i = 3;
	if (ac >= 5)
	{
		fdout = open_file(av[ac - 1], OUTFILE);
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
			write(STDERR, "here_doc", 8);
		fdin = open_file(av[1], INFILE);
		dup2(fdin, STDIN);
		dup2(fdout, STDOUT);
		redir(av[2], env, fdin);
		while (i < ac - 2)
			redir(av[i++], env, 1);
		exec(av[i], env);
	}
	else
		write(STDERR, "Invalid number of arguments.\n", 29);
	return (1);
}
