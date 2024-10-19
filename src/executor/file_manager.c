/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:48:00 by aquinter          #+#    #+#             */
/*   Updated: 2024/10/19 13:17:56 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	close_files(t_command *cmd_node)
{
	t_file	*file;

	file = cmd_node->file;
	while (file)
	{
		if (file->fd > 0)
			close(file->fd);
		file = file->next;
	}
	return (-1);
}

int	file_error(char *filename, t_command *cmd_node)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	if (filename)
	{
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	perror(NULL);
	return (close_files(cmd_node));
}

int	open_files(t_command *cmd_node)
{
	t_file	*file;
	int		res_dup;

	file = cmd_node->file;
	while (file)
	{
		if (file->is_heredoc || file->is_redirect_in)
			file->fd = open(file->name, O_RDONLY);
		else if (file->is_redirect_out)
			file->fd = open(file->name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			file->fd = open(file->name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (file->fd == -1)
			return (file_error(file->name, cmd_node));
		if (file->is_heredoc || file->is_redirect_in)
			res_dup = dup2(file->fd, STDIN_FILENO);
		else
			res_dup = dup2(file->fd, STDOUT_FILENO);
		if (res_dup == -1)
			return (file_error(NULL, cmd_node));
		file = file->next;
	}
	return (0);
}
