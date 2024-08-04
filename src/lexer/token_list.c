/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:18:35 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/04 17:13:06 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		print_matrix(current->str);
		current = current->next;
	}
}

void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*current_next;

	current = head;
	while (current != NULL)
	{
		current_next = current->next;
		free_matrix(current->str);
		free(current);
		current = current_next;
	}
}

static char	**process_quoted_string(char *str)
{
	char	*quoted_str;
	char	**result;
	int		i;

	i = 1;
	while (str[i] && str[i] != str[0])
		i++;
	if (str[i] == str[0])
	{
		quoted_str = ft_substr(str, 1, i - 1);
		if (!quoted_str)
			return (NULL);
		result = malloc(sizeof(char *) * 2);
		if (!result)
		{
			free(quoted_str);
			return (NULL);
		}
		result[0] = quoted_str;
		result[1] = NULL;
		return (result);
	}
	return (NULL);
}

void	append_node(t_token **head, char *str)
{
	t_token	*node;
	t_token	*last_node;
	char	*trimmed_str;

	if (!head)
		return ;
	node = malloc(sizeof(t_token));
	if (!node)
		return ;
	trimmed_str = ft_strtrim(str, " ");
	if (str[0] == 34 || str[0] == 39)
		node->str = process_quoted_string(trimmed_str);
	else
		node->str = ft_split(trimmed_str, ' ');
	if (!node->str)
	{
		free(node);
		return ;
	}
	node->next = NULL;
	if (!(*head))
		*head = node;
	else
	{
		last_node = *head;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = node;
	}
	free(trimmed_str);
}
