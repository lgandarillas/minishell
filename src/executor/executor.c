/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:40:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/22 17:56:22 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_builtin(t_shell *shell)
{
	if (ft_strcmp(*(shell->cmd), "echo") == 0)
		return (ft_echo(shell));
	if (ft_strcmp(*(shell->cmd), "cd") == 0)
		return (ft_cd(shell));
	if (ft_strcmp(*(shell->cmd), "pwd") == 0)
		return (ft_pwd(shell));
	if (ft_strcmp(*(shell->cmd), "export") == 0)
		return (ft_export(shell));
	if (ft_strcmp(*(shell->cmd), "unset") == 0)
		return (ft_unset((shell)));
	if (ft_strcmp(*(shell->cmd), "env") == 0)
		return (ft_env(shell));
	if (ft_strcmp(*(shell->cmd), "exit") == 0)
		return (ft_exit(shell));
	return (FAILURE);
}
