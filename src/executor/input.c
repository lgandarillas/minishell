/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:36:56 by aquinter          #+#    #+#             */
/*   Updated: 2024/09/01 17:45:45 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	append_input_node(t_input **input_node, t_lexer *lexer_node)
{
	t_input	*new_input_node;
	t_input	*last_input_node;

	new_input_node = malloc(sizeof(t_input));
	if (!new_input_node)
		return ;
	if (lexer_node->is_heredoc)
	{
		new_input_node->name = NULL;
		new_input_node->delimiter = ft_strdup(lexer_node->next->argv[0]);
		if (!new_input_node->delimiter)
			return ;
	}
	else
	{
		new_input_node->delimiter = NULL;
		new_input_node->name = ft_strdup(lexer_node->next->argv[0]);
		if (!new_input_node->name)
			return ;
	}
	new_input_node->is_heredoc = lexer_node->is_heredoc;
	new_input_node->fd = 0;
	new_input_node->next = NULL;
	if (!(*input_node))
		*input_node = new_input_node;
	else
	{
		last_input_node = *input_node;
		while (last_input_node->next)
			last_input_node = last_input_node->next;
		last_input_node->next = new_input_node;
	}
}

void	handle_input(t_command *cmd_node, t_lexer *lexer_node)
{
	append_input_node(&cmd_node->input, lexer_node);
}
