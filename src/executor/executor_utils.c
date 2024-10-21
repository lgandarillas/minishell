/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:45:38 by aquinter          #+#    #+#             */
/*   Updated: 2024/10/19 10:53:29 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_file_nodes(t_file *file_node)
{
	t_file	*current;
	t_file	*current_next;

	current = file_node;
	while (current)
	{
		current_next = current->next;
		if (current->name)
			free(current->name);
		if (current->is_heredoc)
			free(current->delimiter);
		free(current);
		current = current_next;
	}
}

void	free_command_nodes(t_command *cmd_node, t_shell *shell)
{
	t_command	*current;
	t_command	*current_next;

	current = cmd_node;
	delete_heredoc_files(cmd_node);
	while (current)
	{
		current_next = current->next;
		free_matrix(current->cmd);
		free_file_nodes(current->file);
		free(current);
		current = current_next;
	}
	free(shell->expand_heredoc);
}

int	total_commands(t_command *cmd_node)
{
	int	i;

	i = 0;
	while (cmd_node)
	{
		i++;
		cmd_node = cmd_node->next;
	}
	return (i);
}

int	restore_std_fds(int *std_fds)
{
	if (dup2(std_fds[0], STDIN_FILENO) == -1)
	{
		perror("msh");
		return (-1);
	}
	close(std_fds[0]);
	if (dup2(std_fds[1], STDOUT_FILENO) == -1)
	{
		perror("msh");
		return (-1);
	}
	close(std_fds[1]);
	return (0);
}
