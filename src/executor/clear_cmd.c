/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:56:30 by aquinter          #+#    #+#             */
/*   Updated: 2024/09/01 16:47:31 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_redirection(t_lexer *lexer_node)
{
	if (lexer_node->is_redirect_in || \
		lexer_node->is_redirect_out || \
		lexer_node->is_heredoc || \
		lexer_node->is_append)
		return (true);
	return (false);
}

void	handle_redirection(t_lexer *lexer_node, t_command *cmd_node)
{
	if (lexer_node->is_redirect_out || lexer_node->is_append)
		handle_output(cmd_node, lexer_node);
	else
		handle_input(cmd_node, lexer_node);
}

void	clear_cmd(t_command *cmd_node, t_lexer *lexer_node)
{
	int	i;

	while (lexer_node != NULL)
	{
		if (lexer_node->is_pipe == true)
			cmd_node = cmd_node->next;
		else
		{
			i = 0;
			if (is_redirection(lexer_node))
			{
				handle_redirection(lexer_node, cmd_node);
				lexer_node = lexer_node->next;
				i++;
			}
			while (lexer_node->argv[i] != NULL)
			{
				cmd_node->cmd = \
					append_str(cmd_node->cmd, lexer_node->argv[i]);
				i++;
			}
		}
		lexer_node = lexer_node->next;
	}
}
