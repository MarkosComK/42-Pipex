/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:14:18 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/24 22:18:20 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*pipex_init(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = malloc(1 * sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->pipefd = NULL;
	pipex->cmd_nb = 0;
	pipex->cmd_start = NULL;
	pipex->path = path_to_llist(envp, info);
	return (pipex);
}

