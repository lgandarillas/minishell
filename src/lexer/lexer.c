/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:44:14 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/25 15:05:31 by aquinter         ###   ########.fr       */
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

static bool	process_token(char *prompt, int *i, t_lexer **node)
{
	char	*token_str;
	int		start;
	int		end;

	start = *i;
	end = next_node_end(prompt, start);
	if (end > start)
	{
		token_str = ft_strndup(prompt + start, end - start);
		if (!token_str)
			return (false);
		append_node(node, token_str);
		free(token_str);
		*i = end;
		return (true);
	}
	return (false);
}

static bool	tokenize_prompt(char *prompt, t_lexer **node)
{
	int		i;

	i = 0;
	while (prompt[i])
	{
		while (is_space(prompt[i]))
			i++;
		if (prompt[i] == '\0')
			break ;
		if (!process_token(prompt, &i, node))
			return (false);
	}
	return (true);
}

t_lexer	*lexer(char *prompt)
{
	t_lexer	*node;

	node = NULL;
	if (!prompt)
		return (node);
	if (!tokenize_prompt(prompt, &node))
		return (NULL);
	analyze_tokens_type(node);
	return (node);
}
