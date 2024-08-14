/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:15:22 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/12 11:34:24 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include "../libft/libft.h"

void	close_pipes(int **fd);
void	free_pipes(int **fd);
void	error_msg(char *msg, int **fd, char *str, int exit_status);

void	free_tab(char **tab);
char	*get_path(char *cmd, char **env);
char	*my_getenv(char *name, char **env);
int		open_file(char *file, int in_or_out);

#endif
