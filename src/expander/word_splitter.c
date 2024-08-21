/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:01:11 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/21 15:59:03 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	init_count_words(const char *str, int *words, \
		int *len, bool *in_word)
{
	if (str)
	{
		*words = 0;
		*len = ft_strlen(str);
		*in_word = false;
		return (0);
	}
	else
	{
		*words = 0;
		*len = 0;
		*in_word = false;
		return (-1);
	}
}

static int	count_words(const char *str)
{
	int		i;
	int		words;
	int		len;
	bool	in_word;

	i = init_count_words(str, &words, &len, &in_word);
	while (i < len)
	{
		if (is_quote(str[i]))
		{
			i = find_quote_block_end(str, i);
			if (i <= len)
				words++;
			in_word = false;
		}
		else if (str[i] != ' ' && (i == 0 || str[i - 1] == ' '))
		{
			words++;
			in_word = true;
		}
		else if (str[i] == ' ' && in_word)
			in_word = false;
		i++;
	}
	return (words);
}

static bool	init_splitter_vars(char *str, char ***result, size_t *num_words)
{
	*num_words = count_words(str);
	*result = (char **)malloc(sizeof(char *) * (*num_words + 1));
	if (!*result)
		return (false);
	return (result != NULL);
}

char	**word_splitter(char *str)
{
	char	**result;
	size_t	num_words;
	size_t	i;
	size_t	j;

	if (!str || !init_splitter_vars(str, &result, &num_words))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		if (is_quote(str[i]))
			result[j] = handle_quote_block(str, &i);
		else
			result[j] = handle_word_block(str, &i);
		if (!result[j])
			return (free_matrix(result), NULL);
		j++;
	}
	result[j] = NULL;
	return (result);
}
