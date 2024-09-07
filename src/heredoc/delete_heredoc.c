/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:20:05 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/07 13:46:15 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	delete_heredoc_files(t_command *cmd)
{
	t_file	*file;

	while (cmd)
	{
		file = cmd->file;
		while (file)
		{
			if (file->is_heredoc && file->name)
			{
				unlink(file->name);
				free(file->name);
				file->name = NULL;
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
}
