/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:09:10 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/17 12:12:05 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*handle_word_block(const char *str, size_t *index)
{
	int	start;

	start = *index;
	while (str[*index] && str[*index] != ' ' && !is_quote(str[*index]))
		(*index)++;
	return (ft_substr(str, start, *index - start));
}

char	*handle_quote_block(const char *str, size_t *index)
{
	int	start;
	int	end;

	start = *index;
	end = find_quote_block_end(str, start);
	*index = end;
	return (ft_substr(str, start, end - start));
}

int	find_quote_block_end(const char *str, int start_index)
{
	char	quote_char;
	int		i;

	quote_char = str[start_index];
	i = start_index + 1;
	while (str[i] && str[i] != quote_char)
		i++;
	if (str[i] == '\0')
		return (i);
	return (i + 1);
}
