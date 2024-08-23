/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:01:11 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/23 19:39:28 by lgandari         ###   ########.fr       */
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
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		if ((str[i] == '\"' || str[i] == '\'') && !in_quote)
		{
			in_quote = true;
			quote_char = str[i++];
			while (str[i] && str[i] != quote_char)
				i++;
			if (str[i])
				i++;
			in_quote = false;
		}
		else
		{
			while (str[i] && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
				i++;
		}
		words++;
	}
	return (words);
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
		while (str[*index] && str[*index] != ' ' && str[*index] != '\"' && str[*index] != '\'')
			(*index)++;
	}
	if (*index > start)
		return (ft_substr(str, start, *index - start));
	else
		return (NULL);
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
		result[j] = extract_block(str, &i);
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
