/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:27:36 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/04 20:51:32 by lgandari         ###   ########.fr       */
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

static int	write_heredoc(int fd, const char *delimiter, bool expand)
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
		//if (expand == true)
		//	output_line = expand_heredoc_line(line);
		//else
		if (expand == false)
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

static int	handle_single_heredoc(t_input *input, int num, bool expand)
{
	int	fd;

	if (!input->name)
		input->name = create_heredoc_filename(num);
	if (!input->name)
		return (-1);
	fd = open_heredoc(input->name);
	if (fd < 0 || write_heredoc(fd, input->delimiter, expand) < 0)
	{
		if (fd >= 0)
			close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

void	handle_heredoc(t_command *cmd)
{
	t_input	*input;
	int		num;

	num = 0;
	while (cmd)
	{
		input = cmd->input;
		while (input)
		{
			if (input->is_heredoc)
			{
				if (handle_single_heredoc(input, ++num, false) < 0)
					return ;
			}
			input = input->next;
		}
		cmd = cmd->next;
	}
}
