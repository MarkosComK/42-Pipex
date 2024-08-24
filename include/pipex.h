/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:12:30 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/24 22:06:21 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

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

typedef struct s_cmd
{
	int				index;
	char			*cmd_name;
	char			*cmd_path;
	char			**cmd_argv;
	int				exist;
	int				is_exec;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_info
{
	t_files	*files;
	t_list	*path;
	t_cmd	*cmd;
	t_cmd	*cmd_start;
	int		**pipefd;
	int		cmd_nb;
	pid_t	last_pid;
	int		exit_code;
}				t_info;

//check_args.c
int	check_args(int argc, char **argv);

//parser.c
char	**quote_space_parser(int argc, char **argv);
int		counter(char *str, char c);
char	*space_to_minus(char *str);
char	*dequote_single(char *str);

#endif
