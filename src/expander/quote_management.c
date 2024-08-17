/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:13:23 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/17 12:57:15 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	*add_quotes_to_result(char *result, char quote_char)
{
	char	*quote_str;

	quote_str = ft_strndup(&quote_char, 1);
	result = ft_strjoin_free(result, quote_str, true, false);
	free(quote_str);
	return (result);
}
