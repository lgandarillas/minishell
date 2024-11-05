/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multiple_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:52:55 by aquinter          #+#    #+#             */
/*   Updated: 2024/11/05 19:43:41 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	pipe_error(pid_t *pids)
{
	free(pids);
	perror("msh: pipe");
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

static void	handle_first_process(t_shell *shell, t_command *cmd_node, int *tube)
{
	close(tube[0]);
	if (dup2(tube[1], STDOUT_FILENO) == -1)
	{
		perror("msh");
		exit(FAILURE);
	}
	if (open_files(cmd_node) == -1)
		exit(FAILURE);
	shell->cmd = cmd_node->cmd;
	close(tube[1]);
	close_files(cmd_node);
	if (!shell->cmd)
		exit(SUCCESS);
	execute_cmd(shell);
}

static void	handle_mid_process(t_shell *shell, t_command *cmd_node, \
	int input, int *tube)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		perror("msh");
		exit(FAILURE);
	}
	close(input);
	if (dup2(tube[1], STDOUT_FILENO) == -1)
	{
		perror("msh");
		exit(FAILURE);
	}
	if (open_files(cmd_node) == -1)
		exit(FAILURE);
	shell->cmd = cmd_node->cmd;
	close(tube[1]);
	close_files(cmd_node);
	if (!shell->cmd)
		exit(SUCCESS);
	execute_cmd(shell);
}

static void	handle_last_process(t_shell *shell, t_command *cmd_node, int *tube)
{
	close(tube[1]);
	if (dup2(tube[0], STDIN_FILENO) == -1)
	{
		perror("msh");
		exit(FAILURE);
	}
	if (open_files(cmd_node) == -1)
		exit(FAILURE);
	shell->cmd = cmd_node->cmd;
	close(tube[0]);
	close_files(cmd_node);
	if (!shell->cmd)
		exit(SUCCESS);
	execute_cmd(shell);
}

int	handle_multiple_cmds(t_shell *shell, t_command *cmd_node)
{
	int		i;
	int		status;
	int		tube[2];
	int		input;
	pid_t	*pids;

	i = 0;
	pids = ft_calloc(sizeof(pid_t), shell->num_cmds);
	if (!pids)
	{
		perror("msh: malloc failure");
		return (FAILURE);
	}
	while (cmd_node)
	{
		if (cmd_node->next)
		{
			input = tube[0];
			if (pipe(tube) == -1)
				return (pipe_error(pids));
		}
		if (i == 0)
		{
			pids[i] = fork();
			if (pids[i] == -1)
			{
				perror("fork");
				free(pids);
				return (FAILURE);
			}
			if (pids[i] == 0)
				handle_first_process(shell, cmd_node, tube);
		}
		else if (cmd_node->next && i > 0)
		{
			pids[i] = fork();
			if (pids[i] == -1)
			{
				perror("fork");
				free(pids);
				return (FAILURE);
			}
			if (pids[i] == 0)
				handle_mid_process(shell, cmd_node, input, tube);
			close(input);
		}
		else
		{
			pids[i] = fork();
			if (pids[i] == -1)
			{
				perror("fork");
				free(pids);
				return (FAILURE);
			}
			if (pids[i] == 0)
				handle_last_process(shell, cmd_node, tube);
			close(tube[0]);
		}
		close(tube[1]);
		i++;
		cmd_node = cmd_node->next;
	}
	status = wait_processes(shell, pids);
	free(pids);
	return (status);
}
