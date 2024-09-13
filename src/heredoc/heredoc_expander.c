/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:15:15 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/13 12:37:24 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_heredocs(t_lexer *node)
{
	t_lexer	*head;
	int	num_heredocs;

	head = node;
	num_heredocs = 0;
	while (head)
	{
		if (head->is_heredoc)
			num_heredocs++;
		head = head->next;
	}
	return (num_heredocs);
}

void	print_expand_heredoc(t_shell *shell, int num_heredocs)
{
	int	i;

	i = 0;
	while (i  < num_heredocs)
	{
		printf("expand_heredoc[%d] = %d\n", i, shell->expand_heredoc[i]);
		i++;
	}
}

void	check_expand_heredoc(t_lexer *node, t_shell *shell)
{
	int	num_heredocs;
	int	i;

	num_heredocs = count_heredocs(node);
	shell->expand_heredoc = malloc(sizeof(bool) * (num_heredocs + 1));
	if (!shell->expand_heredoc)
		return ;
	i = 0;
	while (node)
	{
		if (node->is_heredoc)
		{
			if (node->next && node->next->old_args && node->next->old_args[0])
			{
				if (node->next->old_args[0][0] == '\'' || node->next->old_args[0][0] == '\"')
					shell->expand_heredoc[i] = false;
				else
					shell->expand_heredoc[i] = true;
			}
			else
				shell->expand_heredoc[i] = true;
			i++;
		}
		node = node->next;
	}
	print_expand_heredoc(shell, num_heredocs);
}

char	*expand_heredoc_line(char *line, t_shell *shell)
{
	char	*expanded_str;
	char	*expanded_final;

	expanded_str = expand_variables(line, shell->env);
	if (!expanded_str)
		return (NULL);
	expanded_final = expand_status(expanded_str, shell->status);
	if (expanded_final != expanded_str)
		free(expanded_str);
	return (expanded_final);
}
