/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_token_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:26:30 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/30 16:49:16 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	initialize_token_flags(t_lexer *lexer_node)
{
	while (lexer_node)
	{
		lexer_node->is_pipe = false;
		lexer_node->is_redirect_in = false;
		lexer_node->is_redirect_out = false;
		lexer_node->is_append = false;
		lexer_node->is_heredoc = false;
		lexer_node->is_command = false;
		lexer_node->expand = false;
		lexer_node->is_syntax_error = false;
		lexer_node->is_builtin = false;
		lexer_node = lexer_node->next;
	}
}

void	analyze_tokens_type(t_lexer *lexer_node)
{
	initialize_token_flags(lexer_node);
	while (lexer_node)
	{
		if (ft_strcmp(lexer_node->str, "|") == 0)
			lexer_node->is_pipe = true;
		else if (ft_strcmp(lexer_node->str, "<") == 0)
			lexer_node->is_redirect_in = true;
		else if (ft_strcmp(lexer_node->str, ">") == 0)
			lexer_node->is_redirect_out = true;
		else if (ft_strcmp(lexer_node->str, ">|") == 0)
			lexer_node->is_redirect_out = true;
		else if (ft_strcmp(lexer_node->str, ">>") == 0)
			lexer_node->is_append = true;
		else if (ft_strcmp(lexer_node->str, "<<") == 0)
			lexer_node->is_heredoc = true;
		else if (!is_token_str(lexer_node->str))
			lexer_node->is_command = true;
		else
			lexer_node->is_syntax_error = true;
		lexer_node = lexer_node->next;
	}
}
