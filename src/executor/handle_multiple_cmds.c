/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multiple_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:52:55 by aquinter          #+#    #+#             */
/*   Updated: 2024/10/26 14:23:36 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
			if (WIFEXITED(*status))
				*status = WEXITSTATUS(*status);
			else if (WIFSIGNALED(*status))
				*status = 128 + WTERMSIG(*status);
			else if (WIFSTOPPED(*status))
				*status = 128 + WSTOPSIG(*status);
		}
		i++;
	}
}

int	handle_first_process(t_shell *shell, t_command *cmd_node, int *pipe_fd)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("msh");
		exit(FAILURE);
	}
	if (open_files(cmd_node) == -1)
		exit(FAILURE);
	shell->cmd = cmd_node->cmd;
	close(pipe_fd[1]);
	close_files(cmd_node);
	execute_cmd(shell);
	exit(SUCCESS);
}

int	handle_mid_process(t_shell *shell, t_command *cmd_node, int *pipe_fd)
{
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("msh");
		exit(FAILURE);
	}
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("msh");
		exit(FAILURE);
	}
	if (open_files(cmd_node) == -1)
		exit(FAILURE);
	shell->cmd = cmd_node->cmd;
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close_files(cmd_node);
	execute_cmd(shell);
	exit(SUCCESS);
}

int	handle_last_process(t_shell *shell, t_command *cmd_node, int *pipe_fd)
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("msh");
		exit(FAILURE);
	}
	if (open_files(cmd_node) == -1)
		exit(FAILURE);
	shell->cmd = cmd_node->cmd;
	close(pipe_fd[0]);
	close_files(cmd_node);
	execute_cmd(shell);
	exit(SUCCESS);
}

int	handle_multiple_cmds(t_shell *shell, t_command *cmd_node)
{
	int		i;
	int		status;
	int		pipe_fd[2];
	pid_t	*pid;

	i = 0;
	pid = ft_calloc(sizeof(pid_t), total_commands(cmd_node));
	if (!pid)
	{
		perror("msh: malloc failure");
		return (FAILURE);
	}
	while (cmd_node)
	{
		if (cmd_node->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("msh: pipe");
				return (FAILURE);
			}
		}
		if (i == 0)
		{
			pid[i] = fork();
			if (pid[i] == -1)
			{
				perror("fork");
				free(pid);
				return (FAILURE);
			}
			if (pid[i] == 0)
				handle_first_process(shell, cmd_node, pipe_fd);
		}
		else if (cmd_node->next)
		{
			pid[i] = fork();
			if (pid[i] == -1)
			{
				perror("fork");
				free(pid);
				return (FAILURE);
			}
			if (pid[i] == 0)
				handle_mid_process(shell, cmd_node, pipe_fd);
		}
		else
		{
			pid[i] = fork();
			if (pid[i] == -1)
			{
				perror("fork");
				free(pid);
				return (FAILURE);
			}
			if (pid[i] == 0)
				handle_last_process(shell, cmd_node, pipe_fd);
		}
		i++;
		cmd_node = cmd_node->next;
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait_processes(shell->cmd_node, pid, &status);
	free(pid);
	return (status);
}
