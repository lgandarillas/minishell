/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:21:50 by lgandari          #+#    #+#             */
/*   Updated: 2024/10/14 20:44:36 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_inputs(t_file *file)
{
	int	i;

	i = 0;
	if (file)
	{
		while (file)
		{
			if (file->is_heredoc || file->is_redirect_in)
			{
				printf("INPUT_INDEX:[%d]", i);
				if (file->name)
					printf(" NAME [%s] ", file->name);
				if (file->delimiter)
					printf(" DELIMITER [%s] ", file->delimiter);
				printf("is_heredoc:[%d]\n", file->is_heredoc);
				i++;
			}
			file = file->next;
		}
		if (i == 0)
			printf("(without input)\n");
	}
	else
		printf("(without input)\n");
}

static void	print_outputs(t_file *file)
{
	int	i;

	i = 0;
	if (file)
	{
		while (file)
		{
			if (file->is_append || file->is_redirect_out)
			{
				printf("OUTPUT_INDEX:[%d]", i);
				printf(" NAME [%s] ", file->name);
				printf("is_append:[%d]\n", file->is_append);
				i++;
			}
			file = file->next;
		}
		if (i == 0)
			printf("(without output)\n");
	}
	else
		printf("(without output)\n");
}

static void	print_cmd_nodes(t_command *cmd_node)
{
	t_command	*current_cmd_node;
	int			cmd_count;
	int			i;

	current_cmd_node = cmd_node;
	cmd_count = 1;
	while (current_cmd_node)
	{
		printf("NODE:%d\n", cmd_count);
		if (current_cmd_node->cmd)
		{
			i = 0;
			while (current_cmd_node->cmd[i])
			{
				printf("cmd[%d]:%s\n", i, current_cmd_node->cmd[i]);
				i++;
			}
		}
		else
			printf("(empty command)\n");
		print_inputs(current_cmd_node->file);
		print_outputs(current_cmd_node->file);
		current_cmd_node = current_cmd_node->next;
		if (current_cmd_node)
			printf("\n");
		cmd_count++;
	}
}

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
	print_cmd_nodes(cmd_node);
	return (cmd_node);
}
