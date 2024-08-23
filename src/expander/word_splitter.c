/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:01:11 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/24 00:02:48 by lgandari         ###   ########.fr       */
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

	start = *index;
	if (str[start] == '\"' || str[start] == '\'')
	{
		quote_char = str[start];
		(*index)++;
		while (str[*index] && str[*index] != quote_char)
			(*index)++;
		if (str[*index] == quote_char)
			(*index)++;
	}
	else
	{
		while (str[*index] && str[*index] != ' ')
			(*index)++;
	}
	return (ft_substr(str, start, *index - start));
}

char	**word_splitter(char *str)
{
	char	**result;
	size_t	num_words;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	num_words = count_parts(str);
	printf("STR:%s\nWORDS=%ld\n", str, num_words);
	result = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!result)
		return (NULL);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		result[j] = extract_block(str, &i);
		if (!result[j])
		{
			free_matrix(result);
			return (NULL);
		}
		j++;
		while (str[i] == ' ')
			i++;
	}
	result[j] = NULL;
	return (result);
}
