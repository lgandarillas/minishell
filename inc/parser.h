/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:56:25 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/25 14:24:09 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct	s_token
{
	char			*str;
	struct s_token	*next;
}	t_token;

char	**parser(char *prompt);
bool	check_prompt_errors(char *prompt);

bool	is_token(char c);
bool	is_space(char c);
int	skip_tokens(char *prompt, int i);
int	skip_quoted_section(char *prompt, int i, int *quote);

#endif
