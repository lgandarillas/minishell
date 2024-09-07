/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:15:56 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/07 14:19:45 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_file
{
	struct s_file		*next;
	char				*name;
	char				*delimiter;
	int					fd;
	bool				is_redirect_in;
	bool				is_redirect_out;
	bool				is_append;
	bool				is_heredoc;
}	t_file;

typedef struct s_command
{
	struct s_command		*next;
	char					**cmd;
	t_file					*file;
}	t_command;

t_command	*prepare_cmd(t_lexer *lexer_node);
char		**append_str(char **arr, char *str);
void		clear_cmd(t_command *cmd_node, t_lexer *lexer_node);
void		free_command_nodes(t_command *cmd_node, t_shell *shell);
void		handle_redirections(t_command *cmd_node, t_lexer *lexer_node);

#endif
