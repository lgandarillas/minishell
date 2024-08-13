/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:27:46 by aquinter          #+#    #+#             */
/*   Updated: 2024/08/13 17:11:32 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	parser(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		printf("===================================\n");
		printf("%s\n", current->str);
		printf("%d append\n", current->is_append);
		printf("%d command\n", current->is_command);
		printf("%d heredoc\n", current->is_heredoc);
		printf("%d pipe\n", current->is_pipe);
		printf("%d redirect in\n", current->is_redirect_in);
		printf("%d redirect out\n", current->is_redirect_out);
		printf("===================================\n");

		if (!current->is_command && !current->next->is_command)
		{
			ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
			ft_putchar_fd('`', STDERR_FILENO);
			ft_putstr_fd(current->str, STDERR_FILENO);
			ft_putchar_fd('\'', STDERR_FILENO);
		}

		current = current->next;
	}
	return (true);
}
