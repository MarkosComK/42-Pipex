/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:03:22 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/24 21:37:29 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* nb of single quotes not escapped by \ */

int	counter(char *str, char c)
{
	int		i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		if (i > 0 && *str == c && *(str - 1) == '\\')
			i--;
		str++;
	}
	return (i);
}

/*
 *	If not quoted, if a backslash followed by any character:
 *	skip the backslash and the following character (increment
 *	the string pointer twice).
 *	If not quoted, if a single quote and the previous character
 *	is not a backslash: replace the single quote with -1.
 *	ASCII codes: Single quote (') is ASCII 39, backslash (\) is ASCII 92.
 *	EX:
 *	Original string: This is a 'string with spaces' and a backslash \ space
 *	Modified string: This-is-a-'string-with-spaces'-and-a-backslash-\space
 *
 *	int main()
 *	{
	char *input = "This is a 'string with spaces' and a backslash \\ space";
	char *output = space_to_minus(input);

	printf("Original string: %s\n", input);
	printf("Modified string: %s\n", output);

	return 0;
	}
 */
char	*space_to_minus(char *str)
{
	int			in_quote;
	int			i;

	in_quote = 0;
	i = -1;
	while (str[++i])
	{
		if (!in_quote && str[i] == 39)
			in_quote = 1;
		else if (in_quote && str[i] == 39)
			in_quote = 0;
		else if (!in_quote && str[i] == 92 && str [i + 1] == ' ')
			i++;
		else if (!in_quote && str[i] == ' ')
			str[i] = -1;
	}
	return (str);
}

/*
 * Remove the single quote from the *STR but only when it's not
 * part of a escape sequence for EX
 * Input string:    "This is a 'string' with a backslash \\ and a single quote '"
 * Expected output: "This is a string with a backslash \ and a single quote '"
 */
char	*dequote_single(char *str)
{
	int			i;
	int			j;
	char		*new;
	static char	c = 39;

	i = -1;
	j = -1;
	new = str;
	while (str[++i])
	{
		if (str[i] != c && str[i] != '\\')
			new[++j] = str[i];
		else if (str[i] == '\\' && str[i + 1] != c && str[i + 1] != ' ')
			new[++j] = str[i];
		else if (i > 0 && str[i] == c && str[i - 1] == '\\')
			new[++j] = str[i];
	}
	new[++j] = '\0';
	return (new);
}

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
			if (count % 2 != 0)
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
