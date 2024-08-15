/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:01:11 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/15 20:04:56 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

static int	find_quote_block_end(const char *str, int start_index)
{
	char	quote_char;
	int		i;

	quote_char = str[start_index];
	i = start_index + 1;
	while (str[i] && str[i] != quote_char)
		i++;
	return (i + 1);
}

static int	count_words(const char *str)
{
	int		i;
	int		words;
	bool	in_word;

	i = 0;
	words = 0;
	in_word = false;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			i = find_quote_block_end(str, i);
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

static char	**allocate_result(size_t num_words)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!result)
		return (NULL);
	return (result);
}

static char	*handle_quote_block(const char *str, size_t *index)
{
	int	start;
	int	end;

	start = *index;
	end = find_quote_block_end(str, start);
	*index = end;
	return (ft_substr(str, start, end - start));
}

static char	*handle_word_block(const char *str, size_t *index)
{
	int	start;

	start = *index;
	while (str[*index] && str[*index] != ' ' && !is_quote(str[*index]))
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
	num_words = count_words(str);
	result = allocate_result(num_words);
	i = 0;
	j = 0;
	if (!result)
		return (NULL);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		if (is_quote(str[i]))
			result[j] = handle_quote_block(str, &i);	// SEGV here
		else
			result[j] = handle_word_block(str, &i);
		if (!result[j])
			return (free_matrix(result), NULL);
		j++;
	}
	result[j] = NULL;
	return (result);
}

/*
int	main(int argc, char **argv)
{
	char	**args;

	if (argc != 2 && argv[1] != NULL)
		return (0);
	printf("INPUT: %s\n", argv[1]);
	printf("WORDS: %d\n", count_words(argv[1]));
	args = word_splitter(argv[1]);
	return (0);
}
*/
