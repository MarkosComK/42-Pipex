/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:21 by marsoare          #+#    #+#             */
/*   Updated: 2024/07/23 19:47:24 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av)
{
	char	*argv[] =  {"cat", "./infile", NULL};
	if (execve("/bin/cat", argv, NULL) == -1)
		perror("execve"); // Print error message if execve fails
	return 0;
}
