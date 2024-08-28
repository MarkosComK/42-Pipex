/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 01:12:49 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/25 17:44:01 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**get_pipes(t_pipex *pipex)
{
	int	i;
	int	**pipefd;

	pipefd = malloc((pipex->cmd_nb - 1) * sizeof(int *));
	if (!pipefd)
		return (NULL);
	i = 0;
	while (i < pipex->cmd_nb - 1)
	{
		pipefd[i] = malloc(2 * sizeof(int));
		if (!pipefd[i] || pipe(pipefd[i]) == -1)
		{
			perror("pipex");
			free_int_matrix(pipefd, i + 1);
			return (NULL);
		}
		i++;
	}
	return (pipefd);
}
