/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:46:23 by lgandari          #+#    #+#             */
/*   Updated: 2024/11/08 17:46:26 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execution_failure(pid_t *pids)
{
	free(pids);
	perror("msh");
	return (FAILURE);
}

int	wait_processes(t_shell *shell, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < (shell->num_cmds - 1))
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	waitpid(pids[i], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	else
		return (status);
	return (SUCCESS);
}

t_multiple_cmds	*init_multiple_cmds(t_shell *shell)
{
	t_multiple_cmds	*vars;

	vars = malloc(sizeof(t_multiple_cmds));
	if (!vars)
		return (NULL);
	vars->i = 0;
	vars->pids = ft_calloc(sizeof(pid_t), shell->num_cmds);
	if (!vars->pids)
	{
		free(vars);
		return (NULL);
	}
	return (vars);
}

void	free_multiple_cmds(t_multiple_cmds *vars)
{
	if (vars)
	{
		free(vars->pids);
		free(vars);
	}
}
