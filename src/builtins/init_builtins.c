/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:48:36 by aquinter          #+#    #+#             */
/*   Updated: 2024/08/22 17:58:28 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_builtins(t_shell *shell)
{
	shell->builtins[0].name = "echo";
	shell->builtins[0].func = ft_echo;
	shell->builtins[1].name = "cd";
	shell->builtins[1].func = ft_cd;
	shell->builtins[2].name = "pwd";
	shell->builtins[2].func = ft_pwd;
	shell->builtins[3].name = "export";
	shell->builtins[3].func = ft_export;
	shell->builtins[4].name = "unset";
	shell->builtins[4].func = ft_unset;
	shell->builtins[5].name = "env";
	shell->builtins[5].func = ft_env;
	shell->builtins[6].name = "exit";
	shell->builtins[6].func = ft_exit;
	shell->builtins[7].name = NULL;
	shell->builtins[7].func = NULL;
}
