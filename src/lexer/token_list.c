/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:18:35 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/25 15:10:25 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_tokens(t_lexer *node)
{
	while (node)
	{
		ft_printf("%s\n", node->str);
		node = node->next;
	}
}

void	free_tokens(t_lexer *node)
{
	t_lexer	*current;
	t_lexer	*current_next;

	current = node;
	while (current != NULL)
	{
		current_next = current->next;
		free(current->str);
		free_matrix(current->argv);
		free(current);
		current = current_next;
	}
}

void	append_node(t_lexer **node, char *str)
{
	t_lexer	*new_node;
	t_lexer	*last_node;
	char	*trimmed_str;

	if (!node)
		return ;
	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return ;
	trimmed_str = ft_strtrim(str, " ");
	new_node->str = trimmed_str;
	new_node->next = NULL;
	if (!(*node))
		*node = new_node;
	else
	{
		last_node = *node;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}
