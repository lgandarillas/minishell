/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:40:38 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/15 17:57:28 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo(t_shell *shell)
{
	if (ft_strcmp(shell->cmd[1], "$?") == 0)
		printf("%d\n", shell->status);
	else
		printf("%s\n", shell->cmd[1]);
	return (SUCCESS);
}