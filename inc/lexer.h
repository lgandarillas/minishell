/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:45:53 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/03 13:05:01 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	char			*str;
	struct s_token	*next;
}	t_token;

char	**check_prompt(char *prompt);

bool	is_token(char c);
bool	is_space(char c);
int		skip_tokens(char *prompt, int i);
int		skip_quoted_section(char *prompt, int i, int *quote);

bool	lexer(char *prompt);
void	print_tokens(t_token *head);
void	free_tokens(t_token *head);
void	append_node(t_token **head, char *str);
bool	is_valid_bracket_sequence(char *prompt, int *i, int *brackets);

#endif
