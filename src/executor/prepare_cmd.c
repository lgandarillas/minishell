/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:21:50 by lgandari          #+#    #+#             */
/*   Updated: 2024/11/04 22:26:39 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	assign_builtin_flag(t_command *cmd_node, t_shell *shell)
{
	while (cmd_node)
	{
		if (cmd_node->cmd != NULL)
			cmd_node->is_builtin = is_builtin(shell, cmd_node->cmd[0]);
		cmd_node = cmd_node->next;
	}
}

static void	append_cmd_node(t_command **cmd_node)
{
	t_command	*new_cmd_node;
	t_command	*last_cmd_node;

	new_cmd_node = malloc(sizeof(t_command));
	if (!new_cmd_node)
		return ;
	new_cmd_node->next = NULL;
	new_cmd_node->cmd = NULL;
	new_cmd_node->file = NULL;
	new_cmd_node->is_builtin = false;
	if (!(*cmd_node))
		*cmd_node = new_cmd_node;
	else
	{
		last_cmd_node = *cmd_node;
		while (last_cmd_node->next)
			last_cmd_node = last_cmd_node->next;
		last_cmd_node->next = new_cmd_node;
	}
}

static void	create_cmd_node_after_pipe(t_command **head, t_command **current)
{
	append_cmd_node(head);
	*current = *head;
	while ((*current)->next)
		*current = (*current)->next;
}

t_command	*prepare_cmd(t_lexer *lexer_node, t_shell *shell)
{
	t_command	*cmd_node;
	t_command	*current_cmd_node;
	t_lexer		*current_lexer_node;

	cmd_node = NULL;
	append_cmd_node(&cmd_node);
	current_lexer_node = lexer_node;
	current_cmd_node = cmd_node;
	while (current_lexer_node)
	{
		if (current_lexer_node->is_pipe == true)
			create_cmd_node_after_pipe(&cmd_node, &current_cmd_node);
		current_lexer_node = current_lexer_node->next;
	}
	clear_cmd(cmd_node, lexer_node);
	assign_builtin_flag(cmd_node, shell);
	shell->num_cmds = get_num_cmds(cmd_node);
	print_cmd_nodes(cmd_node);
	return (cmd_node);
}
