/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_token_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:26:30 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/21 18:30:07 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	initialize_token_flags(t_token *token)
{
	while (token)
	{
		token->is_pipe = false;
		token->is_redirect_in = false;
		token->is_redirect_out = false;
		token->is_append = false;
		token->is_heredoc = false;
		token->is_command = false;
		token->expand = false;
		token->is_syntax_error = false;
		token = token->next;
	}
}

void	analyze_tokens_type(t_token *token)
{
	initialize_token_flags(token);
	while (token)
	{
		if (ft_strcmp(token->str, "|") == 0)
			token->is_pipe = true;
		else if (ft_strcmp(token->str, "<") == 0)
			token->is_redirect_in = true;
		else if (ft_strcmp(token->str, ">") == 0)
			token->is_redirect_out = true;
		else if (ft_strcmp(token->str, ">|") == 0)
			token->is_redirect_out = true;
		else if (ft_strcmp(token->str, ">>") == 0)
			token->is_append = true;
		else if (ft_strcmp(token->str, "<<") == 0)
			token->is_heredoc = true;
		else if (!is_token_str(token->str))
			token->is_command = true;
		else
			token->is_syntax_error = true;
		token = token->next;
	}
}
