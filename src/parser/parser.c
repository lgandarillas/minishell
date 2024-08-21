/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:27:46 by aquinter          #+#    #+#             */
/*   Updated: 2024/08/21 18:54:42 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	syntax_error(char *str)
{
	ft_putstr_fd("msh: syntax error near unexpected token ", STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\'\n", STDERR_FILENO);
	return (FAILURE); // errorcode?
}

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
	t_token	*current;

	current = head;
	while (current)
	{
		// print_current(current);
		if (!current->is_command)
		{
			if (current->is_redirect_out && !current->next->is_command)
				return (syntax_error(current->next->argv[0]));
		}
		current = current->next;
	}
	return (SUCCESS);
}
