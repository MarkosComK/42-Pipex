/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:03:22 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/24 21:04:46 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**quote_space_parser(int argc, char **argv)
{
	int	i;
	int	count;

	i = 0;
	if (argc > 1)
	{
		while (argv[i])
		{
			count = counter(argv[i], 39);
			if (count & 1)
			{
				ft_putstr_fd("Quote error (odd number). Pipex exiting.\n", 2);
				exit(EXIT_FAILURE);
			}
			argv[i] = space_to_minus(argv[i]);
			argv[i] = dequote_single(argv[i]);
			i++;
		}
	}
	return (argv);
}
