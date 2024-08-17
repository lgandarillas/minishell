/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:16:20 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/15 16:16:49 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*handle_expansion(char *str, size_t *i, char **env)
{
	size_t	start;
	size_t	len;
	char	*var;
	char	*value;
	char	*result;

	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalpha(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	var = ft_strndup(str + start, len);
	var = ft_strjoin_free(var, "=", true, false);
	value = ft_getenv(env, var);
	free(var);
	if (value)
		result = ft_strdup(value);
	else
		result = ft_strdup("");
	return (result);
}
