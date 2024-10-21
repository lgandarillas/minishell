/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_one_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:03:44 by lgandari          #+#    #+#             */
/*   Updated: 2024/10/21 18:03:46 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_dup(int *std_fds)
{
	std_fds[0] = dup(STDIN_FILENO);
	std_fds[1] = dup(STDOUT_FILENO);
	if (std_fds[0] == -1 || std_fds[1] == -1)
		return (FAILURE);
	return (SUCCESS);
}

int	handle_one_builtin(t_shell *shell)
{
	int	std_fds[2];
	int	status;

	if (handle_dup(std_fds) == FAILURE)
		return (FAILURE);
	if (open_files(shell->cmd_node) == -1)
	{
		restore_std_fds(std_fds);
		return (FAILURE);
	}
	shell->cmd = shell->cmd_node->cmd;
	close_files(shell->cmd_node);
	status = execute_builtin(shell);
	if (restore_std_fds(std_fds) == -1)
		return (FAILURE);
	return (status);
}

int	handle_one_child_process(t_shell *shell, int *std_fds)
{
	if (open_files(shell->cmd_node) == -1)
	{
		restore_std_fds(std_fds);
		exit(FAILURE);
	}
	shell->cmd = shell->cmd_node->cmd;
	close_files(shell->cmd_node);
	execute_cmd(shell);
	if (restore_std_fds(std_fds) == -1)
		exit(FAILURE);
	exit(SUCCESS);
}

int	handle_one_cmd(t_shell *shell)
{
	int	pid;
	int	std_fds[2];
	int	status;

	if (handle_dup(std_fds) == FAILURE)
		return (FAILURE);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit (FAILURE);
	}
	if (pid == 0)
		handle_one_child_process(shell, std_fds);
	waitpid(pid, &status, 0);
	if (restore_std_fds(std_fds) == -1)
		return (FAILURE);
	if (WIFEXITED(status) && WEXITSTATUS(status) == SUCCESS)
		return (SUCCESS);
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		return (127);
	else
		return (FAILURE);
}
