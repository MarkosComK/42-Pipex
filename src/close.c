/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:48:52 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/24 23:51:41 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_n_free(t_pipex *pipex)
{
	if (pipex->files)
	{
		close_files(pipex->files);
		if (pipex->files->here_doc)
			unlink("/tmp/.here_doc.txt");
		free(pipex->files);
	}
	if (pipex->cmd_nb && pipex->pipefd)
	{
		close_pipefd(pipex->cmd_nb, pipex->pipefd);
		free_int_matrix(pipex->pipefd, pipex->cmd_nb);
	}
	if (pipex->path)
		ft_lstclear(&(pipex->path), &free);
	if (pipex->cmd_start)
		cmd_lstclear(&(pipex->cmd_start), &free);
	free(pipex);
}

void	close_files(t_files *files)
{
	if (files->in_fd > 0)
		close(files->in_fd);
	if (files->out_fd > 0)
		close(files->out_fd);
}

void	close_pipefd(int cmd_nb, int **pipefd)
{
	int	i;

	if (!cmd_nb || !pipefd)
		return ;
	i = 0;
	while (i < cmd_nb - 1)
	{
		close(pipefd[i][WRITE_END]);
		close(pipefd[i][READ_END]);
		i++;
	}
}
