/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:40:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/10/16 21:17:25 by aquinter         ###   ########.fr       */
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

int	handle_one_builtin(t_shell *shell)
{
	int	std_fds[2];

	std_fds[0] = dup(STDIN_FILENO);
	if (std_fds[0] == -1)
		return (1);
	std_fds[1] = dup(STDOUT_FILENO);
	if (std_fds[1] == -1)
		return (1);
	if (open_files(shell->cmd_node) == -1)
		return (1);
	shell->cmd = shell->cmd_node->cmd;
	return (execute_builtin(shell));	
}

int	execute(t_shell *shell)
{
	int	status;
	int	pid;
	int	total_cmds;

	if (!shell->cmd_node->cmd)
		return (SUCCESS);
	total_cmds = total_commands(shell->cmd_node);
	if (total_cmds == 1 && shell->cmd_node->is_builtin)
		return (handle_one_builtin(shell));		
	while (shell->cmd_node)
	{
		shell->cmd = shell->cmd_node->cmd;
		if (shell->cmd_node->is_builtin)
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
		shell->cmd_node = shell->cmd_node->next;
	}
	return (status);
}
