/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:33:28 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/24 23:41:12 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_paths(t_list *list)
{
	t_list	*current;
	int		index;

	current = list;
	index = 0;
	ft_printf("[Node] -> [%- 40s]\n", "Content");
	while (current)
	{
		ft_printf("[%-4i] -> [%-40 s]\n", index, current->content);
		current = current->next;
		index++;
	}
}

void	print_files(t_files files)
{
	ft_printf("%-20s | % 20s\n", "FILES", "STATUS");
	ft_printf("%-20s   % 20s\n", "~", "~");
	if (!files.here_doc)
	{
		ft_printf("%-20s | % 20s\n", "infile name", files.inf);
		ft_printf("%-20s | % 20i\n","infile exist", files.in_e);
		ft_printf("%-20s | % 20i\n","infile R_OK", files.in_r);
		ft_printf("%-20s | % 20i\n","infile fd", files.in_fd);
		ft_printf("%-20s   % 20s\n", "~", "~");
	}
	else
	{
		ft_printf("here_doc?:    % 40i\n", files.here_doc);
		ft_printf("lim:          % 40s\n", files.lim);
		ft_printf("inf_fd:       % 40i\n", files.in_fd);
	}
	ft_printf("%-20s | % 20s\n","outfile", files.out);
	ft_printf("%-20s | % 20i\n","outfile exist", files.out_e);
	ft_printf("%-20s | % 20i\n","outfile WR_OK", files.out_w);
	ft_printf("%-20s | % 20i\n","outfile fd", files.out_fd);
}
