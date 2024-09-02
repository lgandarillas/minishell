/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:27:36 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/02 15:56:39 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*create_heredoc_filename(int temp_num)
{
	char	*num_str;
	char	*file_name;

	num_str = ft_itoa(temp_num);
	if (!num_str)
		return (NULL);
	file_name = ft_strjoin("/tmp/.heredoc", num_str);
	free(num_str);
	return (file_name);
}

static int	open_heredoc(int num)
{
	char	*filename;
	int		fd;

	filename = create_heredoc_filename(num);
	if (!filename)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(filename);
	return (fd);
}

static int	write_heredoc(int fd, const char *delimiter)
{
	char	*line;
	
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
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

bool	handle_heredoc(t_command *cmd)
{
	t_input	*input;
	int		num;
	int		fd;

	num = 0;
	while (cmd)
	{
		input = cmd->input;
		while (input)
		{
			if (input->is_heredoc)
			{
				num++;
				fd = open_heredoc(num);
				if (fd < 0 || write_heredoc(fd, input->delimiter) < 0)
				{
					if (fd >= 0)
						close(fd);
					return (false);
				}
				close(fd);
			}
			input = input->next;
		}
		cmd = cmd->next;
	}
	return (true);
}

void	delete_heredoc_files(t_command *cmd)
{
	t_input	*input;
	char	*filename;
	int		num;

	num = 0;
	while (cmd)
	{
		input = cmd->input;
		while (input)
		{
			if (input->is_heredoc)
			{
				num++;
				filename = create_heredoc_filename(num);
				if (filename)
				{
					unlink(filename);
					free(filename);
				}
			}
			input = input->next;
		}
		cmd = cmd->next;
	}
}
