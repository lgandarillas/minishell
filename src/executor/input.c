/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:36:56 by aquinter          #+#    #+#             */
/*   Updated: 2024/09/04 23:21:25 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_input	*init_input_node(t_lexer *lexer_node)
{
	t_input	*node;

	node = malloc(sizeof(t_input));
	if (!node)
		return (NULL);
	node->name = NULL;
	node->delimiter = NULL;
	node->is_heredoc = lexer_node->is_heredoc;
	node->fd = 0;
	node->next = NULL;
	return (node);
}

static void	append_input_node(t_input **input_node, t_lexer *lexer_node)
{
	t_input	*new_input_node;
	t_input	*last_input_node;

	new_input_node = init_input_node(lexer_node);
	if (!new_input_node)
		return ;
	if (new_input_node->is_heredoc)
		new_input_node->delimiter = ft_strdup(lexer_node->next->argv[0]);
	else
		new_input_node->name = ft_strdup(lexer_node->next->argv[0]);
	if (!new_input_node->name && !new_input_node->delimiter)
		return ;
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
