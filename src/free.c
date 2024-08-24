/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:29:29 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/24 23:53:13 by marsoare         ###   ########.fr       */
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

void	cmd_lstclear(t_cmd **start, void (*del)(void *))
{
	t_cmd	*tmp;

	if (!start || !*start)
		return ;
	while (*start)
	{
		tmp = (*start)->next;
		cmd_lstdelone(*start, del);
		*start = tmp;
	}
}

void	cmd_lstdelone(t_cmd *cmd, void (*del)(void *))
{
	if (!del || !cmd)
		return ;
	free_char_matrix(cmd->cmd_argv);
	if (cmd->cmd_path)
		(*del)(cmd->cmd_path);
	free(cmd);
}
