/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:01:11 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/23 18:48:33 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_words(const char *str)
{
	int		i;
	int		words;
	bool	in_quote;
	char	quote_char;

	i = 0;
	words = 0;
	in_quote = false;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && !in_quote)
		{
			in_quote = true;
			quote_char = str[i];
			i++;
			while (str[i] && str[i] != quote_char)
				i++;
			if (str[i])
				i++;
			words++;
		}
		else if (!in_quote && str[i] == ' ' && (i == 0 || str[i - 1] == ' '))
		{
			words++;
			while (str[i] && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
				i++;
		}
		else
			i++;
	}
	return (words);
}

static char	*extract_quoted_block(const char *str, size_t *index)
{
	char	quote_char;
	int		start;

	start = *index;
	quote_char = str[start];
	(*index)++;
	while (str[*index] && str[*index] != quote_char)
		(*index)++;
	if (str[*index])
		(*index)++;
	return (ft_substr(str, start, *index - start));
}

static char	*extract_word(const char *str, size_t *index)
{
	int	start;

	start = *index;
	while (str[*index] && str[*index] != ' ' && str[*index] != '\"' && str[*index] != '\'')
		(*index)++;
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
	num_words = count_words(str);
	result = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!result)
		return (NULL);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		if (str[i] == '\"' || str[i] == '\'')
			result[j] = extract_quoted_block(str, &i);
		else
			result[j] = extract_word(str, &i);	// SEGFAULT
		if (!result[j])
		{
			free_matrix(result);
			return (NULL);
		}
		j++;
	}
	result[j] = NULL;
	return (result);
}
