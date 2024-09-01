/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:45:38 by aquinter          #+#    #+#             */
/*   Updated: 2024/09/01 16:45:38 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_input_nodes(t_input *input_node)
{
	t_input	*current;
	t_input	*current_next;

	current = input_node;
	while (current)
	{
		current_next = current->next;
		free(current->name);
		free(current);
		current = current_next;
	}
}

void	free_output_nodes(t_output *output_node)
{
	t_output	*current;
	t_output	*current_next;

	current = output_node;
	while (current)
	{
		current_next = current->next;
		free(current->name);
		free(current);
		current = current_next;
	}
}

void	free_command_nodes(t_command *cmd_node)
{
	t_command	*current;
	t_command	*current_next;

	current = cmd_node;
	while (current)
	{
		current_next = current->next;
		free_matrix(current->cmd);
		free_input_nodes(current->input);
		free_output_nodes(current->output);
		free(current);
		current = current_next;
	}
}
