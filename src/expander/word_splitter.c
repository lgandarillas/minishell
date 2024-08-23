/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:01:11 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/24 00:26:24 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_parts(char const *s)
{
	int		i;
	int		parts;
	char	quote_char;

	i = 0;
	parts = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && (i == 0 || s[i - 1] == ' '))
			parts++;
		if (s[i] == '\"' || s[i] == '\'')
		{
			quote_char = s[i];
			i++;
			while (s[i] != '\0' && s[i] != quote_char)
				i++;
			if (s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (parts);
}

static char	*extract_block(const char *str, size_t *index)
{
	char	quote_char;
	size_t	start;
	char	*result;

	start = *index;
	result = NULL;
	while (str[*index] && str[*index] != ' ')
	{
		if (str[*index] == '\"' || str[*index] == '\'')
		{
			quote_char = str[*index];
			(*index)++;
			while (str[*index] && str[*index] != quote_char)
				(*index)++;
			if (str[*index] == quote_char)
				(*index)++;
		}
		else
			(*index)++;
	}
	if (*index > start)
		result = ft_substr(str, start, *index - start);
	return (result);
}

static void	skip_spaces(char *str, size_t *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

static int	process_words(char *str, char **result)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		skip_spaces(str, &i);
		if (str[i] == '\0')
			break ;
		result[j] = extract_block(str, &i);
		if (!result[j])
			return (0);
		j++;
		skip_spaces(str, &i);
	}
	result[j] = NULL;
	return (1);
}

char	**word_splitter(char *str)
{
	char	**result;
	size_t	num_words;

	if (!str)
		return (NULL);
	num_words = count_parts(str);
	result = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!result)
		return (NULL);
	if (!process_words(str, result))
	{
		free_matrix(result);
		return (NULL);
	}
	return (result);
}
