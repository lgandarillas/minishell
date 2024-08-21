/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:45:53 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/21 18:22:34 by lgandari         ###   ########.fr       */
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
}	t_token;

bool	check_prompt(char *prompt);

bool	is_token(char c);
bool	is_space(char c);
int		skip_tokens(char *prompt, int i);

t_token	*lexer(char *prompt);
void	print_tokens(t_token *head);
void	free_tokens(t_token *head);
void	append_node(t_token **head, char *str);
bool	is_valid_bracket_sequence(char *prompt, int *i, int *brackets);
void	analyze_tokens_type(t_token *token);

bool	is_token_str(char *str);

#endif
