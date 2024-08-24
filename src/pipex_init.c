/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:14:18 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/24 22:32:10 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*pipex_init(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	(void) argv;
	(void) argc;

	pipex = malloc(1 * sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->pipefd = NULL;
	pipex->cmd_nb = 0;
	pipex->cmd_start = NULL;
	pipex->path = path_to_llist(envp, pipex);
	return (pipex);
}

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
