/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:20:05 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/03 12:20:21 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	delete_heredoc_files(t_command *cmd)
{
	t_input	*input;

	while (cmd)
	{
		input = cmd->input;
		while (input)
		{
			if (input->is_heredoc && input->name)
			{
				unlink(input->name);
				free(input->name);
				input->name = NULL;
			}
			input = input->next;
		}
		cmd = cmd->next;
	}
}
