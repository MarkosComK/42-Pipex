/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:47:11 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/25 17:50:13 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup_first_cmd(t_pipex *pipex)
{
	close(pipex->pipefd[pipex->cmd->index][READ_END]);
	dupper(pipex->pipefd[pipex->cmd->index][WRITE_END], 1, pipex);
	if (!pipex->files->in_e && !pipex->files->in_r)
		dupper(pipex->files->in_fd, 0, pipex);
	else
	{
		close(pipex->pipefd[pipex->cmd->index][WRITE_END]);
		if (pipex->files->in_e)
			ft_putendl_fd(NSFD, 2);
		else if (pipex->files->in_r)
			ft_putendl_fd(PDND, 2);
		close_n_free(pipex);
		exit(EXIT_FAILURE);
	}
}

void	dupper(int new_fd, int old_fd, t_pipex *pipex)
{
	if (dup2(new_fd, old_fd) == -1)
	{
		perror("pipex (dup2)");
		close_n_free(pipex);
		exit(EXIT_FAILURE);
	}
}

void	dup_mid_cmd(t_pipex *pipex)
{
	close(pipex->pipefd[pipex->cmd->index - 1][WRITE_END]);
	close(pipex->pipefd[pipex->cmd->index][READ_END]);
	dupper(pipex->pipefd[pipex->cmd->index - 1][READ_END], 0, pipex);
	dupper(pipex->pipefd[pipex->cmd->index][WRITE_END], 1, pipex);
}

void	dup_last_cmd(t_pipex *pipex)
{
	dupper(pipex->pipefd[pipex->cmd->index - 1][READ_END], 0, pipex);
	if (!pipex->files->out_w)
		dupper(pipex->files->out_fd, 1, pipex);
	else
	{
		close(pipex->pipefd[pipex->cmd->index - 1][READ_END]);
		ft_putendl_fd(PDND, 2);
		pipex->exit_code = 1;
		close_n_free(pipex);
		exit(EXIT_FAILURE);
	}
}
