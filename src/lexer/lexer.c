/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:44:14 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/25 18:07:59 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static bool	process_token(char *prompt, int *i, t_token **head)
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

	if (prompt == NULL)
		return (false);
	head = NULL;
	i = 0;
	while (prompt[i])
	{
		while (prompt[i] && is_space(prompt[i]))
			i++;
		if (prompt[i] == '\0')
			break ;
		if (!process_token(prompt, &i, &head))
			return (false);
	}
	print_tokens(head);
	free_tokens(head);
	return (true);
}
