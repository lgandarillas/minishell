/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:44:14 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/25 16:07:33 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	print_tokens(t_token *head)
{
	t_token	*current;

	current=node;
	while (current != NULL)
	{
		printf(">%s\n", current->str);
		current = current->next;
	}
}

static void	free_tokens(t_token *head)
{
	t_token	current;
	t_token	current_next;

	current = head;
	while (current != NULL)
	{
		current_next = current->next;
		free(current);
		current = current_next;
	}
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

/*
bool	lexer(char *prompt)
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
