/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:45:53 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/30 16:49:16 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	struct s_token	*next;
	char			*str;
	char			**argv;
	bool			is_pipe;
	bool			is_redirect_in;
	bool			is_redirect_out;
	bool			is_append;
	bool			is_heredoc;
	bool			is_command;
	bool			expand;
	bool			is_syntax_error;
	bool			is_builtin;
}	t_lexer;

bool	check_prompt(char *prompt);

bool	is_token(char c);
bool	is_space(char c);
int		skip_tokens(char *prompt, int i);

t_lexer	*lexer(char *prompt);
void	print_tokens(t_lexer *lexer_node);
void	free_tokens(t_lexer *lexer_node);
void	append_lexer_node(t_lexer **lexer_node, char *str);
bool	is_valid_bracket_sequence(char *prompt, int *i, int *brackets);
void	analyze_tokens_type(t_lexer *lexer_node);

bool	is_token_str(char *str);

#endif
