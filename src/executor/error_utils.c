/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:01:56 by lgandari          #+#    #+#             */
/*   Updated: 2024/11/10 17:02:12 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_error_cmd(char *cmd, int error_type, t_shell *shell)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (error_type == 1)
	{
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		shell->status = 126;
		exit(126);
	}
	else if (error_type == 2)
	{
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		shell->status = 127;
		exit(127);
	}
	else
	{
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		shell->status = 127;
		exit(127);
	}
}
