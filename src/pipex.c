/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:48:40 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/24 21:51:35 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		exit_code = 1;
	(void) envp;
	(void) argv;
	(void) argc;

	//argv = quote_space_parser(argc, argv);
	char input[] = "This is a 'string with spaces' and a backslash \\ space";
	char *output = space_to_minus(input);

	ft_printf("Original string: %s\n", input);
	ft_printf("Modified string: %s\n", output);
	return (exit_code);
}
