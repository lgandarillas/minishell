/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:44:14 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/04 16:38:02 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	next_token_end(char *prompt, int i)
{
	int	quote;

	quote = 0;
	if (is_token(prompt[i]))
		return (skip_tokens(prompt, i));
	while (prompt[i])
	{
		if ((prompt[i] == 34 || prompt[i] == 39) && quote == 0)
		{
			i = skip_quoted_section(prompt, i, &quote);
			if (prompt[i] == '\0')
				break ;
		}
		if (is_token(prompt[i]))
			return (i);
		i++;
	}
	return (i);
}

static bool	add_next_node(char *prompt, int *i, t_token **head)
{
	char	*token_str;
	int		start;
	int		end;

	start = *i;
	end = next_token_end(prompt, start);
	if (end > start)
	{
		token_str = ft_strndup(prompt + start, end - start);
		if (!token_str)
			return (false);
		append_node(head, token_str);
		free(token_str);
		*i = end;
		return (true);
	}
	return (false);
}

bool	lexer(char *prompt)
{
	t_token	*head;
	int		i;

	if (!prompt)
		return (false);
	head = NULL;
	i = 0;
	while (prompt[i])
	{
		if (!add_next_node(prompt, &i, &head))
			return (false);
		analyze_tokens_type(head);
	}
	print_tokens(head);
	free_tokens(head);
	return (true);
}
