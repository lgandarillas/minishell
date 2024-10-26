/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multiple_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:52:55 by aquinter          #+#    #+#             */
/*   Updated: 2024/10/26 15:39:05 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipe_error(pid_t *pids)
{
	free(pids);
	perror("msh: pipe");
	return (FAILURE);
}

void	wait_processes(t_command *cmd_node, pid_t *pids, int *status)
{
	int	i;
	int	pid;
	int	total_cmds;

	i = 0;
	total_cmds = total_commands(cmd_node);
	while (i < total_cmds)
	{
		pid = wait(status);
		if (pid == -1)
		{
			*status = 1;
			return ;
		}
		if (pid == pids[total_cmds - 1])
		{
			if (WIFEXITED(*status) && WEXITSTATUS(*status) == SUCCESS)
				*status = SUCCESS;
			else if (WIFEXITED(*status) && WEXITSTATUS(*status) == 127)
				*status = 127;
		}
		i++;
	}
}

int	handle_first_process(t_shell *shell, t_command *cmd_node, int *main_tube)
{
	close(main_tube[0]);
	if (dup2(main_tube[1], STDOUT_FILENO) == -1)
	{
		perror("msh");
		exit(FAILURE);
	}
	if (open_files(cmd_node) == -1)
		exit(FAILURE);
	shell->cmd = cmd_node->cmd;
	close(main_tube[1]);
	close_files(cmd_node);
	execute_cmd(shell);
	exit(SUCCESS);
}

int	handle_mid_process(t_shell *shell, t_command *cmd_node, int *main_tube, int *aux_tube)
{
	close(aux_tube[0]);
	if (dup2(main_tube[0], STDIN_FILENO) == -1)
	{
		perror("msh");
		exit(FAILURE);
	}
	close(main_tube[0]);
	if (dup2(aux_tube[1], STDOUT_FILENO) == -1)
	{
		perror("msh");
		exit(FAILURE);
	}
	if (open_files(cmd_node) == -1)
		exit(FAILURE);
	shell->cmd = cmd_node->cmd;
	close(aux_tube[1]);
	close_files(cmd_node);
	execute_cmd(shell);
	exit(SUCCESS);
}

int	handle_last_process(t_shell *shell, t_command *cmd_node, int *main_tube)
{
	close(main_tube[1]);
	if (dup2(main_tube[0], STDIN_FILENO) == -1)
	{
		perror("msh");
		exit(FAILURE);
	}
	if (open_files(cmd_node) == -1)
		exit(FAILURE);
	shell->cmd = cmd_node->cmd;
	close(main_tube[0]);
	close_files(cmd_node);
	execute_cmd(shell);
	exit(SUCCESS);
}

int	handle_multiple_cmds(t_shell *shell, t_command *cmd_node)
{
	int		i;
	int		status;
	int		main_tube[2];
	int		aux_tube[2];
	pid_t	*pids;

	i = 0;
	pids = ft_calloc(sizeof(pid_t), total_commands(cmd_node));
	if (!pids)
	{
		perror("msh: malloc failure");
		return (FAILURE);
	}
	if (pipe(main_tube) == -1)
		return (pipe_error(pids));
	while (cmd_node)
	{
		if (cmd_node->next && i > 0)
		{
			if (pipe(aux_tube) == -1)
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
				handle_first_process(shell, cmd_node, main_tube);
			close(main_tube[1]);
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
				handle_mid_process(shell, cmd_node, main_tube, aux_tube);
			close(main_tube[0]);
			main_tube[0] = aux_tube[0];
			main_tube[1] = aux_tube[1];
			close(main_tube[1]);
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
				handle_last_process(shell, cmd_node, main_tube);
			close(main_tube[0]);
		}
		i++;
		cmd_node = cmd_node->next;
	}
	wait_processes(shell->cmd_node, pids, &status);
	free(pids);
	return (status);
}
