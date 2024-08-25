/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_token_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:26:30 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/25 15:10:25 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	initialize_token_flags(t_lexer *node)
{
	while (node)
	{
		node->is_pipe = false;
		node->is_redirect_in = false;
		node->is_redirect_out = false;
		node->is_append = false;
		node->is_heredoc = false;
		node->is_command = false;
		node->expand = false;
		node->is_syntax_error = false;
		node->is_builtin = false;
		node = node->next;
	}
}

void	analyze_tokens_type(t_lexer *node)
{
	initialize_token_flags(node);
	while (node)
	{
		if (ft_strcmp(node->str, "|") == 0)
			node->is_pipe = true;
		else if (ft_strcmp(node->str, "<") == 0)
			node->is_redirect_in = true;
		else if (ft_strcmp(node->str, ">") == 0)
			node->is_redirect_out = true;
		else if (ft_strcmp(node->str, ">|") == 0)
			node->is_redirect_out = true;
		else if (ft_strcmp(node->str, ">>") == 0)
			node->is_append = true;
		else if (ft_strcmp(node->str, "<<") == 0)
			node->is_heredoc = true;
		else if (!is_token_str(node->str))
			node->is_command = true;
		else
			node->is_syntax_error = true;
		node = node->next;
	}
}
