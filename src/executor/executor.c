/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:40:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/22 18:26:58 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	init_builtins(t_builtin *builtins)
{
	builtins[0].name = "echo";
	builtins[0].func = ft_echo;
	builtins[1].name = "cd";
	builtins[1].func = ft_cd;
	builtins[2].name = "pwd";
	builtins[2].func = ft_pwd;
	builtins[3].name = "export";
	builtins[3].func = ft_export;
	builtins[4].name = "unset";
	builtins[4].func = ft_unset;
	builtins[5].name = "env";
	builtins[5].func = ft_env;
	builtins[6].name = "exit";
	builtins[6].func = ft_exit;
	builtins[7].name = NULL;
	builtins[7].func = NULL;
}

int	execute_builtin(t_shell *shell)
{
	int			i;
	t_builtin	builtins[8];

	i = 0;
	init_builtins(builtins);
	while (builtins[i].name != NULL)
	{
		if (ft_strcmp(shell->cmd[0], builtins[i].name) == 0)
			return (builtins[i].func(shell));
		i++;
	}
	return (FAILURE);
}
