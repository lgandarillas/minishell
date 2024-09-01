/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:15:56 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/01 17:40:56 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_input
{
	struct s_input		*next;
	char				*name;
	char				*delimiter;
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
char		**append_str(char **arr, char *str);
void		clear_cmd(t_command *cmd_node, t_lexer *lexer_node);
void		free_command_nodes(t_command *cmd_node);
void		free_output_nodes(t_output *output_node);
void		free_input_nodes(t_input *input_node);
void		handle_input(t_command *cmd_node, t_lexer *lexer_node);
void		handle_output(t_command *cmd_node, t_lexer *lexer_node);

#endif
