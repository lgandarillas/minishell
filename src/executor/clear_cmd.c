/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:56:30 by aquinter          #+#    #+#             */
/*   Updated: 2024/09/01 10:27:36 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// typedef struct s_input
// {
// 	struct s_input		*next;
// 	char				*name;
// 	int					fd;
// 	bool				is_heredoc;
// }	t_input;

// typedef struct s_output
// {
// 	struct s_output		*next;
// 	char				*name;
// 	int					fd;
// 	bool				is_append;
// }	t_output;

void	handle_input(char *str, t_input *input)
{
	(void)str;
	(void)input;	
}

void	handle_output(char *str, t_output *output)
{
	(void)str;
	(void)output;	
}

t_command	*clear_cmd(t_command *cmd_node)
{
	int			i;
	char		**cmd_cleared;
	t_input		*input;
	t_output	*output;
	
	input = NULL;
	output = NULL;
	while (cmd_node)
	{
		i = 0;
		cmd_cleared = NULL;
		while (cmd_node->cmd[i] != NULL)
		{
			// > output src/main.c 
			if (redirect())
				cmd_node = cmd_node->next;
				// output src/main.c
			else
				cmd_cleared = append_str(cmd_cleared, cmd_node->cmd[i]);
			cmd_node = cmd_node->next;
			i++;
		}
		free_matrix(cmd_node->cmd);
		cmd_node->cmd = cmd_cleared;
		cmd_node = cmd_node->next;
	}
	return (cmd_node);
}
