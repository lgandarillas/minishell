/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:27:36 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/02 19:52:34 by lgandari         ###   ########.fr       */
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
	// RELLENAR EL ARRAY
	(void)shell;
}

void	handle_heredoc(t_command *cmd)
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
				if (!input->name)
					input->name = create_heredoc_filename(++num);
				if (!input->name)
					return ;
				fd = open_heredoc(input->name);
				if (fd < 0 || write_heredoc(fd, input->delimiter) < 0)
				{
					if (fd >= 0)
						close(fd);
					return ;
				}
				close(fd);
			}
			input = input->next;
		}
		cmd = cmd->next;
	}
}

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
