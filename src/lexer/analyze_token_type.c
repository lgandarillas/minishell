/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_token_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:26:30 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/03 14:38:08 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	analyze_token_type(t_token *token)
{
	while (token)
	{
		if (ft_strcmp(token->str[0], "|") == 0)
			token->is_pipe = true;
		else if (ft_strcmp(token->str[0], "<") == 0)
			token->is_redirect_in = true;
		else if (ft_strcmp(token->str[0], ">") == 0)
			token->is_redirect_out = true;
		else if (ft_strcmp(token->str[0], ">>") == 0)
			token->is_append = true;
		else if (ft_strcmp(token->str[0], "<<") == 0)
			token->is_heredoc = true;
		else
			token->is_command = true;
		token = token->next;
	}
}
