/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:35:19 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/22 20:18:35 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*handle_reg_chars(char *str, size_t *i, char *result, char **env)
{
	char	*tmp;

	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
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

static char	*expand_variables(char *str, char **env)
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

char	*expand_status(char *str, int status)
{
	char	*result;
	char	*status_str;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	status_str = ft_itoa(status);
	if (!status_str)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(status_str) - 1));
	if (!result)
	{
		free(status_str);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			ft_strcpy(result + j, status_str);
			j += ft_strlen(status_str);
			i += 2;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	free(status_str);
	return (result);
}

void	expander(t_token *head, t_shell *shell)
{
	char	*expanded_str;
	char	*expanded_final;
	char	**new_args;

	while (head)
	{
		printf("- - - - - - - - - - - - - - -\n");
		printf("ORIGINAL_NODE: %s\n", head->str);
		expanded_str = expand_variables(head->str, shell->env);
		if (!expanded_str)
			return ;
		free(head->str);
		head->str = expanded_str;
		expanded_final = expand_status(head->str, shell->status);
		if (expanded_final)
		{
			free(head->str);
			head->str = expanded_final;
		}
		printf("EXPANDED_NODE: %s\n", head->str);
		head->argv = word_splitter(head->str);
		printf("SPLITTED_NODE:\n");
		print_matrix(head->argv);
		new_args = quote_cleaner(head->argv);
		free_matrix(head->argv);
		head->argv = new_args;
		printf("CLEANED_SPLIT:\n");
		print_matrix(head->argv);
		printf("- - - - - - - - - - - - - - -\n\n");
		head = head->next;
	}
}
