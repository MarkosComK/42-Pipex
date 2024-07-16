/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:21 by marsoare          #+#    #+#             */
/*   Updated: 2024/07/16 16:20:02 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

int main(int agrc, char* argv[])
{
	int id1 = fork();
	int id2 = fork();
	if (id1 == 0 && id2 == 0){
		return 0;
		printf("last process\n");
	}
	printf("Process id: %d\n Parent id: %d \n fork1(%d) \n fork2(%d) \n\n", getpid(), getppid(), id1, id2);
	while(wait(NULL) != -1 || errno != ECHILD)
		printf("wait\n");
	return 0;
}
