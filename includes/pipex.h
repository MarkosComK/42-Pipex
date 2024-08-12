/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:26:02 by marsoare          #+#    #+#             */
/*   Updated: 2024/07/25 20:21:04 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"

void	free_tab(char **tab);
void	error_msg(char *str, int *fd, int file, int exit_code);
char	*get_path(char *cmd, char **env);
char	*my_getenv(char *name, char **env);
int		open_file(char *file, int in_or_out);

#endif
