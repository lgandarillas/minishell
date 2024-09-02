/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:36:54 by aquinter          #+#    #+#             */
/*   Updated: 2024/09/01 15:40:26 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	append_output_node(t_output **output_node, t_lexer *lexer_node)
{
	t_output	*new_output_node;
	t_output	*last_output_node;

	new_output_node = malloc(sizeof(t_output));
	if (!new_output_node)
		return ;
	new_output_node->name = ft_strdup(lexer_node->next->argv[0]);
	if (!new_output_node->name)
		return ;
	new_output_node->is_append = lexer_node->is_append;
	new_output_node->fd = 0;
	new_output_node->next = NULL;
	if (!(*output_node))
		*output_node = new_output_node;
	else
	{
		last_output_node = *output_node;
		while (last_output_node->next)
			last_output_node = last_output_node->next;
		last_output_node->next = new_output_node;
	}
}

void	handle_output(t_command *cmd_node, t_lexer *lexer_node)
{
	append_output_node(&cmd_node->output, lexer_node);
}
