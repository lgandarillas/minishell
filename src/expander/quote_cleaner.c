/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:15:28 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/17 19:47:48 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*clean_line_quotes(char *arg)
{
	char	*cleaned_line;
	char	quote_char;
	size_t	i;
	size_t	j;

	cleaned_line = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	if (!cleaned_line)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			quote_char = arg[i];
			i++;
			while (arg[i] && arg[i] != quote_char)
				cleaned_line[j++] = arg[i++];
			if (arg[i])
				i++;
		}
		else
			cleaned_line[j++] = arg[i++];
	}
	cleaned_line[j] = '\0';
	return (cleaned_line);
}

char	**quote_cleaner(char **argv)
{
	char	**new_args;
	size_t	arrlen;
	size_t	i;

	arrlen = ft_arrlen((void **)argv);
	new_args = malloc(sizeof(char *)*(arrlen + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < arrlen)
	{
		new_args[i] = clean_line_quotes(argv[i]);
		i++;
	}
	new_args[i] = NULL;
	return (new_args);
}
