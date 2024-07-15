/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:40:38 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/15 22:17:22 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	ft_echo(t_shell *shell)
{
	if (ft_strcmp(shell->cmd[1], "$?") == 0)
		printf("%d\n", shell->status);
	else
		printf("%s\n", shell->cmd[1]);
	return (true);
}
