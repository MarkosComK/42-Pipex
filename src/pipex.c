/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:48:40 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/24 22:43:48 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		exit_code = 1;
	(void) envp;

	if (!check_args(argc, argv))
		return (3);
	argv = quote_space_parser(argc, argv);
	pipex = pipex_init(argc, argv, envp);
	print_list(pipex->path);
	return (exit_code);
}
