/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:27:46 by aquinter          #+#    #+#             */
/*   Updated: 2024/11/13 21:01:33 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	syntax_error(char *str)
{
	if (str != NULL)
	{
		ft_putstr_fd("msh: syntax error near unexpected token ", STDERR_FILENO);
		ft_putchar_fd('`', STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\'\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd("msh: syntax error\n", STDERR_FILENO);
	return (SYNTAX_ERROR);
}

int	parser(t_lexer *lexer_node, t_shell *shell)
{
	if (lexer_node->is_pipe)
		return (syntax_error(lexer_node->argv[0]));
	while (lexer_node)
	{
		if (!lexer_node->is_command)
		{
			if (lexer_node->is_syntax_error)
				return (syntax_error(NULL));
			if (lexer_node->next == NULL)
				return (syntax_error("newline"));
			if ((lexer_node->is_pipe && lexer_node->next->is_pipe) || \
				(!lexer_node->is_pipe && !lexer_node->next->is_command))
				return (syntax_error(lexer_node->next->argv[0]));
		}
		else
			lexer_node->is_builtin = is_builtin(shell, lexer_node->argv[0]);
		lexer_node = lexer_node->next;
	}
	return (SUCCESS);
}
