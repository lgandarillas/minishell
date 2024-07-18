/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:00:25 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/18 16:11:59 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Not used yet
int	idx_after_whitespaces(char *str, int from)
{
	int	i;

	i = from;
	if (str[i] != ' ')
		return (-1);
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}
