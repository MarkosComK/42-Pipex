/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:29:29 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/25 01:48:13 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_char_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	free_int_matrix(int **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
		free(matrix[i++]);
	free(matrix);
}

int	analyze_exit_code(int status, t_pipex *pipex)
{
	if (pipex->files->out_w)
		return (1);
	pipex->cmd = cmd_lstlast(pipex->cmd_start);
	if (pipex->cmd->exist)
		return (127);
	if (pipex->cmd->is_exec)
		return (126);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (status);
}
