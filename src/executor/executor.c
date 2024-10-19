/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:40:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/10/19 10:48:59 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_builtin(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->builtins[i].name != NULL)
	{
		if (ft_strcmp(shell->cmd[0], shell->builtins[i].name) == 0)
			return (shell->builtins[i].func(shell));
		i++;
	}
	return (FAILURE);
}

char	*build_cmd(char *path, char *cmd)
{
	char	*command;

	command = ft_strjoin(path, cmd);
	if (!command)
		return (NULL);
	return (command);
}

void	print_error_cmd(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

void	execute_cmd(t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	if (access(shell->cmd[0], X_OK) == SUCCESS)
		execve(shell->cmd[0], shell->cmd, shell->env);
	while (shell->path[i] != NULL)
	{
		tmp = build_cmd(shell->path[i], shell->cmd[0]);
		if (!tmp)
			print_error("error cmd");
		if (access(tmp, X_OK) == SUCCESS)
			execve(tmp, shell->cmd, shell->env);
		free(tmp);
		i++;
	}
	print_error_cmd(shell->cmd[0]);
	exit(127);
}

int	restore_std_fds(int *std_fds)
{
	int	res_dup;

	res_dup = dup2(std_fds[0], STDIN_FILENO);
	if (res_dup == -1)
		return (1);
	close(std_fds[0]);
	res_dup = dup2(std_fds[1], STDOUT_FILENO);
	if (res_dup == -1)
		return (1);
	close(std_fds[1]);
	return (0);
}

int	handle_one_builtin(t_shell *shell)
{
	int	std_fds[2];
	int	status;
	int	restore_fds;

	std_fds[0] = dup(STDIN_FILENO);
	if (std_fds[0] == -1)
		return (1);
	std_fds[1] = dup(STDOUT_FILENO);
	if (std_fds[1] == -1)
		return (1);
	if (open_files(shell->cmd_node) == -1)
		return (1);
	shell->cmd = shell->cmd_node->cmd;
	close_files(shell->cmd_node);
	status = execute_builtin(shell);
	restore_fds = restore_std_fds(std_fds);
	if (restore_fds == 1)
		return (1);
	return (status);
}

int	execute(t_shell *shell)
{
	int			status;
	int			pid;
	int			total_cmds;
	t_command	*cmd_node;

	cmd_node = shell->cmd_node;
	if (!cmd_node->cmd)
		return (SUCCESS);
	total_cmds = total_commands(cmd_node);
	if (total_cmds == 1 && cmd_node->is_builtin)
		return (handle_one_builtin(shell));
	while (cmd_node)
	{
		shell->cmd = cmd_node->cmd;
		if (cmd_node->is_builtin)
			status = execute_builtin(shell);
		else
		{
			pid = fork();
			if (pid == -1)
				printf("Error creating fork\n");
			if (pid == 0)
				execute_cmd(shell);
			wait(&status);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
		}
		cmd_node = cmd_node->next;
	}
	return (status);
}
