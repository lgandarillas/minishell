/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:48:16 by aquinter          #+#    #+#             */
/*   Updated: 2024/11/13 22:55:22 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_hd_eof(char *delimiter)
{
	ft_putstr_fd("msh: warning: here-document delimited ", STDERR_FILENO);
	ft_putstr_fd("by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
	return (0);
}

int	handle_hd_signal_status(char *line, t_shell *shell)
{
	free(line);
	shell->status = 130;
	return (-1);
}
