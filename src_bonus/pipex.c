/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:48:40 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/28 10:50:14 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		exit_code;

	if (!check_args(argc, argv))
		return (3);
	argv = quote_space_parser(argc, argv);
	pipex = pipex_init(argc, argv, envp);
	if (!pipex)
		return (4);
	pipex->pipefd = get_pipes(pipex);
	if (!pipex->pipefd)
	{
		close_n_free(pipex);
		return (4);
	}
	pipex_process(pipex, envp);
	exit_code = analyze_exit_code(pipex->exit_code, pipex);
	close_n_free(pipex);
	return (exit_code);
}
