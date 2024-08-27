/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:35:19 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/27 18:14:28 by lgandari         ###   ########.fr       */
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

void	expander(t_lexer *node, t_shell *shell)
{
	char	*expanded_str;
	char	*expanded_final;
	char	**new_args;

	while (node)
	{
		// printf("- - - - - - - - - - - - - - -\n");
		// printf("ORIGINAL_NODE: %s\n", node->str);
		expanded_str = expand_variables(node->str, shell->env);
		if (!expanded_str)
			return ;
		free(node->str);
		node->str = expanded_str;
		expanded_final = expand_status(node->str, shell->status);
		if (expanded_final)
		{
			free(node->str);
			node->str = expanded_final;
		}
		// printf("EXPANDED_NODE: %s\n", node->str);
		node->argv = word_splitter(node->str);
		// printf("SPLITTED_NODE:\n");
		// print_matrix(node->argv);
		new_args = quote_cleaner(node->argv);
		free_matrix(node->argv);
		node->argv = new_args;
		// printf("CLEANED_SPLIT:\n");
		// print_matrix(node->argv);
		// printf("- - - - - - - - - - - - - - -\n\n");
		node = node->next;
	}
}
