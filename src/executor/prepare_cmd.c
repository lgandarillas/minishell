/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:21:50 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/30 19:53:30 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		current_cmd_node = current_cmd_node->next;
		cmd_count++;
	}
}

static char	**append_str(char **arr, char *str)
{
	size_t	len;
	size_t	i;
	char	**new_arr;

	len = ft_arrlen((void **)arr) + 1;
	new_arr = ft_calloc(sizeof(char *), len + 1);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < len - 1)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
			return (free_matrix(new_arr), NULL);
		i++;
	}
	new_arr[len - 1] = ft_strdup(str);
	if (!new_arr[len - 1])
		return (free_matrix(new_arr), NULL);
	free_matrix(arr);
	return (new_arr);
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

void	free_command_nodes(t_command *cmd_node)
{
	t_command	*current;
	t_command	*current_next;

	current = cmd_node;
	while (current)
	{
		current_next = current->next;
		free_matrix(current->cmd);
		free(current);
		current = current_next;
	}
}

t_command	*prepare_cmd(t_lexer *lexer_node)
{
	t_command	*cmd_node;
	t_command	*current_cmd_node;
	int			i;

	cmd_node = NULL;
	append_cmd_node(&cmd_node);
	current_cmd_node = cmd_node;
	while (lexer_node)
	{
		i = 0;
		while (lexer_node->argv[i])
		{
			if (ft_strcmp(lexer_node->argv[i], "|") == 0)
				create_cmd_node_after_pipe(&cmd_node, &current_cmd_node);
			else
				current_cmd_node->cmd = \
					append_str(current_cmd_node->cmd, lexer_node->argv[i]);
			i++;
		}
		lexer_node = lexer_node->next;
	}
	print_cmd_nodes(cmd_node);
	return (cmd_node);
}
