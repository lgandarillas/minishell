/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interrupt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:57:26 by aquinter          #+#    #+#             */
/*   Updated: 2024/11/13 22:04:49 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_sigint(int sig)
{
	ft_putchar_fd('\n', STDERR_FILENO);
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = 1;
	}
}

void	handle_heredoc_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		ioctl(0, TIOCSTI, "\n");
		g_sig = 2;
	}
}
