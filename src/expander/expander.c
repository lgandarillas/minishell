/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:35:19 by lgandari          #+#    #+#             */
/*   Updated: 2024/11/03 18:39:42 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	update_lexer_node(t_lexer *lexer_node, t_shell *shell)
{
	char	*expanded_str;
	char	*expanded_final;

	expanded_str = expand_variables(lexer_node->str, shell->env);
	if (!expanded_str)
		return (FAILURE);
	free(lexer_node->str);
	lexer_node->str = expanded_str;
	expanded_final = expand_status(lexer_node->str, shell->status);
	if (expanded_final)
	{
		free(lexer_node->str);
		lexer_node->str = expanded_final;
	}
	lexer_node->argv = word_splitter(lexer_node->str);
	return (SUCCESS);
}

void	expander(t_lexer *lexer_node, t_shell *shell)
{
	char	**new_args;
	t_lexer	*head;

	head = lexer_node;
	while (lexer_node)
	{
		if (update_lexer_node(lexer_node, shell) == FAILURE)
			return ;
		new_args = quote_cleaner(lexer_node->argv);
		lexer_node->old_args = lexer_node->argv;
		lexer_node->argv = new_args;
		lexer_node = lexer_node->next;
	}
	check_expand_heredoc(head, shell);
}
