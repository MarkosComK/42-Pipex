/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:12:30 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/25 17:55:37 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

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

typedef struct s_pipex
{
	t_files	*files;
	t_list	*path;
	t_cmd	*cmd;
	t_cmd	*cmd_start;
	int		**pipefd;
	int		cmd_nb;
	pid_t	last_pid;
	int		exit_code;
}				t_pipex;

//check_args.c
int		check_args(int argc, char **argv);

//close.c
void	close_n_free(t_pipex *pipex);
void	close_files(t_files *files);
void	close_pipefd(int cmd_nb, int **pipefd);

//cmd_list_frees.c
void	cmd_lstclear(t_cmd **start, void (*del)(void *));
void	cmd_lstdelone(t_cmd *cmd, void (*del)(void *));

//cmd_list_utils.c
t_cmd	*cmd_lstnew(char **cmd_spltd, int index);
t_cmd	*cmd_lstadd_back(t_cmd **start, t_cmd *new);
t_cmd	*cmd_lstlast(t_cmd *start);
int		cmd_lstsize(t_cmd *start);

//cmd_parser.c
t_cmd	*cmd_parser(char **argv, t_pipex *pipex);
int		set_cmd_infos(t_cmd **start, t_list *path);
void	path_finder(t_cmd *cmd, t_list *path);

//create_path_list.c
t_list	*path_to_llist(char **envp, t_pipex *pipex);
t_list	*create_path_list(char **tmp, t_pipex *pipex);

//dups.c
void	dup_first_cmd(t_pipex *pipex);
void	dupper(int new_fd, int old_fd, t_pipex *pipex);
void	dup_mid_cmd(t_pipex *pipex);
void	dup_last_cmd(t_pipex *pipex);

//free.c
void	free_char_matrix(char **matrix);
void	free_int_matrix(int **matrix, int size);
int		analyze_exit_code(int status, t_pipex *pipex);

//get_pipes.c
int		**get_pipes(t_pipex *pipex);

//list_test
void	print_paths(t_list *list);
void	print_files(t_files files);
void	print_cmd_list(t_cmd *start);

//quote_parser.c
char	**quote_space_parser(int argc, char **argv);
int		counter(char *str, char c);
char	*space_to_minus(char *str);
char	*dequote_single(char *str);

//pipex_init.c
t_pipex	*pipex_init(int argc, char **argv, char **envp);
t_files	*file_parser(int argc, char **argv);
void	open_files(t_files *files);
void	launch_here_doc(t_files *files);
char	*str_join_double_free(char *s1, char *s2);

//redirect.c
void	pipex_process(t_pipex *pipex, char **envp);
void	redirect(t_pipex *pipex, char **envp);
void	wait_cmds(t_pipex *pipex);

#endif
