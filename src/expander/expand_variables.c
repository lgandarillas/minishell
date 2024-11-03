/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:16:20 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/17 18:14:01 by lgandari         ###   ########.fr       */
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

	start = ++(*i);
	if (!ft_isalpha(str[start]) && str[start] != '_')
	{
		result = ft_strndup(str + start - 1, 2);
		(*i) = start + 1;
		return (result);
	}
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

static char	*handle_single_quotes(char *str, size_t *i, char *result)
{
	size_t	start;
	char	*tmp;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	tmp = ft_strndup(str + start, *i - start);
	result = ft_strjoin_free(result, tmp, true, true);
	return (result);
}

static char	*handle_dbl_quotes(char *str, size_t *i, char *result, char **env)
{
	char	*tmp;

	result = add_quotes_to_result(result, '\"');
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$')
		{
			tmp = handle_expansion(str, i, env);
			result = ft_strjoin_free(result, tmp, true, true);
		}
		else
		{
			tmp = ft_strndup(str + *i, 1);
			result = ft_strjoin_free(result, tmp, true, true);
			(*i)++;
		}
	}
	if (str[*i] == '\"')
	{
		(*i)++;
		result = add_quotes_to_result(result, '\"');
	}
	return (result);
}

static char	*handle_reg_chars(char *str, size_t *i, char *result, char **env)
{
	char	*tmp;

	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
	{
		if (str[*i] == '$')
		{
			if (str[*i + 1] == '\0')
			{
				tmp = ft_strdup("$");
				(*i)++;
			}
			else
				tmp = handle_expansion(str, i, env);
			result = ft_strjoin_free(result, tmp, true, true);
		}
		else
		{
			tmp = ft_strndup(str + *i, 1);
			result = ft_strjoin_free(result, tmp, true, true);
			(*i)++;
		}
	}
	return (result);
}

char	*expand_variables(char *str, char **env)
{
	char	*result;
	size_t	i;

	if (!str || !env || !*env)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			result = handle_single_quotes(str, &i, result);
		else if (str[i] == '\"')
			result = handle_dbl_quotes(str, &i, result, env);
		else
			result = handle_reg_chars(str, &i, result, env);
	}
	return (result);
}