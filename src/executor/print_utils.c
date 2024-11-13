/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:19:46 by lgandari          #+#    #+#             */
/*   Updated: 2024/11/13 20:58:17 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_inputs(t_file *file)
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

void	print_outputs(t_file *file)
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

void	print_cmd_nodes(t_command *cmd_node)
{
	t_command	*current_cmd_node;
	int			cmd_count;
	int			i;

	current_cmd_node = cmd_node;
	cmd_count = 1;
	return ;
	while (current_cmd_node)
	{
		printf("NODE:%d\n", cmd_count);
		if (current_cmd_node->cmd)
		{
			i = -1;
			while (current_cmd_node->cmd[++i])
				printf("cmd[%d]:%s\n", i, current_cmd_node->cmd[i]);
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
