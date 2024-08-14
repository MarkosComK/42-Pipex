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

int	**create_pipes(int pipe_number)
{
	int	**fd;
	int	i;

	fd = ft_calloc(sizeof(*fd), pipe_number + 1);
	if (fd == NULL)
		error_msg("Error allocating memory for pipes!\n", NULL, NULL, 1);
	i = 0;
	while (i < pipe_number)
	{
		fd[i] = ft_calloc(sizeof(*fd[i]), 2);
		if (fd[i] == NULL)
		{
			while (i < pipe_number)
				free(fd[i++]);
			free_pipes(fd);
			error_msg("Error creating pipes!\n", NULL, NULL, 1);
		}
		i++;
	}
	i = 0;
	while (i < pipe_number)
		pipe(fd[i++]);
	return (fd);
}

void	input(char **argv, char **envp, int **fd)
{
	int		infile;
	char	*path;
	char	**cmd;

	if (ft_memcmp(argv[1], "here_doc", 8) == 0)
		here_doc_input(argv[2], fd);
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		error_msg("Error opening infile in input!\n", fd, NULL, 1);
	if (dup2(infile, 0) == -1 || dup2(fd[0][1], 1) == -1)
		error_msg("Error calling dup2 in output!\n", fd, NULL, 1);
	close(infile);
	close_pipes(fd);
	path = ft_filterenv(envp);
	if (path == NULL)
		error_msg("Error calling ft_strcut in input!\n", NULL, NULL, 1);
	path = get_path(path, envp);
	cmd = get_cmd(argv[2]);
	if (cmd == NULL)
		error_msg("Error calling get_cmd in input!\n", NULL, path, 1);
	if (execve(path, cmd, envp) == -1)
		panic_free("Error calling execve in input!\n", cmd, path, 1);
	panic_free("Command not found!\n", cmd, path, 127);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	**fd;
	int	pid;
	int	i;

	if (argc < 5)
		error_msg("Invalid number of arguments!\n", NULL, NULL, 1);
	fd = creat_pipes(argc - 4);
	i = 0;
	while (i < argc - 4)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				input(argv, envp, fd);
			else
				execute(i, argv, envp, fd);
		}
		i++;
	}
	output(argc, argv, envp, fd);
}
