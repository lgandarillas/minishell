/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:44:14 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/13 13:59:20 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	next_node_end(char *prompt, int i)
{
	int	quote;

	quote = 0;
	if (is_token(prompt[i]))
		return (skip_tokens(prompt, i));
	while (prompt[i])
	{
		if ((prompt[i] == 34 || prompt[i] == 39) && quote == 0)
		{
			quote = prompt[i];
			i++;
			while (prompt[i] && prompt[i] != quote)
				i++;
			if (prompt[i] != quote)
				break ;
			i++;
		}
		if (is_token(prompt[i]))
			return (i);
		if (prompt[i])
			i++;
	}
	return (i);
}

static bool	tokenize_prompt(char *prompt, t_token **head)
{
	char	*token_str;
	int		start;
	int		end;
	int		i;

	i = 0;
	while (prompt[i])
	{
		start = i;
		end = next_node_end(prompt, start);
		if (end > start)
		{
			token_str = ft_strndup(prompt + start, end - start);
			if (!token_str)
				return (false);
			append_node(head, token_str);
			free(token_str);
			i = end;
		}
		else
			i++;
	}
	return (true);
}

t_token	*lexer(char *prompt)
{
	t_token	*head;

	head = NULL;
	if (!prompt)
		return (head);
	if (!tokenize_prompt(prompt, &head))
		return (NULL);
	analyze_tokens_type(head);
	print_tokens(head);
	return (head);
}
