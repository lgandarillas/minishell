/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:27:46 by aquinter          #+#    #+#             */
/*   Updated: 2024/08/22 18:05:24 by aquinter         ###   ########.fr       */
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

// static t_token *get_last_token(t_token *head)
// {
// 	while (head->next != NULL)
// 		head = head->next;
// 	return (head);
// }

// static void	print_current(t_token *current)
// {
// 		printf("===================================\n");
// 		printf("%s - str\n", current->str);
// 		printf("%s - argv[0]\n", current->argv[0]);
// 		printf("%d - append\n", current->is_append);
// 		printf("%d - command\n", current->is_command);
// 		printf("%d - heredoc\n", current->is_heredoc);
// 		printf("%d - pipe\n", current->is_pipe);
// 		printf("%d - redirect in\n", current->is_redirect_in);
// 		printf("%d - redirect out\n", current->is_redirect_out);
// 		printf("===================================\n");
// }

bool	parser(t_token *head)
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
			// head->is_builtin = is_builtin(head->argv[0]);
		head = head->next;
	}
	return (SUCCESS);
}
