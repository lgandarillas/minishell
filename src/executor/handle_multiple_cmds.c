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

static pid_t	*get_array_pid(t_shell *shell)
{
	pid_t	*pids;

	pids = ft_calloc(sizeof(pid_t), shell->num_cmds);
	if (!pids)
	{
		perror("msh: malloc failure");
		return (NULL);
	}
	return (pids);
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

int	handle_multiple_cmds(t_shell *shell, t_command *cmd_node)
{
	int		i;
	int		status;
	int		tube[2];
	int		input;
	pid_t	*pids;

	i = 0;
	pids = get_array_pid(shell);
	if (!pids)
		return (FAILURE);
	while (cmd_node)
	{
		input = tube[0];
		if (cmd_node->next && pipe(tube) == -1)
			return (execution_failure(pids));
		pids[i] = fork();
		if (pids[i] == -1)
			return (execution_failure(pids));
		if (pids[i] == 0)
			handle_process(shell, cmd_node, input, tube);
		close(input);
		close(tube[1]);
		if (!cmd_node->next)
			close(tube[0]);
		i++;
		cmd_node = cmd_node->next;
	}
	status = wait_processes(shell, pids);
	free(pids);
	return (status);
}
