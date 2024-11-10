/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:40:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/11/04 22:34:49 by aquinter         ###   ########.fr       */
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

void	print_error_cmd(char *cmd, int error_type, t_shell *shell)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (error_type == 1)
	{
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		shell->status = 126;
		exit(126);
	}
	else if (error_type == 2)
	{
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		shell->status = 127;
		exit(127);
	}
	else
	{
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		shell->status = 127;
		exit(127);
	}
}

void	execute_cmd(t_shell *shell)
{
	struct stat	info;
	char		*tmp;
	int			i;

	if (!shell->cmd || !shell->cmd[0])
		return ;
	i = 0;
	if (stat(shell->cmd[0], &info) == 0 && S_ISDIR(info.st_mode))
		print_error_cmd(shell->cmd[0], 1, shell);
	else if ((shell->cmd[0][0] == '/' || (shell->cmd[0][0] == '.' && \
		shell->cmd[0][1] == '/')) && access(shell->cmd[0], F_OK) != 0)
		print_error_cmd(shell->cmd[0], 2, shell);
	if (access(shell->cmd[0], X_OK) == SUCCESS)
		execve(shell->cmd[0], shell->cmd, shell->env);
	if (!shell->path)
		print_error_cmd(shell->cmd[0], 0, shell);
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
	print_error_cmd(shell->cmd[0], 0, shell);
}

int	execute(t_shell *shell)
{
	t_command	*cmd_node;

	cmd_node = shell->cmd_node;
	if (!cmd_node->cmd)
		return (SUCCESS);
	if (shell->num_cmds == 1 && cmd_node->is_builtin)
		return (handle_one_builtin(shell));
	else if (shell->num_cmds == 1 && !cmd_node->is_builtin)
		return (handle_one_cmd(shell));
	else
		return (handle_multiple_cmds(shell, cmd_node));
}
