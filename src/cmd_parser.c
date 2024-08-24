/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:00:09 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/25 00:17:37 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*cmd_parser(char **argv, t_pipex *pipex)
{
	t_cmd	*start;
	t_cmd	*tmp;
	char	**cmd_spltd;
	int		index;

	argv++;
	if (pipex->files->here_doc)
		argv++;
	start = NULL;
	index = -1;
	while (*(argv + 2))
	{
		cmd_spltd = ft_split(*(++argv), -1);
		if (!cmd_spltd)
			return (cmd_lstclear(&start, &free), NULL);
		tmp = cmd_lstnew(cmd_spltd, ++index);
		if (!tmp)
			return (cmd_lstclear(&start, &free), NULL);
		start = cmd_lstadd_back(&start, tmp);
	}
	if (set_cmd_infos(&start, pipex->path) == -2)
		return (NULL);
	return (start);
}


int	set_cmd_infos(t_cmd **start, t_list *path)
{
	t_cmd	*ptr;

	ptr = *start;
	while (ptr)
	{
		ptr->cmd_path = NULL;
		if (!ptr->cmd_name)
			ptr->cmd_name = " ";
		if (ft_strchr(ptr->cmd_name, '/'))
		{
			ptr->is_exec = access(ptr->cmd_name, X_OK);
			ptr->exist = access(ptr->cmd_name, F_OK);
			ptr->cmd_path = ft_strdup(ptr->cmd_name);
		}
		else
			path_finder(ptr, path);
		if (!ptr->cmd_path)
		{
			cmd_lstclear(start, &free);
			return (-2);
		}
		ptr = ptr->next;
	}
	return (0);
}

void	path_finder(t_cmd *cmd, t_list *path)
{
	char	*tmp_path;
	char	*tmp_name;

	tmp_name = ft_strjoin("/", cmd->cmd_name);
	if (!tmp_name)
		return ;
	while (path)
	{
		tmp_path = ft_strjoin(path->content, tmp_name);
		if (!tmp_path)
			return (free(tmp_name));
		if (!access(tmp_path, F_OK))
		{
			cmd->cmd_path = tmp_path;
			cmd->exist = access(tmp_path, F_OK);
			cmd->is_exec = access(tmp_path, X_OK);
			return (free(tmp_name));
		}
		free(tmp_path);
		path = path->next;
	}
	free(tmp_name);
	cmd->cmd_path = ft_strdup(cmd->cmd_name);
	cmd->exist = -1;
	cmd->is_exec = -1;
}
