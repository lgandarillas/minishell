/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:18:35 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/13 12:36:13 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_tokens(t_lexer *lexer_node)
{
	while (lexer_node)
	{
		ft_printf("%s\n", lexer_node->str);
		lexer_node = lexer_node->next;
	}
}

void	free_tokens(t_lexer *lexer_node)
{
	t_lexer	*current;
	t_lexer	*current_next;

	current = lexer_node;
	while (current != NULL)
	{
		current_next = current->next;
		free(current->str);
		free_matrix(current->argv);
		free_matrix(current->old_args);
		free(current);
		current = current_next;
	}
}

void	append_lexer_node(t_lexer **lexer_node, char *str)
{
	t_lexer	*new_lexer_node;
	t_lexer	*last_lexer_node;
	char	*trimmed_str;

	if (!lexer_node)
		return ;
	new_lexer_node = malloc(sizeof(t_lexer));
	if (!new_lexer_node)
		return ;
	trimmed_str = ft_strtrim(str, " ");
	new_lexer_node->str = trimmed_str;
	new_lexer_node->next = NULL;
	if (!(*lexer_node))
		*lexer_node = new_lexer_node;
	else
	{
		last_lexer_node = *lexer_node;
		while (last_lexer_node->next)
			last_lexer_node = last_lexer_node->next;
		last_lexer_node->next = new_lexer_node;
	}
}
