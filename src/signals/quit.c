/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:58:01 by aquinter          #+#    #+#             */
/*   Updated: 2024/08/06 19:05:15 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putnbr_fd(sig, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}