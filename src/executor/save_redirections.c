/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:47:57 by aquinter          #+#    #+#             */
/*   Updated: 2024/09/07 14:06:25 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_file	*init_file_node(t_lexer *lexer_node)
{
	t_file	*node;

	node = malloc(sizeof(t_file));
	if (!node)
		return (NULL);
	node->name = NULL;
	node->delimiter = NULL;
	node->is_append = lexer_node->is_append;
	node->is_heredoc = lexer_node->is_heredoc;
	node->is_redirect_in = lexer_node->is_redirect_in;
	node->is_redirect_out = lexer_node->is_redirect_out;
	node->fd = 0;
	node->next = NULL;
	return (node);
}

static void	append_file_node(t_file **file_node, t_lexer *lexer_node)
{
	t_file	*new_file_node;
	t_file	*last_file_node;

	new_file_node = init_file_node(lexer_node);
	if (!new_file_node)
		return ;
	if (lexer_node->is_heredoc)
		new_file_node->delimiter = ft_strdup(lexer_node->next->argv[0]);
	else
		new_file_node->name = ft_strdup(lexer_node->next->argv[0]);
	if (!new_file_node->name && !new_file_node->delimiter)
		return ;
	if (!(*file_node))
		*file_node = new_file_node;
	else
	{
		last_file_node = *file_node;
		while (last_file_node->next)
			last_file_node = last_file_node->next;
		last_file_node->next = new_file_node;
	}
}

void	handle_redirections(t_command *cmd_node, t_lexer *lexer_node)
{
	append_file_node(&cmd_node->file, lexer_node);
}
