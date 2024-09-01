/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:15:56 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/31 10:14:14 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_input
{
	struct s_input		*next;
	char				*name;
	int					fd;
	bool				is_heredoc;
}	t_input;

typedef struct s_output
{
	struct s_output		*next;
	char				*name;
	int					fd;
	bool				is_append;
}	t_output;

typedef struct s_command
{
	struct s_command	*next;
	char				**cmd;
	t_input				*input;
	t_output			*output;
}	t_command;

t_command	*prepare_cmd(t_lexer *lexer_node);
t_command	*clear_cmd(t_command *cmd_node);
void		free_command_nodes(t_command *cmd_node);
char		**append_str(char **arr, char *str);

#endif
