/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:46:23 by lgandari          #+#    #+#             */
/*   Updated: 2024/11/13 22:38:47 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execution_failure(pid_t *pids)
{
	free(pids);
	perror("msh");
	return (FAILURE);
}

void	catch_status(int status, bool *newline)
{
	if (WIFSIGNALED(status) && *newline == true)
	{
		if (128 + WTERMSIG(status) == 131)
			printf("Quit\n");
		else if (128 + WTERMSIG(status) == 130)
			printf("\n");
		*newline = false;
	}
}

int	wait_processes(t_shell *shell, pid_t *pids)
{
	int		i;
	int		status;
	bool	newline;

	i = 0;
	status = 0;
	newline = true;
	while (i < (shell->num_cmds - 1))
	{
		waitpid(pids[i], &status, 0);
		catch_status(status, &newline);
		i++;
	}
	waitpid(pids[i], &status, 0);
	catch_status(status, &newline);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	return (status);
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
