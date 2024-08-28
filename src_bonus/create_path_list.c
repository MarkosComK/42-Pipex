/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:35:22 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/25 17:35:36 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list	*path_to_llist(char **envp, t_pipex *pipex)
{
	t_list	*path;
	char	**tmp;

	while (*envp)
	{
		if (!ft_strncmp("PATH", *envp, 4))
			break ;
		envp++;
	}
	path = NULL;
	if (*envp)
	{
		tmp = ft_split(ft_strchr(*envp, '=') + 1, ':');
		if (!tmp)
		{
			free(pipex);
			exit(-2);
		}
		path = create_path_list(tmp, pipex);
	}
	return (path);
}

t_list	*create_path_list(char **tmp, t_pipex *pipex)
{
	int		i;
	char	*content;
	t_list	*new;
	t_list	*path;

	i = -1;
	path = NULL;
	while (tmp[++i])
	{
		content = ft_strdup(tmp[i]);
		new = ft_lstnew(content);
		if (!content || !new)
		{
			free(content);
			free(new);
			ft_lstclear(&path, &free);
			free_char_matrix(tmp);
			free(pipex);
			exit(-2);
		}
		ft_lstadd_back(&path, new);
	}
	free_char_matrix(tmp);
	return (path);
}
