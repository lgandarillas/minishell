/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:27:46 by aquinter          #+#    #+#             */
/*   Updated: 2024/08/25 15:09:13 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	syntax_error(char *str)
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

bool	parser(t_lexer *node, t_shell *shell)
{
	if (node->is_pipe)
		return (syntax_error(node->argv[0]));
	while (node)
	{
		if (!node->is_command)
		{
			if (node->is_syntax_error)
				return (syntax_error(NULL));
			if (node->next == NULL)
				return (syntax_error("newline"));
			if ((node->is_pipe && node->next->is_pipe) || \
				(!node->is_pipe && !node->next->is_command))
				return (syntax_error(node->next->argv[0]));
		}
		else
			node->is_builtin = is_builtin(shell, node->argv[0]);
		node = node->next;
	}
	return (SUCCESS);
}
