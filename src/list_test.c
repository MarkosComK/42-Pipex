/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:33:28 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/24 22:50:21 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_list(t_list *list)
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
