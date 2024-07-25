/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:48:56 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/25 13:20:52 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/minishell.h"

#include <stdio.h>
#include <stdbool.h>

bool	is_token(char c)
{
	if (c == '\0')
		return (false);
	if (c == '>' || c == '<' || c == '|')
		return (true);
	return (false);
}

bool	is_space(char c)
{
	if (c == '\0')
		return (false);
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

static int	skip_tokens(char *prompt, int i)
{
	while (is_token(prompt[i]))
		i++;
	return (i);
}

static int	skip_quoted_section(char *prompt, int i, int *quote)
{
	*quote = prompt[i];
	i++;
	while (prompt[i] && prompt[i] != *quote)
		i++;
	if (prompt[i] == *quote)
		*quote = 0;
	i++;
	return (i);
}

static int	next_token_end(char *prompt, int i)
{
	int	quote;
	int	start_token;

	quote = 0;
	start_token = -1;
	if (is_token(prompt[i]))
		return (skip_tokens(prompt, i));
	while (prompt[i])
	{
		if ((prompt[i] == 34 || prompt[i] == 39) && quote == 0)
			i = skip_quoted_section(prompt, i, &quote);
		if (is_token(prompt[i]))
			return (i);
		i++;
	}
	return (i);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	printf("%s\n", argv[1]);
	printf("i = %d\n", next_token_end(argv[1], 0));
	return (0);
}

/*
bool	tokenize_prompt(char *prompt)
{
	t_token	*token;
	int		i;

	if (prompt == NULL)
		return (false);
	i = 0;
	while (prompt[i])
	{
	
	}
}
*/
