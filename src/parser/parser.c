/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:27:46 by aquinter          #+#    #+#             */
/*   Updated: 2024/08/24 13:32:19 by aquinter         ###   ########.fr       */
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

bool	parser(t_token *head, t_shell *shell)
{
	if (head->is_pipe)
		return (syntax_error(head->argv[0]));
	while (head)
	{
		if (!head->is_command)
		{
			if (head->is_syntax_error)
				return (syntax_error(NULL));
			if (head->next == NULL)
				return (syntax_error("newline"));
			if ((head->is_pipe && head->next->is_pipe) || \
				(!head->is_pipe && !head->next->is_command))
				return (syntax_error(head->next->argv[0]));
		}
		else
			head->is_builtin = is_builtin(shell, head->argv[0]);
		head = head->next;
	}
	return (SUCCESS);
}
