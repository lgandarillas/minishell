/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:01:11 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/15 19:25:36 by lgandari         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	(void)argv;
	printf("INPUT: %s\n", argv[1]);
	printf("WORDS: %d\n", count_words(argv[1]));
}
