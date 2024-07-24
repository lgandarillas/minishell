/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:48:56 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/24 20:01:20 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/minishell.h"

// DELETE down

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

// DELETE up

static int	next_token_end(char *prompt, int i)
{
	int	quote;
	int	start_token;

	quote = 0;
	start_token = -1;
	while (prompt[i])
	{
		if ((prompt[i] == 34 || prompt[i] == 39) && quote == 0)
		{
			quote = prompt[i];
			i++;
			while (prompt[i] && prompt[i] != quote)
				i++;
			if (prompt[i] == quote)
				quote = 0;
			i++;
		}
		if (!quote)
		{
			if (is_space(prompt[i]))
			{
				while (is_space(prompt[i]))
					i++;
				continue ;
			}
			if (is_token(prompt[i]))
			{
				if (start_token == -1)
					start_token = i;
				while (is_token(prompt[i]))
					i++;
			}
			else if (start_token != -1)
				return (i);
		}
		i++;
	}
	return (i);
}

// DELETE down
int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	printf("%s\n", argv[1]);
	printf("i = %d\n", next_token_end(argv[1], 13));
	return (0);
}
// DELETE up

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
