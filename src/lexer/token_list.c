/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:18:35 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/05 20:58:54 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_tokens(t_token *token)
{
	while (token)
	{
		print_matrix(token->str);
		if (token->next)
			ft_printf("\n");
		token = token->next;
	}
}

void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*current_next;

	current = head;
	while (current != NULL)
	{
		current_next = current->next;
		free_matrix(current->str);
		free(current);
		current = current_next;
	}
}

void	append_node(t_token **head, char *str)
{
	t_token	*node;
	t_token	*last_node;
	char	*trimmed_str;

	if (!head)
		return ;
	node = malloc(sizeof(t_token));
	if (!node)
		return ;
	trimmed_str = ft_strtrim(str, " ");
	node->str = ft_split(trimmed_str, ' ');
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
	free(trimmed_str);
}
