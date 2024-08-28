/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_frees.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:16:06 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/25 00:16:15 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
