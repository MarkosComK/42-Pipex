/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:12:38 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/25 00:16:47 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*cmd_lstnew(char **cmd_spltd, int index)
{
	t_cmd	*new;

	if (!cmd_spltd)
		return (NULL);
	new = malloc(1 * sizeof(t_cmd));
	if (!new)
		return (free_char_matrix(cmd_spltd), NULL);
	new->cmd_argv = cmd_spltd;
	new->cmd_name = cmd_spltd[0];
	new->cmd_path = NULL;
	new->index = index;
	new->next = NULL;
	return (new);
}

t_cmd	*cmd_lstadd_back(t_cmd **start, t_cmd *new)
{
	t_cmd	*ptr;

	if (!start)
		return (NULL);
	if (!new)
		return (*start);
	if (start)
	{
		if (!*start)
		{
			*start = new;
			return (*start);
		}
		ptr = cmd_lstlast(*start);
		ptr->next = new;
	}
	return (*start);
}

t_cmd	*cmd_lstlast(t_cmd *start)
{
	if (!start)
		return (NULL);
	while (start->next)
		start = start->next;
	return (start);
}
