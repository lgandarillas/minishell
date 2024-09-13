/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:27:36 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/13 13:28:02 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*create_heredoc_filename(int temp_num)
{
	char	*num_str;
	char	*filename;

	num_str = ft_itoa(temp_num);
	if (!num_str)
		return (NULL);
	filename = ft_strjoin("/tmp/.heredoc", num_str);
	free(num_str);
	return (filename);
}

static int	open_heredoc(const char *filename)
{
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

static int	write_heredoc(int fd, char *delimiter, bool expand, t_shell *shell)
{
	char	*line;
	char	*output_line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (-1);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (expand == true)
			output_line = expand_heredoc_line(line, shell);
		else
			output_line = ft_strdup(line);
		free(line);
		if (!output_line)
			return (-1);
		ft_putstr_fd(output_line, fd);
		write(fd, "\n", 1);
		free(output_line);
	}
	return (0);
}

static int	handle_single_heredoc(t_file *file, \
				int num, bool expand, t_shell *shell)
{
	int	fd;

	if (!file->name)
		file->name = create_heredoc_filename(num);
	if (!file->name)
		return (-1);
	fd = open_heredoc(file->name);
	if (fd < 0 || write_heredoc(fd, file->delimiter, expand, shell) < 0)
	{
		if (fd >= 0)
			close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

void	handle_heredoc(t_command *cmd, t_shell *shell)
{
	t_file	*file;
	bool	expand;
	int		num;

	num = 0;
	while (cmd)
	{
		file = cmd->file;
		while (file)
		{
			if (file->is_heredoc)
			{
				if (shell->expand_heredoc[num] == true)
					expand = true;
				else
					expand = false;
				if (handle_single_heredoc(file, num, expand, shell) < 0)
					return ;
				num++;
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
}
