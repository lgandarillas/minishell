/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:06:07 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/25 14:23:10 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_token(char c)
{
	if (c == '\0')
		return (false);
	if (c == '>' || c == '<' || c == '|')
		return (true);
	return (false);
}

bool	is_space(char c)
{
	if (c == '\0')
		return (false);
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

int	skip_tokens(char *prompt, int i)
{
	while (is_token(prompt[i]))
		i++;
	return (i);
}

int	skip_quoted_section(char *prompt, int i, int *quote)
{
	*quote = prompt[i];
	i++;
	while (prompt[i] && prompt[i] != *quote)
		i++;
	if (prompt[i] == *quote)
		*quote = 0;
	i++;
	return (i);
}
