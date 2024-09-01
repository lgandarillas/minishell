/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:21:50 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/01 16:45:19 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_inputs(t_input *input)
{
	int	i;

	i = 0;
	if (input)
	{
		while (input)
		{
			printf("INPUT_INDEX:[%d]", i);
			printf(" NAME [%s] ", input->name);
			printf("is_heredoc:[%d]\n", input->is_heredoc);
			i++;
			input = input->next;
		}
	}
	else
		printf("(without input)\n");
}

static void	print_outputs(t_output *output)
{
	int	i;

	i = 0;
	if (output)
	{
		while (output)
		{
			printf("OUTPUT_INDEX:[%d]", i);
			printf(" NAME [%s] ", output->name);
			printf("is_append:[%d]\n", output->is_append);
			i++;
			output = output->next;
		}
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
		print_inputs(current_cmd_node->input);
		print_outputs(current_cmd_node->output);
		current_cmd_node = current_cmd_node->next;
		if (current_cmd_node)
			printf("\n");
		cmd_count++;
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
	new_cmd_node->input = NULL;
	new_cmd_node->output = NULL;
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

t_command	*prepare_cmd(t_lexer *lexer_node)
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
	print_cmd_nodes(cmd_node);
	return (cmd_node);
}
