/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multiple_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:52:55 by aquinter          #+#    #+#             */
/*   Updated: 2024/11/08 17:34:15 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
