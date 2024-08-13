/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:35:19 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/13 15:53:54 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*expand_variables(char *node, char **env)
{
	char	*result;

	result = NULL;
	if (!node || !env || !*env)
		return (result);
	// develop function
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
