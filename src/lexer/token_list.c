/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:18:35 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/03 18:41:14 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	printf("TOKENS:\n");
	while (current != NULL)
	{
		print_matrix(current->str);
		current = current->next;
	}
	printf("END TOKENS;\n");
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
	int	i;

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

static char	*clean_paired_quotes(char *str)
{
	int	start;
	int	end;
	char	*cleaned_str;

	if (!str)
		return (NULL);
	start = 0;
	end = ft_strlen(str);
	while (str[start] && (str[start] == 34 || str[start] == 39) && \
		str[start] == str[start + 1])
		start += 2;
	while (end > start && (str[end - 1] == 34 || str[end - 1] == 39) && \
		str[end -1] == str[end - 2])
		end -= 2;
	cleaned_str = malloc(sizeof(char) * (end - start + 1));
	if (!cleaned_str)
		return (NULL);
	ft_memcpy(cleaned_str, &str[start], end - start);
	cleaned_str[end - start] = '\0';
	return (cleaned_str);
}

void	append_node(t_token **head, char *str)
{
	t_token	*node;
	t_token	*last_node;

	if (!head)
		return ;
	node = malloc(sizeof(t_token));
	if (!node)
		return ;
	str = ft_strtrim(str, " ");
	str = clean_paired_quotes(str);
	if (str[0] == 34 || str[0] == 39)
		node->str = process_quoted_string(str);
	else
		node->str = ft_split(str, ' ');
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
}
