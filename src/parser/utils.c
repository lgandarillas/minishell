/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:06:07 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/22 18:08:41 by lgandari         ###   ########.fr       */
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
