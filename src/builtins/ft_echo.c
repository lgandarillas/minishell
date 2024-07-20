/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:40:38 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/20 14:10:30 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo(t_shell *shell)
{
	int		i;
	int		j;
	bool	newline;

	i = 1;
	newline = true;
	while (shell->cmd[i] && shell->cmd[i][0] == '-' && shell->cmd[i][1] == 'n')
	{
		j = 1;
		while (shell->cmd[i][j] == 'n')
			j++;
		if (shell->cmd[i][j] == '\0')
			newline = false;
		else
			break ;
		i++;
	}
	while (shell->cmd[i] != NULL)
	{
		printf("%s", shell->cmd[i]);
		i++;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}
