/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:12:30 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/24 20:57:54 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../libft/libft.h"

/* colors */
# define RED "\033[31m"
# define REDBOLD "\033[1;31m"
# define GREEN "\033[32m"
# define GREENBOLD "\033[1;32m"
# define BOLD "\033[1m"
# define UNDRLN "\033[4m"
# define END "\033[0m"

/* pipes */
# define READ_END 0
# define WRITE_END 1

/* custom err msg */
# define NSFD "pipex: no such file or directory: "
# define PDND "pipex: permission denied: "
# define CNFD "pipex: command not found: "

typedef struct files
{
	char	*inf;
	int		in_e;
	int		in_r;
	int		in_fd;
	char	*out;
	int		out_e;
	int		out_w;
	int		out_fd;
	int		here_doc;
	char	*lim;
}				t_files;

#endif
