/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:03:43 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/03 13:08:17 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_valid_bracket_sequence(char *prompt, int *i, int *brackets)
{
	if ((prompt[*i] == '<' && prompt[*i + 1] != '<') || \
		(prompt[*i] == '>' && prompt[*i + 1] != '>'))
	{
		(*brackets)++;
		if (*brackets > 2)
			return (false);
	}
	else if ((prompt[*i] == '<' && prompt[*i + 1] == '<') || \
		(prompt[*i] == '>' && prompt[*i + 1] == '>'))
	{
		(*i)++;
		*brackets = 0;
	}
	else if ((prompt[*i] == '<' && prompt[*i + 1] == '>') || \
		(prompt[*i] == '>' && prompt[*i + 1] == '<'))
		return (false);
	return (true);
}
