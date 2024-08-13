/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:35:19 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/13 20:25:31 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
static int	is_valid_variable_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}
*/

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
	tmp = ft_substr(str, start, *i - start);
	result = ft_strjoin_free(result, tmp);
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
			result = handle_single_quotes(str, &i, result);				// TO DO
		else		//delete
			i++;	//delete
		/*
		else if (str[i] == '\"')
			result = handle_double_quotes(str, &i, result, env);		// TO DO
		else if (str[i] == '$' && is_valid_variable_start(str[i + 1]))
			result = handle_variable_expansion(str, &i, result, env);	// TO DO
		else
			result = handle_regular_chars(str, &i, result);
		*/
	}
	return (result);
}

void	expander(t_token *head, t_shell *shell)
{
	char	*aux;

	while (head)
	{
		aux = expand_variables(head->str, shell->env);
		printf("AUX=%s\n", aux);
		free(head->str);
		head->str = aux;
		head = head->next;
	}
}
