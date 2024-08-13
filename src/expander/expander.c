/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:35:19 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/13 18:18:17 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * DONE
static int	is_valid_variable_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}
*/

static char	*expand_variables(char *str, char **env)
{
	char	*result;
	size_t	i;

	if (!str || !env || !*env)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	(void)i;
	/*
	while (str[i])
	{
		if (str[i] == '\'')
		{
			void(str[i]);//delete
		}
		else if (str[i] == '\"')
		{
		
		}
		else
		{
		
		}
	}
	*/
	return (result);
}

void	expander(t_token *head, t_shell *shell)
{
	char	*aux;

	while (head)
	{
		aux = expand_variables(head->str, shell->env);
		free(head->str);
		head->str = aux;
		head = head->next;
	}
}
