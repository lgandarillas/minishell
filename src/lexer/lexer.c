/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:44:14 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/25 17:29:45 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		printf("$%s$\n", current->str);
		current = current->next;
	}
}

static void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*current_next;

	current = head;
	while (current != NULL)
	{
		current_next = current->next;
		free(current->str);
		free(current);
		current = current_next;
	}
}

static void	append_node(t_token **head, char *str)
{
	t_token	*node;
	t_token	*last_node;

	if (!head)
		return ;
	node = malloc(sizeof(t_token));
	if (!node)
		return ;
	node->str = ft_strdup(str);
	if (!node->str)
	{
		free(node);
		return ;
	}
	node->next = NULL;
	if (!(*head))
		*head = node;
	else
	{
		last_node = *head;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = node;
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

bool	lexer(char *prompt)
{
	t_token	*head;
	t_token	*current;
	char	*token_str;
	int		i;
	int		start;
	int		end;

	if (prompt == NULL)
		return (false);
	head = NULL;
	current = NULL;
	i = 0;
	while (prompt[i])
	{
		while (prompt[i] && is_space(prompt[i]))
			i++;
		if (prompt[i] == '\0')
			break ;
		start = i;
		end = next_token_end(prompt, i);
		if (end > start)
		{
			token_str = ft_strndup(prompt + start, end - start);
			if (!token_str)
				return (false);
			append_node(&head, token_str);
			free(token_str);
			i = end;
		}
	}
	print_tokens(head);
	free_tokens(head);
	return (true);
}
