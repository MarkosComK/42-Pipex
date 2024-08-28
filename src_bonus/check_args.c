/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:59:50 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/28 10:52:29 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_args(int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putstr_fd("Provide at least 4 arguments\n", 2);
		ft_putstr_fd("Usage : ", 2);
		ft_putstr_fd("\"infile\" \"cmd1\" \"cmd2\" ... ", 2);
		ft_putstr_fd("\"cmdn\" \"outfile\"\n", 2);
		return (0);
	}
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) && argc < 6)
	{
		ft_putstr_fd("5 arguments needed if here_doc\n", 2);
		ft_putstr_fd("Usage : ", 2);
		ft_putstr_fd("here_doc \"Limiter\" \"cmd1\" \"cmd2\" ... ", 2);
		ft_putstr_fd("\"cmdn\" \"outfile\"\n", 2);
		return (0);
	}
	return (1);
}
