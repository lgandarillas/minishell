/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 21:39:29 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/23 09:43:07 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*copy_status(char *result, char *status_str, size_t *i, size_t *j)
{
	ft_strcpy(result + *j, status_str);
	*j += ft_strlen(status_str);
	*i += 2;
	return (result);
}

static char	*handle_squote_status(char *str, char *result, size_t *i, size_t *j)
{
	result[(*j)++] = str[(*i)++];
	while (str[*i] && str[*i] != '\'')
		result[(*j)++] = str[(*i)++];
	if (str[*i] == '\'')
		result[(*j)++] = str[(*i)++];
	return (result);
}

static char	*expand_status_str(char *str, char *status_str, char *result)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			result = handle_squote_status(str, result, &i, &j);
		else if (str[i] == '$' && str[i + 1] == '?')
			result = copy_status(result, status_str, &i, &j);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*expand_status(char *str, int status)
{
	char	*result;
	char	*status_str;

	if (!str)
		return (NULL);
	status_str = ft_itoa(status);
	if (!status_str)
		return (NULL);
	result = malloc(ft_strlen(str) + ft_strlen(status_str));
	if (!result)
	{
		free(status_str);
		return (NULL);
	}
	result = expand_status_str(str, status_str, result);
	free(status_str);
	return (result);
}
