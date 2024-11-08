/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multiple_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:52:55 by aquinter          #+#    #+#             */
/*   Updated: 2024/11/05 22:26:47 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	execution_failure(pid_t *pids)
{
	free(pids);
	perror("msh");
	return (FAILURE);
}

static int	wait_processes(t_shell *shell, pid_t *pids)
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

static bool	handle_tube(t_command *cmd_node, int input, int *tube)
{
	if (cmd_node->role == CMD_MIDDLE || cmd_node->role == CMD_FINAL)
	{
		if (dup2(input, STDIN_FILENO) == -1)
		{
			perror("msh");
			return (false);
		}
		close(input);
	}
	if (cmd_node->role == CMD_INITIAL || cmd_node->role == CMD_MIDDLE)
	{
		if (dup2(tube[1], STDOUT_FILENO) == -1)
		{
			perror("msh");
			return (false);
		}
	}
	return (true);
}

static void	handle_process(t_shell *shell, t_command *cmd_node, int input, \
	int *tube)
{
	int	exit_code;

	if (!handle_tube(cmd_node, input, tube))
		exit(FAILURE);
	close(tube[0]);
	close(tube[1]);
	if (open_files(cmd_node) == -1)
		exit(FAILURE);
	close_files(cmd_node);
	shell->cmd = cmd_node->cmd;
	if (!shell->cmd)
		exit(SUCCESS);
	if (!cmd_node->is_builtin)
		execute_cmd(shell);
	exit_code = execute_builtin(shell);
	exit(exit_code);
}

static t_multiple_cmds	*init_multiple_cmds(t_shell *shell)
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

static void	free_multiple_cmds(t_multiple_cmds *vars)
{
	if (vars)
	{
		free(vars->pids);
		free(vars);
	}
}

static int	exec_cmd_chain(t_shell *shell, t_command *cmd_node, \
	t_multiple_cmds *vars)
{
	int	input;

	input = vars->tube[0];
	if (cmd_node->next && pipe(vars->tube) == -1)
		return (execution_failure(vars->pids));
	(vars->pids)[vars->i] = fork();
	if ((vars->pids)[vars->i] == -1)
		return (execution_failure(vars->pids));
	if ((vars->pids)[vars->i] == 0)
		handle_process(shell, cmd_node, input, vars->tube);
	close(input);
	close((vars->tube)[1]);
	if (!cmd_node->next)
		close((vars->tube)[0]);
	(vars->i)++;
	return (SUCCESS);
}

/*NEW*/

static t_multiple_cmds	*init_multiple_cmds(t_shell *shell)
{
	t_multiple_cmds	*vars;

	vars = malloc(sizeof(t_multiple_cmds));
	if (!vars)
		return (NULL);
	vars->i = 0;
	vars->input = 0;
	vars->pids = ft_calloc(sizeof(pid_t), shell->num_cmds);
	if (!vars->pids)
	{
		free(vars);
		return (NULL);
	}
	return (vars);
}

static void	free_multiple_cmds(t_multiple_cmds *vars)
{
	if (vars)
	{
		free(vars->pids);
		free(vars);
	}
}

/* NEW */
static int	handle_fork(t_multiple_cmds *vars)
{
	(vars->pids)[vars->i] = fork();
	if ((vars->pids)[vars->i] == -1)
	{
		perror("fork");
		free(vars->pids);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	handle_process(t_shell *shell, t_command *cmd_node, \
		t_multiple_cmds *vars)
{
	if (vars->i == 0)
	{
		if (handle_fork(vars) == FAILURE)
			return (FAILURE);
		if ((vars->pids)[vars->i] == 0)
			handle_first_process(shell, cmd_node, vars->tube);
	}
	else if (cmd_node->next && vars->i > 0)
	{
		if (handle_fork(vars) == FAILURE)
			return (FAILURE);
		if ((vars->pids)[vars->i] == 0)
			handle_mid_process(shell, cmd_node, vars->input, vars->tube);
		close(vars->input);
	}
	else
	{
		if (handle_fork(vars) == FAILURE)
			return (FAILURE);
		if ((vars->pids)[vars->i] == 0)
			handle_last_process(shell, cmd_node, vars->tube);
		close((vars->tube)[0]);
	}
	close((vars->tube)[1]);
	(vars->i)++;
	return (SUCCESS);
}

int	handle_multiple_cmds(t_shell *shell, t_command *cmd_node)
{
	t_multiple_cmds	*vars;
	int				status;

	vars = init_multiple_cmds(shell);
	if (!vars)
	{
		perror("msh: malloc failure");
		return (FAILURE);
	}
	while (cmd_node)
	{
		if (exec_cmd_chain(shell, cmd_node, vars) == FAILURE)
			return (FAILURE);
		cmd_node = cmd_node->next;
	}
	status = wait_processes(shell, vars->pids);
	free_multiple_cmds(vars);
	return (status);
}
