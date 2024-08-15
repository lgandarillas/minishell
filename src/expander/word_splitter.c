/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:01:11 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/15 19:09:38 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#include "../../inc/minishell.h"

static bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

static int	count_words(const char *str)
{
	int		i;
	int		words;
	bool	in_word;
	char	quote_char;

	i = 0;
	words = 0;
	in_word = false;
	quote_char = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			if (quote_char == '\0')
			{
				quote_char = str[i];
				in_word = true;
			}
			else if (quote_char == str[i])
			{
				quote_char = '\0';
				words++;
				in_word = false;
			}
		}
		else if (quote_char == '\0' && (str[i] != ' ' && (i == 0 || str[i - 1] == ' ')))
		{
			words++;
			in_word = true;
		}
		else if (quote_char == '\0' && str[i] == ' ' && in_word)
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
