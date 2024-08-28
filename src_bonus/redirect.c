/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 01:24:37 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/25 17:51:41 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_process(t_pipex *pipex, char **envp)
{
	pid_t	pid;

	while (pipex->cmd)
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
			redirect(pipex, envp);
		if (pid > 0)
		{
			if (!pipex->cmd->next)
				pipex->last_pid = pid;
			if (pipex->cmd->index == 1)
				close(pipex->pipefd[pipex->cmd->index - 1][WRITE_END]);
			else if (pipex->cmd->index != 0)
			{
				close(pipex->pipefd[pipex->cmd->index - 2][READ_END]);
				close(pipex->pipefd[pipex->cmd->index - 1][WRITE_END]);
			}
		}
		pipex->cmd = pipex->cmd->next;
	}
	close(pipex->pipefd[pipex->cmd_nb - 2][READ_END]);
	wait_cmds(pipex);
}

void	redirect(t_pipex *pipex, char **envp)
{
	if (pipex->cmd->index == 0)
		dup_first_cmd(pipex);
	else if (pipex->cmd->next)
		dup_mid_cmd(pipex);
	else
		dup_last_cmd(pipex);
	if (pipex->cmd->exist)
	{
		if (!ft_strchr(pipex->cmd->cmd_name, '/'))
			ft_putendl_fd(CNFD, 2);
		else
			ft_putendl_fd(NSFD, 2);
		close_n_free(pipex);
		exit(EXIT_FAILURE);
	}
	close_pipefd(pipex->cmd_nb, pipex->pipefd);
	close_files(pipex->files);
	execve(pipex->cmd->cmd_path, pipex->cmd->cmd_argv, envp);
	perror("pipex (execve)");
	close_n_free(pipex);
	exit(EXIT_FAILURE);
}

void	wait_cmds(t_pipex *pipex)
{
	int		child_status;
	pid_t	ret;

	ret = 0;
	while (ret != -1)
	{
		if (ret == pipex->last_pid)
			pipex->exit_code = child_status;
		ret = waitpid(-1, &child_status, 0);
	}
}
