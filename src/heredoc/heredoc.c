/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:27:36 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/02 12:05:18 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Recibe un número y devuelve el nombre del archivo
char	*create_heredoc_filename(int temp_num)
{
	char	*num_str;
	char	*file_name;

	num_str = ft_itoa(temp_num);
	if (!num_str)
		return (NULL);
	file_name = ft_strjoin("/tmp/heredoc", num_str);
	free(num_str);
	return (file_name);
}

// Abrir un heredoc concreto dado un número
int	open_heredoc(int num)
{
	char	*filename;
	int		fd;

	filename = create_heredoc_filename(num);
	if (!filename)
		return (-1);
	fd = -1;
	if (access(filename, F_OK) == 0)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	free(filename);
	return (fd);
}

// Escribe en un heredoc dado un fd y un delimitador
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

/*
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
*/
