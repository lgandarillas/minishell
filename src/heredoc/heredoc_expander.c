/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:15:15 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/03 11:55:23 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_heredocs(t_lexer *node)
{
	int	num_heredocs;

	num_heredocs = 0;
	while (node)
	{
		if (node->is_heredoc)
			num_heredocs++;
		node = node->next;
	}
	return (num_heredocs);
}

void	check_expand_heredoc(t_lexer *node, t_shell *shell)
{
	int	num_heredocs;

	num_heredocs = count_heredocs(node);
	shell->expand_heredoc = malloc(sizeof(bool) * (num_heredocs + 1));
	if (!shell->expand_heredoc)
		return ;
	//FILL ARRAY
	(void)shell;
}
