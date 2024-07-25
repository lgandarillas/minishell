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

#include "../inc/minishell.h"

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
