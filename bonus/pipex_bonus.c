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

}

int	main(int argc, char *argv[], char *envp[])
{
	int	**fd;
	int	pid;
	int	i;

	if (argc < 5)
		exit_msg("Invalid number of arguments!\n", NULL, NULL, 1);
	fd = creat_pipes(argc - 4);
	i = -1;
	while (++i < argc - 4)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				input(argv, envp, fd);
			else
				execute(i, argv, envp, fd);
		}
	}
	output(argc, argv, envp, fd);
}
