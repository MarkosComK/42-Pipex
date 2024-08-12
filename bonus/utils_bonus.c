/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:56:40 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/12 11:56:54 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

void	close_pipes(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	free_pipes(int	**fd)
{
	int	i;

	i = -1;
	while (fd[++i])
		free(fd[i]);
	free(fd);
}

void	exit_msg(char *msg, int **fd, char *str, int exit_status)
{
	int	len;

	if (fd)
	{
		close_pipes(fd);
		free_pipes(fd);
	}
	if (str)
		free(str);
	if (msg)
	{
		len = ft_strlen(msg);
		write(2, msg, len);
	}
	exit(exit_status);
}

