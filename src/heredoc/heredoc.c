/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:27:36 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/01 16:34:07 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*create_filename(int temp_num)
{
	char	*num_str;
	char	*file_name;

	num_str = ft_itoa(temp_num);
	if (!num_str)
		return (NULL);
	file_name = ft_strjoin("/tmp/heredoc_", num_str);
	free(num_str);
	return (file_name);
}

int	open_heredoc(char **file_name, int *temp_num)
{
	char	*file_path;
	int		fd;

	file_path = create_filename(*temp_num);
	if (!file_path)
		return (-1);
	while (access(file_path, F_OK) == 0)
	{
		(*temp_num)++;
		free(file_path);
		file_path = create_filename(*temp_num);
		if (!file_path)
			return (-1);
	}
	fd = open(file_path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	free(file_path);
	return (fd);
}

int	write_heredoc(int fd, const char *delimiter)
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

void	heredoc_sigint(int signal)
{
	rl_on_new_line();
	rl_redisplay();
	signal(SIGINT, SIG_DFL);
}

void	heredoc_signals(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

char	*expand_heredoc(char *input)
{
	char	*result;

	// FINISH CODE
	return (result);
}
